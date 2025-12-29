#include "pch.h"
#include "ModuleManager.h"

namespace Vertex::Menu
{
	ModuleManager::ModuleManager() : m_state(ModuleManagerState::Uninitialised)
	{
		// TODO: load config ?
		
	}

	void ModuleManager::initialise()
	{
		if (m_state != ModuleManagerState::Uninitialised)
		{
			return;
		}

		// To avoid the Static Initialisation Order Fiasco, build the m_modules vector here, 
		// instead of in the constructor.
		m_state = ModuleManagerState::BuildingModules;

		for (const auto& [name, pModule] : m_modules)
		{
			ModuleView view;
			view.name = name;
			view.description = pModule->getDescription();
			view.category = pModule->getCategory();
			view.enabled = pModule->isEnabled();

			m_allModuleInfo.emplace_back(view);
		}

		// Check if this somehow failed
		if (m_modules.size() < 1)
		{
			m_state = ModuleManagerState::Failed;
		}
		else
		{
			m_state = ModuleManagerState::Complete;
		}
		
		return;
	}

	void ModuleManager::registerModule(std::unique_ptr<Modules::IModule> module)
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

	const std::vector<ModuleView>& ModuleManager::getAllModules() const
	{
		return m_allModuleInfo;
	}
}
