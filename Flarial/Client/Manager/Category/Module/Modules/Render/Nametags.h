#pragma once
#include "../../Module.h"

class Nametags : public Module {
public:
	int ctxFrames = 0;
public:
	Nametags(Manager* mgr) : Module(mgr->categories[CategoryType::RENDER], "Nametags") {

		registerEvent<ImGuiEvent>([&](auto) {

			/* WIP */

		});

	};
};