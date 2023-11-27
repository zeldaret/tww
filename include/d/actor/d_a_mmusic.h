#ifndef D_A_MMUSIC_H
#define D_A_MMUSIC_H

#include "f_op/f_op_actor.h"

namespace daMmusic {
class Act_c : public fopAc_ac_c {
public:
    bool solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    bool Macore_is_playing();
    void set_mtx();
    s32 _create();
    bool _delete();
    void init_se();
    void manage_se(int);
    void delete_se();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ u8 field_0x290[0x2A0 - 0x290];
    /* 0x2A2 */ int field_0x2A0;
    /* 0x2A2 */ u8 field_0x2A2[0x2A4 - 0x2A2];  
    /* 0x2A4 */ int field_0x2A4;
    /* 0x2A8 */ u8 field_0x2A8[0x2D4 - 0x2A8];
    /* 0x2D4 */ short field_0x2D4;
    /* 0x2D6 */ u8 field_0x2D6[0x300 - 0x2D6];
};
};  // namespace daMmusic

#endif /* D_A_MMUSIC_H */
