#include "pch.h"
#include "ModuleWidget.h"
#include "ModuleManager.h"

namespace Vertex::Menu::UI
{
	template<Category category>
	ModuleWidget<category>::ModuleWidget() : IWidget(0.0f, 0.0f, 400.0f, 400.0f)
	{
		m_title = toString(category);
	}

	template<Category category>
	ModuleWidget<category>::ModuleWidget(float x, float y) 
		: IWidget(x, y, 400.0f, 400.0f) // TODO: remove magic, define macro
	{
		m_title = toString(category);
	}

	template<Category category>
	ModuleWidget<category>::ModuleWidget(float x, float y, float width, float height)
		: IWidget(x, y, width, height)
	{
		m_title = toString(category);
	}

	template<Category category>
	void ModuleWidget<category>::draw()
	{
		ImGui::SetNextWindowSize(m_size, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(m_pos, ImGuiCond_FirstUseEver);

		// Draw window
		ImGui::Begin(m_title.c_str(), NULL, ImGuiWindowFlags_None);
		ImGui::Text(m_title.c_str());

		for (const auto& module : ModuleManager::getInstance().getAllModules())
		{
			// Only display modules of this widget's category type
			if (module.category != category)
			{
				continue;
			}

			// Create a copy of the bool so that ImGui's checkbox can stay 
			// compliant with ModuleManager::getAllModules (const vs non-const)
			bool enabled = module.enabled;

			// Create a checkbox for this module. When clicked, invoke the toggle
			if (ImGui::Checkbox(module.name.c_str(), &enabled))
			{
				ModuleManager::getInstance().toggleModule(module.name);
			}

			ImGui::SetItemTooltip(module.description.c_str(), module.name.c_str());
		}

		ImGui::End();
	}

	// Factory method for the UIManager to use in its main draw call
	std::unique_ptr<IWidget> createModuleWidget(Category category)
	{
		switch (category)
		{
		case Category::Cheat:			return std::make_unique<ModuleWidget<Category::Cheat>>();
		case Category::Customisation:	return std::make_unique<ModuleWidget<Category::Customisation>>();
		case Category::Music:			return std::make_unique<ModuleWidget<Category::Music>>();
		case Category::Interface:		return std::make_unique<ModuleWidget<Category::Interface>>();
		case Category::Utility:			return std::make_unique<ModuleWidget<Category::Utility>>();
		case Category::Performance:		return std::make_unique<ModuleWidget<Category::Performance>>();
		case Category::Bugfix:			return std::make_unique<ModuleWidget<Category::Bugfix>>();
		case Category::Online:			return std::make_unique<ModuleWidget<Category::Online>>();
		case Category::Miscellaneous:	return std::make_unique<ModuleWidget<Category::Miscellaneous>>();
		default:						return nullptr;
		}
	}
}
