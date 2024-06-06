#pragma once

#include <string>
#include <sstream>
#include <stdexcept>
#include <initializer_list>

namespace STL
{
	/// <summary>
	/// �б�˳���
	/// </summary>
	/// <typeparam name="T">Ԫ������</typeparam>
	template<typename T>
	class List
	{
	private:
		T* m_Data;				// Ԫ���б�
		uint32_t m_Size;		// Ԫ�ظ���
		uint32_t m_Capacity;	// �б��С

		/// <summary>
		/// ����
		/// </summary>
		void InCreaseCapacity();
	public:
		List() : m_Data(new T[1]), m_Size(0), m_Capacity(1) {}

		List(uint32_t capacity) : m_Data(new T[capacity]), m_Size(0), m_Capacity(capacity) {}

		List(const std::initializer_list<T>& initList);

		~List();

		bool IsEmpty() const { return m_Size == 0; }

		uint32_t GetSize() const { return m_Size; }

		uint32_t GetCapacity() const { return m_Capacity; }

		/// <summary>
		/// ����Ԫ��
		/// </summary>
		/// <param name="index">�����λ��</param>
		/// <param name="value">�����Ԫ��</param>
		void Insert(uint32_t index, const T& value);

		/// <summary>
		/// ���Ԫ�أ���ӵ��б�ĩβ
		/// </summary>
		/// <param name="value">����ӵ�Ԫ��</param>
		void Add(const T& value);

		/// <summary>
		/// ����Ԫ�أ����Ҵ����ҵ�һ��Ԫ��
		/// </summary>
		/// <param name="value">������Ԫ��</param>
		/// <returns>Ԫ��λ��</returns>
		int Find(const T& value);

		/// <summary>
		/// �Ƴ�Ԫ�أ�����������
		/// </summary>
		/// <param name="index">���Ƴ�Ԫ�ص�λ��</param>
		void RemoveAt(uint32_t index);

		/// <summary>
		/// �Ƴ��б����һ��Ԫ��
		/// </summary>
		void RemoveLast();

		T& operator[](uint32_t index);

		const T& operator[](uint32_t index) const;

		std::string ToString() const;
	};

	template<typename T>
	inline void List<T>::InCreaseCapacity()
	{
		uint32_t newCapacity = m_Capacity * 2;		// ������
		T* newData = new T[newCapacity];		// �����¿ռ�

		// ����Ԫ��
		for (uint32_t i = 0; i < m_Size; i++) {
			newData[i] = m_Data[i];
		}

		delete[] m_Data;			// �ͷžɿռ�

		m_Data = newData;
		m_Capacity = newCapacity;
	}

	template<typename T>
	inline List<T>::List(const std::initializer_list<T>& initList) : m_Size(initList.size()), m_Capacity(initList.size())
	{
		m_Data = new T[m_Capacity];

		std::copy(initList.begin(), initList.end(), m_Data);	// ���Ƴ�ʼ���б��ֵ�� m_Data
	}

	template<typename T>
	inline List<T>::~List()
	{
		if (m_Data) {
			delete[] m_Data;
		}
	}

	template<typename T>
	inline void List<T>::Insert(uint32_t index, const T& value)
	{
		if (index < 0 || index > m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		// �б�����
		if (m_Size == m_Capacity) {
			InCreaseCapacity();		// ����
		}

		// Ԫ�غ���
		for (uint32_t i = m_Size; i > index; i--) {
			m_Data[i] = m_Data[i - 1];
		}

		m_Data[index] = value;	// ������Ԫ��
		m_Size++;
	}

	template<typename T>
	inline void List<T>::Add(const T& value)
	{
		Insert(m_Size, value);
	}

	template<typename T>
	inline int List<T>::Find(const T& value)
	{
		for (uint32_t i = 0; i < m_Size; i++) {
			if (m_Data[i] == value) {
				return i;
			}
		}
		return -1;
	}

	template<typename T>
	inline void List<T>::RemoveAt(uint32_t index)
	{
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}

		for (uint32_t i = index; i < m_Size - 1; i++) {
			m_Data[i] = m_Data[i + 1];
		}

		m_Data[m_Size - 1].~T();	// �Ƴ����һ��û�õ�Ԫ��
		m_Size--;
	}

	template<typename T>
	inline void List<T>::RemoveLast()
	{
		RemoveAt(m_Size - 1);
	}

	template<typename T>
	inline T& List<T>::operator[](uint32_t index)
	{
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}
		return m_Data[index];
	}

	template<typename T>
	inline const T& List<T>::operator[](uint32_t index) const
	{
		if (index < 0 || index >= m_Size) {
			throw std::out_of_range("Index is out of range.");
		}
		return m_Data[index];
	}

	template<typename T>
	inline std::string List<T>::ToString() const
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
}