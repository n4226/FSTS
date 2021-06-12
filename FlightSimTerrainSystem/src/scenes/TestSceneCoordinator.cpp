#include "TestSceneCoordinator.h"


gfx::VirtualGraphicsPipeline* testPipe() {

	static  gfx::VirtualGraphicsPipeline* cashed = nullptr;

	if (cashed != nullptr) {
		return cashed;
	}

	auto pipeOptions = sunrise::gfx::GraphicsPipelineOptions();

	pipeOptions.descriptorSetLayouts = {};

	pipeOptions.shaderStages = {
		{ "shaders/greenPipe.vert.spv",vk::ShaderStageFlagBits::eVertex },
		{ "shaders/greenPipe.frag.spv",vk::ShaderStageFlagBits::eFragment }
	};

	auto meshBindingDes = Mesh::getBindingDescription();
	pipeOptions.bindingDescriptions = std::vector(meshBindingDes.begin(), meshBindingDes.end());
	auto meshAttributeDes = Mesh::getAttributeDescriptions();
	pipeOptions.attributeDescriptions = std::vector(meshAttributeDes.begin(), meshAttributeDes.end());

	auto testPipe = new sunrise::gfx::VirtualGraphicsPipeline(std::move(pipeOptions));

	cashed = testPipe;
	return cashed;
}

class TestRenderStage : public sunrise::gfx::GPURenderStage {
public:
	using gfx::GPURenderStage::GPURenderStage;

	// Inherited via GPURenderStage
	virtual vk::CommandBuffer* encode(uint32_t subpass, sunrise::Window& window) override
	{
		auto buff = selectAndSetupCommandBuff(subpass, window);

		setPipeline(window, *buff, testPipe());

		

		buff->end();

		return buff;
	}
};



void TestSceneCoordinator::createPasses()
{




	registerPipeline(testPipe());

	auto mainStage = new TestRenderStage(app, "TestStage");

	registerStage(mainStage, {}, {}, {});

}
