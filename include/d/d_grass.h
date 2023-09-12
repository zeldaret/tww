#ifndef D_GRASS_H
#define D_GRASS_H

#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"

class dCcMassS_HitInf;
class cCcD_Obj;
class fopAc_ac_c;

class dGrass_data_c {
public:
    dGrass_data_c();
    ~dGrass_data_c();

    void WorkCo(fopAc_ac_c*, u32, int);
    void WorkAt_NoCutAnim(fopAc_ac_c*, u32, int, dCcMassS_HitInf*, cCcD_Obj*);
    void WorkAt(fopAc_ac_c*, u32, int, dCcMassS_HitInf*);
    void hitCheck(int);
    
    /* 0x00 */ u8 mState;
    /* 0x01 */ u8 mInitFlags;
    /* 0x02 */ u8 mAnimIdx;
    /* 0x03 */ u8 mItemIdx;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ Mtx mModelMtx;
    /* 0x40 */ dGrass_data_c* mpNextData;
};

class dGrass_anm_c {
public:
    dGrass_anm_c();

    /* 0x00 */ u8 mState;
    /* 0x02 */ s16 mRotY;
    /* 0x04 */ s16 mRotX;
    /* 0x08 */ Mtx mAnimMtx;
};

class dGrass_room_c {
public:
    void newData(dGrass_data_c*);
    void deleteData();
    dGrass_room_c();

    /* 0x0 */ dGrass_data_c* mpData;
};

class dGrass_packet_c : public J3DPacket {
public:
    dGrass_packet_c();
    
    void calc();
    void update();
    void setData(dGrass_data_c*, int, cXyz&, int, s8);
    void newData(cXyz&, int, s8);
    void newAnm();
    void setAnm(int, s16);

    virtual void draw();
    virtual ~dGrass_packet_c();

    /* 0x00010 */ s16 mRndm;
    /* 0x00012 */ u8 field_0x00012[0x00014 - 0x00012];
    /* 0x00014 */ dGrass_data_c mGrassData[1500];
    /* 0x18E84 */ dGrass_anm_c mGrassAnm[104];
    /* 0x1A544 */ dGrass_room_c mGrassRoom[64];
    /* 0x1A644 */ f32* mpPosArr;
    /* 0x1A648 */ GXColor* mpColorArr;
    /* 0x1A64C */ f32* mpTexCoordArr;
    /* 0x1A650 */ void* mpMatDL;
    /* 0x1A654 */ u32 mMatDLSize;
    /* 0x1A658 */ void* mpDL;
    /* 0x1A65C */ u32 mDLSize;
    /* 0x1A660 */ void* mpDLCut;
    /* 0x1A664 */ u32 mDLCutSize;
    /* 0x1A668 */ u16 mCoParticle;
    /* 0x1A66A */ u16 field_0x1a66a;
};

#endif /* D_GRASS_H */