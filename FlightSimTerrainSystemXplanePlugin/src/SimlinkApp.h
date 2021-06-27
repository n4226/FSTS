#pragma once


#include "Sunrise.h"

class SimlinkApp: public sunrise::Application
{
public:

	SimlinkApp();
	~SimlinkApp();

private:

	virtual void run() override;
	virtual void shutdown() override;

	virtual const char* getName() override { return "Simlink for X-plane"; }

	ApplicationConfig configure() override;

};

