#include "Dynamixel.hpp"

Dynamixel Bus;

Dynamixel::Dynamixel() {
	this->rxQueue = xQueueCreate(40, sizeof(uint8_t));
	osSemaphoreDef(xRxSemaphore);
	xRxSemaphoreHandle = osSemaphoreCreate(osSemaphore(xRxSemaphore), 1);
}

void Dynamixel::Init(UART_HandleTypeDef* huart) {
	uart_ = huart;
}

void Dynamixel::Send(uint8_t* data, uint8_t length) {
	HAL_UART_Transmit_DMA(uart_, data, length);
}

void Dynamixel::Receive(uint8_t* buffer, uint8_t length) {
	HAL_UART_Receive_DMA(uart_, buffer, length);
}

//Dynamixel::~Dynamixel() {}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	osSemaphoreRelease(Bus.xRxSemaphoreHandle);
}
