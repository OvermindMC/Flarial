#include "Minecraft.h"

auto MC::getClientInstance(void) -> ClientInstance* {

	static uintptr_t sig = NULL;

	if (sig == NULL)
		sig = Mem::findSig("48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 83 39 ? 74 ? 48 8B 05 ? ? ? ? 48 85 C0 74 ? F0 FF 40 ? 48 8B 05 ? ? ? ? 48 8B 0D ? ? ? ? 48 89 43 ? 48 8b C3 48 89 3B C6 43 ? ? 48 89 4B ? 48 8B 5C 24 ? 48 83 C4 ? 5F C3 33 C0 48 8b CF 48 89 03 88 43 ? 48 89 43 ? 48 89 43 ? E8 ? ? ? ? 48 8B C3 48 8b 5C 24 ? 48 83 C4 ? 5f C3 CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 11");

	auto offset = *(int*)(sig + 3);
	auto basePtr = (uintptr_t)(uintptr_t**)(sig + offset + 7);

	return ((ClientInstance*)Mem::findMultiLvlPtr(basePtr, { 0x0, 0x48, 0x0 }, true));

};

auto MC::getLocalPlayer(void) -> Player* {

	return (getClientInstance() != nullptr ? getClientInstance()->getPlayer() : nullptr);

};