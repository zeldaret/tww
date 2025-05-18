#ifndef D_A_GM_H
#define D_A_GM_H

#include "f_op/f_op_actor.h"

class gm_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ u8 m2AC[0x2CD - 0x2AC];
    /* 0x2CD */ u8 m2CD;
    /* 0x2CE */ u8 m2CE[0x31E - 0x2CE];
    /* 0x31E */ s16 m31E;
    /* 0x320 */ u8 m320[0x3D0 - 0x320];
    /* 0x3D0 */ f32 z;
    /* 0x3D4 */ u8 m3D4[0x3DC - 0x3D4];
    /* 0x3DC */ f32 m3DC;
    /* 0x3E0 */ f32 m3E0;
    /* 0x3E4 */ u8 m3E4[0x43E - 0x3E4];
    /* 0x43E */ s16 m43E;
    /* 0x440 */ u8 m440[0x442 - 0x440];
    /* 0x442 */ s16 m442;
};

#endif /* D_A_GM_H */
