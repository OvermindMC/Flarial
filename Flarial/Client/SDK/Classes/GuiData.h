#pragma once
#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

class GuiData {
public:
	BUILD_ACCESS(this, Vec2<float>, screenResA, 0x30);
	BUILD_ACCESS(this, Vec2<float>, screenResB, 0x38);
	BUILD_ACCESS(this, Vec2<float>, screenResC, 0x40);
	BUILD_ACCESS(this, float, uiScale, 0x4C);
};