#ifndef GXINIT_H
#define GXINIT_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx/mtx.h"

typedef GXTexRegion* (*GXTexRegionCallback)(const GXTexObj* t_obj, GXTexMapID id);
typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 idx);

typedef struct _GXData {
    // Bypass and vertex info
    /* 0x000 */ u16 vNumNot;
    /* 0x002 */ u16 bpSentNot;
    /* 0x004 */ u16 vNum;
    /* 0x006 */ u16 vLim;

    // Command process (CP) regs
    /* 0x008 */ u32 cpEnable;
    /* 0x00C */ u32 cpStatus;
    /* 0x010 */ u32 cpClr;
    /* 0x014 */ u32 vcdLo;
    /* 0x018 */ u32 vcdHi;
    /* 0x01C */ u32 vatA[8];
    /* 0x03C */ u32 vatB[8];
    /* 0x05C */ u32 vatC[8];
    /* 0x07C */ u32 lpSize;
    /* 0x080 */ u32 matIdxA;
    /* 0x084 */ u32 matIdxB;

    // Index loading base/stride regs (pos, nrm, tex, light)
    /* 0x088 */ u32 indexBase[4];
    /* 0x098 */ u32 indexStride[4];

    // Transform and lighting regs
    /* 0x0A8 */ u32 ambColor[2];
    /* 0x0B0 */ u32 matColor[2];

    // Setup regs
    /* 0x0B8 */ u32 suTs0[8];
    /* 0x0D8 */ u32 suTs1[8];
    /* 0x0F8 */ u32 suScis0;
    /* 0x0FC */ u32 suScis1;

    // Raster regs
    /* 0x100 */ u32 tref[8];
    /* 0x120 */ u32 iref;

    // Bump/Indirect texture regs
    /* 0x124 */ u32 bpMask;
    /* 0x128 */ u32 IndTexScale0;
    /* 0x12C */ u32 IndTexScale1;

    // Tev regs
    /* 0x130 */ u32 tevc[16];
    /* 0x170 */ u32 teva[16];
    /* 0x1B0 */ u32 tevKsel[8];

    // Performance regs
    /* 0x1D0 */ u32 cmode0;
    /* 0x1D4 */ u32 cmode1;
    /* 0x1D8 */ u32 zmode;
    /* 0x1DC */ u32 peCtrl;

    // Display copy regs
    /* 0x1E0 */ u32 cpDispSrc;
    /* 0x1E4 */ u32 cpDispSize;
    /* 0x1E8 */ u32 cpDispStride;
    /* 0x1EC */ u32 cpDisp;

    // Texture copy regs
    /* 0x1F0 */ u32 cpTexSrc;
    /* 0x1F4 */ u32 cpTexSize;
    /* 0x1F8 */ u32 cpTexStride;
    /* 0x1FC */ u32 cpTex;
    /* 0x200 */ GXBool cpTexZ;

    // General raster mode
    /* 0x204 */ u32 genMode;

    // Texture regions
    /* 0x208 */ GXTexRegion TexRegions0[GX_MAX_TEXMAP];
    /* 0x288 */ GXTexRegion TexRegions1[4];
    /* 0x2C8 */ u32 nextTexRgn;
    /* 0x2C8 */ u32 nextTexRgnCI;

    // Texture lookup table regions
    /* 0x2D0 */ GXTlutRegion TlutRegions[GX_MAX_TLUT_ALL];
    /* 0x410 */ GXTexRegionCallback texRegionCallback;
    /* 0x414 */ GXTlutRegionCallback tlutRegionCallback;

    // Command processor vars
    /* 0x418 */ GXAttrType nrmType;
    /* 0x41C */ GXBool hasNrms;
    /* 0x41D */ GXBool hasBiNrms;
    /* 0x420 */ u32 projType;
    /* 0x424 */ f32 projMtx[6];

    // Viewport parms
    /* 0x43C */ f32 vpLeft;
    /* 0x440 */ f32 vpTop;
    /* 0x444 */ f32 vpWd;
    /* 0x448 */ f32 vpHt;
    /* 0x44C */ f32 vpNearz;
    /* 0x450 */ f32 vpFarz;
    /* 0x454 */ f32 zOffset;
    /* 0x458 */ f32 zScale;

    // Texture regs
    /* 0x45C */ u32 tImage0[8];
    /* 0x47C */ u32 tMode0[8];
    /* 0x49C */ u32 texmapId[16];
    /* 0x4DC */ u32 tcsManEnab;
    /* 0x4E0 */ u32 tevTcEnab;

    // Performance metrics
    /* 0x4E4 */ GXPerf0 perf0;
    /* 0x4E8 */ GXPerf1 perf1;
    /* 0x4EC */ u32 perfSel;

    // Flags
    /* 0x4F0 */ GXBool inDispList;
    /* 0x4F1 */ GXBool dlSaveContext;
    /* 0x4F2 */ u8 dirtyVAT;
    /* 0x4F4 */ u32 dirtyState;
} GXData;  // Size: 0x4F8

STATIC_ASSERT(sizeof(GXData) == 0x4F8);

extern GXData* const gx;

// Define register addresses.
#define GX_CP_ADDR  (0x0C000000)
#define GX_PE_ADDR  (0x0C001000)
#define GX_PI_ADDR  (0x0C003000)
#define GX_MEM_ADDR (0x0C004000)

extern u32* __piReg;
extern u16* __cpReg;
extern u16* __peReg;
extern vu16* __memReg;

#define GX_GET_MEM_REG(offset) (*(vu16*)((vu16*)(__memReg) + (offset)))
#define GX_GET_CP_REG(offset)  (*(vu16*)((vu16*)(__cpReg) + (offset)))
#define GX_GET_PE_REG(offset)  (*(vu16*)((vu16*)(__peReg) + (offset)))
#define GX_GET_PI_REG(offset)  (*(vu32*)((vu32*)(__piReg) + (offset)))

#define GX_SET_MEM_REG(offset, val) (*(vu16*)((vu16*)(__memReg) + (offset)) = val)
#define GX_SET_CP_REG(offset, val)  (*(vu16*)((vu16*)(__cpReg) + (offset)) = val)
#define GX_SET_PE_REG(offset, val)  (*(vu16*)((vu16*)(__peReg) + (offset)) = val)
#define GX_SET_PI_REG(offset, val)  (*(vu32*)((vu32*)(__piReg) + (offset)) = val)

inline void GXSetWasteFlags() {
    GXData* data = gx;
    data->dirtyState |= GX_DIRTY_SU_TEX | GX_DIRTY_BP_MASK;
    data->bpSentNot = 0;
}

static inline void set_x2(u16 value)
{
    gx->bpSentNot = value;
}

#ifdef __cplusplus
extern "C" {
#endif

GXTexRegion* __GXDefaultTexRegionCallback(const GXTexObj* obj, GXTexMapID id);
GXTlutRegion* __GXDefaultTlutRegionCallback(u32 tlut);
BOOL __GXShutdown(BOOL final);
void __GXInitRevisionBits(void);
GXFifoObj* GXInit(void* base, u32 size);
void __GXInitGX(void);

#ifdef __cplusplus
};
#endif

#endif /* GXINIT_H */
