#ifndef D_A_TAG_KB_ITEM_H
#define D_A_TAG_KB_ITEM_H

#include "f_op/f_op_actor.h"

class daTagKbItem_c : public fopAc_ac_c {
public:
    void getR() {}

    void kb_dig(fopAc_ac_c*);
    void dig_main();
    bool _delete();
    void CreateInit();
    cPhs_State _create();
    bool _execute();
    bool _draw();

    /* 0x290 */ request_of_phase_process_class mPhase; // Unused
    /* 0x298 */ bool field_0x298;
    /* 0x299 */ bool field_0x299;
    /* 0x29C */ int mItemBitNo;
    /* 0x2A0 */ u8 mItemNo;
    /* 0x2A1 */ u8 mEnemyKind;
    /* 0x2A4 */ int mSwBitNo;
    /* 0x2A8 */ fopAc_ac_c* mpActor;
};  // Size: 0x2AC

#endif /* D_A_TAG_KB_ITEM_H */
