#ifndef J3DCLUSTER_H
#define J3DCLUSTER_H

#include "dolphin/types.h"

class J3DDeformer;

class J3DCluster {
public:
    void operator=(const J3DCluster& other) {
        field_0x0 = other.field_0x0;
        field_0x4 = other.field_0x4;
        field_0x8 = other.field_0x8;
        field_0xc = other.field_0xc;
        field_0x10 = other.field_0x10;
        field_0x12 = other.field_0x12;
        field_0x14 = other.field_0x14;
        field_0x16 = other.field_0x16;
        field_0x18 = other.field_0x18;
        field_0x1c = other.field_0x1c;
        mDeformer = other.mDeformer;
    }

    J3DDeformer* getDeformer() { return mDeformer; }
    void setDeformer(J3DDeformer* deformer) { mDeformer = deformer; }

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ void* field_0x8;
    /* 0x0C */ u8 field_0xc;
    /* 0x0D */ u8 field_0xd[0x10 - 0x0D];
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ void* field_0x18;
    /* 0x1C */ void* field_0x1c;
    /* 0x20 */ J3DDeformer* mDeformer;
};  // Size: 0x24

class J3DClusterKey {
public:
    void operator=(const J3DClusterKey& other) {
        field_0x0 = other.field_0x0;
        field_0x2 = other.field_0x2;
        field_0x4 = other.field_0x4;
        field_0x8 = other.field_0x8;
    }

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ u16 field_0x0;
    /* 0x02 */ u16 field_0x2;
    /* 0x04 */ void* field_0x4;
    /* 0x08 */ void* field_0x8;
};  // Size: 0x0C

class J3DClusterVertex {
public:
    void operator=(const J3DClusterVertex& other) {
        field_0x0 = other.field_0x0;
        field_0x4 = other.field_0x4;
        field_0x8 = other.field_0x8;
    }

private:
    friend class J3DClusterLoader;
    friend class J3DClusterLoader_v15;

    /* 0x00 */ u16 field_0x0;
    /* 0x04 */ u16* field_0x4;
    /* 0x08 */ u16* field_0x8;
};  // Size: 0x0C

#endif /* J3DCLUSTER_H */
