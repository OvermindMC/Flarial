#include "ClientInstance.h"

auto ClientInstance::getPlayer(void) -> LocalPlayer* {

	return Utils::CallVFunc<24, LocalPlayer*>(this);

};