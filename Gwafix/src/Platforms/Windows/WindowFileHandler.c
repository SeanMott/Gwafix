//Windows implementation of the file handler

#include <gpch.h>
#include <Gwafix\Util\FileHandler.h>

#include <string.h>

const char* Gwafix_FileHander_ReadTextFile(const char* filePath)
{
	FILE* file;
	char* text = 0;
	long length;

	file = fopen(filePath, "rb");
	if (!file)
	{
		LogData("Error: File Handler || Failed to open text file at: %s\n", filePath);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	text = calloc(length, length);
	if (text)
		fread(text, 1, length, file);

	fclose(file);

	return text;
}

bool Gwafix_FileHandler_StringMatch(const char* string1, const char* string2)
{
	return (strcmp(string1, string2) == 0 ? true : false);
}