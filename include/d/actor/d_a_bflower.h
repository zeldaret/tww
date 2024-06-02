#ifndef D_A_BFLOWER_H
#define D_A_BFLOWER_H

#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"

class daBFlower_c : public fopAc_ac_c {
public:
    inline BOOL _delete();

    BOOL CreateHeap();
    void CreateInit();
    int init_bck_anm(s16 param);
    s32 _create();
    void set_mtx();
    BOOL _execute();
    void actLive();
    void actDead();
    void animPlay();
    void setCollision();
    BOOL _draw();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ dCcD_Sph mSph;
    /* 0x534 */ mDoExt_bckAnm mBck1;
    /* 0x544 */ mDoExt_brkAnm mBrk1;
    /* 0x55C */ s16 m55C;
    /* 0x55E */ u8 m55E[0x560 - 0x55E];
    /* 0x560 */ J3DModel* mpModel2;
    /* 0x564 */ mDoExt_bckAnm mBck2;
    /* 0x574 */ mDoExt_brkAnm mBrk2;
    /* 0x58C */ u8 m58C;
    /* 0x58D */ u8 m58D;
    /* 0x58E */ u8 m58E;
    /* 0x58F */ u8 mKind;
    /* 0x590 */ s32 mSwitchNo;
    /* 0x594 */ s32 m594;
    /* 0x598 */ s32 m598;
    /* 0x59C */ fopAc_ac_c* m59C;
    /* 0x5A0 */ s32 m5A0;
    /* 0x5A4 */ f32 m5A4;
    /* 0x5A8 */ u32 m5A8;
    /* 0x5AC */ cXyz m5AC;
    /* 0x5B8 */ u8 m5B8;
};

namespace daBFlower_prm {
    inline u8 getKind(daBFlower_c* actor) {
        return (fopAcM_GetParam(actor) >> 4) & 0xF;
    }

    inline u8 getSwitchNo(daBFlower_c* actor) {
        return (fopAcM_GetParam(actor) >> 8) & 0xFF;
    }
}

#endif /* D_A_BFLOWER_H */
