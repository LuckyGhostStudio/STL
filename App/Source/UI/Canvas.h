#pragma once

#include <vector>
#include <memory>

#include "UIElement.h"

namespace UI
{
	class Canvas
	{
    private:
        std::vector<UIElement*> m_UIElements;   // UIԪ���б�
    public:
        void Render();

        void AddUIElement(UIElement* element);
        void RemoveUIElement(UIElement* element);
	};
}