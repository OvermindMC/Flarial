#include "Actor.h"

auto Actor::getLevel(void) -> Level* {

	return *(Level**)((uintptr_t)(this) + 0x310);

};

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

auto Actor::isHostile(void) -> bool {

	auto type = this->getEntityTypeId();

	switch (type) {

	case ActorType::zombie:
		return true;
		break;

	case ActorType::creeper:
		return true;
		break;

	case ActorType::skeleton:
		return true;
		break;

	case ActorType::spider:
		return true;
		break;

	case ActorType::zombie_pigman:
		return true;
		break;

	case ActorType::slime:
		return true;
		break;

	case ActorType::enderman:
		return true;
		break;

	case ActorType::silverfish:
		return true;
		break;

	case ActorType::cave_spider:
		return true;
		break;

	case ActorType::ghast:
		return true;
		break;

	case ActorType::magma_cube:
		return true;
		break;

	case ActorType::blaze:
		return true;
		break;

	case ActorType::zombie_villager:
		return true;
		break;

	case ActorType::witch:
		return true;
		break;

	case ActorType::stray:
		return true;
		break;

	case ActorType::husk:
		return true;
		break;

	case ActorType::wither_skeleton:
		return true;
		break;

	case ActorType::guardian:
		return true;
		break;

	case ActorType::elder_guardian:
		return true;
		break;

	case ActorType::wither:
		return true;
		break;

	case ActorType::ender_dragon:
		return true;
		break;

	case ActorType::shulker:
		return true;
		break;

	case ActorType::endermite:
		return true;
		break;

	case ActorType::vindicator:
		return true;
		break;

	case ActorType::phantom:
		return true;
		break;

	case ActorType::ravager:
		return true;
		break;

	case ActorType::evocation_illager:
		return true;
		break;

	case ActorType::vex:
		return true;
		break;

	case ActorType::drowned:
		return true;
		break;

	case ActorType::pillager:
		return true;
		break;

	case ActorType::zombie_villager_v2:
		return true;
		break;

	case ActorType::piglin:
		return true;
		break;

	case ActorType::hoglin:
		return true;
		break;

	case ActorType::piglin_brute:
		return true;
		break;

	case ActorType::warden:
		return true;
		break;

	default:
		return false;
	};

	return false;

};

auto Actor::isPassive(void) -> bool {

	auto type = this->getEntityTypeId();

	switch (type) {

	case ActorType::chicken:
		return true;
		break;

	case ActorType::cow:
		return true;
		break;

	case ActorType::pig:
		return true;
		break;

	case ActorType::sheep:
		return true;
		break;

	case ActorType::wolf:
		return true;
		break;

	case ActorType::villager:
		return true;
		break;

	case ActorType::mooshroom:
		return true;
		break;

	case ActorType::squid:
		return true;
		break;

	case ActorType::rabbit:
		return true;
		break;

	case ActorType::bat:
		return true;
		break;

	case ActorType::iron_golem:
		return true;
		break;

	case ActorType::snow_golem:
		return true;
		break;

	case ActorType::ocelot:
		return true;
		break;

	case ActorType::horse:
		return true;
		break;

	case ActorType::donkey:
		return true;
		break;

	case ActorType::mule:
		return true;
		break;

	case ActorType::skeleton_horse:
		return true;
		break;

	case ActorType::zombie_horse:
		return true;
		break;

	case ActorType::polar_bear:
		return true;
		break;

	case ActorType::llama:
		return true;
		break;

	case ActorType::parrot:
		return true;
		break;

	case ActorType::dolphin:
		return true;
		break;

	case ActorType::turtle:
		return true;
		break;

	case ActorType::cat:
		return true;
		break;

	case ActorType::pufferfish:
		return true;
		break;

	case ActorType::salmon:
		return true;
		break;

	case ActorType::tropicalfish:
		return true;
		break;

	case ActorType::cod:
		return true;
		break;

	case ActorType::panda:
		return true;
		break;

	case ActorType::villager_v2:
		return true;
		break;

	case ActorType::wandering_trader:
		return true;
		break;

	case ActorType::fox:
		return true;
		break;

	case ActorType::bee:
		return true;
		break;

	case ActorType::strider:
		return true;
		break;

	case ActorType::goat:
		return true;
		break;

	case ActorType::frog:
		return true;
		break;

	case ActorType::tadpole:
		return true;
		break;

	case ActorType::allay:
		return true;
		break;

	default:
		return false;

	};

	return false;

};