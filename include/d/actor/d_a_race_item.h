#ifndef D_A_RACE_ITEM_H
#define D_A_RACE_ITEM_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_itembase.h"

class daRaceItem_c : public fopAc_ac_c {
public:
    void draw() {}
    void execute() {}
    void setListStart() {}

    void set_mtx();
    void Delete();
    void create();
    void CreateInit();
    void checkGet();

public:
    /* 0x000 */ daItemBase_c parent;
    /* 0x63C */ u8 m63C[0x648 - 0x63C];
};

#endif /* D_A_RACE_ITEM_H */
