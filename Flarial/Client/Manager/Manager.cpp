#include "Manager.h"
#include "Hook/Hook.h"
#include "Category/Category.h"

/* Module Includes */

#include "Category/Module/Modules/Render/TabGui.h"
#include "Category/Module/Modules/Player/FreeLook.h"
#include "Category/Module/Modules/Misc/Uninject.h"
#include "Category/Module/Modules/Misc/TestMod.h"

/* Hooks */

#include "Hook/Hooks/RenderContext/HookRenderCtx.h"
#include "Hook/Hooks/GameMode/HookGameMode.h"
#include "Hook/Hooks/Network/HookNetwork.h"
#include "Hook/Hooks/Entity/HookEntity.h"
#include "Hook/Hooks/Key/HookKey.h"

/* Other */

#include "../ImGui/Fonts/ProductSans.h"

/* Manager Constructor */

Manager::Manager(Client* c) {

	this->client = c;

	for (auto I = (int)CategoryType::RENDER; I <= (int)CategoryType::MISC; I++) {

		auto type = (CategoryType)I;
		this->categories[type] = new Category(this, type);

		Utils::debugOutput("Initialized Category: " + this->categories[type]->getName());

	};

	new TabGui(this);
	new FreeLook(this);
	new Uninject(this);
	new TestMod(this);

	MH_Initialize();

	new HookRenderCtx(this);
	new HookGameMode(this);
	new HookNetwork(this);
	new HookEntity(this);
	new HookKey(this);

	for (;;) {

		for (auto [type, category] : this->categories)
			category->tick();

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