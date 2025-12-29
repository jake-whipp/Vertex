#pragma once
#include "HookService.h"
#include "UI/ModuleView.h"

namespace Vertex::Menu
{
	enum class UIManagerState
	{
		Uninitialised,
		BuildingHooks,
		BuildingImGui,
		Complete,
		Failed
	};

	class UIManager
	{
	public:
		static UIManager& getInstance()
		{
			static UIManager instance;
			return instance;
		}

		void initialise();

	private:
		UIManager();
		~UIManager();

		HMODULE m_hOpenGL;
		HWND m_hGameWindow;
		WNDPROC m_hGameWindowProc;
		static LRESULT CALLBACK wndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static BOOL WINAPI wglSwapBuffersHook(HDC hdc);
		Hooks::wglSwapBuffers_t m_pSwapBuffersHookPoint;
		Hooks::wglSwapBuffers_t m_pOriginalSwapBuffers;

		void draw();

		std::vector<ModuleView> m_moduleInformation;

		bool m_menuShown;
		UIManagerState m_state;
	};
}
