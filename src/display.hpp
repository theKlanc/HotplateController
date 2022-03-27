#pragma once
#include "FreeRTOS.h"
#include "task.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern TaskHandle_t display_task_handle;

void DISPLAY_TASK();

#ifdef __cplusplus
}
#endif