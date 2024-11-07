#include "dolphin/gx/GXTransform.h"
#include "dolphin/gx/GX.h"
#include "dolphin/gx/GXInit.h"

static void Copy6Floats(register f32 src[6], register f32 dst[6]) {
    register f32 ps_0, ps_1, ps_2;

    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_st ps_0,  0(dst), 0, 0
        psq_st ps_1,  8(dst), 0, 0
        psq_st ps_2, 16(dst), 0, 0
    }
#endif
    // clang-format on
}

static void WriteProjPS(const register f32 src[6], register volatile void* dst) {
    register f32 ps_0, ps_1, ps_2;

    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_st ps_0,  0(dst), 0, 0
        psq_st ps_1,  0(dst), 0, 0
        psq_st ps_2,  0(dst), 0, 0
    }
#endif
    // clang-format on
}

void GXProject(f32 model_x, f32 model_y, f32 model_z, Mtx model_mtx, f32* proj_mtx, f32* viewpoint,
               f32* screen_x, f32* screen_y, f32* screen_z) {
    f32 sp10[3];
    f32 var_f30;
    f32 var_f29;
    f32 var_f28;
    f32 var_f31;

    sp10[0] = (model_mtx[0][0] * model_x) + (model_mtx[0][1] * model_y) +
              (model_mtx[0][2] * model_z) + model_mtx[0][3];
    sp10[1] = (model_mtx[1][0] * model_x) + (model_mtx[1][1] * model_y) +
              (model_mtx[1][2] * model_z) + model_mtx[1][3];
    sp10[2] = (model_mtx[2][0] * model_x) + (model_mtx[2][1] * model_y) +
              (model_mtx[2][2] * model_z) + model_mtx[2][3];

    if (proj_mtx[0] == 0.0f) {
        var_f30 = (sp10[0] * proj_mtx[1]) + (sp10[2] * proj_mtx[2]);
        var_f29 = (sp10[1] * proj_mtx[3]) + (sp10[2] * proj_mtx[4]);
        var_f28 = proj_mtx[6] + (sp10[2] * proj_mtx[5]);
        var_f31 = 1.0f / -sp10[2];
    } else {
        var_f30 = proj_mtx[2] + (sp10[0] * proj_mtx[1]);
        var_f29 = proj_mtx[4] + (sp10[1] * proj_mtx[3]);
        var_f28 = proj_mtx[6] + (sp10[2] * proj_mtx[5]);
        var_f31 = 1.0f;
    }

    *screen_x = (viewpoint[2] / 2) + (viewpoint[0] + (var_f31 * (var_f30 * viewpoint[2] / 2)));
    *screen_y = (viewpoint[3] / 2) + (viewpoint[1] + (var_f31 * (-var_f29 * viewpoint[3] / 2)));
    *screen_z = viewpoint[5] + (var_f31 * (var_f28 * (viewpoint[5] - viewpoint[4])));
}

void GXSetProjection(const Mtx44 proj, GXProjectionType type) {
    volatile void* fifo;
    u32 reg;
    gx->projType = type;

    gx->projMtx[0] = proj[0][0];
    gx->projMtx[2] = proj[1][1];
    gx->projMtx[4] = proj[2][2];
    gx->projMtx[5] = proj[2][3];

    if (type == GX_ORTHOGRAPHIC) {
        gx->projMtx[1] = proj[0][3];
        gx->projMtx[3] = proj[1][3];
    } else {
        gx->projMtx[1] = proj[0][2];
        gx->projMtx[3] = proj[1][2];
    }


    reg = 0x00061020;
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    GX_WRITE_XF_REG_F(32, gx->projMtx[0]);
    GX_WRITE_XF_REG_F(33, gx->projMtx[1]);
    GX_WRITE_XF_REG_F(34, gx->projMtx[2]);
    GX_WRITE_XF_REG_F(35, gx->projMtx[3]);
    GX_WRITE_XF_REG_F(36, gx->projMtx[4]);
    GX_WRITE_XF_REG_F(37, gx->projMtx[5]);
    GX_WRITE_XF_REG_2(38, gx->projType);

    gx->bpSentNot = GX_TRUE;
}

void GXSetProjectionv(f32* proj) {
    gx->projType = proj[0];
    gx->projMtx[0] = proj[1];
    gx->projMtx[1] = proj[2];
    gx->projMtx[2] = proj[3];
    gx->projMtx[3] = proj[4];
    gx->projMtx[4] = proj[5];
    gx->projMtx[5] = proj[6];


    GX_WRITE_U8(0x10);
    GX_WRITE_U32(0x00061020);
    GX_WRITE_XF_REG_F(32, gx->projMtx[0]);
    GX_WRITE_XF_REG_F(33, gx->projMtx[1]);
    GX_WRITE_XF_REG_F(34, gx->projMtx[2]);
    GX_WRITE_XF_REG_F(35, gx->projMtx[3]);
    GX_WRITE_XF_REG_F(36, gx->projMtx[4]);
    GX_WRITE_XF_REG_F(37, gx->projMtx[5]);
    GX_WRITE_XF_REG_2(38, gx->projType);
    gx->bpSentNot = GX_TRUE;
}

void GXGetProjectionv(f32* proj) {
    proj[0] = gx->projType;
    proj[1] = gx->projMtx[0];
    proj[2] = gx->projMtx[1];
    proj[3] = gx->projMtx[2];
    proj[4] = gx->projMtx[3];
    proj[5] = gx->projMtx[4];
    proj[6] = gx->projMtx[5];
}

static void WriteMTXPS4x3(register volatile void* dst, register const Mtx src) {
    register f32 ps_0, ps_1, ps_2, ps_3, ps_4, ps_5;

    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_l  ps_3, 24(src), 0, 0
        psq_l  ps_4, 32(src), 0, 0
        psq_l  ps_5, 40(src), 0, 0

        psq_st ps_0, 0(dst),  0, 0
        psq_st ps_1, 0(dst),  0, 0
        psq_st ps_2, 0(dst),  0, 0
        psq_st ps_3, 0(dst),  0, 0
        psq_st ps_4, 0(dst),  0, 0
        psq_st ps_5, 0(dst),  0, 0
    }
#endif
    // clang-format on
}

void GXLoadPosMtxImm(Mtx mtx, u32 id) {
    GX_XF_LOAD_REGS(4 * 3 - 1, id * 4 + GX_XF_MEM_POSMTX);
    WriteMTXPS4x3(&GXFIFO, mtx);
}

static void WriteMTXPS3x3(register volatile void* dst, register const Mtx src) {
    register f32 ps_0, ps_1, ps_2, ps_3, ps_4, ps_5;

    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_l  ps_0,  0(src), 0, 0
        lfs    ps_1,  8(src)
        psq_l  ps_2, 16(src), 0, 0
        lfs    ps_3, 24(src)
        psq_l  ps_4, 32(src), 0, 0
        lfs    ps_5, 40(src)

        psq_st ps_0, 0(dst),  0, 0
        stfs   ps_1, 0(dst)
        psq_st ps_2, 0(dst),  0, 0
        stfs   ps_3, 0(dst)
        psq_st ps_4, 0(dst),  0, 0
        stfs   ps_5, 0(dst)
    }
#endif
    // clang-format on
}

void GXLoadNrmMtxImm(Mtx mtx, u32 id) {
    GX_XF_LOAD_REGS(3 * 3 - 1, id * 3 + GX_XF_MEM_NRMMTX);
    WriteMTXPS3x3(&GXFIFO, mtx);
}

void GXSetCurrentMtx(u32 id) {
    GX_SET_REG(gx->matIdxA, id, GX_XF_MTXIDX0_GEOM_ST, GX_XF_MTXIDX0_GEOM_END);
    __GXSetMatrixIndex(GX_VA_PNMTXIDX);
}

static void WriteMTXPS4x2(register volatile void* dst, register const Mtx src) {
    register f32 ps_0, ps_1, ps_2, ps_3;

    // clang-format off
#ifdef __MWERKS__
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_l  ps_3, 24(src), 0, 0

        psq_st ps_0, 0(dst),  0, 0
        psq_st ps_1, 0(dst),  0, 0
        psq_st ps_2, 0(dst),  0, 0
        psq_st ps_3, 0(dst),  0, 0
    }
#endif
    // clang-format on
}

void GXLoadTexMtxImm(const Mtx mtx, u32 id, GXTexMtxType type) {
    u32 addr;
    u32 num;
    u32 reg;

    // Matrix address in XF memory
    addr = id >= GX_PTTEXMTX0 ? (id - GX_PTTEXMTX0) * 4 + GX_XF_MEM_DUALTEXMTX :
                                id * 4 + (u64)GX_XF_MEM_POSMTX;

    // Number of elements in matrix
    num = type == GX_MTX2x4 ? (u64)(2 * 4) : 3 * 4;

    reg = addr | (num - 1) << 16;

    GX_XF_LOAD_REG_HDR(reg);

    if (type == GX_MTX3x4) {
        WriteMTXPS4x3(&GXFIFO, mtx);
    } else {
        WriteMTXPS4x2(&GXFIFO, mtx);
    }
}

void __GXSetViewport(void) {
    f32 a, b, c, d, e, f;
    f32 near, far;

    a = gx->vpWd / 2;
    b = -gx->vpHt / 2;
    d = gx->vpLeft + (gx->vpWd / 2) + 342.0f;
    e = gx->vpTop + (gx->vpHt / 2) + 342.0f;

    near = gx->vpNearz * gx->zScale;
    far = gx->vpFarz * gx->zScale;

    c = far - near;
    f = far + gx->zOffset;

    GX_XF_LOAD_REGS(5, GX_XF_REG_SCALEX);
    GXFIFO.f32 = a;
    GXFIFO.f32 = b;
    GXFIFO.f32 = c;
    GXFIFO.f32 = d;
    GXFIFO.f32 = e;
    GXFIFO.f32 = f;
}

void GXSetViewport(f32 left, f32 top, f32 width, f32 height, f32 nearZ, f32 farZ) {
    gx->vpLeft = left;
    gx->vpTop = top;
    gx->vpWd = width;
    gx->vpHt = height;
    gx->vpNearz = nearZ;
    gx->vpFarz = farZ;
    __GXSetViewport();
    gx->bpSentNot = GX_TRUE;
}

void GXGetViewportv(f32* p) {
    Copy6Floats(&gx->vpLeft, p);
}

void GXSetScissor(u32 left, u32 top, u32 width, u32 height) {
    u32 y1, x1, y2, x2;
    u32 reg;

    y1 = top + 342;
    x1 = left + 342;

    GX_SET_REG(gx->suScis0, y1, GX_BP_SCISSORTL_TOP_ST, GX_BP_SCISSORTL_TOP_END);
    GX_SET_REG(gx->suScis0, x1, GX_BP_SCISSORTL_LEFT_ST, GX_BP_SCISSORTL_LEFT_END);

    y2 = y1 + height - 1;
    x2 = (x1 + width) - 1;

    GX_SET_REG(gx->suScis1, y2, GX_BP_SCISSORBR_BOT_ST, GX_BP_SCISSORBR_BOT_END);
    GX_SET_REG(gx->suScis1, x2, GX_BP_SCISSORBR_RIGHT_ST, GX_BP_SCISSORBR_RIGHT_END);

    GX_BP_LOAD_REG(gx->suScis0);
    GX_BP_LOAD_REG(gx->suScis1);
    gx->bpSentNot = FALSE;
}

void GXGetScissor(u32* left, u32* top, u32* width, u32* height) {
    u32 y1 = (gx->suScis0 & 0x0007FF) >> 0;
    u32 x1 = (gx->suScis0 & 0x7FF000) >> 12;
    u32 y2 = (gx->suScis1 & 0x0007FF) >> 0;
    u32 x2 = (gx->suScis1 & 0x7FF000) >> 12;

    *left = x1 - 0x156;
    *top = y1 - 0x156;
    *width = (x2 - x1) + 1;
    *height = (y2 - y1) + 1;
}

void GXSetScissorBoxOffset(s32 x, s32 y) {
    u32 cmd = 0;
    u32 x1;
    u32 y1;

    x1 = (u32)(x + 342) / 2;
    y1 = (u32)(y + 342) / 2;
    GX_SET_REG(cmd, x1, GX_BP_SCISSOROFS_OX_ST, GX_BP_SCISSOROFS_OX_END);
    GX_SET_REG(cmd, y1, GX_BP_SCISSOROFS_OY_ST, GX_BP_SCISSOROFS_OY_END);

    GX_SET_REG(cmd, GX_BP_REG_SCISSOROFFSET, 0, 7);

    GX_BP_LOAD_REG(cmd);
    gx->bpSentNot = GX_FALSE;
}

void GXSetClipMode(GXClipMode mode) {
    GX_XF_LOAD_REG(GX_XF_REG_CLIPDISABLE, mode);
    gx->bpSentNot = GX_TRUE;
}

void __GXSetMatrixIndex(GXAttr index) {
    // Tex4 and after is stored in XF MatrixIndex1
    if (index < GX_VA_TEX4MTXIDX) {
        GX_CP_LOAD_REG(GX_CP_REG_MTXIDXA, gx->matIdxA);
        GX_XF_LOAD_REG(GX_XF_REG_MATRIXINDEX0, gx->matIdxA);
    } else {
        GX_CP_LOAD_REG(GX_CP_REG_MTXIDXB, gx->matIdxB);
        GX_XF_LOAD_REG(GX_XF_REG_MATRIXINDEX1, gx->matIdxB);
    }

    gx->bpSentNot = GX_TRUE;
}
