#pragma once
#include "../../Module.h"

class Uninject : public Module {
public:
	Uninject(Manager* mgr) : Module(mgr->categories[CategoryType::MISC], "Uninject") {

		registerEvent<ModuleEvent>([&](ModuleEvent* args) {

			if (!args->isTicking && args->isEnabled) {

				auto mgr = this->category->manager;
				for (auto [type, category] : mgr->categories) {

					for (auto mod : category->modules) {

						if (mod->isEnabled)
							mod->callEvent<ModuleEvent>(ModuleEvent{ false, false });

					};

				};

				MH_DisableHook(MH_ALL_HOOKS);
				Sleep(100);

				MH_Uninitialize();
				FreeLibraryAndExitThread(Mem::getDll(), 1);

			};

		});

	};
};