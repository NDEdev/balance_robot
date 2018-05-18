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
}

Telemetry::~Telemetry() {

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
