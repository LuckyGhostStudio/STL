#pragma once

#include "List.h"

namespace STL
{
	/// <summary>
	/// ջ
	/// </summary>
	/// <typeparam name="T">Ԫ������</typeparam>
	/// <typeparam name="Container">�ײ��������ͣ�Ĭ��˳���</typeparam>
	template<typename T, typename Container = List<T>>
	class Stack
	{
	private:
		Container m_Container;	// ����
	public:
		Stack() : m_Container() {}

		uint32_t GetSize() const { return m_Container.GetSize(); }

		bool IsEmpty() const { return m_Container.IsEmpty(); }

		/// <summary>
		/// ��ջ
		/// </summary>
		/// <param name="value">����ջԪ��</param>
		void Push(const T& value);

		/// <summary>
		/// ��ջ
		/// </summary>
		/// <returns>��ջԪ��</returns>
		void Pop();

		/// <summary>
		/// ��ȡջ��Ԫ��
		/// </summary>
		/// <returns>ջ��Ԫ��</returns>
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
		return m_Container[m_Container.GetSize() - 1];		// ����ĩβԪ��
	}
}