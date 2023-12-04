#ifndef D_CLOTH_PACKET_H
#define D_CLOTH_PACKET_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "SSystem/SComponent/c_xyz.h"

class dKy_tevstr_c;

class dCloth_packet_c : public J3DPacket {
public:
    dCloth_packet_c(ResTIMG*, int, int, float, float, dKy_tevstr_c*, cXyz**);
    ~dCloth_packet_c();
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();

    void draw();
    void setGlobalWind(cXyz*);
    void getFactor(cXyz*, cXyz*, cXyz*, float, float, float, int, int);
    void setNrm();
    void plot();

    void setScale(cXyz scale) { mScale = scale; }
    void setMtx(Mtx mtx);
    typedef int (*FactorCheck)(dCloth_packet_c*, int, int);
    void setFactorCheckCB(FactorCheck cb) { mpFactorCheckCB = cb; }
    void setWindPower(f32 wind, f32 windWave) {
        mWindSpeed = wind;
        mWindSpeedWave = windWave;
    }
    void setParam(f32 spring, f32 grav, f32 drag, f32 flyFlex, f32 hoistFlex, s16 wave, s16 param_1, s16 ripple, s16 rotate, f32 wind, f32 windWave) {
        mSpring = spring;
        mGravity = grav;
        mDrag = drag;
        mFlyFlex = flyFlex;
        mHoistFlex = hoistFlex;
        mWaveSpeed = wave;
        field_0xF2 = param_1;
        mRipple = ripple;
        mRotateY = rotate;
        setWindPower(wind, windWave);
    }

private:
    /* 0x10 */ s32 mFlyGridSize;
    /* 0x14 */ s32 mHoistGridSize;
    /* 0x18 */ f32 mFlyLength;
    /* 0x1C */ f32 mHoistLength;
    /* 0x20 */ dKy_tevstr_c* mpTevstr;
    /* 0x24 */ FactorCheck mpFactorCheckCB;
    /* 0x28 */ cXyz* mpPosArr[2];
    /* 0x30 */ cXyz* mpNrmArr[2];
    /* 0x38 */ cXyz* mpNrmArrBack[2];
    /* 0x40 */ cXyz* mpSpeedArr;
    /* 0x44 */ cXyz mGlobalWind;
    /* 0x50 */ cXyz mScale;
    /* 0x5C */ f32 mWindSpeed;
    /* 0x60 */ f32 mWindSpeedWave;
    /* 0x64 */ u32 field_0x64;
    /* 0x68 */ GXTexObj mTexObj;
    /* 0x88 */ GXTexObj mToonTex;
    /* 0xA8 */ Mtx mMtx;
    /* 0xD8 */ f32 mSpring;
    /* 0xDC */ f32 mGravity;
    /* 0xE0 */ f32 mDrag;
    /* 0xE4 */ f32 mFlyFlex;
    /* 0xE8 */ f32 mHoistFlex;
    /* 0xEC */ s16 mWave;
    /* 0xEE */ s16 mWaveSpeed;
    /* 0xF0 */ s16 field_0xF0;
    /* 0xF2 */ s16 field_0xF2;
    /* 0xF4 */ s16 mRipple;
    /* 0xF6 */ s16 mRotateY;
    /* 0xF8 */ u8 mCurArr;
}; // Size: 0xFC

class dCloth_packetXlu_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
};

class dClothVobj03_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

public:
    static void* top_pointer;
    static const s32 cloth_counter;
};
dClothVobj03_c* dClothVobj03_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

class dClothVobj04_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

public:
    static void* top_pointer;
    static const s32 cloth_counter;
};
dClothVobj04_c* dClothVobj04_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

class dClothVobj05_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

public:
    static void* top_pointer;
    static const s32 cloth_counter;
};
dClothVobj05_c* dClothVobj05_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

class dClothVobj07_0_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

public:
    static void* top_pointer;
    static const s32 cloth_counter;
};
dClothVobj07_0_c* dClothVobj07_0_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

dCloth_packetXlu_c* dCloth_packetXlu_create(ResTIMG*, ResTIMG*, int, int, float, float, dKy_tevstr_c*, cXyz**);

#endif /* D_A_CLOTH_PACKET_H */
