#ifndef D_A_ACORN_LEAF_H
#define D_A_ACORN_LEAF_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"

class daAleaf_c : public fopAc_ac_c {
public:
    BOOL CreateHeap();
    void CreateInit();
    void create_acorn();
    fpc_ProcID create_acorn_sub(bool);
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    bool _draw();
    inline bool _delete();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class unk_290;
    /* 0x298 */ J3DModel* unk_298;
    /* 0x29C */ dCcD_Stts unk_29C;
    /* 0x2D8 */ dCcD_Cyl unk_2D8;
    /* 0x408 */ mDoExt_bckAnm unk_408;
    /* 0x418 */ bool unk_418;
    /* 0x419 */ bool unk_419;
    /* 0x41A */ char unk41A[1];
    /* 0x41B */ s8 unk_41B;
    /* 0x41C */ s32 unk_41C;
    /* 0x420 */ s32 unk_420;
    /* 0x424 */ fpc_ProcID unk_424;
    /* 0x428 */ fpc_ProcID unk_428;
    /* 0x42C */ f32 unk_42C;
};

#endif /* D_A_ACORN_LEAF_H */
