#include "FreeRTOS.h"
#include "tempProbe.hpp"
#include "task.h"
#include "utils.hpp"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/multicore.h"
#include <cstdio>

TaskHandle_t temp_task_handle;

void TEMP_TASK(){
    adc_init();
    adc_gpio_init(TEMP_PROBE_PIN);
    float temperature = 0;

    while(1){ 
        uint16_t adcData = adc_read();
        printf("temp: %d\n", adcData);
        //read adc
        //convert to temp
        //if diff(temps) > 1
        //  push temp to queue
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
