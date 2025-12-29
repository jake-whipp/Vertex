#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "Modules/IModule.h"
#include "UI/ModuleView.h"

namespace Vertex::Menu 
{
	enum class ModuleManagerState
	{
		Uninitialised,
		BuildingModules,
		Complete,
		Failed
	};

	class ModuleManager
	{
	public:
		static ModuleManager& getInstance() 
		{
			static ModuleManager instance;
			return instance;
		}

		void initialise();

		void registerModule(std::unique_ptr<Modules::IModule> module);

		void toggleModule(const std::string& name);

		const std::vector<ModuleView>& getAllModules() const;

	private:
		ModuleManager();
		
		std::unordered_map<std::string, std::unique_ptr<Modules::IModule>> m_modules;

		std::vector<ModuleView> m_allModuleInfo;

		ModuleManagerState m_state;
	};
}
