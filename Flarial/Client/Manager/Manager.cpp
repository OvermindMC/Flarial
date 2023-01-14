#include "Manager.h"

template<typename T, typename... TArgs>
class Hook {
public:
	Manager* manager = nullptr;
public:
	using Func = T(__thiscall*)(TArgs...);
	Func _Func = (Func)nullptr;
public:
	static T detourCallback(TArgs... args) {
		if(callback)
			callback(args...);
	};
public:
	static inline std::function<T(TArgs...)> callback = [&](TArgs... args) -> T {};
	__int64* sig;
public:
	const char* name;
public:
	Hook(Manager* mgr, const char* name, uintptr_t sig, std::function<T(TArgs...)> cb) {

		this->name = name;
		this->manager = mgr;
		this->callback = cb;
		this->sig = (__int64*)sig;

		if (MH_CreateHook((void*)sig, &detourCallback, reinterpret_cast<LPVOID*>(&_Func)) != MH_OK) {
			Utils::debugOutput("Failed to initialize " + std::string(name) + " hook!");
			return;
		};

		MH_EnableHook((void*)sig);
		this->manager->hooks.push_back((__int64*)this);

	};
};

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

	auto renderCtxHook = new Hook<void, uintptr_t*, uintptr_t*>(
		this,
		"RenderContext",
		Mem::findSig("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 54 24 ? 4C"),
		[&](uintptr_t* p1, uintptr_t* ctx) {

			auto _this = getHook<void, uintptr_t*, uintptr_t*>("RenderContext");
			
			if(_this) {

				/* Draw stuff via ctx here */

				_this->_Func(p1, ctx);

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