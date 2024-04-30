#ifndef D_A_LBRIDGE_H
#define D_A_LBRIDGE_H

#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor.h"


class daLbridge_c : public fopAc_ac_c {
public:
    inline BOOL _delete();

    BOOL CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void setMoveBGMtx();
    BOOL _execute();
    void sw_check();
    void demo();
    void appear_bridge();
    void disappear_bridge();
    void set_on_se();
    void set_off_se();
    BOOL _draw();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel *mpModel;                  /* inferred */
    /* 0x29C */ dBgW *mpBgW;                        /* inferred */
    /* 0x2A0 */ Mtx mMtx;                           /* inferred */
    /* 0x2D0 */ mDoExt_btkAnm mBtkAnm;              /* inferred */
    /* 0x2E4 */ mDoExt_bpkAnm mBpkAnm;              /* inferred: Might be wrong (doesn't match) */
    /* 0x2F8 */ mDoExt_brkAnm mBrkAnm;              /* inferred */
    /* 0x310 */ void *unk310;                       /* inferred */
    /* 0x314 */ s32 mSwitchNo;                      /* inferred */
    /* 0x318 */ s16 unk318;                         /* inferred */
    /* 0x31A */ s16 unk31A;                         /* inferred */
    /* 0x31C */ s16 unk31C;                         /* inferred */
    /* 0x31E */ u8 unk31E;                          /* inferred */
    /* 0x31F */ u8 unk31F;                          /* inferred */
};

#endif /* D_A_LBRIDGE_H */
