#ifndef D_A_SPC_ITEM01_H
#define D_A_SPC_ITEM01_H

#include "d/actor/d_a_itembase.h"

class daSpcItem01_c : public daItemBase_c {
public:
    void set_mtx();
    BOOL _delete();
    s32 _create();
    BOOL CreateInit();
    BOOL _execute();
    void set_effect();
    void scale_anim();
    void anim_play();
    void move();
    void rotate_item();
    void setCol();
    BOOL _draw();
    void setTevStr();

    /* Place member variables here */
    f32 field_0x63C;
    s16 field_0x640;
    u8 field_0x642;
    u8 field_0x643;
    u16 field_0x644;
    u8 field_0x646;
    u8 field_0x647;
};

STATIC_ASSERT(sizeof(daSpcItem01_c) == 0x648);
#endif /* D_A_SPC_ITEM01_H */
