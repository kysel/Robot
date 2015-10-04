#include "..\..\..\..\..\..\..\SysGCC\arm-eabi\arm-eabi\sys-include\stdint.h"


typedef struct
{
	uint8_t header1;
	uint8_t header2;
	uint8_t id;
	uint8_t length; // length does not include first 4 bytes
	uint8_t instruction; // or error for status packets
	uint8_t parameter[250]; // reserve for maximum packet size
	uint8_t checksum; // Needs to be copied at end of parameters
} DynamixelPacket;

typedef struct
{
	uint8_t* data_str_;
	uint8_t data_length_t_;
} SendableData;

void PacketToByteArray(DynamixelPacket* packet, SendableData* data)
{
	data->data_str_[0] = packet->header1;
	data->data_str_[1] = packet->header2;
	data->data_str_[2] = packet->id;
	data->data_str_[3] = packet->length;
	data->data_str_[4] = packet->instruction;
	for (uint8_t i = 0; i != packet->length - 2; i++)
		data->data_str_[5 + i] = packet->parameter[i];
	data->data_str_[packet->length + 3] = packet->checksum;
	data->data_length_t_ = packet->length + 3;
}

void CreateMovePacket(DynamixelPacket* packet, uint8_t id, uint16_t position)
{
	packet->header1 = 0xff;
	packet->header2 = 0xff;
	packet->id = id;
	packet->length = 5;
	packet->instruction = 0x03; //write data
	packet->parameter[0] = 0x1e;
	packet->parameter[1] = position & 0xff;
	packet->parameter[2] = (position >> 8) & 0xff;

	uint8_t checksum = 0;
	for (uint8_t i = 2; i < packet->length + 3; i++)
	{
		checksum += ((uint8_t*)packet)[i];
	}
	checksum ^= 0xff; //xor
	packet->checksum = checksum;
}