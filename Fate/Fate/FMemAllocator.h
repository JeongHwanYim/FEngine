#pragma once

#include <cstdlib>
#include "FIMemAllocator.h"

namespace FTL
{
	class StdAllocator : public IMemAllocator
	{
	public:
		virtual void* Alloc(size_t nSize) { return ::malloc(nSize); }
		virtual void Free(void* Address) { ::free(Address); }
	};
}