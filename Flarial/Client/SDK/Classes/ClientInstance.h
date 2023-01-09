#pragma once
#include "Player.h"

class ClientInstance {
public:
	auto getPlayer(void) -> LocalPlayer*;
};