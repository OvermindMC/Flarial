#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		this->isEnabled = true;

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			auto instance = args->ctx->instance;
			auto lp = (instance != nullptr ? instance->getLpSender() : nullptr);
			auto nh = (lp != nullptr ? lp->networkHandler : nullptr);
			auto raknet = (nh != nullptr ? nh->raknet : nullptr);
			auto rak = (raknet != nullptr ? raknet->instance : nullptr);

			if (rak) {

				Utils::debugOutput(rak->serverName);
				this->isEnabled = false;

			};

		});

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

		registerEvent<KeyEvent>([&](KeyEvent* args) {

			if(!args->isDown)
				return;
			
			if (args->key == VK_SPACE) {

				auto instance = MC::getClientInstance();
				auto player = instance->getPlayer();

				if (player) {

					auto motion = Vec3<float>(0.f, 1.f, 0.f);
					player->lerpMotion(&motion);

				};

			};

		});

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			/*auto instance = args->ctx->instance;
			auto font = (instance != nullptr ? instance->getMcGame()->mcFont : nullptr);

			if (!font)
				return;

			auto fontSize = 1.2f;
			auto text = std::string("Hello");
			auto textPos = Vec2<float>(10.f, 10.f);
			auto color = Color(255.f, 255.f, 255.f, 1.f);

			args->ctx->drawText(font, text, textPos, color, fontSize);
			args->ctx->flushText(0.f);*/

		});

	};
};