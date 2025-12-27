#ifndef D_A_GOAL_FLAG_H
#define D_A_GOAL_FLAG_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daGFlag_packet_c : public J3DPacket {
public:
    daGFlag_packet_c() {
        field_0x1384 = false;
        field_0x0010 = 0;
    }
    void changeCurrentPos() {}
    void getDPos() {}
    void getMtx() {}
    void getNrm() {}
    void getOffsetVec() {}
    void getPos() {}
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
    /* 0x0088 */ cXyz field_0x0088[90];
    /* 0x04C0 */ cXyz field_0x04C0[90];
    /* 0x08F8 */ cXyz field_0x08F8[90];
    /* 0x0D30 */ cXyz field_0x0D30[90];
    /* 0x1168 */ cXyz field_0x1168[45];
    /* 0x1384 */ bool field_0x1384;
    /* 0x1385 */ u8 field_0x1385[0x1388 - 0x1385];
};  // Size: 0x1388

class daGoal_Flag_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void getRopePos(int, int) {}
    void setAction(int (daGoal_Flag_c::*)()) {}

    void getRacePath(unsigned char);
    void RopeMove();
    void CreateBuoyRaces();
    void goal_check();
    void flag_move();
    void get_cloth_anim_factor(cXyz*, cXyz*, cXyz*, int, int);
    void CreateHeap();
    void getDemoAction(int);
    void RaceStart();
    void TimerExecute();
    void RaceEnd();

public:
    /* 0x0290 */ daGFlag_packet_c field_0x0290;
    /* 0x1618 */ request_of_phase_process_class field_0x1618;
    /* 0x1620 */ request_of_phase_process_class field_0x1620;
    /* 0x1628 */ u8 field_0x1628[0x1658 - 0x1628];
    /* 0x1658 */ cXyz field_0x1658[2];
    /* 0x1670 */ u8 field_0x1670[0x1674 - 0x1670];
    /* 0x1674 */ fpc_ProcID field_0x1674;
    /* 0x1678 */ fpc_ProcID field_0x1678;
    /* 0x167C */ u8 field_0x167C[0x1688 - 0x167C];
    /* 0x1688 */ u8 field_0x1688;
    /* 0x1689 */ u8 field_0x1689[0x16AC - 0x1689];
    /* 0x16AC */ int field_0x16AC;
    /* 0x16B0 */ mDoExt_3DlineMat0_c field_0x16B0[4];
    /* 0x1720 */ int (daGoal_Flag_c::*field_0x1720)();
};  // Size: 0x172C

class daGoal_Flag_HIO_c {
public:
    virtual ~daGoal_Flag_HIO_c() {
        field_0x00 = -1;
    }
public:
    /* 0x00 */ s8 field_0x00;
};

#endif /* D_A_GOAL_FLAG_H */
