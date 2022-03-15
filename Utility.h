#pragma once

#include<iostream>
#include<fstream>

#include"ByteBuffer.h"

//File functions
std::string ReadASCIIFile(const char* FilePath);
uint8_t* ReadBinaryFile(const char* FilePath);
int WriteBinaryFile(const char* FilePath, ByteBuffer* ByteCode);

//Bytecode functions
uint16_t Read_16(uint8_t* Buffer, uint32_t Index);
uint32_t Read_32(uint8_t* Buffer, uint32_t Index);
