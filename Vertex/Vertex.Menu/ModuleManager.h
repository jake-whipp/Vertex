#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "Modules/IModule.h"
#include "ModuleView.h"

namespace Vertex::Menu 
{
	class ModuleManager
	{
	public:
		static ModuleManager& getInstance() 
		{
			static ModuleManager instance;
			return instance;
		}

		void registerModule(std::unique_ptr<IModule> module);

		void toggleModule(const std::string& name);

		std::vector<ModuleView> GetAllModules();

	private:
		ModuleManager();
		~ModuleManager();
		
		std::unordered_map<std::string, std::unique_ptr<IModule>> m_modules;
	};
}
