#pragma once

#include "Sunrise.h"

#include "XPLM/XPLMDisplay.h"
#include "XPLM/XPLMGraphics.h"
#include "XPLM/XPLMPlugin.h"
#include "XPLM/XPLMMenus.h"
#include "XPLM/XPLMDataAccess.h"
#include <string>

class DataRefManager
{
public:

	static DataRefManager* shared();

	void runFrame();

	sunrise::SimlinkMessages::simpleUpdate latestUpdate;

private:
	DataRefManager();
	~DataRefManager();

	void readAll();

	//data refs 

	XPLMDataRef latd;
	XPLMDataRef lond;
	XPLMDataRef altd;

	XPLMDataRef thetaf;
	XPLMDataRef phif;
	XPLMDataRef psif;

};

