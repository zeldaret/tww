#ifndef J3DMODEL_H
#define J3DMODEL_H

#include "JSystem/J3DGraphAnimator/J3DSkinDeform.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphBase/J3DVertex.h"
#include "dolphin/mtx/mtx.h"
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

class J3DAnmVisibilityFull;
class J3DMatPacket;
class J3DShapePacket;

class J3DVisibilityManager {
public:
    J3DVisibilityManager(J3DAnmVisibilityFull* visibility) {
        mAnmVisibility = visibility;
        mbActive = 1;
    }
    virtual ~J3DVisibilityManager();
    virtual void setVisibility(J3DModelData*);

    /* 0x04 */ J3DAnmVisibilityFull* mAnmVisibility;
    /* 0x08 */ int mbActive;
};

class J3DUnkCallBack {
public:
    virtual void calc(J3DModel*);
};

class J3DModel {
public:
    J3DModel();

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
    void calcBBoard();
    void calcDrawMtx();
    void prepareShapePackets();
    MtxP getAnmMtx(int idx) { return mpNodeMtx[idx]; }
    void setAnmMtx(int idx, Mtx mtx) { MTXCopy(mtx, mpNodeMtx[idx]); }
    MtxP getWeightAnmMtx(int idx) { return mpWeightEnvMtx[idx]; }
    void setWeightAnmMtx(int idx, Mtx mtx) { MTXCopy(mtx, mpWeightEnvMtx[idx]); }

    s32 setNoUseDrawMtx();
    s32 createSingleDrawMtx(J3DModelData*);
    s32 createDoubleDrawMtx(J3DModelData*, u32);
    s32 createBumpMtxArray(J3DModelData*, u32);

    virtual void update();
    virtual void entry();
    virtual void calc();
    virtual void calcMaterial();
    virtual void viewCalc();
    virtual ~J3DModel();

    J3DModelData* getModelData() { return mModelData; }

    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) const { return (mFlags & flag) ? true : false; }

    bool isCpuSkinningOn() const { return (mFlags & J3DMdlFlag_SkinPosCpu) && (mFlags & J3DMdlFlag_SkinNrmCpu); }

    void swapDrawMtx() {
        Mtx* tmp = mpDrawMtxBuf[0][mCurrentViewNo];
        mpDrawMtxBuf[0][mCurrentViewNo] = mpDrawMtxBuf[1][mCurrentViewNo];
        mpDrawMtxBuf[1][mCurrentViewNo] = tmp;
    }

    void swapNrmMtx() {
        Mtx33* tmp = mpNrmMtxBuf[0][mCurrentViewNo];
        mpNrmMtxBuf[0][mCurrentViewNo] = mpNrmMtxBuf[1][mCurrentViewNo];
        mpNrmMtxBuf[1][mCurrentViewNo] = tmp;
    }

    Mtx& getBaseTRMtx() { return mBaseTransformMtx; }
    void setBaseTRMtx(Mtx m) { MTXCopy(m, mBaseTransformMtx); }
    u32 getMtxCalcMode() { return mFlags & 0x03; }
    u8 getScaleFlag(int idx) const { return mpScaleFlagArr[idx]; }
    void setScaleFlag(int idx, u8 param_1) { mpScaleFlagArr[idx] = param_1; }
    u8 getEnvScaleFlag(int idx) const { return mpEvlpScaleFlagArr[idx]; }
    J3DVertexBuffer* getVertexBuffer() { return (J3DVertexBuffer*)&mVertexBuffer; }
    J3DMatPacket* getMatPacket(u16 idx) { return &mpMatPacket[idx]; }
    J3DMatPacket* getMatPacketArray() { return mpMatPacket; }
    J3DShapePacket* getShapePacket(u16 idx) { return &mpShapePacket[idx]; }
    J3DShapePacket* getShapePacketArray() { return mpShapePacket; }
    Mtx* getDrawMtxPtr() { return mpDrawMtxBuf[1][mCurrentViewNo]; }
    Mtx& getDrawMtx(int idx) { return getDrawMtxPtr()[idx]; }
    Mtx33* getNrmMtxPtr() { return mpNrmMtxBuf[1][mCurrentViewNo]; }
    Mtx33& getNrmMtx(int idx) { return getNrmMtxPtr()[idx]; }
    Mtx33* getBumpMtxPtr(int idx) { return mpBumpMtxArr[1][idx][mCurrentViewNo]; }
    void setBaseScale(const Vec& scale) { mBaseScale = scale; }
    void setUserArea(u32 area) { mUserArea = area; }
    u32 getUserArea() const { return mUserArea; }
    void setVisibilityManager(J3DVisibilityManager* manager) { mpVisibilityManager = manager; }

    // TODO
    void getCurrentVtxNrm() {}
    void setCurrentVtxNrm(void*) {}
    void getCurrentVtxPos() {}
    void setCurrentVtxPos(void*) {}
    void setModelData(J3DModelData*) {}
    void setNrmMtx(int, Mtx) {}

    // Appears in TP debug maps but not TWW debug maps.
    Vec* getBaseScale() { return &mBaseScale; }

    /* 0x004 */ J3DModelData* mModelData;
    /* 0x008 */ u32 mFlags;
    /* 0x00C */ u32 mDiffFlag;
    /* 0x010 */ J3DCalcCallBack mCalcCallBack;
    /* 0x014 */ u32 mUserArea;
    /* 0x018 */ Vec mBaseScale;
    /* 0x024 */ Mtx mBaseTransformMtx;
    /* 0x054 */ Mtx mViewBaseMtx;
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
    /* 0x0C4 */ J3DUnkCallBack * field_0xc4;
    /* 0x0C8 */ J3DUnkCallBack * field_0xc8;
    /* 0x0CC */ J3DVertexBuffer mVertexBuffer;
    /* 0x104 */ J3DVisibilityManager * mpVisibilityManager;

    static Mtx sNoUseDrawMtx;
    static Mtx33 sNoUseNrmMtx;
    static Mtx* sNoUseDrawMtxPtr;
    static Mtx33* sNoUseNrmMtxPtr;
};

STATIC_ASSERT(sizeof(J3DModel) == 0x108);

#endif /* J3DMODEL_H */
