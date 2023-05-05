//***********************
//
// Author:	Justin Echols
// Date LM: 5/5/2023
// License: MIT
//
//***********************

// This file is intended for simple checks of the utility/base layer. The base
// layer will be essentially used everywhere, so it will get tested throughout
// development. Which is why we are only doing simple checks ATM.

#include "base.h"
#include "base.cpp"

#define StdPrint(x) printf("%s = %d\n", #x, (s32)(x))
#define StdPrintLL(x) printf("%s = %lld\n", #x, (s64)(x))
#define StdPrintU(x) printf("%s = %u\n", #x, (u32)(x))
#define StdPrintULL(x) printf("%s = %llu\n", #x, (u64)(x))
#define StdPrintF(x) printf("%s = %f\n", #x, (f32)(x))

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

	StdPrint(OffsetOfMember(TestStruct, a));
	StdPrint(OffsetOfMember(TestStruct, b));
	StdPrint(OffsetOfMember(TestStruct, c));
	StdPrint(OffsetOfMember(TestStruct, d));

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

	StdPrint(min_s8);
	StdPrint(min_s16);
	StdPrint(min_s32);
	StdPrintLL(min_s64);

	StdPrint(max_s8);
	StdPrint(max_s16);
	StdPrint(max_s32);
	StdPrintLL(max_s64);

	f32 inf = inf_f32();
	f32 neg_inf = neg_inf_f32();
	StdPrintF(inf);
	StdPrintF(neg_inf);

	return(0);
}
