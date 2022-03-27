#pragma once
#include "FreeRTOS.h"
#include "task.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern TaskHandle_t controller_task_handle;

void CONTROLLER_TASK();

#ifdef __cplusplus
}
#endif