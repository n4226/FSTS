#pragma once

#include "Sunrise.h"

namespace sunrise {
	class NetworkManager;
}

class SimlinkNetworkManager
{
public:
	static void makeShared(sunrise::Application& app);
	static SimlinkNetworkManager* shared();

	void sendSimpleUpdate(const sunrise::SimlinkMessages::simpleUpdate& data);

private:
	SimlinkNetworkManager(sunrise::Application& app);
	~SimlinkNetworkManager();

	sunrise::NetworkManager* networkManager = nullptr;

	sunrise::Application& app;

	static SimlinkNetworkManager* global;

};

