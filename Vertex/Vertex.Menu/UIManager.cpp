#include "pch.h"
#include "UIManager.h"
#include "ModuleManager.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Vertex::Menu
{
	UIManager::UIManager()
	{
		m_hGameWindow = nullptr;
		m_hGameWindowProc = nullptr;

		m_menuShown = false;
		m_state = UIManagerState::Uninitialised;
		m_pOriginalSwapBuffers = nullptr;
		m_pSwapBuffersHookPoint = nullptr;

		m_hOpenGL = NULL;
	}

	UIManager::~UIManager()
	{

	}

	void UIManager::initialise()
	{
		if (m_state != UIManagerState::Uninitialised)
		{
			return;
		}

		m_state = UIManagerState::BuildingHooks;
		while (!m_pSwapBuffersHookPoint)
		{
			// TODO: - deal w. magic literals
			//		 - and probably polling is bad
			if (m_hOpenGL == NULL)
			{
				m_hOpenGL = GetModuleHandle(L"opengl32.dll");
			}

			if (m_hOpenGL != NULL && m_pSwapBuffersHookPoint == nullptr)
			{
				m_pSwapBuffersHookPoint = (Hooks::wglSwapBuffers_t)GetProcAddress(m_hOpenGL, "wglSwapBuffers");
			}

			Sleep(10);
		}

		HookService& hookService = HookService::getInstance();
		hookService.CreateHook((LPVOID)m_pSwapBuffersHookPoint, &wglSwapBuffersHook, (LPVOID*)&m_pOriginalSwapBuffers);
		hookService.EnableHook((LPVOID)m_pSwapBuffersHookPoint);

		m_state = UIManagerState::BuildingImGui;
	}

	LRESULT CALLBACK UIManager::wndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		UIManager& uiManager = UIManager::getInstance();

		// Toggle the overlay using the delete key (TODO: magic again!!!!)
		if (uMsg == WM_KEYDOWN && wParam == VK_DELETE) {
			// Refresh module info
			uiManager.m_moduleInformation = ModuleManager::getInstance().GetAllModules();

			uiManager.m_menuShown = !uiManager.m_menuShown;
			return false;
		}

		// If the overlay is shown, direct input to the overlay only
		if (uiManager.m_menuShown) {
			CallWindowProc(ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);
			return true;
		}

		// Otherwise, call the game's wndProc function (as gui not open)
		return CallWindowProc(uiManager.m_hGameWindowProc, hWnd, uMsg, wParam, lParam);
	}

	BOOL WINAPI UIManager::wglSwapBuffersHook(HDC hdc)
	{
		UIManager& uiManager = UIManager::getInstance();

		if (uiManager.m_state == UIManagerState::BuildingImGui)
		{
			// Get GD's window from the handle to the device context
			uiManager.m_hGameWindow = WindowFromDC(hdc);

			// Overwrite GD's wndProc function
			uiManager.m_hGameWindowProc = (WNDPROC)SetWindowLongPtr(uiManager.m_hGameWindow, GWLP_WNDPROC, (LONG_PTR)wndProcHook);

			// Init ImGui
			ImGui_ImplWin32_EnableDpiAwareness();
			ImGui::CreateContext();

			// Scaling
			float dpi_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

			ImGuiStyle& style = ImGui::GetStyle();
			style.ScaleAllSizes(dpi_scale);

			ImGuiIO& io = ImGui::GetIO();
			ImFontConfig cfg;
			cfg.RasterizerDensity = dpi_scale;
			cfg.SizePixels = std::floor(16.0f * dpi_scale);
			
			// TODO: use project resources
			io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", cfg.SizePixels, &cfg);

			// Colour
			ImGui::StyleColorsDark();

			ImGui_ImplWin32_Init(uiManager.m_hGameWindow);
			ImGui_ImplOpenGL3_Init();

			uiManager.m_state = UIManagerState::Complete;
		}

		// potentially save opengl state here 
		// (so next frame renders properly without interception from imgui)

		if (uiManager.m_menuShown)
		{
			uiManager.draw();
		}

		// potentially restore opengl state here

		return uiManager.m_pOriginalSwapBuffers(hdc);
	}

	void UIManager::draw()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Demo UI (for now..............)
		ImGui::ShowDemoWindow();

		// Extra UI Code (for now also...........)
		ImGui::SetNextWindowSize(ImVec2(400, 400));
		ImGui::Begin("GD Menu", NULL, ImGuiWindowFlags_None);

		for (auto& module : m_moduleInformation)
		{
			if (ImGui::Checkbox(module.name.c_str(), &module.enabled))
			{
				ModuleManager::getInstance().toggleModule(module.name);
			}

			ImGui::SetItemTooltip(module.description.c_str(), module.name.c_str());
		}

		ImGui::End();

		ImGui::Render();

		// Draw the overlay
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
	