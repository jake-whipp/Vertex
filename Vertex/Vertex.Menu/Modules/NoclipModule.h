#pragma once
#include "RegisteredModule.h"
#include "ModuleManager.h"

namespace Vertex::Menu::Modules
{
	namespace Hooks 
	{
		typedef __int64(__fastcall* gdSpikeCollision_t)();
	}

	class NoclipModule : public RegisteredModule<NoclipModule>
	{
	public:
		NoclipModule();
		~NoclipModule();

		void onEnable() override;
		void onDisable() override;

		static __int64 __fastcall hazardCollisionHook();

	private:
		uintptr_t m_blockCollisionOffset;
		uintptr_t m_hazardCollisionOffset;
		Hooks::gdSpikeCollision_t m_pHazardCollisionHookPoint;
		Hooks::gdSpikeCollision_t m_pOriginalHazardCollision;
	};
}
