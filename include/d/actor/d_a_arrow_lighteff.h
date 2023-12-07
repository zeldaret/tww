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
    void brk_play() {} // based on position in the debug map this would play the btk so not sure what this is really doing

    void setTopPos();
    void setPointLight();
    void delete_particle();
    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    u32 field_0x290;
    u32 field_0x294;
    J3DModel* field_0x298;
    cXyz field_0x29C;
    cXyz field_0x2A8;
    mDoExt_brkAnm mBrk;
    mDoExt_btkAnm mBtk;
    f32 field_0x2E0;
    s32 field_0x2E4;
    u8 field_0x2E8;
    u8 field_0x2E9;
    u8 field_0x2EA;
    u32 field_0x2EC;
    u32 field_0x2F0;
    dPa_followEcallBack field_0x2F4;
    dPa_followEcallBack field_0x308;
    LIGHT_INFLUENCE field_0x31C;
    f32 field_0x33C;
};

#endif /* D_A_ARROW_LIGHTEFF_H */
