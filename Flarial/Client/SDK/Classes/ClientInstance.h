#pragma once
#include "Player.h"
#include "GuiData.h"
#include "MinecraftGame.h"
#include "LevelRenderer.h"
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
public:
	auto getLevelRenderer(void) -> LevelRenderer* {

		return *(LevelRenderer**)((uintptr_t)(this) + 0xD0);

	};
public:
	auto getFov(void) -> Vec2<float> {

		return Vec2<float>(*(float*)((uintptr_t)(this) + 0x690), *(float*)((uintptr_t)(this) + 0x6A4));

	};
public:
	auto getbadrefdef(void) -> glmatrixf* {

		return (glmatrixf*)((uintptr_t)(this) + 0x2F0);

	};
};