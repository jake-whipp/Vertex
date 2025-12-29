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

	// TODO: reduce coupling -- can be done with some kind of macro
	static constexpr Category allCategories[] = {
		Category::Cheat, Category::Customisation, Category::Music,
		Category::Interface, Category::Utility, Category::Performance,
		Category::Bugfix, Category::Online, Category::Miscellaneous
	};

	inline std::string toString(Category c) {
		switch (c) {
		case Category::Cheat:			return "Cheat";
		case Category::Customisation:	return "Customisation";
		case Category::Music:			return "Music";
		case Category::Interface:		return "Interface";
		case Category::Utility:			return "Utility";
		case Category::Performance:		return "Performance";
		case Category::Bugfix:			return "Bugfix";
		case Category::Online:			return "Online";
		case Category::Miscellaneous:	return "Miscellaneous";
		default:						return "Unknown";
		// TODO raise runtime error if default case reached
		}
	}

	struct ModuleView
	{
		std::string name;
		std::string description;
		Category category = Category::Miscellaneous;
		bool enabled = false;
	};
}
