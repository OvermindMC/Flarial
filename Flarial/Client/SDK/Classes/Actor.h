#pragma once
#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

enum GameType { Survival = 0, Creative = 1, Adventure = 2, Default = 5 };

class Actor {
public:
	BUILD_ACCESS(this, Vec3<float>, renderPosition, 0x140);
	BUILD_ACCESS(this, bool, isOnGround, 0x188);
	BUILD_ACCESS(this, uint64_t, runtimeId, 0x418);
	BUILD_ACCESS(this, bool, isFlying, 0x998);
	BUILD_ACCESS(this, std::string, username, 0x2478);
public:
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x350), Vec3<float>, motion, 0x18);
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x360), Vec3<float>, bodyRot, 0x0);
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x358), AABB<float>, boundingBox, 0x0);
private:
	virtual ~Actor(void);
public:
	virtual auto getStatusFlag(enum ActorFlags) -> bool;
	virtual auto setStatusFlag(enum ActorFlags, bool) -> void;
public:
	virtual auto hasComponent(class HashedString*) -> bool;
public:
	virtual auto getLastHurtByMob(void) -> Actor*;
	virtual auto setLastHurtByMob(Actor*) -> void;
public:
	virtual auto getLastHurtByPlayer(void) -> class Player*;
	virtual auto setLastHurtByPlayer(class Player*) -> void;
public:
	virtual auto getLastHurtMob(void) -> Actor*;
	virtual auto setLastHurtMob(Actor*) -> void;
public:
	virtual auto outOfWorld(void) -> void;
private:
	virtual auto reloadHardcoded(enum ActorInitializationMethod, class VariantParameterList const&) -> void;
	virtual auto reloadHardcodedClient(enum ActorInitializationMethod, class VariantParameterList const&) -> void;
public:
	virtual auto initializeComponents(enum ActorInitializationMethod, class VariantParameterList const&) -> void;
	virtual auto reloadComponents(enum ActorInitializationMethod, class VariantParameterList const&) -> void;
public:
	virtual auto _serverInitItemStackIds(void) -> void;
	virtual auto _doInitialMove(void) -> void;
public:
	virtual auto resetUserPos(bool) -> void;
public:
	virtual auto getDimensionId(void) -> __int64;
public:
	virtual auto getOwnerEntityType(void) -> __int64;
	virtual auto remove(void) -> void;
public:
	virtual auto setPos(Vec3<float>*) -> void;
};