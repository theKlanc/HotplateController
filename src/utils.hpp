#pragma once
#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>

//PINS
const uint32_t TEMP_PROBE_PIN = 26;
const uint32_t HEATER_PWM_PIN = 6;

//Queues
extern QueueHandle_t tempQueue;
extern QueueHandle_t pwmQueue;
