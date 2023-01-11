#pragma once
#include "Player.h"

class ClientInstance {
public:
	auto getPlayer(void) -> LocalPlayer* {
		return Utils::CallVFunc<24, LocalPlayer*>(this);
	};
};