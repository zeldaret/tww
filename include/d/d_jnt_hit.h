#ifndef D_JNT_HIT_H
#define D_JNT_HIT_H

#include "global.h"
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"

struct __jnt_hit_data_c {
public:
    /* 0x0 */ s16 field_0x0;
    /* 0x2 */ s16 mJointIndex;
    /* 0x4 */ f32 field_0x4;
    /* 0x8 */ cXyz* field_0x8;
};

class JntHit_c {
public:
    void CreateInit();
    void CylHitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*, cXyz, cXyz, f32);
    void Cyl2HitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*, cXyz, cXyz, f32);
    void SphHitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*, cXyz, f32);
    void HitBufferUpdate(int*, cXyz*, int, csXyz*, cXyz*);
    s32 searchJntHitPosAngleOffset(cXyz*, csXyz*, cXyz*, csXyz*);
    
    J3DModel* getModel() { return mpModel; }
    
    /* 0x00 */ __jnt_hit_data_c* mpHitData;
    /* 0x04 */ J3DModel* mpModel;
    /* 0x08 */ cXyz* field_0x08;
    /* 0x0C */ short* field_0x0c;
    /* 0x10 */ short* field_0x10;
    /* 0x14 */ short* mpJointIndexes;
    /* 0x18 */ s16 mHitDataCount;
    /* 0x1A */ u8 field_0x1A[0x20 - 0x1A];
};

class JntHit_HIO_c {
public:
    JntHit_HIO_c();
    virtual ~JntHit_HIO_c();
};

JntHit_c* JntHit_create(J3DModel* model, __jnt_hit_data_c* jntHitData, s16 hitDataCount);

#endif /* D_JNT_HIT_H */
