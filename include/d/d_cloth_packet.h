#ifndef D_CLOTH_PACKET_H
#define D_CLOTH_PACKET_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "SSystem/SComponent/c_xyz.h"

class dKy_tevstr_c;

class dCloth_packet_c : public J3DPacket {
public:
    typedef dCloth_packet_c* (*CreateFunc)(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);
    typedef int (*FactorCheck)(dCloth_packet_c*, int, int);

    dCloth_packet_c(ResTIMG* i_toonimage, int flyGridSize, int hoistGridSize, float flyLength, float hoistLength, dKy_tevstr_c* tevstr, cXyz** posArr);
    ~dCloth_packet_c();
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG* i_img);
    virtual void TexObjLoad();
    virtual void TevSetting();

    void draw();
    void setGlobalWind(cXyz* wind);
    cXyz getFactor(cXyz* pPos, cXyz* pNrm, cXyz* pSpeed, float distFly, float distHoist, float distBoth, int x, int y);
    void setNrm();
    void plot();

    void setScale(cXyz scale) { mScale = scale; }
    void setMtx(Mtx mtx);
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

    void changeCurrentBuff() { mCurArr ^= 1; }

    bool chkCreateBuff() {
        if (mpPosArr[0] != NULL && mpPosArr[1] != NULL && mpNrmArr[0] != NULL && mpNrmArr[1] != NULL && mpNrmArrBack[0] != NULL && mpNrmArrBack[1] != NULL &&
            mpSpeedArr != NULL)
            return true;
        return false;
    }

    cXyz* getPosP() const { return mpPosArr[mCurArr]; }
    cXyz* getNrmP() const { return mpNrmArr[mCurArr]; }
    cXyz* getBackNrmP() const { return mpNrmArrBack[mCurArr]; }
    cXyz* getSpdP() const { return mpSpeedArr; }
    u32 getVerticalNum() const { return mHoistGridSize; }
    GXTexObj* getTexObjP() { return &mTexObj; }
    GXTexObj* getToonTexObjP() { return &mToonTex; }

    friend int default_factor_checkCB(dCloth_packet_c* pPkt, int x, int y);
    friend dCloth_packet_c* dCloth_packet_create(ResTIMG*, ResTIMG*, int, int, float, float, dKy_tevstr_c*, cXyz**);

protected:
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
dCloth_packet_c* dCloth_packet_create(
    ResTIMG* i_flagimage, ResTIMG* i_toonimage, int flyGridSize, int hoistGridSize, float flyLength, float hoistLength, dKy_tevstr_c* tevstr, cXyz** posArr
);

class dCloth_packetXlu_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();

private:
    dCloth_packetXlu_c(ResTIMG* i_toonimage, int flyGridSize, int hoistGridSize, float flyLength, float hoistLength, dKy_tevstr_c* tevstr, cXyz** posArr)
        : dCloth_packet_c(i_toonimage, flyGridSize, hoistGridSize, flyLength, hoistLength, tevstr, posArr) {}

    friend dCloth_packetXlu_c* dCloth_packetXlu_create(ResTIMG*, ResTIMG*, int, int, float, float, dKy_tevstr_c*, cXyz**);

private:
    u32 field_0xFC;
};

dCloth_packetXlu_c* dCloth_packetXlu_create(
    ResTIMG* i_flagimage, ResTIMG* i_toonimage, int flyGridSize, int hoistGridSize, float flyLength, float hoistLength, dKy_tevstr_c* tevstr, cXyz** posArr
);

class dClothVobj03_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

private:
    dClothVobj03_c(ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr)
        : dCloth_packet_c(i_toonimage, 5, 5, 120.0f, 60.0f, tevstr, posArr) {
        if (posArr) {
            field_0x108 = 1;
        } else {
            field_0x108 = 0;
        }
    }

public:
    static dClothVobj03_c* top_pointer;
    static s32 cloth_counter;

    friend dClothVobj03_c* dClothVobj03_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

private:
    GXTlutObj mTlutObj;
    u8 field_0x108;
    u8 mIsIndoors;
};
dClothVobj03_c* dClothVobj03_create(ResTIMG* i_flagimage, ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr);

class dClothVobj04_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

private:
    dClothVobj04_c(ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr)
        : dCloth_packet_c(i_toonimage, 5, 5, 120.0f, 60.0f, tevstr, posArr) {
        if (posArr) {
            field_0x108 = 1;
        } else {
            field_0x108 = 0;
        }
    };

public:
    static dClothVobj04_c* top_pointer;
    static s32 cloth_counter;

    friend dClothVobj04_c* dClothVobj04_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

private:
    GXTlutObj mTlutObj;
    u8 field_0x108;
    u8 mIsIndoors;
};
dClothVobj04_c* dClothVobj04_create(ResTIMG* i_flagimage, ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr);

class dClothVobj05_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

private:
    dClothVobj05_c(ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr)
        : dCloth_packet_c(i_toonimage, 5, 5, 50.0f, 120.0f, tevstr, posArr) {
        if (posArr) {
            field_0x108 = 1;
        } else {
            field_0x108 = 0;
        }
    }

public:
    static dClothVobj05_c* top_pointer;
    static s32 cloth_counter;

    friend dClothVobj05_c* dClothVobj05_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

private:
    GXTlutObj mTlutObj;
    u8 field_0x108;
    u8 mIsIndoors;
};
dClothVobj05_c* dClothVobj05_create(ResTIMG* i_flagimage, ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr);

class dClothVobj07_0_c : public dCloth_packet_c {
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();
    void cloth_copy();

private:
    dClothVobj07_0_c(ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr)
        : dCloth_packet_c(i_toonimage, 5, 5, 120.0f, 70.0f, tevstr, posArr) {
        if (posArr) {
            field_0x108 = 1;
        } else {
            field_0x108 = 0;
        }
    }

public:
    static dClothVobj07_0_c* top_pointer;
    static s32 cloth_counter;

    friend dClothVobj07_0_c* dClothVobj07_0_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

private:
    GXTlutObj mTlutObj;
    u8 field_0x108;
    u8 mIsIndoors;
};
dClothVobj07_0_c* dClothVobj07_0_create(ResTIMG* i_flagimage, ResTIMG* i_toonimage, dKy_tevstr_c* tevstr, cXyz** posArr);

#endif /* D_A_CLOTH_PACKET_H */
