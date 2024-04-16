#pragma once

#include "Utils/Vector2.h"

using namespace Math;

namespace UI
{
	/// <summary>
	/// UI元素的基类
	/// </summary>
	class UIElement
	{
	protected:
		Vector2 m_Position;
		Vector2 m_Size;
	public:
		UIElement() {}
		UIElement(const Vector2& position, const Vector2& size) : m_Position(position), m_Size(size) {}

		const Vector2& GetPosition() const { return m_Position; }
		const Vector2& GetSize() const { return m_Size; }

		void SetPosition(const Vector2& position) { m_Position = position; }
		void SetSize(const Vector2& size) { m_Size = size; }

		virtual void Render() = 0;
		virtual void OnEvent() = 0;
	};
}