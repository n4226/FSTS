#include "TestSceneCoordinator.h"


class TestRenderStage : public sunrise::gfx::GPURenderStage {
public:
	using gfx::GPURenderStage::GPURenderStage;

	// Inherited via GPURenderStage
	virtual vk::CommandBuffer* encode(uint32_t subpass, sunrise::Window& window) override
	{
		auto buff = selectAndSetupCommandBuff(subpass, window);

		buff->end();

		return buff;
	}
};



void TestSceneCoordinator::createPasses()
{

	auto mainStage = TestRenderStage(app, "TestStage");

	registerStage(&mainStage, {}, {}, {});

}
