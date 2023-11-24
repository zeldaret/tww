#ifndef D_A_DEMO_ITEM_H
#define D_A_DEMO_ITEM_H

#include "f_op/f_op_actor.h"

class daDitem_c : public fopAc_ac_c {
public:
    void Delete() {}
    void chkArgFlag(unsigned char) {}
    void clrFlag() {}
    void create() {}
    void draw() {}
    void execute() {}
    void isdelete() {}
    void setOffsetPos(cXyz) {}

    void setParticle();
    void CreateInit();
    void set_effect();
    void set_pos();
    void anim_control();
    void set_mtx();
    void settingBeforeDraw();
    void setListStart();

public:
    /* 0x290 */ u8 m290[0x65C - 0x290];
};

#endif /* D_A_DEMO_ITEM_H */
