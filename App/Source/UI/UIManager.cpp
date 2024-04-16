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
			m_Canvas = std::make_shared<Canvas>();	// ����Canvas
		}
		m_Canvas->AddUIElement(element);			// ���UIԪ�ص�Canvas
	}

	void UIManager::RemoveUIElement(UIElement* element)
	{
		if (m_Canvas) {
			m_Canvas->RemoveUIElement(element);		// ��Canvas�Ƴ�UIԪ��
		}
	}
}