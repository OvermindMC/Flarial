#include "Actor.h"

auto Actor::getHealth(void) -> int {

	static uintptr_t sig = NULL;
	auto health = 0;

	if (sig == NULL)
		sig = Mem::findSig("48 83 EC ? 48 8B 01 48 8D 15 ? ? ? ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? F3 0f 10 88 ? ? ? ? F3 0F 2C C1 66 0F 6E C0 8D 48 ? 0F 5B C0 0F 2F C1 0F 42 C1 48 83 C4 ? C3 CC CC CC CC 48 83 EC");

	if (sig != NULL) {

		try {

			using GetHealth = __int64(__thiscall*)(Actor*);
			auto _GetHealth = (GetHealth)sig;

			std::stringstream o;
			
			o << _GetHealth(this);
			o >> health;

		} catch (const std::runtime_error& e) {};

	};

	return health;

};