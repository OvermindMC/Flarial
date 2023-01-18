#pragma once
#include "../../Module.h"

class TabGui : public Module {
public:
	bool selectedCategory = false, selectedMod = false;
	int currCategory = 0, currModule = 0;
public:
	float alpha = 0.f;
	int renderFrame = 0;
public:
	TabGui(Manager* mgr) : Module(mgr->categories[CategoryType::RENDER], "TabGui") {

		this->isEnabled = true;

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			this->renderFrame++;
			
			if(this->renderFrame < 3)
				return;

			this->renderFrame = 0;

			auto instance = args->ctx->instance;
			auto mcGame = (instance != nullptr ? instance->getMcGame() : nullptr);
			auto font = (mcGame != nullptr ? mcGame->mcFont : nullptr);

			if (instance == nullptr || font == nullptr)
				return;

			Utils::reachOff(&alpha, (mcGame->canUseKeys ? 1.f : 0.f), 0.05f);
			
			if (alpha <= 0.f)
				return;
			
			auto mgr = this->category->manager;
			auto client = mgr->client;

			args->ctx->drawText(font, client->name, Vec2<float>(10.f, 10.f), Color(255.f, 255.f, 255.f, alpha), 1.f);
			args->ctx->flushText(0.f);

		});

	};
};