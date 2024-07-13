#include "dolphin/types.h"
#include "string.h"

void* memcpy(void* dst, const void* src, size_t n)
{
	const char* p;
	char* q;
	int rev = ((u32)src < (u32)dst);

	if (!rev) {

		for (p = (const char*)src - 1, q = (char*)dst - 1, n++; --n;)
			*++q = *++p;

	} else {
		for (p = (const char*)src + n, q = (char*)dst + n, n++; --n;)
			*--q = *--p;
	}
	return (dst);
}

void __fill_mem(void* dst, int val, u32 n)
{
	u32 v = (u8)val;
	u32 i;

	((u8*)dst) = ((u8*)dst) - 1;

	if (n >= 32) {
		i = (~(u32)dst) & 3;

		if (i) {
			n -= i;

			do
				*++(((u8*)dst)) = v;
			while (--i);
		}

		if (v)
			v |= v << 24 | v << 16 | v << 8;

		((u32*)dst) = ((u32*)(((u8*)dst) + 1)) - 1;

		i = n >> 5;

		if (i)
			do {
				*++(((u32*)dst)) = v;
				*++(((u32*)dst)) = v;
				*++(((u32*)dst)) = v;
				*++(((u32*)dst)) = v;
				*++(((u32*)dst)) = v;
				*++(((u32*)dst)) = v;
				*++(((u32*)dst)) = v;
				*++(((u32*)dst)) = v;
			} while (--i);

		i = (n & 31) >> 2;

		if (i)
			do
				*++(((u32*)dst)) = v;
			while (--i);

		((u8*)dst) = ((u8*)(((u32*)dst) + 1)) - 1;

		n = n & 3;
	}

	if (n)
		do
			*++(((u8*)dst)) = v;
		while (--n);

	return;
}

void* memset(void* dst, int val, size_t n)
{
	__fill_mem(dst, val, n);

	return (dst);
}