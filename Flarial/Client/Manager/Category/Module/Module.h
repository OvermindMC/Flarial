#pragma once
#include "../Category.h"
#include "../../Event/Event.h"

struct ModuleEvent {
    bool isEnabled, isTicking;
};

class Module {
public:
	Category* category = nullptr;
	std::vector<__int64*> events;
public:
	std::string name;
public:
	bool wasEnabled = false, isEnabled = false;
public:
	Module(Category*, std::string);
public:
	auto tick(void) -> void;
public:
    template<typename T>
    auto registerEvent(std::function<void(T*)> fn) {
        auto ev = new Event<T>();

        ev->type = typeid(T).name();
        ev->callback = fn;

        this->events.push_back((__int64*)ev);
    };
public:
    template<typename T>
    auto callEvent(T args) {
        for (auto ptr : this->events) {
            auto ev = (Event<T>*)ptr;
            
            if (typeid(T).name() == ev->type)
                ev->callback(&args);
        };
    };
public:
    auto forEachEntity(std::function<void(Actor*, bool)> fn, std::function<bool(Actor*, Actor*)> cmp = std::function<bool(Actor*, Actor*)>()) -> void {

        auto entityMap = this->category->manager->entityMap;
        auto entities = std::vector<std::pair<uint64_t, Actor*>>(entityMap.begin(), entityMap.end());

        if(cmp)
            std::sort(entities.begin(), entities.end(), [&](const std::pair<uint64_t, Actor*> first, const std::pair<uint64_t, Actor*> second) {
                return cmp(first.second, second.second);
            });
        
        for (auto [runtimeId, entity] : entities) {
            auto isRegular = (entity->getEntityTypeId() == ActorType::player || entity->isPassive() || entity->isHostile());
            fn(entity, isRegular);
        };

    };
};