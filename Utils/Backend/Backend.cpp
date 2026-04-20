#include "Headers/Menu/MenuSetup.h"

Backend::presentVariable originalPresent;
Backend::presentVariable hookedPresent;


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static bool init = false;

Backend RunBackend;


void INIT_CONSOLE()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitleA("Logs");
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	// support ANSI escape sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
	system("chcp 65001");
	system("cls");
}

bool Backend::DirectXPresentHook()
{
	ZeroMemory(&m_gSwapChainDescription, sizeof(m_gSwapChainDescription));

	m_gSwapChainDescription.BufferCount = 2;
	m_gSwapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_gSwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_gSwapChainDescription.OutputWindow = GetForegroundWindow();
	m_gSwapChainDescription.SampleDesc.Count = 1;
	m_gSwapChainDescription.Windowed = TRUE;
	m_gSwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT createDevice = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, m_gFeatureLevels, 2, D3D11_SDK_VERSION, &m_gSwapChainDescription, &m_gSwapChain, &m_gDevice, nullptr, nullptr);
		
	if (FAILED(createDevice)) 
		return false; // dont return false make an endless cycle (only if u wanna go cpu boom) 

	void** DX11Vtable = *reinterpret_cast<void***>(m_gSwapChain);

	UnloadDevices(false); // don't need to reset mainrendertargetview
	hookedPresent = (Backend::presentVariable)DX11Vtable[8]; // 8. virtual table is present

	return true;
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (RunBackend.m_bOpenMenu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	if (RunBackend.m_bOpenMenu) {
		//return true;
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return CallWindowProc(RunBackend.m_goriginalWndProc, hWnd, uMsg, wParam, lParam);
}

void Backend::LoadImGui(HWND window, ID3D11Device* device, ID3D11DeviceContext* context)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	ImGui::StyleColorsDark();

	{ // INIT FONTS
		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0xE000, 0xE226, // icons
			0,
		};

		ImFontConfig icons_config;
		ImFontConfig font_config;

		font_config.GlyphRanges = ranges;

		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		icons_config.MergeMode = true; icons_config.PixelSnapH = true; icons_config.OversampleH = 8; icons_config.OversampleV = 8; icons_config.GlyphMinAdvanceX = 15.0f;

		ImGui::Fonts::MuseoSansMain = io.Fonts->AddFontFromMemoryTTF((void*)logoFont, sizeof(logoFont), 14.f, &font_config);
		ImGui::Fonts::MuseoSans500 = io.Fonts->AddFontFromMemoryTTF((void*)logoFont, sizeof(logoFont), 18.f, &font_config);
		ImGui::Fonts::FontAwesome6 = io.Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data, fa_solid_900_compressed_size, 15.0f, &icons_config, icons_ranges);
	}

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, context);
}

bool ReceivedNotificationInfo = false;
void Backend::DrawImGui(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetview)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	ImGui::PushFont(ImGui::Fonts::MuseoSans500);

	if (!ReceivedNotificationInfo) {
		ImGui::InsertNotification({ ImGuiToastType::Info, 15000, OBF("NOTE: If the Game freezes, go to the Command\nPrompt and press CTRL + C (ONLY ONCE)") });
		ReceivedNotificationInfo = true;
	}

	ImGui::SetNextWindowSize(ImVec2(800, 600));

	if (m_bOpenMenu)
	{
		ImGui::GetIO().MouseDrawCursor = RunBackend.m_bOpenMenu;
		ClipCursor(NULL);

		if (vars::iwefdefefkje == OBF(""))
		{
			if (vars::ujirngjenujfgrgjgikr) {
				if (vars::UserData[1] != OBF("empty") && vars::UserData[2] != OBF("empty")) {
					if (wdkdfjf::wsjmdwkdiemfjerf(vars::UserData[1], vars::UserData[2], irjfejfrnhgnrhjfjrgjrng(kmedwdkefjfedmefj()), OBF("wdwdwfeefw")) == OBF("Fail___") && vars::eifjeuifjeuf == OBF("___Success")) {
						printf(OBF("\nLogging in...\n"));
						vars::iwefdefefkje = OBF("dednmwidrf");
						vars::wijdiwduefuejfieufiw = true;
						vars::ijenujefnjerfnehnfef = true; // remember me
						printf(OBF("Logged in!\n\n"));
					}
				}
				vars::ujirngjenujfgrgjgikr = false;
			}

			ImGui::Begin(OBF("##ikwfiwjkfieghnuwf"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDecoration);
			{
				auto pos = ImVec2{};
				pos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y); //drag

				// add frame glow effect
				ImGui::GetBackgroundDrawList()->AddShadowRect(ImGui::GetWindowPos(), ImVec2(pos.x + 250 + 450, pos.y + 480), ImColor(Menu::MenuBGFGlowColor[0], Menu::MenuBGFGlowColor[1], Menu::MenuBGFGlowColor[2], Menu::MenuBGFGlowColor[3]), Menu::MenuBGFrameThickness, ImVec2(0, 0), 1, 10);

				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 132, pos.y + 480), ImColor(15, 13, 15), 10, ImDrawFlags_RoundCornersLeft);
				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 132, pos.y), ImVec2(pos.x + 132 + 568, pos.y + 480), ImColor(20, 18, 20), 10, ImDrawFlags_RoundCornersRight);
				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 132 + 10, pos.y + 10), ImVec2(pos.x + 132 + 10 + 548, pos.y + 10 + 58), ImColor(15, 13, 15), 4);

				ImGui::SetWindowFontScale(2.0f);
				ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 132 + 20, pos.y + 10 + 10), ImColor(116, 102, 149), ICON_FA_ID_CARD);
				ImGui::SetWindowFontScale(1.0f);

				ImGui::SetWindowFontScale(1.2f);

				// Void
				ImGui::GetWindowDrawList()->AddShadowRect(ImVec2(pos.x + ImGui::CalcTextSize("Void").x + 15, pos.y + 35), ImVec2(pos.x + ImGui::CalcTextSize("Void").x + 30, pos.y + 35), ImColor(255, 255, 255, 120), 40, ImVec2(0, 0), 1, 10);
				ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 38, pos.y + 25), ImColor(255, 255, 255), "Void");
				// PG
				ImGui::GetWindowDrawList()->AddShadowRect(ImVec2(pos.x + ImGui::CalcTextSize("VoidPG").x + 15, pos.y + 35), ImVec2(pos.x + ImGui::CalcTextSize("VoidPG").x + 30, pos.y + 35), ImColor(157, 131, 216, 120), 40, ImVec2(0, 0), 1, 10);
				ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 38 + ImGui::CalcTextSize("Void").x, pos.y + 25), ImColor(157, 131, 216), "PG");

				ImGui::SetWindowFontScale(1.0f);

				ImGui::SetCursorPos(Menu::MenuChildPos1);
				ImGui::CustomBeginChild(OBF("wdfoiwjdiwejfujwndfiwhnfu"), OBF("Login"), ImVec2(548, 400)); // LOGIN CHILD
				{
					ImGui::SameLine(); ImGui::CustomInputText(OBF("krkejmfikemfjkemfefge"), OBF("Username"), vars::rijfjerifkefef, std::size(vars::rijfjerifkefef));
					ImGui::NewLine(); ImGui::SameLine(); ImGui::CustomInputText(OBF("eikgrejnejnmfgeungefg"), OBF("Password"), vars::erifjejkfjrgrg, std::size(vars::erifjejkfjrgrg), { 0,0 }, ImGuiInputTextFlags_Password);
					ImGui::Checkbox(OBF("Remember me"), &vars::ijenujefnjerfnehnfef);
					if (ImGui::CustomButton(OBF("ejfjweifnerujifgzhuef"), OBF("Login"))) {

						if (wdkdfjf::wsjmdwkdiemfjerf(irjfejfrnhgnrhjfjrgjrng(vars::rijfjerifkefef), irjfejfrnhgnrhjfjrgjrng(vars::erifjejkfjrgrg), irjfejfrnhgnrhjfjrgjrng(kmedwdkefjfedmefj()), OBF("wdwdwfeefw")) == OBF("Fail___") && vars::eifjeuifjeuf == OBF("___Success")) {
							vars::iwefdefefkje = OBF("dednmwidrf");
							vars::wijdiwduefuejfieufiw = true;
							if (vars::ijenujefnjerfnehnfef) {
								vars::UserData(FormatString(OBF("%s\n%s"), irjfejfrnhgnrhjfjrgjrng(vars::rijfjerifkefef).c_str(), irjfejfrnhgnrhjfjrgjrng(vars::erifjejkfjrgrg).c_str()));
								vars::UserData.Apply();
							}
						}

					}
					ImGui::SameLine(); if (ImGui::CustomButton(OBF("wfikedjmikefjwnbgfh"), OBF("Discord"))) system(OBF("start https://discord.gg/voidpg"));
					ImGui::NewLine(); ImGui::SameLine(); ImGui::Text(OBF("%s"), vars::orfmgkemfkrg.c_str());
				}
				ImGui::EndChild();
			}
			ImGui::End();

		}
		else if (vars::iwefdefefkje == OBF("dednmwidrf")) {
			DrawMainMenu();
			if (Menu::BlackBackground) context->ClearRenderTargetView(targetview, Menu::ClearBGColor);
		}
		else Backend::UnloadImGui();
	}

	ImGui::RenderNotifications();
	ImGui::PopFont();

	ImGui::EndFrame();
	ImGui::Render();
	context->OMSetRenderTargets(1, &targetview, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void Backend::UnloadDevices(bool renderTargetViewReset)
{
	if(renderTargetViewReset) if (m_gMainRenderTargetView) { m_gMainRenderTargetView->Release(); m_gMainRenderTargetView = nullptr; }
	if (m_gPointerContext) { m_gPointerContext->Release(); m_gPointerContext = nullptr; }
	if (m_gDevice) { m_gDevice->Release(); m_gDevice = nullptr; }
	SetWindowLongPtr(m_gWindow, GWLP_WNDPROC, (LONG_PTR)(m_goriginalWndProc));
}

static long __stdcall PresentHook(IDXGISwapChain* pointerSwapChain, UINT sync, UINT flags)
{
	if (!init) {
		if (SUCCEEDED(pointerSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&RunBackend.m_gDevice))) // check if device working 
		{
			RunBackend.m_gDevice->GetImmediateContext(&RunBackend.m_gPointerContext); // need context immediately!!
			pointerSwapChain->GetDesc(&RunBackend.m_gPresentHookSwapChain); // welp we need the presenthook's outputwindow so it's actually ours o_o
			RunBackend.m_gWindow = RunBackend.m_gPresentHookSwapChain.OutputWindow;

			pointerSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&RunBackend.m_gPointerBackBuffer); // getting back buffer
			if (RunBackend.m_gPointerBackBuffer != nullptr) RunBackend.m_gDevice->CreateRenderTargetView(RunBackend.m_gPointerBackBuffer, NULL, &RunBackend.m_gMainRenderTargetView); // from backbuffer to our monitor
			RunBackend.m_gPointerBackBuffer->Release(); // don't need this shit anymore, but please comeback the next injection

			RunBackend.LoadImGui(RunBackend.m_gWindow, RunBackend.m_gDevice, RunBackend.m_gPointerContext); // load imgui!!!
			RunBackend.m_goriginalWndProc = (WNDPROC)SetWindowLongPtr(RunBackend.m_gWindow, GWLP_WNDPROC, (LONG_PTR)WndProc); // i think u need this

			init = true;
		}
		else
			return originalPresent(pointerSwapChain, sync, flags); // returning original too
	}

	if (Utils::keyPressed(VK_F11) || Utils::keyPressed(VK_RMENU) || Utils::keyPressed(VK_RCONTROL) || Utils::keyPressed(VK_INSERT)) {
		RunBackend.m_bOpenMenu = !RunBackend.m_bOpenMenu;
		ImGui::GetIO().MouseDrawCursor = RunBackend.m_bOpenMenu;
		ClipCursor(NULL);
	}


	RunBackend.DrawImGui(RunBackend.m_gPointerContext, RunBackend.m_gMainRenderTargetView); // draw imgui every time
	return originalPresent(pointerSwapChain, sync, flags); // return the original so no stack corruption
}

bool Backend::Load()
{
	INIT_CONSOLE();
	printf(OBF("Initializing...\n"));
	auto start = std::chrono::high_resolution_clock::now();

#ifndef DEVMODE
	vars::oeifjkeokfiegj = ednferjnfejfnehjfnehfn(httpSx::weikfnwejifnmeujfgnehfgew(edikeiofe(OBF("aHR0cHM6Ly9hcGkuaXBpZnkub3Jn")), httpSx::efkmefkeoifmejkfgn), 2); // https://api.ipify.org base64 encoded
#endif

	printf(OBF("Step 1/6 done\n"));

#ifndef DEVMODE
	wdkdfjf::ierjfowejkfgierfi(); // Security Check
	HookTracer::DetectHooks(false);
#endif

	printf(OBF("Step 2/6 done\n"));

	RunBackend.DirectXPresentHook();
	MH_Initialize();

	MH_CreateHook(reinterpret_cast<void**>(hookedPresent), &PresentHook, reinterpret_cast<void**>(&originalPresent)); 
	MH_EnableHook(hookedPresent);

	printf(OBF("Step 3/6 done\n"));

	while (!Il2CppUtils::INIT()) Sleep(1);
	BNM::INIT();
	INIT_CLASSES();

	printf(OBF("Step 4/6 done\n"));

	Pointers();
	Hooks();

	printf(OBF("Step 5/6 done\n"));

	WS::GameVersion = efergegeg()->ToString().c_str();
	INIT_LISTS();
	/*
#ifndef DEVMODE
	if (ekfmefjerhfgrehg(httpSx::weikfnwejifnmeujfgnehfgew(OBF("https://raw.githubusercontent.com/SxitxmaKurosaki/SibidiDopDop/refs/heads/main/efefsgers"), httpSx::efkmefkeoifmejkfgn), WS::GameVersion) != OBF("Sifejmfgrlwfkmekgehgdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergwefegerhgodkbnrbmolekfekgrghodefgjret402446eofgkm462ergwfefgrehrhdkbnrbmwpfkerifejmfgrofkrfgodwef101201kaswsowpfker02446eofgkm462ergkijhdkbnrbmoegjr02446eofgkm462ergkeefolergoegjrwfefgrehrhdontwwdrfhelpdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergekgerjgdwef101201kaswsoifejmfgrwfefgrehrh010009wfe"))
	{
		exit(200);
	}
#endif
	*/	
	// FOR FIXING CRASH ISSUES
	//if (ekfmefjerhfgrehg(httpSx::weikfnwejifnmeujfgnehfgew(OBF("https://raw.githubusercontent.com/SxitxmaKurosaki/SibidiDopDop/refs/heads/main/testSkibidi"), httpSx::efkmefkeoifmejkfgn), OBF("test")) != OBF("Sifejmfgrlwfkmekgehgdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergwefegerhgodkbnrbmolekfekgrghodefgjret402446eofgkm462ergwfefgrehrhdkbnrbmwpfkerifejmfgrofkrfgodwef101201kaswsowpfker02446eofgkm462ergkijhdkbnrbmoegjr02446eofgkm462ergkeefolergoegjrwfefgrehrhdontwwdrfhelpdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergekgerjgdwef101201kaswsoifejmfgrwfefgrehrh010009wfe"))
	//{
	//	exit(200);
	//}

	/*
	if (ekfmefjerhfgrehg(httpSx::weikfnwejifnmeujfgnehfgew<ojson>(OBF("https://leminare.xyz/api/versions"), httpSx::efkmefkeoifmejkfgn, { OBF("User-Agent: myModMenu") }), WS::GameVersion) != OBF("Sifejmfgrlwfkmekgehgdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergwefegerhgodkbnrbmolekfekgrghodefgjret402446eofgkm462ergwfefgrehrhdkbnrbmwpfkerifejmfgrofkrfgodwef101201kaswsowpfker02446eofgkm462ergkijhdkbnrbmoegjr02446eofgkm462ergkeefolergoegjrwfefgrehrhdontwwdrfhelpdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergekgerjgdwef101201kaswsoifejmfgrwfefgrehrh010009wfe"))
	{
		exit(200);
	}
	*/

	printf(OBF("Step 6/6 done\n"));
	
	WS::Slots::INIT(); // make sure this shit is only being called when you're NOT in the loading screen, else you will get big proplams

	UnityThread* ok_ = new UnityThread;
	UNITY_CREATE_THREAD(ok_, SexyJews, []() {
		std::this_thread::sleep_for(std::chrono::milliseconds(333));
		if (vars::SecureLvl) {
			ImGui::InsertNotification({ ImGuiToastType::Warning, 8000, OBF("SECURING LEVEL...") });
			std::this_thread::sleep_for(std::chrono::seconds(8));
			vars::CallInUnityThread.emplace_back([]() {defkjfjeref(il2cpp_object_new(GET_CLASS(___skibidi::______aa____)), 0, 6549877, nullptr, nullptr); });
			ImGui::InsertNotification({ ImGuiToastType::Success, 2000, OBF("Level Secured!") });
			vars::SecureLvl = false;
		}
	});

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	printf(OBF("Initialization took %f seconds!\n\n"), elapsed.count());

	printf(OBF("NOTE: If the Game freezes, go to the Command Prompt and press CTRL + C (ONLY ONCE)\nIt's most likely because you touched the Command Prompt (what you're reading here right now)\n\n"));
	
	return true;
}

void Backend::Unload()
{
	UnloadImGui(); // imgui unload
	UnloadDevices(true); // unloading all devices
}

/*
DWORD WINAPI Backend::AuthActivity(LPVOID lpReserved)
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(20));
		if (vars::wijdiwduefuejfieufiw) {
			// check the license validation all 20 seconds
		}
	}
}
*/

#define __DETECT__(modulename) (void*)GetProcAddress(oejoekfi, OBF(modulename))
DWORD WINAPI Backend::DetectHooks(LPVOID lpReserved)
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(4));

		HMODULE oejoekfi = GetModuleHandleA(OBF("kernel32.dll"));

		DetectHook(__DETECT__("VirtualProtect"));
		HookTracer::DetectHooks(false);
	}
}