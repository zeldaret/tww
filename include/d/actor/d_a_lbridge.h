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
    /* 0x298 */ J3DModel *unk298;                   /* inferred */
    /* 0x29C */ dBgW *mpBgW;                        /* inferred */
    /* 0x2A0 */ Mtx mMtx;                           /* inferred */
    /* 0x2D0 */ mDoExt_btkAnm unk2D0;               /* inferred */
    /* 0x2D0 */ char pad2D0[4];
    /* 0x2D4 */ void *unk2D4;                       /* inferred */
    /* 0x2D8 */ char pad2D8[4];
    /* 0x2DC */ s32 unk2DC;                         /* inferred */
    /* 0x2E0 */ char pad2E0[4];
    /* 0x2E4 */ mDoExt_bpkAnm unk2E4;               /* inferred */
    /* 0x2E4 */ char pad2E4[4];
    /* 0x2E8 */ void *unk2E8;                       /* inferred */
    /* 0x2EC */ char pad2EC[4];
    /* 0x2F0 */ s32 unk2F0;                         /* inferred */
    /* 0x2F4 */ char pad2F4[4];
    /* 0x2F8 */ mDoExt_brkAnm unk2F8;               /* inferred */
    /* 0x2F8 */ char pad2F8[4];
    /* 0x2FC */ void *unk2FC;                       /* inferred */
    /* 0x300 */ char pad300[4];
    /* 0x304 */ s32 unk304;                         /* inferred */
    /* 0x308 */ s32 unk308;                         /* inferred */
    /* 0x30C */ char pad30C[4];
    /* 0x310 */ void *unk310;                       /* inferred */
    /* 0x314 */ s32 unk314;                         /* inferred */
    /* 0x318 */ s16 unk318;                         /* inferred */
    /* 0x31A */ s16 unk31A;                         /* inferred */
    /* 0x31C */ s16 unk31C;                         /* inferred */
    /* 0x31E */ u8 unk31E;                          /* inferred */
    /* 0x31F */ u8 unk31F;                          /* inferred */
};

#endif /* D_A_LBRIDGE_H */
