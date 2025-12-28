#include "pch.h"
#include "ModuleManager.h"

namespace Vertex::Menu
{
	ModuleManager::ModuleManager()
	{

	}

	ModuleManager::~ModuleManager()
	{
		// Disable all active modules to safely restore game instructions
		for (const auto& [name, pModule] : m_modules)
		{
			if (pModule->isEnabled())
			{
				pModule->onDisable();
			}
		}

		// Clear the map
		m_modules.clear();
	}

	void ModuleManager::registerModule(std::unique_ptr<IModule> module)
	{
		// Provide a reference to the module indexable by the name of the module
		m_modules[module->getName()] = std::move(module);
	}

	void ModuleManager::toggleModule(const std::string& name)
	{
		if (m_modules.find(name) != m_modules.end())
		{
			m_modules[name]->toggle();
		}
	}

	std::vector<ModuleView> ModuleManager::GetAllModules()
	{
		std::vector<ModuleView> allModuleInfo;

		for (const auto& [name, pModule] : m_modules)
		{
			ModuleView view;
			view.name = name;
			view.description = pModule->getDescription();
			view.category = pModule->getCategory();

			allModuleInfo.emplace_back(view);
		}

		return allModuleInfo;
	}
}
