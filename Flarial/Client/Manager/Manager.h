#pragma once
#include "../Client.h"

enum class CategoryType;
class Category;

template<typename T, typename... TArgs> class Hook;

class Manager {
public:
	Client* client = nullptr;
public:
	std::map<enum CategoryType, class Category*> categories;
	std::vector<__int64*> hooks;
public:
	Manager(Client*);
public:
	template<typename T, typename... TArgs>
	auto getHook(const char*) -> Hook<T, TArgs...>*;
};