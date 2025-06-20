#ifndef D_A_FALLROCK_H
#define D_A_FALLROCK_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

class dCcD_SrcCyl;

class daFallRock_c : public fopAc_ac_c {
public:
    ~daFallRock_c();

    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();

    BOOL CreateHeap();
    void set_mtx();
    void setParticle(int, cXyz*);

    static char m_arcname[];
    static f32 m_falllen;
    static s16 m_rot_speed;

    static const dCcD_SrcCyl m_cyl_src;

public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ dBgS_ObjAcch field_0x29C;
    /* 0x460 */ dBgS_AcchCir field_0x460;
    /* 0x4A0 */ dCcD_Stts mStts;
    /* 0x4DC */ dCcD_Cyl mCyl;
    /* 0x60C */ GXColor field_0x60C;
    /* 0x610 */ f32 field_0x610;
    /* 0x614 */ int field_0x614;
};  // Size: 0x618

#endif /* D_A_FALLROCK_H */
