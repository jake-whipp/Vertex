#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "IModule.h"

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

	private:
		ModuleManager();
		~ModuleManager();
		
		std::unordered_map<std::string, std::unique_ptr<IModule>> m_modules;
	};
}
