#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		//this->isEnabled = true;

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			//

		});

		registerEvent<ModuleEvent>([&](ModuleEvent* args) {

			auto player = MC::getLocalPlayer();
			
			if (!args->isTicking && args->isEnabled) {

				if (player) {

					auto lerp = Vec3<float>(0.f, 2.f, 0.f);

					player->lerpMotion(&lerp);
					player->isFlying = true;

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