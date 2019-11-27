#ifndef c64d951b_1ce6_d806_46a6_d3b9f161561a
#define c64d951b_1ce6_d806_46a6_d3b9f161561a

#ifdef BUILDING_LOTUSEA
// Will be force included in other projects.
#include "config.hpp"
#endif
#include <EASTL/internal/config.h>
#include <EASTL/shared_ptr.h>

#include <LotusEA/smart_ptr.hpp>

namespace LotusEA
{
template<typename T, typename... Args>
eastl::shared_ptr<T> MakeShared(
	Args &&...arguments)
{
	void *const memory = Details::AllocateOrThrow(sizeof(T));

	return eastl::shared_ptr<T>(
		new (memory) T(
			std::forward<Args>(arguments)...),
			DefaultDeleter{});
}

template<typename T, typename... Args>
eastl::shared_ptr<T> MakeSharedAligned(
	size_t alignment,
	Args &&...arguments)
{
	void *const memory = Details::AllocateOrThrow(sizeof(T), alignment);

	return eastl::shared_ptr<T>(
		new (memory) T(
			std::forward<Args>(arguments)...),
			DefaultDeleter{});
}

template<typename T, typename... Args>
eastl::shared_ptr<T> MakeSharedAlignedOffset(
	size_t alignment,
	size_t offset,
	Args &&...arguments)
{
	void *const memory = Details::AllocateOrThrow(sizeof(T), alignment, offset);

	return eastl::shared_ptr<T>(
		new (memory) T(
			std::forward<Args>(arguments)...),
			DefaultDeleter{});
}

template<typename T, typename... Args>
eastl::shared_ptr<T> MakeSharedAlignedOffsetFlags(
	size_t alignment,
	size_t offset,
	size_t flags,
	Args &&...arguments)
{
	void *const memory = Details::AllocateOrThrow(
		sizeof(T),
		alignment,
		offset,
		flags);

	return eastl::shared_ptr<T>(
		new (memory) T(
			std::forward<Args>(arguments)...),
			DefaultDeleter{});
}
} // namespace LotusEA

#endif // c64d951b_1ce6_d806_46a6_d3b9f161561a
