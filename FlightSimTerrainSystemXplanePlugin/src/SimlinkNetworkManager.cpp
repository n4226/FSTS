#include "SimlinkNetworkManager.h"

#include "Sunrise/Sunrise/networking/networking.h"

SimlinkNetworkManager* SimlinkNetworkManager::global;


void SimlinkNetworkManager::makeShared(sunrise::Application& app) {
	global = new SimlinkNetworkManager(app);
}

SimlinkNetworkManager* SimlinkNetworkManager::shared() {
	return global;
}

void SimlinkNetworkManager::sendSimpleUpdate(const sunrise::SimlinkMessages::simpleUpdate& data)
{
	networkManager->clientSend(data);
}

SimlinkNetworkManager::SimlinkNetworkManager(sunrise::Application& app)
	: app(app)
{
	sunrise::NetworkManager::CreateOptions options{};

	options.type = sunrise::NetworkManager::Type::client;
	
	networkManager = new sunrise::NetworkManager(options, *app.context);
	networkManager->connect("127.0.0.1");
	//networkManager->connect("26.81.92.243");

	void* msg = malloc(1);
	networkManager->clientSend(msg,1);
}

SimlinkNetworkManager::~SimlinkNetworkManager()
{

}
