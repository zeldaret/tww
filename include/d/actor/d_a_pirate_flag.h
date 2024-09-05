#ifndef D_A_PIRATE_FLAG_H
#define D_A_PIRATE_FLAG_H

#include "f_op/f_op_actor.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_hostIO.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"


class daPirate_Flag_packet_c : public J3DPacket {
public:
    void changeCurrentPos() {}
    void getEscapeNrmAngle() {}
    void getMtx() {}
    void getNrm() {}
    void getOffsetVec() {}
    void getPos() {}
    void setNrmMtx() {}
    void setTevStr(dKy_tevstr_c*) {}

    void setCorrectNrmAngle(s16, f32);
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
    void draw();
public:
    /* 0x010 */ Mtx m010;
    /* 0x040 */ dKy_tevstr_c* m040;
    /* 0x044 */ u8 m044[0x878 - 0x044];
    /* 0x878 */ s16 m878;
    /* 0x87A */ s16 m87A;
    /* 0x87C */ s16 m87C;
    /* 0x87E */ u8 m87E;
};

class daPirate_Flag_HIO_c : public JORReflexible {
public:
    daPirate_Flag_HIO_c() {}
    virtual ~daPirate_Flag_HIO_c() {
        mChildID = -1;
    }

public:
    /* 0x04 */ s8 mChildID;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ s32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
};

class pirate_flag_class : public fopAc_ac_c {
public:
    /* Place member variables here */
    /* 0x290 */ request_of_phase_process_class mPhs1;
    /* 0x298 */ request_of_phase_process_class mPhs2;
    /* 0x2A0 */ u8 pad2A0[0x18];
    /* 0x2B8 */ daPirate_Flag_packet_c packet;
};

#endif /* D_A_PIRATE_FLAG_H */
