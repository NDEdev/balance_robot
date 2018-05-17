#include "capture_frequency.h"

void CaptureFrequency::reinit ( void ) {
	this->m = xSemaphoreCreateMutex();		                                                        // Для предотвращения доступа к пользовательским функциям одновременно из разных потоков.
	xTaskCreate( this->task, "capFreq", 200, this, this->cfg->taskPrio, NULL );
}

void CaptureFrequency::task ( void *obj ) {
	CaptureFrequency* o		=	( CaptureFrequency* )obj;

	/// Выделяем память под вектор состояния каналов.
	o->channelState			=	static_cast< captureChannelState* >
								( pvPortMalloc( sizeof( captureChannelState ) * o->cfg->channelCount ) );
	configASSERT( o->channelState );

	/// Для точного отсчета времени.
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while( true ) {
		xSemaphoreTake ( o->m, portMAX_DELAY );
		/// Перезаполняем данные каналов,
		/// на это время трогать вектор
		/// состояния из других потоков или CLI запрещено.
		for ( uint32_t channelNumber = 0; channelNumber < o->cfg->channelCount; channelNumber++ ) {
			if ( o->cfg->channelCfg[ channelNumber ].timer->getStateChannel(
					o->cfg->channelCfg[ channelNumber ].channel
			) ) {
				/// Если был захват.
				if ( o->cfg->channelCfg[ channelNumber ].timer->getFlagCaptureChannel(
						o->cfg->channelCfg[ channelNumber ].channel
				) ) {
					o->channelState[ channelNumber ].updateTick		= 0;	/// Мы обновили данные о канале.

					/// Забираем частоту на канале.
					o->cfg->channelCfg[ channelNumber ].timer->getFrequency(
							o->cfg->channelCfg[ channelNumber ].channel,
							o->channelState[ channelNumber ].frequency
					);
				} else {
					o->channelState[ channelNumber ].updateTick++;			/// Канал жив, но захвата нет.

					/// Для теста!
					o->channelState[ channelNumber ].frequency = 0;
				}
			} else {										/// Канала нет или он лежит.
				o->channelState[ channelNumber ].flagResCh		= true;		/// Указываем, что канал мертв.
				o->channelState[ channelNumber ].updateTick++;				/// Считаем время до воскрешения.
				o->channelState[ channelNumber ].resetChannelCount++;		/// Указываем факт того, что на
																			/// этой миллисекунде канал падал.
				/*!
				 * Работаем по переполнению так как в автопилоте с телеметрией так удобней работать (измерять интервалы между запросами телеметрии геморой)
				 */
			}
		}

		xSemaphoreGive ( o->m );

		vTaskDelayUntil( &xLastWakeTime, 1 );
	}
}

uint32_t CaptureFrequency::getBlockChannelStatus ( const uint32_t channel ) {
	if ( channel >= this->cfg->channelCount ) return 0;
	uint32_t returnValue =  this->channelState[ channel ].resetChannelCount;
	return returnValue;
}

#define CAPTURE_FREQUENCY_HELP_STRING			"Usage {cmd} {channel}\n"		\
												"Channel may be value: 0..%lu\n\n"

#define CAPTURE_FREQUENCY_CHANNEL_ERROR_STRING	"Channel number wrong!\n"		\
												"Channel may be value: 0..%lu\n\n"

#define CAPTURE_FREQUENCY_CHANNEL_DATA_STRING	"Channel:\t\t\t%lu\n"				\
												"Frequency:\t\t\t%f\n"				\
												"Frequency update time:\t\t%lu\n"	\
												"Reset channel flag:\t\t%lu\n\n"

int CaptureFrequency::cli ( const void *obj, char *arg, char *buf, int buf_size ) {
	CaptureFrequency *o = ( CaptureFrequency* ) obj;		/// Нам передали основной объект.

	/// Считываем номер канала или пустоту.
	int countArg;
	uint32_t channel;
	countArg = sscanf( arg, "%lu", &channel );

	if ( countArg != 1 ) {
		snprintf ( buf, buf_size, CAPTURE_FREQUENCY_HELP_STRING, o->cfg->channelCount );
		return 0;

	} else {
		if ( channel >= o->cfg->channelCount ) {
			snprintf ( buf, buf_size, CAPTURE_FREQUENCY_CHANNEL_ERROR_STRING, o->cfg->channelCount );
			return 0;
		}

		xSemaphoreTake ( o->m, portMAX_DELAY );

		snprintf ( buf, buf_size, CAPTURE_FREQUENCY_CHANNEL_DATA_STRING,
				   channel,
				   o->channelState[ channel ].frequency,
				   o->channelState[ channel ].updateTick,
				   o->channelState[ channel ].flagResCh );

		/// Флаг был вычитан.
		o->channelState[ channel ].flagResCh = false;

		xSemaphoreGive ( o->m );
	}

	return 0;
}
