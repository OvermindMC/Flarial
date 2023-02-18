#pragma once
#include "Classes/ClientInstance.h"

class MC {
public:
	static auto getClientInstance(void) -> ClientInstance*;
	static auto getLocalPlayer(void) -> Player*;
public:
	static auto getMoveInputHandler(void) -> MoveInputHandler*;
public:
	static auto gameIsFullScreen(void) -> bool;
};