//defines a genaric Texture interface

#ifndef Texture_h
#define Texture_h

#ifdef __cplusplus

extern "C" {
#endif

#include <stdint.h>

	//defines a Texture type
	typedef enum
	{
		Gwafix_TextureType_2D = 0x01,
		//other types

	} Gwafix_Texture_TextureType;

	//defines a Texture
	typedef struct
	{
		//identity data
		uint32_t id;
		uint8_t type : 1; //stores the type of texture 2D or other types
		uint8_t extention : 2; //stores the type of texture JPEG, PNG, ect

		//the dimentions and channels of the texture
		uint32_t width, height, numChannels;

	} Gwafix_Texture_Texture;

	//creates a Texture 2D
	Gwafix_Texture_Texture* Gwafix_Texture_Create2D(const char* path, bool makeBackgroundTrans);
	//add create methods for other Texture types

	//destroys a Texture
	void Gwafix_Texture_Destroy(Gwafix_Texture_Texture* texture);

	//binds a Texture
	void Gwafix_Texture_Bind(Gwafix_Texture_Texture* texture, uint32_t slot);
	//unbinds a Texture
	void Gwafix_Texture_Unbind(Gwafix_Texture_Texture* texture);

#ifdef __cplusplus

}
#endif

#endif