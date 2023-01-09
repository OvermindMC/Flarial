#pragma once
#include "SDK/Minecraft.h"

class Manager;

class Client {
public:
	std::string name;
public:
	Manager* mgr = nullptr;
public:
	Client(std::string);
};