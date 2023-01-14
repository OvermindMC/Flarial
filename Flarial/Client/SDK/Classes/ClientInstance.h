#pragma once
#include "Player.h"
#include "GuiData.h"
#include "MinecraftGame.h"

class ClientInstance {
public:
	auto getPlayer(void) -> LocalPlayer* {
		return Utils::CallVFunc<24, LocalPlayer*>(this);
	};
public:
	auto getGuiData(void) -> GuiData* {
		return *(GuiData**)((uintptr_t)(this) + 0x500);
	};
public:
	auto getMcGame(void) -> MinecraftGame* {
		return *(MinecraftGame**)((uintptr_t)(this) + 0xA8);
	};
};