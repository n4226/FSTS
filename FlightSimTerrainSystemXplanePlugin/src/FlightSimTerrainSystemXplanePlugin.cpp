


//#include "XPLM/XPLMUtilities.h"
#include "XPLM/XPLMDisplay.h"
#include "XPLM/XPLMGraphics.h"
#include "XPLM/XPLMPlugin.h"
#include "XPLM/XPLMMenus.h"
#include "XPLM/XPLMDataAccess.h"
#include "XPLM/XPLMProcessing.h"

#include "DataRefManager.h"

#include <string.h>
#if IBM
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#elif __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


#ifndef XPLM200
#error This is made to be compiled against the XPLM200 SDK
#endif

#include "Sunrise.h"
#define SR_NO_AUTO_ENTRY
#include "Sunrise/Sunrise/core/EntryPoint.h"

sunrise::Application* sunrise::CreateApplication() {
	//throw std::runtime_error("");
	return new sunrise::NO_APPLICATION();
}


// An opaque handle to the window we will create
static XPLMWindowID	helloWindow;

// Callbacks we will register when we create our window
void				draw_hello_world(XPLMWindowID in_window_id, void* in_refcon);
int					dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void* in_refcon) { return 0; }
XPLMCursorStatus	dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void* in_refcon) { return xplm_CursorDefault; }
int					dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void* in_refcon) { return 0; }
void				dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void* in_refcon, int losing_focus) { }


static void ReloadPluginsMenuHandler(void* mRef, void* iRef);
XPLMFlightLoopID flightLoopId;

static float	MyFlightLoopCallback(
	float                inElapsedSinceLastCall,
	float                inElapsedTimeSinceLastFlightLoop,
	int                  inCounter,
	void* inRefcon);

PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	strcpy(outName, "Fs Terrain System Simlink X-plane Plugin");
	strcpy(outSig, "SkyStarDevelopment.surnise.simlink.v1.0a1.plugin");
	strcpy(outDesc, "The plugin for sending X-Plane tellemetry to the Fs Terrain System / sunrise engine");

	//main(0,nullptr);


	XPLMCreateWindow_t params;
	params.structSize = sizeof(params);
	params.visible = 1;
	params.drawWindowFunc = draw_hello_world;
	// Note on "dummy" handlers:
	// Even if we don't want to handle these events, we have to register a "do-nothing" callback for them
	params.handleMouseClickFunc = dummy_mouse_handler;
	params.handleRightClickFunc = dummy_mouse_handler;
	params.handleMouseWheelFunc = dummy_wheel_handler;
	params.handleKeyFunc = dummy_key_handler;
	params.handleCursorFunc = dummy_cursor_status_handler;
	params.refcon = NULL;
	params.layer = xplm_WindowLayerFloatingWindows;
	// Opt-in to styling our window like an X-Plane 11 native window
	// If you're on XPLM300, not XPLM301, swap this enum for the literal value 1.
	params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;

	// Set the window's initial bounds
	// Note that we're not guaranteed that the main monitor's lower left is at (0, 0)...
	// We'll need to query for the global desktop bounds!
	int left, bottom, right, top;
	XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
	params.left = left + 50;
	params.bottom = bottom + 150;
	params.right = params.left + 200;
	params.top = params.bottom + 200;

	helloWindow = XPLMCreateWindowEx(&params);

	// Position the window as a "free" floating window, which the user can drag around
	XPLMSetWindowPositioningMode(helloWindow, xplm_WindowPositionFree, -1);
	// Limit resizing our window: maintain a minimum width/height of 100 boxels and a max width/height of 300 boxels
	XPLMSetWindowResizingLimits(helloWindow, 200, 200, 300, 300);
	XPLMSetWindowTitle(helloWindow, "Sample Window");

	{

		/* First we must fill in the passed in buffers to describe our
	 * plugin to the plugin-system. */
	/*	XPLMMenuID	id;
		int			item;

		item = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "ReloadPlugins", NULL, 1);

		id = XPLMCreateMenu("ReloadPlugins", XPLMFindPluginsMenu(), item, ReloadPluginsMenuHandler, NULL);
		XPLMAppendMenuItem(id, "Reload", (void*)"Reload plugins", 1);*/



	}

	DataRefManager::shared();

	{
		XPLMCreateFlightLoop_t params;

		params.structSize = sizeof(params);
		params.phase = xplm_FlightLoop_Phase_AfterFlightModel;
		params.callbackFunc = MyFlightLoopCallback;
		params.refcon = nullptr;

		flightLoopId = XPLMCreateFlightLoop(&params);

		XPLMScheduleFlightLoop(flightLoopId, -1, true);

	}

	sunrise::runEngine();

	return 1;
}

PLUGIN_API void	XPluginStop(void) {
	XPLMDestroyWindow(helloWindow);
	helloWindow = NULL;

	XPLMDestroyFlightLoop(flightLoopId);
	flightLoopId = nullptr;
}


PLUGIN_API int  XPluginEnable(void) {
	return 1;
}


PLUGIN_API void XPluginDisable(void) {

}


PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { 
	
}


void	draw_hello_world(XPLMWindowID in_window_id, void* in_refcon)
{
	// Mandatory: We *must* set the OpenGL state before drawing
	// (we can't make any assumptions about it)
	XPLMSetGraphicsState(
		0 /* no fog */,
		0 /* 0 texture units */,
		0 /* no lighting */,
		0 /* no alpha testing */,
		1 /* do alpha blend */,
		1 /* do depth testing */,
		0 /* no depth writing */
	);

	int l, t, r, b;
	XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);

	float col_white[] = { 1.0, 1.0, 1.0 }; // red, green, blue

	XPLMDrawString(col_white, l + 10, t - 20, "Hello world!", NULL, xplmFont_Proportional);
}



void ReloadPluginsMenuHandler(void* mRef, void* iRef)
{
	if (!strcmp((char*)iRef, "Reload plugins"))
	{
		XPLMReloadPlugins();
	}
}




float	MyFlightLoopCallback(
	float                inElapsedSinceLastCall,
	float                inElapsedTimeSinceLastFlightLoop,
	int                  inCounter,
	void* inRefcon)
{
	DataRefManager::shared()->runFrame();

	return -1;
}


//#if IBM
//#include <windows.h>
//BOOL APIENTRY DllMain(HANDLE hModule,
//	DWORD ul_reason_for_call,
//	LPVOID lpReserved
//)
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//	case DLL_PROCESS_DETACH:
//		break;
//	}
//	return TRUE;
//}
//#endif