#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		this->isEnabled = true;

		registerEvent<ModuleEventArgs>([&](ModuleEventArgs* args) {

			if (args->isTicking && args->isEnabled) {

				auto player = MC::getClientInstance()->getPlayer();

				if (player == nullptr)
					return;

				player->isOnGround = true;

			};

		});

	};
};