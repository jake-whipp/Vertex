#pragma once
#include "RegisteredModule.h"
#include "ModuleManager.h"

namespace Vertex::Menu::Modules
{
	class NoclipModule : public RegisteredModule<NoclipModule>
	{
	public:
		NoclipModule();
		~NoclipModule();

		void onEnable() override;
		void onDisable() override;
	};
}
