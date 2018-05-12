/*
 * mpu6500.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */


#include "mpu6500.h"
#include "string.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#ifndef M_PI
	#define M_PI           3.14159265358979323846
#endif

#define MPU_WHO_AM_I_VALUE 0x70

//таблица адресов
typedef const struct {
	uint8_t who_am_i;
	uint8_t smplrt_div;//rate_div;
	uint8_t xg_offset_h;//
	uint8_t xg_offset_l;//
	uint8_t yg_offset_h;//
	uint8_t yg_offset_l;//
	uint8_t zg_offset_h;//
	uint8_t zg_offset_l;//
	uint8_t config;//
	uint8_t fifo_en;//
	uint8_t gyro_config;//gyro_cfg;
	uint8_t accel_config;//accel_cfg;
	uint8_t accel_config2;//accel_cfg2;

	uint8_t raw_accel;
	uint8_t int_pin_cfg;
	uint8_t int_enable;
	uint8_t int_status;
	uint8_t user_ctrl;
	uint8_t accel_offsets;
	uint8_t gyro_offsets;
} mpu6500_reg_table_t;

__attribute__ ((section(".rodata")))
mpu6500_reg_table_t mpu_regs = {
	//Таблица регистров (стр. 6 "RM-MPU-6500A-00.pdf")
    .who_am_i       = 0x75,
	.smplrt_div		= 0x19,//делитель частоты, 1кГц делится на (1 + smplrt_div)

	.xg_offset_h	= 0x13,
	.xg_offset_l	= 0x14,
	.yg_offset_h	= 0x15,
	.yg_offset_l	= 0x16,
	.zg_offset_h	= 0x17,
	.zg_offset_l	= 0x18,
	.config 		= 0x1A, //R/W Конфигурация (cтр. 13)
							//[7] - зарезервирован
							//[6] - FIFO_MODE "1" - если буфер заполнен, новые данные не записываются
							//		"0" - новые данные замещают старые
							//[5:3] - EXT_SYNC_SET[2:0] Enables the FSYNC pin data to be sampled
							//[2:0] - DLPF_CFG
							//		  конфигурируется DLPF_CFG ,
							//		  когда FCHOICE_B [ 1 : 0 ] = 2b'00 .
							//		  Гироскоп и датчик температуры фильтруются
							//		  в соответствии со значением DLPF_CFG
							//		  и FCHOICE_B

	.fifo_en  		= 0x23, //R/W Регистр разрешения буфера FIFO (cтр. 18)
								//		  Reset value: 0x00 (function is disabled)
	.gyro_config	= 0x1B,	//R/W	Gyroscope Configuration	(cтр. 14)
							//[7] - X Gyro self-test
							//[6] - Y Gyro self-test
							//[5] - Z Gyro self-test
							//[4:3] - Gyro Full Scale Select
							//		00 = ±250dps
							//		01 = ±500dps
							//		10 = ±1000dps
							//		11 = ±2000dps
							//[2] - Reserved
							//[1:0] - Used to bypass DLPF as shown in the table above
	.accel_config	= 0x1C, 	//R/W	Accelerometer Configuration (cтр. 15)
							//		Reset value: 0x00
							//[7] - XA_ST	X Accel self-test
							//[6] - YA_ST	Y Accel self-test
							//[5] - ZA_ST	Z Accel self-test
							//[4:3]- 	ACCEL_FS_SEL[1:0]
							//			Accel Full Scale Select:
							//			±2g (00), ±4g (01), ±8g (10), ±16g (11)
							//[2:0]	- Reserved
	.accel_config2	= 0x1D,	//R/W  Accelerometer Configuration 2	(стр. 15)
							//		Reset value: 0x00
							//[7:4] - Reserved
							//[3] - ACCEL_FCHOICE_B  Used to bypass DLPF as shown in the table below.
							//[2:0] - A_DLPF_CFG Accelerometer low pass filter setting as shown in the second table below

    .raw_accel      = 0x3B, //
	.int_pin_cfg 	= 0x37, //R/W INT Pin / Bypass Enable Configuration (cтр. 29)
							//		  Reset value: 0x00
							//[7] - ACTL	1 – The logic level for INT pin is active low.
							//				0 – The logic level for INT pin is active high.
							//[6] - OPEN	1 – INT вывод настроен как выход с открытым стоком
							//				0 – INT pin is configured as push-pull
							//[5] - LATCH_INT_EN	1 – INT pin level held until interrupt status is cleared
							//				0 – INT pin indicates interrupt pulse’s is width 50 mks
							//[4] - INT_ANYRD_2CLEAR	1 – Состояние прерывания очищается, если выполняются операции чтения
							//				0 – Interrupt status is cleared only by reading INT_STATUS register
							//[3] - ACTL_FSYNC	1 – The logic level for the FSYNC pin as an interrupt is active low
							//				0 – The logic level for the FSYNC pin as an interrupt is active high
							//[2] - FSYNC_INT_MODE_EN	1 – This enables the FSYNC pin to be used as an interrupt
							//				0 – This disables the FSYNC pin from causing an interrupt.
							//[1] - BYPASS_EN	1 – This enables the FSYNC pin to be used as an interrupt
							//				0 – This disables the FSYNC pin from causing an interrupt.
							//[0] - Reserved
	.int_enable		= 0x38, //R/W Interrupt Enable (cтр. 29)
							//[7] - Reserved
							//[6] - WOM_EN 	1 - Enable interrupt for wake on motion to propagate to interrupt pin.
							//				0 - function is disabled
							//[5] - Reserved
							//[4] - FIFO_OVERFLOW_EN 	1 - Enable interrupt for FIFO overflow to propagate to interrupt pin.
							//[3] - FSYNC_INT_EN		1 - Enable FSYNC interrupt to propagate to interrupt pin	0 - function is disabled
							//[2] - Reserved
							//[1] - Reserved
							//[0] - RAW_RDY_EN		1 - Enable Raw Sensor Data Ready interrupt	0 - function is disabled
	.int_status		= 0x3A, // R/C Interrupt Status. Reset value: 0x00 (cтр. 30)
							//[7] - Reserved
							//[6] - WOM_INT  	1 - Wake on motion interrupt occurred
							//[5] - Reserved
							//[4] - FIFO_OVERFLOW_INT
							//[3] - FSYNC_INT 	1 – FSYNC interrupt occurred.
							//[2] - Reserved
							//[1] - DMP_INT 	This bit automatically sets to 1 when the DMP interrupt has been generated.
							//[0] - RAW_DATA_RDY_INT
	.user_ctrl		= 0x6A,	//[0] - полный резет, остальные биты не используются
	.accel_offsets = 0x77,	//offset accell registers:  int16 offsetX int16 offsetY int16 offsetZ
	.gyro_offsets = 0x13,	//offset gyro registers:  int16 offsetX int16 offsetY int16 offsetZ
};


Mpu6500::Mpu6500(SpiMaster8BitBase *_spi):  spi(_spi){
	sync = nullptr;
	mutex = nullptr;
	extSync = nullptr;
	inited = false;
	calibration_enable = false;
}

Mpu6500::~Mpu6500(){

}

bool Mpu6500::init(void){
	bool rv = false;

	if(!spi)
		return false;

	if(spi->reinit() == BASE_RESULT::OK){
		spi->on();
		rv = true;
	}

	mutex = USER_OS_STATIC_MUTEX_CREATE(&mutexBuff);
	sync = USER_OS_STATIC_BIN_SEMAPHORE_CREATE(&syncBuff);
	extSync = USER_OS_STATIC_BIN_SEMAPHORE_CREATE(&extSyncBuff);
	USER_OS_STATIC_TASK_CREATE( mpuThread, "mpuTask", TASK_STACK_SIZES, this, 3, this->p_stack, &this->p_struct );

	return rv;
}

void Mpu6500::mpuThread(void *p){
	Mpu6500 *o = (Mpu6500*) p;
	uint8_t buf[32];

	if(!o){
		configASSERT(o);
	}

	//check who_am_i
	while (1) {
		buf[0] = 1;//инициируем полный сброс
		o->data_write ( buf, mpu_regs.user_ctrl, 1);
		vTaskDelay (100);

		o->data_read ( buf, mpu_regs.who_am_i, 1);
		if ( buf[0] == MPU_WHO_AM_I_VALUE ) {
			break;
		}
	}

	//config MPU

	//Настраиваем частоту семплирования
	buf[0] = 3;//SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV),	where INTERNAL_SAMPLE_RATE = 1kHz
	o->data_write (buf, mpu_regs.smplrt_div, 1);

	//выставляем цифровую фильтрацию - фильтрация отсутствует, при этом частота 1кгц
	buf[0] = 1;
	o->data_write (buf, mpu_regs.config, 1);

	//Установка диапазонов измерения акселерометра и гироскопа
	o->set_range(ACCEL_RANGE, GYRO_RANGE, 0b00);

	//Настраиваем ножку прерываний - активный уровень - 1, висит пока причина прерывания не устранится
	buf[0] = 1<<5;
	o->data_write (buf, mpu_regs.int_pin_cfg, 1);

	//Разрешаем прерывания по готовности данных
	buf[0] = 1;
	o->data_write (buf, mpu_regs.int_enable, 1);

	//Считываем состояния регистров (для проверки правильности установки данных)
	o->data_read (buf, mpu_regs.int_enable, 1);
	o->int_enable = buf[0];
	o->data_read (buf, mpu_regs.accel_config, 1);
	o->accel_config = buf[0];
	o->data_read (buf, mpu_regs.accel_config2, 1);
	o->accel_config2 = buf[0];

	o->set_accel_offsets(0,0,0);
	o->set_gyro_offsets(0,0,0);

	//Инициализация завершена
	o->inited = true;
	uint32_t TaskTickCountOld = xTaskGetTickCount();//Прошлое значение системного таймера

	while(true){

		if(USER_OS_TAKE_SEMAPHORE(o->sync, 100) != pdTRUE){
			//возможно, контроллер пропустил фронт сигнала и мы все время сидим в режиме "есть данные"
			//обнулим статус наличия данных (и соответственно сигнал прерывания) чтением регистра статуса прерываний
			o->data_read (buf, mpu_regs.int_status, 1);
			continue;
		}

		TickType_t dt = xTaskGetTickCount() - TaskTickCountOld;//Считаем интервал между прерываниями в системных тиках
		TaskTickCountOld = xTaskGetTickCount();//Текущее значение системного таймера стало прошлым

		if ( o->data_read ( buf, mpu_regs.int_status, 15) ) {
			if ( USER_OS_TAKE_MUTEX ( o->mutex, (TickType_t) 10 ) == pdTRUE ) {

				o->accelGyroRaw[0] = ((int16_t)(buf[1]<<8) + buf[2]);
				o->accelGyroRaw[1] = ((int16_t)(buf[3]<<8) + buf[4]);
				o->accelGyroRaw[2] = ((int16_t)(buf[5]<<8) + buf[6]);

				o->accelGyroRaw[3] = ((int16_t)(buf[9]<<8) + buf[10]);
				o->accelGyroRaw[4] = ((int16_t)(buf[11]<<8) + buf[12]);
				o->accelGyroRaw[5] = ((int16_t)(buf[13]<<8) + buf[14]);

				//Ручная калибровка
				o->accelGyroRaw[0] -= 8700;
				o->accelGyroRaw[1] += 11300;
				o->accelGyroRaw[2] -= 200;
				o->accelGyroRaw[3] -= 8;
				o->accelGyroRaw[4] -= 153;
				o->accelGyroRaw[5] += 153;

				o->accel[0] = o->accelGyroRaw[0] * o->acc_scale;// * -1
				o->accel[1] = o->accelGyroRaw[1] * o->acc_scale;// * -1
				o->accel[2] = o->accelGyroRaw[2] * o->acc_scale;// * -1

				o->gyro[0] = o->accelGyroRaw[3] * o->gyro_scale;
				o->gyro[1] = o->accelGyroRaw[4] * o->gyro_scale;
				o->gyro[2] = o->accelGyroRaw[5] * o->gyro_scale;
				o->tempr = ( ((buf[7] << 8) | buf[8]) - MPU6500_TEMP_OFFSET) / MPU6500_TEMP_SENSIVITY + 21.0;

				USER_OS_GIVE_MUTEX ( o->mutex );
			}
			if (o->extSync != NULL) {
				USER_OS_GIVE_BIN_SEMAPHORE(o->extSync);
			}
		}
	}
}

bool Mpu6500::data_write(void *buf, uint8_t addr, int l){
	BASE_RESULT rv = BASE_RESULT::INPUT_VALUE_ERROR;

	if ( (l<0) || l>256 ) {
		return false;
	}

	uint8_t lbuf[l+1];
	lbuf[0] = addr & ~(1<<7);
	memcpy ( &lbuf[1], buf, l );
	rv = spi->tx(lbuf, l+1 );

	if ( rv != BASE_RESULT::OK) return false;

	return true;
}

bool Mpu6500::data_read(void *buf, uint8_t addr, int l){
	BASE_RESULT rv = BASE_RESULT::INPUT_VALUE_ERROR;

	if ( (l<0) || l>256 ) {
		return false;
	}
	uint8_t bufLen = l+1;
	uint8_t lbuf[bufLen];
	uint8_t rxbuf[bufLen];
	lbuf[0] = addr | (1<<7);
	rv = spi->tx((uint8_t*)lbuf, rxbuf, bufLen);

	if ( rv != BASE_RESULT::OK) return false;

	memcpy ( buf, &rxbuf[1], l );

	return true;
}

//Установка диапазонов измерения акселерометра и гироскопа
bool Mpu6500::set_range(int acell_range, int gyro_range, uint8_t fchoice_b ){
	uint8_t reg_value;
	//Устанавливаем диапазон измерения акселерометра
	switch ( acell_range ) {
		case 2:
			reg_value = 0b00000000;
			this->acc_scale = 9.8 * (float) 1/4096; // ! пока не ясно почему но здесь такой коэфицент деления
			break;

		case 4:
			reg_value = 0b00001000;
			this->acc_scale = 9.8 * (float) 1/8192;
			break;

		case 8:
			reg_value = 0b00010000;
			this->acc_scale = 9.8 * (float) 1/4096;
			break;

		case 16:
			reg_value = 0b00011000;
			this->acc_scale = 9.8 * (float) 1/2048;
			break;

		default:
			configASSERT(0);
	}

	if( !data_write ( &reg_value, mpu_regs.accel_config, 1) )
		return false;


	//Устанавливаем диапазон измерения акселерометра
	switch ( gyro_range ) {
		case 250:
			reg_value = 0b00000000;
			this->gyro_scale = (float) (M_PI/180) / 131;
			break;

		case 500:
			reg_value = 0b00001000;
			this->gyro_scale = (float) (M_PI/180) /65.6;
			break;

		case 1000:
			reg_value = 0b00010000;
			this->gyro_scale = (float) (M_PI/180) /32.8;
			break;

		case 2000:
			reg_value = 0b00011000;
			this->gyro_scale = (float) (M_PI/180) /16.4;
			break;

		default:
			configASSERT(0);
	}
	reg_value |= fchoice_b & 0b11;

	if( !data_write (&reg_value, mpu_regs.gyro_config, 1) )
		return false;

}

/*!
 * Метод записывает в ПЗУ mpu6500 значения смещения акселерометров
 */
bool Mpu6500::set_accel_offsets(int16_t x_offser, int16_t y_offset, int16_t z_offset){
	mpu6500_offsets_t accel_offsets;
	accel_offsets.offset_x = x_offser;
	accel_offsets.offset_y = y_offset;
	accel_offsets.offset_z = z_offset;
	return data_write(&accel_offsets, mpu_regs.accel_offsets, sizeof(accel_offsets));
}

/*!
 * Метод записывает в ПЗУ mpu6500 значения смещения гироскопов
 */
bool Mpu6500::set_gyro_offsets(int16_t x_offser, int16_t y_offset, int16_t z_offset){
	mpu6500_offsets_t gyro_offsets;
	gyro_offsets.offset_x = x_offser;
	gyro_offsets.offset_y = y_offset;
	gyro_offsets.offset_z = z_offset;
	return data_write(&gyro_offsets, mpu_regs.gyro_offsets, sizeof(gyro_offsets));
}

bool Mpu6500::read_offsets (uint8_t addr, mpu6500_offsets_t *d){
	bool rv = false;
	mpu6500_offsets_t offsets;
	rv = data_read(&offsets, addr, sizeof(offsets));

	if(rv)
		*d = offsets;

	return rv;
}

typedef struct {
	int16_t accX;
	int16_t accY;
	int16_t accZ;
	int16_t gyroX;
	int16_t gyroY;
	int16_t gyroZ;
}rawData_t;


void Mpu6500::solutionReadyIrqHandler(void){
	USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR(sync, NULL);
}

bool	Mpu6500::getSolBlocked(Mpu::mpu_sol_t &sol){
	bool rv = false;

	if(USER_OS_TAKE_SEMAPHORE(extSync, portMAX_DELAY) == pdTRUE){
		if ( USER_OS_TAKE_MUTEX ( mutex, (TickType_t) portMAX_DELAY ) == pdTRUE ) {
			sol.gyro[0] = gyro[0];
			sol.gyro[1] = gyro[1];
			sol.gyro[2] = gyro[2];

			sol.accel[0] = accel[0];
			sol.accel[1] = accel[1];
			sol.accel[2] = accel[2];

			sol.tempr = tempr;
			rv = true;
			USER_OS_GIVE_MUTEX ( mutex );
		}
	}
	return rv;
}

bool	Mpu6500::getSol(Mpu::mpu_sol_t &sol){
	bool rv = false;

	if ( USER_OS_TAKE_MUTEX ( mutex, (TickType_t) portMAX_DELAY ) == pdTRUE ) {
		sol.accel[0] = gyro[0];
		sol.accel[1] = gyro[1];
		sol.accel[2] = gyro[2];

		sol.accel[0] = accel[0];
		sol.accel[1] = accel[1];
		sol.accel[2] = accel[2];

		sol.tempr = tempr;
		rv = true;
		USER_OS_GIVE_MUTEX ( mutex );
	}

	return rv;
}

bool 	Mpu6500::isReadyToWork(void){
	return inited;
}

