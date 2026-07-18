/**
 * d_a_obj_trap.cpp
 * Enemy - Blade Trap (normal)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_trap.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "f_pc/f_pc_draw_priority.h"
#include "f_pc/f_pc_name.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Trap.h"

/* 000000EC-0000010C       .text solidHeapCB__11daObjTrap_cFP10fopAc_ac_c */
void daObjTrap_c::solidHeapCB(fopAc_ac_c*) {
    create_heap();
}

f32 const daObjTrap_c::M_speed_table[] = {50.0f, 80.0f, 100.0f};
s16 const daObjTrap_c::M_wait_f_table[] = {30, 10, 0};
const char daObjTrap_c::M_arcname[] = "Trap";

/* 0000010C-000002A4       .text create_heap__11daObjTrap_cFv */
bool daObjTrap_c::create_heap() {
    /* Nonmatching */
    bool result = false;
    J3DModelData* mdl_data =
        (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_ID_TRAP_BDL_HTORA1_e);
    JUT_ASSERT(355, mdl_data != NULL);
    if (mdl_data){
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000222);
        if (mpModel != NULL){
            J3DAnmTextureSRTKey* btk_data = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(
                M_arcname, dRes_ID_TRAP_BTK_HTORA1_e);
            JUT_ASSERT(364, btk_data != NULL);
            if (btk_data){
                int btk_anm_init_result = mBtkAnm.init(mdl_data, btk_data, true, JUTGamePad::CRumble::LOOP_ONCE, 1.0, 0, -1, false, FALSE);
                if (btk_anm_init_result){
                    Mtx &mdl_tr_mtx = mpModel->getBaseTRMtx();
                    cBgD_t* dzb_data =
                        (cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_ID_TRAP_DZB_HTORA1_e);
                    mpcBgW = D_BG_W_H::dBgW_NewSet(dzb_data, cBgW::MOVE_BG_e, &mdl_tr_mtx);
                    if (mpcBgW != NULL){
                        result = true;
                    }
                }
            }
        }
    }

    return result;
}

/* 000002A4-00000510       .text _create__11daObjTrap_cFv */
cPhs_State daObjTrap_c::_create() {
    /* Nonmatching */
}

/* 00000DF0-00000E84       .text _delete__11daObjTrap_cFv */
bool daObjTrap_c::_delete() {
    if (heap != NULL) {
        if (mpcBgW != NULL) {
            if (mpcBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpcBgW);
                mpcBgW = NULL;
            }
        }
    }
    dComIfG_resDelete(&mPhase, M_arcname);
    return true;
}

/* 00000E84-00000F20       .text init_mtx__11daObjTrap_cFv */
void daObjTrap_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 00000F20-00000F70       .text set_co_pos__11daObjTrap_cFv */
void daObjTrap_c::set_co_pos() {
    cXyz pos(current.pos);
    pos.y -= 40.0f;
    mCcCyl.SetC(pos);
}

/* 00000F70-00000FF4       .text get_ground__11daObjTrap_cFv */
void daObjTrap_c::get_ground() {
    cXyz pos(current.pos.x, current.pos.y + 50.0f, current.pos.z);
    mGndChk.SetPos(&pos);
    mGndChk.SetActorPid(fopAcM_GetID(this));
    mGroundY = dComIfG_Bgsp()->GroundCross(&mGndChk);
}

/* 00000FF4-0000112C       .text circle_search__11daObjTrap_cFv */
void daObjTrap_c::circle_search() {
    /* Nonmatching */
}

/* 0000112C-0000122C       .text set_move_info__11daObjTrap_cFv */
void daObjTrap_c::set_move_info() {
    dPnt* point = &mpPath->m_points[mPathPoint];
    mPathPos.set(point->m_position.x, current.pos.y, point->m_position.z);
    point = &mpPath->m_points[(mPathPoint + 1) & 1];
    mNextPathPos.set(point->m_position.x, current.pos.y, point->m_position.z);
    mPathDirection = mNextPathPos - mPathPos;
    mPathDirectionSign = mPathDirection.normalizeRS();
    mPathOffset = cXyz::Zero;
    mPathStep = mPathDirection * 100.0f;
}

/* 0000122C-000013E4       .text check_arrival__11daObjTrap_cFv */
void daObjTrap_c::check_arrival() {
    /* Nonmatching */
}

/* 000013E4-000018E4       .text check_wall__11daObjTrap_cFv */
void daObjTrap_c::check_wall() {
    /* Nonmatching */
}

/* 00001C88-00001D7C       .text check_block_target_pos__11daObjTrap_cFP4cXyz */
void daObjTrap_c::check_block_target_pos(cXyz*) {
    /* Nonmatching */
}

/* 00001D7C-000023D4       .text check_block__11daObjTrap_cF4cXyz */
void daObjTrap_c::check_block(cXyz) {
    /* Nonmatching */
}

/* 000023D4-0000250C       .text set_vib_mode__11daObjTrap_cFv */
void daObjTrap_c::set_vib_mode() {
    /* Nonmatching */
}

/* 0000250C-0000255C       .text vibrate__11daObjTrap_cFv */
void daObjTrap_c::vibrate() {
    f32 amplitude;
    amplitude = 288.0f;
    shape_angle.x = amplitude * JMASSin(mVibrationTimer * 0x5555);
}

/* 0000255C-00002678       .text bound__11daObjTrap_cFv */
void daObjTrap_c::bound() {
    /* Nonmatching */
}

/* 00002678-0000270C       .text set_shine__11daObjTrap_cFv */
void daObjTrap_c::set_shine() {
    /* Nonmatching */
}

/* 0000270C-00002758       .text shine_move__11daObjTrap_cFv */
void daObjTrap_c::shine_move() {
    if (mShineStatus == 1 && mBtkAnm.play()) {
        mShineStatus = 0;
    }
}

/* 00002758-00002CB0       .text _execute__11daObjTrap_cFv */
bool daObjTrap_c::_execute() {
    /* Nonmatching */
}

/* 00002CB0-00002D54       .text _draw__11daObjTrap_cFv */
bool daObjTrap_c::_draw() {
    /* Nonmatching */
}

namespace {
/* 00002D54-00002D74       .text Mthd_Create__26@unnamed@d_a_obj_trap_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjTrap_c*)i_this)->_create();
}

/* 00002D74-00002D98       .text Mthd_Delete__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjTrap_c*)i_this)->_delete();
}

/* 00002D98-00002DBC       .text Mthd_Execute__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjTrap_c*)i_this)->_execute();
}

/* 00002DBC-00002DE0       .text Mthd_Draw__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjTrap_c*)i_this)->_draw();
}

/* 00002DE0-00002DE8       .text Mthd_IsDelete__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Trap_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Trap = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Trap_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTrap_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Trap_e,
    /* Actor SubMtd */ &Trap_Mthd_Table,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
