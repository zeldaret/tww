#include "dolphin/gd/GDBase.h"
#include "dolphin/gd/GDGeometry.h"
#include "dolphin/gf/GF.h"

void GFLoadPosMtxImm(MtxP mtx, u32 id) {
    GFWriteXFCmdHdr(4 * id, 12);
    GFWrite_f32(mtx[0][0]);
    GFWrite_f32(mtx[0][1]);
    GFWrite_f32(mtx[0][2]);
    GFWrite_f32(mtx[0][3]);
    GFWrite_f32(mtx[1][0]);
    GFWrite_f32(mtx[1][1]);
    GFWrite_f32(mtx[1][2]);
    GFWrite_f32(mtx[1][3]);
    GFWrite_f32(mtx[2][0]);
    GFWrite_f32(mtx[2][1]);
    GFWrite_f32(mtx[2][2]);
    GFWrite_f32(mtx[2][3]);
}

void GFLoadNrmMtxImm(MtxP mtx, u32 id) {
    GFWriteXFCmdHdr(id * 3 + 0x400, 9);
    GFWrite_f32(mtx[0][0]);
    GFWrite_f32(mtx[0][1]);
    GFWrite_f32(mtx[0][2]);
    GFWrite_f32(mtx[1][0]);
    GFWrite_f32(mtx[1][1]);
    GFWrite_f32(mtx[1][2]);
    GFWrite_f32(mtx[2][0]);
    GFWrite_f32(mtx[2][1]);
    GFWrite_f32(mtx[2][2]);
}

void GFSetCurrentMtx(u32 pn, u32 t0, u32 t1, u32 t2, u32 t3, u32 t4, u32 t5, u32 t6, u32 t7) {
    u32 regA;
    u32 regB;

    regA = CP_MTX_REG_A(pn, t0, t1, t2, t3);
    regB = CP_MTX_REG_B(t4, t5, t6, t7);

    GFWriteCPCmd(CP_MTX_REG_A_ID, regA);
    GFWriteCPCmd(CP_MTX_REG_B_ID, regB);
    GFWriteXFCmdHdr(XF_REG_MATRIXINDEX0_ID, 2);
    GFWrite_u32(regA);
    GFWrite_u32(regB);
}
