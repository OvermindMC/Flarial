#pragma once
#include "../../Module.h"

class FreeLook : public Module {
public:
	bool canWrite = false;
	Vec2<float> rotations;
public:
	FreeLook(Manager* mgr) : Module(mgr->categories[CategoryType::PLAYER], "Free Look") {

		registerEvent<ModuleEvent>([&](ModuleEvent* args) {

			if (args->isTicking)
				return;
			
			if(args->isEnabled) {

				auto player = MC::getLocalPlayer();

				if (player) {

					rotations = player->bodyRot;
					canWrite = true;

				}
				else {

					this->isEnabled = false;

				};

			}
			else {

				canWrite = false;

			};

		});

		registerEvent<InterpolatorTickEvent>([&](InterpolatorTickEvent* args) {

			if(!canWrite)
				return;

			auto player = MC::getLocalPlayer();
			
			if(player && player->runtimeId == args->entity->runtimeId) {

				player->bodyRot = rotations;

			};

		});

		registerEvent<PacketEvent>([&](PacketEvent* args) {

			auto pkt = args->packet;

			if(pkt->VTable == MovePlayerPacket().VTable) {

				auto currPkt = (MovePlayerPacket*)pkt;

				currPkt->bodyRot = rotations;
				currPkt->headYaw = rotations.y;

			}
			else if (pkt->VTable == PlayerAuthInputPacket().VTable) {

				auto currPkt = (PlayerAuthInputPacket*)pkt;

				currPkt->bodyRot = rotations;
				currPkt->headYaw = rotations.y;

			};

		});

	};
};