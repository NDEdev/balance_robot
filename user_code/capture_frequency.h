#pragma once

#include "timer.h"
#include "freertos_headers.h"

/*!
 * Структура соотношения таймер-канал.
 */
struct captureFrequencyChannelCfg {
	TimCapture*			timer;
	uint8_t 			channel;
};

struct CaptureFrequencyCfg {
	captureFrequencyChannelCfg*			channelCfg;
	uint32_t 							channelCount;

	uint32_t							taskPrio;
};

/*!
 * Текущее состояние каждого из каналов.
 */
struct captureChannelState {
	float					frequency;				/// Текущая частота на канале.
	uint32_t				updateTick;				/// Время с последнего обновления на канале.
	bool	 				flagResCh;				/// Был ли канал перезагружен
													/// (детектированы помехи или слишком высокая частота).
													/// Сбрасывается вычеткой из cli.
	uint8_t					resetChannelCount;		/// Количество перезагрузок таймера с последнего считывания.
};

/*!
 * Метод предназначен для получения захваченной
 * частоты с перечня таймеров с возможностью вывода через CLI.
 */
class CaptureFrequency {
public:
	CaptureFrequency( const CaptureFrequencyCfg* const cfg ) :
			cfg( cfg ) {}

	void		reinit									( void );

	/*!
	 * Метод возвращает количество падений
	 * канала между предыдущим считыванием и текущим.
	 *
	 * Если канала не существует, то вернется 0.
	 */
	uint32_t	getBlockChannelStatus					( const uint32_t channel );

	static	int		cli ( const void *obj, char *arg, char *buf, int buf_size );


private:
	const CaptureFrequencyCfg*	const cfg;				/// Массив конфигураций каналов.

	SemaphoreHandle_t			m;						/// Mutex на данные каналов.

	captureChannelState*		channelState;			/// Текущее состояние каждого из каналов.

	/// Задача мониторит все каналы.
	static	void	task		( void *obj );
};
