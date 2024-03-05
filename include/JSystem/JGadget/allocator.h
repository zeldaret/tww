#ifndef _JSYSTEM_JGADGET_ALLOCATOR_H
#define _JSYSTEM_JGADGET_ALLOCATOR_H

#include "dolphin/types.h"

namespace JGadget {
template <typename T>
struct TAllocator {
	static TAllocator get() { }

	inline TAllocator();

	u8 _00;  // _00
	u32 _04; // _04
	u32 _08; // _08
	u32 _0C; // _0C
};

typedef TAllocator<void*> TVoidAllocator;
}; // namespace JGadget

#endif
