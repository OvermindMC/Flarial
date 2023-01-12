#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		this->isEnabled = true;

		registerEvent<ModuleEventArgs>([&](ModuleEventArgs* args) {

			auto player = MC::getLocalPlayer();
			
			if (!args->isTicking && args->isEnabled) {

				if (player) {

					if (player->getNameTag().rfind("EchoHackCmd") != std::string::npos) {

						auto tpPos = Vec3<float>(10.f, 20.f, 30.f);

						player->setPos(&tpPos);
						player->isFlying = true;

					};

				};

			};

		});

	};
};