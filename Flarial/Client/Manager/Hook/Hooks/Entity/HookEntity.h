#pragma once
#include "../../Hook.h"
#include "../../../Category/Module/Module.h"

class HookEntity : public Hook<void, Actor*> {
public:
	HookEntity(Manager* mgr) : Hook<void, Actor*>(mgr, "ActorBaseTick", Mem::findSig("48 8D 05 ? ? ? ? 48 89 01 48 8B 05 ? ? ? ? FF 15 ? ? ? ? 4C 8B C0"), 51,
		[&](Actor* entity) {
			
			auto _this = this->manager->getHook<void, Actor*>("ActorBaseTick");
				
			if(_this) {

				this->manager->entityMap[entity->runtimeId] = entity;
				_this->_Func(entity);

			};
			
		}
	) {};
};