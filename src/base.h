// TODO: 
// - Helper macros
// - Linked List Macros
// - Basic types
// - Variadic functions
// - Basic Constants
// - Symbolic Constants
// - Compound types
// - Data access flags
// - Time
// - File properties
// - 
#if !defined(BASE_H)

// NOTE(Justin): The compiler macros ipso facto tell us what OS macros to check

#if defined(__clang__)
# define COMPILER_CLANG 1

# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error Missed ARCH
# endif

# if defined(__amd64__)
#  define ARCH_X64 1
# elif defined(__i386__)
#  define ARCH_X86 1
# elif defined(__arm__)
#  define ARCH_ARM 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# else
#  error Missed ARCH
# endif

#elif defined(_MSC_VER)
# define COMPILER_CL 1

# if defined(_WIN32)
#  define OS_WINDOWS 1
# else
#  error Missed OS
# endif

# if defined(_M_AMD64)
#  define ARCH_X64 1
# elif defined(_M_I86)
#  define ARCH_X86 1
# elif defined(_M_ARM)
#  define ARCH_ARM 1
# else
# error Missed ARCH detect
# endif

#elif defined(__GNUC__)
# define COMPILER_GCC 1

# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error Missed OS
# endif

# if defined(__amd64__)
#  define ARCH_X64 1
# elif defined(__i386__)
#  define ARCH_X86 1
# elif defined(__arm__)
#  define ARCH_ARM 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# else
#  error Missed ARCH
# endif

#else
# error Context unresolved for this compiler
#endif

//NOTE(Justin):  
#if !defined(COMPILER_CL)
# define COMPILER _CL 0
#endif
#if !defined(COMPILER_CLANG)
# define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_GCC)
# define COMPILER_GCC 0
#endif
#if !defined(OS_WINDOWS)
# define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
# define OS_LINUX 0
#endif
#if !defined(OS_MAC)
# define OS_MAC 0
#endif
#if !defined(ARCH_X64)
# define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
# define ARCH_X86 0
#endif
#if !defined(ARCH_ARM)
# define ARCH_ARM 0
#endif
#if !defined(ARCH_ARM64)
# define ARCH_ARM64 0
#endif

//Note(Justin): Helper Macros.

#define Statement(S) do{ S }while(0)

#if !defined(AssertBreak)
# define AssertBreak() (*(volatile int *)0 = 0)
#endif

#if ENABLE_ASSERT
# define Assert(c) Statement( if (!(c)){ AssertBreak(); } )
#else
# define Assert(c)
#endif

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Glue_(A, B) A##B
#define Glue(A, B) Glue_(A, B)

#define ArrayCount(a) (sizeof(a) / sizeof(*(a)))

#define IntFromPtr(p) (unsigned long long)((char *)p - (char *)0)
#define PtrFromInt(n) (void *)((char *)0 + (n))

//NOTE(Justin): This Member macro can access a member of a struct. However
// we cannot R/W to the member. Useful for getting offsets.

#define Member(T,m) (((T *)0)->m)
#define OffsetOfMember(T,m) IntFromPtr(&Member(T,m))

#define Min(a,b) (((a) < (b)) ? (a) : (b))
#define Max(a,b) (((a) > (b)) ? (a) : (b))

#define Clamp(a, x, b) (((x) < (a)) ? (a):\
						((b) < (x)) ? (b) : (x))

#define ClampTop(a,b) Min(a,b)
#define ClampBot(a,b) Max(a,b)

#define global static
#define local static
#define function static

#define c_linkage_begin extern "C"{
#define c_linkage_end }
#define c_linkage extern "C"
 
#include <string.h>
#define MemoryZero(p,z) memset((p), 0, (z))
#define MemoryZeroStruct(p) MemoryZero((p), sizeof(*(p)))
#define MemoryZeroArray(p) MemoryZero((p), sizeof(p))
#define MemoryZeroTyped(p,c) MemoryZero((p), sizeof(*(p))*(c))

#define MemoryMatch(a,b,z) (memcmp((a),(b),(z)) == 0)

#define MemoryCopy(d, s, z) memmove((d), (s), (z))
#define MemoryCopyStruct(d,s) MemoryCopy((d),(s),\
											Min(sizeof(*(d)), sizeof(*(s)))

#define MemoryCopyArray(d, s) MemoryCopy((d), (s), Min(sizeof(d), sizeof(s)))
#define MemoryCopyTyped(d, s, c) MemoryCopy((d), (s),\
												Min(sizeof(*(d)), sizeof(*(s)))*(c))
#define BASE_H
#endif
