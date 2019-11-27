#ifndef a75afc52_7c61_c5a3_1610_62cb4287ea3d
#define a75afc52_7c61_c5a3_1610_62cb4287ea3d

#ifdef BUILDING_LOTUSEA
// Will be force included in other projects.
#include "config.hpp"
#endif
#include <EASTL/internal/config.h>
#include <EASTL/unique_ptr.h>

#include <LotusEA/smart_ptr.hpp>

namespace LotusEA
{
template<typename T>
using UniquePtr = eastl::unique_ptr<T, DefaultDeleter>;

template<typename T, typename... Args>
UniquePtr<T> MakeUnique(
	Args &&...arguments)
{
	void *const memory = Details::AllocateOrThrow(sizeof(T));

	return UniquePtr<T>(
		new (memory) T(std::forward<Args>(arguments)...));
}

template<typename T, typename... Args>
UniquePtr<T> MakeUniqueAligned(
	size_t alignment,
	Args &&...arguments)
{
	void *const memory = Details::AllocateOrThrow(sizeof(T), alignment);

	return UniquePtr<T>(
		new (memory) T(std::forward<Args>(arguments)...));
}

template<typename T, typename... Args>
UniquePtr<T> MakeUniqueAlignedOffset(
	size_t alignment,
	size_t offset,
	Args &&...arguments)
{
	void *const memory = Details::AllocateOrThrow(sizeof(T), alignment, offset);

	return UniquePtr<T>(
		new (memory) T(std::forward<Args>(arguments)...));
}

template<typename T, typename... Args>
UniquePtr<T> MakeUniqueAlignedOffsetFlags(
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

	return UniquePtr<T>(
		new (memory) T(std::forward<Args>(arguments)...));
}
} // namespace LotusEA

#endif // a75afc52_7c61_c5a3_1610_62cb4287ea3d
