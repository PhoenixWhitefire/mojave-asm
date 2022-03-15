#pragma once

#include<iostream>
#include<string.h>

#include"Token.h"

class Lexer {
	public:
		static int Tokenize(std::string Code, TokenList* Tokens);
};
