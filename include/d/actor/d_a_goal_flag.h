#ifndef D_A_GOAL_FLAG_H
#define D_A_GOAL_FLAG_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

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
STATIC_ASSERT(sizeof(daGFlag_HIO_c) == 0x40);

class daGFlag_packet_c : public J3DPacket {
public:
    daGFlag_packet_c() {
        field_0x1384 = 0;
        field_0x0010 = 0;
    }
    virtual ~daGFlag_packet_c() {}
    void changeCurrentPos() {}
    void getDPos() {}
    void getMtx() {}
    void getNrm() {}
    void getOffsetVec() {}
    cXyz* getPos() { return field_0x0088[field_0x1384]; } // TODO: does getPos actually return field_0x0088?
    void getTexObjP() {}
    void getToonTexObjP() {}
    void setTevStr(dKy_tevstr_c*) {}

    void setTexObj(unsigned char);
    void setToonTexObj();
    void draw();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
public:
    /* 0x0010 */ s16 field_0x0010;
    /* 0x0012 */ u8 field_0x0012[0x0088 - 0x0012];
    /* 0x0088 */ cXyz field_0x0088[2][45];
    /* 0x04C0 */ cXyz field_0x04C0[90];
    /* 0x08F8 */ cXyz field_0x08F8[90];
    /* 0x0D30 */ cXyz field_0x0D30[90];
    /* 0x1168 */ cXyz field_0x1168[45];
    /* 0x1384 */ u8 field_0x1384;
    /* 0x1385 */ u8 field_0x1385[0x1388 - 0x1385];
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

    BOOL getRacePath(unsigned char);
    void RopeMove();
    void CreateBuoyRaces();
    int goal_check();
    void flag_move();
    void get_cloth_anim_factor(cXyz*, cXyz*, cXyz*, int, int);
    BOOL CreateHeap();
    void getDemoAction(int);
    BOOL RaceStart();
    BOOL TimerExecute();
    BOOL RaceEnd();

public:
    /* 0x0290 */ daGFlag_packet_c field_0x0290;
    /* 0x1618 */ request_of_phase_process_class field_0x1618;
    /* 0x1620 */ request_of_phase_process_class field_0x1620;
    /* 0x1628 */ Mtx field_0x1628;
    /* 0x1658 */ cXyz field_0x1658[2];
    /* 0x1670 */ u8 field_0x1670[0x1674 - 0x1670];
    /* 0x1674 */ fpc_ProcID field_0x1674;
    /* 0x1678 */ fpc_ProcID field_0x1678;
    /* 0x167C */ u8 field_0x167C[0x1680 - 0x167C];
    /* 0x1680 */ f32 field_0x1680;
    /* 0x1684 */ s16 field_0x1684;
    /* 0x1686 */ u8 field_0x1686[0x1688 - 0x1686];
    /* 0x1688 */ u8 field_0x1688;
    /* 0x1689 */ u8 field_0x1689[0x169C - 0x1689];
    /* 0x169C */ u32 field_0x169C[4];
    /* 0x16AC */ int field_0x16AC;
    /* 0x16B0 */ mDoExt_3DlineMat0_c field_0x16B0[4];
    /* 0x1720 */ ProcFunc field_0x1720;
};  // Size: 0x172C

#endif /* D_A_GOAL_FLAG_H */
