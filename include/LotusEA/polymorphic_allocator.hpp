#ifndef d02ce476_718d_37a1_87e8_d8ad2e4ce64a
#define d02ce476_718d_37a1_87e8_d8ad2e4ce64a

#ifdef BUILDING_LOTUSEA
// Will be force included in other projects.
#include "config.hpp"
#endif
#include <EASTL/internal/config.h>
#include <EASTL/type_traits.h>

namespace LotusEA
{
// A simple polymorphic allocator that ignores all flags and uses malloc/free.
// Subject to change.
class EASTL_API PolymorphicAllocator
{
public:
	PolymorphicAllocator() noexcept = default;
	EASTL_ALLOCATOR_EXPLICIT PolymorphicAllocator(char const*) noexcept;
	PolymorphicAllocator(PolymorphicAllocator const &other) = default;
	PolymorphicAllocator(PolymorphicAllocator const &other, char const*);
	PolymorphicAllocator(PolymorphicAllocator &&other) = default;
	virtual ~PolymorphicAllocator() noexcept = default;

	PolymorphicAllocator &operator=(PolymorphicAllocator const &other) = default;
	PolymorphicAllocator &operator=(PolymorphicAllocator &&other) noexcept = default;

	virtual void *allocate(size_t size, int flags = 0);
	virtual void *allocate(
		size_t size,
		size_t alignment,
		size_t offset = 0, // !!!Deviates from default EASTL allocator interface
		int flags = 0);
	virtual void deallocate(void *pointer, size_t size);

	virtual char const *get_name() const;
	virtual void set_name(char const*);

	// Not part of the EASTL allocator interface.
	virtual bool Equals(PolymorphicAllocator const &other) const;
};

static_assert(eastl::is_copy_constructible_v<PolymorphicAllocator>);
static_assert(eastl::is_copy_assignable_v<PolymorphicAllocator>);
static_assert(!eastl::is_trivially_copyable_v<PolymorphicAllocator>);

static_assert(eastl::is_move_constructible_v<PolymorphicAllocator>);
static_assert(eastl::is_move_assignable_v<PolymorphicAllocator>);

inline bool operator==(PolymorphicAllocator const &a, PolymorphicAllocator const &b)
{
	return a.Equals(b);
}

inline bool operator!=(PolymorphicAllocator const &a, PolymorphicAllocator const &b)
{
	return !a.Equals(b);
}

EASTL_API PolymorphicAllocator* GetDefaultAllocator();
} // namespace LotusEA

#endif // d02ce476_718d_37a1_87e8_d8ad2e4ce64a
