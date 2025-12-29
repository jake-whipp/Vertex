#pragma once
#include <string>
#include "UI/ModuleView.h"

namespace Vertex::Menu
{
	class IModule
	{
	public:
		IModule(std::string name, std::string desc, Category cat) 
			: m_name(std::move(name)), m_description(std::move(desc)), m_category(cat), m_enabled(false) {}
		virtual ~IModule() = default;

		// Define framework for each module
		virtual void onEnable() = 0;
		virtual void onDisable() = 0;
		virtual void onUpdate() {}

		void toggle()
		{
			m_enabled = !m_enabled;
			m_enabled ? onEnable() : onDisable();
		}

		bool isEnabled() const { return m_enabled; }
		const std::string& getName() { return m_name; }
		const std::string& getDescription() { return m_description; }
		const Category getCategory() { return m_category; }

	protected:
		std::string m_name;
		std::string m_description;
		const Category m_category;
		bool m_enabled;
	};
}
