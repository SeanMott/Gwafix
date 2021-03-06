#include <gpch.h>
#include <Gwafix\VertexBuffer.h>

#include <glad\glad.h>

Gwafix_VertexBuffer_Buffer* Gwafix_VertexBuffer_CreateStatic(float* vertices, uint32_t size)
{
	if (!vertices)
	{
		LogError("Vertex Buffer vertices NULL", "The vertices give to a static Vertex Buffer were NULL, can not make buffer.");
		return NULL;
	}

	//gens vertex and array buffer
	Gwafix_VertexBuffer_Buffer* buffer = malloc(sizeof(Gwafix_VertexBuffer_Buffer));
	glGenVertexArrays(1, &buffer->vertexArray);
	glGenBuffers(1, &buffer->vertexBuffer);
	glBindVertexArray(buffer->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vertexBuffer);

	//sets static data
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	buffer->size = size;
	buffer->vertices = vertices;

	return buffer;
}

Gwafix_VertexBuffer_Buffer* Gwafix_VertexBuffer_CreateDynamic(uint32_t size)
{
	//gens vertex and array buffer
	Gwafix_VertexBuffer_Buffer* buffer = malloc(sizeof(Gwafix_VertexBuffer_Buffer));
	glGenVertexArrays(1, &buffer->vertexArray);
	glGenBuffers(1, &buffer->vertexBuffer);
	glBindVertexArray(buffer->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vertexBuffer);

	//sets static data
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	buffer->size = size;
	buffer->vertices = NULL;

	return buffer;
}

void Gwafix_VertexBuffer_Destroy(Gwafix_VertexBuffer_Buffer* buffer)
{
	if (!buffer)
	{
		LogError("NULL Vertex Buffer", "Buffer is NULL can not destroy!");
		return;
	}

	glDeleteBuffers(1, &buffer->vertexArray);
	glDeleteVertexArrays(1, &buffer->vertexBuffer);
	buffer->vertices = NULL;
	free(buffer);
	buffer = NULL;
}

void Gwafix_VertexBuffer_Layout(Gwafix_VertexBuffer_Buffer* buffer, Gwafix_VertexLayout_Layout* layout)
{
	if (!buffer)
	{
		LogError("NULL Vertex Buffer (Opengl)", "Buffer is NULL can not add layout!");
		return;
	}

	if (!layout)
	{
		LogError("NULL Buffer Layout (Opengl)", "Layout is NULL can not add layout!");
		return;
	}

	if (!layout->normalize || !layout->elements)
	{
		LogError("Buffer Layout (Opengl)", "Layout elements or normalize is NULL, can not add layout!");
		return;
	}

	uint32_t offset = 0, totalCompCount = 0;
	uint32_t currentCompCount = 0, currentCompDatatype = 0;

	//gets total component count
	for (uint32_t i = 0; i < layout->elementCount; i++)
		totalCompCount += Gwafix_VertexLayout_GetComponentCount(layout->elements[i]);

	//sets attrib pointer
	for (uint32_t pointer = 0; pointer < layout->elementCount; pointer++)
	{
		currentCompCount = Gwafix_VertexLayout_GetComponentCount(layout->elements[pointer]);
		currentCompDatatype = Gwafix_VertexLayout_GetNativeAPIType(layout->elements[pointer]);

		glVertexAttribPointer(pointer, currentCompCount, currentCompDatatype,
			layout->normalize[pointer], totalCompCount * sizeof(float), (void*)offset);
		glEnableVertexAttribArray(pointer);

		offset += (currentCompCount * sizeof(currentCompDatatype));
	}
}

void Gwafix_VertexBuffer_Bind(Gwafix_VertexBuffer_Buffer* buffer)
{
	if (!buffer)
	{
		LogError("NULL Vertex Buffer", "Buffer is NULL can not bind!");
		return;
	}

	glBindVertexArray(buffer->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vertexBuffer);
}

void Gwafix_VertexBuffer_Unbind(Gwafix_VertexBuffer_Buffer* buffer)
{
	//don't check since Opengl does not require it

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Gwafix_VertexBuffer_Draw(Gwafix_VertexBuffer_Buffer* buffer, Gwafix_DrawType_Type primitiveType, uint32_t startIndex)
{
	if (!buffer)
	{
		LogError("NULL Vertex Buffer", "Buffer is NULL can not draw!");
		return;
	}

	if(primitiveType == Gwafix_PrimitiveType_Triangles)
		glDrawArrays(GL_TRIANGLES, startIndex, buffer->size);
	else if(primitiveType == Gwafix_PrimitiveType_Points)
		glDrawArrays(GL_POINTS, startIndex, buffer->size);
}