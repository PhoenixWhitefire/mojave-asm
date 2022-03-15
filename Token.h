#pragma once

#include<stdlib.h>

enum class LexerTokenType {
	TOKENTYPE_INSTRUCTION,
	TOKENTYPE_CALLFUNC,
	TOKENTYPE_FUNCDECL,
	TOKENTYPE_VARDECL,
	TOKENTYPE_NUMBER
};

enum class Instruction {
	INSTRUCTION_PUSH,

	INSTRUCTION_ADD,
	INSTRUCTION_SUB,
	INSTRUCTION_MUL,

	INSTRUCTION_PRINT,
	INSTRUCTION_HALT
};

class Token {
	public:
		Token(LexerTokenType TType, int TData, int TLine);

		LexerTokenType Type;
		int Data;
		int Line;
};

class TokenList {
	public:
		TokenList(int Size);

		void AddToken(Token* Tok);
		Token* GetToken(int Index);

		Token* Data;
		int Pointer;
		int Size;
};
