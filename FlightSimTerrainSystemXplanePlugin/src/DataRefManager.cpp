#include "DataRefManager.h"

#include "SimlinkNetworkManager.h"

DataRefManager::DataRefManager()
{
	// get all data refs

	// aircraft pos 
	latd = XPLMFindDataRef("sim/flightmodel/position/latitude");
	lond = XPLMFindDataRef("sim/flightmodel/position/longitude");
	altd = XPLMFindDataRef("sim/flightmodel/position/elevation");

	thetaf = XPLMFindDataRef("sim/flightmodel/position/theta");
	phif = XPLMFindDataRef("sim/flightmodel/position/phi");
	psif = XPLMFindDataRef("sim/flightmodel/position/psi");
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
	// Datad is in double form
	auto lat = XPLMGetDatad(latd);
	auto lon = XPLMGetDatad(lond);
	auto alt = XPLMGetDatad(altd);

	auto theta = XPLMGetDataf(thetaf);
	auto phi = XPLMGetDataf(phif);
	auto psi = XPLMGetDataf(psif);

	sunrise::SimlinkMessages::simpleUpdate update{};

	update.id = sunrise::SimlinkMessages::simpleUpdate::msgID;
	update.lla = glm::dvec3(lat, lon, alt);
	update.rot = glm::quat(glm::vec3(theta,phi,psi));


	SimlinkNetworkManager::shared()->sendSimpleUpdate(update);

}
