#pragma once
#include "../Manager.h"

enum class CategoryType {
	RENDER = 1, COMBAT = 2, PLAYER = 3, EXPLOIT = 4, WORLD = 5, MOVE = 6, MISC = 7
};

class Module;

class Category {
public:
	Manager* manager = nullptr;
public:
	CategoryType type;
	std::vector<Module*> modules;
public:
	Category(Manager*, CategoryType);
public:
	auto tick(void) -> void;
public:
	auto getName(void) -> std::string;
};