#pragma once
#include "FreeRTOS.h"
#include "task.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern TaskHandle_t PID_task_handle;

void PID_TASK();

#ifdef __cplusplus
}
#endif