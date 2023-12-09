#ifndef D_A_MMUSIC_H
#define D_A_MMUSIC_H

#include "JSystem/JGeometry.h"
#include "f_op/f_op_actor.h"

namespace daMmusic {
class Act_c : public fopAc_ac_c {
public:
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    BOOL Macore_is_playing();
    void set_mtx();
    s32 _create();
    BOOL _delete();
    void init_se();
    void manage_se(int);
    void delete_se();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ BOOL field_0x298;
    /* 0x29C */ BOOL field_0x29C;
    /* 0x2A0 */ int field_0x2A0;
    /* 0x2A4 */ Mtx field_0x2A4;
    /* 0x2D4 */ short field_0x2D4;
    /* 0x2D6 */ u8 field_0x2D6[0x448 - 0x2D6];
};
};  // namespace daMmusic

#endif /* D_A_MMUSIC_H */
