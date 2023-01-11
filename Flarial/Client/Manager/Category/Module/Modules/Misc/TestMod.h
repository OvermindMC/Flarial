#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		this->isEnabled = true;

		registerEvent<ModuleEventArgs>([&](ModuleEventArgs* args) {

			auto player = MC::getLocalPlayer();
			
			if (args->isTicking) {

				if (player) {

					auto motion = Vec3<float>(0.f, 2.f, 0.f);
					
					if (player->isBlocking())
						player->lerpMotion(&motion);

					Sleep(50);

				};

			}
			else {

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