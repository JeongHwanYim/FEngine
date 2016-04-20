#pragma once

#include "FMemFunc.h"

#ifndef _countof
#define _countof(x) sizeof(x) / sizeof(x[0])
#endif

template <typename DataType>
class FArray
{
public:
	FArray(size_t nSize) : m_nCurSize(0)
	{
		for (int i = 0; i < _countof(FTL::FibArray); ++i)
		{
			if (nSize <= FTL::FibArray[i])
			{
				m_nSizeIndex = i;
				break;
			}
		}
		m_nMaxSize = FTL::FibArray[m_nSizeIndex];
		m_pPivot = FTL::Alloc<DataType>(m_nMaxSize);
	}

	FArray() : FArray(1) {}
	
	//Copy Constructor
	FArray(const FArray<DataType>& other) : m_nCurSize(other.m_nCurSize), m_nMaxSize(other.m_nMaxSize), m_nSizeIndex(other.m_nSizeIndex)
	{
		m_pPivot = FTL::Alloc<DataType>(m_nMaxSize);
		FTL::memcpy<DataType>(m_pPivot, other.m_pPivot, m_nCurSize);
	}

	//Move Constructor
	FArray(FArray<DataType>&& other) : m_nCurSize(other.m_nCurSize), m_nMaxSize(other.m_nMaxSize), m_nSizeIndex(other.m_nSizeIndex), m_pPivot(other.m_pPivot)
	{
		other.Finalize();
	}

	void Finalize()
	{
		m_nCurSize = 0;
		m_nMaxSize = 0;
		m_nSizeIndex = 0;
		m_pPivot = nullptr;
	}

	void Resize()
	{
		size_t nTempMaxSize = m_nMaxSize;
		DataType* pTempPivot = nullptr;
		// ����� ���� ��� Resize

		while (FTL::NeedIncreaseSize(m_nCurSize, m_nMaxSize) == true)
			m_nMaxSize = FTL::FibArray[++m_nSizeIndex];

		while (FTL::NeedDecreaseSize(m_nCurSize, m_nMaxSize) == true)
			m_nMaxSize = FTL::FibArray[--m_nSizeIndex];

		if (nTempMaxSize == m_nMaxSize)
			return;

		pTempPivot = FTL::Alloc<DataType>(m_nMaxSize);
		FTL::memcpy(pTempPivot, m_pPivot, m_nCurSize);
		FTL::Free(m_pPivot);

		m_pPivot = pTempPivot;
	}

	void push_back(const DataType& Element)
	{
		// ����� ���� ��� Resize
		if (FTL::NeedIncreaseSize(m_nCurSize, m_nMaxSize) == true)
			Resize();

		// ������� ���縦 ��������.
		m_pPivot[m_nCurSize++] = Element;
	}

	void push_back(const FArray<DataType>& other)
	{
		size_t nPrevSize = m_nCurSize;
		m_nCurSize += other.m_nCurSize;
		// ����� ���� ��� Resize
		if (FTL::NeedIncreaseSize(m_nCurSize, m_nMaxSize) == true)
			Resize();

		// ������� ���縦 ��������.
		for (size_t i = 0; i < other.m_nCurSize; ++i)
			m_pPivot[nPrevSize + i] = other.m_pPivot[i];
	}

	void push_back(FArray<DataType>&& other)
	{
		size_t nPrevSize = m_nCurSize;
		m_nCurSize += other.m_nCurSize;
		// ����� ���� ��� Resize
		if (FTL::NeedIncreaseSize(m_nCurSize, m_nMaxSize) == true)
			Resize();

		// �޸� ���縦 �����Ѵ�.
		FTL::memcpy(m_pPivot + nPrevSize, other.m_pPivot, other.m_nCurSize);
		
		other.Finalize();
	}

	void pop_back()
	{
		if (m_nCurSize > 0)
			m_pPivot[--m_nCurSize]::~DataType();

		// �� ���� ���� �޸� ������ �����ְڳ�... ���߿� �����η� ~.~
		if (FTL::NeedDecreaseSize(m_nCurSize, m_nMaxSize) == true)
			Resize();
	}

	size_t Size() { return m_nCurSize; }


	DataType* begin() { return m_pPivot; }
	const DataType* cbegin() const { return m_pPivot; }

	DataType* end() { return m_pPivot + m_nCurSize; }
	const DataType* cend() const { return m_pPivot + m_nCurSize; }

protected:
	size_t m_nCurSize;
	size_t m_nMaxSize;
	size_t m_nSizeIndex;
	DataType* m_pPivot;
};