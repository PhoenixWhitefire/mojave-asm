#pragma once

#define STACK_SIZE 1024

#include<stdint.h>

#include"Utility.h"
#include"OpCode.h"

class Runtime {
	public:
		Runtime(uint8_t* ByteCode);

		int Run(int* ReturnCodePtr);

		uint8_t* Code;

		uint8_t Stack[STACK_SIZE];
		uint32_t StackPtr;

		uint32_t ByteIndex;

		bool Running;
};
