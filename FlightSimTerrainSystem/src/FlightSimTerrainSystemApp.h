#pragma once

#include "Sunrise.h"
#include "Sunrise/Sunrise/core/EntryPoint.h"

class FlightSimTerrainSystemApp: public sunrise::Application
{
public:
	FlightSimTerrainSystemApp();
	~FlightSimTerrainSystemApp();

	const char* getName() override;

	void startup() override;
	//void run() override;
	void shutdown() override;

}; 

