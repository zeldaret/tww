#ifndef J3DSHAPE_H
#define J3DSHAPE_H

#include "JSystem/J3DAssert.h"
#include "JSystem/J3DGraphBase/J3DShapeDraw.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/gd/GDGeometry.h"
#include "dolphin/gx/GX.h"
#include "dolphin/types.h"

class J3DShapeMtx;

class J3DCurrentMtxInfo {
public:
    /* 0x00 */ u32 mMtxIdxRegA;
    /* 0x04 */ u32 mMtxIdxRegB;
};

static inline void JRNLoadCPCmd(u8 cmd, u32 param) {
    GXCmd1u8(GX_CMD_LOAD_CP_REG);
    GXCmd1u8(cmd);
    GXCmd1u32(param);
}

inline void JRNLoadXFCmdHdr(u16 cmd, u8 len) {
    GXCmd1u8(GX_CMD_LOAD_XF_REG);
    GXCmd1u16(len - 1);
    GXCmd1u16(cmd);
}

class J3DCurrentMtx : public J3DCurrentMtxInfo {
public:
    J3DCurrentMtx() {
        mMtxIdxRegA = 0x3cf3cf00;
        mMtxIdxRegB = 0x00f3cf3c;
    }

    void operator=(const J3DCurrentMtxInfo& info) {
        mMtxIdxRegA = info.mMtxIdxRegA;
        mMtxIdxRegB = info.mMtxIdxRegB;
    }

    u32 getMtxIdxRegA() const { return mMtxIdxRegA; }
    u32 getMtxIdxRegB() const { return mMtxIdxRegB; }

    void load() const {
        JRNLoadCPCmd(CP_REG_MTXIDXA_ID, mMtxIdxRegA);
        JRNLoadCPCmd(CP_REG_MTXIDXB_ID, mMtxIdxRegB);
        JRNLoadXFCmdHdr(GX_XF_REG_MATRIXINDEX0, 2);
        GXCmd1u32(mMtxIdxRegA);
        GXCmd1u32(mMtxIdxRegB);
    }

    void setCurrentTexMtx(u8 t0, u8 t1, u8 t2, u8 t3, u8 t4, u8 t5, u8 t6, u8 t7) {
        mMtxIdxRegA = t0 << 6 | t1 << 12 | t2 << 18 | t3 << 24;
        mMtxIdxRegB = t4 << 0 | t5 << 6 | t6 << 12 | t7 << 18;
    }
};

class J3DMaterial;
class J3DVertexData;
struct J3DDrawMtxData;

enum J3DShpFlag {
    J3DShpFlag_Hide = 0x0001,
    J3DShpFlag_SkinPosCpu = 0x0004,
    J3DShpFlag_SkinNrmCpu = 0x0008,
    J3DShpFlag_Hidden = 0x0010,
    J3DShpFlag_EnableLod = 0x0100,
    J3DShpFlag_NoMtx = 0x0200,
};

class J3DShape {
public:
    J3DShape() {
        initialize();
    }

    enum {
        kVcdVatDLSize = 0xC0,
    };

    void initialize();
    void addTexMtxIndexInDL(GXAttr, u32);
    void addTexMtxIndexInVcd(GXAttr);
    void calcNBTScale(Vec const&, Mtx33*, Mtx33*);
    u32 countBumpMtxNum() const;
    void loadVtxArray() const;
    bool isSameVcdVatCmd(J3DShape*);
    void makeVtxArrayCmd();
    void makeVcdVatCmd();
    void loadPreDrawSetting() const;
    void setArrayAndBindPipeline() const;

    virtual void draw() const;
    virtual void drawFast() const;
    virtual void simpleDraw() const;
    virtual void simpleDrawCache() const;

    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) const { return (mFlags & flag) ? true : false; }
    void setMaterial(J3DMaterial* pMaterial) {
        J3D_ASSERT_NULLPTR(509, pMaterial != NULL);
        mMaterial = pMaterial;
    }
    void setDrawMtxDataPointer(J3DDrawMtxData* pMtxData) {
        J3D_ASSERT_NULLPTR(554, pMtxData != NULL);
        mDrawMtxData = pMtxData;
    }
    void setVertexDataPointer(J3DVertexData* pVtxData) {
        J3D_ASSERT_NULLPTR(657, pVtxData != NULL);
        mVertexData = pVtxData;
    }
    void* getVcdVatCmd() { return mVcdVatCmd; }
    void setVcdVatCmd(void* pVatCmd) { mVcdVatCmd = (u8*)pVatCmd; }
    void show() { offFlag(J3DShpFlag_Hide); }
    void hide() { onFlag(J3DShpFlag_Hide); }
    void setCurrentViewNoPtr(u32* pViewNoPtr) {
        J3D_ASSERT_NULLPTR(584, pViewNoPtr != NULL);
        mCurrentViewNo = pViewNoPtr;
    }
    void setCurrentMtx(J3DCurrentMtx& mtx) { mCurrentMtx = mtx; }
    void setScaleFlagArray(u8* pScaleFlagArray) {
        J3D_ASSERT_NULLPTR(595, pScaleFlagArray != NULL);
        mScaleFlagArray = pScaleFlagArray;
    }
    void setDrawMtx(Mtx** pDrawMtx) { mDrawMtx = pDrawMtx; }
    void setNrmMtx(Mtx33** pNrmMtx) { mNrmMtx = pNrmMtx; }
    u32 getBumpMtxOffset() const { return mBumpMtxOffset; }
    void setBumpMtxOffset(u32 offs) { mBumpMtxOffset = offs; }
    GXVtxDescList* getVtxDesc() { return mVtxDesc; }

    J3DMaterial* getMaterial() const { return mMaterial; }
    u32 getIndex() const { return mIndex; }
    u32 getMtxGroupNum() const { return mMtxGroupNum; }
    J3DShapeDraw* getShapeDraw(u16 idx) { return mShapeDraw[idx]; }
    J3DShapeMtx* getShapeMtx(u16 idx) { return mShapeMtx[idx]; }

    static void resetVcdVatCache() { sOldVcdVatCmd = NULL; }

    static void* sOldVcdVatCmd;
    static u8 sEnvelopeFlag;

private:
    friend struct J3DShapeFactory;
    friend class J3DJointTree;

    /* 0x04 */ J3DMaterial* mMaterial;
    /* 0x08 */ u16 mIndex;
    /* 0x0A */ u16 mMtxGroupNum;
    /* 0x0C */ u32 mFlags;
    /* 0x10 */ f32 mRadius;
    /* 0x14 */ Vec mMin;
    /* 0x20 */ Vec mMax;
    /* 0x2C */ u8* mVcdVatCmd;
    /* 0x30 */ GXVtxDescList* mVtxDesc;
    /* 0x34 */ bool mHasNBT;
    /* 0x38 */ J3DShapeMtx** mShapeMtx;
    /* 0x3C */ J3DShapeDraw** mShapeDraw;
    /* 0x40 */ J3DCurrentMtx mCurrentMtx;
    /* 0x48 */ bool mHasPNMTXIdx;
    /* 0x4C */ J3DVertexData* mVertexData;
    /* 0x50 */ J3DDrawMtxData* mDrawMtxData;
    /* 0x54 */ u8* mScaleFlagArray;
    /* 0x58 */ Mtx** mDrawMtx;
    /* 0x5C */ Mtx33** mNrmMtx;
    /* 0x60 */ u32* mCurrentViewNo;
    /* 0x64 */ u32 mBumpMtxOffset;
};

class J3DShapeMtx {
public:
    typedef void (J3DShapeMtx::*MtxLoadIndx)(int mtxNo, u16 index) const;

    J3DShapeMtx(u16 useMtxIndex) : mUseMtxIndex(useMtxIndex) {}

    void loadMtxIndx_PNGP(int, u16) const;
    void loadMtxIndx_PCPU(int, u16) const;
    void loadMtxIndx_NCPU(int, u16) const;
    void loadMtxIndx_PNCPU(int, u16) const;

    virtual ~J3DShapeMtx() {}
    virtual u32 getType() const { return 'SMTX'; }
    virtual u32 getUseMtxNum() const { return 1; }
    virtual u16 getUseMtxIndex(u16) const { return mUseMtxIndex; }
    virtual void load() const;
    virtual void calcNBTScale(Vec const&, Mtx33*, Mtx33*);

    static MtxLoadIndx sMtxLoadPipeline[4];
    static u32 sCurrentPipeline;
    static u8* sCurrentScaleFlag;
    static u8 sNBTFlag;

    static void setCurrentPipeline(u32 pipeline) {
        J3D_ASSERT_RANGE(91, pipeline < 4);
        sCurrentPipeline = pipeline;
    }

protected:
    /* 0x04 */ u16 mUseMtxIndex;
};

#endif /* J3DSHAPE_H */
