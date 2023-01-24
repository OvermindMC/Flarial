#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		registerEvent<ModuleEvent>([&](ModuleEvent* args) {

			if (!args->isTicking && args->isEnabled) {

				auto instance = MC::getClientInstance();
				auto player = (instance != nullptr ? instance->getPlayer() : nullptr);

				if (player) {

					std::ostringstream o;
					o << std::hex << player;

					Utils::debugOutput("Player: " + o.str());

				};

			};

		});

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			auto ctx = args->ctx;
			auto instance = ctx->instance;
			auto player = instance->getPlayer();

			if (player) {

				auto font = instance->getMcGame()->mcFont;
				auto gamePos = Vec3<float>(0.f, -58.f, 0.f);
				auto dist = player->getPos()->dist(gamePos);

				std::ostringstream o;
				o << std::setprecision(4) << dist;

				auto fontSize = std::fmin(std::fmax(dist, 0.8f), 1.f);
				
				auto text = std::string(std::to_string((int)(gamePos.x)) + ", " + std::to_string((int)(gamePos.y)) + ", " + std::to_string((int)(gamePos.z)));
				text += " [ " + o.str() + " ]";

				auto screenPos = ctx->gameToScreenPos(gamePos);
				auto len = ctx->getTextLength(font, &text, fontSize, false);

				screenPos.x -= (len / 2.f);

				ctx->fillRectangle(Rect(screenPos.x - 2.f, screenPos.y - fontSize, (screenPos.x + 2.f) + len, screenPos.y + (fontSize * 10.f)), Color(21.f, 21.f, 21.f, .8f));
				ctx->drawText(font, text, screenPos, Color(), fontSize);
				ctx->flushText(0.f);

			};

		});

	};
};