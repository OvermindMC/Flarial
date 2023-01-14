#pragma once
#include "../../Module.h"

class TabGui : public Module {
public:
	TabGui(Manager* mgr) : Module(mgr->categories[CategoryType::RENDER], "TabGui") {

		this->isEnabled = true;

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			auto instance = args->ctx->instance;
			auto mcGame = (instance != nullptr ? instance->getMcGame() : nullptr);
			auto guidata = (instance != nullptr ? instance->getGuiData() : nullptr);

			if ((mcGame == nullptr || !mcGame->canUseKeys) || guidata == nullptr)
				return;

			//


		});

		registerEvent<KeyEvent>([&](KeyEvent* args) {

			auto instance = MC::getClientInstance();
			auto mcGame = (instance != nullptr ? instance->getMcGame() : nullptr);

			if (mcGame == nullptr || !mcGame->canUseKeys)
				return;
			
			if(!args->isDown)
				return;
			
			if(args->key != VK_LEFT && args->key != VK_RIGHT && args->key != VK_DOWN && args->key != VK_UP)
				return;

		});

	};
};