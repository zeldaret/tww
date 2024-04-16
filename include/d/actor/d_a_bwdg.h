#ifndef D_A_BWDG_H
#define D_A_BWDG_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_phase.h"

class dBgWHf;

class daBwdg_packet_c : public J3DPacket {
public:
    daBwdg_packet_c() {
        m00010 = 0;
    }
    virtual ~daBwdg_packet_c() {}

    MtxP getMtx() { return mMtx; }
    void setTevStr(dKy_tevstr_c* tevstr) { mpTevStr = tevstr; }
    cXyz* getPos() { return &mPos[m00010 * 0x1081]; }
    cXyz* getNrm() { return &mNrm[m00010 * 0x1081]; }

    void draw();

public:
    /* 0x00010 */ u8 m00010;
    /* 0x00014 */ Mtx mMtx;
    /* 0x00044 */ dKy_tevstr_c* mpTevStr;
    /* 0x00048 */ cXyz mPos[0x1081 * 2];
    /* 0x18C60 */ cXyz mNrm[0x1081 * 2];
};  // Size: 0x31878

class bwdg_class : public fopAc_ac_c {
public:
    /* 0x00290 */ u8 m00290[0x002AC - 0x00290];
    /* 0x002AC */ request_of_phase_process_class mPhase;
    /* 0x002B4 */ s16 m002B4;
    /* 0x002B6 */ u8 m002B6[0x002B8 - 0x002B6];
    /* 0x002B8 */ s16 m002B8;
    /* 0x002BC */ dBgWHf* mpBgW;
    /* 0x002C0 */ f32 m002C0[0x1081];
    /* 0x044C4 */ daBwdg_packet_c mBwdgPacket;
    /* 0x35D3C */ u8 m35D3C[0x35D40 - 0x35D3C];
};  // Size: 0x35D40

#endif /* D_A_BWDG_H */
