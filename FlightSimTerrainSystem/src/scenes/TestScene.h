#pragma once

#include "Sunrise.h"

class TestScene
	: public sunrise::Scene
{
public:
	using Scene::Scene;
	~TestScene();

	void load() override;

	void update() override;

	void unload() override;

};

