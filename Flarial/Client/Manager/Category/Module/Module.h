#pragma once
#include "../Category.h"
#include "../../Event/Event.h"

struct ModuleEventArgs {
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
    auto forEachEntity(std::function<void(Actor*, bool)> fn) -> void {

        for (auto [runtimeId, entity] : this->category->manager->entityMap) {
            auto isRegular = (entity->getEntityTypeId() == ActorType::player || entity->isPassive() || entity->isHostile());
            fn(entity, isRegular);
        };

    };
};