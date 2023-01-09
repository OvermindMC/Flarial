#pragma once
#include "Classes/ClientInstance.h"

class MC {
public:
	static auto getClientInstance(void) -> ClientInstance*;
public:
	AS_FIELD(ClientInstance*, clientInstance, getClientInstance);
};