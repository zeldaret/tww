
#ifndef F_F_OP_OVERLAP_H_
#define F_F_OP_OVERLAP_H_

#include "f_pc/f_pc_leaf.h"
#include "f_pc/f_pc_manager.h"

extern leafdraw_method_class g_fopOvlp_Method;

inline s16 fopOvlpM_GetName(void* ovlp) {
    return fpcM_GetName(ovlp);
}

#endif
