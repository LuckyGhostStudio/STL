#pragma once

#include "List.h"

namespace STL
{
	/// <summary>
	/// ����
	/// </summary>
	/// <typeparam name="T">Ԫ������</typeparam>
	/// <typeparam name="Container">�ײ��������ͣ�Ĭ��˳���</typeparam>
	template<typename T, typename Container = List<T>>
	class Queue
	{
	private:
		Container m_Container;	// ����
	public:
		Queue() : m_Container() {}

		uint32_t GetSize() const { return m_Container.GetSize(); }

		bool IsEmpty() const { return m_Container.IsEmpty(); }

		/// <summary>
		/// ���
		/// </summary>
		/// <param name="value">�����Ԫ��</param>
		void Push(const T& value);

		/// <summary>
		/// ����
		/// </summary>
		/// <returns>��ջԪ��</returns>
		void Pop();

		/// <summary>
		/// ��ȡ����Ԫ��
		/// </summary>
		/// <returns>����Ԫ��</returns>
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
		m_Container.RemoveAt(0);		// �Ƴ��� 0 ��Ԫ��
	}

	template<typename T, typename Container>
	inline const T& Queue<T, Container>::GetFront() const
	{
		return m_Container[0];		// ������ 0 ��Ԫ��
	}
}