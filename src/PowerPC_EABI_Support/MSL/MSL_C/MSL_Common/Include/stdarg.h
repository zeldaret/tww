#ifndef _MSL_COMMON_STDARG_H
#define _MSL_COMMON_STDARG_H

#include "__va_arg.h"

#ifdef __cplusplus
namespace std {
#endif

struct __tag_va_List {
    va_list list;
};

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_STDARG_H */
