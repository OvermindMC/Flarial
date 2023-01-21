#include "Module.h"

Module::Module(Category* c, std::string n) {
	this->category = c;
	this->name = n;

	this->category->modules.push_back(this);
};

auto Module::tick(void) -> void {

	if (this->wasEnabled != this->isEnabled) {

		this->wasEnabled = this->isEnabled;
		this->callEvent<ModuleEvent>(ModuleEvent{ this->isEnabled, false });

	};

	if(this->isEnabled)
		this->callEvent<ModuleEvent>(ModuleEvent{ this->isEnabled, true });

};