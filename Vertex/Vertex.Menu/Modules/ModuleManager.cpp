#include "pch.h"
#include "ModuleManager.h"

Vertex::Menu::ModuleManager::ModuleManager()
{
	if (MH_Initialize() != MH_OK)
	{
		// TODO:	Log error
		//			Throw exception
	}
}

Vertex::Menu::ModuleManager::~ModuleManager()
{
	// Disable all active modules to safely restore game instructions
	for (auto const& [name, pModule] : m_modules)
	{
		if (pModule->isEnabled())
		{
			pModule->onDisable();
		}
	}

	// Clear the map
	m_modules.clear();

	// Shut down MinHook
	MH_Uninitialize();
}

void Vertex::Menu::ModuleManager::registerModule(std::unique_ptr<IModule> module)
{
	// Provide a reference to the module indexable by the name of the module
	m_modules[module->getName()] = std::move(module);
}

void Vertex::Menu::ModuleManager::toggleModule(const std::string& name)
{
	if (m_modules.find(name) != m_modules.end())
	{
		m_modules[name]->toggle();
	}
}
