#include "FreeRTOS.h"
#include "pidController.hpp"
#include "task.h"
#include "pico/multicore.h"
#include <cstdio>

#include "PID.h"

TaskHandle_t PID_task_handle;

float getTemp(){
    return 51;
}

void setPWM(float duty){
    //printf("PWM Output: %f\n", duty);
    return;
}

void PID_TASK(){
    PIDController<float> pidController(1,1,1, getTemp, setPWM);
    pidController.setInputBounds(-50, 500);
    pidController.setOutputBounds(0, 1);
    pidController.registerTimeFunction(time_us_32);
    pidController.setEnabled(true);
    while(1){ 
        pidController.setTarget(50);
        pidController.tick();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
