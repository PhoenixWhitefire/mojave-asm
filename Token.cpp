#include"Token.h"

Token::Token(LexerTokenType TType, int TData, int TLine){
	this->Type = TType;
	this->Data = TData;
	this->Line = TLine;
}

TokenList::TokenList(int Size) {
	this->Data = (Token*)malloc(sizeof(Token) * Size);
	this->Pointer = 0;
	this->Size = Size;
}

void TokenList::AddToken(Token* Tok) {
	if (this->Pointer >= this->Size) {
		this->Size *= 2;

		Token* Temp = (Token*)realloc(this->Data, sizeof(Token) * this->Size);

		if (Temp != NULL) {
			this->Data = Temp;
		}
	}

	this->Data[this->Pointer++] = *Tok;
}

Token* TokenList::GetToken(int Index) {
	return &this->Data[Index];
}
