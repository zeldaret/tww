#ifndef D_A_SEA_H
#define D_A_SEA_H

#include "dolphin/types.h"
#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/JGeometry.h"

class daSea_WaterHeightInfo_Mng {
public:
    /* 0x00 */ u8 mHeight[9][9];
    /* 0x51 */ u8 m51[0x54 - 0x51];
    /* 0x54 */ /* vtable */

public:
    void Pos2Index(f32, f32*);
    void GetHeight(f32, f32);
    void GetHeight(int, int);
    void GetArea(int, int, f32*, f32*, f32*, f32*);
    void SetInf();
    virtual ~daSea_WaterHeightInfo_Mng() {}
};
STATIC_ASSERT(sizeof(daSea_WaterHeightInfo_Mng) == 0x58);

struct daSea_WaveInfo__Table {
    /* 0x00 */ f32 mHeight;
    /* 0x04 */ f32 mKm;
    /* 0x08 */ s16 mPhase;
    /* 0x0A */ u8 m0A[0x0C - 0x0A];
    /* 0x0C */ f32 mScaleX;
    /* 0x10 */ f32 mScaleZ;
    /* 0x14 */ int mCounterMax;
};

class daSea_WaveInfo {
public:
    /* 0x00 */ daSea_WaveInfo__Table* mWaveInfoTable;
    /* 0x04 */ f32 m04[4];
    /* 0x14 */ int mCounters[4];
    /* 0x24 */ f32 mCurScale;
    /* 0x28 */ /* vtable */

public:
    daSea_WaveInfo();
    virtual ~daSea_WaveInfo();
    void AddCounter();
    void GetRatio(int);
    void GetKm(int);
    void GetScale(f32);
};

class daSea_packet_c : public J3DPacket {
public:
    void create(cXyz&);
    void CleanUp();
    daSea_packet_c();
    void SetFlat();
    void ClrFlat();
    void CalcFlatInterTarget(cXyz&);
    void CalcFlatInter();
    void SetCullStopFlag();
    void CheckRoomChange();
    void execute(cXyz&);
    void draw();
    ~daSea_packet_c();

public:
    /* 0x010 */ daSea_WaterHeightInfo_Mng mWaterHeightMgr;
    /* 0x068 */ daSea_WaveInfo mWaveInfo;
    /* 0x094 */ JGeometry::TVec3<f32> mPlayerPos;
    /* 0x0A0 */ int mIdxX;
    /* 0x0A4 */ int mIdxZ;
    /* 0x0A8 */ f32 mFlatInter;
    /* 0x0AC */ f32 mFlatTarget;
    /* 0x0B0 */ f32 mFlatInterCounter;
    /* 0x0B4 */ _GXTexObj mTexSea0;
    /* 0x0D4 */ _GXTexObj mTexSea1;
    /* 0x0F4 */ _GXTexObj mpTexWyurayura;
    /* 0x114 */ f32 mDrawMinX;
    /* 0x118 */ f32 mDrawMinZ;
    /* 0x11C */ f32 mDrawMaxX;
    /* 0x120 */ f32 mDrawMaxZ;
    /* 0x124 */ float* mpHeightTable;
    /* 0x128 */ JGeometry::TVec3<f32> mCurPos;
    /* 0x134 */ JGeometry::TVec3<f32>* mpDrawVtx;
    /* 0x138 */ u8 mbIsDelete;
    /* 0x139 */ u8 mCullStopFlag;
    /* 0x13A */ u8 m13A;
    /* 0x13B */ u8 m13B[0x13C - 0x13B];
    /* 0x13C */ int mRoomNo;
    /* 0x140 */ int mFlags;
    /* 0x144 */ s16 mAnimCounter;
    /* 0x146 */ u8 field_146[0x148 - 0x146];
    
    static f32 BASE_HEIGHT;
};

class sea_class;

void get_wave_max(int);
void calcMinMax(int, f32*, f32*);
void daSea_Init();
void daSea_ChkAreaBeforePos(f32, f32);
bool daSea_ChkArea(f32, f32);
f32 daSea_calcWave(f32, f32);
void daSea_GetPoly(void*, void (*)(void*, cXyz&, cXyz&, cXyz&), const cXyz&, const cXyz&);
void daSea_execute(cXyz&);
void daSea_Draw(sea_class*);
void daSea_Execute(sea_class*);
void daSea_IsDelete(sea_class*);
void daSea_Delete(sea_class*);
void CheckCreateHeap(fopAc_ac_c*);
void daSea_Create(fopAc_ac_c*);

#endif /* D_A_SEA_H */
