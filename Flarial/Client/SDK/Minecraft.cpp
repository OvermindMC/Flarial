#include "Minecraft.h"

auto MC::getClientInstance(void) -> ClientInstance* {

	static uintptr_t sig = NULL;

	if (sig == NULL)
		sig = Mem::findSig("48 8B 15 ?? ?? ?? ?? 48 8B 12 48 89 16 40 84 FF 74 ?? 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B C6 48 8B 4C 24 ?? 48 33 CC E8 ?? ?? ?? ?? 48 8B 5C 24 ?? 48 8B 74 24 ?? 48 83 C4 ?? 5F C3 E8 ?? ?? ?? ?? 90 CC CC CC CC CC CC CC CC CC 48 89 6C 24");

	auto offset = *(int*)(sig + 3);
	auto basePtr = (uintptr_t)(uintptr_t**)(sig + offset + 7);

	return ((ClientInstance*)Mem::findMultiLvlPtr(basePtr, { 0x0, 0x48, 0x0, 0x0 }, true));

};

auto MC::getLocalPlayer(void) -> Player* {

	return (getClientInstance() != nullptr ? getClientInstance()->getPlayer() : nullptr);

};

auto MC::getMoveInputHandler(void) -> MoveInputHandler* {

	return (getClientInstance() != nullptr ? getClientInstance()->getMoveInputHandler() : nullptr);

};

auto MC::gameIsFullScreen(void) -> bool {

	auto instance = getClientInstance();
	auto guidata = (instance != nullptr ? instance->getGuiData() : nullptr);

	if (guidata == nullptr)
		return false;

	if (guidata->uiScale < 3.f)
		return false;

	auto window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");
	
	DWORD windowProcessId;
	GetWindowThreadProcessId(window, &windowProcessId);

	WINDOWPLACEMENT placement;
	GetWindowPlacement(window, &placement);

	return placement.showCmd == 1;

};