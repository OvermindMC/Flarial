#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		this->isEnabled = true;

		registerEvent<ModuleEventArgs>([&](ModuleEventArgs* args) {

			if (args->isTicking) {

				if (MC::getLocalPlayer())
					MC::getLocalPlayer()->isOnGround = true;

			}
			else {

				auto player = MC::getLocalPlayer();
				auto tpPos = Vec3<float>(10.f, 20.f, 30.f);

				if (player) {

					if (player->getNameTag().rfind("EchoHackCmd") != std::string::npos) {
						
						player->setPos(&tpPos);
						player->isFlying = true;

					};

				};

			};

		});

	};
};