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
		Online
	};

	struct ModuleView
	{
		std::string name;
		std::string description;
		Category category;
	};
}
