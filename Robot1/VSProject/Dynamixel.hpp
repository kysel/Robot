#pragma once
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "queue.h"


class Dynamixel
{
private:
	UART_HandleTypeDef* uart_;
public:
	SemaphoreHandle_t xRxSemaphoreHandle;
	QueueHandle_t rxQueue;
	Dynamixel();
	void Init(UART_HandleTypeDef* huart);
	void Send(uint8_t* data, uint8_t length);
	void Receive(uint8_t* buffer, uint8_t length);
};

extern Dynamixel Bus;

