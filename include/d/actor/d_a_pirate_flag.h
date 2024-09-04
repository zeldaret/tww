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
};

class daPirate_Flag_HIO_c : public JORReflexible {
public:
    daPirate_Flag_HIO_c() {}
    virtual ~daPirate_Flag_HIO_c() {
        mChildID = -1;
    }

public:
    /* 0x04 */ s8 mChildID;
};

class pirate_flag_class : public fopAc_ac_c {
public:
    /* Place member variables here */
    /* 0x290 */ request_of_phase_process_class mPhs1;
    /* 0x298 */ request_of_phase_process_class mPhs2;
};

#endif /* D_A_PIRATE_FLAG_H */
