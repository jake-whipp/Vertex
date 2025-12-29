#include "pch.h"
#include "Vertex.h"
#include "HookService.h"
#include "ModuleManager.h"
#include "UIManager.h"

namespace Vertex::Menu
{
	void initialise()
	{
		HookService::getInstance();
		ModuleManager::getInstance();
		UIManager::getInstance().initialise();
	}

	void shutdown()
	{

	}
}
