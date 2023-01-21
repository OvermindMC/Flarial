#pragma once
#include "../../Hook.h"
#include "../../../Category/Module/Module.h"

class HookNetwork : public Hook<void, LoopbackPacketSender*, Packet*> {
public:
	HookNetwork(Manager* mgr) : Hook<void, LoopbackPacketSender*, Packet*>(mgr, "LoopbackSend", Mem::findSig("48 89 5C 24 08 57 48 83 EC 20 48 8B D9 48 8B FA 48 8B 49 10"),
		[&](LoopbackPacketSender* lp, Packet* packet) {
			
			auto _this = this->manager->getHook<void, LoopbackPacketSender*, Packet*>("LoopbackSend");
			auto cancel = false;

			if(_this) {

				for (auto [ type, category ] : this->manager->categories) {

					for (auto mod : category->modules) {

						if (mod->isEnabled)
							mod->callEvent<PacketEvent>(PacketEvent{ &cancel, packet });

					};

				};

				if (!cancel)
					_this->_Func(lp, packet);

			};
			
		}
	) {};
};