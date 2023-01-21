#pragma once
#include "../../Module.h"

class TabGui : public Module {
public:
	bool selectedCategory = false, selectedMod = false;
	size_t currCategory = 0, currModule = 0;
public:
	float fontSize = 1.f, alpha = 0.f;
	int renderFrame = 0;
public:
	float selCatAnimOff = 0.f, selModAnimOff = 0.f;
	float animModifier = .7f;
public:
	std::vector<std::pair<CategoryType, Category*>> categories;
	std::vector<Module*> modules;
public:
	TabGui(Manager* mgr) : Module(mgr->categories[CategoryType::RENDER], "TabGui") {

		this->isEnabled = true;

		registerEvent<RenderCtxEvent>([&](RenderCtxEvent* args) {

			this->renderFrame++;
			
			if(this->renderFrame >= 2)
				this->renderFrame = 0;
			else
				return;

			auto instance = args->ctx->instance;
			auto mcGame = (instance != nullptr ? instance->getMcGame() : nullptr);
			auto font = (mcGame != nullptr ? mcGame->mcFont : nullptr);

			if (instance == nullptr || font == nullptr)
				return;

			Utils::reachOff(&alpha, (mcGame->canUseKeys ? 1.f : 0.f), 0.02f);
			
			if (alpha <= 0.f)
				return;
			
			auto mgr = this->category->manager;
			auto client = mgr->client;

			auto startPos = Vec2<float>(10.f, 10.f);

			if (this->categories.empty()) {

				this->categories = std::vector<std::pair<CategoryType, Category*>>(mgr->categories.begin(), mgr->categories.end());
				std::sort(categories.begin(), categories.end(), [&](const std::pair<CategoryType, Category*>& p1, const std::pair<CategoryType, Category*>& p2) {
					
					auto nameA = p1.second->getName();
					auto nameB = p2.second->getName();
					
					return args->ctx->getTextLength(font, &nameA, fontSize, false) > args->ctx->getTextLength(font, &nameB, fontSize, false);

				});

			};

			this->modules = this->categories[this->currCategory].second->modules;

			auto fCatName = categories.front().second->getName();
			auto categoriesW = args->ctx->getTextLength(font, &fCatName, fontSize, false);
			auto categoryRect = Rect(startPos.x - 2.f, startPos.x - 2.f, (startPos.x + 2.f) + categoriesW, startPos.y + (categories.size() * ((fontSize * 10.f)) + ((fontSize * 10.f) + 2.f)));

			args->ctx->fillRectangle(categoryRect, Color(60.f, 70.f, 80.f, alpha - .2f));
			args->ctx->fillRectangle(Rect(categoryRect.x, categoryRect.y, categoryRect.z, startPos.y + (fontSize * 10.f)), Color(30.f, 70.f, 80.f, alpha - .1f));
			args->ctx->drawText(font, client->name, startPos, Color(40.f, 105.f, 160.f, alpha), 1.f);
			args->ctx->flushText(0.f);

			auto I = 0;
			for (auto [_, category] : categories) {

				auto textPos = Vec2<float>(startPos.x, (startPos.y + (fontSize * 10.f)) + (I * (fontSize * 10.f)));

				if (this->selectedCategory && this->currCategory == I) {

					if (this->selCatAnimOff <= 0.f)
						this->selCatAnimOff = textPos.x + 1.f;

					Utils::reachOff(&this->selCatAnimOff, categoryRect.z - 1.f, this->animModifier);

					auto yOff = textPos.y + (fontSize * 10.f);
					args->ctx->fillRectangle(Rect(textPos.x - 1.f, yOff - 1.f, this->selCatAnimOff, yOff), Color(50.f, 125.f, 168.f, alpha - .2f));

				};

				args->ctx->drawText(font, category->getName(), textPos, Color(255.f, 255.f, 255.f, alpha), fontSize);
				I++;

			};

			if (this->selectedCategory) {

				if (!modules.empty()) {

					std::sort(modules.begin(), modules.end(), [&](Module* modA, Module* modB) {

						return args->ctx->getTextLength(font, &modA->name, fontSize, false) > args->ctx->getTextLength(font, &modB->name, fontSize, false);

					});

					auto len = args->ctx->getTextLength(font, &modules.back()->name, fontSize, false);
					auto rect = Rect(categoryRect.z, ((categoryRect.y + 2.f) + (fontSize * 10.f)) + (currCategory * (fontSize * 10.f)), (categoryRect.z + 4.f) + len, ((categoryRect.y + 2.f) + (fontSize * 10.f)) + (currCategory * (fontSize * 10.f)) + (modules.size() * (fontSize * 10.f)) + 2.f);

					args->ctx->fillRectangle(rect, Color(60.f, 70.f, 80.f, alpha - .2f));

					I = 0;
					for (auto mod : modules) {

						auto textPos = Vec2<float>(rect.x + 2.f, (rect.y + (I * (fontSize * 10.f))));

						if (this->selectedMod && this->currModule == I) {

							if (this->selModAnimOff <= 0.f)
								this->selModAnimOff = textPos.x + 1.f;

							Utils::reachOff(&this->selModAnimOff, rect.z - 1.f, this->animModifier);

							auto yOff = textPos.y + (fontSize * 10.f);
							args->ctx->fillRectangle(Rect(textPos.x - 1.f, yOff - 1.f, this->selModAnimOff, yOff), Color(50.f, 125.f, 168.f, alpha - .2f));

						};

						args->ctx->drawText(font, mod->name, textPos, mod->isEnabled ? Color(40.f, 160.f, 160.f, alpha) : Color(255.f, 255.f, 255.f, alpha), fontSize);
						I++;

					};

				};

			};

			args->ctx->flushText(0.f);

		});

		registerEvent<KeyEvent>([&](KeyEvent* args) {

			if(alpha <= 0.f)
				return;
			
			auto key = args->key;
			auto isDown = args->isDown;

			if (key != VK_UP && key != VK_DOWN && key != VK_LEFT && key != VK_RIGHT)
				return;

			*args->cancel = true;

			if (!isDown)
				return;

			auto category = this->categories[this->currCategory].second;

			switch (key) {

				case VK_RIGHT:

					if (!this->selectedCategory) {
						this->selectedCategory = true;
					}
					else {

						auto mod = (!this->modules.empty() ? this->modules.at(this->currModule) : nullptr);

						if (!this->selectedMod)
							this->selectedMod = true;
						else
							if (mod != nullptr)
								mod->isEnabled = !mod->isEnabled;
					};

				break;

				case VK_LEFT:

					if (this->selectedMod) {
						this->selModAnimOff = 0.f;
						this->selectedMod = false;
						this->currModule = 0;
					}
					else if (this->selectedCategory) {
						this->selCatAnimOff = 0.f;
						this->selectedCategory = false;
					};

				break;

				case VK_UP:

					if (this->selectedCategory && !this->selectedMod) {

						if (this->currCategory <= 0)
							this->currCategory = this->categories.size();

						this->currCategory--;
						this->selCatAnimOff = 0.f;

					}
					else if (this->selectedMod) {

						if (this->currModule <= 0)
							this->currModule = this->modules.size();

						this->currModule--;
						this->selModAnimOff = 0.f;

					};


				break;

				case VK_DOWN:

					if (this->selectedCategory && !this->selectedMod) {

						this->currCategory++;
						this->selCatAnimOff = 0.f;

						if (this->currCategory >= this->categories.size())
							this->currCategory = 0;

					}
					else if (this->selectedMod) {

						this->currModule++;
						this->selModAnimOff = 0.f;

						if (this->currModule >= this->modules.size())
							this->currModule = 0;

					};

				break;

			};

		});

	};
};