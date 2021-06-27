#include "SimlinkApp.h"

SimlinkApp::SimlinkApp()
	: Application(nullptr)
{
}

SimlinkApp::~SimlinkApp()
{
}

void SimlinkApp::run() {

}

void SimlinkApp::shutdown() {

}

SimlinkApp::ApplicationConfig SimlinkApp::configure() {
	ApplicationConfig config{};

	config.enableMarl = false;
	config.vulkan = false;
	config.wantsWindows = false;
	config.enableAsioContextThread = false;
	config.enableAsioContext = true;
	config.useFileSys = false;

	return config;
}

