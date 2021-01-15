#include "DataRefManager.h"

DataRefManager::DataRefManager()
{
	// get all data refs

	// aircraft pos 
	latd = XPLMFindDataRef("sim/flightmodel/position/latitude");
	lond = XPLMFindDataRef("sim/flightmodel/position/longitude");
	altd = XPLMFindDataRef("sim/flightmodel/position/elevation");
}

DataRefManager::~DataRefManager()
{
}

DataRefManager* DataRefManager::shared()
{
	static DataRefManager* global = new DataRefManager();

	return global;
}

void DataRefManager::runFrame()
{
	readAll();
}

void DataRefManager::readAll()
{

	auto lat = XPLMGetDatad(latd);
	auto lon = XPLMGetDatad(lond);
	auto alt = XPLMGetDatad(altd);

}
