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
#define TASK_STACK_SIZES 	300
#define QUEUE_LEN			10
#define QUEUE_ITEM_SIZE		sizeof(mc_plot_package::package)
	typedef std::map<std::string, mc_plot_package::item_id_t> telem_list_t;

	UartBase 		*uart;
	telem_list_t 	list;
	bool 			telemetryListResponded; // Список телеметрии отправлен по запросу. Клиент готов к приёму сообщений.

	//поток разобра сообщений от клиента
	static void 		telemetryThread		(void *p);
	USER_OS_STATIC_STACK_TYPE 				p_stack[TASK_STACK_SIZES];
	USER_OS_STATIC_TASK_STRUCT_TYPE			p_struct;

	USER_OS_STATIC_QUEUE					queueHandle;	// Сюда приходят данне от глобального парсера в виде пакетов телеметрии
	USER_OS_STATIC_QUEUE_STRUCT				queueStruct;
	uint8_t									queueStorage[QUEUE_LEN*QUEUE_ITEM_SIZE];
public:
	Telemetry	(UartBase *_uart);
	virtual ~Telemetry();

	bool init			(void);

	bool registry			(std::string name);  // Регистрация телеметрии дожна происходить до запуска потоков
	bool sendValue			(std::string name, float val, uint32_t time_us);
	bool sendMessage		(std::string message, uint32_t time_us);
	void telemetryFlowSet	(bool state); // enable/disable
};

#endif /* USER_CODE_TELEMETRY_H_ */

