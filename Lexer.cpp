#include"Lexer.h"

int GetNumber(const char* Buffer) {
	return atoi(&Buffer[1]);
}

int GetInstruction(char* Buffer) {
	if (strcmp(Buffer, "push") == 0) {
		return (int)Instruction::INSTRUCTION_PUSH;
	}

	if (strcmp(Buffer, "add") == 0) {
		return (int)Instruction::INSTRUCTION_ADD;
	}

	if (strcmp(Buffer, "sub") == 0) {
		return (int)Instruction::INSTRUCTION_SUB;
	}

	if (strcmp(Buffer, "mul") == 0) {
		return (int)Instruction::INSTRUCTION_MUL;
	}

	if (strcmp(Buffer, "put") == 0) {
		return (int)Instruction::INSTRUCTION_PRINT;
	}

	if (strcmp(Buffer, "hlt") == 0) {
		return (int)Instruction::INSTRUCTION_HALT;
	}

	printf("Invalid instruction: %s\n", Buffer);

	return -1;
}

int Lexer::Tokenize(std::string Code, TokenList* Tokens) {
	char Lex[256]{};
	int TokenIndex = 0;
	int Index = 0;

	int Line = 1;

	while (true) {
		Token* NewToken;

		char Current = Code[Index];

		//Put next characters in token until we find whitespace
		while (Current != ' ' && Current != '\n' && Current != '\0' && Current != '\r' && Current != '\b' && Current != '\t') {
			Lex[TokenIndex++] = Code[Index++];
			Current = Code[Index];
		}

		Lex[TokenIndex] = '\0';

		if (strlen(Lex) == 0) {
			TokenIndex = 0;
			Index++;

			continue;
		}

		if (Lex[0] == '#') {
			int Number = GetNumber(Lex);

			NewToken = new Token(LexerTokenType::TOKENTYPE_NUMBER, Number, Line);

			Tokens->AddToken(NewToken);
		}
		else {
			int Inst = GetInstruction(Lex);

			if (Inst == -1) {
				printf("at line %d, character %d\n", Line, Index);

				return -1;
			}

			if (Inst == -2) {
				continue;
			}

			NewToken = new Token(LexerTokenType::TOKENTYPE_INSTRUCTION, Inst, Line);

			Tokens->AddToken(NewToken);
		}

		if (Code[Index] == '\n') {
			Line++;
		}

		if (Code[Index] == '\0') {
			break;
		}

		TokenIndex = 0;
		Index++;
	}

	return 0;
}
