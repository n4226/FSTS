#pragma once

#include "Sunrise.h"


class TestSceneCoordinator: public sunrise::gfx::SceneRenderCoordinator
{
public:
	using SceneRenderCoordinator::SceneRenderCoordinator;

	void createPasses() override;

	sunrise::gfx::ComposableRenderPass::CreateOptions renderpassConfig(vk::Format swapChainFormat) override;

};

