#pragma once

#include "FArray.h"
#include "FLibrary.h"
#include <tchar.h>
#include <memory>

#ifdef UNICODE
#ifndef TEXT
#define TEXT(x) L##x
#endif
#else
#ifndef TEXT
#define TEXT(x) x
#endif
#endif


class FString : public FArray<TCHAR>
{
public:
	FString() : FArray()
	{
		FTL::memZero(begin(), m_nCurSize);
	}
	FString(const TCHAR* str) : FArray(FTL::strlen(str)+1)
	{
		m_nCurSize = FTL::strlen(str) + 1;
		FTL::memcpy(begin(), str, m_nCurSize);
	}

	FString(const FString& other) : FArray(other) {}
	FString(FString&& other) : FArray(std::move(other)) {}

	size_t Len() { return m_nCurSize - 1; }

	bool operator== (const TCHAR *str) const { return FTL::stricmp(cbegin(), str) == 0; }
	bool operator== (const FString& other) const { return FTL::stricmp(cbegin(), other.cbegin()) == 0; }
	bool operator!= (const TCHAR *str) const { return !(operator==(str)); }
	bool operator!= (const FString& other) const { return !(operator==(other)); }
	FString& operator+= (const FString& other)
	{
		m_nCurSize--;
		push_back(other);
		return *this;
	}
	FString& operator= (const TCHAR *str)
	{
		*this = FString(str);
		return *this;
	}
	FString& operator= (const FString& other)
	{
		m_nCurSize = other.m_nCurSize;
		m_nMaxSize = other.m_nMaxSize;
		m_nSizeIndex = other.m_nSizeIndex;

		Resize();

		FTL::memcpy(begin(), other.cbegin(), m_nCurSize);
		
		return *this;
	}
	FString& operator= (FString&& other)
	{
		//TODO : Refactoring
		m_nCurSize = other.m_nCurSize;
		m_nMaxSize = other.m_nMaxSize;
		m_nSizeIndex = other.m_nSizeIndex;

		m_pPivot = other.m_pPivot;

		other.Finalize();
		return *this;
	}
	FString& operator+= (const TCHAR *str)
	{
		*this += FString(str);
		return *this;
	}
	FString operator+ (FString&& other) const
	{
		return  std::move(FString(*this) += std::move(other));
	}
	FString operator+ (const FString& other) const
	{
		return  std::move(FString(*this) += other);
	}
	FString operator+ (const TCHAR *str) const
	{
		return std::move(FString(*this) += str);
	}
};