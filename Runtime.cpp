#include"Runtime.h"

void Push_8(Runtime* VM, uint8_t Data) {
	VM->Stack[++VM->StackPtr] = Data;
}

void Push_16(Runtime* VM, uint16_t Data) {
	Push_8(VM, (Data & 0xFF00) >> 8);
	Push_8(VM, (Data & 0x00FF));
}

void Push_32(Runtime* VM, uint32_t Data) {
	Push_8(VM, (Data & 0xFF000000) >> 24);
	Push_8(VM, (Data & 0x00FF0000) >> 16);
	Push_8(VM, (Data & 0x0000FF00) >> 8);
	Push_8(VM, (Data & 0x000000FF));
}

uint8_t Pop_8(Runtime* VM) {
	return VM->Stack[VM->StackPtr--];
}

uint16_t Pop_16(Runtime* VM) {
	//Need to be in reverse order!
	uint16_t Block2 = Pop_8(VM);
	uint16_t Block1 = Pop_8(VM);

	return (Block1 << 8) | Block2;
}

uint32_t Pop_32(Runtime* VM) {
	uint8_t Block4 = Pop_8(VM);
	uint8_t Block3 = Pop_8(VM);
	uint8_t Block2 = Pop_8(VM);
	uint8_t Block1 = Pop_8(VM);

	return (Block1 << 24) | (Block2 << 16) | (Block3 << 8) | Block4;
}

Runtime::Runtime(uint8_t* ByteCode) {
	this->Running = false;
	this->Code = ByteCode;

	this->Stack[STACK_SIZE - 1] = { 0 };
	this->StackPtr = -1;

	this->ByteIndex = 0;
}

int Runtime::Run(int* ReturnCodePtr) {
	this->Running = true;

	while (this->Running) {
		switch (this->Code[this->ByteIndex++]) {

			//Push 32-bit number to stack
			case OpCode::OP_PUSHCONST: {
				Push_32(this, Read_32(this->Code, this->ByteIndex));
				this->ByteIndex += 4;

				break;
			}

			//Pop last 32-bit numbers off stack, add together, then push back onto stack as 32-bit number
			case OpCode::OP_ADDSTACK: {
				uint32_t A = Pop_32(this);
				uint32_t B = Pop_32(this);

				Push_32(this, A + B);

				break;
			}

			case OpCode::OP_SUBSTACK: {
				uint32_t A = Pop_32(this);
				uint32_t B = Pop_32(this);

				Push_32(this, B - A);

				break;
			}

			case OpCode::OP_MULSTACK: {
				uint32_t A = Pop_32(this);
				uint32_t B = Pop_32(this);

				Push_32(this, A * B);

				break;
			}

			//Print the last 32-bit number on the stack to the standard output
			case OpCode::OP_PRINTSTACK: {
				printf("printreq %d\n", (uint8_t)Pop_32(this));

				break;
			}

			//Stop running the code and print stack to standard output
			case OpCode::OP_HALT: {
				this->Running = false;

				uint8_t ReturnCode = Pop_8(this);

				printf("Return code: %d\n", ReturnCode);

				memset(ReturnCodePtr, ReturnCode, sizeof(uint8_t));

				break;
			}

			default: {
				printf("Unknown bytecode operation: %d\n", this->Code[this->ByteIndex]);

				return -1;

				break;
			}
		}
	}

	return 0;
}
