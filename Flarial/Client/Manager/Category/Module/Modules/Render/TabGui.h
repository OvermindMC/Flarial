#pragma once
#include "../../Module.h"

class TabGui : public Module {
public:
	bool selectedCategory = false, selectedMod = false;
	int currCategory = 0, currModule = 0;
public:
	float alpha = 0.f;
public:
	TabGui(Manager* mgr) : Module(mgr->categories[CategoryType::RENDER], "TabGui") {

		this->isEnabled = true;

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			auto instance = args->ctx->instance;
			auto font = (instance != nullptr && instance->getMcGame() != nullptr ? instance->getMcGame()->mcFont : nullptr);

			if (instance == nullptr || font == nullptr)
				return;
			
			auto mgr = this->category->manager;
			auto client = mgr->client;

			args->ctx->drawText(font, client->name, Vec2<float>(10.f, 10.f), Color(255.f, 255.f, 255.f), 1.f);
			args->ctx->flushText(0.f);

		});

	};
};