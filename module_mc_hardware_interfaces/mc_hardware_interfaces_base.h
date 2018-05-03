#pragma once

#include <stdint.h>

#ifdef __cplusplus

enum class BASE_RESULT {
	OK                  = 0,            // Операция успешна произведена.
    TIME_OUT            = 1,            // Был произведён выход по истечении времени ожидания.
    LENGTH_ERROR        = 2,            // Попытка передать/принять пакет 0-й длины.
    ERROR_INIT          = 3,
	NOT_DATA			= 4,			// Нет запрашиваемых данных.
};

#define check_result( base_result_variable )			if ( base_result_variable != BASE_RESULT::OK ) return base_result_variable;

#endif
