#pragma once

namespace Vertex::Menu::UI
{
	class IWidget
	{
	public:
		IWidget(float x, float y, float width, float height)
			: m_pos(ImVec2(x, y)), m_size(ImVec2(width, height)) {}

		void setPos(float x, float y) { m_pos = ImVec2(x, y); }
		void setSize(float width, float height) { m_size = ImVec2(width, height); }

		virtual void draw() = 0;
		virtual ~IWidget() = default;

	protected:
		ImVec2 m_pos;
		ImVec2 m_size;
	};
}
