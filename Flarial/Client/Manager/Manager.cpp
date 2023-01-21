#include "Manager.h"
#include "Hook/Hook.h"
#include "Category/Category.h"

/* Module Includes */

#include "Category/Module/Modules/Render/TabGui.h"
#include "Category/Module/Modules/Misc/Uninject.h"
#include "Category/Module/Modules/Misc/TestMod.h"

/* Hooks */

#include "Hook/Hooks/RenderContext/HookRenderCtx.h"
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
	new Uninject(this);
	new TestMod(this);

	MH_Initialize();

	new HookRenderCtx(this);
	new HookNetwork(this);
	new HookEntity(this);
	new HookKey(this);

	{ /* GameMode */

		auto sig = Mem::findSig("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 8B 89 ? ? ? ? 48 85 C9 74 11 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C9 74 17");

		if (sig) {

			auto offset = *(int*)(sig + 3);
			auto VTable = (uintptr_t**)(sig + offset + 7);

			new Hook<void, GameMode*>(this, "GameModeTick", (uintptr_t)VTable[8], [&](GameMode* GM) {

				auto _this = getHook<void, GameMode*>("GameModeTick");

				if(_this) {

					for (auto [type, category] : this->categories) {

						for (auto mod : category->modules) {

							if (mod->isEnabled)
								mod->callEvent<GameModeTickEvent>(GameModeTickEvent{ GM });

						};
					};

					_this->_Func(GM);

				};

			});

		};

	};

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