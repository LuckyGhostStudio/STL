#pragma once

#include "List.h"

namespace STL
{
	/// <summary>
	/// 栈
	/// </summary>
	/// <typeparam name="T">元素类型</typeparam>
	/// <typeparam name="Container">底层容器类型：默认顺序表</typeparam>
	template<typename T, typename Container = List<T>>
	class Stack
	{
	private:
		Container m_Container;	// 容器
	public:
		Stack() : m_Container() {}

		uint32_t GetSize() const { return m_Container.GetSize(); }

		bool IsEmpty() const { return m_Container.IsEmpty(); }

		/// <summary>
		/// 入栈
		/// </summary>
		/// <param name="value">待入栈元素</param>
		void Push(const T& value);

		/// <summary>
		/// 出栈
		/// </summary>
		/// <returns>出栈元素</returns>
		void Pop();

		/// <summary>
		/// 获取栈顶元素
		/// </summary>
		/// <returns>栈顶元素</returns>
		const T& Top() const;
	};

	template<typename T, typename Container>
	inline void Stack<T, Container>::Push(const T& value)
	{
		m_Container.Add(value);
	}

	template<typename T, typename Container>
	inline void Stack<T, Container>::Pop()
	{
		m_Container.RemoveLast();
	}

	template<typename T, typename Container>
	inline const T& Stack<T, Container>::Top() const
	{
		return m_Container[m_Container.GetSize() - 1];		// 容器末尾元素
	}
}