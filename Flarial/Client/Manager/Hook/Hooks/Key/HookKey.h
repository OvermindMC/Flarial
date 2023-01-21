#pragma once
#include "../../Hook.h"
#include "../../../Category/Module/Module.h"

class HookKey : public Hook<void, uint64_t, bool> {
public:
	HookKey(Manager* mgr) : Hook<void, uint64_t, bool>(mgr, "KeyHook", Mem::findSig("48 ? ? 48 ? ? ? 4C 8D 05 ? ? ? ? 89"),
		[&](uint64_t key, bool isDown){
			
			auto cancel = false;
			auto _this = this->manager->getHook<void, uint64_t, bool>("KeyHook");
			
			if(_this) {

				this->manager->keyMap[key] = isDown;

				for (auto [type, category] : this->manager->categories) {

					for (auto mod : category->modules) {

						if (mod->isEnabled)
							mod->callEvent<KeyEvent>(KeyEvent{ key, isDown, &cancel });

					};

				};

				if(!cancel)
					_this->_Func(key, isDown);

			};
			
		}
	) {};
};