#include "Manager.h"
#include "Hook/Hook.h"
#include "Category/Category.h"

/* Module Includes */

#include "Category/Module/Modules/Render/ClickGui.h"

#include "Category/Module/Modules/Player/Zoom.h"
#include "Category/Module/Modules/Player/AutoSprint.h"

#include "Category/Module/Modules/Misc/Uninject.h"
#include "Category/Module/Modules/Misc/TestMod.h"

/* Hooks */

#include "Hook/Hooks/SwapChain/HookSwapChain.h"
#include "Hook/Hooks/GameMode/HookGameMode.h"
#include "Hook/Hooks/Network/HookNetwork.h"
#include "Hook/Hooks/Entity/HookEntity.h"
#include "Hook/Hooks/Mouse/HookMouse.h"
#include "Hook/Hooks/Key/HookKey.h"

/* Manager Constructor */

Manager::Manager(Client* c) {

	this->client = c;

	for (auto I = (int)CategoryType::RENDER; I <= (int)CategoryType::MISC; I++) {

		auto type = (CategoryType)I;
		this->categories[type] = new Category(this, type);

		Utils::debugOutput("Initialized Category: " + this->categories[type]->getName());

	};

	new ClickGui(this);

	new Zoom(this);
	new AutoSprint(this);
	
	new TestMod(this);
	new Uninject(this);

	MH_Initialize();

	new HookSwapChain(this);
	new HookGameMode(this);
	/*new HookNetwork(this);
	new HookEntity(this);*/
	new MouseHook(this);
	new HookKey(this);

	for (;;) {

		for (auto [type, category] : this->categories)
			category->tick();

		this->tickNotifications();
		Sleep(1);

	};

};

template<typename T, typename... TArgs>
auto Manager::getHook(const char* name) -> Hook<T, TArgs...>* {

	auto res = (Hook<T, TArgs...>*)nullptr;

	for (auto hookPtr : this->hooks) {

		auto hook = (Hook<T, TArgs...>*)hookPtr;

		if (hook->name == name) {
			res = hook;
			break;
		};

	};

	return res;

};

auto Manager::addNotification(std::string title, std::string contents, ImGuiToastType type) -> void {

	this->notifications.push_back(new ImGuiNotif(title, contents, type));

};

auto Manager::tickNotifications(void) -> void {

	if (!ImGui::GetCurrentContext() || this->notifications.empty())
		return;

	auto now = std::chrono::high_resolution_clock::now();

	if (now < lastNotif + std::chrono::milliseconds(800))
		return;

	lastNotif = now;

	auto notif = this->notifications.front();
	ImGuiToast toast(notif->type, 2000);
	
	toast.set_title(notif->title.c_str());
	toast.set_content(notif->contents.c_str());

	ImGui::InsertNotification(toast);
	this->notifications.erase(this->notifications.begin());

};