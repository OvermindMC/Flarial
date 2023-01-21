#pragma once
#include "../../Hook.h"
#include "../../../Category/Module/Module.h"

class HookRenderCtx : public Hook<void, void*, MinecraftUIRenderContext*> {
public:
	HookRenderCtx(Manager* mgr) : Hook<void, void*, MinecraftUIRenderContext*>(mgr, "RenderContext", Mem::findSig("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 54 24 ? 4C"),
		[&](void* p1, MinecraftUIRenderContext* ctx) {
			
			auto _this = this->manager->getHook<void, void*, MinecraftUIRenderContext*>("RenderContext");
			
			if(_this) {

				auto instance = ctx->instance;
				auto player = (instance != nullptr ? instance->getPlayer() : nullptr);
				auto level = (player != nullptr ? player->getLevel() : nullptr);

				if (level) {

					for (auto [runtimeId, entity] : this->manager->entityMap) {

						if (level->getRuntimeEntity(runtimeId, false) == nullptr)
							this->manager->entityMap.erase(runtimeId);

					};

				}
				else {

					this->manager->entityMap.clear();

				};

				for (auto [type, category] : this->manager->categories) {

					for (auto mod : category->modules) {

						if (mod->isEnabled)
							mod->callEvent<RenderCtxEvent>(RenderCtxEvent{ ctx });

					};

				};

				_this->_Func(p1, ctx);

			};
			
		}
	){

		auto sig = Mem::findSig("48 8D 05 ? ? ? ? 48 89 01 48 89 51 ? 4C 89 41 ? 48 8B 02");

		if (sig) {

			auto offset = *(int*)(sig + 3);
			auto VTable = (uintptr_t**)(sig + offset + 7);

			new Hook<__int64, MinecraftUIRenderContext*, TexturePath*, Vec2<float>*, Vec2<float>*, Vec2<float>*, Vec2<float>*>(this->manager, "DrawImage", (uintptr_t)VTable[7],
			[&](MinecraftUIRenderContext* ctx, TexturePath* pathPtr, Vec2<float>* imagePos, Vec2<float>* imageDimensions, Vec2<float>* uvPos, Vec2<float>* uvSize){
				
				auto _this = this->manager->getHook<__int64, MinecraftUIRenderContext*, TexturePath*, Vec2<float>*, Vec2<float>*, Vec2<float>*, Vec2<float>*>("DrawImage");

				if(std::string(pathPtr->filePath->path).rfind("textures/ui/title") != std::string::npos) {

					auto instance = ctx->instance;
					auto font = (instance != nullptr ? instance->getMcGame()->mcFont : nullptr);
					auto screenRes = (instance != nullptr ? instance->getGuiData()->screenResC : Vec2<float>());

					auto color = Color(255.f, 255.f, 255.f);
					auto text = this->manager->client->name;

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
};