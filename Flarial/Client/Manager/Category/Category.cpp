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