#pragma once
#include "../../Module.h"

class TabGui : public Module {
public:
	TabGui(Manager* mgr) : Module(mgr->categories[CategoryType::RENDER], "TabGui") {

		this->isEnabled = true;

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			//

		});

	};
};