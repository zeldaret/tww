#ifndef D_A_OBJ_PLANT_H
#define D_A_OBJ_PLANT_H

#include "f_op/f_op_actor.h"

class daObjPlant_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline BOOL _draw();
    inline bool _execute();

    void CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts field_0x29C;
    /* 0x2D8 */ dCcD_Cyl field_0x2D8;
    /* 0x408 */ s16 field_0x408;
    /* 0x40A */ u8 field_0x40A[0x40E - 0x40A];
    /* 0x40E */ s16 field_0x40E;
    /* 0x410 */ u8 field_0x410;
    /* 0x411 */ u8 field_0x411[0x414 - 0x411];
};  // Size: 0x414


inline BOOL daObjPlant_c::_draw() {
    g_env_light.settingTevStruct(1, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList(); 
    cXyz shadow_vec;
    shadow_vec.x = 0.0f;
    shadow_vec.y = 1.0f;
    shadow_vec.z = 0.0f;
    dComIfGd_setSimpleShadow(&current.pos, current.pos.y, 60.0f, &shadow_vec, 0, 1.0f, &dDlst_shadowControl_c::mSimpleTexObj);
    return TRUE;
}

#endif /* D_A_OBJ_PLANT_H */
