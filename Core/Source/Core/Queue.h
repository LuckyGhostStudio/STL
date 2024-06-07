#pragma once

#include "List.h"

namespace STL
{
	/// <summary>
	/// 队列
	/// </summary>
	/// <typeparam name="T">元素类型</typeparam>
	/// <typeparam name="Container">底层容器类型：默认顺序表</typeparam>
	template<typename T, typename Container = List<T>>
	class Queue
	{
	private:
		Container m_Container;	// 容器
	public:
		Queue() : m_Container() {}

		uint32_t GetSize() const { return m_Container.GetSize(); }

		bool IsEmpty() const { return m_Container.IsEmpty(); }

		/// <summary>
		/// 入队
		/// </summary>
		/// <param name="value">待入队元素</param>
		void Push(const T& value);

		/// <summary>
		/// 出队
		/// </summary>
		/// <returns>出栈元素</returns>
		void Pop();

		/// <summary>
		/// 获取队首元素
		/// </summary>
		/// <returns>队首元素</returns>
		const T& GetFront() const;
	};

	template<typename T, typename Container>
	inline void Queue<T, Container>::Push(const T& value)
	{
		m_Container.Add(value);
	}

	template<typename T, typename Container>
	inline void Queue<T, Container>::Pop()
	{
		m_Container.RemoveAt(0);		// 移除第 0 个元素
	}

	template<typename T, typename Container>
	inline const T& Queue<T, Container>::GetFront() const
	{
		return m_Container[0];		// 容器第 0 个元素
	}
}