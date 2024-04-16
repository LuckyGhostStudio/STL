#pragma once

#include <string>
#include <stringapiset.h>

namespace Utils
{
	static wchar_t* StringToWChar(const std::string& str)
	{
		int wcharlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length() + 1, NULL, 0);
		wchar_t* wcstr = new wchar_t[wcharlen];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length() + 1, wcstr, wcharlen);

		return wcstr;
	}
}