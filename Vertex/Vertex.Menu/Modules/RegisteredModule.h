#pragma once
#include "IModule.h"
#include "ModuleManager.h"

namespace Vertex::Menu
{
	template <typename T>
	class RegisteredModule : public IModule
	{
	public:
		// Self-registering factory pattern (https://www.cppstories.com/2018/02/factory-selfregister/)
		static void registerSelf()
		{
			auto instance = std::make_unique<T>();
			ModuleManager::getInstance().registerModule(std::move(instance));
		}

	protected:
		RegisteredModule(std::string name) : IModule(std::move(name)) {}

		virtual ~RegisteredModule() = default;
	};
}
