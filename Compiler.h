#pragma once

#include<iostream>

#include"ByteBuffer.h"
#include"OpCode.h"
#include"Token.h"

class Compiler {
	public:
		Compiler();

		int CompileToBytecode(TokenList* Tokens);

		ByteBuffer* ByteCode;

		TokenList* LexedTokens;
};
