#include "FreeRTOS.h"
#include "pidController.hpp"
#include "task.h"
#include "queue.h"
#include "utils.hpp"
#include "pico/multicore.h"
#include <cstdio>

#include "PID.h"

TaskHandle_t PID_task_handle;

float getTemp(){
    float temp;
    xQueueReceive(tempQueue, &temp, portMAX_DELAY);
    return temp;
}

void setPWM(float duty){
    xQueueSend(displayPWMQueue, &duty, 0);
    xQueueSend(pwmQueue, &duty, portMAX_DELAY);
}

void PID_TASK(){
    PIDController<float> pidController(5,0.05,0, getTemp, setPWM);
    pidController.setInputBounds(-50, 500);
    pidController.setOutputBounds(0, 1);
    pidController.registerTimeFunction(time_us_32);
    float target = 250;
    pidController.setTarget(target);
    pidController.setEnabled(true);
    while(1){
        xQueueReceive(targetTempQueue, &target, 0);
        pidController.setTarget(target);
        pidController.tick();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
