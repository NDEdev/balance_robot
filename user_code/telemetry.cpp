/*
 * telemetry.cpp
 *
 *  Created on: May 9, 2018
 *      Author: demid
 */

#include "telemetry.h"
#include "cobs_ex.h"


Telemetry::Telemetry(UartBase *_uart) : uart(_uart) {
	configASSERT(_uart);
	telemetryListResponded = false;
	queueHandle = USER_OS_STATIC_QUEUE_CREATE(100, sizeof(uint8_t), queueStorage, &queueStruct);
	USER_OS_STATIC_TASK_CREATE(telemetryThread, "rxTelem", TASK_STACK_SIZES, this, 3, p_stack, &p_struct);
}

Telemetry::~Telemetry() {

}

void Telemetry::telemetryThread(void *p){
	Telemetry *o = (Telemetry*) p;
	mc_plot_package::package recv_pckg;
	int rxLn = 0, txLn = 0, txLnTmp = 0;
	uint8_t tmpTxBuff[sizeof(mc_plot_package::package)];
	uint8_t txBuff[sizeof(mc_plot_package::package)+10]; // +10 оверхед для кобса с запасом

	mc_plot_package::telemetry_list_item tm_item;
	mc_plot_package tm_pkt(mc_plot_package::REPLAY_TELEMETRY_LIST);

	while(true){
		rxLn = 0;
		txLn = 0;
		txLnTmp = 0;
		// Получаем пакет от глобального парсера
		rxLn = USER_OS_QUEUE_RECEIVE(o->queueHandle, &recv_pckg, portMAX_DELAY);

		auto it = o->list.begin();

		switch(recv_pckg.id){
		case mc_plot_package::REQUEST_TELEMETRY_LIST:
			// отправим всю зарегистрированную телемтрию

			if(it == o->list.end())
				continue; // В списке не зарегестрировано не одного параметра

			for(; it != o->list.end(); ++it ){
				tm_item.item_id = it->second;
				strcpy(tm_item.item_name, it->first.c_str());
				tm_item.total_item_count = o->list.size();

				tm_pkt.fill_payload((uint8_t*)&tm_item, tm_item.size());
				txLnTmp = tm_pkt.assemble_to_binary(tmpTxBuff, sizeof(tmpTxBuff));
				txLn = cobs_ex::cobs_encode(tmpTxBuff, txLnTmp,  txBuff);
				o->uart->tx(txBuff, sizeof(txBuff), 50);
			}

			// Разрешаем передачу телеметрии клиенту
			o->telemetryFlowSet(true);
			break;

		case mc_plot_package::DISABLE_TELEM_FLOW:
			o->telemetryFlowSet(false);
			break;
		}

	}
}


bool Telemetry::registry(std::string name){
	bool rv = true;
	mc_plot_package::item_id_t newId = 0;

	// определим id для регистрируемого кадра телеметрии
	auto it = list.rbegin();

	if(it == list.rend()){
		newId = 1; // Нет ни одного зарегестрированного элемента
	}else{
		newId = it->second + 1;
	}

	auto result = list.insert(std::pair<std::string, mc_plot_package::item_id_t>(name, newId));

	if(result.second == false)
		rv = false; // имя кадра уже зарегистрировано

	return rv;
}

bool Telemetry::sendValue(std::string name, float val, uint32_t time_us){
	bool rv = true;

	if(!telemetryListResponded)
		return false; // список телеметрии не отправлен. клиент не готов к приёму телеметрии

	// проверка зарегестировано ли имя параметра
	auto search = list.find(name);

	if(search == list.end())
		return false;  // данный кадр не зарегистрирован

	// получим id соответсвующий имени кадра
	mc_plot_package::item_id_t id =  search->second;

	// собираем полезную нагрузку пакета
	mc_plot_package::parametr_item payload;
	payload.item_id = id;
	payload.time_us = time_us;
	payload.accuracy_coeff = 1000;
	payload.value = val * payload.accuracy_coeff;

	// собираем кадр для отправки
	mc_plot_package	pakege(mc_plot_package::PARAMETR_MSG);
	pakege.fill_payload((uint8_t*)&payload, payload.size());

	// преобразуем в бинарный формат для передачи
	uint8_t buff[0xFF] = {0};
	int len = pakege.assemble_to_binary(buff, sizeof(buff));

	// кодируем бинарный пакет в протоколом cobs
	uint8_t send_buf[0xFF];
	int tx_len = cobs_ex::cobs_encode(buff, len, send_buf);

	//посылаем данные в интерфейс
	if(uart->tx(send_buf, tx_len) != BASE_RESULT::OK)
		rv = false;

	return rv;
}

bool Telemetry::sendMessage(std::string message, uint32_t time_us){
	bool rv = true;

	if(!telemetryListResponded)
		return false; // список телеметрии не отправлен. клиент не готов к приёму телеметрии

	// собираем полезную нагрузку пакета
	mc_plot_package::event_item payload;
	payload.event_time_us = time_us;
	if(message.size() < sizeof(payload.event_msg))
			strcpy(payload.event_msg, message.c_str());

	// собираем кадр для отправки
	mc_plot_package	pakege(mc_plot_package::EVENT_MSG);
	pakege.fill_payload((uint8_t*)&payload, payload.size());

	// преобразуем в бинарный формат для передачи
	uint8_t buff[0xFF] = {0};
	int len = pakege.assemble_to_binary(buff, sizeof(buff));

	// кодируем бинарный пакет в протоколом cobs
	uint8_t send_buf[0xFF];
	int tx_len = cobs_ex::cobs_encode(buff, len, send_buf);

	//посылаем данные в интерфейс
	if(uart->tx(send_buf, tx_len) != BASE_RESULT::OK)
		rv = false;

	return rv;
}

void Telemetry::telemetryFlowSet(bool state){
	telemetryListResponded = state;
}
