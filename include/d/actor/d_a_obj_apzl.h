#ifndef D_A_OBJ_APZL_H
#define D_A_OBJ_APZL_H

#include "f_op/f_op_actor.h"
#include "d/d_lib.h"

class daObjApzl_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    u8 getblank() { return field_0x476[field_0x471]; } // maybe field_0x471 is blank index

    bool move_piece();
    void check_arrow_draw();
    u8 search_piece(u8);
    void swap_piece(u8, u8);
    void randamize_piece();
    void save_piece();
    bool check_clear();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    u16 talk(int);
    void privateCut();
    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* field_0x298[16];
    /* 0x2D8 */ J3DModel* field_0x2D8[4];
    /* 0x2E8 */ J3DModel* field_0x2E8[16];
    /* 0x328 */ mDoExt_btpAnm field_0x328[16];
    /* 0x468 */ u8 field_0x468;
    /* 0x469 */ u8 field_0x469[0x46C - 0x469];
    /* 0x46C */ STControl* stick;
    /* 0x470 */ u8 field_0x470;
    /* 0x471 */ u8 field_0x471; // blank piece
    /* 0x472 */ u8 field_0x472;
    /* 0x473 */ u8 field_0x473;
    /* 0x474 */ u8 field_0x474;
    /* 0x475 */ bool field_0x475;
    /* 0x476 */ u8 field_0x476[16]; // piece pos?
    /* 0x486 */ u8 field_0x486;
    /* 0x487 */ u8 field_0x487[4];
    /* 0x48B */ u8 field_0x48B[0x48C - 0x48B];
    /* 0x48C */ s16 field_0x48C;
    /* 0x48E */ s16 field_0x48E;
    /* 0x490 */ s16 field_0x490;
    /* 0x492 */ s8 mActIdx;
    /* 0x493 */ bool field_0x493;
    /* 0x494 */ bool field_0x494;
    /* 0x495 */ bool field_0x495;
    /* 0x496 */ bool field_0x496;
    /* 0x497 */ bool field_0x497;
    /* 0x498 */ bool field_0x498;
    /* 0x499 */ u8 field_0x499[0x49C - 0x499];
    /* 0x49C */ fpc_ProcID mProcId[30];
    /* 0x514 */ int field_0x514;
    /* 0x518 */ u32 mMsgNo;
    /* 0x51C */ u32 field_0x51C;
    /* 0x520 */ msg_class* mpCurrMsg;
    /* 0x524 */ int field_0x524;
};  // Size: 0x528

namespace daObjApzl_prm {
    inline u8 getType(daObjApzl_c* i_this) { return (fopAcM_GetParam(i_this) >> 8); }
}

#endif /* D_A_OBJ_APZL_H */
