#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	bool boolVar = false;
	float floatVar = 1.f;
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod", "Test Mod for Developers") {

		registerEvent<ModuleEvent>([&](ModuleEvent* args) {

			if(args->isTicking)
				return;
			
			auto instance = MC::getClientInstance();
			auto player = (instance ? instance->getPlayer() : nullptr);

			if (args->isEnabled) {

				if (player) {

					player->setPos(Vec3<float>(100.f, 200.f, 300.f));

				};

			};

		});

		registerEvent<ClickGuiModConfigEvent>([&](auto) {

			ImGui::Checkbox("Checkbox", &boolVar);
			ImGui::SliderFloat("Slider", &floatVar, .0f, 100.f);

		});

	};
};