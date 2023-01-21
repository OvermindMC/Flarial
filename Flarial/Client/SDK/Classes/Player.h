#pragma once
#include "Actor.h"

class Player : public Actor {
public:
	auto getSupplies(void) -> PlayerInventory* {
		return *(PlayerInventory**)((uintptr_t)(this) + 0xDB8);
	};
public:
	auto getGameMode(void) -> GameMode* {
		return *(GameMode**)((uintptr_t)(this) + 0x1658);
	};
private:
	virtual ~Player(void);
public:
	auto setSprinting(bool state) -> void {

		return Utils::CallVFunc<284, void, bool>(this, state);

	};
};