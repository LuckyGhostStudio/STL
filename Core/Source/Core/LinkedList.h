#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

namespace STL
{
	/// <summary>
	/// 链表结点
	/// </summary>
	/// <typeparam name="T">结点数据的类型</typeparam>
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
	/// 单链表
	/// </summary>
	/// <typeparam name="T">结点数据的类型</typeparam>
	template<typename T>
	class LinkedList
	{
	private:
		ListNode<T>* m_Head;	// 头结点
		uint32_t m_Size;		// 长度
	public:
		LinkedList() : m_Head(nullptr), m_Size(0) {}
		~LinkedList();

		uint32_t GetSize() const;

		/// <summary>
		/// 插入元素
		/// </summary>
		/// <param name="index">待插入索引</param>
		/// <param name="value">待插入元素</param>
		void Insert(uint32_t index, const T& value);

		/// <summary>
		/// 添加元素到末尾
		/// </summary>
		/// <param name="value">待添加元素</param>
		void Add(const T& value);

		/// <summary>
		/// 移除元素
		/// </summary>
		/// <param name="index">待移除索引</param>
		void RemoveAt(uint32_t index);

		/// <summary>
		/// 移除最后一个元素
		/// </summary>
		void RemoveLast();

		/// <summary>
		/// 查找元素：从头结点开始的第一个值相等的元素
		/// </summary>
		/// <param name="value">待查找元素值</param>
		/// <returns>元素的索引</returns>
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
		// 判断插入位置是否合法
		if (index < 0 || index > m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		ListNode<T>* newNode = new ListNode<T>(value);		// 创建新结点

		if (index == 0) {				// 插入位置为头结点
			newNode->m_Next = m_Head;	// 新节点 next 指向头结点
			m_Head = newNode;			// 新节点作为头结点
		}
		else {
			ListNode<T>* curr = m_Head;
			// 找到第 index - 1 个结点
			for (uint32_t i = 0; i < index - 1; i++) {
				curr = curr->m_Next;
			}

			newNode->m_Next = curr->m_Next;		// 新节点的 next 指向第 index 个结点
			curr->m_Next = newNode;				// 第 index - 1 个结点的下一个（第 index 个）为 新结点
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
		// 判断索引是否合法
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		if (index == 0) {					// 删除头结点
			ListNode<T>* temp = m_Head;
			m_Head = m_Head->m_Next;		// 头结点更新为头结点的 next
			delete temp;
		}
		else {
			ListNode<T>* curr = m_Head;
			// 找到第 index - 1 个结点
			for (uint32_t i = 0; i < index - 1; i++) {
				curr = curr->m_Next;
			}

			ListNode<T>* temp = curr->m_Next;
			curr->m_Next = temp->m_Next;		// 第 index - 1 个结点的 next 指向第 index + 1 个结点
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
			// 找到 value
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
		// 判断索引是否合法
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		ListNode<T>* curr = m_Head;
		// 找到第 index 个结点
		for (uint32_t i = 0; i < index; i++) {
			curr = curr->m_Next;
		}

		return curr->m_Data;
	}

	template<typename T>
	inline const T& LinkedList<T>::operator[](uint32_t index) const
	{
		// 判断索引是否合法
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