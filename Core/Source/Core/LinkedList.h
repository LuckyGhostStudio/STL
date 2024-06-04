#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

namespace STL
{
	/// <summary>
	/// ������
	/// </summary>
	/// <typeparam name="T">������ݵ�����</typeparam>
	template<typename T>
	class ListNode
	{
	public:
		template<typename T> friend class LinkedList;
	private:
		T m_Data;
		ListNode* m_Next;

		ListNode(const T& data, ListNode* next = nullptr) : m_Data(data), m_Next(next) {}
	};

	/// <summary>
	/// ������
	/// </summary>
	/// <typeparam name="T">������ݵ�����</typeparam>
	template<typename T>
	class LinkedList
	{
	private:
		ListNode<T>* m_Head;	// ͷ���
		uint32_t m_Size;		// ����
	public:
		LinkedList() : m_Head(nullptr), m_Size(0) {}
		~LinkedList();

		uint32_t GetSize() const;

		/// <summary>
		/// ����Ԫ��
		/// </summary>
		/// <param name="index">����������</param>
		/// <param name="value">������Ԫ��</param>
		void Insert(uint32_t index, const T& value);

		/// <summary>
		/// ���Ԫ�ص�ĩβ
		/// </summary>
		/// <param name="value">�����Ԫ��</param>
		void Add(const T& value);

		/// <summary>
		/// �Ƴ�Ԫ��
		/// </summary>
		/// <param name="index">���Ƴ�����</param>
		void RemoveAt(uint32_t index);

		/// <summary>
		/// �Ƴ����һ��Ԫ��
		/// </summary>
		void RemoveLast();

		/// <summary>
		/// ����Ԫ�أ���ͷ��㿪ʼ�ĵ�һ��ֵ��ȵ�Ԫ��
		/// </summary>
		/// <param name="value">������Ԫ��ֵ</param>
		/// <returns>Ԫ�ص�����</returns>
		uint32_t Find(const T& value);

		T& operator[](uint32_t index);
		const T& operator[](uint32_t index) const;

		std::string ToString() const;
	};

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		ListNode<T>* curr = m_Head;

		while (curr) {
			ListNode<T>* temp = curr;
			curr = curr->m_Next;

			delete temp;
		}
	}

	template<typename T>
	inline uint32_t LinkedList<T>::GetSize() const
	{
		return m_Size;
	}

	template<typename T>
	inline void LinkedList<T>::Insert(uint32_t index, const T& value)
	{
		// �жϲ���λ���Ƿ�Ϸ�
		if (index < 0 || index > m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		ListNode<T>* newNode = new ListNode<T>(value);		// �����½��

		if (index == 0) {				// ����λ��Ϊͷ���
			newNode->m_Next = m_Head;	// �½ڵ� next ָ��ͷ���
			m_Head = newNode;			// �½ڵ���Ϊͷ���
		}
		else {
			ListNode<T>* curr = m_Head;
			// �ҵ��� index - 1 �����
			for (uint32_t i = 0; i < index - 1; i++) {
				curr = curr->m_Next;
			}

			newNode->m_Next = curr->m_Next;		// �½ڵ�� next ָ��� index �����
			curr->m_Next = newNode;				// �� index - 1 ��������һ������ index ����Ϊ �½��
		}

		m_Size++;
	}

	template<typename T>
	inline void LinkedList<T>::Add(const T& value)
	{
		Insert(m_Size, value);
	}

	template<typename T>
	inline void LinkedList<T>::RemoveAt(uint32_t index)
	{
		// �ж������Ƿ�Ϸ�
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		if (index == 0) {					// ɾ��ͷ���
			ListNode<T>* temp = m_Head;
			m_Head = m_Head->m_Next;		// ͷ������Ϊͷ���� next
			delete temp;
		}
		else {
			ListNode<T>* curr = m_Head;
			// �ҵ��� index - 1 �����
			for (uint32_t i = 0; i < index - 1; i++) {
				curr = curr->m_Next;
			}

			ListNode<T>* temp = curr->m_Next;
			curr->m_Next = temp->m_Next;		// �� index - 1 ������ next ָ��� index + 1 �����
			delete temp;
		}

		m_Size--;
	}

	template<typename T>
	inline void LinkedList<T>::RemoveLast()
	{
		RemoveAt(m_Size - 1);
	}

	template<typename T>
	inline uint32_t LinkedList<T>::Find(const T& value)
	{
		ListNode<T>* curr = m_Head;
		
		for (uint32_t i = 0; curr != nullptr; i++) {
			// �ҵ� value
			if (curr->m_Data == value) {
				return i;
			}
			curr = curr->m_Next;
		}

		return -1;
	}

	template<typename T>
	inline T& LinkedList<T>::operator[](uint32_t index)
	{
		// �ж������Ƿ�Ϸ�
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		ListNode<T>* curr = m_Head;
		// �ҵ��� index �����
		for (uint32_t i = 0; i < index; i++) {
			curr = curr->m_Next;
		}

		return curr->m_Data;
	}

	template<typename T>
	inline const T& LinkedList<T>::operator[](uint32_t index) const
	{
		// �ж������Ƿ�Ϸ�
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		ListNode<T>* curr = m_Head;
		for (uint32_t i = 0; i < index; i++) {
			curr = curr->m_Next;
		}

		return curr->m_Data;
	}

	template<typename T>
	inline std::string LinkedList<T>::ToString() const
	{
		if (m_Size == 0) {
			return "[ ]";
		}

		std::stringstream ss;
		ss << "[";

		ListNode<T>* curr = m_Head;

		for (uint32_t i = 0; curr != nullptr; i++) {
			ss << curr->m_Data;
			if (i != m_Size - 1) {
				ss << ", ";
			}

			curr = curr->m_Next;
		}

		ss << "]";

		return ss.str();
	}
}