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
			auto dists = std::map<uint64_t, double>();
			auto entities = this->category->manager->entityMap;

			for (auto [runtimeId, entity] : entities) {

				if (player->runtimeId == runtimeId)
					continue;

				if (!entity->isAlive())
					continue;

				auto pos = entity->getPos();
				auto dist = pos->dist(*myPos);

				if (dist <= 12.f)
					dists[runtimeId] = dist;

			};

			if (dists.empty())
				return;

			for (auto [runtimeId, dist] : dists) {

				auto entity = (entities.contains(runtimeId) ? entities[runtimeId] : nullptr);

				if (entity == nullptr)
					continue;

				player->swing();
				gm->attack(entity);

			};

		});

	};
};