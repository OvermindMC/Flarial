#pragma once
#include "Classes/ClientInstance.h"

class MC {
public:
	static auto getClientInstance(void) -> ClientInstance*;
};