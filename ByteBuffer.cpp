#include"ByteBuffer.h"

ByteBuffer::ByteBuffer(int Size) {
	this->Buffer = (uint8_t*)malloc(sizeof(uint8_t) * Size);
	this->Pointer = 0;
	this->Size = Size;
}

void ByteBuffer::Write_8(uint8_t Data) {
	if (this->Pointer >= this->Size) {
		this->Size *= 2;

		uint8_t* Temp = (uint8_t*)realloc(this->Buffer, sizeof(uint8_t) * this->Size);

		if (Temp != NULL) {
			this->Buffer = Temp;
		}
	}

	this->Buffer[this->Pointer++] = Data;
}

void ByteBuffer::Write_16(uint16_t Data) {
	this->Write_8((Data & 0xFF00) >> 8);
	this->Write_8((Data & 0x00FF));
}

void ByteBuffer::Write_32(uint32_t Data) {
	this->Write_8((Data & 0xFF000000) >> 24);
	this->Write_8((Data & 0x00FF0000) >> 16);
	this->Write_8((Data & 0x0000FF00) >> 8);
	this->Write_8((Data & 0x000000FF));
}

ByteBuffer::~ByteBuffer() {
	free(this->Buffer);
}
