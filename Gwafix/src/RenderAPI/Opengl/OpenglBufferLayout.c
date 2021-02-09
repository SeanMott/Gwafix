#include <gpch.h>
#include <Gwafix\BufferLayout.h>

#include <glad\glad.h>

uint32_t Gwafix_VertexLayout_GetNativeAPIType(Gwafix_VertexLayout_Element type)
{
	switch (type)
	{
	case Gwafix_LayoutType_Float1:
		return GL_FLOAT;
	case Gwafix_LayoutType_Float2:
		return GL_FLOAT;
	case Gwafix_LayoutType_Float3:
		return GL_FLOAT;
	case Gwafix_LayoutType_Float4:
		return GL_FLOAT;
	case Gwafix_LayoutType_Mat3:
		return GL_FLOAT;
	case Gwafix_LayoutType_Mat4:
		return GL_FLOAT;
	case Gwafix_LayoutType_Int1:
		return GL_INT;
	case Gwafix_LayoutType_Int2:
		return GL_INT;
	case Gwafix_LayoutType_Int3:
		return GL_INT;
	case Gwafix_LayoutType_Int4:
		return GL_INT;
	case Gwafix_LayoutType_Bool:
		return GL_BOOL;
	}

	LogError("Layout Type", "Unknown shader data type.\n");
	return 0;
}