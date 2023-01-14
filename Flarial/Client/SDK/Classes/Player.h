#pragma once
#include "Actor.h"

class LocalPlayer : public Actor {
private:
	virtual ~LocalPlayer(void);
public:
	auto setSprinting(bool state) -> void {

		return Utils::CallVFunc<284, void, bool>(this, state);

	};
};