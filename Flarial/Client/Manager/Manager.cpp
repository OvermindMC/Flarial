#include "Manager.h"

/* Module Includes */

#include "Category/Module/Modules/Misc/TestMod.h"

/* Manager Constructor */

Manager::Manager(Client* c) {

	this->client = c;

	for (auto I = (int)CategoryType::RENDER; I <= (int)CategoryType::MISC; I++) {

		auto type = (CategoryType)I;
		this->categories[type] = new Category(this, type);

	};

	new TestMod(this);

	for (;;) {

		for (auto [type, category] : this->categories)
			category->tick();

	};

};