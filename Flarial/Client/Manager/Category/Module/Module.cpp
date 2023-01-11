#include "Module.h"

Module::Module(Category* c) {
	this->category = c;
	this->category->modules.push_back(this);
};

auto Module::tick(void) -> void {

	if (this->wasEnabled != this->isEnabled) {

		this->wasEnabled = this->isEnabled;

		//

	};

};