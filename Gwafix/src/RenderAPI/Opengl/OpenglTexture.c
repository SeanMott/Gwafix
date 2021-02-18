//Opengl implementation of a Texture

#include <gpch.h>
#include <Gwafix\Texture.h>

#include <Gwafix\Util\FileHandler.h>

#include <string.h>
#include <glad\glad.h>
#include <stb_image.h>

#define EXTENTION_LENGTH_CAP 20

Gwafix_Texture_Texture* Gwafix_Texture_Create2D(const char* path, bool makeBackgroundTrans)
{
	if (!path)
	{
		LogError("Texture Path NULL", "Can not create a path from a NULL path.");
		return NULL;
	}

	//get extention
	uint32_t length = strlen(path);
	char* flippedExtention = calloc(EXTENTION_LENGTH_CAP, sizeof(char));
	uint32_t exPos = 0;
	for (int32_t i = length - 1; i > -1; i--)
	{
		if (exPos == EXTENTION_LENGTH_CAP)
		{
			LogData("Gwafix Error: Extention Length Cap || What ever extention your trying to load as a Texture. It's extention is greater then %u, check Github for updates and maybe help expand the lib to support this extension. Thanks :).\n Path: \"%s\"\n", EXTENTION_LENGTH_CAP, path);
			return NULL;
		}

		//found extention
		if (path[i] == '.')
			break;

		flippedExtention[exPos] = path[i];
		exPos++;
	}

	//flip extention
	length = strlen(flippedExtention);
	char* extention = calloc(length + 1, sizeof(char));
	exPos = 0;
	for (int32_t i = length - 1; i > -1; i--)
	{
		extention[exPos] = flippedExtention[i];
		exPos++;
	}

	//load based on extension
	Gwafix_Texture_Texture* texture = malloc(sizeof(Gwafix_Texture_Texture));
	texture->type = Gwafix_TextureType_2D;

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//flips image
	stbi_set_flip_vertically_on_load(1);

	//load image, create texture and generate mipmaps

	unsigned char* data = stbi_load(path, &texture->width, &texture->height, &texture->numChannels, 0);
	if (data)
	{
		//JPEG
		if (Gwafix_FileHandler_StringMatch(extention, "jpg"))
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}

		//PNG
		else if (Gwafix_FileHandler_StringMatch(extention, "png"))
		{
			glTexImage2D(GL_TEXTURE_2D, 0, (makeBackgroundTrans == true ? GL_RGBA : GL_RGB),
				texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		//if not supported
		else
		{
			LogData("Gwafix Error: Unsupported Texture formate || The Texture formate is not supported. Check Github for updates or help add support to Gwafix. Thanks :).\nFormate: \"%s\" Path: \"%s\"", extention, path);
			free(texture);
			free(extention);
			free(flippedExtention);
			stbi_image_free(data);
			return NULL;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LogData("Gwafix Error: Invalid Texture Path || Failed to load a Texture from the give path, check that it is there.\nPath: \"%s\"\n", path);
		free(texture);
		free(extention);
		free(flippedExtention);
		stbi_image_free(data);
		return NULL;
	}

	free(extention);
	free(flippedExtention);
	stbi_image_free(data);
	return texture;
}

void Gwafix_Texture_Destroy(Gwafix_Texture_Texture* texture)
{
	if (!texture)
	{
		LogError("NULL Texture", "Texture is Null, can not destroy");
		return;
	}

	glDeleteTextures(1, &texture->id);
	free(texture);
	texture = NULL;
}

void Gwafix_Texture_Bind(Gwafix_Texture_Texture* texture, uint32_t slot)
{
	if (!texture)
	{
		LogError("NULL Texture", "Texture is NULL can not bind.");
		return;
	}

	//sets slot
	glActiveTexture(GL_TEXTURE0 + slot);

	if(texture->type == Gwafix_TextureType_2D)
		glBindTexture(GL_TEXTURE_2D, texture->id);

	//other types
}

void Gwafix_Texture_Unbind(Gwafix_Texture_Texture* texture, uint32_t slot)
{
	if (!texture)
	{
		LogError("NULL Texture", "Texture is NULL can not unbind.");
		return;
	}

	//sets slot
	glActiveTexture(GL_TEXTURE0 + slot);

	if (texture->type == Gwafix_TextureType_2D)
		glBindTexture(GL_TEXTURE_2D, texture->id);

	//other types
}