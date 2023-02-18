#pragma once
#include "../../Hook.h"
#include "../../../Category/Module/Module.h"

class HookEntity : public Hook<void, Actor*> {
public:
	HookEntity(Manager* mgr) : Hook<void, Actor*>(mgr, "ActorNormalTick", Mem::findSig("48 8D 05 ? ? ? ? 48 89 03 48 C7 83 ? ? ? ? ? ? ? ? 48 8B 8B"), 50,
		[&](Actor* entity) {
			
			auto _this = this->manager->getHook<void, Actor*>("ActorNormalTick");
				
			if(_this) {

				this->manager->entityMap[entity->getRuntimeId()] = entity;
				_this->_Func(entity);

			};
			
		}
	) {}
};
