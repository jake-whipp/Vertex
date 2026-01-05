#include "pch.h"
#include "HookService.h"

namespace Vertex::Menu
{
	uintptr_t HookService::GetGDBase()
	{
		// NULL specifies no module (aka GD itself)
		return m_pGeometryDashBase;
	}

	MH_STATUS HookService::CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal)
	{
		MH_STATUS result = MH_CreateHook(pTarget, pDetour, ppOriginal);
		
		if (result == MH_OK)
		{
			m_activeHooks.emplace_back(pTarget);
		}

		return result;
	}

	MH_STATUS HookService::RemoveHook(LPVOID pTarget)
	{
		MH_STATUS result = MH_RemoveHook(pTarget);

		if (result == MH_OK)
		{
			// See https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			m_activeHooks.erase(
				std::remove(m_activeHooks.begin(), m_activeHooks.end(), pTarget), m_activeHooks.end());
		}

		return result;
	}

	MH_STATUS HookService::EnableHook(LPVOID pTarget)
	{
		return MH_EnableHook(pTarget);
	}

	MH_STATUS HookService::DisableHook(LPVOID pTarget)
	{
		return MH_DisableHook(pTarget);
	}

	HookService::HookService()
	{
		m_pGeometryDashBase = (uintptr_t)GetModuleHandleA(NULL);

		// Init. MH
		if (MH_Initialize() != MH_OK)
		{
			// TODO:	Log error
			//			Throw exception
		}
	}

	HookService::~HookService()
	{
		std::vector<LPVOID> hooks = m_activeHooks;
		for (const auto& hook : hooks)
		{
			RemoveHook(hook);
		}

		// Shutdown MH
		MH_Uninitialize();
	}
}
