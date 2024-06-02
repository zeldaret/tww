#ifndef D_A_BFLOWER_H
#define D_A_BFLOWER_H

#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daBFlower_c : public fopAc_ac_c {
public:
    inline BOOL _delete();

    BOOL CreateHeap();
    void CreateInit();
    void init_bck_anm(s16);
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
    /* 0x29C */ u8 m29C[0x534 - 0x29C];
    /* 0x534 */ mDoExt_bckAnm m534;
    /* 0x544 */ mDoExt_brkAnm m544;
    /* 0x55C */ u8 m55C[0x560 - 0x55C];
    /* 0x560 */ create_request* m560;
    /* 0x564 */ mDoExt_bckAnm mBck;
    /* 0x574 */ mDoExt_brkAnm mBrk;
    /* 0x58C */ u8 m58C[0x58F - 0x58C];
    /* 0x58F */ u8 m58F;
    /* 0x590 */ node_class* m590;
};

#endif /* D_A_BFLOWER_H */
