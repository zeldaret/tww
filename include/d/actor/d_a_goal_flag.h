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
        m30 = 12.0f;
        m34 = 4.0f;
        m38 = -1.0f;
        m3C = 0.4f;
        m24 = 0xff;
        m28 = 0x80;
        m2C = 0x80;
    }
    inline virtual ~daGFlag_HIO_c();
public:
    /* 0x04 */ s8 m04;
    /* 0x05 */ s8 m05;
    /* 0x06 */ s8 m06;
    /* 0x07 */ s8 m07;
    /* 0x08 */ s8 m08;
    /* 0x09 */ s8 m09;
    /* 0x0A */ u8 field_0x0A[0x0C - 0x0A];
    /* 0x0C */ u32 m0C;
    /* 0x10 */ u32 m10;
    /* 0x14 */ u32 m14;
    /* 0x18 */ u32 m18;
    /* 0x1C */ u32 m1C;
    /* 0x20 */ u32 m20;
    /* 0x24 */ u32 m24;
    /* 0x28 */ u32 m28;
    /* 0x2C */ u32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
};  // Size: 0x40

class daGFlag_packet_c : public J3DPacket {
public:
    daGFlag_packet_c() {
        mCurrArr = 0;
        m0010 = 0;
    }
    virtual ~daGFlag_packet_c() {}
    void changeCurrentPos() { mCurrArr = mCurrArr ^ 1; }
    cXyz* getDPos() { return mDPos[mCurrArr]; }
    Mtx* getMtx() { return &mMtx; }
    cXyz* getNrm() { return mNrm[mCurrArr]; }
    cXyz* getOffsetVec() { return m1168; }
    cXyz* getPos() { return mPos[mCurrArr]; }
    GXTexObj* getTexObjP() { return &m0014; }
    GXTexObj* getToonTexObjP() { return &m0034; }
    void setTevStr(dKy_tevstr_c* i_tevStr_p) { field_0x0084 = i_tevStr_p; }

    void setTexObj(unsigned char);
    void setToonTexObj();
    void draw();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
public:
    /* 0x0010 */ s16 m0010;
    /* 0x0012 */ s16 m0012;
    /* 0x0014 */ GXTexObj m0014;
    /* 0x0034 */ GXTexObj m0034;
    /* 0x0054 */ Mtx mMtx;
    /* 0x0084 */ dKy_tevstr_c* field_0x0084;
    /* 0x0088 */ cXyz mPos[2][45];
    /* 0x04C0 */ cXyz mDPos[2][45];
    /* 0x08F8 */ cXyz mNrm[2][45];
    /* 0x0D30 */ cXyz mBackNrm[2][45];
    /* 0x1168 */ cXyz m1168[45];
    /* 0x1384 */ u8 mCurrArr;
    /* 0x1385 */ u8 m1385[0x1388 - 0x1385];
};  // Size: 0x1388

class daGoal_Flag_c : public fopAc_ac_c {
public:
    typedef BOOL (daGoal_Flag_c::*ProcFunc)();
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    // TODO: does getRopePos actually do this?
    cXyz* getRopePos(int i_matIdx, int i_segmentIdx) { return field_0x16B0[i_matIdx].getPos(0) + (i_segmentIdx * 4); }
    void setAction(ProcFunc i_proc) { field_0x1720 = i_proc; }

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
    /* 0x0290 */ daGFlag_packet_c field_0x0290;
    /* 0x1618 */ request_of_phase_process_class field_0x1618;
    /* 0x1620 */ request_of_phase_process_class field_0x1620;
    /* 0x1628 */ Mtx field_0x1628;
    /* 0x1658 */ cXyz field_0x1658[2];
    /* 0x1670 */ s16 field_0x1670;
    /* 0x1672 */ u8 field_0x1672[0x1674 - 0x1672];
    /* 0x1674 */ fpc_ProcID field_0x1674;
    /* 0x1678 */ fpc_ProcID field_0x1678;
    /* 0x167C */ u8 field_0x167C[0x1680 - 0x167C];
    /* 0x1680 */ f32 field_0x1680;
    /* 0x1684 */ s16 field_0x1684;
    /* 0x1686 */ s16 field_0x1686;
    /* 0x1688 */ u8 field_0x1688;
    /* 0x1689 */ u8 field_0x1689[0x168C - 0x1689];
    /* 0x168C */ dPath* field_0x168C[4];
    /* 0x169C */ u32 field_0x169C[4];
    /* 0x16AC */ int field_0x16AC;
    /* 0x16B0 */ mDoExt_3DlineMat0_c field_0x16B0[4];
    /* 0x1720 */ ProcFunc field_0x1720;
};  // Size: 0x172C

#endif /* D_A_GOAL_FLAG_H */
