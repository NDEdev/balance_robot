/*
 * telemetry.h
 *
 *  Created on: May 9, 2018
 *      Author: demid
 */

#ifndef USER_CODE_TELEMETRY_H_
#define USER_CODE_TELEMETRY_H_

#include "mc_hardware_interfaces_uart.h"
#include "mc_data_plot_api.h"
#include <string>
#include <map>
#include "user_os.h"


class Telemetry {
	typedef std::map<std::string, mc_plot_package::item_id_t> telem_list_t;

	UartBase 		*uart;
	telem_list_t 	list;
	bool 			telemetryListResponded; // Список телеметрии отправлен по запросу. Клиент готов к приёму сообщений.


public:
	Telemetry	(UartBase *_uart);
	virtual ~Telemetry();

	bool registry		(std::string name);
	bool sendValue		(std::string name, float val, uint32_t time_us);
	bool sendMessage	(std::string message);
};

#endif /* USER_CODE_TELEMETRY_H_ */

