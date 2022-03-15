#include"Utility.h"

std::string ReadASCIIFile(const char* FilePath) {
	std::ifstream InFile(FilePath, std::ios::binary);

	if (InFile) {
		std::string Contents;

		InFile.seekg(0, std::ios::end);
		Contents.resize(InFile.tellg());
		InFile.seekg(0, std::ios::beg);
		InFile.read(&Contents[0], Contents.size());
		InFile.close();

		return(Contents);
	}

	printf("COULD NOT LOAD FILE: %s\n", FilePath);

	return "noparse";
}

int WriteBinaryFile(const char* FilePath, ByteBuffer* ByteCode) {
	std::FILE* File;

	fopen_s(&File, FilePath, "wb");

	if (!File) {
		printf("Could not write to %s\n", FilePath);

		return -1;
	}

	printf("Writing to %s\n", FilePath);

	std::fwrite(ByteCode->Buffer, 1, ByteCode->Pointer, File);

	std::fclose(File);

	return 0;
}

uint8_t* ReadBinaryFile(const char* FilePath) {
	std::FILE* File;

	fopen_s(&File, FilePath, "rb");

	if (!File) {
		printf("Could not read file %s\n", FilePath);

		return NULL;
	}

	std::fseek(File, 0, SEEK_END);
	int Size = std::ftell(File);
	std::fseek(File, 0, SEEK_SET);

	uint8_t* Buffer = (uint8_t*)malloc(sizeof(uint8_t) * Size);

	if (Buffer == 0) {
		printf("Buffer is 0\n");

		return NULL;
	}

	std::fread(Buffer, 1, Size, File);

	return Buffer;
}

uint16_t Read_16(uint8_t* Buffer, uint32_t Index) {
	return (Buffer[Index] << 16) |
		(Buffer[Index + 1]);
}

uint32_t Read_32(uint8_t* Buffer, uint32_t Index) {
	return (Buffer[Index] << 24) |
		(Buffer[Index + 1] << 16) |
		(Buffer[Index + 2] << 8) |
		(Buffer[Index + 3]);
}
