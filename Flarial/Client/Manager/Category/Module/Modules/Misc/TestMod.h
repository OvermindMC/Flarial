#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		this->isEnabled = true;

		registerEvent<ModuleEventArgs>([&](ModuleEventArgs* args) {

			if (args->isTicking && args->isEnabled) {

				if (MC::getLocalPlayer())
					MC::getLocalPlayer()->isOnGround = true;

			};

		});

	};
};