#pragma once

#include "Sunrise.h"

class FlightSimTerrainSystemApp: public Sunrise::Application
{
public:

	FlightSimTerrainSystemApp();
	~FlightSimTerrainSystemApp();

	const char* getName() override;

};

