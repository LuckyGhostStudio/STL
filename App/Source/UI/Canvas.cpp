#include "Canvas.h"

namespace UI
{
    void Canvas::Render()
    {
        for (const auto& element : m_UIElements) {
            element->Render();
        }
    }

    void Canvas::AddUIElement(UIElement* element)
    {
        m_UIElements.push_back(element);
    }

    void Canvas::RemoveUIElement(UIElement* element)
    {
        // TODO ÒÆ³ý UI ÔªËØµÄÂß¼­
    }
}