#pragma once
#include "Player.h"
#include "GuiData.h"
#include "MinecraftGame.h"
#include "LoopbackPacketSender.h"

class ClientInstance {
public:
	auto getPlayer(void) -> Player* {
		return Utils::CallVFunc<24, Player*>(this);
	};
public:
	auto getGuiData(void) -> GuiData* {
		return *(GuiData**)((uintptr_t)(this) + 0x500);
	};
public:
	auto getMcGame(void) -> MinecraftGame* {
		return *(MinecraftGame**)((uintptr_t)(this) + 0xA8);
	};
public:
	auto getLpSender(void) -> LoopbackPacketSender* {
		return *(LoopbackPacketSender**)((uintptr_t)(this) + 0xE0);
	};
};