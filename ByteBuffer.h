#pragma once

#include<stdint.h>
#include<stdlib.h>

class ByteBuffer {
	public:
		ByteBuffer(int Size);

		void Write_8(uint8_t Data);
		void Write_16(uint16_t Data);
		void Write_32(uint32_t Data);

		uint8_t* Buffer;
		int Pointer;
		int Size;

		~ByteBuffer();
};
