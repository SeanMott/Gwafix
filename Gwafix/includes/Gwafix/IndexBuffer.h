//defines a genaric Index Buffer

#ifndef IndexBuffer_h
#define IndexBuffer_h

#include <stdint.h>
#include <Gwafix\DrawTypePrimitives.h>

#ifdef __cplusplus
extern "C" {
#endif

//defines the Index Buffer
typedef struct
{
	uint32_t id;
	uint32_t* indices;
	uint32_t count;

}Gwafix_IndexBuffer_Buffer;

//creates a static buffer
Gwafix_IndexBuffer_Buffer* Gwafix_IndexBuffer_CreateStatic(uint32_t* indices, uint32_t count);
//creates a dynamic buffer
Gwafix_IndexBuffer_Buffer* Gwafix_IndexBuffer_CreateDynamic(uint32_t count);
//destroys a buffer
void Gwafix_IndexBuffer_Destroy(Gwafix_IndexBuffer_Buffer* buffer);

//binds a buffer
void Gwafix_IndexBuffer_Bind(Gwafix_IndexBuffer_Buffer* buffer);
//unbinds a buffer
void Gwafix_IndexBuffer_Unbind(Gwafix_IndexBuffer_Buffer* buffer);

//draws a buffer || assumes it's already been bound
void Gwafix_IndexBuffer_Draw(Gwafix_IndexBuffer_Buffer* buffer, Gwafix_DrawType_Type primitiveType, uint32_t startIndex);

#ifdef __cplusplus

}
#endif

#endif