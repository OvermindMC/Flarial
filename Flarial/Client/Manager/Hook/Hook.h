#pragma once
#include "../Manager.h"

template<typename T, typename... TArgs>
class Hook {
public:
	Manager* manager = nullptr;
public:
	using Func = T(__thiscall*)(TArgs...);
	Func _Func = (Func)nullptr;
public:
	static T detourCallback(TArgs... args) {
		if (callback)
			callback(args...);
		
		return T{};
	};
public:
	static inline std::function<T(TArgs...)> callback = [&](TArgs... args) -> T { return (T)NULL; };
	__int64* sig;
public:
	const char* name;
public:
	Hook(Manager* mgr, const char* name, uintptr_t vtable, size_t vTableIndex, std::function<T(TArgs...)> cb) {
		
		auto offset = *(int*)(vtable + 3);
		auto VTable = (uintptr_t**)(vtable + offset + 7);

		this->manager = mgr;

		this->name = name;
		this->manager = mgr;
		this->callback = cb;
		this->sig = (__int64*)vtable;

		if (MH_CreateHook((void*)VTable[vTableIndex], &detourCallback, reinterpret_cast<LPVOID*>(&_Func)) != MH_OK) {
			Utils::debugOutput("Failed to initialize [ " + std::string(name) + " ] hook!");
			this->manager->addNotification("[ " + std::string(name) + " ] Hook", "Failed to initialize [ " + std::string(name) + " ] hook!", ImGuiToastType_Warning);
			return;
		};

		std::ostringstream o;
		o << std::hex << VTable[vTableIndex];

		MH_EnableHook((void*)VTable[vTableIndex]);
		this->manager->hooks.push_back((__int64*)this);
		Utils::debugOutput("Successfully initialized [ " + std::string(name) + " ] hook { " + o.str() + " }");
		this->manager->addNotification("[ " + std::string(name) + " ] Hook", "Successfully initialized [ " + std::string(name) + " ] hook!", ImGuiToastType_Success);

	};
public:
	Hook(Manager* mgr, const char* name, uintptr_t sig, std::function<T(TArgs...)> cb) {

		this->manager = mgr;

		this->name = name;
		this->manager = mgr;
		this->callback = cb;
		this->sig = (__int64*)sig;

		std::ostringstream o;
		o << std::hex << sig;

		if (MH_CreateHook((void*)sig, &detourCallback, reinterpret_cast<LPVOID*>(&_Func)) != MH_OK) {
			Utils::debugOutput("Failed to initialize [ " + std::string(name) + " ] hook!");
			this->manager->addNotification("[ " + std::string(name) + " ] Hook", "Failed to initialize [ " + std::string(name) + " ] hook!", ImGuiToastType_Warning);
			return;
		};

		MH_EnableHook((void*)sig);
		this->manager->hooks.push_back((__int64*)this);
		Utils::debugOutput("Successfully initialized [ " + std::string(name) + " ] hook { " + o.str() + " }");
		this->manager->addNotification("[ " + std::string(name) + " ] Hook", "Successfully initialized [ " + std::string(name) + " ] hook!", ImGuiToastType_Success);

	};
public:
	Hook(Manager* mgr) {
		
		this->manager = mgr;

	};
};