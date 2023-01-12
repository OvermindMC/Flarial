#include "Category.h"
#include "Module/Module.h"

Category::Category(Manager* mgr, CategoryType t) {
	this->manager = mgr;
	this->type = t;
};

auto Category::tick(void) -> void {

	for (auto mod : this->modules)
		mod->tick();

};

auto Category::getName(void) -> std::string {

	switch (this->type) {

		case CategoryType::RENDER:
			return "Render";
		break;

		case CategoryType::COMBAT:
			return "Combat";
		break;

		case CategoryType::PLAYER:
			return "Player";
		break;

		case CategoryType::EXPLOIT:
			return "Exploit";
		break;

		case CategoryType::WORLD:
			return "World";
		break;

		case CategoryType::MOVE:
			return "Move";
		break;

		case CategoryType::MISC:
			return "Misc";
		break;

	};

	return "";

};