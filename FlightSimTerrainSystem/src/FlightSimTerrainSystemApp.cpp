#include "FlightSimTerrainSystemApp.h"


FlightSimTerrainSystemApp::FlightSimTerrainSystemApp()
{
	SR_INFO("Startup");


FlightSimTerrainSystemApp::~FlightSimTerrainSystemApp()
{

}

const char* FlightSimTerrainSystemApp::getName()
{
	return "FSTS";
}


Sunrise::Application* Sunrise::CreateApplication() {
	return new FlightSimTerrainSystemApp();
}