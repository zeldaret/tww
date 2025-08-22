#ifndef D_A_PIRATE_FLAG_H
#define D_A_PIRATE_FLAG_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_phase.h"

class daPirate_Flag_packet_c : public J3DPacket {
public:
    daPirate_Flag_packet_c() {
        m87E = 0;
        m878 = 0;
        m87C = 0;
        m87A = 0;
        m87F = 1;
    }

    virtual ~daPirate_Flag_packet_c() {}

    MtxP getMtx() { return mMtx; }
    void setTevStr(dKy_tevstr_c* i_tevStr) { mTevStr = i_tevStr; }
    cXyz* getPos() { return mPos[m87E]; }
    cXyz* getNrm() { return mNrm[m87E]; }
    cXyz* getBackNrm() { return mBackNrm[m87E]; }
    cXyz* getOffsetVec() { return m74C; } // Guessed based on size in debug maps
    s16 getEscapeNrmAngle() { return m87A; }
    void changeCurrentPos() { m87E ^= 1; }
    void setNrmMtx() {
        cMtx_YrotS(*calc_mtx, m878);
    }

    void setCorrectNrmAngle(s16, f32);
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
    void draw();
public:
    /* 0x010 */ Mtx mMtx;
    /* 0x040 */ dKy_tevstr_c* mTevStr;
    /* 0x044 */ cXyz mPos[2][25];
    /* 0x29C */ cXyz mNrm[2][25];
    /* 0x4F4 */ cXyz mBackNrm[2][25];
    /* 0x74C */ cXyz m74C[25];
    /* 0x878 */ s16 m878;
    /* 0x87A */ s16 m87A;
    /* 0x87C */ s16 m87C;
    /* 0x87E */ u8 m87E;
    /* 0x87F */ u8 m87F;
};

class pirate_flag_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs1;
    /* 0x298 */ request_of_phase_process_class mPhs2;
    /* 0x2A0 */ u8 pad2A0[0x08];
    /* 0x2A8 */ s16 m2A8;
    /* 0x2AA */ u8 pad2AA[0x0C];
    /* 0x2B8 */ daPirate_Flag_packet_c mPacket;
};

#endif /* D_A_PIRATE_FLAG_H */
