#pragma once

#include "Sunrise.h"

using namespace sunrise;

class TestSceneCoordinator: public sunrise::gfx::SceneRenderCoordinator
{
public:
	using SceneRenderCoordinator::SceneRenderCoordinator;

	void createPasses() override;

};

