#ifndef d15616fc_2ae8_d969_ac7e_cb432b640a85
#define d15616fc_2ae8_d969_ac7e_cb432b640a85

// RTTI and exceptions
#define EASTL_RTTI_ENABLED 0
#define EASTL_EXCEPTIONS_ENABLED 1

// Strings
#define EASTL_STRING_OPT_LENGTH_ERRORS 0
#define EASTL_STRING_OPT_RANGE_ERRORS 0
#define EASTL_STRING_OPT_ARGUMENT_ERRORS 0

// Allocators
#define EASTL_ALLOCATOR_COPY_ENABLED 1
#define EASTL_ALLOCATOR_EXPLICIT_ENABLED 1
#define EASTLAllocatorType LotusEA::PolymorphicAllocator
#define EASTLAllocatorDefault LotusEA::GetDefaultAllocator
#define EASTL_USER_DEFINED_ALLOCATOR
#define LOTUSEA_DEFAULT_ALLOCATOR_HEADER <LotusEA/polymorphic_allocator.hpp>

#endif // d15616fc_2ae8_d969_ac7e_cb432b640a85
