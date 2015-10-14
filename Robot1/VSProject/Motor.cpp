#include "Motor.hpp"

Motor::Motor()
{
	int i = 0;
}

Motor& Motor::operator[](const uint8_t id)
{
	current_id_t_ = id;
	return *this;
}



Motor::~Motor()
{
}
