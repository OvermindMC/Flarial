#pragma once
#include "../../Hook.h"
#include "../../../Category/Module/Module.h"

class HookGameMode : public Hook<void, GameMode*> {
public:
	HookGameMode(Manager* mgr) : Hook<void, GameMode*>(mgr, "GameModeTick", Mem::findSig("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 8B 89 ? ? ? ? 48 85 C9 74 11 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C9 74 17"), 8,
		[&](GameMode* GM){
			
			auto _this = this->manager->getHook<void, GameMode*>("GameModeTick");
			
			if(_this) {

				for (auto [type, category] : this->manager->categories) {

					for (auto mod : category->modules) {

						if (mod->isEnabled)
							mod->callEvent<GameModeTickEvent>(GameModeTickEvent{ GM });

					};
				};

				_this->_Func(GM);

			};
			
		}
	) {};
};