#pragma once
#include "../Client.h"

class Manager {
public:
	Client* client = nullptr;
public:
	Manager(Client*);
};