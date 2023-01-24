#pragma once
#include "../Manager.h"

enum class CategoryType {
	RENDER = 1, PLAYER = 2, WORLD = 3, MOVE = 4, MISC = 5
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