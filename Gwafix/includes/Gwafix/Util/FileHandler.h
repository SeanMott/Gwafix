//defines a genaric File Handler

#ifndef FileHandler_h
#define FileHandler_h

#ifdef __cplusplus

extern "C" {
#endif

	//reads a text file from a path
	const char* Gwafix_FileHander_ReadTextFile(const char* filePath);
	//reads a binary file from a path
	//const char* Gwafix_FileHander_ReadBinaryFile(const char* filePath);

#ifdef __cplusplus

}
#endif

#endif