#include"Compiler.h"

Compiler::Compiler() {
	this->ByteCode = NULL;
	this->LexedTokens = NULL;
}

int Compiler::CompileToBytecode(TokenList* Tokens) {
	this->ByteCode = new ByteBuffer(1);

	this->LexedTokens = Tokens;

	for (int Index = 0; Index < this->LexedTokens->Pointer; Index++) {
		Token Tk = this->LexedTokens->Data[Index];
		Token* NextTk = NULL;

		if (this->LexedTokens->Pointer > Index - 1) {
			NextTk = &this->LexedTokens->Data[Index + 1];
		}

		if (Tk.Type == LexerTokenType::TOKENTYPE_INSTRUCTION) {
			switch (Tk.Data) {
				case (int)Instruction::INSTRUCTION_PUSH: {
					if (NextTk != NULL && NextTk->Type == LexerTokenType::TOKENTYPE_NUMBER) {
						this->ByteCode->Write_8((uint8_t)OpCode::OP_PUSHCONST);
						this->ByteCode->Write_32((uint32_t)NextTk->Data);

						Index++;
					}
					else {
						printf("PUSH requires number argument!\n");

						return -1;
					}

					break;
				}

				case (int)Instruction::INSTRUCTION_ADD: {
					this->ByteCode->Write_8((uint8_t)OpCode::OP_ADDSTACK);

					break;
				}

				case (int)Instruction::INSTRUCTION_SUB: {
					this->ByteCode->Write_8((uint8_t)OpCode::OP_SUBSTACK);

					break;
				}

				case (int)Instruction::INSTRUCTION_MUL: {
					this->ByteCode->Write_8((uint8_t)OpCode::OP_MULSTACK);

					break;
				}

				case (int)Instruction::INSTRUCTION_PRINT: {
					this->ByteCode->Write_8((uint8_t)OpCode::OP_PRINTSTACK);

					break;
				}

				case (int)Instruction::INSTRUCTION_HALT: {
					this->ByteCode->Write_8((uint8_t)OpCode::OP_HALT);

					break;
				}

				default: {
					printf("Unknown instruction %d\n", Tk.Data);

					return -1;
				}
			}
		}
	}

	return 0;
}
