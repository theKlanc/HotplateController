#include "display.hpp"
#include "utils.hpp"
#include "queue.h"
#include <cstdio>

TaskHandle_t display_task_handle;

void DISPLAY_TASK(){
    float pwm, temp;
    while(true){
        float p;
        if(xQueueReceive(displayPWMQueue, &p, 10) == pdTRUE){
            pwm = p;
        }
        float t;
        if(xQueueReceive(displayTempQueue, &t, 10) == pdTRUE){
            temp = t;
        }

        printf("Temp: %3f\n", temp);
        printf("PWM:  %3f\n", pwm);
        printf("\n\n");
        
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}