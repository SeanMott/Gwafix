//allows a vertex buffer layout to be defined

#ifndef BufferLayout_h
#define BufferLayout_h

#ifdef __cplusplus

extern "C" {
#endif

#include <stdint.h>
#include <Logger.h>

	//defines a Layout Element
	typedef enum
	{
		Gwafix_LayoutType_None,

		Gwafix_LayoutType_Bool,

		Gwafix_LayoutType_Int1,
		Gwafix_LayoutType_Int2,
		Gwafix_LayoutType_Int3,
		Gwafix_LayoutType_Int4,

		Gwafix_LayoutType_Float1,
		Gwafix_LayoutType_Float2,
		Gwafix_LayoutType_Float3,
		Gwafix_LayoutType_Float4,

		//there if used
		Gwafix_LayoutType_Vec2,
		Gwafix_LayoutType_Vec3,
		Gwafix_LayoutType_Vec4,

		Gwafix_LayoutType_Mat2,
		Gwafix_LayoutType_Mat3,
		Gwafix_LayoutType_Mat4,

	} Gwafix_VertexLayout_Element;

	//defines a Layout
	typedef struct
	{
		Gwafix_VertexLayout_Element* elements;
		bool* normalize;
		uint32_t elementCount;

	} Gwafix_VertexLayout_Layout;

	//gets the size of a data type
	inline uint32_t Gwafix_VertexLayout_GetDataTypeSize(Gwafix_VertexLayout_Element type)
	{
		switch (type)
		{
		case Gwafix_LayoutType_None:
			return 0;
		case Gwafix_LayoutType_Float1:
			return 4;
		case Gwafix_LayoutType_Float2:
			return 8;
		case Gwafix_LayoutType_Float3:
			return 12;
		case Gwafix_LayoutType_Float4:
			return 16;
		case Gwafix_LayoutType_Mat3:
			return 36;
		case Gwafix_LayoutType_Mat4:
			return 64;
		case Gwafix_LayoutType_Int1:
			return 4;
		case Gwafix_LayoutType_Int2:
			return 8;
		case Gwafix_LayoutType_Int3:
			return 12;
		case Gwafix_LayoutType_Int4:
			return 16;
		case Gwafix_LayoutType_Bool:
			return 1;
		}

		LogError("Layout Type", "Unknown shader data type.\n");
		return 0;
	}

	//gets the count of a data type || float3 = 3
	inline uint32_t Gwafix_VertexLayout_GetComponentCount(Gwafix_VertexLayout_Element type)
	{
		switch (type)
		{
		case Gwafix_LayoutType_None:
			return 0;
		case Gwafix_LayoutType_Float1:
			return 1;
		case Gwafix_LayoutType_Float2:
			return 2;
		case Gwafix_LayoutType_Float3:
			return 3;
		case Gwafix_LayoutType_Float4:
			return 4;
		case Gwafix_LayoutType_Mat3:
			return 9;
		case Gwafix_LayoutType_Mat4:
			return 16;
		case Gwafix_LayoutType_Int1:
			return 1;
		case Gwafix_LayoutType_Int2:
			return 2;
		case Gwafix_LayoutType_Int3:
			return 3;
		case Gwafix_LayoutType_Int4:
			return 4;
		case Gwafix_LayoutType_Bool:
			return 1;
		default:
			LogError("Layout Type", "Unknown shader data type.\n");
			return 0;
		}
	}

	//converts the element to the native Render API data type
	uint32_t Gwafix_VertexLayout_GetNativeAPIType(Gwafix_VertexLayout_Element type);

#ifdef __cplusplus
}
#endif

#endif