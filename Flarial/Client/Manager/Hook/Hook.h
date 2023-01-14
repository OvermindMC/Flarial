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
	std::function<T(TArgs...)> callback;
	__int64* sig;
public:
	Hook(Manager* mgr, const char* name, unsigned long long sig, std::function<T(TArgs...)> cb) {
		
		this->sig = sig;
		this->name = name;
		this->manager = mgr;
		this->callback = cb;

		if (MH_CreateHook((void*)sig, &cb, reinterpret_cast<LPVOID*>(&_Func)) != MH_OK) {
			Utils::debugOutput("Failed to initialize " + std::string(name) " hook!");
			return;
		};

		MH_EnableHook((void*)sig);

	};
};