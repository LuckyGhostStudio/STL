#pragma once

#include <vector>
#include <memory>

#include "Canvas.h"
#include "UIElement.h"

namespace UI
{
	class UIManager
	{
	private:
		std::shared_ptr<Canvas> m_Canvas;	// Canvas

		UIManager() {}
		UIManager(const UIManager&) = delete;
		void operator=(const UIManager&) = delete;
	public:
		static UIManager& GetInstance();

		void RenderUI();

		void AddUIElement(UIElement* element);
		void RemoveUIElement(UIElement* element);
	};
}