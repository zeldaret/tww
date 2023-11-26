#ifndef D_A_MMUSIC_H
#define D_A_MMUSIC_H

#include "f_op/f_op_actor.h"

namespace daMmusic {
class Act_c : public fopAc_ac_c {
public:
    BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    BOOL Macore_is_playing();
    void set_mtx();
    s32 _create();
    BOOL _delete();
    void init_se();
    void manage_se(int);
    void delete_se();
    BOOL _execute();
    BOOL _draw();

public:
    /* 0x290 */ u8 field_0x290[0x2D4 - 0x290];
    /* 0x2D4 */ short field_0x2D4;
};
};  // namespace daMmusic

#endif /* D_A_MMUSIC_H */
