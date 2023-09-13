#ifndef J3DMODEL_H
#define J3DMODEL_H

#include "JSystem/J3DGraphAnimator/J3DSkinDeform.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphBase/J3DVertex.h"
#include "dolphin/mtx/mtxvec.h"
#include "dolphin/types.h"

enum J3DMdlFlag {
    /* 0x00001 */ J3DMdlFlag_Unk00001 = 0x1,
    /* 0x00002 */ J3DMdlFlag_Unk00002 = 0x2,
    /* 0x00004 */ J3DMdlFlag_SkinPosCpu = 0x4,
    /* 0x00008 */ J3DMdlFlag_SkinNrmCpu = 0x8,
    /* 0x00010 */ J3DMdlFlag_Unk00010 = 0x10, 
    /* 0x20000 */ J3DMdlFlag_Unk20000 = 0x20000,
    /* 0x40000 */ J3DMdlFlag_Unk40000 = 0x40000,
    /* 0x80000 */ J3DMdlFlag_Unk80000 = 0x80000,
};

struct J3DUnkCalc1 {
    virtual void calc(J3DModel* model);
};

struct J3DUnkCalc2 {
    virtual void unk();
    virtual void calc(J3DModelData* mpModelData);
};

typedef void (*J3DCalcCallBack)(J3DModel*, u32 timing);

class J3DMatPacket;
class J3DShapePacket;
class J3DVisibilityManager;

class J3DModel {
public:
    J3DModel() {
        initialize();
    }
    J3DModel(J3DModelData* param_0, u32 param_1, u32 param_2) {
        initialize();
        entryModelData(param_0, param_1, param_2);
    }

    void setBaseTRMtx(f32 (*)[4]);
    void initialize();
    s32 entryModelData(J3DModelData*, u32, u32);
    s32 createShapePacket(J3DModelData*);
    s32 createMatPacket(J3DModelData*, u32);
    s32 newDifferedDisplayList(u32);
    void lock();
    void unlock();
    void diff();
    s32 setDeformData(J3DDeformData*, u32);
    s32 setSkinDeform(J3DSkinDeform*, u32);
    void calcAnmMtx();
    void calcWeightEnvelopeMtx();
    void calcNrmMtx();
    void calcBumpMtx();
    void calcBBoardMtx();
    void prepareShapePackets();
    MtxP getAnmMtx(int);

    virtual void update();
    virtual void entry();
    virtual void calc();
    virtual void calcMaterial();
    virtual void calcDiffTexMtx();
    virtual void viewCalc();
    virtual ~J3DModel();

    J3DModelData* getModelData() { return mModelData; }

    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) const { return (mFlags & flag) ? true : false; }

    bool isCpuSkinningOn() const { return (mFlags & J3DMdlFlag_SkinPosCpu) && (mFlags & J3DMdlFlag_SkinNrmCpu); }

    Mtx& getBaseTRMtx() { return mBaseTransformMtx; }
    void i_setBaseTRMtx(Mtx m) { MTXCopy(m, mBaseTransformMtx); }
    u32 getMtxCalcMode() const { return mFlags & 0x03; }
    J3DVertexBuffer* getVertexBuffer() const { return (J3DVertexBuffer*)&mVertexBuffer; }
    J3DMatPacket* getMatPacket(u16 idx) const { return &mpMatPacket[idx]; }
    J3DShapePacket* getShapePacket(u16 idx) const { return &mpShapePacket[idx]; }
    // Mtx33* getBumpMtxPtr(int idx) const { return mMtxBuffer->getBumpMtxPtr(idx); }
    Mtx33* getNrmMtxPtr() const { return mpNrmMtxBuf[1][mCurrentViewNo]; }
    Mtx* getDrawMtxPtr() const { return mpDrawMtxBuf[1][mCurrentViewNo]; }
    void setBaseScale(const Vec& scale) { mBaseScale = scale; }
    void setUserArea(u32 area) { mUserArea = area; }
    u32 getUserArea() const { return mUserArea; }
    Vec* getBaseScale() { return &mBaseScale; }

    /* 0x004 */ J3DModelData* mModelData;
    /* 0x008 */ u32 mFlags;
    /* 0x00C */ u32 mDiffFlag;
    /* 0x010 */ J3DCalcCallBack mCalcCallBack;
    /* 0x014 */ u32 mUserArea;
    /* 0x018 */ Vec mBaseScale;
    /* 0x024 */ Mtx mBaseTransformMtx;
    /* 0x054 */ Mtx mInternalView;
    /* 0x084 */ u8* mpScaleFlagArr;
    /* 0x088 */ u8* mpEvlpScaleFlagArr;
    /* 0x08C */ Mtx* mpNodeMtx;
    /* 0x090 */ Mtx* mpWeightEnvMtx;
    /* 0x094 */ Mtx** mpDrawMtxBuf[2];
    /* 0x09C */ Mtx33** mpNrmMtxBuf[2];
    /* 0x0A4 */ Mtx33*** mpBumpMtxArr[2];
    /* 0x0AC */ u32 mMtxBufferFlag;
    /* 0x0B0 */ u32 mCurrentViewNo;
    /* 0x0B4 */ J3DMatPacket* mpMatPacket;
    /* 0x0B8 */ J3DShapePacket* mpShapePacket;
    /* 0x0BC */ J3DDeformData* mpDeformData;
    /* 0x0C0 */ J3DSkinDeform* mpSkinDeform;
    /* 0x0C4 */ void * pad4[2];
    /* 0x0CC */ J3DVertexBuffer mVertexBuffer;
    /* 0x104 */ J3DVisibilityManager * mpVisibilityManager;
};

STATIC_ASSERT(sizeof(J3DModel) == 0x108);

#endif /* J3DMODEL_H */
