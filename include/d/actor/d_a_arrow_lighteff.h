#ifndef D_A_ARROW_LIGHTEFF_H
#define D_A_ARROW_LIGHTEFF_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_particle.h"
#include "d/d_kankyo.h"

class JPABaseEmitter;

class daArrow_Lighteff_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    inline void brk_play();

    void setTopPos();
    void setPointLight();
    void delete_particle();
    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ u32 field_0x290;
    /* 0x294 */ u32 field_0x294;
    /* 0x298 */ J3DModel* field_0x298;
    /* 0x29C */ cXyz field_0x29C;
    /* 0x2A8 */ cXyz field_0x2A8;
    /* 0x2B4 */ mDoExt_brkAnm mBrk;
    /* 0x2CC */ mDoExt_btkAnm mBtk;
    /* 0x2E0 */ f32 field_0x2E0;
    /* 0x2E4 */ s32 field_0x2E4;
    /* 0x2E8 */ u8 field_0x2E8;
    /* 0x2E9 */ u8 field_0x2E9;
    /* 0x2EA */ u8 field_0x2EA;
    /* 0x2EC */ u32 field_0x2EC;
    /* 0x2F0 */ u32 field_0x2F0;
    /* 0x2F4 */ dPa_followEcallBack field_0x2F4;
    /* 0x308 */ dPa_followEcallBack field_0x308;
    /* 0x31C */ LIGHT_INFLUENCE field_0x31C;
    /* 0x33C */ f32 field_0x33C;
}; // Size: 0x340

#endif /* D_A_ARROW_LIGHTEFF_H */
