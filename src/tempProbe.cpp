#include "FreeRTOS.h"
#include "tempProbe.hpp"
#include "task.h"
#include "utils.hpp"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/multicore.h"
#include <cstdio>
#include <cmath>

TaskHandle_t temp_task_handle;

float getVoltage(){
    const float conversion_factor = 3.3f / (1 << 12);
    return adc_read() * conversion_factor;    
}

const int R = 4700;

int calculateResistance(float v){
    const float V = 3.3;
    float r1 = (v/((V-v)/(float)R));
    return r1;
}


float calculateTemperature(float r){
    //Steinhart-Hart coeffs
    const float A = 0.6444018963e-3;
    const float B = 2.277383708e-4;
    const float C = 0.5745683866e-7;
    // 1/T = A + BlnR + C (lnR)^3
    float temp =1.0/(A + B*log(r) + (C * (pow(log(r),3))));
    return temp;
}

void TEMP_TASK(){
    adc_init();
    adc_gpio_init(TEMP_PROBE_PIN);
    float oldTemp = 0;

    while(1){
        const unsigned adcIterations = 3;
        float v = 0;
        for(int i = 0; i < adcIterations; i++){
            v += getVoltage();
        }
        v /= adcIterations;
        float r = calculateResistance(v);
        float t = calculateTemperature(r) - 273;
        if(abs(t-oldTemp) > 2){
            oldTemp = t;
            xQueueSend(tempQueue, &t, portMAX_DELAY);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
