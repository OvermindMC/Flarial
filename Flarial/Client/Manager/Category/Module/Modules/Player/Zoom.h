#pragma once
#include "../../Module.h"

class Zoom : public Module {
public:
	Zoom(Manager* mgr) : Module(mgr->categories[CategoryType::PLAYER], "Zoom") {

		registerEvent<ModuleEvent>([&](ModuleEvent* args) {

			if(args->isTicking && !args->isEnabled)
				return;
			
			auto player = MC::getLocalPlayer();
			
			if(player)
				player->setFieldOfViewModifier(1.f);

		});

		registerEvent<GameModeTickEvent>([&](GameModeTickEvent* args) {

			auto player = args->GM->player;
			player->setFieldOfViewModifier(0.3f);

		});

	};
};