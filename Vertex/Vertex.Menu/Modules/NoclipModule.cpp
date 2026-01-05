#include "pch.h"
#include "NoclipModule.h"
#include "HookService.h"

namespace Vertex::Menu::Modules
{
	static bool _register = []() {
		NoclipModule::registerSelf();
		return true;
		}();

	NoclipModule::NoclipModule() : RegisteredModule(
		"Noclip", 
		"Lets the user move through objects.", 
		Category::Cheat)
	{
		m_blockCollisionOffset = 0x37BC40;
		m_hazardCollisionOffset = 0x39CAF0;
		
		HookService& hookService = HookService::getInstance();

		// Assign fn ptrs
		m_pHazardCollisionHookPoint = (Hooks::gdSpikeCollision_t)(hookService.GetGDBase() + m_hazardCollisionOffset);
		
		// Create hazard hook
		hookService.CreateHook(
			(LPVOID)m_pHazardCollisionHookPoint, 
			&hazardCollisionHook, 
			(LPVOID*)&m_pOriginalHazardCollision
		);

		// TODO Create block hook
	}

	NoclipModule::~NoclipModule()
	{
		// Disable the hook if necessary
		if (m_enabled)
		{
			toggle();
		}

		// TODO Remove the hook
	}

	void NoclipModule::onEnable()
	{
		// Enable hook via HookService

		// gd 00007FF7412A0000 ?

		// geometrydash.exe+0x39CAF0 - Spike collision Fn (e.g. contact with killing object)
		// geometrydash.exe+0x37BC40 - Block collision Fn (e.g can't surmount terrain item at this angle)

		// 00007FF7412F6EBD - Sound FX function

		HookService& hookService = HookService::getInstance();
		hookService.EnableHook((LPVOID)m_pHazardCollisionHookPoint);
	}

	void NoclipModule::onDisable()
	{
		HookService& hookService = HookService::getInstance();
		hookService.DisableHook((LPVOID)m_pHazardCollisionHookPoint);
	}
	
	__int64 __fastcall NoclipModule::hazardCollisionHook()
	{
		// Cancel the fn and disable hazard collision by returning immediately
		return 0;
	}
}
