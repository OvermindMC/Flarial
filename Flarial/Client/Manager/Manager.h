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
	std::unordered_map<uint64_t, Actor*> entityMap;
public:
	std::map<uint64_t, bool> keyMap;
	auto isUsingKey(uint64_t key) -> bool {
		return (keyMap.contains(key) ? keyMap[key] : false);
	};
public:
	Manager(Client*);
public:
	template<typename T, typename... TArgs>
	auto getHook(const char*) -> Hook<T, TArgs...>*;
};