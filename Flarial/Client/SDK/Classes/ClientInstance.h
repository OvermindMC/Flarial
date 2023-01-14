#pragma once
#include "Player.h"
#include "MinecraftGame.h"

class ClientInstance {
public:
	auto getPlayer(void) -> LocalPlayer* {
		return Utils::CallVFunc<24, LocalPlayer*>(this);
	};
public:
	auto getMcGame(void) -> MinecraftGame* {
		return *(MinecraftGame**)((uintptr_t)(this) + 0xA8);
	};
};