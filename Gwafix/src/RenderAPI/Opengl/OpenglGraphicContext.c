//defines the Opengl implmentation of the Graphic Context

#include <gpch.h>
#include <Gwafix\GraphicContext.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

Gwafix_GraphicContext_GraphicContext* Gwafix_GraphicContext_Create(void* window)
{
	if (!window)
	{
		LogError("Graphic Context (Opengl)", "Window is NULL, can not set up context! Check if the window was lost somewhere.");
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef Mac_Build
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LogFatalError("Graphic Context (Opengl)", "Failed to init GLAD!");
		return NULL;
	}

	Gwafix_GraphicContext_GraphicContext* context = malloc(sizeof(Gwafix_GraphicContext_GraphicContext));
	context->window = window;
	context->isZBuffer = false;

	return context;
}

void Gwafix_GraphicContext_Destroy(Gwafix_GraphicContext_GraphicContext* context)
{
	if (!context)
	{
		LogWarning("Graphic Context (Opengl)", "Context is NULL, can not destroy! Check if it was lost somewhere or already deleted.");
		return;
	}

	context->window = NULL;
	free(context);
	context = NULL;
}

void Gwafix_GraphicContext_UseBlending(Gwafix_Context* context, bool state)
{
	if (!context)
	{
		LogError("Graphic Context (Opengl)", "Context is NULL, can not change blend setting! Check if it was lost somewhere.");
		return;
	}

	if (state)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);
}

void Gwafix_GraphicContext_UseZBuffer(Gwafix_Context* context, bool state)
{
	if (!context)
	{
		LogError("Graphic Context (Opengl)", "Context is NULL, can not change Z buffer setting! Check if it was lost somewhere.");
		return;
	}

	(state == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST));
	context->isZBuffer = state;
}

void Gwafix_GraphicContext_UseFaceCulling(Gwafix_Context* context, bool state)
{
	if (!context)
	{
		LogError("Graphic Context (Opengl)", "Context is NULL, can not change face culling setting! Check if it was lost somewhere.");
		return;
	}

	(state == true ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE));
}

void Gwafix_GraphicContext_Viewport(Gwafix_Context* context, int32_t width, int32_t height, int32_t xPos, int32_t yPos)
{
	if (!context)
	{
		LogError("Graphic Context (Opengl)", "Context is NULL, can not resize viewport! Check if it was lost somewhere.");
		return;
	}

	glViewport(xPos, yPos, width, height);
}

void Gwafix_GraphicContext_ClearColor(Gwafix_Context* context, float red, float green, float blue, float alpha)
{
	if (!context)
	{
		LogError("Graphic Context (Opengl)", "Context is NULL, can not set clear color! Check if it was lost somewhere.");
		return;
	}

	glClearColor(red, green, blue, alpha);
}

void Gwafix_GraphicContext_ClearColorVec(Gwafix_Context* context, float* clearColor)
{
	if (!context)
	{
		LogError("Graphic Context (Opengl)", "Context is NULL, can not set clear color! Check if it was lost somewhere.");
		return;
	}

	if (!clearColor)
	{
		LogError("Graphic Context (Opengl)", "clearColor array is NULL, a 4 element array is expected!\nYou can uses ClearColor instead of ClearColorVec.");
		return;
	}

	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void Gwafix_GraphicContext_Clear(Gwafix_Context* context)
{
	if (!context)
	{
		LogError("Graphic Context (Opengl)", "Context is NULL, can not clear screen! Check if it was lost somewhere.");
		return;
	}

	(context->isZBuffer == true ? glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) :
		glClear(GL_COLOR_BUFFER_BIT));
}