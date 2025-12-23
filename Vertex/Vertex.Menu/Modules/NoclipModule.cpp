#include "pch.h"
#include "NoclipModule.h"

namespace Vertex::Menu::Modules
{
	static bool _register = []() {
		NoclipModule::registerSelf();
		return true;
		}();

	NoclipModule::NoclipModule() : RegisteredModule("Noclip")
	{
		// Create hook via MH
	}

	NoclipModule::~NoclipModule()
	{
		// Disable the hook if necessary
		if (m_enabled)
		{
			toggle();
		}

		// Remove the hook
	}

	void NoclipModule::onEnable()
	{
		// Enable hook via MH
	}

	void NoclipModule::onDisable()
	{
		// Disable hook via MH
	}
}
