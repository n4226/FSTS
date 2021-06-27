#pragma once

#include "Sunrise.h"

class TestScene
	: public sunrise::Scene
{
public:
	//using Scene::Scene;
	TestScene(sunrise::Application* app);
	~TestScene();

	void load() override;

	void update() override;

	void unload() override;

private:
	sunrise::NetworkManager* networkManager;

};

