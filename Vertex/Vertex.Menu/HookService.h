#pragma once
#include <vector>

namespace Vertex::Menu
{
	class HookService
	{
	public:
		static HookService& getInstance()
		{
			static HookService instance;
			return instance;
		}

		uintptr_t GetGDBase();

		// MH-related wrappers:

		MH_STATUS CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);
		MH_STATUS RemoveHook(LPVOID pTarget);

		MH_STATUS EnableHook(LPVOID pTarget);
		MH_STATUS DisableHook(LPVOID pTarget);

	private:
		HookService();
		~HookService();

		std::vector<LPVOID> m_activeHooks;

		uintptr_t m_pGeometryDashBase;
	};
}
