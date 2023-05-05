// TODO(Justin): 
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

//
// NOTE(Justin): Helper Macros.
//

// NOTE(Justin): Converts preprocessor statements 
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

// NOTE(Justin): This Member macro can access a member of a struct. However
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
#define MemoryCopyStruct(d,s) MemoryCopy((d),(s), Min(sizeof(*(d)), sizeof(*(s))))

#define MemoryCopyArray(d, s) MemoryCopy((d), (s), Min(sizeof(d), sizeof(s)))
#define MemoryCopyTyped(d, s, c) MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s)))*(c))

//Note(Justin): Basic types

#include <stdint.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef s8 b8;
typedef s16 b16;
typedef s32 b32;
typedef s64 b64;

typedef float f32;
typedef double f64;

// Note(Justin): VoidFunc type for working with, for example,
// tables of function pointers. For func ptr size correctness.

typedef void VoidFunc(void);


//
// NOTE(Justin): Useful constants
//

global s8 min_s8	= (s8)0x80;
global s16 min_s16 = (s16)0x8000;
global s32 min_s32 = (s32)0x80000000;
global s64 min_s64 = (s64)0x8000000000000000llu;

global s8 max_s8	= (s8)0x7F;
global s16 max_s16 = (s16)0x7FFF;
global s32 max_s32 = (s32)0x7FFFFFFF;
global s64 max_s64 = (s64)0x7FFFFFFFFFFFFFFFllu;

global u8 max_u8	= 0xFF;
global u16 max_u16 = 0xFFFF;
global u32 max_u32 = 0xFFFFFFFF;
global u64 max_u64 = 0xFFFFFFFFFFFFFFFFllu;

global f32 epsilon_f32 = 1.1920929e-7f;
global f32 pi_f32 = 3.14159265359f;
global f32 tau_f32 = 6.28318530718f;
global f32 e_f32 = 2.71828182846f;
global f32 gold_big_f32 = 1.61803398875f;
global f32 gold_small_f32 = 0.61803398875f;


global f64 epsilon_f64 = 2.220446e-16;
global f64 pi_f64 = 3.14159265359;
global f64 tau_f64 = 6.28318530718;
global f64 e_f64 = 2.71828182846;
global f64 gold_big_f64 = 1.61803398875;
global f64 gold_small_f64 = 0.61803398875;

//
// Note(Justin): Float constants in order not to have to include anything
// unecessarily.
//

function f32 inf_f32(void);
function f32 neg_inf_f32(void);
function f64 inf_f64(void);
function f64 neg_inf_f64(void);



//
// Note(Justin): Math functions. ATM will use CRT, but replace eventually.
//

function f32 abs_f32(f32 x);
function f64 abs_f64(f64 x);

function f32 sqrt_f32(f32 x);
function f32 sin_f32(f32 angle);
function f32 cos_f32(f32 angle);
function f32 tan_f32(f32 angle);
function f32 ln_f32(f32 x);

function f64 sqrt_f64(f64 x);
function f64 sin_f64(f64 angle);
function f64 cos_f64(f64 angle);
function f64 tan_f64(f64 angle);
function f64 ln_f64(f64 x);


//
// NOTE(Justin): Compound types
//

union V2S32
{
	struct
	{
		s32 x;
		s32 y;
	};
	s32 v[2];
};

union V3S32
{
	struct
	{
		s32 x;
		s32 y;
		s32 z;
	};
	s32 v[3];
};

union V4S32
{
	struct
	{
		s32 x;
		s32 y;
		s32 z;
		s32 w;
	};
	s32 v[4];
};

union V2F32
{
	struct
	{
		f32 x;
		f32 y;
	};
	f32 v[2];
};

union V3F32
{
	struct
	{
		f32 x;
		f32 y;
		f32 z;
	};
	f32 v[3];
};


//
// TODO(Justin): Compound type functions
//





















#define BASE_H
#endif
