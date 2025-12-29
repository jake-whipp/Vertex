#pragma once
#include <string>

namespace Vertex::Menu
{
	enum class Category
	{
		Cheat,
		Customisation,
		Music,
		Interface,
		Utility,
		Performance,
		Bugfix,
		Online,
		Miscellaneous
	};

	struct ModuleView
	{
		std::string name;
		std::string description;
		Category category = Category::Miscellaneous;
		bool enabled = false;
	};
}
