#include "base.h"

#define StdPrint(x) printf("%s = %d\n", #x, (int)(x))

struct TestStruct
{
	int a;
	int b;
	int c;
	int d;
};

#include <stdio.h>
int main()
{
	int foo[100];
	for (int i = 0; i < ArrayCount(foo); i++) {
		foo[i] = i;
	}
	StdPrint(ArrayCount(foo));

	int bar[100];
	MemoryCopyArray(bar, foo);
	StdPrint(bar[50]);
	StdPrint(MemoryMatch(foo, bar, sizeof(foo)));
	MemoryZeroArray(bar);
	StdPrint(bar[50]);
	StdPrint(MemoryMatch(foo, bar, sizeof(foo)));

	TestStruct t = {1, 2, 3, 4};
	StdPrint(t.a);
	StdPrint(t.d);
	MemoryZeroStruct(&t);
	StdPrint(t.a);
	StdPrint(t.d);

	StdPrint(Min(1, 10));
	StdPrint(Min(100, 10));
	StdPrint(Max(1, 10));
	StdPrint(Max(100, 10));
	StdPrint(Clamp(1, 10, 100));
	StdPrint(Clamp(1, 0, 100));
	StdPrint(Clamp(1, 500, 100));

#if 0
	printf("cl		= %d\n", COMPILER_CL);
	printf("clang	= %d\n", COMPILER_CLANG);
	printf("gcc		= %d\n", COMPILER_GCC);
	printf("win		= %d\n", OS_WINDOWS);
	printf("lin		= %d\n", OS_LINUX);
	printf("mac		= %d\n", OS_MAC);
	printf("x64		= %d\n", ARCH_X64);
	printf("x86		= %d\n", ARCH_X86);
	printf("arm		= %d\n", ARCH_ARM);
	printf("arm64	= %d\n", ARCH_ARM64);
#endif
	return(0);
}
