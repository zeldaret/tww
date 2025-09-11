#ifndef D_A_OBJ_QUAKE_H
#define D_A_OBJ_QUAKE_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daObjQuake_c : public fopAc_ac_c {
public:
    enum Prm_e {
        PRM_SCH_W = 0x8,
        PRM_SCH_S = 0x0,

        PRM_TYPE_W = 0x3,
        PRM_TYPE_S = 0x8,

        PRM_POWER_W = 0x3,
        PRM_POWER_S = 0xB,
    };

    cPhs_State _create();
    BOOL _delete();
    BOOL _is_delete();
    BOOL _execute();
    u8 getPrmType();
    u8 getPrmSch();
    s32 getPrmPower();

public:
    /* 0x290 */ f32 m290;
    /* 0x294 */ f32 m294;
    /* 0x298 */ f32 m298;
    /* 0x29C */ f32 m29C;
    /* 0x2A0 */ u8 mType;
    /* 0x2A1 */ bool m2A1;
};

class daObjQuake_HIO_c : public JORReflexible {
public:
    daObjQuake_HIO_c();
    virtual ~daObjQuake_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ u8 field_0x0C;
    /* 0x0D */ u8 field_0x0D;
    /* 0x0E */ u8 field_0x0E;
    /* 0x0F */ u8 field_0x0F;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
};

#endif /* D_A_OBJ_QUAKE_H */
