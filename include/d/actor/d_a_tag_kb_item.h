#ifndef D_A_TAG_KB_ITEM_H
#define D_A_TAG_KB_ITEM_H

#include "f_op/f_op_actor_mng.h"

class daTagKbItem_c : public fopAc_ac_c {
public:
    void getR() {}

    void kb_dig(fopAc_ac_c*);
    void dig_main();
    bool _delete();
    void CreateInit();
    int _create();
    bool _execute();
    bool _draw();

    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ u8 field_0x298;
    /* 0x299 */ u8 field_0x299;
    /* 0x29C */ s32 field_0x29c;
    /* 0x2A0 */ u8 field_0x2a0;
    /* 0x2A1 */ u8 field_0x2a1;
    /* 0x2A4 */ s32 field_0x2a4;
    /* 0x2A8 */ fopAc_ac_c* mpActor;
};  // Size: 0x2AC

#endif /* D_A_TAG_KB_ITEM_H */
