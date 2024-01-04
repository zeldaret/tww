#ifndef J3DCLUSTER_H
#define J3DCLUSTER_H

#include "dolphin/types.h"

class J3DDeformer;
class J3DClusterKey;
class J3DClusterVertex;

class J3DCluster {
public:
    void operator=(const J3DCluster& other) {
        mMaxAngle = other.mMaxAngle;
        mMinAngle = other.mMinAngle;
        mClusterKey = other.mClusterKey;
        mFlags = other.mFlags;
        mKeyNum = other.mKeyNum;
        mPosNum = other.mPosNum;
        field_0x14 = other.field_0x14;
        field_0x16 = other.field_0x16;
        field_0x18 = other.field_0x18;
        mClusterVertex = other.mClusterVertex;
        mDeformer = other.mDeformer;
    }

    J3DDeformer* getDeformer() { return mDeformer; }
    void setDeformer(J3DDeformer* deformer) { mDeformer = deformer; }

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ f32 mMaxAngle;
    /* 0x04 */ f32 mMinAngle;
    /* 0x08 */ J3DClusterKey* mClusterKey;
    /* 0x0C */ u8 mFlags;
    /* 0x0D */ u8 field_0xd[0x10 - 0x0D];
    /* 0x10 */ u16 mKeyNum;
    /* 0x12 */ u16 mPosNum;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ u16* field_0x18;
    /* 0x1C */ J3DClusterVertex* mClusterVertex;
    /* 0x20 */ J3DDeformer* mDeformer;
};  // Size: 0x24

class J3DClusterKey {
public:
    void operator=(const J3DClusterKey& other) {
        mPosNum = other.mPosNum;
        mNrmNum = other.mNrmNum;
        field_0x4 = other.field_0x4;
        field_0x8 = other.field_0x8;
    }

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ u16 mPosNum;
    /* 0x02 */ u16 mNrmNum;
    /* 0x04 */ void* field_0x4;
    /* 0x08 */ void* field_0x8;
};  // Size: 0x0C

class J3DClusterVertex {
public:
    void operator=(const J3DClusterVertex& other) {
        mNum = other.mNum;
        field_0x4 = other.field_0x4;
        field_0x8 = other.field_0x8;
    }

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ u16 mNum;
    /* 0x04 */ u16* field_0x4;
    /* 0x08 */ u16* field_0x8;
};  // Size: 0x0C

#endif /* J3DCLUSTER_H */
