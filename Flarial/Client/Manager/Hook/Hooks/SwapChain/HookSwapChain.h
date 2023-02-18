#pragma once
#include "../../Hook.h"

struct FrameContext {
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12Resource* main_render_target_resource = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;
};

class HookSwapChain : public Hook<void> {
public:
	ID3D11Device* d3d11Device = nullptr;
	ID3D12Device* d3d12Device = nullptr;
public:
	ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiRender = nullptr;
	ID3D12DescriptorHeap* d3d12DescriptorHeapBackBuffers = nullptr;
	ID3D12GraphicsCommandList* d3d12CommandList = nullptr;
	ID3D12CommandQueue* d3d12CommandQueue = nullptr;
	ID3D12CommandAllocator* allocator = nullptr;
public:
	uint64_t buffersCounts = -1;
	FrameContext* frameContext = nullptr;
public:
	bool contextInitialized = false;
public:
	HookSwapChain(Manager* mgr) : Hook<void>(mgr) {

		IDXGISwapChain* pSwapChain;

		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = NULL;
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = L"SwapChain Window";
		windowClass.hIconSm = NULL;

		::RegisterClassEx(&windowClass);

		HWND window = ::CreateWindow(windowClass.lpszClassName, L"DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);
		
		HMODULE libDXGI;
		HMODULE libD3D12;
		
		if ((libDXGI = ::GetModuleHandle(L"dxgi.dll")) == NULL || (libD3D12 = ::GetModuleHandle(L"d3d12.dll")) == NULL) {
			
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			
			Utils::debugOutput("d2d12.dll or dxgi.dll is missing in the current process!");
			return;
		};

		void* CreateDXGIFactory;
		if ((CreateDXGIFactory = ::GetProcAddress(libDXGI, "CreateDXGIFactory")) == NULL) {
			
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			
			Utils::debugOutput("Failed to get DXGIFactory process");
			return;
		};

		IDXGIFactory* factory;
		if (((long(__stdcall*)(const IID&, void**))(CreateDXGIFactory))(__uuidof(IDXGIFactory), (void**)&factory) < 0) {
			
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			
			Utils::debugOutput("Failed create DXGIFactory");
			return;

		};

		IDXGIAdapter* adapter;
		if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND) {

			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

			Utils::debugOutput("Failed create Adapter");
			return;

		};

		void* D3D12CreateDevice;
		if ((D3D12CreateDevice = ::GetProcAddress(libD3D12, "D3D12CreateDevice")) == NULL) {

			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

			Utils::debugOutput("Failed get D3D12CreateDevice process");
			return;

		};

		ID3D12Device* device;
		if (((long(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(D3D12CreateDevice))(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&device) < 0) {

			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

			Utils::debugOutput("Failed create ID3D12Device");
			return;

		};

		D3D12_COMMAND_QUEUE_DESC queueDesc;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = 0;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 0;

		ID3D12CommandQueue* commandQueue;
		if (device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&commandQueue) < 0) {

			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

			Utils::debugOutput("Failed create Command Queue");
			return;

		};

		ID3D12CommandAllocator* commandAllocator;
		if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&commandAllocator) < 0) {

			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

			Utils::debugOutput("Failed create Command Allocator");
			return;

		};

		ID3D12GraphicsCommandList* commandList;
		if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&commandList) < 0) {

			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

			Utils::debugOutput("Failed create Command List");
			return;

		};

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.OutputWindow = window;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* swapChain;
		if (factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain) < 0) {
			
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			
			Utils::debugOutput("Failed create SwapChain");
			return;


		};

		auto sc_methodsTable = (uint64_t*)::calloc(150, sizeof(uint64_t));
		
		::memcpy(sc_methodsTable, *(uint64_t**)device, 44 * sizeof(uint64_t));
		::memcpy(sc_methodsTable + 44, *(uint64_t**)commandQueue, 19 * sizeof(uint64_t));
		::memcpy(sc_methodsTable + 44 + 19, *(uint64_t**)commandAllocator, 9 * sizeof(uint64_t));
		::memcpy(sc_methodsTable + 44 + 19 + 9, *(uint64_t**)commandList, 60 * sizeof(uint64_t));
		::memcpy(sc_methodsTable + 44 + 19 + 9 + 60, *(uint64_t**)swapChain, 18 * sizeof(uint64_t));

		//Utils::debugOutput("Successfully stored SwapChain VTable methods!");

		device->Release();
		device = NULL;

		commandQueue->Release();
		commandQueue = NULL;

		commandAllocator->Release();
		commandAllocator = NULL;

		commandList->Release();
		commandList = NULL;

		swapChain->Release();
		swapChain = NULL;

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		new Hook<HRESULT, IDXGISwapChain3*, UINT, UINT>(mgr, "SwapChainPresent", (uintptr_t)sc_methodsTable[140],
			[&](IDXGISwapChain3* ppSwapChain, UINT syncInterval, UINT flags){
				
				auto _this = this->manager->getHook<HRESULT, IDXGISwapChain3*, UINT, UINT>("SwapChainPresent");
				auto window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");

				auto onRndr = [&]() {

					auto instance = MC::getClientInstance();
					auto player = (instance != nullptr ? instance->getPlayer() : nullptr);

					auto level = player->getLevel();
					auto entmap = this->manager->entityMap;

					if (level) {

						for (auto [runtimeId, entity] : entmap) {

							auto ptr = level->getRuntimeEntity(runtimeId, false);

							std::ostringstream o;
							o << std::hex << ptr << std::endl;

							Utils::debugOutput(std::to_string(runtimeId) + ", " + o.str());

						};

					};

					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
					ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
					ImGui::RenderNotifications();
					ImGui::PopStyleVar(1);
					ImGui::PopStyleColor(1);

					auto draw = ImGui::GetOverlayDrawList();

					draw->AddCircleFilled(ImGui::GetIO().MousePos, 2.f, ImColor(255.f, 255.f, 255.f, 1.f), 30);
					draw->AddCircleFilled(ImGui::GetIO().MousePosPrev, 2.f, ImColor(255.f, 255.f, 255.f, 1.f), 30);

					for (auto [type, category] : this->manager->categories) {

						for (auto mod : category->modules) {

							if (mod->isEnabled)
								mod->callEvent<ImGuiEvent>({  });

						};

					};

				};
				
				if(d3d11Device == nullptr && d3d12Device == nullptr) {

					if (SUCCEEDED(ppSwapChain->GetDevice(IID_PPV_ARGS(&d3d12Device)))) {

						Utils::debugOutput("SwapChain initializing for D3D12");

					}
					else if (SUCCEEDED(ppSwapChain->GetDevice(IID_PPV_ARGS(&d3d11Device)))) {

						Utils::debugOutput("SwapChain initializing for D3D11");

					};

				};

				if (d3d11Device) {

					if (!contextInitialized) {

						ImGui::CreateContext();
						ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(ProductSans_compressed_data, ProductSans_compressed_size, 18.f);
						ImGui::MergeIconsWithLatestFont(18.f, false);

						contextInitialized = true;

					};

					ID3D11RenderTargetView* mainRenderTargetView = nullptr;
					ID3D11DeviceContext* ppContext = nullptr;
					ID3D11Texture2D* pBackBuffer = nullptr;

					d3d11Device->GetImmediateContext(&ppContext);

					if (ppContext) {

						if (SUCCEEDED(ppSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer))) {

							if (SUCCEEDED(d3d11Device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView))) {

								ImGui_ImplWin32_Init(window);
								ImGui_ImplDX11_Init(d3d11Device, ppContext);

								ImGui_ImplDX11_NewFrame();
								ImGui_ImplWin32_NewFrame();
								ImGui::NewFrame();

								onRndr();

								ImGui::EndFrame();
								ImGui::Render();

								ppContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
								ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

							};

						};

					};

					if (pBackBuffer)
						pBackBuffer->Release();
					
					if(mainRenderTargetView)
						mainRenderTargetView->Release();

					return _this->_Func(ppSwapChain, syncInterval, flags);

				}
				else if (d3d12Device) {

					if (d3d12CommandQueue) {

						if (!contextInitialized) {

							ImGui::CreateContext();
							ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(ProductSans_compressed_data, ProductSans_compressed_size, 20.f);
							ImGui::MergeIconsWithLatestFont(18.f, false);

						};

						DXGI_SWAP_CHAIN_DESC sdesc;
						ppSwapChain->GetDesc(&sdesc);
						sdesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
						sdesc.OutputWindow = window;
						sdesc.Windowed = ((GetWindowLongPtr(window, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

						buffersCounts = sdesc.BufferCount;
						frameContext = new FrameContext[buffersCounts];

						D3D12_DESCRIPTOR_HEAP_DESC descriptorImGuiRender = {};
						descriptorImGuiRender.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
						descriptorImGuiRender.NumDescriptors = buffersCounts;
						descriptorImGuiRender.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

						if (d3d12DescriptorHeapImGuiRender|| SUCCEEDED(d3d12Device->CreateDescriptorHeap(&descriptorImGuiRender, IID_PPV_ARGS(&d3d12DescriptorHeapImGuiRender)))) {

							if (SUCCEEDED(d3d12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator)))) {

								for (size_t i = 0; i < buffersCounts; i++) {
									frameContext[i].commandAllocator = allocator;
								};

								if (SUCCEEDED(d3d12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, NULL, IID_PPV_ARGS(&d3d12CommandList)))) {

									D3D12_DESCRIPTOR_HEAP_DESC descriptorBackBuffers;
									descriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
									descriptorBackBuffers.NumDescriptors = buffersCounts;
									descriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
									descriptorBackBuffers.NodeMask = 1;

									if (SUCCEEDED(d3d12Device->CreateDescriptorHeap(&descriptorBackBuffers, IID_PPV_ARGS(&d3d12DescriptorHeapBackBuffers)))) {

										const auto rtvDescriptorSize = d3d12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
										D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = d3d12DescriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();

										for (size_t i = 0; i < buffersCounts; i++) {
											ID3D12Resource* pBackBuffer = nullptr;

											frameContext[i].main_render_target_descriptor = rtvHandle;
											ppSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
											d3d12Device->CreateRenderTargetView(pBackBuffer, nullptr, rtvHandle);
											frameContext[i].main_render_target_resource = pBackBuffer;
											rtvHandle.ptr += rtvDescriptorSize;

											pBackBuffer->Release();
										};

										if (!contextInitialized) {

											ImGui_ImplWin32_Init(window);
											ImGui_ImplDX12_Init(d3d12Device, buffersCounts,
												DXGI_FORMAT_R8G8B8A8_UNORM, d3d12DescriptorHeapImGuiRender,
												d3d12DescriptorHeapImGuiRender->GetCPUDescriptorHandleForHeapStart(),
												d3d12DescriptorHeapImGuiRender->GetGPUDescriptorHandleForHeapStart());

											contextInitialized = true;

										};

										ImGui_ImplDX12_NewFrame();
										ImGui_ImplWin32_NewFrame();
										ImGui::NewFrame();

										onRndr();

										FrameContext& currentFrameContext = frameContext[ppSwapChain->GetCurrentBackBufferIndex()];
										currentFrameContext.commandAllocator->Reset();

										D3D12_RESOURCE_BARRIER barrier;
										barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
										barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
										barrier.Transition.pResource = currentFrameContext.main_render_target_resource;
										barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
										barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
										barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

										d3d12CommandList->Reset(currentFrameContext.commandAllocator, nullptr);
										d3d12CommandList->ResourceBarrier(1, &barrier);
										d3d12CommandList->OMSetRenderTargets(1, &currentFrameContext.main_render_target_descriptor, FALSE, nullptr);
										d3d12CommandList->SetDescriptorHeaps(1, &d3d12DescriptorHeapImGuiRender);

										ImGui::EndFrame();
										ImGui::Render();

										ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), d3d12CommandList);

										barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
										barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

										d3d12CommandList->ResourceBarrier(1, &barrier);
										d3d12CommandList->Close();

										d3d12CommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&d3d12CommandList));

									};

								};

							};

						};

					};

				};

				if (allocator)
					allocator->Release();

				if (d3d12CommandList)
					d3d12CommandList->Release();

				if(d3d12DescriptorHeapBackBuffers)
					d3d12DescriptorHeapBackBuffers->Release();

				if (frameContext->commandAllocator)
					frameContext->commandAllocator->Release();

				if (frameContext->main_render_target_resource)
					frameContext->main_render_target_resource->Release();

				delete frameContext;
				
				return _this->_Func(ppSwapChain, syncInterval, flags);
				
		});

		new Hook<void, ID3D12CommandQueue*, UINT, ID3D12CommandList*>(this->manager, "SwapChainCommandQueue", (uintptr_t)sc_methodsTable[54],
			[&](ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists){
				
				auto _this = this->manager->getHook<void, ID3D12CommandQueue*, UINT, ID3D12CommandList*>("SwapChainCommandQueue");
				
				if(!d3d12CommandQueue)
					d3d12CommandQueue = queue;
				
				return _this->_Func(queue, NumCommandLists, ppCommandLists);
				
		});

	};
};