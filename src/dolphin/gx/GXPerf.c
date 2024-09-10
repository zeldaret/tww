#include "dolphin/gx/GXPerf.h"
#include "dolphin/gx/GX.h"

void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1) {
    switch (__GXData->perf0) {
    case GX_PERF0_VERTICES:
    case GX_PERF0_CLIP_VTX:
    case GX_PERF0_CLIP_CLKS:
    case GX_PERF0_XF_WAIT_IN:
    case GX_PERF0_XF_WAIT_OUT:
    case GX_PERF0_XF_XFRM_CLKS:
    case GX_PERF0_XF_LIT_CLKS:
    case GX_PERF0_XF_BOT_CLKS:
    case GX_PERF0_XF_REGLD_CLKS:
    case GX_PERF0_XF_REGRD_CLKS:
    case GX_PERF0_CLIP_RATIO:
    case GX_PERF0_CLOCKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0);
        break;

    case GX_PERF0_TRIANGLES:
    case GX_PERF0_TRIANGLES_CULLED:
    case GX_PERF0_TRIANGLES_PASSED:
    case GX_PERF0_TRIANGLES_SCISSORED:
    case GX_PERF0_TRIANGLES_0TEX:
    case GX_PERF0_TRIANGLES_1TEX:
    case GX_PERF0_TRIANGLES_2TEX:
    case GX_PERF0_TRIANGLES_3TEX:
    case GX_PERF0_TRIANGLES_4TEX:
    case GX_PERF0_TRIANGLES_5TEX:
    case GX_PERF0_TRIANGLES_6TEX:
    case GX_PERF0_TRIANGLES_7TEX:
    case GX_PERF0_TRIANGLES_8TEX:
    case GX_PERF0_TRIANGLES_0CLR:
    case GX_PERF0_TRIANGLES_1CLR:
    case GX_PERF0_TRIANGLES_2CLR:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x23000000);
        break;

    case GX_PERF0_QUAD_0CVG:
    case GX_PERF0_QUAD_NON0CVG:
    case GX_PERF0_QUAD_1CVG:
    case GX_PERF0_QUAD_2CVG:
    case GX_PERF0_QUAD_3CVG:
    case GX_PERF0_QUAD_4CVG:
    case GX_PERF0_AVG_QUAD_CNT:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x24000000);
        break;

    case GX_PERF0_NONE:
        break;
    }

    switch (__GXData->perf1) {
    case GX_PERF1_TEXELS:
    case GX_PERF1_TX_IDLE:
    case GX_PERF1_TX_REGS:
    case GX_PERF1_TX_MEMSTALL:
    case GX_PERF1_TC_CHECK1_2:
    case GX_PERF1_TC_CHECK3_4:
    case GX_PERF1_TC_CHECK5_6:
    case GX_PERF1_TC_CHECK7_8:
    case GX_PERF1_TC_MISS:
    case GX_PERF1_CLOCKS:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000000);
        break;

    case GX_PERF1_VC_ELEMQ_FULL:
    case GX_PERF1_VC_MISSQ_FULL:
    case GX_PERF1_VC_MEMREQ_FULL:
    case GX_PERF1_VC_STATUS7:
    case GX_PERF1_VC_MISSREP_FULL:
    case GX_PERF1_VC_STREAMBUF_LOW:
    case GX_PERF1_VC_ALL_STALLS:
    case GX_PERF1_VERTICES:
        FAST_FLAG_SET(__GXData->perfSel, 0, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;

    case GX_PERF1_FIFO_REQ:
    case GX_PERF1_CALL_REQ:
    case GX_PERF1_VC_MISS_REQ:
    case GX_PERF1_CP_ALL_REQ:
        GX_SET_CP_REG(3, 0);
        break;

    case GX_PERF1_NONE:
        break;
    }

    __GXData->perf0 = perf0;

    switch (__GXData->perf0) {
    case GX_PERF0_VERTICES:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x273);
        break;
    case GX_PERF0_CLIP_VTX:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x14A);
        break;
    case GX_PERF0_CLIP_CLKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x16B);
        break;
    case GX_PERF0_XF_WAIT_IN:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x84);
        break;
    case GX_PERF0_XF_WAIT_OUT:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0xC6);
        break;
    case GX_PERF0_XF_XFRM_CLKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x210);
        break;
    case GX_PERF0_XF_LIT_CLKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x252);
        break;
    case GX_PERF0_XF_BOT_CLKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x231);
        break;
    case GX_PERF0_XF_REGLD_CLKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x1AD);
        break;
    case GX_PERF0_XF_REGRD_CLKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x1CE);
        break;
    case GX_PERF0_CLOCKS:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x21);
        break;
    case GX_PERF0_CLIP_RATIO:
        GX_WRITE_U8(0x10);
        GX_WRITE_U32(0x1006);
        GX_WRITE_U32(0x153);
        break;

    case GX_PERF0_TRIANGLES:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300AE7F);
        break;
    case GX_PERF0_TRIANGLES_CULLED:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x23008E7F);
        break;
    case GX_PERF0_TRIANGLES_PASSED:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x23009E7F);
        break;
    case GX_PERF0_TRIANGLES_SCISSORED:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x23001E7F);
        break;
    case GX_PERF0_TRIANGLES_0TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300AC3F);
        break;
    case GX_PERF0_TRIANGLES_1TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300AC7F);
        break;
    case GX_PERF0_TRIANGLES_2TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300ACBF);
        break;
    case GX_PERF0_TRIANGLES_3TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300ACFF);
        break;
    case GX_PERF0_TRIANGLES_4TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300AD3F);
        break;
    case GX_PERF0_TRIANGLES_5TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300AD7F);
        break;
    case GX_PERF0_TRIANGLES_6TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300ADBF);
        break;
    case GX_PERF0_TRIANGLES_7TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300ADFF);
        break;
    case GX_PERF0_TRIANGLES_8TEX:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300AE3F);
        break;
    case GX_PERF0_TRIANGLES_0CLR:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300A27F);
        break;
    case GX_PERF0_TRIANGLES_1CLR:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300A67F);
        break;
    case GX_PERF0_TRIANGLES_2CLR:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2300AA7F);
        break;

    case GX_PERF0_QUAD_0CVG:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2402C0C6);
        break;
    case GX_PERF0_QUAD_NON0CVG:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2402C16B);
        break;
    case GX_PERF0_QUAD_1CVG:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2402C0E7);
        break;
    case GX_PERF0_QUAD_2CVG:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2402C108);
        break;
    case GX_PERF0_QUAD_3CVG:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2402C129);
        break;
    case GX_PERF0_QUAD_4CVG:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2402C14A);
        break;
    case GX_PERF0_AVG_QUAD_CNT:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x2402C1AD);
        break;

    case GX_PERF0_NONE:
        break;
    }

    __GXData->perf1 = perf1;

    switch (__GXData->perf1) {
    case GX_PERF1_TEXELS:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000042);
        break;
    case GX_PERF1_TX_IDLE:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000084);
        break;
    case GX_PERF1_TX_REGS:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000063);
        break;
    case GX_PERF1_TX_MEMSTALL:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000129);
        break;
    case GX_PERF1_TC_MISS:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000252);
        break;
    case GX_PERF1_CLOCKS:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000021);
        break;
    case GX_PERF1_TC_CHECK1_2:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x6700014B);
        break;
    case GX_PERF1_TC_CHECK3_4:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x6700018D);
        break;
    case GX_PERF1_TC_CHECK5_6:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x670001CF);
        break;
    case GX_PERF1_TC_CHECK7_8:
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(0x67000211);
        break;

    case GX_PERF1_VC_ELEMQ_FULL:
        FAST_FLAG_SET(__GXData->perfSel, 2, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;
    case GX_PERF1_VC_MISSQ_FULL:
        FAST_FLAG_SET(__GXData->perfSel, 3, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;
    case GX_PERF1_VC_MEMREQ_FULL:
        FAST_FLAG_SET(__GXData->perfSel, 4, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;
    case GX_PERF1_VC_STATUS7:
        FAST_FLAG_SET(__GXData->perfSel, 5, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;
    case GX_PERF1_VC_MISSREP_FULL:
        FAST_FLAG_SET(__GXData->perfSel, 6, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;
    case GX_PERF1_VC_STREAMBUF_LOW:
        FAST_FLAG_SET(__GXData->perfSel, 7, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;
    case GX_PERF1_VC_ALL_STALLS:
        FAST_FLAG_SET(__GXData->perfSel, 9, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;
    case GX_PERF1_VERTICES:
        FAST_FLAG_SET(__GXData->perfSel, 8, 4, 4);
        GX_WRITE_U8(8);
        GX_WRITE_U8(32);
        GX_WRITE_U32(__GXData->perfSel);
        break;

    case GX_PERF1_FIFO_REQ:
        GX_SET_CP_REG(3, 2);
        break;
    case GX_PERF1_CALL_REQ:
        GX_SET_CP_REG(3, 3);
        break;
    case GX_PERF1_VC_MISS_REQ:
        GX_SET_CP_REG(3, 4);
        break;
    case GX_PERF1_CP_ALL_REQ:
        GX_SET_CP_REG(3, 5);
        break;

    case GX_PERF1_NONE:
        break;
    }

    __GXData->bpSentNot = GX_FALSE;
}

void GXClearGPMetric(void) {
    GX_SET_CP_REG(2, 4);
}

#pragma scheduling off
void GXReadXfRasMetric(u32* xfWaitIn, u32* xfWaitOut, u32* rasBusy, u32* clocks) {
    *rasBusy = GXReadCPReg(32, 33);
    *clocks = GXReadCPReg(34, 35);
    *xfWaitIn = GXReadCPReg(36, 37);
    *xfWaitOut = GXReadCPReg(38, 39);
}
#pragma scheduling reset
