#ifndef D_JNT_HIT_H
#define D_JNT_HIT_H

#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"

enum {
    /* 0x0 */ JntHitType_CYL_e,
    /* 0x1 */ JntHitType_SPH_e,
    /* 0x2 */ JntHitType_CYL2_e,
    /* 0x3 */ JntHitType_CYL_THROW_e,
    /* 0x4 */ JntHitType_SPH_THROW_e,
    /* 0x5 */ JntHitType_CYL_UNK_e, // Unused?
    /* 0x6 */ JntHitType_SPH_UNK_e, // Unused?
    /* 0x7 */ JntHitType_CYL_DELETE_e,
    /* 0x8 */ JntHitType_SPH_DELETE_e,
};

enum {
    JntHitIdx_DELETE_e = -3, // Hit a delete joint, so the actor should delete itself.
    JntHitIdx_NONE_e = -1,
};

struct __jnt_hit_data_c {
public:
    /* 0x0 */ s16 mShapeType;
    /* 0x2 */ s16 mJointIndex;
    /* 0x4 */ f32 mRadius;
    /* 0x8 */ Vec* mpOffsets;
}; // size = 0xC

class JntHit_c {
public:
    JntHit_c()
        : mpModel(NULL)
        , mpOffsets(NULL)
        , mpRadiuses(NULL)
        , mpShapeTypes(NULL)
        , field_0x1C(NULL) {}

    BOOL CreateInit();
    BOOL CylHitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*, cXyz, cXyz, f32);
    BOOL Cyl2HitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*, cXyz, cXyz, f32);
    BOOL SphHitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*, cXyz, f32);
    BOOL HitBufferUpdate(int*, cXyz*, int, csXyz*, cXyz*);
    s32 searchJntHitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*);
    
    J3DModel* getModel() { return mpModel; }
    void setSearchData(__jnt_hit_data_c* data) { mpSearchData = data; }
    void setMdlPtr(J3DModel* model) { mpModel = model; }
    void setMaxNum(s16 num) { mMaxNum = num; }
    bool isThrow(int type) {
        if (type == JntHitType_SPH_THROW_e || type == JntHitType_CYL_THROW_e) {
            return true;
        }
        return false;
    }
    bool isDelete(int type) {
        if (type == JntHitType_SPH_DELETE_e || type == JntHitType_CYL_DELETE_e) {
            return true;
        }
        return false;
    }
    bool isCylinder(int type) {
        if (type == JntHitType_CYL_e || type == JntHitType_CYL2_e || type == JntHitType_CYL_THROW_e || type == JntHitType_CYL_UNK_e || type == JntHitType_CYL_DELETE_e) {
            return true;
        }
        return false;
    }
    bool isSphere(int type) {
        if (type == JntHitType_SPH_e || type == JntHitType_SPH_THROW_e || type == JntHitType_SPH_UNK_e || type == JntHitType_SPH_DELETE_e) {
            return true;
        }
        return false;
    }
    // DBdraw(JntHit_HIO_c&);
    // DBdrawCyl(MtxP, cXyz*, cXyz*, f32);
    // DBdrawSph(MtxP, cXyz*, f32);
    // DBdrawAll();
    
    /* 0x00 */ __jnt_hit_data_c* mpSearchData;
    /* 0x04 */ J3DModel* mpModel;
    /* 0x08 */ cXyz* mpOffsets;
    /* 0x0C */ f32* mpRadiuses;
    /* 0x10 */ s16* mpShapeTypes;
    /* 0x14 */ s16* mpJointIndexes;
    /* 0x18 */ s16 mMaxNum;
    /* 0x1A */ u8 field_0x1A[2];
    /* 0x1C */ void* field_0x1C;
};

class JntHit_HIO_c {
public:
    JntHit_HIO_c();
    virtual ~JntHit_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x06 */ s16 m06;
    /* 0x08 */ s16 m08;
    /* 0x0A */ u8 m0A[0x0C - 0x0A];
    /* 0x0C */ f32 m0C;
    /* 0x10 */ cXyz m10;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ u8 m28[0x2C - 0x28];
};  // Size: 0x2C

JntHit_c* JntHit_create(J3DModel* model, __jnt_hit_data_c* jntHitData, s16 hitDataCount);

#endif /* D_JNT_HIT_H */
