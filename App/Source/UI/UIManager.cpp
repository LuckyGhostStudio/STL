#include "UIManager.h"

namespace UI
{
	UIManager& UIManager::GetInstance()
	{
		static UIManager instance;
		return instance;
	}

	void UIManager::RenderUI()
	{
		if (m_Canvas) {
			m_Canvas->Render();
		}
	}

	void UIManager::AddUIElement(UIElement* element)
	{
		if (!m_Canvas) {
			m_Canvas = std::make_shared<Canvas>();	// 创建Canvas
		}
		m_Canvas->AddUIElement(element);			// 添加UI元素到Canvas
	}

	void UIManager::RemoveUIElement(UIElement* element)
	{
		if (m_Canvas) {
			m_Canvas->RemoveUIElement(element);		// 从Canvas移除UI元素
		}
	}
}