//the Window Implementation of Display

#include <gpch.h>
#include <Gwafix\Display.h>

#include <GLFW\glfw3.h>

//temp
#include <glad\glad.h>

//----GLFW Callbacks----//
//logs errors
void GLFWErrorCallBack(int error, const char* description);
//allows the window to resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//allows the exit window button to be pressed || closes the window
void window_close_callback(GLFWwindow* window);
//allows mouse move events to be triggered
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
//allows mouse scroll events
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//allows keyboard pressed events to be triggered
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//allows mouse pressed events to be triggered
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//char callback allows typing
void character_callback(GLFWwindow* window, unsigned int keycode);
//if the window gains or loses focues
void window_focus_callback(GLFWwindow* window, int focused);

static bool GLFWInit = false;

Gwafix_Display_Display* Gwafix_Display_Create(Gwafix_Display_CreateInfo* info)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't create Display, Create Info is NULL!");
		return NULL;
	}
	
	Gwafix_Display_Display* display = malloc(sizeof(Gwafix_Display_Display));

	//inits GLFW
	if (!GLFWInit)
	{
		if (!glfwInit())
		{
			LogError("Display", "GLFW failed to init!");
			Gwafix_Display_Destroy(display);
			return NULL;
		}

		GLFWInit = true;
	}

	//allows resizing
	glfwWindowHint(GLFW_RESIZABLE, info->enableResizeing);

	//make window || add full screen and share context support
	display->window = glfwCreateWindow(info->width, info->height, info->name, NULL, NULL);
	if (!display->window)
	{
		LogError("Display", "Window could not be initalized!");
		Gwafix_Display_Destroy(display);
		return NULL;
	}
	glfwMakeContextCurrent(display->window); //Make the window's context current

	//set method call backs
	glfwSetErrorCallback(GLFWErrorCallBack);
	glfwSetFramebufferSizeCallback(display->window, framebuffer_size_callback); //resize
	glfwSetWindowCloseCallback(display->window, window_close_callback); //closes the window when the exit button is pressed
	glfwSetKeyCallback(display->window, key_callback);//key input
	glfwSetMouseButtonCallback(display->window, mouse_button_callback); //mouse input
	glfwSetCursorPosCallback(display->window, cursor_position_callback);//mouse move
	glfwSetScrollCallback(display->window, scroll_callback);//mouse scroll
	glfwSetCharCallback(display->window, character_callback); //type input
	glfwSetWindowFocusCallback(display->window, window_focus_callback); //sets focus

	//inits the Graphic Context
	display->context = Gwafix_GraphicContext_Create(display->window);
	if (!display->context)
	{
		LogError("Display", "Failed to set up Graphic Context");
		Gwafix_Display_Destroy(display);
		return NULL;
	}

	//sets clear color
	Gwafix_GraphicContext_ClearColorVec(display->context, info->clearColor);

	//sets window size
	Gwafix_Display_Resize(display, info->width, info->height, 0, 0);

	//render setings
	Gwafix_GraphicContext_UseBlending(display->context, info->enableBlending);
	Gwafix_GraphicContext_UseFaceCulling(display->context, info->enableFaceCulling);
	Gwafix_GraphicContext_UseZBuffer(display->context, info->enableZBuffer);

	display->isRunning = true;

	glfwSetWindowUserPointer(display->window, display); //stores the display to it's window

	//sets the desktop callback events
	display->onWindowResizeCallback = info->onWindowResizeCallback;
	display->windowResizeEventCount = info->windowResizeEventCount;
	display->onWindowCloseCallback = info->onWindowCloseCallback;
	display->windowCloseEventCount = info->windowCloseEventCount;
	display->onMousePositionCallback = info->onMousePositionCallback;
	display->mousePositionEventCount = info->mousePositionEventCount;
	display->onMouseScrollCallback = info->onMouseScrollCallback;
	display->MouseScrollEventCount = info->MouseScrollEventCount;
	display->onKeyCallback = info->onKeyCallback;
	display->keyEventCount = info->keyEventCount;
	display->onMouseButtonCallback = info->onMouseButtonCallback;
	display->mouseButtonEventCount = info->mouseButtonEventCount;
	display->onKeyTypeCallback = info->onKeyTypeCallback;
	display->keyTypeEventCount = info->keyTypeEventCount;
	display->onFocusCallback = info->onFocusCallback;
	display->focusEventCount = info->focusEventCount;

	//zeros out the phone callback events

	return display;
}

void Gwafix_Display_Destroy(Gwafix_Display_Display* display)
{
	if (!display)
	{
		LogError("Display NULL", "Display is NULL, can not be destroyed!");
		return;
	}

	Gwafix_Display_Shutdown(display);

	Gwafix_GraphicContext_Destroy(display->context);
	
	glfwTerminate();
	free(display);
	display = NULL;
}

void Gwafix_Display_Shutdown(Gwafix_Display_Display* display)
{
	if (!display)
	{
		LogError("Display NULL", "Display is NULL, can not shutdown window!");
		return;
	}

	if (!display->window)
	{
		LogWarning("Window NULL", "Window is NULL, check if the pointer was lost somewhere. This window could have been shutdown before.");
		return;
	}

	//clears out the desktop callback events
	free(display->onWindowResizeCallback);
	free(display->onWindowCloseCallback);
	free(display->onMousePositionCallback);
	free(display->onMouseScrollCallback);
	free(display->onKeyCallback);
	free(display->onMouseButtonCallback);
	free(display->onKeyTypeCallback);
	free(display->onFocusCallback);
	
	display->onWindowResizeCallback = NULL;
	display->windowResizeEventCount = 0;
	display->onWindowCloseCallback = NULL;
	display->windowCloseEventCount = 0;
	display->onMousePositionCallback = NULL;
	display->mousePositionEventCount = 0;
	display->onMouseScrollCallback = NULL;
	display->MouseScrollEventCount = 0;
	display->onKeyCallback = NULL;
	display->keyEventCount = 0;
	display->onMouseButtonCallback = NULL;
	display->mouseButtonEventCount = 0;
	display->onKeyTypeCallback = NULL;
	display->keyTypeEventCount = 0;
	display->onFocusCallback = NULL;
	display->focusEventCount = 0;

	display->isRunning = false;
	glfwDestroyWindow(display->window);
	display->window = NULL;
}

void Gwafix_Display_Resize(Gwafix_Display_Display* display, int32_t width, int32_t height, int32_t xPos, int32_t yPos)
{
	if (!display)
	{
		LogError("Display NULL", "Display is NULL, can not resize window!");
		return;
	}

	if (!display->context)
	{
		LogError("Graphic Context NULL", "Context is NULL, can not resize window!");
		return;
	}

	Gwafix_GraphicContext_Viewport(display->context, width, height, xPos, yPos);
	display->height = height;
	display->width = width;
}

void Gwafix_Display_SwapRenderBuffer(Gwafix_Display_Display* display)
{
	if (!display)
	{
		LogError("Display NULL", "Display is NULL, can not swap render buffers!");
		return;
	}

	if (!display->window)
	{
		LogError("Display Window NULL", "Display window is NULL, can not swap render buffers!");
		return;
	}

	glfwSwapBuffers(display->window);
}

void Gwafix_Display_Clear(Gwafix_Display_Display* display)
{
	if (!display)
	{
		LogError("Display NULL", "Display is NULL, can not clear window!");
		return;
	}

	if (!display->context)
	{
		LogError("Graphic Context NULL", "Context is NULL, can not clear window!");
		return;
	}

	Gwafix_GraphicContext_Clear(display->context);
}

void Gwafix_Display_PollEvents(Gwafix_Display_Display* display)
{
	//don't check disp;ay valid since it's not needed in Opengl

	glfwPollEvents();
}

double Gwafix_Display_GetTime(Gwafix_Display_Display* display)
{
	//don't check disp;ay valid since it's not needed in Opengl

	return glfwGetTime();
}

//----GLFW Callbacks----//
#define GetWindowPointer ((Gwafix_Display_Display*)glfwGetWindowUserPointer(window))

void GLFWErrorCallBack(int error, const char* description)
{
	LogData("Gwafix GLFW Error: (%i) || %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onWindowResizeCallback)
	{
		for (uint32_t i = 0; i < display->windowResizeEventCount; i++)
		{
			if (!display->onWindowResizeCallback[i])
			{
				LogError("Window Resize Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onWindowResizeCallback[i](width, height);
		}
	}

	Gwafix_Display_Resize(display, width, height, 0, 0);
}

void window_close_callback(GLFWwindow* window)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onWindowCloseCallback)
	{
		for (uint32_t i = 0; i < display->windowCloseEventCount; i++)
		{
			if (!display->onWindowCloseCallback[i])
			{
				LogError("Window Close Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onWindowCloseCallback[i]();
		}
	}

	Gwafix_Display_Shutdown(display);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onMousePositionCallback)
	{
		for (uint32_t i = 0; i < display->mousePositionEventCount; i++)
		{
			if (!display->onMousePositionCallback[i])
			{
				LogError("Window Mouse Position Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onMousePositionCallback[i](xpos, ypos);
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onMouseScrollCallback)
	{
		for (uint32_t i = 0; i < display->MouseScrollEventCount; i++)
		{
			if (!display->onMouseScrollCallback[i])
			{
				LogError("Window Mouse Scroll Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onMouseScrollCallback[i](xoffset, yoffset);
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onKeyCallback)
	{
		for (uint32_t i = 0; i < display->keyEventCount; i++)
		{
			if (!display->onKeyCallback[i])
			{
				LogError("Window Key Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onKeyCallback[i](key, scancode, action, mods);
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onMouseButtonCallback)
	{
		for (uint32_t i = 0; i < display->mouseButtonEventCount; i++)
		{
			if (!display->onMouseButtonCallback[i])
			{
				LogError("Window Mouse Button Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onMouseButtonCallback[i](button, action, mods);
		}
	}
}

void character_callback(GLFWwindow* window, unsigned int keycode)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onKeyTypeCallback)
	{
		for (uint32_t i = 0; i < display->keyTypeEventCount; i++)
		{
			if (!display->onKeyTypeCallback[i])
			{
				LogError("Window Key Type Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onKeyTypeCallback[i](keycode);
		}
	}
}

void window_focus_callback(GLFWwindow* window, int focused)
{
	Gwafix_Display_Display* display = GetWindowPointer;

	//call events
	if (display->onFocusCallback)
	{
		for (uint32_t i = 0; i < display->focusEventCount; i++)
		{
			if (!display->onFocusCallback[i])
			{
				LogError("Window Focus Event", "Not all events have valid func pointers but space was allocated!");
				continue;
			}

			display->onFocusCallback[i](focused);
		}
	}
}
