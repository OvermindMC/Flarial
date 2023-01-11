#pragma once
#include "../Client.h"

enum class CategoryType;
class Category;

class Manager {
public:
	Client* client = nullptr;
public:
	std::map<enum CategoryType, class Category*> categories;
public:
	Manager(Client*);
};