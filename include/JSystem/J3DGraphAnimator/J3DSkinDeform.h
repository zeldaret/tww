#ifndef J3DSKINDEFORM_H
#define J3DSKINDEFORM_H

#include "JSystem/J3DGraphAnimator/J3DCluster.h"
#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "dolphin/types.h"
#include "global.h"

class J3DModelData;
class J3DVertexBuffer;
class J3DModel;
class J3DAnmCluster;

class J3DDeformData {
public:
    J3DDeformData();
    void clear();
    void deform(J3DVertexBuffer*);
    void deform(J3DModel*);
    void setAnm(J3DAnmCluster*);

private:
    /* 0x00 */ u16 mClusterNum;
    /* 0x02 */ u16 mClusterKeyNum;
    /* 0x04 */ u16 field_0x4;
    /* 0x08 */ J3DCluster** mClusterPointer;
    /* 0x0C */ J3DClusterKey** mClusterKeyPointer;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ void* mVtxPos;
    /* 0x1C */ void* mVtxNrm;
    /* 0x20 */ int field_0x20;
    /* 0x24 */ int field_0x24;
};  // Size: 0x28

struct J3DSkinNList {
    J3DSkinNList();
    void calcSkin_VtxPosF32(f32 (*)[4], void*, void*);
    void calcSkin_VtxNrmF32(f32 (*)[4], void*, void*);

    /* 0x00 */ u16* field_0x0;
    /* 0x04 */ u16* field_0x4;
    /* 0x08 */ f32* field_0x8;
    /* 0x0C */ f32* field_0xc;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
};  // Size: 0x14

class J3DSkinDeform {
public:
    J3DSkinDeform();
    int initMtxIndexArray(J3DModelData*);
    void changeFastSkinDL(J3DModelData*);
    void calcNrmMtx(J3DModel*);
    void deformVtxPos_F32(J3DModel*) const;
    void deformVtxPos_S16(J3DModel*) const;
    void deformVtxNrm_F32(J3DModel*) const;
    void deformVtxNrm_S16(J3DModel*) const;
    void setNrmMtx(int i, MtxP mtx) {
        J3DPSMtx33CopyFrom34(mtx, (Mtx3P)mNrmMtx[i]);
    }
    Mtx3P getNrmMtx(int i) { return mNrmMtx[i]; }
    void onFlag(u32 flag) { mFlags |= flag; }
    void offFlag(u32 flag) { mFlags &= ~flag; }
    bool checkFlag(u32 flag) { return mFlags & flag; }

    virtual void deform(J3DModel*);
    virtual ~J3DSkinDeform() {}

    static u16* sWorkArea_WEvlpMixMtx[1024];
    static f32* sWorkArea_WEvlpMixWeight[1024];
    static u16 sWorkArea_MtxReg[1024 + 4 /* padding */];

private:
    /* 0x04 */ u16* mPosData;
    /* 0x08 */ u16* mNrmData;
    /* 0x0C */ Mtx33* mNrmMtx;
    /* 0x10 */ u32 mFlags;
    /* 0x14 */ u8 field_0x14;
};  // Size: 0x18

STATIC_ASSERT(sizeof(J3DSkinDeform) == 0x18);

class J3DDeformer {
public:
    J3DDeformer(J3DDeformData*);
    void clear();
    void deform(J3DVertexBuffer*, u16, f32*);
    void deform(J3DVertexBuffer*, u16);
    void deform_VtxPosF32(J3DVertexBuffer*, J3DCluster*, J3DClusterKey*, f32*);
    void deform_VtxNrmF32(J3DVertexBuffer*, J3DCluster*, J3DClusterKey*, f32*);
    void normalize(f32*);
    void normalizeWeight(int, f32*);

private:
    /* 0x00 */ J3DDeformData* mDeformData;
    /* 0x04 */ J3DAnmCluster* mAnmCluster;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ int field_0xc;
    /* 0x10 */ u32 mFlags;
};  // Size: 0x14

inline void J3DFillZero32B(register void* param_0, register u32 param_1) {
    asm {
        srwi param_1, param_1, 5
        mtctr param_1
    lbl_8032D948:
        dcbz 0, param_0
        addi param_0, param_0, 0x20
        bdnz lbl_8032D948
    }
}

#endif /* J3DSKINDEFORM_H */
