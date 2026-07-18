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
#include "d/d_a_obj.h"
#include "d/actor/d_a_obj_movebox.h"
#include "d/d_path.h"
#include "f_pc/f_pc_draw_priority.h"
#include "f_pc/f_pc_name.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Trap.h"

/* 000000EC-0000010C       .text solidHeapCB__11daObjTrap_cFP10fopAc_ac_c */
int daObjTrap_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<daObjTrap_c*>(i_this)->create_heap();
}

f32 const daObjTrap_c::M_speed_table[] = {50.0f, 80.0f, 100.0f};
s16 const daObjTrap_c::M_wait_f_table[] = {30, 10, 0};
const char daObjTrap_c::M_arcname[] = "Trap";

static dCcD_SrcCyl l_daObjTrap_cyl_data = {
    {
        cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        AT_TYPE_SPIKE,
        1,
        5,
        0,
        0,
        0,
        dCcG_SE_NONE,
        dCcG_AtHitMark_None_e,
        dCcG_At_Spl_UNK1,
        0,
        0,
        dCcG_SE_NONE,
        dCcG_TgHitMark_None_e,
        dCcG_Tg_Spl_UNK0,
        0,
        dCcG_TgSPrm_NoHitMark_e,
        0,
    },
    {{{0.0f, -40.0f, 0.0f}, 155.0f, 100.0f}},
};

/* 0000010C-000002A4       .text create_heap__11daObjTrap_cFv */
int daObjTrap_c::create_heap() {
    /* Nonmatching */
    J3DModelData* mdl_data;
    int result = false;

    mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_ID_TRAP_BDL_HTORA1_e);
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
    fopAcM_SetupActor(this, daObjTrap_c);

    cPhs_State phase = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase == cPhs_COMPLEATE_e) {
        phase = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            mPathId = fopAcM_GetParam(this);
            if (mPathId != 0xFF) {
                mpPath = dPath_GetRoomPath(mPathId, fopAcM_GetRoomNo(this));
                if (mpPath != NULL && mpPath->m_points != NULL) {
                    mSpeedType = (fopAcM_GetParam(this) >> 8) & 0xF;
                    if (mSpeedType == 0xF) {
                        mSpeedType = 0;
                    }
                    mSpeed = M_speed_table[mSpeedType];
                    mWaitFrame = M_wait_f_table[mSpeedType];
                    dPnt* first_point = mpPath->m_points;
                    f32 z = first_point->m_position.z;
                    current.pos.x = first_point->m_position.x;
                    current.pos.z = z;
                    set_move_info();
                    cXyz path_diff = mNextPathPos - mPathPos;
                    mPathLength = cXyz(path_diff.x, 0.0f, path_diff.z).abs();
                    mPathTarget = current.pos;
                    init_mtx();
                    mCcStts.Init(0, 0xFF, this);
                    mCcCyl.SetStts(&mCcStts);
                    mCcCyl.Set(l_daObjTrap_cyl_data);
                    set_co_pos();
                    dComIfG_Bgsp()->Regist(mpcBgW, this);
                    get_ground();
                    phase = cPhs_COMPLEATE_e;
                } else {
                    mPathId = 0xFF;
                    phase = cPhs_ERROR_e;
                }
            }
        }
    }

    return phase;
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
int daObjTrap_c::circle_search() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz offset = player->current.pos - current.pos;
    f32 distance = offset.absXZ();
    int result = false;
    if (distance <= 400.0f && mPathDirectionSign == 1) {
        if (mPathDirection.x * offset.x + mPathDirection.z * offset.z >= 0.0f) {
            result = true;
        }
    }

    return result;
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
int daObjTrap_c::check_arrival() {
    cXyz target_offset = mPathTarget - mPathPos;
    cXyz next_offset = mNextPathPos - mPathPos;
    return target_offset.absXZ() >= next_offset.absXZ();
}

/* 000013E4-000018E4       .text check_wall__11daObjTrap_cFv */
cXyz daObjTrap_c::check_wall() {
    static const s16 angle_y[] = {0, 0x4000, -0x4000};
    static const f32 trans_a[] = {0.0f, 145.0f, 145.0f};
    static dBgS_ObjLinChk lin_chk;

    cXyz forward = mPathDirection * 150.0f;
    cXyz upward = cXyz::BaseY * 75.0f;
    cXyz wall_offset = cXyz::Zero;

    for (int i = 0; i < 3; i++) {
        mDoMtx_stack_c::YrotS(angle_y[i]);
        cXyz offset;
        mDoMtx_stack_c::multVec(&mPathDirection, &offset);
        offset *= trans_a[i];
        offset += upward;

        cXyz start = current.pos + offset;
        cXyz end = start + mPathOffset;
        end += forward;
        lin_chk.Set(&start, &end, this);
        lin_chk.SetActorPid(fopAcM_GetID(this));

        if (dComIfG_Bgsp()->LineCross(&lin_chk)) {
            cXyz hit = lin_chk.GetCross();
            hit -= start;
            if (wall_offset == cXyz::Zero || wall_offset.absXZ() > hit.absXZ()) {
                wall_offset = hit - current.pos - forward;
            }
        }
    }

    return wall_offset;
}

/* 00001C88-00001D7C       .text check_block_target_pos__11daObjTrap_cFP4cXyz */
bool daObjTrap_c::check_block_target_pos(cXyz* target_pos) {
    cXyz offset = *target_pos - current.pos;
    f32 dot = mPathDirection.x * offset.x + mPathDirection.z * offset.z;
    bool result = false;

    if (dot >= 0.0f && dot < 150.0f + mPathLength) {
        mDoMtx_stack_c::YrotS(0x4000);
        cXyz direction;
        mDoMtx_stack_c::multVec(&mPathDirection, &direction);
        if (std::fabsf(direction.x * offset.x + direction.z * offset.z) < 225.0f) {
            result = true;
        }
    }

    return result;
}

/* 00001D7C-000023D4       .text check_block__11daObjTrap_cF4cXyz */
cXyz daObjTrap_c::check_block(cXyz i_block_offset) {
    static s16 angle_y[] = {0x4000, -0x4000};
    static dBgS_ObjLinChk lin_chk;

    cXyz forward = mPathDirection * 150.0f;
    cXyz block_offset = i_block_offset;
    cXyz upward = cXyz::BaseY * 75.0f;

    for (int i = 0; i < 2; i++) {
        mDoMtx_stack_c::YrotS(angle_y[i]);
        cXyz offset;
        mDoMtx_stack_c::multVec(&mPathDirection, &offset);
        offset *= 225.0f;
        offset += upward;

        cXyz start = current.pos + offset;
        cXyz end = start + mPathOffset;
        end += forward;
        lin_chk.Set(&start, &end, this);
        lin_chk.SetActorPid(fopAcM_GetID(this));

        if (dComIfG_Bgsp()->LineCross(&lin_chk)) {
            cXyz target_pos;
            bool check_target;
            fopAc_ac_c* actor = dComIfG_Bgsp()->GetActorPointer(lin_chk);
            if (actor != NULL && fopAc_IsActor(actor) &&
                fopAcM_GetName(actor) == fpcNm_Obj_Movebox_e) {
                daObjMovebox::Act_c* movebox = static_cast<daObjMovebox::Act_c*>(actor);
                if (movebox->mMode == daObjMovebox::Act_c::MODE_WALK) {
                    mDoMtx_stack_c::push();
                    mDoMtx_stack_c::YrotS(movebox->home.angle.y);
                    mDoMtx_stack_c::transM((f32)movebox->m628, 0.0f,
                                           (f32)movebox->m62C);
                    MtxP mtx = mDoMtx_stack_c::get();
                    cXyz box_offset(mtx[0][3], mtx[1][3], mtx[2][3]);
                    mDoMtx_stack_c::YrotS(movebox->home.angle.y +
                                           daObjMovebox::Act_c::M_dir_base[movebox->m634]);
                    cXyz box_dir;
                    mDoMtx_stack_c::multVecSR(&cXyz::BaseZ, &box_dir);
                    mDoMtx_stack_c::pop();

                    target_pos = (box_offset + box_dir) * 75.0f + movebox->current.pos;
                    check_target = true;
                } else {
                    check_target = false;
                }
            } else {
                check_target = false;
            }
            if (check_target && check_block_target_pos(&target_pos)) {
                cXyz hit = lin_chk.GetCross();
                hit -= start;
                if (block_offset == cXyz::Zero ||
                    block_offset.absXZ() > hit.absXZ()) {
                    block_offset = hit - current.pos - forward;
                }
            }
        }
    }

    return block_offset;
}

/* 000023D4-0000250C       .text set_vib_mode__11daObjTrap_cFv */
void daObjTrap_c::set_vib_mode() {
    mVibrationAngle = shape_angle.x;
    mVibrationTimer = 6;
    mVibrationFrame = 35.0f;
    mBoundTimer = 16;
    mVibrationPosition = cXyz::Zero;
    mMode = 2;

    cXyz pos = mPathDirection * 150.0f;
    pos += current.pos;
    cXyz direction = mPathDirection * -0.5f;
    pos.y += 50.0f;
    daObj::HitEff_hibana(&pos, &direction);

    if (mVibrationTimer != 0) {
        vibrate();
        mVibrationTimer--;
    }
    if (mBoundTimer != 0) {
        bound();
        mBoundTimer--;
    }
}

/* 0000250C-0000255C       .text vibrate__11daObjTrap_cFv */
void daObjTrap_c::vibrate() {
    f32 amplitude;
    amplitude = 288.0f;
    shape_angle.x = amplitude * JMASSin(mVibrationTimer * 0x5555);
}

/* 0000255C-00002678       .text bound__11daObjTrap_cFv */
void daObjTrap_c::bound() {
    cXyz offset = mPathDirection * -0.5f;
    mPathTarget -= mVibrationPosition;
    offset *= (f32)fabs((s16)(mVibrationFrame * cM_ssin(mBoundTimer << 14)));
    mPathTarget += offset;
    mVibrationPosition = offset;
    cLib_addCalc(&mVibrationFrame, 0.0f, 0.17f, 35.0f, 1.0f);
}

/* 00002678-0000270C       .text set_shine__11daObjTrap_cFv */
void daObjTrap_c::set_shine() {
    mShineStatus = 1;
    if (cXyz::BaseX.inprod(mPathDirection) >= 0.0f) {
        mBtkAnm.setFrame(35.0f);
        mBtkAnm.setPlaySpeed(1.0f);
    } else {
        mBtkAnm.setFrame(46.0f);
        mBtkAnm.setPlaySpeed(-0.5f);
    }
}

/* 0000270C-00002758       .text shine_move__11daObjTrap_cFv */
void daObjTrap_c::shine_move() {
    if (mShineStatus == 1 && mBtkAnm.play()) {
        mShineStatus = 0;
    }
}

/* 00002758-00002CB0       .text _execute__11daObjTrap_cFv */
bool daObjTrap_c::_execute() {
    mPathTarget = current.pos;
    cXyz block_offset;

    switch (mMode) {
    case 0: {
        int arrived = cLib_chasePosXZ(&mPathTarget, mNextPathPos, mSpeed);
        mPathOffset = mPathTarget - current.pos;
        block_offset = check_wall();
        block_offset = check_block(block_offset);

        if (block_offset != cXyz::Zero) {
            mPathTarget = block_offset;
            set_vib_mode();
            set_shine();
            mDoAud_seStart(0x6A02, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        } else if (arrived == true) {
            set_vib_mode();
            set_shine();
            mDoAud_seStart(0x6A02, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        } else if (circle_search() == true) {
            mMode = 1;
        } else {
            mDoAud_seStart(0x704F, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        }
        break;
    }
    case 1: {
        cLib_addCalcPosXZ(&mPathOffset, mPathStep, 0.1f, 40.0f, 0.0f);
        mPathTarget += mPathOffset;
        block_offset = check_wall();
        block_offset = check_block(block_offset);

        if (block_offset != cXyz::Zero) {
            mPathTarget = block_offset;
            set_vib_mode();
            set_shine();
            mDoAud_seStart(0x6A02, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        } else if (check_arrival() == true) {
            mPathTarget = mNextPathPos;
            set_vib_mode();
            set_shine();
            mDoAud_seStart(0x6A02, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        } else {
            mDoAud_seStart(0x704F, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        }
        break;
    }
    case 2:
        if (mVibrationTimer != 0) {
            vibrate();
            mVibrationTimer--;
        }
        if (mBoundTimer != 0) {
            bound();
            mBoundTimer--;
        }
        if (mVibrationTimer == 0) {
            shape_angle.x = mVibrationAngle;
            if (mBoundTimer == 0) {
                mWaitTimer = mWaitFrame;
                mMode = 3;
            }
        }
        break;
    case 3:
        if (mWaitTimer > 0) {
            mWaitTimer--;
        }
        if (mWaitTimer == 0) {
            mPathPoint = (mPathPoint + 1) & 1;
            set_move_info();
            mMode = 0;
        }
        break;
    }

    current.pos = mPathTarget;
    shine_move();
    get_ground();
    init_mtx();
    set_co_pos();
    dComIfG_Ccsp()->Set(&mCcCyl);
    if (heap != NULL && mpcBgW != NULL && mpcBgW->ChkUsed()) {
        mpcBgW->Move();
    }
    return true;
}

/* 00002CB0-00002D54       .text _draw__11daObjTrap_cFv */
bool daObjTrap_c::_draw() {
    g_env_light.settingTevStruct(1, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    J3DModelData* model_data = mpModel->getModelData();
    mBtkAnm.entry(model_data, mBtkAnm.getFrame());
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setSimpleShadow2(&current.pos, mGroundY, 150.0f, mGndChk, 0, 1.0f,
                              dDlst_shadowControl_c::getSimpleTex());
    return true;
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
