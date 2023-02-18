#pragma once
#include "../../Module.h"

class ClickGui : public Module {
public:
	int currWindow = 0;
public:
	Module* moduleConfig = nullptr;
public:
	ClickGui(Manager* mgr) : Module(mgr->categories[CategoryType::RENDER], "ClickGui", "Interact with modules via mouse", VK_INSERT) {

		registerEvent<ModuleEvent>([&](ModuleEvent* args) {

			if(args->isTicking)
				return;

			auto instance = MC::getClientInstance();
			
			if(args->isEnabled) {

				instance->releaseMouse();

			}
			else {

				auto currScreenName = instance->getTopScreenName();

				if (currScreenName.rfind("hud_screen") != std::string::npos)
					instance->grabMouse();

			};

		});

		registerEvent<MouseEvent>([&](MouseEvent* args) {

			*args->cancel = true;
								  
		});

		registerEvent<KeyEvent>([&](KeyEvent* args) {

			auto key = args->key;
			auto isDown = args->isDown;

			if (key == VK_ESCAPE && isDown)
				this->isEnabled = false;

			*args->cancel = true;

		});
		
		registerEvent<ImGuiEvent>([&](ImGuiEvent* args) {

			auto instance = MC::getClientInstance();
			auto currScreenName = instance->getTopScreenName();

			if (currScreenName.rfind("hud_screen") == std::string::npos) {

				this->isEnabled = false;
				return;

			};

			instance->releaseMouse();

			ImVec2 displaySize = ImGui::GetIO().DisplaySize;
			ImVec2 windowSize = ImVec2(displaySize.x / 2, displaySize.y / 2);
			ImGui::SetNextWindowPos(ImVec2((displaySize.x - windowSize.x) / 2, (displaySize.y - windowSize.y) / 2));
			ImGui::SetNextWindowSize(windowSize);
			ImGui::SetNextWindowContentSize(ImVec2(windowSize.x, windowSize.y + 100.f));
			
			auto mgr = this->category->manager;
			auto categories = std::vector<std::string>();

			for (auto [type, category] : mgr->categories)
				categories.push_back(category->getName());

			ImVec4 window_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
			window_color.w = 0.6f;

			ImGui::PushStyleColor(ImGuiCol_WindowBg, window_color);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));

			if (ImGui::Begin(std::string(std::string(ICON_FA_ATOM) + " " + mgr->client->name).c_str(), NULL, ImGuiWindowFlags_NoCollapse)) {
				
				auto font = *ImGui::GetFont();
				font.Scale = 1.f;

				ImGui::PushFont(&font);
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 6.f));
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.23, 0.78f, 0.51, 1.0f));

				/* Navbar Contents */

				if (ImGui::Button("Modules")) {

					currWindow = 0;

				}; ImGui::SameLine();

				if (ImGui::Button("Friends")) {

					currWindow = 1;

				}; ImGui::SameLine();

				if (ImGui::Button("Settings")) {

					currWindow = 2;

				}; ImGui::SameLine();
				
				ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (ImGui::CalcTextSize("X").x * 4.f) - ImGui::GetStyle().WindowPadding.x);
				
				if(ImGui::Button(" X "))
					this->isEnabled = false;

				/* End Of Navbar Contents */

				/* Windows */

				if (ImGui::BeginChild("Module Configs", ImVec2(120.f, 0.f), true)) {

					auto font = *ImGui::GetFont();
					font.Scale = .6f;

					ImGui::PushFont(&font);
					
					if (moduleConfig)
						moduleConfig->callEvent<ClickGuiModConfigEvent>(ClickGuiModConfigEvent{});

					ImGui::PopFont();

					ImGui::EndChild();

				}; ImGui::SameLine();

				if (ImGui::BeginChild("Current Window", ImVec2(ImGui::GetWindowWidth() - 170.f, 0.f), true)) {

					if (currWindow == 0) {

						auto modules = std::vector<Module*>();

						for (auto [type, category] : mgr->categories) {

							for (auto mod : category->modules)
								modules.push_back(mod);

						};

						auto font = *ImGui::GetFont();
						font.Scale = 1.f;

						ImGui::PushFont(&font);

						auto I = 0;
						for (auto mod : modules) {

							I++;

							if (ImGui::BeginChild(std::string("Card-" + mod->name).c_str(), ImVec2((ImGui::GetWindowWidth() - 30.f) / 3.f, 100.f), true)) {

								ImGui::Text(std::string(std::string(ICON_FA_STAR) + " " + mod->name).c_str());

								ImGui::Spacing();
								ImGui::Spacing();
								
								if (ImGui::Button(ICON_FA_COG))
									moduleConfig = mod;

								ImGui::SameLine();

								bool isEnabled = mod->isEnabled;

								if(!isEnabled)
									ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.89, 0.31f, 0.23, 1.0f));
								
								if (ImGui::Button(mod->isEnabled ? "Enabled" : "Disabled"))
									mod->isEnabled = !mod->isEnabled;

								if (!isEnabled)
									ImGui::PopStyleColor();
								
								ImGui::EndChild();

							};
							
							if (I == 3)
								I = 0;
							else
								ImGui::SameLine();

						};

						ImGui::PopFont();

					};
					
					ImGui::EndChild();

				};

				/* End Of Windows */

				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();
				ImGui::PopFont();
				ImGui::End();

			};

			ImGui::PopStyleVar();
			ImGui::PopStyleColor();

		});

	};
};