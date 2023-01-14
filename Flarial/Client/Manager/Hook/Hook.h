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
	};
public:
	static inline std::function<T(TArgs...)> callback = [&](TArgs... args) -> T { return (T)NULL; };
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