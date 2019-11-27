#ifndef afcf07eb_3805_d872_484e_d073a275378d
#define afcf07eb_3805_d872_484e_d073a275378d

#ifdef BUILDING_LOTUSEA
// Will be force included in other projects.
#include "config.hpp"
#endif
#include <EASTL/internal/config.h>

#ifdef EASTL_EXCEPTIONS_ENABLED
#include <stdexcept>
#include <new>
#endif // EASTL_EXCEPTIONS_ENABLED

#include LOTUSEA_DEFAULT_ALLOCATOR_HEADER

namespace LotusEA
{
struct DefaultDeleter
{
	void operator()(void *pointer)
	{
		EASTLAllocatorDefault()->deallocate(pointer, 0);
	}
}

namespace Details
{
inline void *AllocateOrThrow(
	size_t size,
	size_t alignment = alignof(void*),
	size_t offset = 0,
	int flags = 0)
{
	void *memory = nullptr;

#ifdef EASTL_EXCEPTIONS_ENABLED
	do
	{
#endif // EASTL_EXCEPTIONS_ENABLED
		memory = GetDefaultAllocator()->allocate(size, alignment, offset, flags);

#ifdef EASTL_EXCEPTIONS_ENABLED
		if(!memory)
		{
			std::new_handler handler = std::get_new_handler();

			if(handler)
				handler();
			else
				throw std::bad_alloc();
		}
	} while(!memory);
#endif // EASTL_EXCEPTIONS_ENABLED

	return memory;
}
} // namespace Details
} // namespace LotusEA

#endif // afcf07eb_3805_d872_484e_d073a275378d
