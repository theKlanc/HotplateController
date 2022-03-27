#include "FreeRTOS.h"
#include "heater.hpp"
#include "task.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include <cstdio>
#include "utils.hpp"

TaskHandle_t heater_task_handle;

const unsigned period = 100;

void HEATER_TASK(){
    gpio_set_function(HEATER_PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(HEATER_PWM_PIN);
    pwm_set_wrap(slice_num, period);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(HEATER_PWM_PIN), 0);
    pwm_set_enabled(slice_num, true);
    while(1){
        float pidOutput;
        xQueueReceive(pwmQueue, &pidOutput, portMAX_DELAY);
        pwm_set_chan_level(slice_num, pwm_gpio_to_channel(HEATER_PWM_PIN), period * pidOutput);
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
