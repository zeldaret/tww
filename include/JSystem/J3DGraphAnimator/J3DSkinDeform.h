#ifndef J3DSKINDEFORM_H
#define J3DSKINDEFORM_H

#include "JSystem/J3DGraphAnimator/J3DCluster.h"
#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "dolphin/types.h"
#include "global.h"

class J3DModelData;
class J3DModel;
class J3DVertexBuffer;
class J3DAnmCluster;
class JUTNameTab;

class J3DDeformData {
public:
    J3DDeformData();
    void clear();
    void deform(J3DVertexBuffer*);
    void deform(J3DModel*);

    u16 getClusterNum() const { return mClusterNum; }
    u16 getClusterKeyNum() const { return mClusterKeyNum; }
    J3DCluster* getClusterPointer(u16 i) { return &mClusterPointer[i]; }
    J3DClusterKey* getClusterKeyPointer(u16 i) { return &mClusterKeyPointer[i]; }
    f32* getVtxPos() { return mVtxPos; }
    f32* getVtxNrm() { return mVtxNrm; }

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ u16 mClusterNum;
    /* 0x02 */ u16 mClusterKeyNum;
    /* 0x04 */ u16 mClusterVertexNum;
    /* 0x08 */ J3DCluster* mClusterPointer;
    /* 0x0C */ J3DClusterKey* mClusterKeyPointer;
    /* 0x10 */ J3DClusterVertex* mClusterVertex;
    /* 0x14 */ u16 mVtxPosNum;
    /* 0x16 */ u16 mVtxNrmNum;
    /* 0x18 */ f32* mVtxPos;
    /* 0x1C */ f32* mVtxNrm;
    /* 0x20 */ JUTNameTab* mClusterName;
    /* 0x24 */ JUTNameTab* mClusterKeyName;
};  // Size: 0x28

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
    /* 0x04 */ u16* mPosUseMtx;
    /* 0x08 */ u16* mNrmUseMtx;
    /* 0x0C */ Mtx33* mNrmMtx;
    /* 0x10 */ u32 mFlags;
    /* 0x14 */ u8 field_0x14;
};  // Size: 0x18

STATIC_ASSERT(sizeof(J3DSkinDeform) == 0x18);

class J3DDeformer {
public:
    J3DDeformer(J3DDeformData* data) {
        clear();
        mDeformData = data;
    }
    void clear();
    void deform(J3DVertexBuffer*, u16, f32*);
    void deform(J3DVertexBuffer*, u16);
    void deform_VtxPosF32(J3DVertexBuffer*, J3DCluster*, J3DClusterKey*, f32*);
    void deform_VtxNrmF32(J3DVertexBuffer*, J3DCluster*, J3DClusterKey*, f32*);
    void normalize(f32*);
    void normalizeWeight(int, f32*);

    void checkFlag(u32) {}

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ J3DDeformData* mDeformData;
    /* 0x04 */ J3DAnmCluster* mAnmCluster;
    /* 0x08 */ f32* mWeightList;
    /* 0x0C */ f32* field_0x0c;
    /* 0x10 */ u32 mFlags;
};  // Size: 0x14

#endif /* J3DSKINDEFORM_H */
