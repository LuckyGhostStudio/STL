#pragma once

#include <cstdint>
#include <ostream>

namespace STL
{
	/// <summary>
	/// ×Ö·û´®
	/// </summary>
	class String
	{
	private:
		char* m_Str;		// ×Ö·û´®
		uint32_t m_Length;	// ³¤¶È
	public:
		String();
		String(const char* str);
		String(const String& str);
		~String();

		uint32_t GetLength() const;
		
		char operator[](uint32_t index) const;
		
		String& operator=(const String& str);
		String& operator+=(const String& str);
		String operator+(const String& str) const;
		
		bool operator!=(const String& str) const;
		bool operator==(const String& str) const;

		String Copy() const;


		friend std::ostream& operator<<(std::ostream& out, const String& str);
	};
}