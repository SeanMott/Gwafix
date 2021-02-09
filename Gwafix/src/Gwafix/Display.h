//genaric Display

#ifndef Display_h
#define Display_h

#include <Gwafix\GraphicContext.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <Logger.h>

//window state callback params
#define Gwafix_Display_CallbackPrams_Resize int32_t width, int32_t height
#define Gwafix_Display_CallbackPrams_Focuse bool isFocused

//window desktop input callback params
#define Gwafix_Display_CallbackPrams_Key int32_t key, int32_t scancode, int32_t action, int32_t mods
#define Gwafix_Display_CallbackPrams_KeyTyped uint32_t key
#define Gwafix_Display_CallbackPrams_MouseButton int32_t button, int32_t action, int32_t mods
#define Gwafix_Display_CallbackPrams_MousePos double xPos, double yPos
#define Gwafix_Display_CallbackPrams_MouseScroll double xOffset, double yOffset

//window phone input callback params

//create info struct for Display
typedef struct
{
	//window
	char* name;
	uint32_t width, height;
	float* clearColor;

	//settings
	bool enableBlending, enableFaceCulling, enableZBuffer, enableResizeing;

	//desktop callbacks
	uint8_t windowResizeEventCount;
	uint8_t windowCloseEventCount;
	uint8_t mousePositionEventCount;
	uint8_t MouseScrollEventCount;
	uint8_t keyEventCount;
	uint8_t mouseButtonEventCount;
	uint8_t keyTypeEventCount;
	uint8_t focusEventCount;

	void(**onWindowResizeCallback)(Gwafix_Display_CallbackPrams_Resize);
	void(**onWindowCloseCallback)();
	void(**onMousePositionCallback)(Gwafix_Display_CallbackPrams_MousePos);
	void(**onMouseScrollCallback)(Gwafix_Display_CallbackPrams_MouseScroll);
	void(**onKeyCallback)(Gwafix_Display_CallbackPrams_Key);
	void(**onMouseButtonCallback)(Gwafix_Display_CallbackPrams_MouseButton);
	void(**onKeyTypeCallback)(Gwafix_Display_CallbackPrams_KeyTyped);
	void(**onFocusCallback)(Gwafix_Display_CallbackPrams_Focuse);
	

} Gwafix_Display_CreateInfo;

//inits the Create Info
inline void Gwafix_Display_CreateInfo_Init(Gwafix_Display_CreateInfo* info)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	//sets up window
	info->name = calloc(13, sizeof(char));
	info->name = "Gwafix Window";
	info->width = 800;
	info->height = 800;
	info->clearColor = (float*)calloc(4, sizeof(float));
	info->clearColor[0] = 0.0f; info->clearColor[1] = 173.0f; info->clearColor[2] = 173.0f;
	info->clearColor[3] = 1.0f;

	//defaults render settings
	info->enableBlending = true;
	info->enableZBuffer = false;
	info->enableFaceCulling = true;
	info->enableResizeing = true;

	//zeros out the desktop callback events
	info->onWindowResizeCallback = NULL;
	info->windowResizeEventCount = 0;
	info->onWindowCloseCallback = NULL;
	info->windowCloseEventCount = 0;
	info->onMousePositionCallback = NULL;
	info->mousePositionEventCount = 0;
	info->onMouseScrollCallback = NULL;
	info->MouseScrollEventCount = 0;
	info->onKeyCallback = NULL;
	info->keyEventCount = 0;
	info->onMouseButtonCallback = NULL;
	info->mouseButtonEventCount = 0;
	info->onKeyTypeCallback = NULL;
	info->keyTypeEventCount = 0;
	info->onFocusCallback = NULL;
	info->focusEventCount = 0;
}

//sets the window section of data
inline void Gwafix_Display_CreateInfo_Window(Gwafix_Display_CreateInfo* info, const char* name, uint32_t width, uint32_t height)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	info->name = name;
	info->width = width;
	info->height = height;
}

//sets the clear color
inline void Gwafix_Display_CreateInfo_ClearColor(Gwafix_Display_CreateInfo* info, float red, float green, float blue, float alpha)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	info->clearColor[0] = red; info->clearColor[1] = green; info->clearColor[2] = blue; info->clearColor[3] = alpha;
}

//sets the clear color || expects a 4 element array
inline void Gwafix_Display_CreateInfo_ClearColorVec(Gwafix_Display_CreateInfo* info, float* clearColor)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	if (!clearColor)
	{
		LogWarning("Display Info: clearColor NULL", "clearColor can not be NULL");
		return;
	}

	info->clearColor = clearColor;
}

//sets the settings section
inline void Gwafix_Display_CreateInfo_Enables(Gwafix_Display_CreateInfo* info, bool enableBlending, bool enableFaceCulling, bool enableZBuffer, bool enableResizing)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	info->enableBlending = enableBlending;
	info->enableFaceCulling = enableFaceCulling;
	info->enableZBuffer = enableZBuffer;
	info->enableResizeing = enableResizing;
}

//sets the settings section || expects a 4 element array
inline void Gwafix_Display_CreateInfo_EnablesVec(Gwafix_Display_CreateInfo* info, bool* settings)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	if (!settings)
	{
		LogWarning("Display Info: settings NULL", "Settings was found to be NULL all be set to false!");
		info->enableBlending = false;
		info->enableFaceCulling = false;
		info->enableZBuffer = false;
		info->enableResizeing = false;
		return;
	}

	info->enableBlending = settings[0];
	info->enableFaceCulling = settings[1];
	info->enableZBuffer = settings[2];
	info->enableResizeing = settings[3];
}

//sets the window focuse, close, resize, and rotate callbacks section for the Create Info || rotate is not supported
inline void Gwafix_Display_CreateInfo_WindowStateCallbacks(Gwafix_Display_CreateInfo* info,
	void(**onWindowResizeCallback)(int32_t width, int32_t height), uint8_t windowResizeEventCount,
	void(**onWindowCloseCallback)(), uint8_t windowCloseEventCount,
	void(**onFocusCallback)(bool isFocused), uint8_t focusEventCount /*add rotate*/)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	info->onWindowCloseCallback = onWindowCloseCallback;
	info->windowCloseEventCount = windowCloseEventCount;
	info->onWindowResizeCallback = onWindowResizeCallback;
	info->windowResizeEventCount = windowResizeEventCount;
	info->onFocusCallback = onFocusCallback;
	info->focusEventCount = focusEventCount;

	//rotate
}

//sets the desktop input callbacks section for the Create Info
inline void Gwafix_Display_CreateInfo_DesktopInputWindowCallbacks(Gwafix_Display_CreateInfo* info,
	void(**onMousePositionCallback)(double xPos, double yPos), uint8_t mousePositionEventCount,
void(**onMouseScrollCallback)(double xOffset, double yOffset), uint8_t MouseScrollEventCount,
void(**onKeyCallback)(int32_t key, int32_t scancode, int32_t action, int32_t mods), uint8_t keyEventCount,
void(**onMouseButtonCallback)(int32_t button, int32_t action, int32_t mods), uint8_t mouseButtonEventCount,
void(**onKeyTypeCallback)(uint32_t key), uint8_t keyTypeEventCount)
{
	if (!info)
	{
		LogError("Display Info NULL", "Can't mod values!");
		return;
	}

	info->onMousePositionCallback = onMousePositionCallback;
	info->mousePositionEventCount = mousePositionEventCount;
	info->onMouseScrollCallback = onMouseScrollCallback;
	info->MouseScrollEventCount = MouseScrollEventCount;
	info->onKeyCallback = onKeyCallback;
	info->keyEventCount = keyEventCount;
	info->onMouseButtonCallback = onMouseButtonCallback;
	info->mouseButtonEventCount = mouseButtonEventCount;
	info->onKeyTypeCallback = onKeyTypeCallback;
	info->keyTypeEventCount = keyTypeEventCount;
}

//sets the phone input callbacks section for the Create Info || not supported

//defines a Display
typedef struct
{
	//window data
	/*union
	{
		void* window;
		void* surface;
	};*/

	void* window;
	int32_t width, height;
	bool isRunning;

	//desktop callbacks
	uint8_t windowResizeEventCount;
	uint8_t windowCloseEventCount;
	uint8_t mousePositionEventCount;
	uint8_t MouseScrollEventCount;
	uint8_t keyEventCount;
	uint8_t mouseButtonEventCount;
	uint8_t keyTypeEventCount;
	uint8_t focusEventCount;

	void(**onWindowResizeCallback)(Gwafix_Display_CallbackPrams_Resize);
	void(**onWindowCloseCallback)();
	void(**onMousePositionCallback)(Gwafix_Display_CallbackPrams_MousePos);
	void(**onMouseScrollCallback)(Gwafix_Display_CallbackPrams_MouseScroll);
	void(**onKeyCallback)(Gwafix_Display_CallbackPrams_Key);
	void(**onMouseButtonCallback)(Gwafix_Display_CallbackPrams_MouseButton);
	void(**onKeyTypeCallback)(Gwafix_Display_CallbackPrams_KeyTyped);
	void(**onFocusCallback)(Gwafix_Display_CallbackPrams_Focuse);

	//phone callbacks


	Gwafix_GraphicContext_GraphicContext* context;

} Gwafix_Display_Display;

//creates a Display
Gwafix_Display_Display* Gwafix_Display_Create(Gwafix_Display_CreateInfo* info);
//destroys a Display
void Gwafix_Display_Destroy(Gwafix_Display_Display* display);

//shutsdown a Display
void Gwafix_Display_Shutdown(Gwafix_Display_Display* display);
//resizes a Display
void Gwafix_Display_Resize(Gwafix_Display_Display* display, int32_t width, int32_t height, int32_t xPos, int32_t yPos);

//swaps the render buffer
void Gwafix_Display_SwapRenderBuffer(Gwafix_Display_Display* display);
//clears the screen
void Gwafix_Display_Clear(Gwafix_Display_Display* display);
//polls for input
void Gwafix_Display_PollEvents(Gwafix_Display_Display* display);
//gets the time
double Gwafix_Display_GetTime(Gwafix_Display_Display* display);

#endif