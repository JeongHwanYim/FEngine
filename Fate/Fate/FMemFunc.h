#pragma once

#include "FIMemAllocator.h"

namespace FTL
{
	//Fibonacci-value precompute in compile time.
	template< unsigned int N > struct Fib { enum { Val = Fib<N - 1>::Val +Fib<N - 2>::Val }; };
	template<> struct Fib<1> { enum { Val = 1 }; };
	template<> struct Fib<0> { enum { Val = 0 }; };

	static const size_t FibArray[] = {
		Fib<0>::Val, Fib<1>::Val, Fib<2>::Val,
		Fib<3>::Val, Fib<4>::Val, Fib<5>::Val,
		Fib<6>::Val, Fib<7>::Val, Fib<8>::Val,
		Fib<9>::Val, Fib<10>::Val, Fib<11>::Val,
		Fib<12>::Val, Fib<13>::Val, Fib<14>::Val,
		Fib<15>::Val, Fib<16>::Val, Fib<17>::Val,
		Fib<18>::Val, Fib<19>::Val, Fib<20>::Val,
		Fib<21>::Val, Fib<22>::Val, Fib<23>::Val,
		Fib<24>::Val, Fib<25>::Val, Fib<26>::Val,
		Fib<27>::Val, Fib<28>::Val, Fib<29>::Val,
		Fib<30>::Val, Fib<31>::Val, Fib<32>::Val,
		Fib<33>::Val, Fib<34>::Val, Fib<35>::Val,
		Fib<36>::Val, Fib<37>::Val, Fib<38>::Val
	};
}

namespace FTL
{
	template<typename AllocType>
	__forceinline AllocType* Alloc(size_t nSize = 1)
	{
		extern IMemAllocator* gAllocator;
		return (AllocType *)gAllocator->Alloc(nSize * sizeof(AllocType));
	}

	template<typename AllocType>
	__forceinline void Free(AllocType* &Pointer)
	{
		extern IMemAllocator* gAllocator;
		gAllocator->Free(Pointer);

		Pointer = nullptr;
	}

	template<typename DataType>
	__forceinline void memcpy(DataType* Dest, const DataType* Src, size_t nSize = 1)
	{
		::memcpy((void *)Dest, (void *)Src, sizeof(DataType)*nSize);
	}

	template<typename DataType>
	__forceinline void memZero(DataType* Dest, size_t nSize = 1)
	{
		::memset((void *)Dest, 0, sizeof(DataType)*nSize);
	}

	__forceinline bool NeedIncreaseSize(size_t nCurSize, size_t nMaxSize)
	{
		return nCurSize >= nMaxSize;
	}

	__forceinline bool NeedDecreaseSize(size_t nCurSize, size_t nMaxSize)
	{
		return nCurSize * 3 < nMaxSize;
	}

	__forceinline size_t GetNextSize(size_t nSize)
	{
		return nSize * 2 + 1;
	}

	__forceinline size_t GetPrevSize(size_t nSize)
	{
		return nSize / 2 + 1;
	}
}