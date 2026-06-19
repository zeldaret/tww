#ifndef J3DCLUSTER_H
#define J3DCLUSTER_H

#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/types.h"

class J3DDeformer;
class J3DClusterKey;
class J3DClusterVertex;
class J3DModel;
class J3DVertexBuffer;
class JUTNameTab;

class J3DCluster {
public:
    void operator=(const J3DCluster& other) {
        mMaxAngle = other.mMaxAngle;
        mMinAngle = other.mMinAngle;
        mClusterKey = other.mClusterKey;
        mFlags = other.mFlags;
        mKeyNum = other.mKeyNum;
        mPosNum = other.mPosNum;
        mNrmNum = other.mNrmNum;
        mClusterVertexNum = other.mClusterVertexNum;
        mPosDstIdx = other.mPosDstIdx;
        mClusterVertex = other.mClusterVertex;
        mDeformer = other.mDeformer;
    }

    J3DDeformer* getDeformer() { return mDeformer; }
    void setDeformer(J3DDeformer* deformer) { mDeformer = deformer; }

public:
    /* 0x00 */ f32 mMaxAngle;
    /* 0x04 */ f32 mMinAngle;
    /* 0x08 */ J3DClusterKey* mClusterKey;
    /* 0x0C */ u8 mFlags;
    /* 0x0D */ u8 field_0xd[0x10 - 0x0D];
    /* 0x10 */ u16 mKeyNum;
    /* 0x12 */ u16 mPosNum;
    /* 0x14 */ u16 mNrmNum;
    /* 0x16 */ u16 mClusterVertexNum;
    /* 0x18 */ u16* mPosDstIdx;
    /* 0x1C */ J3DClusterVertex* mClusterVertex;
    /* 0x20 */ J3DDeformer* mDeformer;
};  // Size: 0x24

class J3DClusterKey {
public:
    void operator=(const J3DClusterKey& other) {
        mPosNum = other.mPosNum;
        mNrmNum = other.mNrmNum;
        mPosFlag = other.mPosFlag;
        mNrmFlag = other.mNrmFlag;
    }

public:
    /* 0x00 */ u16 mPosNum;
    /* 0x02 */ u16 mNrmNum;
    /* 0x04 */ u16* mPosFlag;
    /* 0x08 */ u16* mNrmFlag;
};  // Size: 0x0C

class J3DDeformData {
public:
    J3DDeformData();
    void clear();
    void deform(J3DVertexBuffer*);
    void deform(J3DModel*);

    u16 getClusterNum() const { return mClusterNum; }
    u16 getClusterKeyNum() const { return mClusterKeyNum; }
    J3DCluster* getClusterPointer(u16 index) {
        J3D_ASSERT(186, (index < mClusterNum), "Error : range over.");
        return &mClusterPointer[index];
    }
    J3DClusterKey* getClusterKeyPointer(u16 i) {
        J3D_ASSERT(199, (i < mClusterKeyNum), "Error : range over.");
        return &mClusterKeyPointer[i];
    }
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

class J3DClusterVertex {
public:
    void operator=(const J3DClusterVertex& other) {
        mNum = other.mNum;
        mSrcIdx = other.mSrcIdx;
        mDstIdx = other.mDstIdx;
    }

public:
    /* 0x00 */ u16 mNum;
    /* 0x04 */ u16* mSrcIdx;
    /* 0x08 */ u16* mDstIdx;
};  // Size: 0x0C

#endif /* J3DCLUSTER_H */
