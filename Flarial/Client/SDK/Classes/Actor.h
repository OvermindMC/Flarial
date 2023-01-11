#pragma once
#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

class Actor {
public:
	BUILD_ACCESS(this, bool, isOnGround, 0x188);
public:
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x350), Vec3<float>, motion, 0x18);
private:
	virtual ~Actor(void);
public:
	//
};