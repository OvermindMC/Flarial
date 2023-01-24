#pragma once
#include "Level.h"
#include "GameMode.h"
#include "PlayerInventory.h"

enum GameType { Survival = 0, Creative = 1, Adventure = 2, Default = 5 };

template<typename A, typename B>
class AutomaticID;

class Actor {
public:
	BUILD_ACCESS(this, Vec3<float>, renderPosition, 0x140);
	BUILD_ACCESS(this, bool, isOnGround, 0x188);
	BUILD_ACCESS(this, uint64_t, runtimeId, 0x418);
	BUILD_ACCESS(this, bool, isFlying, 0x998);
	BUILD_ACCESS(this, std::string, username, 0x2478);
public:
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x350), Vec3<float>, motion, 0x18);
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x360), Vec2<float>, bodyRot, 0x0);
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x360), Vec2<float>, bodyRot2, 0x8);
	BUILD_ACCESS(*(uintptr_t**)((uintptr_t)(this) + 0x358), AABB<float>, boundingBox, 0x0);
public:
	auto getLevel(void) -> Level*;
public:
	auto getHealth(void) -> int;
public:
	auto isHostile(void) -> bool;
	auto isPassive(void) -> bool;
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
	virtual auto getPos(void) -> Vec3<float>*;
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
public:
	virtual auto getActorRendererId(void) -> class HashedStruct*;
public:
	virtual auto spawnAtLocation(class ItemStack*, float) -> class ItemActor*;
	virtual auto spawnAtLocation(class Block*, int, float) -> class ItemActor*;
	virtual auto spawnAtLocation(class Block*, int) -> class ItemActor*;
	virtual auto spawnAtLocation(int, int, float) -> class ItemActor*;
	virtual auto spawnAtLocation(int, int) -> class ItemActor*;
public:
	virtual auto despawn(void) -> void;
	virtual auto killed(Actor*) -> void;
	virtual auto awardKillScore(Actor*, int) -> void;
public:
	virtual auto setArmor(enum ArmorSlot, class ItemStack const&) -> void;
public:
	virtual auto getArmor(enum ArmorSlot) -> void;
	virtual auto getAllArmor(void) -> std::vector<class ItemStack*>;
public:
	virtual auto getArmorMaterialTypeInSlot(enum ArmorSlot) -> enum ArmorMaterialType;
	virtual auto getArmorMaterialTextureTypeInSlot(enum ArmorSlot) -> enum ArmorTextureType;
	virtual auto getArmorColorInSlot(enum ArmorSlot, int) -> float;
public:
	virtual auto getEquippedSlot(enum EquipmentSlot) -> class ItemStack const&;
	virtual auto setEquippedSlot(enum EquipmentSlot, class ItemStack const&) -> void;
public:
	virtual auto setCarriedItem(class ItemStack*) -> void;
	virtual auto getCarriedItem(void) -> class ItemStack*;
	virtual auto setOffhandSlot(class ItemStack*) -> void;
	virtual auto getEquippedTotem(void) -> class ItemStack*;
	virtual auto consumeTotem(void) -> void;
public:
	virtual auto save(class CompoundTag*) -> bool;
	virtual auto saveWithoutId(class CompoundTag*) -> void;
	virtual auto load(class CompoundTag*, class DataLoadHelper*) -> bool;
	virtual auto loadLinks(class CompoundTag const&, class std::vector<class ActorLink, class std::allocator<class ActorLink>>&, class DataLoadHelper&) -> void;
public:
	virtual auto getEntityTypeId(void) -> uint8_t;
public:
	virtual auto queryEntityRenderer(void) -> void;
	virtual auto getSourceUniqueID(void) -> uint64_t;
public:
	virtual auto thawFreezeEffect(void) -> void;
	virtual auto canFreeze(void) -> bool;
public:
	virtual auto isWearingLeatherArmor(void) -> bool;
public:
	virtual auto getLiquidAABB(enum MaterialType) -> AABB<float>;
public:
	virtual auto handleInsidePortal(Vec3<int>*) -> void;
	virtual auto getPortalCooldown(void) -> __int64;
	virtual auto getPortalWaitTime(void) -> __int64;
public:
	virtual auto canChangeDimensionsUsingPortal(void) -> bool;
	virtual auto changeDimension(class AutomaticID<class Dimension, int>) -> void;
	virtual auto changeDimension(Packet*) -> void;
public:
	virtual auto getControllingPlayer(void) -> uint64_t;
public:
	virtual auto checkFallDamage(float, bool) -> void;
	virtual auto causeFallDamage(float, float, class ActorDamageSource) -> void;
	virtual auto handleFallDistanceOnServer(float, float, bool) -> void;
public:
	virtual auto playSynchronizedSound(enum LevelSoundEvent, Vec3<float> const&, int, bool) -> void;
	virtual auto playSynchronizedSound(enum LevelSoundEvent, Vec3<float> const&, class Block const&, bool) -> void;
public:
	virtual auto onSynchedFlagUpdate(int, __int64, __int64) -> void;
	virtual auto onSynchedDataUpdate(int) -> void;
public:
	virtual auto canAddPassenger(Actor*) -> bool;
public:
	virtual auto canPickupItem(class ItemStack*) -> bool;
public:
	virtual auto canBePulledIntoVehicle(void) -> bool;
	virtual auto inCaravan(void) -> bool;
public:
	virtual auto isLeashableType(void) -> bool;
	virtual auto tickLeash(void) -> void;
public:
	virtual auto sendMotionPacketIfNeeded(void) -> void;
public:
	virtual auto canSynchronizeNewEntity(void) -> bool;
public:
	virtual auto stopRiding(bool, bool, bool) -> void;
public:
	virtual auto startSwimming(void) -> void;
	virtual auto stopSwimming(void) -> void;
public:
	virtual auto buildDebugInfo(std::string&) -> __int64;
public:
	virtual auto getCommandPermissionLevel(void) -> enum CommandPermissionLevel;
public:
	virtual auto isClientSide(void) -> bool;
public:
	virtual auto getMutableAttribute(class Attribute*) -> class AttributeInstance*;
	virtual auto getAttribute(class Attribute*) -> class AttributeInstance*;
public:
	virtual auto getDeathTime(void) -> __int64;
	virtual auto heal(int) -> void;
public:
	virtual auto isInvertedHealAndHarm(void) -> bool;
public:
	virtual auto canBeAffected(UCHAR) -> bool;
	virtual auto canBeAffectedByArrow(class MobEffectInstance*) -> bool;
	virtual auto onEffectAdded(class MobEffectInstance*) -> void;
	virtual auto onEffectUpdated(class MobEffectInstance*) -> void;
	virtual auto onEffectRemoved(class MobEffectInstance*) -> void;
	virtual auto canObstructSpawningAndBlockPlacement(void) -> bool;
public:
	virtual auto getAnimationComponent(void) -> class AnimationComponent*;
	virtual auto openContainerComponent(class Player*) -> void;
public:
	virtual auto swing(void) -> void;
public:
	virtual auto useItem(class ItemStackBase*, enum ItemUseMethod, bool) -> void;
public:
	virtual auto hasOutputSignal(unsigned __int8) -> bool;
	virtual auto getOutputSignal(void) -> __int64;
public:
	virtual auto getDebugText(std::vector<std::string>&) -> void;
public:
	virtual auto getMapDecorationRotation(void) -> float;
	virtual auto getPassengerYRotation(Actor*) -> float;
public:
	virtual auto isWorldBuilder(void) -> bool;
	virtual auto isCreative(void) -> bool;
	virtual auto isAdventure(void) -> bool;
	virtual auto isSurvival(void) -> bool;
	virtual auto isSpectator(void) -> bool;
	virtual auto isAttackableGamemode(void) -> bool;
public:
	virtual auto add(class ItemStack*) -> bool;
	virtual auto drop(class ItemStack*, bool) -> bool;
public:
	virtual auto getInteraction(class Player*, class ActorInteraction*, Vec3<float>*) -> bool;
public:
	virtual auto canDestroyBlock(Block*) -> bool;
	virtual auto setAuxValue(int) -> void;
public:
	virtual auto setSize(float, float) -> void;
public:
	virtual auto onOrphan(void) -> void;
	virtual auto wobble(void) -> void;
	virtual auto wasHurt(void) -> bool;
public:
	virtual auto startSpinAttack(void) -> void;
	virtual auto stopSpinAttack(void) -> void;
	virtual auto setDamageNearbyMobs(bool) -> void;
public:
	virtual auto renderDebugServerState(class Options*) -> void;
public:
	virtual auto reloadLootTable(void) -> void;
	virtual auto reloadLootTable(class EquipmentTableDefinition*) -> void;
public:
	virtual auto getDeletionDelayTimeSeconds(void) -> __int64;
public:
	virtual auto kill(void) -> void;
	virtual auto die(class ActorDamageSource*) -> void;
public:
	virtual auto shouldDropDeathLoot(void) -> bool;
	virtual auto shouldTick(void) -> bool;
public:
	virtual auto applySnapshot(class EntityContext*, class EntityContext*) -> void;
	virtual auto getNextStep(float) -> float;
public:
	virtual auto getLootTable(void) -> class LootTable*;
public:
	virtual auto interpolatorTick(void) -> void;
};

enum ActorType {

	/* Drops */

	item = 64,
	xp_orb = 69,

	/* Blocks */

	tnt = 65,
	falling_block = 66,
	moving_block = 67,

	/* Immobile and projectiles */

	armor_stand = 61,
	xp_bottle = 68,
	eye_of_ender_signal = 70,
	ender_crystal = 71,
	fireworks_rocket = 72,
	thrown_trident = 73,
	shulker_bullet = 76,
	fishing_hook = 77,
	dragon_fireball = 79,
	arrow = 80,
	snowball = 81,
	egg = 82,
	painting = 83,
	minecart = 84,
	fireball = 85,
	splash_potion = 86,
	ender_pearl = 87,
	leash_knot = 88,
	wither_skull = 89,
	boat = 90,
	wither_skull_dangerous = 91,
	lightning_bolt = 93,
	small_fireball = 94,
	area_effect_cloud = 95,
	hopper_minecart = 96,
	tnt_minecart = 97,
	chest_minecart = 98,
	command_block_minecart = 100,
	lingering_potion = 101,
	llama_spit = 102,
	evocation_fang = 103,
	ice_bomb = 106,
	balloon = 107,
	chest_boat = 218,

	/* Hostile mobs */

	zombie = 32,
	creeper = 33,
	skeleton = 34,
	spider = 35,
	zombie_pigman = 36,
	slime = 37,
	enderman = 38,
	silverfish = 39,
	cave_spider = 40,
	ghast = 41,
	magma_cube = 42,
	blaze = 43,
	zombie_villager = 44,
	witch = 45,
	stray = 46,
	husk = 47,
	wither_skeleton = 48,
	guardian = 49,
	elder_guardian = 50,
	wither = 52,
	ender_dragon = 53,
	shulker = 54,
	endermite = 55,
	vindicator = 57,
	phantom = 58,
	ravager = 59,
	evocation_illager = 104,
	vex = 105,
	drowned = 110,
	pillager = 114,
	zombie_villager_v2 = 116,
	piglin = 123,
	hoglin = 124,
	zoglin = 126,
	piglin_brute = 127,
	warden = 131,

	/* Passive and neutral mobs */

	chicken = 10,
	cow = 11,
	pig = 12,
	sheep = 13,
	wolf = 14,
	villager = 15,
	mooshroom = 16,
	squid = 17,
	rabbit = 18,
	bat = 19,
	iron_golem = 20,
	snow_golem = 21,
	ocelot = 22,
	horse = 23,
	donkey = 24,
	mule = 25,
	skeleton_horse = 26,
	zombie_horse = 27,
	polar_bear = 28,
	llama = 29,
	parrot = 30,
	dolphin = 31,
	turtle = 74,
	cat = 75,
	pufferfish = 108,
	salmon = 109,
	tropicalfish = 111,
	cod = 112,
	panda = 113,
	villager_v2 = 115,
	wandering_trader = 118,
	fox = 121,
	bee = 122,
	strider = 125,
	goat = 128,
	frog = 132,
	tadpole = 133,
	allay = 134,

	/* Other */

	player = 63,
	shield = 117,

	/* Unused */

	elder_guardian_ghost = 120,

	/* Education Edition */

	npc = 51,
	agent = 56,
	tripod_camera = 62,
	chalkboard = 78

};