/*
	A simple starting point for my programming language Mojave, called Mojave-ASM because of it's ASM-like syntax.
	This was just made to get the basic stuff down on how to create a programming language.

	How to use:
	CODE:
		There is current only 1 datatype, numbers. To declare a number, put a '#' symbol and then the number after it.
		Ex; "#3"
		Numbers are restricted to integers (no decimals)

		There are only four instructions right now:
			-push N
			-add
			-put
			-hlt

		put:
			Prints whatever is at the top of the stack to the standard output

		push N:
			Pushes the number to the top of the stack
			Ex;
				push #2
				put
			(prints 2 in the output)

		add:
			Adds two numbers at the top of the stack, removes those two, and puts the calculated number to the top of the
			stack
			Ex;
				push #2
				push #4
				add
				put
			(prints 6 in the output)

		hlt:
			Ends the program and prints the number at the top of the stack. Not having this results in the code never stopping, even if
			nothing is being executed.


	To use Mojave-ASM:
		-Create a text file
		-Enter some Mojave-ASM language code into it
		-Open Mojave-ASM root folder
		-Navigate to x64>Debug
		-Open a shell window in the folder (on Windows: type 'cmd' in the address bar in File Explorer while in the folder,
		and press enter)
		-Enter the following:
			Mojave-ASM -bytecode -file <the path to your script> -rb
		-Mojave-ASM should execute the code
*/

#include<Windows.h>
#include<string>

#include"Compiler.h"
#include"Utility.h"
#include"Runtime.h"
#include"Lexer.h"

//Print result of lexer tokenization
void PrintTokens(TokenList* Tokens) {
	for (int Index = 0; Index < Tokens->Pointer; Index++) {
		Token* Tk = Tokens->GetToken(Index);

		if (Tk->Type == LexerTokenType::TOKENTYPE_NUMBER) {
			printf("NUMBER=Value: %d Line: %d\n", Tk->Data, Tk->Line);
		}

		if (Tk->Type == LexerTokenType::TOKENTYPE_INSTRUCTION) {
			if (Tk->Data == (int)Instruction::INSTRUCTION_ADD) {
				printf("INST=Type: ADD Line: %d\n", Tk->Line);
			}
			if (Tk->Data == (int)Instruction::INSTRUCTION_PUSH) {
				printf("INST=Type: PUSH Line: %d\n", Tk->Line);
			}
			if (Tk->Data == (int)Instruction::INSTRUCTION_HALT) {
				printf("INST=Type: HALT Line: %d\n", Tk->Line);
			}
			if (Tk->Data == (int)Instruction::INSTRUCTION_PRINT) {
				printf("INST=Type: PRINT Line: %d\n", Tk->Line);
			}
		}
	}
}

//Check if a command-line argument was specified
int ArgSpecified(char** Args, int NumArgs, std::string Arg) {
	for (int Index = 0; Index < NumArgs; Index++) {
		if (Args[Index] == Arg) {
			return Index;
		}
	}

	return -1;
}

int RunBytecode(const char* SpecifiedFile, int FileArgNum) {
	if (FileArgNum == -1) {
		printf("'-file' argument not specified for bytecode run operation\n");

		return -1;
	}

	//ByteBuffer* ByteCode = new ByteBuffer(1);

	uint8_t* Bytecode = ReadBinaryFile(SpecifiedFile);

	if (Bytecode == NULL) {
		printf("Could not get bytecode data\n");

		return -1;
	}

	int ReturnCode;

	Runtime* VM = new Runtime(Bytecode);

	int RuntimeStatus = VM->Run(&ReturnCode);

	if (RuntimeStatus == -1) {
		printf("Runtime error\n");

		return -1;
	}

	return 0;
}

//Created: 12/03/2022
//Last updated: 15/03/2022

int main(int NumArgs, char** Args) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	printf("The Mj-ASM programming language (v1.0 15/03/2022)\n");

	std::string Code;

	int FileArgNum = ArgSpecified(Args, NumArgs, "-file");

	const char* SpecifiedFile = Args[0];

	int BytecodeArgNum = ArgSpecified(Args, NumArgs, "-bytecode");
	int RunArgNum = ArgSpecified(Args, NumArgs, "-btexec");

	int RunBytecodeAfterCompile = ArgSpecified(Args, NumArgs, "-rb");
	
	if (FileArgNum > 0) {
		if (SpecifiedFile == Args[0]) {
			SpecifiedFile = Args[FileArgNum + 1];

			if (SpecifiedFile == NULL) {
				printf("'-file' argument specified, but no file given\n");

				return EXIT_FAILURE;
			}
		}

		SetConsoleTextAttribute(hConsole, 92);

		printf("Input file: %s\n", SpecifiedFile);

		SetConsoleTextAttribute(hConsole, 15);

		Code = ReadASCIIFile(SpecifiedFile);

		if (Code == "noparse") {
			return EXIT_FAILURE;
		}
	}

	if (BytecodeArgNum > 0) {
		//Compile code to bytecode

		if (FileArgNum < 0) {
			printf("Mojave>");

			std::getline(std::cin, Code);
		}

		TokenList* Tokens = new TokenList(256);

		printf("Tokenizing...\n");

		int LexerStatus = Lexer::Tokenize(Code, Tokens);

		if (LexerStatus == -1) {
			printf("Could not parse\n");

			return EXIT_FAILURE;
		}

		Compiler ByteCodeCompiler;

		printf("Compiling...\n");

		int CompilerStatus = ByteCodeCompiler.CompileToBytecode(Tokens);

		if (CompilerStatus == -1) {
			printf("Could not compile\n");

			return EXIT_FAILURE;
		}

		printf("Creating bytecode file...\n");

		WriteBinaryFile("out.mjasmbt", ByteCodeCompiler.ByteCode);

		SetConsoleTextAttribute(hConsole, 32);

		printf("Done!\n");

		SetConsoleTextAttribute(hConsole, 15);

		if (RunBytecodeAfterCompile > 0) {
			printf("\nAuto-running bytecode (-rb argument specified)\n\n");

			RunBytecode("out.mjasmbt", 1);
		}

		return EXIT_SUCCESS;
	}
	else if (RunArgNum > 0) {
		//Execute bytecode

		int RunStatus = RunBytecode(SpecifiedFile, FileArgNum);

		if (RunStatus == -1) {
			printf("Could not execute bytecode\n");
		}
		else {
			return EXIT_SUCCESS;
		}
	}

	printf("Specify either -bytecode or -rb as a command-line argument for Mojave-ASM\n");

	return EXIT_FAILURE;
}
