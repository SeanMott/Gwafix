//defines a Vertex Buffer

#ifndef VertexBuffer_h
#define VertexBuffer_h

#ifdef __cplusplus

extern "C" {
#endif

#include <Gwafix\DrawTypePrimitives.h>
#include <Gwafix\BufferLayout.h>
#include <stdint.h>

	//defines a Vertex Buffer
	typedef struct
	{
		//ids || vertex array is for Opengl
		uint32_t vertexBuffer, vertexArray;

		//vertex data
		float* vertices;
		uint32_t size;

		//layout
		//Gwafix_VertexLayout_Layout* layout;

	} Gwafix_VertexBuffer_Buffer;

	//creates a static buffer
	Gwafix_VertexBuffer_Buffer* Gwafix_VertexBuffer_CreateStatic(float* vertices, uint32_t size);
	//creates a dynamic buffer
	Gwafix_VertexBuffer_Buffer* Gwafix_VertexBuffer_CreateDynamic(uint32_t size);
	//destroys a buffer
	void Gwafix_VertexBuffer_Destroy(Gwafix_VertexBuffer_Buffer* buffer);

	//sets the layout || assumes it's already been bound
	void Gwafix_VertexBuffer_Layout(Gwafix_VertexBuffer_Buffer* buffer, Gwafix_VertexLayout_Layout* layout);

	//binds a buffer
	void Gwafix_VertexBuffer_Bind(Gwafix_VertexBuffer_Buffer* buffer);
	//unbinds a buffer
	void Gwafix_VertexBuffer_Unbind(Gwafix_VertexBuffer_Buffer* buffer);

	//draws a buffer || assumes it's already been bound
	void Gwafix_VertexBuffer_Draw(Gwafix_VertexBuffer_Buffer* buffer, Gwafix_DrawType_Type primitiveType, uint32_t startIndex);

#ifdef __cplusplus

}
#endif

#endif