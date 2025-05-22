#ifndef D_A_FIRE_H
#define D_A_FIRE_H

#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class JPABaseEmitter;

class daFire_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateInit();
    cPhs_State _create();
    bool _execute();
    void search_wind();
    void ctrlEffect();
    void demo_proc();
    void normal_proc();
    void eventOrder();
    void checkOrder();
    void execStopFire();
    void execStopNowFire();
    void execPlayFire();
    void setDirParticle(cXyz*);
    void checkCol();
    bool _draw();

public:
    /* 0x290 */ dCcD_Stts mStts;
    /* 0x2CC */ dCcD_Cyl field_0x2CC[3];
    /* 0x65C */ dCcD_Cyl field_0x65C;
    /* 0x78C */ dCcD_Cyl field_0x78C;
    /* 0x8BC */ JPABaseEmitter* field_0x8BC;
    /* 0x8C0 */ JPABaseEmitter* field_0x8C0;
    /* 0x8C4 */ JPABaseEmitter* field_0x8C4;
    /* 0x8C8 */ s32 mSwitchNo;
    /* 0x8CC */ u32 mTrboxBit;
    /* 0x8D0 */ u8 mShape;
    /* 0x8D1 */ u8 field_0x8D1;
    /* 0x8D2 */ u8 field_0x8D2;
    /* 0x8D4 */ cXyz field_0x8D4;
    /* 0x8E0 */ cXyz field_0x8E0;
    /* 0x8EC */ u8 field_0x8EC;
    /* 0x8ED */ bool field_0x8ED;
    /* 0x8EE */ u8 field_0x8EE[0x8F0 - 0x8EE];
    /* 0x8F0 */ fpc_ProcID field_0x8F0;
    /* 0x8F4 */ s32 field_0x8F4;
    /* 0x8F8 */ s32 field_0x8F8;
    /* 0x8FC */ s16 field_0x8FC;
    /* 0x8FE */ s16 field_0x8FE;
    /* 0x900 */ u8 mType;
    /* 0x901 */ s8 field_0x901;
    /* 0x902 */ u8 field_0x902;
    /* 0x903 */ u8 field_0x903;
};

namespace daFire_prm {
    inline u8 getSwitch(daFire_c* ac) {
        return fopAcM_GetParam(ac);
    }

    inline u8 getTrboxBit(daFire_c* ac) {
        return (fopAcM_GetParam(ac) >> 12) & 0x1F;
    }

    inline u8 getType(daFire_c* ac) {
        return (fopAcM_GetParam(ac) >> 17) & 0x7;
    }

    inline u8 getShape(daFire_c* ac) {
        return (fopAcM_GetParam(ac) >> 8) & 0xF;
    }

    inline u8 getSound(daFire_c* ac) {
        return (fopAcM_GetParam(ac) >> 20) & 0xF;
    }
}

#endif /* D_A_FIRE_H */
