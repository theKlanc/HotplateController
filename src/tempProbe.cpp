#include "FreeRTOS.h"
#include "tempProbe.hpp"
#include "task.h"
#include "pico/multicore.h"
#include <cstdio>

TaskHandle_t temp_task_handle;

void TEMP_TASK(){
    while(1){ 
        printf("TEMP %d\n", get_core_num());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
