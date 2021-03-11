#include "TestScene.h"
#include "TestSceneCoordinator.h"

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

	SR_INFO("Test Scene Loaded");
}

void TestScene::update()
{

}

void TestScene::unload()
{

}
