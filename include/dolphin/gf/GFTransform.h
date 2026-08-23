#ifndef GFTRANSFORM_H
#define GFTRANSFORM_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/mtx/mtx.h"

#define CP_MTX_REG_A_ID 0x30
#define CP_MTX_REG_B_ID 0x40

#define XF_REG_MATRIXINDEX0_ID 0x1018
#define XF_REG_MATRIXINDEX1_ID 0x1019
#define XF_REG_PROJECTIONA_ID 0x1020
#define XF_REG_PROJECTIONB_ID 0x1021
#define XF_REG_PROJECTIONC_ID 0x1022
#define XF_REG_PROJECTIOND_ID 0x1023
#define XF_REG_PROJECTIONE_ID 0x1024
#define XF_REG_PROJECTIONF_ID 0x1025
#define XF_REG_PROJECTORTHO_ID 0x1026

#define CP_MTX_REG_A(pn, t0, t1, t2, t3) \
    ( \
        (u32)(pn) << 0 | \
        (u32)(t0) << 6 | \
        (u32)(t1) << 12 | \
        (u32)(t2) << 18 | \
        (u32)(t3) << 24 \
    )

#define CP_MTX_REG_B(t4, t5, t6, t7) \
    ( \
        (u32)(t4) << 0 | \
        (u32)(t5) << 6 | \
        (u32)(t6) << 12 | \
        (u32)(t7) << 18 \
    )

void GFLoadPosMtxImm(MtxP, u32);
void GFLoadNrmMtxImm(MtxP, u32);
void GFSetCurrentMtx(u32, u32, u32, u32, u32, u32, u32, u32, u32);

#endif /* GFTRANSFORM_H */
