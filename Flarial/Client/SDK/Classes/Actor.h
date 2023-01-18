#pragma once
#include "PlayerInventory.h"

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
public:
	virtual auto isRuntimePredictedMovementEnabled(void) -> bool;
	virtual auto getPredictedMovementValues(void) -> class PredictedMovementValues*;
public:
	virtual auto getPosition(void) -> Vec3<float>*;
	virtual auto getPosPrev(void) -> Vec3<float>*;
	virtual auto getPosExtrapolated(float) -> const Vec3<float>;
public:
	virtual auto getAttachPos(enum ActorLocation, float) -> Vec3<float>;
	virtual auto getFiringPos(void) -> Vec3<float>;
public:
	virtual auto move(class IActorMovementProxy*, Vec3<float>*) -> void;
	virtual auto move(Vec3<float>*) -> void;
public:
	virtual auto getInterpolatedRidingPosition(float) -> Vec3<float>;
public:
	virtual auto getInterpolatedBodyRot(float) -> float;
	virtual auto getInterpolatedHeadRot(float) -> float;
	virtual auto getInterpolatedBodyYaw(float) -> float;
	virtual auto getYawSpeedInDegreesPerSecond(void) -> float;
	virtual auto getInterpolatedWalkAnimSpeed(float) -> float;
	virtual auto getInterpolatedRidingOffset(float, int) -> Vec3<float>;
	virtual auto resetInterpolated(void) -> void;
public:
	virtual auto updateEntityInside(void) -> void;
	virtual auto updateEntityInside(AABB<float>*) -> void;
public:
	virtual auto isFireImmune(void) -> bool;
	virtual auto breaksFallingBlocks(void) -> bool;
public:
	virtual auto blockedByShield(class ActorDamageSource*, Actor*) -> void;
	virtual auto canDisableShield(void) -> bool;
public:
	virtual auto teleportTo(Vec3<float>*, bool, int, int, bool) -> void;
	virtual auto tryTeleportTo(Vec3<float>*, bool, int, int, bool) -> bool;
	virtual auto chorusFruitTeleport(Vec3<float>*) -> void;
public:
	virtual auto lerpMotion(Vec3<float>*) -> void;
public:
	virtual auto tryCreateAddActorPacket(void) -> class Packet*;
public:
	virtual auto normalTick(void) -> void;
	virtual auto baseTick(void) -> void;
	virtual auto passengerTick(void) -> void;
public:
	virtual auto positionPassenger(Actor*, float) -> void;
	virtual auto startRiding(Actor*) -> bool;
	virtual auto addPassenger(Actor*) -> void;
	virtual auto flagPassengerToRemove(Actor*) -> void;
public:
	virtual auto getExitTip(std::string const&, enum InputMode) -> void;
	virtual auto getEntityLocNameString(void) -> std::string const&;
public:
	virtual auto intersects(Vec3<float>*, Vec3<float>*) -> bool;
	virtual auto isInWall(void) -> bool;
	virtual auto isInvisible(void) -> bool;
	virtual auto canShowNameTag(void) -> bool;
public:
	virtual auto canExistInPeaceful(void) -> bool;
public:
	virtual auto setNameTagVisible(bool) -> void;
	virtual auto getNameTag(void) -> std::string const&;
	virtual auto getNameTagAsHash(void) -> class HashedString*;
	virtual auto getFormattedNameTag(void) -> std::string const&;
	virtual auto filterFormattedNameTag(class UIProfanityContext*) -> void;
	virtual auto setNameTag(std::string const&) -> void;
public:
	virtual auto getAlwaysShowNameTag(void) -> bool;
public:
	virtual auto setScoreTag(std::string const&) -> void;
	virtual auto getScoreTag(void) -> std::string const&;
public:
	virtual auto isInWater(void) -> bool;
	virtual auto hasEnteredWater(void) -> bool;
	virtual auto isInLava(class IConstBlockSource*) -> bool;
	virtual auto isUnderLiquid(enum MaterialType) -> bool;
	virtual auto isOverWater(void) -> bool;
public:
	virtual auto setBlockMovementSlowdownMultiplier(class BlockLegacy*, Vec3<float>*) -> void;
	virtual auto resetBlockMovementSlowdownMultiplier(void) -> void;
public:
	virtual auto getCameraOffset(void) -> float;
	virtual auto getShadowHeightOffs(void) -> float;
	virtual auto getShadowRadius(void) -> float;
	virtual auto getHeadLookVector(float) -> Vec3<float>;
public:
	virtual auto canSeeInvisible(void) -> bool; /* Spectator, function detour see spectators? */
	virtual auto canSee(Vec3<float>*) -> bool;
	virtual auto canSee(Actor*) -> bool;
public:
	virtual auto canInteractWithOtherEntitiesInGame(void) -> bool;
public:
	virtual auto isSkyLit(float) -> bool;
	virtual auto getBrightness(float) -> float;
public:
	virtual auto interactPreventDefault(void) -> void;
	virtual auto playerTouch(class Player*) -> void;
public:
	virtual auto onAboveBubbleColumn(bool) -> void;
	virtual auto onInsideBubbleColumn(bool) -> void;
public:
	virtual auto isImmobile(void) -> bool;
	virtual auto isSilent(void) -> bool;
public:
	virtual auto _doSprintParticleEffect(void) -> void;
public:
	virtual auto isPickable(void) -> bool;
	virtual auto isFishable(void) -> bool;
public:
	virtual auto isSleeping(void) -> bool;
	virtual auto setSleeping(bool) -> void;
public:
	virtual auto isShootable(void) -> bool;
public:
	virtual auto setSneaking(bool) -> void;
	virtual auto isBlocking(void) -> bool;
public:
	virtual auto isDamageBlocked(class ActorDamageSource*) -> bool;
public:
	virtual auto isAlive(void) -> bool;
	virtual auto isOnFire(void) -> bool;
	virtual auto isOnHotBlock(void) -> bool;
public:
	virtual auto isCreativeModeAllowed(void) -> bool;
public:
	virtual auto isSurfaceMob(void) -> bool;
public:
	virtual auto isTargetable(void) -> bool;
	virtual auto isLocalPlayer(void) -> bool;
	virtual auto isRemotePlayer(void) -> bool;
	virtual auto isPlayer(void) -> bool;
public:
	virtual auto isAffectedByWaterBottle(void) -> bool;
public:
	virtual auto canAttack(Actor*, bool) -> bool;
	virtual auto setTarget(Actor*) -> bool;
	virtual auto isValidTarget(Actor*) -> bool;
public:
	virtual auto attack(Actor*, enum ActorDamageCause*) -> bool;
	virtual auto performRangedAttack(Actor*, float) -> void;
public:
	virtual auto getEquipmentCount(void) -> __int64;
public:
	virtual auto setOwner(uint64_t) -> void;
public:
	virtual auto setSitting(bool) -> void;
public:
	virtual auto onTame(void) -> void;
	virtual auto onFailedTame(void) -> void;
public:
	virtual auto getInventorySize(void) -> __int64;
	virtual auto getEquipSlots(void) -> __int64;
	virtual auto getChestSlots(void) -> __int64;
public:
	virtual auto setStanding(bool) -> void;
public:
	virtual auto canPowerJump(void) -> bool;
	virtual auto setCanPowerJump(bool) -> void;
	virtual auto isJumping(void) -> bool;
public:
	virtual auto isEnchanted(void) -> bool;
public:
	virtual auto vehicleLanded(Vec3<float>&, Vec3<float>&) -> void;
public:
	virtual auto shouldRender(void) -> bool;
public:
	virtual auto playAmbientSound(void) -> void;
	virtual auto getAmbientSound(void) -> enum LevelSoundEvent;
public:
	virtual auto isInvulnerableTo(class ActorDamageSource*) -> bool;
	virtual auto getBlockDamageCause(class Block&) -> enum ActorDamageCause;
public:
	virtual auto animateHurt(void) -> void;
	virtual auto doFireHurt(int) -> void;
public:
	virtual auto onLightningHit(void) -> void;
	virtual auto onBounceStarted(Vec3<int>&, class Block&) -> void;
public:
	virtual auto feed(int) -> void;
public:
	virtual auto handleEntityEvent(enum ActorEvent, int) -> void;
public:
	virtual auto getPickRadius(void) -> float;
};