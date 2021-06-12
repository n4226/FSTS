#include "FlightSimTerrainSystemApp.h"
#include "scenes/TestScene.h"

using namespace sunrise;

FlightSimTerrainSystemApp::FlightSimTerrainSystemApp()
	//: Application(new WorldScene(this))
	: Application(new TestScene(this))
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
	Application::shutdown();

	SR_TRACE("Shutdown Initiated");
	
}


sunrise::Application* sunrise::CreateApplication() {
	return new FlightSimTerrainSystemApp();
}