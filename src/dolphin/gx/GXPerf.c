#include "dolphin/gx/GXPerf.h"
#include "dolphin/gx/GX.h"

void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1) {
    switch (gx->perf0) {
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
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0;
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
        GFWriteBPCmd(0x23000000);
        break;

    case GX_PERF0_QUAD_0CVG:
    case GX_PERF0_QUAD_NON0CVG:
    case GX_PERF0_QUAD_1CVG:
    case GX_PERF0_QUAD_2CVG:
    case GX_PERF0_QUAD_3CVG:
    case GX_PERF0_QUAD_4CVG:
    case GX_PERF0_AVG_QUAD_CNT:
        GFWriteBPCmd(0x24000000);
        break;

    case GX_PERF0_NONE:
        break;
    }

    switch (gx->perf1) {
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
        GFWriteBPCmd(0x67000000);
        break;

    case GX_PERF1_VC_ELEMQ_FULL:
    case GX_PERF1_VC_MISSQ_FULL:
    case GX_PERF1_VC_MEMREQ_FULL:
    case GX_PERF1_VC_STATUS7:
    case GX_PERF1_VC_MISSREP_FULL:
    case GX_PERF1_VC_STREAMBUF_LOW:
    case GX_PERF1_VC_ALL_STALLS:
    case GX_PERF1_VERTICES:
        SET_REG_FIELD(gx->perfSel, 4, 4, 0);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
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

    gx->perf0 = perf0;

    switch (gx->perf0) {
    case GX_PERF0_VERTICES:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x273;
        break;
    case GX_PERF0_CLIP_VTX:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x14A;
        break;
    case GX_PERF0_CLIP_CLKS:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x16B;
        break;
    case GX_PERF0_XF_WAIT_IN:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x84;
        break;
    case GX_PERF0_XF_WAIT_OUT:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0xC6;
        break;
    case GX_PERF0_XF_XFRM_CLKS:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x210;
        break;
    case GX_PERF0_XF_LIT_CLKS:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x252;
        break;
    case GX_PERF0_XF_BOT_CLKS:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x231;
        break;
    case GX_PERF0_XF_REGLD_CLKS:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x1AD;
        break;
    case GX_PERF0_XF_REGRD_CLKS:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x1CE;
        break;
    case GX_PERF0_CLOCKS:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x21;
        break;
    case GX_PERF0_CLIP_RATIO:
        GXFIFO.u8 = 0x10;
        GXFIFO.u32 = 0x1006;
        GXFIFO.u32 = 0x153;
        break;

    case GX_PERF0_TRIANGLES:
        GFWriteBPCmd(0x2300AE7F);
        break;
    case GX_PERF0_TRIANGLES_CULLED:
        GFWriteBPCmd(0x23008E7F);
        break;
    case GX_PERF0_TRIANGLES_PASSED:
        GFWriteBPCmd(0x23009E7F);
        break;
    case GX_PERF0_TRIANGLES_SCISSORED:
        GFWriteBPCmd(0x23001E7F);
        break;
    case GX_PERF0_TRIANGLES_0TEX:
        GFWriteBPCmd(0x2300AC3F);
        break;
    case GX_PERF0_TRIANGLES_1TEX:
        GFWriteBPCmd(0x2300AC7F);
        break;
    case GX_PERF0_TRIANGLES_2TEX:
        GFWriteBPCmd(0x2300ACBF);
        break;
    case GX_PERF0_TRIANGLES_3TEX:
        GFWriteBPCmd(0x2300ACFF);
        break;
    case GX_PERF0_TRIANGLES_4TEX:
        GFWriteBPCmd(0x2300AD3F);
        break;
    case GX_PERF0_TRIANGLES_5TEX:
        GFWriteBPCmd(0x2300AD7F);
        break;
    case GX_PERF0_TRIANGLES_6TEX:
        GFWriteBPCmd(0x2300ADBF);
        break;
    case GX_PERF0_TRIANGLES_7TEX:
        GFWriteBPCmd(0x2300ADFF);
        break;
    case GX_PERF0_TRIANGLES_8TEX:
        GFWriteBPCmd(0x2300AE3F);
        break;
    case GX_PERF0_TRIANGLES_0CLR:
        GFWriteBPCmd(0x2300A27F);
        break;
    case GX_PERF0_TRIANGLES_1CLR:
        GFWriteBPCmd(0x2300A67F);
        break;
    case GX_PERF0_TRIANGLES_2CLR:
        GFWriteBPCmd(0x2300AA7F);
        break;

    case GX_PERF0_QUAD_0CVG:
        GFWriteBPCmd(0x2402C0C6);
        break;
    case GX_PERF0_QUAD_NON0CVG:
        GFWriteBPCmd(0x2402C16B);
        break;
    case GX_PERF0_QUAD_1CVG:
        GFWriteBPCmd(0x2402C0E7);
        break;
    case GX_PERF0_QUAD_2CVG:
        GFWriteBPCmd(0x2402C108);
        break;
    case GX_PERF0_QUAD_3CVG:
        GFWriteBPCmd(0x2402C129);
        break;
    case GX_PERF0_QUAD_4CVG:
        GFWriteBPCmd(0x2402C14A);
        break;
    case GX_PERF0_AVG_QUAD_CNT:
        GFWriteBPCmd(0x2402C1AD);
        break;

    case GX_PERF0_NONE:
        break;
    }

    gx->perf1 = perf1;

    switch (gx->perf1) {
    case GX_PERF1_TEXELS:
        GFWriteBPCmd(0x67000042);
        break;
    case GX_PERF1_TX_IDLE:
        GFWriteBPCmd(0x67000084);
        break;
    case GX_PERF1_TX_REGS:
        GFWriteBPCmd(0x67000063);
        break;
    case GX_PERF1_TX_MEMSTALL:
        GFWriteBPCmd(0x67000129);
        break;
    case GX_PERF1_TC_MISS:
        GFWriteBPCmd(0x67000252);
        break;
    case GX_PERF1_CLOCKS:
        GFWriteBPCmd(0x67000021);
        break;
    case GX_PERF1_TC_CHECK1_2:
        GFWriteBPCmd(0x6700014B);
        break;
    case GX_PERF1_TC_CHECK3_4:
        GFWriteBPCmd(0x6700018D);
        break;
    case GX_PERF1_TC_CHECK5_6:
        GFWriteBPCmd(0x670001CF);
        break;
    case GX_PERF1_TC_CHECK7_8:
        GFWriteBPCmd(0x67000211);
        break;

    case GX_PERF1_VC_ELEMQ_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 2);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
        break;
    case GX_PERF1_VC_MISSQ_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 3);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
        break;
    case GX_PERF1_VC_MEMREQ_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 4);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
        break;
    case GX_PERF1_VC_STATUS7:
        SET_REG_FIELD(gx->perfSel, 4, 4, 5);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
        break;
    case GX_PERF1_VC_MISSREP_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 6);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
        break;
    case GX_PERF1_VC_STREAMBUF_LOW:
        SET_REG_FIELD(gx->perfSel, 4, 4, 7);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
        break;
    case GX_PERF1_VC_ALL_STALLS:
        SET_REG_FIELD(gx->perfSel, 4, 4, 9);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
        break;
    case GX_PERF1_VERTICES:
        SET_REG_FIELD(gx->perfSel, 4, 4, 8);
        GXFIFO.u8 = 8;
        GXFIFO.u8 = 32;
        GXFIFO.u32 = gx->perfSel;
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

    gx->bpSentNot = GX_FALSE;
}

void GXClearGPMetric(void) {
    GX_SET_CP_REG(2, 4);
}

#pragma scheduling off
void GXReadXfRasMetric(u32 *xf_wait_in, u32 *xf_wait_out, u32 *ras_busy, u32 *clocks)
{
    *ras_busy = __GXReadCPCounterU32(32, 33);
    *clocks = __GXReadCPCounterU32(34, 35);
    *xf_wait_in = __GXReadCPCounterU32(36, 37);
    *xf_wait_out = __GXReadCPCounterU32(38, 39);
}
#pragma scheduling reset
