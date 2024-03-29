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
	std::map<uint64_t, Actor*> entityMap;
public:
	std::map<uint64_t, bool> keyMap;
	auto isUsingKey(uint64_t key) -> bool {
		return (keyMap.contains(key) ? keyMap[key] : false);
	};
public:
	explicit Manager(Client*);
public:
	template<typename T, typename... TArgs>
	auto getHook(const char*) -> Hook<T, TArgs...>*;
private:
	std::chrono::high_resolution_clock::time_point lastNotif;
	std::vector<class ImGuiNotif*> notifications;
public:
	auto addNotification(std::string title, std::string contents, ImGuiToastType type) -> void;
	auto tickNotifications(void) -> void;
};

class ImGuiNotif {
public:
	std::string title;
	std::string contents;
public:
	ImGuiToastType type;
public:
	ImGuiNotif(std::string t, std::string c, ImGuiToastType tp) {
		this->type = tp;
		this->title = t;
		this->contents = c;
	}
};