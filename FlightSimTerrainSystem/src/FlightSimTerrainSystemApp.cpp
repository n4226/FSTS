#include "FlightSimTerrainSystemApp.h"


using namespace sunrise;

FlightSimTerrainSystemApp::FlightSimTerrainSystemApp()
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
	SR_INFO("Startup");
}

void FlightSimTerrainSystemApp::shutdown()
{
	SR_TRACE("Shutdown Initiated");
}


sunrise::Application* sunrise::CreateApplication() {
	return new FlightSimTerrainSystemApp();
}