#pragma once

#include <cstring>

namespace FTL
{
#ifdef UNICODE
	__forceinline int strcmp(const wchar_t* str, const wchar_t* des) { return ::wcscmp(str, des); }
	__forceinline int stricmp(const wchar_t* str, const wchar_t* des) { return ::_wcsicmp(str, des); }
	__forceinline size_t strlen(const wchar_t* str) { return ::wcslen(str); }
#else
	__forceinline int strcmp(const char* str, const char* des) { return ::strcmp(str, des); }
	__forceinline int stricmp(const char* str, const char* des) { return ::stricmp(str, des); }
	__forceinline size_t strlen(const char* str) { return ::strlen(str); }
#endif
}