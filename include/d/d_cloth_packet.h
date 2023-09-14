#ifndef D_CLOTH_PACKET_H
#define D_CLOTH_PACKET_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/JUtility/JUTTexture.h"

class dCloth_packet_c : public J3DPacket {
    s32 mFlyGridSize;
    s32 mHoistGridSize;
    f32 mFlyLength;
    f32 mHoistLength;
    dKy_tevstr_c* mpTevstr;
    u32 mpFactorCheckCB;
    cXyz* mpPosArr[2];
    cXyz* mpNrmArr[2];
    cXyz* mpNrmArrBack[2];
    cXyz* mpSpeedArr;
    cXyz mGlobalWind;
    cXyz mScale;
    f32 mWindSpeed;
    f32 mWindSpeedWave;
    u32 field_0x64;
    GXTexObj mTexObj;
    GXTexObj mToonTex;
    Mtx mMtx;
    f32 mSpring;
    f32 mGravity;
    f32 mDrag;
    f32 mFlyFlex;
    f32 mHoistFlex;
    s16 mWave;
    s16 mWaveSpeed;
    s16 field_0xF0;
    s16 field_0xF2;
    s16 mRipple;
    s16 mRotateY;
    u8 mCurArr;

public:
    void draw();
    ~dCloth_packet_c() {}
    virtual void init();
    virtual void cloth_move();
    virtual void cloth_draw();
    virtual void TexObjInit(ResTIMG*);
    virtual void TexObjLoad();
    virtual void TevSetting();

    void setScale(cXyz scale);
    void setMtx(Mtx mtx);
};

dCloth_packet_c* dClothVobj03_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);
dCloth_packet_c* dClothVobj04_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);
dCloth_packet_c* dClothVobj05_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);
dCloth_packet_c* dClothVobj07_0_create(ResTIMG*, ResTIMG*, dKy_tevstr_c*, cXyz**);

#endif /* D_A_CLOTH_PACKET_H */
