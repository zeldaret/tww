#ifndef D_A_OBJ_PLANT_H
#define D_A_OBJ_PLANT_H

#include "f_op/f_op_actor.h"

class daObjPlant_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts field_0x29C;
    /* 0x2D8 */ dCcD_Cyl field_0x2D8;
    /* 0x408 */ s16 field_0x408;
    /* 0x40A */ s16 field_0x40A;
    /* 0x40C */ s16 mHitTimer;
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

static BOOL _CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daObjPlant_c*>(i_this)->CreateHeap();
}

inline cPhs_State daObjPlant_c::_create() {
    fopAcM_SetupActor(this, daObjPlant_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, "Plant");

    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, _CheckCreateHeap, 0x0D20)) {
            return cPhs_ERROR_e;
        }
    
        CreateInit();
    }

    field_0x410 = 0; 
    return phase_state;
}

inline BOOL daObjPlant_c::_execute() {
    field_0x2D8.SetC(current.pos);
    dComIfG_Ccsp()->Set(&field_0x2D8);

    if ((mHitTimer > 0x38 || field_0x410 == 0) && field_0x2D8.ChkCoHit()) {
        
        fopAc_ac_c* hitAc = field_0x2D8.GetCoHitAc();
        
        cXyz diff = current.pos - hitAc->current.pos;
        s16 angle = cM_atan2s(diff.x, diff.z);
        
        field_0x40E = angle - 0x4000;
        field_0x410 = 1;
        mHitTimer = 0;
        field_0x40A = 0;
        
        fopAcM_seStart(this, 0x69E6, 0);
    }

    // 6. Wobble Animation
    if (field_0x410 != 0) {
        mHitTimer++;
        
        if (mHitTimer < 8) {
            field_0x408 = (s16)((0x100 - mHitTimer) * cM_ssin(field_0x40A) * 32.0f);
            field_0x40A += 0x1000;
        } else {
            field_0x408 = (s16)((0x100 - mHitTimer) * cM_ssin(field_0x40A) * 16.0f);
            field_0x40A += 0x0800;
        }
        
        // Reset after wobbling finishes
        if (mHitTimer > 0x100) {
            field_0x410 = 0;
            mHitTimer = 0;
            field_0x408 = 0;
        }
    }

    // 7. Update Model Matrix
    set_mtx();

    return TRUE;
}

#endif /* D_A_OBJ_PLANT_H */
