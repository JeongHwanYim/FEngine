#pragma once

namespace FTL
{
	class IMemAllocator
	{
	public:
		virtual void* Alloc(size_t nSize) = 0;
		virtual void Free(void* Address) = 0;
	};
}