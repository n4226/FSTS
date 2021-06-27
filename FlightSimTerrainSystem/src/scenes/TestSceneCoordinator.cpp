#include "TestSceneCoordinator.h"

#include "Sunrise/Sunrise/math/mesh/MeshPrimatives.h"
#include "Sunrise/Sunrise/core/Window.h"
#include "Sunrise/Sunrise/graphics/vulkan/resources/MeshBuffers.h"
#include "Sunrise/Sunrise/graphics/vulkan/generalAbstractions/Sampler.h"
#include "Sunrise/Sunrise/graphics/vulkan/renderer/Renderer.h"

using namespace sunrise;
using namespace gfx;

/*VUlkan Cookbook is amazing*/

class TestPipe : public gfx::VirtualGraphicsPipeline {
public:

	using gfx::VirtualGraphicsPipeline::VirtualGraphicsPipeline;

protected:

	virtual GraphicsPipelineOptions makeDeff() override {
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

		return pipeOptions;
	}

};

class TestDeferredPipe : public gfx::VirtualGraphicsPipeline {
public:

	using gfx::VirtualGraphicsPipeline::VirtualGraphicsPipeline;

protected:

	virtual GraphicsPipelineOptions makeDeff() override {
		auto pipeOptions = sunrise::gfx::GraphicsPipelineOptions();

		auto layout = DescriptorSetLayoutBinding::createWholeSet(
			{
				{ vk::DescriptorType::eCombinedImageSampler, vk::ShaderStageFlagBits::eFragment }
			}
		);

		pipeOptions.descriptorSetLayouts = { {layout} }; //DescriptorSetLayout::Create();
		
		pipeOptions.shaderStages = {
			{ "shaders/greenPipeDeferred.vert.spv",vk::ShaderStageFlagBits::eVertex },
			{ "shaders/greenPipeDeferred.frag.spv",vk::ShaderStageFlagBits::eFragment }
		};

		//pipeOptions.bindingDescriptions = { makeVertBinding(0, sizeof(glm::vec2)) };
		//pipeOptions.attributeDescriptions = { makeVertAttribute(0, 0, VertexAttributeFormat::vec2, 0) };

		auto meshBindingDes = Basic2DMesh::getBindingDescription();
		pipeOptions.bindingDescriptions = std::vector(meshBindingDes.begin(), meshBindingDes.end());
		auto meshAttributeDes = Basic2DMesh::getAttributeDescriptions();
		pipeOptions.attributeDescriptions = std::vector(meshAttributeDes.begin(), meshAttributeDes.end());

		return pipeOptions;
	}

};


auto testPipe = new TestPipe();
auto testDeferredPipe = new TestDeferredPipe();

class TestRenderStage : public sunrise::gfx::GPURenderStage {
public:
	using gfx::GPURenderStage::GPURenderStage;

	Mesh* square{};
	MeshBuffer* meshBuff{};

	virtual void setup() {

		square = new Mesh(MeshPrimatives::square());

		meshBuff = new gfx::MeshBuffer(app.renderers[0]->device, app.renderers[0]->allocator, 
			{ gfx::ResourceStorageType::cpuToGpu,vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eIndexBuffer,
			vk::SharingMode::eExclusive }
			, square);
		meshBuff->writeMeshToBuffer(true);
	}

	void cleanup() override {
		delete meshBuff;
		delete square;
	}

	// Inherited via GPURenderStage
	virtual vk::CommandBuffer* encode(RunOptions options) override
	{
		auto buff = selectAndSetupCommandBuff(options);

		setPipeline(options.window, *buff, testPipe);

		
		meshBuff->bindVerticiesIntoCommandBuffer(*buff,0);
		meshBuff->bindIndiciesIntoCommandBuffer(*buff);

		buff->drawIndexed(square->indicies[0].size(), 1, 0, 0, 0);

		buff->end();

		return buff;
	}
};

class TestDeferredStage : public sunrise::gfx::GPURenderStage {
public:
	using gfx::GPURenderStage::GPURenderStage;

	//TODO add builtin support for creating and updating dewcrptors on window resize or other events

	Basic2DMesh* square{};
	Basic2DMeshBuffer* meshBuff{};

	DescriptorPool* pool;

	std::unordered_map<Window*,std::vector<DescriptorSet*>> sets{};

	Sampler* sampler;

	void setup() override
	{
		square = new Basic2DMesh(MeshPrimatives::Basic2D::screenQuad());

		meshBuff = new gfx::Basic2DMeshBuffer(app.renderers[0]->device, app.renderers[0]->allocator,
			{ gfx::ResourceStorageType::cpuToGpu,vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eIndexBuffer,
			vk::SharingMode::eExclusive }
		, square);
		meshBuff->writeMeshToBuffer(true);

		pool = new DescriptorPool(app.renderers[0]->device, { 3,{{vk::DescriptorType::eSampledImage, 3}} });

		sampler = new Sampler(app.renderers[0]->device, {});

	}
	void lateSteup() override {
		//TODO: skip onowned windows
		for (auto window : app.windows)
		{
			sets[window] = {};
			for (size_t swap = 0; swap < window->swapChainImages.size(); swap++)
			{
				auto pipeline = getConcretePipeline(*window, testDeferredPipe);
				auto des = pool->allocate(pipeline->descriptorSetLayouts);

				sets[window].push_back(des[0]);


				/* dont know whatto do :
					[12:30:56] Sunrise: Validation Error: [ VUID-vkCmdDrawIndexed-None-02687 ] Object 0: handle = 0x404f600000000045, type = VK_OBJECT_TYPE_DESCRIPTOR_SET; Object 1: handle = 0x9fe8bd0000000038, type = VK_OBJECT_TYPE_IMAGE_VIEW; Object 2: handle = 0xb09e9c0000000039, type = VK_OBJECT_TYPE_FRAMEBUFFER; | MessageID = 0x6c3b517c | VkDescriptorSet 0x404f600000000045[] encountered the following validation error at vkCmdDrawIndexed() time: VkImageView 0x9fe8bd0000000038[] is used in Descriptor in binding #0 index 0 and VkFramebuffer 0xb09e9c0000000039[] attachment # 1. The Vulkan spec states: Image subresources used as attachments in the current render pass must not be accessed in any way other than as an attachment by this command (https://vulkan.lunarg.com/doc/view/1.2.154.1/windows/1.2-extensions/vkspec.html#VUID-vkCmdDrawIndexed-None-02687)
					https://www.reddit.com/r/vulkan/comments/dm16af/some_questions_regarding_the_rewrite_of_my/
				*/

				vk::DescriptorImageInfo imageInfo = { sampler->vkItem , app.loadedScenes[0]->coordinator->sceneRenderpassHolders[0]->getImage(1,window)->view,vk::ImageLayout::eShaderReadOnlyOptimal };

				DescriptorPool::UpdateOperation updateOp = { DescriptorPool::UpdateOperation::Type::write,des[0]->makeBinding(0),0,1, DescriptorPool::UpdateOperation::ReferenceType(imageInfo) };

				pool->update({ updateOp });
			}
		}


	}



	void cleanup() override {
		delete pool;
	}

	// Inherited via GPURenderStage
	virtual vk::CommandBuffer* encode(RunOptions options) override
	{
		auto buff = selectAndSetupCommandBuff(options);

		setPipeline(options.window, *buff, testDeferredPipe);

		meshBuff->bindVerticiesIntoCommandBuffer(*buff, 0);
		meshBuff->bindIndiciesIntoCommandBuffer(*buff);

		auto pipeline = getConcretePipeline(options.window, testDeferredPipe);

		

		buff->bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline->pipelineLayout, 0, { sets[&options.window][options.window.currentSurfaceIndex]->vkItem }, {});

		buff->drawIndexed(square->indicies.size(), 1, 0, 0, 0);

		buff->end();

		return buff;
	}
};


void TestSceneCoordinator::createPasses()
{

	auto mainStage = new TestRenderStage(app, "TestStage");
	auto deferredStage = new TestDeferredStage(app, "TestDeferredStage");


	registerPipeline(testPipe,mainStage);
	registerPipeline(testDeferredPipe, deferredStage);


	registerStage(mainStage, {}, {}, {});
	registerStage(deferredStage, { mainStage }, { {0, vk::ImageLayout::eColorAttachmentOptimal, vk::AttachmentLoadOp::eClear}, {1, vk::ImageLayout::eShaderReadOnlyOptimal} }, {});

	setLastStage(deferredStage);
	
}

sunrise::gfx::ComposableRenderPass::CreateOptions TestSceneCoordinator::renderpassConfig(vk::Format swapChainFormat)
{
	auto attach = gfx::ComposableRenderPass::CreateOptions::VAttatchment();

	attach.type = gfx::ComposableRenderPass::CreateOptions::AttatchmentType::Color;
	attach.format = swapChainFormat;
	attach.loadOp = vk::AttachmentLoadOp::eClear;
	attach.initialLayout = vk::ImageLayout::eUndefined;
	attach.transitionalToAtStartLayout = vk::ImageLayout::eUndefined;//vk::ImageLayout::eColorAttachmentOptimal;
	//attach.transitionalToAtStartLayout = vk::ImageLayout::eColorAttachmentOptimal;//vk::ImageLayout::eColorAttachmentOptimal;
	attach.finalLayout = vk::ImageLayout::ePresentSrcKHR;
	attach.clearColor = { 0.8f, 0.2f, 0.0f, 1.0f };
	attach.name = "MainRenderAttach";

	auto attach2 = gfx::ComposableRenderPass::CreateOptions::VAttatchment();

	attach2.type = gfx::ComposableRenderPass::CreateOptions::AttatchmentType::Color;
	attach2.format = swapChainFormat;
	attach2.loadOp = vk::AttachmentLoadOp::eClear;
	attach2.initialLayout = vk::ImageLayout::eUndefined;
	attach2.transitionalToAtStartLayout = vk::ImageLayout::eColorAttachmentOptimal;
	attach2.finalLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
	attach2.clearColor = { 0.0f, 0.8f, 0.0f, 1.0f };
	attach2.usage |= vk::ImageUsageFlagBits::eSampled;
	//attach2.usage |= vk::ImageUsageFlagBits::eStorage;
	attach2.name = "TempRenderTarget";

	gfx::ComposableRenderPass::CreateOptions options = { {attach, attach2 }, 0};

	return options;
}


