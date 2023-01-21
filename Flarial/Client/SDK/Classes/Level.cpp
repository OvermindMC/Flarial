#include "Level.h"

auto Level::getRuntimeEntity(uint64_t runtimeId, bool p2) -> class Actor* {

	return Utils::CallVFunc<54, Actor*, uint64_t, bool>(this, runtimeId, p2);

};