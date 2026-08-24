/**
 * d_a_obj_htetu1.cpp
 * Object - Tower of the Gods - Large yellow gate (blocks room containing Small Key)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_htetu1.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_bg_w.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_particle_name.h"
#include "dolphin/types.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_draw_priority.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Htetu1.h"

const u16 l_daObjHtetu1_splash_id_table[] = {
    dPa_name::ID_AK_SN_SIRENWATERGATE00,
    dPa_name::ID_AK_SN_SIRENWATERGATE01
};
const char daObjHtetu1_c::M_arcname[7] = "Htetu1";

/* 00000078-00000178       .text create_s__19daObjHtetu1Splash_cFUsP4cXyzP5csXyzP12dKy_tevstr_c */
void daObjHtetu1Splash_c::create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*) {
    /* Nonmatching */
}

/* 00000178-00000198       .text solidHeapCB__13daObjHtetu1_cFP10fopAc_ac_c */
BOOL daObjHtetu1_c::solidHeapCB(fopAc_ac_c *f) {
    /* Nonmatching */
    return ((daObjHtetu1_c*)f)->create_heap();
}

/* 00000198-00000298       .text create_heap__13daObjHtetu1_cFv */
BOOL daObjHtetu1_c::create_heap() {
    /* Nonmatching */
    BOOL ret = TRUE;
    
    J3DModelData *mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTETU1_BDL_HTETU1_e));
    JUT_ASSERT(0x119, mdl_data != NULL);
    if (mdl_data == NULL) ret = FALSE;
    else {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        Mtx *mdl = &mpModel->getBaseTRMtx();
        cBgD_t *pcVar3 = (cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTETU1_DZB_HTETU1_e);
        field_0x2CC = dBgW_NewSet(pcVar3, cBgW::MOVE_BG_e, mdl);
        if (field_0x2CC == NULL) ret = FALSE;
    }
    return ret;
}

/* 00000298-00000460       .text _create__13daObjHtetu1_cFv */
cPhs_State daObjHtetu1_c::_create() {
    /* Nonmatching */
    fopAcM_ct(this, daObjHtetu1_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);

    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xae0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            field_0x29C = base.base.mParameters & 0xff;
            field_0x2B8 = current.pos.y - 2300;
            if (check_sw() != 0) {
                current.pos.y = field_0x2B8;
                field_0x2C6 = 2;
            }
            field_0x2C8 = -1;
            init_mtx();
            g_env_light.settingTevStruct(2, &current.pos, &tevStr);

            for (int i = 0; i < 2; i++) {
                field_0x2D0[i].create_s(l_daObjHtetu1_splash_id_table[i], &current.pos, &current.angle, &tevStr);
            }
            fopAcM_setCullSizeBox(this, -950, -1000, -100, 950, 1300, 100);
            dComIfG_Bgsp()->Regist(field_0x2CC, this);
            field_0x2C4 = dComIfGp_evmng_getEventIdx("htetu1_open");
            phase_state = cPhs_COMPLEATE_e;
        }
    }
    return phase_state;
}

/* 00000508-00000610       .text _delete__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_delete() {
    /* Nonmatching*/
}

/* 00000610-00000648       .text check_sw__13daObjHtetu1_cFv */
BOOL daObjHtetu1_c::check_sw() {
    /* Nonmatching */
    return g_dComIfG_gameInfo.save.isSwitch(field_0x29C, home.roomNo);
}

/* 00000648-000006E4       .text init_mtx__13daObjHtetu1_cFv */
void daObjHtetu1_c::init_mtx() {
    /* Nonmatching */
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 000006E4-000007F8       .text unlock__13daObjHtetu1_cFv */
void daObjHtetu1_c::unlock() {
    /* Nonmatching */
}

/* 000007F8-0000098C       .text get_water_h__13daObjHtetu1_cFv */
void daObjHtetu1_c::get_water_h() {
    /* Nonmatching */
}

/* 00000AB0-00000BCC       .text splash_manager__13daObjHtetu1_cFv */
void daObjHtetu1_c::splash_manager() {
    /* Nonmatching */
}

/* 00000BCC-0000101C       .text _execute__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_execute() {
    /* Nonmatching */
}

/* 0000101C-0000107C       .text _draw__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_draw() {
    /* Nonmatching */
    g_env_light.settingTevStruct(1, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return 1;
}

namespace {
/* 0000107C-0000109C       .text Mthd_Create__28@unnamed@d_a_obj_htetu1_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_create();
}

/* 0000109C-000010C0       .text Mthd_Delete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_delete();
}

/* 000010C0-000010E4       .text Mthd_Execute__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_execute();
}

/* 000010E4-00001108       .text Mthd_Draw__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_draw();
}

/* 00001108-00001110       .text Mthd_IsDelete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Htetu1_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Htetu1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Htetu1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHtetu1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Htetu1_e,
    /* Actor SubMtd */ &Htetu1_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
