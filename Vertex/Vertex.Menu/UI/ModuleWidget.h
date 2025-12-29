#pragma once
#include <memory>
#include "IWidget.h"
#include "ModuleView.h"

namespace Vertex::Menu::UI
{
	template<Category category>
	class ModuleWidget : public IWidget
	{
	public:
		ModuleWidget();
		ModuleWidget(float x, float y);
		ModuleWidget(float x, float y, float width, float height);

		void draw() override;

	protected:
		std::string m_title;
	};

	std::unique_ptr<IWidget> createModuleWidget(Category category);
}
