#include "TestScene.h"
#include "TestSceneCoordinator.h"

#include "Sunrise/Sunrise/world/simlink/SimlinkMessages.h"

TestScene::TestScene(sunrise::Application* app)
	: Scene(app)
{
	coordinator = new TestSceneCoordinator(this);

}

TestScene::~TestScene()
{
	delete coordinator;
}

void TestScene::load()
{
	sunrise::NetworkManager::CreateOptions netOptions{};

	netOptions.newThread = false;
	netOptions.type = sunrise::NetworkManager::Type::server;
	netOptions.udpBufferSize = sizeof(sunrise::SimlinkMessages::simpleUpdate);

	networkManager = new sunrise::NetworkManager(netOptions, *app.context);

	networkManager->registerUDPMessageCalback(std::function([](const sunrise::SimlinkMessages::simpleUpdate& data) {
		SR_INFO("got a simpleUpdate: position: ({}, {}, {})", data.lla.x, data.lla.y, data.lla.z);
		
	}));

	SR_INFO("Test Scene Loaded");
}

void TestScene::update()
{

}

void TestScene::unload()
{

}
