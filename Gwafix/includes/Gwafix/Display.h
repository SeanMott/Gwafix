//genaric Display

#ifndef Display_h
#define Display_h

#ifdef __cplusplus

extern "C" {
#endif

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
	void Gwafix_Display_CreateInfo_Init(Gwafix_Display_CreateInfo* info);
	//sets the window section of data
	void Gwafix_Display_CreateInfo_Window(Gwafix_Display_CreateInfo* info, const char* name, uint32_t width, uint32_t height);
	//sets the clear color
	void Gwafix_Display_CreateInfo_ClearColor(Gwafix_Display_CreateInfo* info, float red, float green, float blue, float alpha);
	//sets the clear color || expects a 4 element array
	void Gwafix_Display_CreateInfo_ClearColorVec(Gwafix_Display_CreateInfo* info, float* clearColor);

	//sets the settings section
	void Gwafix_Display_CreateInfo_Enables(Gwafix_Display_CreateInfo* info, bool enableBlending, bool enableFaceCulling, bool enableZBuffer, bool enableResizing);
	//sets the settings section || expects a 4 element array
	void Gwafix_Display_CreateInfo_EnablesVec(Gwafix_Display_CreateInfo* info, bool* settings);

	//sets the window focuse, close, resize, and rotate callbacks section for the Create Info || rotate is not supported
	void Gwafix_Display_CreateInfo_WindowStateCallbacks(Gwafix_Display_CreateInfo* info,
		void(**onWindowResizeCallback)(int32_t width, int32_t height), uint8_t windowResizeEventCount,
		void(**onWindowCloseCallback)(), uint8_t windowCloseEventCount,
		void(**onFocusCallback)(bool isFocused), uint8_t focusEventCount /*add rotate*/);

	//sets the desktop input callbacks section for the Create Info
	void Gwafix_Display_CreateInfo_DesktopInputWindowCallbacks(Gwafix_Display_CreateInfo* info,
		void(**onMousePositionCallback)(double xPos, double yPos), uint8_t mousePositionEventCount,
		void(**onMouseScrollCallback)(double xOffset, double yOffset), uint8_t MouseScrollEventCount,
		void(**onKeyCallback)(int32_t key, int32_t scancode, int32_t action, int32_t mods), uint8_t keyEventCount,
		void(**onMouseButtonCallback)(int32_t button, int32_t action, int32_t mods), uint8_t mouseButtonEventCount,
		void(**onKeyTypeCallback)(uint32_t key), uint8_t keyTypeEventCount);

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

#ifdef __cplusplus

}
#endif

#endif