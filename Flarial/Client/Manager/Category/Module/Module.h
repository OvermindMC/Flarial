#pragma once
#include "../Category.h"
#include "../../Event/Event.h"

class Module {
public:
	Category* category = nullptr;
	Events* events = nullptr;
public:
	bool wasEnabled = false, isEnabled = false;
public:
	Module(Category*);
public:
	auto tick(void) -> void;
};