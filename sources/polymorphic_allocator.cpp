#include "polymorphic_allocator.hpp"

#include <cstdlib>

#include <EABase/eabase.h>

namespace LotusEA
{
PolymorphicAllocator::PolymorphicAllocator(char const*) noexcept
{
}

PolymorphicAllocator::PolymorphicAllocator(
	PolymorphicAllocator const &other,
	char const*)
: PolymorphicAllocator(other)
{
}

void *PolymorphicAllocator::allocate(size_t size, int)
{
	return allocate(size, alignof(void*), 0, 0);
}

void *PolymorphicAllocator::allocate(
	size_t size,
	size_t alignment,
	size_t offset,
	int)
{
	EASTL_ASSERT_MSG(
		!(!(alignment == 0) && !(alignment & (alignment - 1))),
		"alignment must be a power of 2!");

	size_t const adjustedAlignment = ((alignment > EA_PLATFORM_PTR_SIZE)
		? alignment
		: EA_PLATFORM_PTR_SIZE) - 1;

	size_t const gap = (0 - offset) & (EA_PLATFORM_PTR_SIZE - 1);

	size_t const infoSize = EA_PLATFORM_PTR_SIZE + gap + adjustedAlignment;
	size_t const blockSize = infoSize + size;
	EASTL_ASSERT(size <= blockSize); // size can be 0

	void *const memory = malloc(blockSize);
	if(!memory)
		return nullptr;

	uintptr_t const baseAddress = reinterpret_cast<uintptr_t>(memory);

	uintptr_t const returnAddress =
		((baseAddress + infoSize + offset) & ~adjustedAlignment) - offset;

	reinterpret_cast<uintptr_t*>(returnAddress - gap)[-1] = baseAddress;

	return reinterpret_cast<void*>(returnAddress);
}

void PolymorphicAllocator::deallocate(void *pointer, size_t)
{
	if(!pointer)
		return;

	uintptr_t const alignedAddress = reinterpret_cast<uintptr_t>(pointer);

	// Silence conversion warning
	constexpr uintptr_t const pointerSize = EA_PLATFORM_PTR_SIZE;

	uintptr_t const baseAddressPointer =
		(alignedAddress & ~(pointerSize - 1)) - pointerSize;

	uintptr_t const baseAddress =
		*reinterpret_cast<uintptr_t*>(baseAddressPointer);

	free(reinterpret_cast<void*>(baseAddress));
}

char const *PolymorphicAllocator::get_name() const
{
	return "LotusEA PolymorphicAllocator";
}

void PolymorphicAllocator::set_name(char const*)
{
}

bool PolymorphicAllocator::Equals(PolymorphicAllocator const &) const
{
	return true;
}

EASTL_API PolymorphicAllocator *GetDefaultAllocator()
{
	static PolymorphicAllocator globalAllocator;
	return &globalAllocator;
}
} // namespace LotusEA
