#pragma once
#include "../../Module.h"

class Killaura : public Module {
public:
	Killaura(Manager* mgr) : Module(mgr->categories[CategoryType::COMBAT], "Killaura") {

		this->isEnabled = true;

		registerEvent<GameModeTickEvent>([&](GameModeTickEvent* args) {

			auto gm = args->GM;
			auto player = gm->player;
			auto myPos = player->getPos();

			auto I = 0;
			forEachEntity([&](Actor* entity, bool isRegular) {

				if(I >= 2 || !isRegular || entity->runtimeId == player->runtimeId || !entity->isAlive())
					return;

				auto pos = entity->getPos();
				auto dist = pos->dist(*myPos);

				if (dist >= 12.f)
					return;

				I++;
				player->swing();
				gm->attack(entity);

			}, [&](Actor* first, Actor* second) {
				return first->getPos()->dist(*myPos) < second->getPos()->dist(*myPos);
			});

		});

	};
};