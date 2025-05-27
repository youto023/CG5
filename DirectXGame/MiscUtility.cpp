#include "MiscUtility.h"
#include <Windows.h> // MultiByteToWideChar	WideCharToMultiByte	CP_UTF8
#include <string>    // string, wstring

// string => wstring 文字列変換
std::wstring MiscUtility::ConvertString(const std::string& str) {
	if (str.empty()) {
		return std::wstring();
	}
	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(str.c_str()),
		static_cast<int>(str.size()), nullptr, 0);
	if (sizeNeeded==0) {
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(str.c_str()),
		static_cast<int>(str.size()), &result[0], sizeNeeded);
	return result;
}

// wstring => string 文字列変換
std::string MiscUtility::ConvertString(const std::wstring& str) {
	if (str.empty()) {
		return std::string();
	}
	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded==0) {
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), result.data(), sizeNeeded, NULL, NULL);
	return result;
}
