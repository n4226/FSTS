#include "FlightSimTerrainSystemApp.h"
#include "scenes/TestScene.h"

using namespace sunrise;

FlightSimTerrainSystemApp::FlightSimTerrainSystemApp()
	: Application(new WorldScene(this))
	//: Application(new TestScene(this))
	//: Application(new UIScene(this))
{

}

FlightSimTerrainSystemApp::~FlightSimTerrainSystemApp()
{

}

const char* FlightSimTerrainSystemApp::getName()
{
	return "FSTS";
}

void FlightSimTerrainSystemApp::startup()
{
	Application::startup();
	// was cosing problems for some unknown reason
	//SR_INFO("Startup");
}

void FlightSimTerrainSystemApp::shutdown()
{
    SR_TRACE("Shutdown Initiated");
    
	Application::shutdown();
}


sunrise::Application* sunrise::CreateApplication() {
	return new FlightSimTerrainSystemApp();
}
