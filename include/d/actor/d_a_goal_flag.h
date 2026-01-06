#ifndef D_A_GOAL_FLAG_H
#define D_A_GOAL_FLAG_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class dPath;

class daGFlag_HIO_c {
public:
    daGFlag_HIO_c() {
        m04 = -1;
        m05 = 1;
        m07 = 0;
        m06 = 0;
        m08 = 0;
        m0C = 0x2ee;
        m10 = 0x800;
        m14 = 0xbd1;
        m18 = 0xf0;
        m1C = 0x96;
        m20 = 0x96;
        m09 = 0;
        mWindScale1 = 12.0f;
        mWindScale2 = 4.0f;
        mFlagSagFactor = -1.0f;
        mClothStiffness = 0.4f;
        mRopeColorR = 0xff;
        mRopeColorG = 0x80;
        mRopeColorB = 0x80;
    }
    inline virtual ~daGFlag_HIO_c();
public:
    /* 0x04 */ s8 m04;
    /* 0x05 */ u8 m05;
    /* 0x06 */ s8 m06;
    /* 0x07 */ s8 m07;
    /* 0x08 */ s8 m08;
    /* 0x09 */ s8 m09;
    /* 0x0A */ /* 2 bytes of alignment padding */
    /* 0x0C */ u32 m0C;
    /* 0x10 */ u32 m10;
    /* 0x14 */ u32 m14;
    /* 0x18 */ u32 m18;
    /* 0x1C */ s32 m1C;
    /* 0x20 */ u32 m20;
    /* 0x24 */ u32 mRopeColorR;
    /* 0x28 */ u32 mRopeColorG;
    /* 0x2C */ u32 mRopeColorB;
    /* 0x30 */ f32 mWindScale1;
    /* 0x34 */ f32 mWindScale2;
    /* 0x38 */ f32 mFlagSagFactor;
    /* 0x3C */ f32 mClothStiffness;
};  // Size: 0x40
STATIC_ASSERT(sizeof(daGFlag_HIO_c) == 0x40);

class daGFlag_packet_c : public J3DPacket {
public:
    daGFlag_packet_c() {
        mCurrArr = 0;
        m0010 = 0;
    }
    virtual ~daGFlag_packet_c() {}
    void changeCurrentPos() { mCurrArr ^= 1; }
    cXyz* getDPos() { return mDPos[mCurrArr]; }
    Mtx* getMtx() { return &mMtx; }
    cXyz* getNrm() { return mNrm[mCurrArr]; }
    cXyz* getOffsetVec() { return mVelocity; }
    cXyz* getPos() { return mPos[mCurrArr]; }
    GXTexObj* getTexObjP() { return &mTexObj; }
    GXTexObj* getToonTexObjP() { return &mToonTexObj; }
    void setTevStr(dKy_tevstr_c* i_tevStr_p) { mpTevStr = i_tevStr_p; }
    cXyz* getBackNrm() { return mBackNrm[mCurrArr]; }

    void setTexObj(unsigned char);
    void setToonTexObj();
    void draw();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
public:
    /* 0x0010 */ s16 m0010;
    /* 0x0012 */ s16 mFlagWavePhase;
    /* 0x0014 */ GXTexObj mTexObj;
    /* 0x0034 */ GXTexObj mToonTexObj;
    /* 0x0054 */ Mtx mMtx;
    /* 0x0084 */ dKy_tevstr_c* mpTevStr;
    /* 0x0088 */ cXyz mPos[2][45];
    /* 0x04C0 */ cXyz mDPos[2][45];
    /* 0x08F8 */ cXyz mNrm[2][45];
    /* 0x0D30 */ cXyz mBackNrm[2][45];
    /* 0x1168 */ cXyz mVelocity[45];
    /* 0x1384 */ u8 mCurrArr;
    /* 0x1385 */ /* 3 bytes of alignment padding */
};  // Size: 0x1388
STATIC_ASSERT(sizeof(daGFlag_packet_c) == 0x1388);

class daGoal_Flag_c : public fopAc_ac_c {
public:
    typedef BOOL (daGoal_Flag_c::*ProcFunc)();

public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    cXyz* getRopePos(int i_matIdx, int i_segmentIdx) { 
        return &mMats[i_matIdx].getPos(0)[i_segmentIdx * 4]; 
    }
    void setAction(ProcFunc i_proc) { mCurrProc = i_proc; }

    BOOL getRacePath(u8);
    void RopeMove();
    BOOL CreateBuoyRaces();
    int goal_check();
    void flag_move();
    cXyz get_cloth_anim_factor(cXyz*, cXyz*, cXyz*, int, int);
    BOOL CreateHeap();
    int getDemoAction(int);
    BOOL RaceStart();
    BOOL TimerExecute();
    BOOL RaceEnd();

public:
    /* 0x0290 */ daGFlag_packet_c mFlagPacket;
    /* 0x1618 */ request_of_phase_process_class mPhs1;
    /* 0x1620 */ request_of_phase_process_class mPhs2;
    /* 0x1628 */ Mtx mMtx;
    /* 0x1658 */ cXyz mGoalFlagPolePos[2];
    /* 0x1670 */ s16 mWindScalePhase;
    /* 0x1672 */ /* 2 bytes of alignment padding */
    /* 0x1674 */ fpc_ProcID mTimerProcID;
    /* 0x1678 */ fpc_ProcID mMgameStartProcID;
    /* 0x167C */ fpc_ProcID mMgameTermProcID;
    /* 0x1680 */ f32 mPrevPlayerLineSide;
    /* 0x1684 */ s16 m1684;
    /* 0x1686 */ s16 m1686;
    /* 0x1688 */ u8 m1688;
    /* 0x1689 */ /* 3 bytes of alignment padding */
    /* 0x168C */ dPath* mpRopePaths[4];
    /* 0x169C */ u32 mNumRopeBuoys[4];
    /* 0x16AC */ int mNumRopes;
    /* 0x16B0 */ mDoExt_3DlineMat0_c mMats[4];
    /* 0x1720 */ ProcFunc mCurrProc;
};  // Size: 0x172C
STATIC_ASSERT(sizeof(daGoal_Flag_c) == 0x172C);

#endif /* D_A_GOAL_FLAG_H */
