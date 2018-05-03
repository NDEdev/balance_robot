#pragma once

#include <stdint.h>

class AdcOneChannelBase {
public:
	//**********************************************************************
	// Метод должен:
	// 1. Отключить ADC.
	// 2. Сконфигурировать ADC и его канал в заданный режим
	// (на один объект один канал и 1 ражим).
	// После переинициализации ADC должен остаться отключенным.
	//**********************************************************************
	virtual bool reinit							( void )	const = 0;

	//**********************************************************************
	// Методы должены включать/отключать ADC (не перетерая поля регистров).
	//**********************************************************************
	virtual void clkEnable						( void )	const = 0;
	virtual void clkDisable						( void )	const = 0;

	//**********************************************************************
	// Метод должен инициировать новое измерение и выйти,
	// не дожидаясь его окончания.
	//**********************************************************************
	virtual bool startContinuousConversion		( void )	const = 0;
	virtual bool stopContinuousConversion		( void )	const = 0;

	//**********************************************************************
	// Метод получает результат измерения (если таковой доступен).
	// В противном случае сообщает о неудаче.
	//**********************************************************************
	virtual void getMeasurement					( uint32_t& channelMeasurement )	const = 0;
};