#include "Manager.h"
#include "Hook/Hook.h"

/* Module Includes */

#include "Category/Module/Modules/Misc/TestMod.h"

/* Manager Constructor */

Manager::Manager(Client* c) {

	this->client = c;

	for (auto I = (int)CategoryType::RENDER; I <= (int)CategoryType::MISC; I++) {

		auto type = (CategoryType)I;
		this->categories[type] = new Category(this, type);

	};

	new TestMod(this);

	MH_Initialize();

	new Hook<void, uintptr_t*, uintptr_t*>(this, "RenderContext", Mem::findSig("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 54 24 ? 4C"),
		[&](uintptr_t* p1, uintptr_t* ctx) {

			auto _this = getHook<void, uintptr_t*, uintptr_t*>("RenderContext");
			
			if(_this) {

				/* Draw stuff via ctx here */

				_this->_Func(p1, ctx);

			};

		}
	);

	new Hook<void, uint64_t, bool>(this, "KeyHook", Mem::findSig("48 ? ? 48 ? ? ? 4C 8D 05 ? ? ? ? 89"),
		[&](uint64_t key, bool isDown) {

			auto _this = getHook<void, uint64_t, bool>("KeyHook");
			
			if(_this) {

				if (key != VK_ESCAPE)
					_this->_Func(key, isDown);

			};

		}
	);

	for (;;) {

		for (auto [type, category] : this->categories)
			category->tick();

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