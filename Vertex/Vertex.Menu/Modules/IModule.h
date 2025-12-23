#pragma once
#include <string>

namespace Vertex::Menu
{
	class IModule
	{
	public:
		IModule(std::string name) : m_name(std::move(name)), m_enabled(false) {}
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

	protected:
		std::string m_name;
		bool m_enabled;
	};
}
