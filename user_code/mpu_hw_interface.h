/*
 * mpu_hw_interface.h
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */

#ifndef USER_CODE_MPU_HW_INTERFACE_H_
#define USER_CODE_MPU_HW_INTERFACE_H_

#ifdef __cplusplus

#include <vector>

namespace Mpu{


/*!
 * mpu_sol_t:
 * 	angrate_x
 * 	angrate_y
 * 	angrate_z
 * 	accel_x
 * 	accel_y
 * 	accel_z
 */
typedef  std::vector<float> 	mpu_sol_t;

class MpuInterface {
public:

/*!
 * Блокирующий запрос рещения инерциалки.
 * Синхронизируется по вычитыванию данных из микросхемы
 * Возвращается true в случае успеха
 */
	virtual bool getSolBlocked(mpu_sol_t &sol) = 0;

/*!
 *  Возвращает true если все инициализировано и готово к работе
 */
	virtual bool isReadyToWork() = 0;

};

}

#endif

#endif /* USER_CODE_MPU_HW_INTERFACE_H_ */
