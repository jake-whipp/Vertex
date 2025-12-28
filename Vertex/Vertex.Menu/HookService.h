#pragma once
#include <vector>

namespace Vertex::Menu
{
	namespace Hooks {
		typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC hdc);
	}

	class HookService
	{
	public:
		static HookService& getInstance()
		{
			static HookService instance;
			return instance;
		}


		// MH-related wrappers:

		MH_STATUS CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);
		MH_STATUS RemoveHook(LPVOID pTarget);

		MH_STATUS EnableHook(LPVOID pTarget);
		MH_STATUS DisableHook(LPVOID pTarget);

	private:
		HookService();
		~HookService();

		std::vector<LPVOID> m_activeHooks;
	};
}
