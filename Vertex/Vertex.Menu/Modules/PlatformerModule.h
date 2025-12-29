#pragma once
#include "RegisteredModule.h"
#include "ModuleManager.h"

namespace Vertex::Menu
{
	class PlatformerModule : public RegisteredModule<PlatformerModule>
	{
	public:
		PlatformerModule();
		~PlatformerModule();

		void onEnable() override;
		void onDisable() override;
	};
}
