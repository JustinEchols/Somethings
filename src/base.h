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

#define StackStringBufferName(name) Glue(foo, name)
#define StackString(name, count) char StackStringBufferName(name)[count];\
	string name;\
name.size = count;\
name.length = 0;\
name.buff = StackStringBufferName(name);

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

#define CLinkageBegin extern "C"{
#define CLinkageEnd }
#define CLinkage extern "C"
 
#include <string.h>
#define Zero(p,z) memset((p), 0, (z))
#define ZeroStruct(p) Zero((p), sizeof(*(p)))
#define ZeroArray(p) Zero((p), sizeof(p))
#define ZeroTyped(p,c) MemoryZero((p), sizeof(*(p))*(c))

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

global s8 S8Min= (s8)0x80;
global s16 S16Min = (s16)0x8000;
global s32 S32Min = (s32)0x80000000;
global s64 S64Min = (s64)0x8000000000000000llu;

global s8 S8Max = (s8)0x7F;
global s16 S16Max = (s16)0x7FFF;
global s32 S32Max = (s32)0x7FFFFFFF;
global s64 S64Max = (s64)0x7FFFFFFFFFFFFFFFllu;

global u8 U8Max = 0xFF;
global u16 U16Max = 0xFFFF;
global u32 U32Max = 0xFFFFFFFF;
global u64 U64Max = 0xFFFFFFFFFFFFFFFFllu;

global f32 Epsilon32 = 1.1920929e-7f;
global f32 PI32 = 3.14159265359f;
global f32 Tau32 = 6.28318530718f;
global f32 E32 = 2.71828182846f;
global f32 GoldenRatioLarge32 = 1.61803398875f;
global f32 GoldenRatioSmall32 = 0.61803398875f;


global f64 Epsilon64 = 2.220446e-16;
global f64 PI64 = 3.14159265359;
global f64 Tau64 = 6.28318530718;
global f64 E64 = 2.71828182846;
global f64 GoldeRatioLarge64 = 1.61803398875;
global f64 GolenRatioSmall64 = 0.61803398875;

//
// Note(Justin): Float constants in order not to have to include anything
// unecessarily.
//

function f32 F32Min(void);
function f32 F32MinNegative(void);
function f64 F64Min(void);
function f64 F64MinNegative(void);

//
// Note(Justin): Math functions. ATM will use CRT, but replace eventually.
//

function f32 AbsF32(f32 x);
function f64 AbsF64(f64 x);

function f32 Sqrt32(f32 x);
function f32 Sin32(f32 angle);
function f32 Cos32(f32 angle);
function f32 Tan32(f32 angle);
function f32 Ln32(f32 x);

function f64 Sqrt64(f64 x);
function f64 Sin64(f64 angle);
function f64 Cos64(f64 angle);
function f64 Tan64(f64 angle);
function f64 Ln64(f64 x);


//
// NOTE(Justin): Compound types
//

struct string
{
	u32 Size;
	u32 Length;
	char *Buff;
};

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
