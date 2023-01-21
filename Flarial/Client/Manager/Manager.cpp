#include "Manager.h"
#include "Hook/Hook.h"
#include "Category/Category.h"

/* Module Includes */

#include "Category/Module/Modules/Render/TabGui.h"
#include "Category/Module/Modules/Misc/TestMod.h"

/* Manager Constructor */

Manager::Manager(Client* c) {

	this->client = c;

	for (auto I = (int)CategoryType::RENDER; I <= (int)CategoryType::MISC; I++) {

		auto type = (CategoryType)I;
		this->categories[type] = new Category(this, type);

		Utils::debugOutput("Initialized Category: " + this->categories[type]->getName());

	};

	new TabGui(this);
	new TestMod(this);

	MH_Initialize();

	{ /* Draw Image */

		auto sig = Mem::findSig("48 8D 05 ? ? ? ? 48 89 01 48 89 51 ? 4C 89 41 ? 48 8B 02");

		if (sig) {

			auto offset = *(int*)(sig + 3);
			auto VTable = (uintptr_t**)(sig + offset + 7);

			new Hook<__int64, MinecraftUIRenderContext*, TexturePath*, Vec2<float>*, Vec2<float>*, Vec2<float>*, Vec2<float>*>(this, "DrawImage", (uintptr_t)VTable[7],
			[&](MinecraftUIRenderContext* ctx, TexturePath* pathPtr, Vec2<float>* imagePos, Vec2<float>* imageDimensions, Vec2<float>* uvPos, Vec2<float>* uvSize){
				
				auto _this = getHook<__int64, MinecraftUIRenderContext*, TexturePath*, Vec2<float>*, Vec2<float>*, Vec2<float>*, Vec2<float>*>("DrawImage");

				if(std::string(pathPtr->filePath->path).rfind("textures/ui/title") != std::string::npos) {

					auto instance = ctx->instance;
					auto font = (instance != nullptr ? instance->getMcGame()->mcFont : nullptr);
					auto screenRes = (instance != nullptr ? instance->getGuiData()->screenResC : Vec2<float>());

					auto color = Color(255.f, 255.f, 255.f);
					auto text = this->client->name;

					auto fontSize = 2.f;
					auto len = ctx->getTextLength(font, &text, fontSize, false);

					auto textPos = Vec2<float>(screenRes.x - (screenRes.x / 2.f), imagePos->y);
					textPos.x -= (len / 2.f);

					ctx->fillRectangle(Rect(textPos.x - fontSize, (textPos.y + fontSize) + (fontSize * 10.f), (textPos.x + fontSize) + len, (textPos.y + fontSize) + (fontSize * 10.f) + 1.f), color);
					ctx->drawText(font, text, Vec2<float>(textPos.x, textPos.y + 1.f), color, fontSize);
					ctx->flushText(0.f);

					return (__int64)NULL;

				};
				
				return _this->_Func(ctx, pathPtr, imagePos, imageDimensions, uvPos, uvSize);
				
				
			});

		};


	};

	{ /* Entity */

		auto sig = Mem::findSig("48 8D 05 ? ? ? ? 48 89 01 48 8B 05 ? ? ? ? FF 15 ? ? ? ? 4C 8B C0");

		if (sig) {

			auto offset = *(int*)(sig + 3);
			auto VTable = (uintptr_t**)(sig + offset + 7);

			new Hook<void, Actor*>(this, "ActorBaseTick", (uintptr_t)VTable[51], [&](Actor* entity) {

				auto _this = getHook<void, Actor*>("ActorBaseTick");
				
				if(_this) {

					this->entityMap[entity->runtimeId] = entity;

					_this->_Func(entity);

				};

			});

		};

	};

	{ /* GameMode */

		auto sig = Mem::findSig("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 8B 89 ? ? ? ? 48 85 C9 74 11 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C9 74 17");

		if (sig) {

			auto offset = *(int*)(sig + 3);
			auto VTable = (uintptr_t**)(sig + offset + 7);

			new Hook<void, GameMode*>(this, "GameModeTick", (uintptr_t)VTable[8], [&](GameMode* GM) {

				auto _this = getHook<void, GameMode*>("GameModeTick");

				if(_this) {

					for (auto [type, category] : this->categories) {

						for (auto mod : category->modules) {

							if (mod->isEnabled)
								mod->callEvent<GameModeTickEvent>(GameModeTickEvent{ GM });

						};
					};

					_this->_Func(GM);

				};

			});

		};

	};

	{ /* Render Context */

		new Hook<void, uintptr_t*, MinecraftUIRenderContext*>(this, "RenderContext", Mem::findSig("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 54 24 ? 4C"),
			[&](uintptr_t* p1, MinecraftUIRenderContext* ctx) {

				auto _this = getHook<void, uintptr_t*, MinecraftUIRenderContext*>("RenderContext");
		
				if(_this) {

					for (auto [type, category] : this->categories) {

						for (auto mod : category->modules) {

							if (mod->isEnabled)
								mod->callEvent<RenderCtxEvent>(RenderCtxEvent{ ctx });

						};
					};

					_this->_Func(p1, ctx);

				};

			}
		);
	};

	{ /* Key Hook */

		new Hook<void, uint64_t, bool>(this, "KeyHook", Mem::findSig("48 ? ? 48 ? ? ? 4C 8D 05 ? ? ? ? 89"),
			[&](uint64_t key, bool isDown) {

				auto cancel = false;
				auto _this = getHook<void, uint64_t, bool>("KeyHook");
			
				if(_this) {

					this->keyMap[key] = isDown;

					for (auto [type, category] : this->categories) {

						for (auto mod : category->modules) {

							if (mod->isEnabled)
								mod->callEvent<KeyEvent>(KeyEvent{ key, isDown, &cancel });

						};

					};

					if(!cancel)
						_this->_Func(key, isDown);

				};

			}
		);

	};

	{ /* LoopbackPacketSender */

		new Hook<void, LoopbackPacketSender*, Packet*>(this, "LoopbackSend", Mem::findSig("48 89 5C 24 08 57 48 83 EC 20 48 8B D9 48 8B FA 48 8B 49 10"),
		[&](LoopbackPacketSender* lp, Packet* packet){
			
				auto _this = getHook<void, LoopbackPacketSender*, Packet*>("LoopbackSend");
				auto cancel = false;

				if(_this) {

					for (auto [ type, category ] : this->categories) {

						for (auto mod : category->modules) {

							if (mod->isEnabled)
								mod->callEvent<PacketEvent>(PacketEvent{ &cancel, packet });

						};

					};

					if (!cancel)
						_this->_Func(lp, packet);

				};
			
			}
		);

	};

	for (;;) {

		for (auto [type, category] : this->categories)
			category->tick();

		Sleep(1);

	};

};

template<typename T, typename... TArgs>
auto Manager::getHook(const char* name) -> Hook<T, TArgs...>* {

	auto res = (Hook<T, TArgs...>*)nullptr;

	for (auto hookPtr : this->hooks) {

		auto hook = (Hook<T, TArgs...>*)hookPtr;

		if (hook->name == name) {
			res = hook;
			break;
		};

	};

	return res;

};