#pragma once
#include "../../Module.h"

class TestMod : public Module {
public:
	int renderFrame = 0;
public:
	TestMod(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "TestMod") {

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			//

		});

	};
};