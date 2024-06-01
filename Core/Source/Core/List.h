#pragma once

#include <string>
#include <sstream>
#include <stdexcept>
#include <initializer_list>

namespace STL
{
	/// <summary>
	/// 列表：顺序表
	/// </summary>
	/// <typeparam name="T">元素类型</typeparam>
	template<typename T>
	class List
	{
	private:
		T* m_Data;				// 元素列表
		uint32_t m_Size;		// 元素个数
		uint32_t m_Capacity;	// 列表大小

		/// <summary>
		/// 扩容
		/// </summary>
		void InCreaseCapacity()
		{
			uint32_t newCapacity = m_Capacity * 2;		// 新容量
			T* newData = new T[newCapacity];		// 申请新空间

			// 复制元素
			for (uint32_t i = 0; i < m_Size; i++) {
				newData[i] = m_Data[i];
			}

			delete[] m_Data;			// 释放旧空间

			m_Data = newData;
			m_Capacity = newCapacity;
		}
	public:
		List() : m_Size(0), m_Capacity(1)
		{
			m_Data = new T[m_Capacity];
		}

		List(uint32_t capacity) : m_Size(0), m_Capacity(capacity)
		{
			m_Data = new T[m_Capacity];
		}

		List(const std::initializer_list<T>& initList) : m_Size(initList.size()), m_Capacity(initList.size())
		{
			m_Data = new T[m_Capacity];

			std::copy(initList.begin(), initList.end(), m_Data);	// 复制初始化列表的值到 m_Data
		}

		~List()
		{
			if (m_Data) {
				delete[] m_Data;
			}
		}

		bool IsEmpty() const
		{
			return m_Size == 0;
		}

		uint32_t GetSize() const
		{
			return m_Size;
		}

		uint32_t GetCapacity() const
		{
			return m_Capacity;
		}

		/// <summary>
		/// 插入元素
		/// </summary>
		/// <param name="index">插入的位置</param>
		/// <param name="value">插入的元素</param>
		void Insert(uint32_t index, const T& value)
		{
			if (index > m_Size) {
				throw std::out_of_range("Index is out of range.");
			}

			// 列表已满
			if (m_Size == m_Capacity) {
				InCreaseCapacity();		// 扩容
			}

			// 元素后移
			for (uint32_t i = m_Size; i > index; i--) {
				m_Data[i] = m_Data[i - 1];
			}

			m_Data[index] = value;	// 插入新元素
			m_Size++;
		}

		/// <summary>
		/// 添加元素：添加到列表末尾
		/// </summary>
		/// <param name="value">待添加的元素</param>
		void Add(const T& value)
		{
			// 列表已满
			if (m_Size == m_Capacity) {
				InCreaseCapacity();		// 扩容
			}

			m_Data[m_Size] = value;		// 添加新元素到末尾
			m_Size++;
		}

		/// <summary>
		/// 查找元素：查找从左到右第一个元素
		/// </summary>
		/// <param name="value">待查找元素</param>
		/// <returns>元素位置</returns>
		int Find(const T& value)
		{
			for (uint32_t i = 0; i < m_Size; i++) {
				if (m_Data[i] == value) {
					return i;
				}
			}
			return -1;
		}

		/// <summary>
		/// 移除元素：按索引查找
		/// </summary>
		/// <param name="index">待移除元素的位置</param>
		void RemoveAt(uint32_t index)
		{
			if (index >= m_Size) {
				throw std::out_of_range("Index is out of range.");
			}

			for (uint32_t i = index; i < m_Size - 1; i++) {
				m_Data[i] = m_Data[i + 1];
			}

			m_Data[m_Size - 1].~T();	// 移除最后一个元素
			m_Size--;
		}

		/// <summary>
		/// 移除列表最后一个元素
		/// </summary>
		void RemoveLast()
		{
			if (m_Size == 0) {
				throw std::out_of_range("Index is out of range.");
			}

			m_Data[m_Size - 1].~T();	// 移除最后一个元素
			m_Size--;
		}

		T& operator[](uint32_t index) {
			if (index >= m_Size) {
				throw std::out_of_range("Index is out of range.");
			}
			return m_Data[index];
		}

		const T& operator[](uint32_t index) const
		{
			if (index >= m_Size) {
				throw std::out_of_range("Index is out of range.");
			}
			return m_Data[index];
		}

		std::string ToString() const
		{
			if (m_Size == 0) {
				return "[ ]";
			}

			std::stringstream ss;
			ss << "[";

			for (uint32_t i = 0; i < m_Size; i++) {
				ss << m_Data[i];
				if (i != m_Size - 1) {
					ss << ", ";
				}
			}

			ss << "]";

			return ss.str();
		}
	};
}