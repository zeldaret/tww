#ifndef D_A_SWC00_H
#define D_A_SWC00_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class swc00_class : public fopAc_ac_c {};

static inline int daSwc00_getSw1No(swc00_class* i_this) { return fopAcM_GetParam(i_this) & 0xFF; }
static inline int daSwc00_getSw2No(swc00_class* i_this) { return (fopAcM_GetParam(i_this) >> 8) & 0xFF; }
static inline int daSwc00_getType(swc00_class* i_this) { return (fopAcM_GetParam(i_this) >> 0x10) & 0x3; }

#endif /* D_A_SWC00_H */
