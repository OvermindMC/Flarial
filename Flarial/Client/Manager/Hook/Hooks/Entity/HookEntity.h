#pragma once
#include "../../Hook.h"
#include "../../../Category/Module/Module.h"

class HookEntity : public Hook<void, Actor*> {
public:
	HookEntity(Manager* mgr) : Hook<void, Actor*>(mgr, "ActorBaseTick", Mem::findSig("48 8D 05 ? ? ? ? 48 89 03 48 C7 83 F0 05 00 00 00 00 00 00"), 51,
		[&](Actor* entity) {
			
			auto _this = this->manager->getHook<void, Actor*>("ActorBaseTick");
				
			if(_this) {

				this->manager->entityMap[entity->runtimeId] = entity;
				_this->_Func(entity);

			};
			
		}
	) {
		new Hook<void, Actor*, void*>(this->manager, "ActorInterpolatorTick", (uintptr_t)this->sig, 256,
		[&](Actor* entity, void* p2){
			
			auto _this = this->manager->getHook<void, Actor*, void*>("ActorInterpolatorTick");
			
			if(_this) {

				for (auto [type, category] : this->manager->categories) {

					for (auto mod : category->modules) {

						if (mod->isEnabled)
							mod->callEvent<InterpolatorTickEvent>(InterpolatorTickEvent{ entity });

					};
				};

				_this->_Func(entity, p2);

			};
			
		});
	};
};