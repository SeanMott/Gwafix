#include <gpch.h>
#include <Gwafix\IndexBuffer.h>

#include <glad\glad.h>

//creates a static buffer
Gwafix_IndexBuffer_Buffer* Gwafix_IndexBuffer_CreateStatic(uint32_t* indices, uint32_t count)
{
	if (!indices)
	{
		LogError("Index Buffer indices NULL", "The indices given to a static Index Buffer were NULL, can not make buffer.");
		return NULL;
	}

	Gwafix_IndexBuffer_Buffer* buffer = malloc(sizeof(Gwafix_IndexBuffer_Buffer));
	glGenBuffers(1, &buffer->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	buffer->count = count;
	buffer->indices = indices;
	return buffer;
}

//creates a dynamic buffer
Gwafix_IndexBuffer_Buffer* Gwafix_IndexBuffer_CreateDynamic(uint32_t count)
{
	Gwafix_IndexBuffer_Buffer* buffer = malloc(sizeof(Gwafix_IndexBuffer_Buffer));
	glGenBuffers(1, &buffer->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), NULL, GL_DYNAMIC_DRAW);
	buffer->count = count;
	buffer->indices = NULL;
	return buffer;
}

//destroys a buffer
void Gwafix_IndexBuffer_Destroy(Gwafix_IndexBuffer_Buffer* buffer)
{
	if (!buffer)
	{
		LogWarning("Index Buffer NULL", "The Index Buffer was NULL, can not destroy buffer.");
	}

	glDeleteBuffers(1, &buffer->id);
	buffer->indices = NULL;
	free(buffer);
	buffer = NULL;
}

//binds a buffer
void Gwafix_IndexBuffer_Bind(Gwafix_IndexBuffer_Buffer* buffer)
{
	if (!buffer)
	{
		LogWarning("Index Buffer NULL", "The Index Buffer was NULL, can not bind buffer.");
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
}

//unbinds a buffer
void Gwafix_IndexBuffer_Unbind(Gwafix_IndexBuffer_Buffer* buffer)
{
	//not needed for Opengl so ignore

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//draws a buffer || assumes it's already been bound
void Gwafix_IndexBuffer_Draw(Gwafix_IndexBuffer_Buffer* buffer, Gwafix_DrawType_Type primitiveType, uint32_t startIndex)
{
	if (!buffer)
	{
		LogError("Index Buffer NULL", "The Index Buffer was NULL, can not draw buffer.");
		return;
	}

	//triangles
	if(primitiveType == Gwafix_PrimitiveType_Triangles)
		glDrawElements(GL_TRIANGLES, buffer->count, GL_UNSIGNED_INT, startIndex);
	//points
	else if (primitiveType == Gwafix_PrimitiveType_Points)
		glDrawElements(GL_POINTS, buffer->count, GL_UNSIGNED_INT, startIndex);
}