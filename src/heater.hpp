#pragma once
#include "FreeRTOS.h"
#include "task.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern TaskHandle_t heater_task_handle;

void HEATER_TASK();

#ifdef __cplusplus
}
#endif