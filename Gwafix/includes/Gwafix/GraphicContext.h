//genaric interface for Graphic Context

#ifndef GraphicContext_h
#define GraphicContext_h

#ifdef __cplusplus

extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

	//defines the Graphic Context
	typedef struct
	{
		void* window; //stores a refrence to the window
		bool isZBuffer;

	}Gwafix_GraphicContext_GraphicContext, Gwafix_Context;

	//creates a Graphic Context
	Gwafix_GraphicContext_GraphicContext* Gwafix_GraphicContext_Create(void* window);
	//destroys a Graphic Context
	void Gwafix_GraphicContext_Destroy(Gwafix_GraphicContext_GraphicContext* context);

	//sets if blending should be used
	void Gwafix_GraphicContext_UseBlending(Gwafix_Context* context, bool state);
	//sets if the Z Buffer (Depth buffer) should be used
	void Gwafix_GraphicContext_UseZBuffer(Gwafix_Context* context, bool state);
	//sets if face culling should be used
	void Gwafix_GraphicContext_UseFaceCulling(Gwafix_Context* context, bool state);

	//sets the view port
	void Gwafix_GraphicContext_Viewport(Gwafix_Context* context, int32_t width, int32_t height, int32_t xPos, int32_t yPos);
	//sets the clear color
	void Gwafix_GraphicContext_ClearColor(Gwafix_Context* context, float red, float green, float blue, float alpha);
	//sets the clear color || expects a 4 element array
	void Gwafix_GraphicContext_ClearColorVec(Gwafix_Context* context, float* clearColor);
	//clears the screen
	void Gwafix_GraphicContext_Clear(Gwafix_Context* context);

#ifdef __cplusplus
}
#endif

#endif