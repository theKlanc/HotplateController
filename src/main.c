/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "queue.h"
#include "utils.hpp"
#include "controller.hpp"
#include "heater.hpp"
#include "display.hpp"
#include "pidController.hpp"
#include "pidController.hpp"
#include "tempProbe.hpp"

auto_init_mutex(xSDKMutex);
static semaphore_t xSDKSemaphore;

QueueHandle_t tempQueue;
QueueHandle_t pwmQueue;

QueueHandle_t displayPWMQueue;
QueueHandle_t displayTempQueue;

QueueHandle_t targetTempQueue;

static void nonRTOSWorker(){
    printf("Core %d: NonRTOSWorker\n", get_core_num());
    while (true) {
        sleep_ms(1200);
    }
}

static void launchRTOS(){
    printf("Core %d: Launching FreeRTOS scheduler\n", get_core_num());
    vTaskStartScheduler();
    panic_unsupported();
}

static void setup( void )
{
    /* Want to be able to printf */
    stdio_init_all();
    /* And flash LED */
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
}

int main(void){
    setup();


    tempQueue = xQueueCreate(1, sizeof(float));
    pwmQueue = xQueueCreate(1, sizeof(float));

    displayTempQueue = xQueueCreate(1, sizeof(float));
    displayPWMQueue = xQueueCreate(1, sizeof(float));

    targetTempQueue = xQueueCreate(1, sizeof(float));

    xTaskCreate(HEATER_TASK, "heater_task", 512, NULL, (configMAX_PRIORITIES-1), &heater_task_handle);
    xTaskCreate(PID_TASK, "pid_task", 512, NULL, (configMAX_PRIORITIES-1), &PID_task_handle);
    xTaskCreate(TEMP_TASK, "temp_task", 512, NULL, (configMAX_PRIORITIES-1), &temp_task_handle);
    xTaskCreate(DISPLAY_TASK, "display_task", 512, NULL, (configMAX_PRIORITIES-1), &display_task_handle);
    xTaskCreate(CONTROLLER_TASK, "controller_task", 512, NULL, (configMAX_PRIORITIES-1), &controller_task_handle);
    
    launchRTOS();
}
