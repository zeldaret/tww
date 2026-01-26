#include "float.h"

unsigned long __float_nan[]     = { 0x7FFFFFFF };
unsigned long __float_huge[]    = { 0x7F800000 };
#if VERSION == VERSION_DEMO
unsigned long __double_max[]    = { 0x7FEFFFFF, 0xFFFFFFFF };
unsigned long __double_huge[]   = { 0x7FF00000, 0 };
unsigned long __extended_min[]  = { 0x00100000, 0 };
unsigned long __extended_max[]  = { 0x7FEFFFFF, 0xFFFFFFFF };
#endif
