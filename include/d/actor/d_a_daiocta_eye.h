#ifndef D_A_DAIOCTA_EYE_H
#define D_A_DAIOCTA_EYE_H

#include "SSystem/SComponent/c_math.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daDaiocta_Eye_c : public fopAc_ac_c {
public:
    void rndRotEye() {
        field_0x2E0 = cM_rndF(field_0x2F2);
        if (std::fabsf(field_0x2E0 - field_0x2E6) < field_0x2EC) {
            field_0x2E0 += field_0x2EC;
        }
        
        field_0x2E2 = cM_rndF(field_0x2F4);
        if (std::fabsf(field_0x2E2 - field_0x2E8) < field_0x2EE) {
            field_0x2E2 += field_0x2EE;
        }
        
        field_0x2E4 = cM_rndF(field_0x2F6);
        if (std::fabsf(field_0x2E4 - field_0x2EA) < field_0x2F0) {
            field_0x2E4 += field_0x2F0;
        }
    }

    void _nodeControl(J3DNode*, J3DModel*);
    void _createHeap();
    void _coHit(fopAc_ac_c*);
    void setMtx();
    void checkTgHit();
    void modeWaitInit();
    void modeWait();
    void modeDamageInit();
    void modeDamage();
    void modeDeathInit();
    void modeDeath();
    void modeProcCall();
    bool _execute();
    bool _draw();
    void createInit();
    cPhs_State _create();
    bool _delete();

public:
    /* 0x290 */ s32 field_0x290;
    /* 0x294 */ u8 field_0x294;
    /* 0x295 */ u8 field_0x295[0x296 - 0x295];
    /* 0x296 */ u8 field_0x296;
    /* 0x297 */ u8 field_0x297;
    /* 0x298 */ u8 field_0x298[0x2E0 - 0x298];
    /* 0x2E0 */ s16 field_0x2E0;
    /* 0x2E2 */ s16 field_0x2E2;
    /* 0x2E4 */ s16 field_0x2E4;
    /* 0x2E6 */ s16 field_0x2E6;
    /* 0x2E8 */ s16 field_0x2E8;
    /* 0x2EA */ s16 field_0x2EA;
    /* 0x2EC */ s16 field_0x2EC;
    /* 0x2EE */ s16 field_0x2EE;
    /* 0x2F0 */ s16 field_0x2F0;
    /* 0x2F2 */ s16 field_0x2F2;
    /* 0x2F4 */ s16 field_0x2F4;
    /* 0x2F6 */ s16 field_0x2F6;
    /* 0x2F8 */ u8 field_0x2F8[0x4A0 - 0x2F8];
};  // Size: 0x4A0

class daDaiocta_Eye_HIO_c {
public:
    daDaiocta_Eye_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_DAIOCTA_EYE_H */
