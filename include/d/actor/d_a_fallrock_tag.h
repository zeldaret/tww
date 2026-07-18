#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "f_op/f_op_actor.h"
#include "c/c_dylink.h"
#include "f_pc/f_pc_node.h"

struct daFallRockTag_dataBase_c {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
};

class daFallRockTag_c : public fopAc_ac_c {
public:
    ~daFallRockTag_c() { cDyl_Unlink(fpcNm_FallRock_e); }

    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    daFallRockTag_dataBase_c* getData();

    void createRock(cXyz*, cXyz*, csXyz*, int, unsigned long);

    static f32 m_div_num;
    static daFallRockTag_dataBase_c m_data;

public:
    /* 0x290 */ u8 field_0x290[0x8];
    /* 0x298 */ s32 field_0x298;
    /* 0x29C */ u8 field_0x29C[0x2];
    /* 0x29E */ u8 mSchBit;
    /* 0x29F */ u8 field_0x29F[0x1];
};

#endif /* D_A_FALLROCK_TAG_H */
