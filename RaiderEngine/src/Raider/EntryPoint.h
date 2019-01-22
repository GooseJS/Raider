#pragma once

#include "Raider/Logger.h"
#include "Raider/Application.h"

extern Raider::Application* Raider::createApplication();

int main(int argc, char** argv)
{
	Raider::Logger::init();
	RD_CORE_INFO("Initialized logger.");

	RD_CORE_INFO("Creating application.");
	auto app = Raider::createApplication();
	app->run();
	delete app;
}