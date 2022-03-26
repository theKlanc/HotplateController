#pragma once
#include "FreeRTOS.h"
#include "task.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern TaskHandle_t temp_task_handle;

void TEMP_TASK();

#ifdef __cplusplus
}
#endif