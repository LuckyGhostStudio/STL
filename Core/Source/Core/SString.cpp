#include "SString.h"

#include <cstring>
#include <stdexcept>

namespace STL
{
	String::String() : m_Length(0)
	{
		m_Str = new char[1];
		m_Str[0] = '/0';
	}

	String::String(const char* str)
	{
		m_Length = strlen(str);
		m_Str = new char[m_Length + 1];

		strcpy(m_Str, str);
	}

	String::String(const String& str)
	{
		m_Length = strlen(str.m_Str);
		m_Str = new char[m_Length + 1];

		strcpy(m_Str, str.m_Str);
	}

	String::~String()
	{
		delete[] m_Str;
	}

	uint32_t String::GetLength() const
	{
		return m_Length;
	}

	char String::operator[](uint32_t index) const
	{
		if (index < 0 || index >= m_Length) {
			throw std::out_of_range("Index out of range.");
		}

		return m_Str[index];
	}

	String& String::operator=(const String& str)
	{
		if (this != &str) {
			delete[] m_Str;
			m_Length = str.m_Length;
			m_Str = new char[m_Length + 1];

			strcpy(m_Str, str.m_Str);
		}

		return *this;
	}

	String& String::operator+=(const String& str)
	{
		uint32_t newLength = m_Length + str.m_Length;	// 计算新字符串的长度

		char* newStr = new char[newLength + 1];			// 重新分配内存

		strcpy(newStr, m_Str);		// 复制原始字符串的内容
		strcat(newStr, str.m_Str);	// 连接第二个字符串的内容

		delete[] m_Str;				// 释放旧内存

		m_Str = newStr;
		m_Length = newLength;

		return *this;				// 返回当前对象的引用
	}

	String String::operator+(const String& str) const
	{
		String result;

		result.m_Length = m_Length + str.m_Length;
		result.m_Str = new char[result.m_Length + 1];

		strcpy(result.m_Str, m_Str);		// m_Str 拷贝到前半段
		strcat(result.m_Str, str.m_Str);	// str.m_Str 拼接到后半段

		return result;
	}

	bool String::operator==(const String& str) const
	{
		return strcmp(m_Str, str.m_Str) == 0;
	}

	bool String::operator!=(const String& str) const
	{
		return strcmp(m_Str, str.m_Str) != 0;
	}

	String String::Copy() const
	{
		String str = *this;
		return str;
	}

	std::ostream& operator<<(std::ostream& out, const String& str)
	{
		out << str.m_Str;	// str.m_Str 输出到输出流
		return out;
	}
}
