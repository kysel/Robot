#pragma once
#include <stdint.h>

class Motor
{
private:
	uint8_t current_id_t_;
public:
	Motor();
	Motor &operator [](const uint8_t id);

	~Motor();
};