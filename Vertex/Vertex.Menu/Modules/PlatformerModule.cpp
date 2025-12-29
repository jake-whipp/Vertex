#include "pch.h"
#include "PlatformerModule.h"

namespace Vertex::Menu::Modules
{
	static bool _register = []() {
		PlatformerModule::registerSelf();
		return true;
		}();

	PlatformerModule::PlatformerModule() : RegisteredModule(
		"Platformer Mode",
		"Forces the gamemode to become a platformer level.",
		Category::Miscellaneous)
	{
		// Create hook via HookService
	}

	PlatformerModule::~PlatformerModule()
	{
		// Disable the hook if necessary
		if (m_enabled)
		{
			toggle();
		}

		// Remove the hook
	}

	void PlatformerModule::onEnable()
	{
		// Enable hook via HookService
	}

	void PlatformerModule::onDisable()
	{
		// Disable hook via HookService
	}
}
