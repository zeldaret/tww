#ifndef F_F_OP_KANKYO_MNG_H_
#define F_F_OP_KANKYO_MNG_H_

#include "SSystem/SComponent/c_xyz.h"
#include "f_pc/f_pc_manager.h"

struct fopKyM_prm_class {
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ cXyz mScale;
    /* 0x18 */ int mParam;
};  // Size: 0x1C

typedef int (*fopKyM_CreateFunc)(void*);

void fopKyM_Delete(void* param_1);
int fopKyM_Create(s16 param_1, fopKyM_CreateFunc param_2, void* param_3);
int fopKyM_create(s16 i_procName, int i_param, cXyz* i_pos, cXyz* i_scale, fopKyM_CreateFunc i_createFunc);
base_process_class* fopKyM_fastCreate(s16 param_0, int param_1, cXyz* param_2, cXyz* param_3,
                                      fopKyM_CreateFunc);
int fopKyM_createWpillar(cXyz const* i_pos, f32 scaleXZ, f32 scaleY, int i_param);

inline void* fopKyM_GetAppend(void* param_0) {
    return fpcM_GetAppend(param_0);
}

#endif
