/**
 * d_a_obj_vtil.cpp
 * Object - Tingle statues
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_vtil.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_agbsw0.h"
#include "d/d_a_obj.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_camera.h"

#include "d/res/res_vtil.h"

const int daObjVtil_c::l_daObjVtil_bdl_idx_table[5] = {
    VTIL_BDL_VTIL1,
    VTIL_BDL_VTIL2,
    VTIL_BDL_VTIL3,
    VTIL_BDL_VTIL5,
    VTIL_BDL_VTIL4,
};

const int daObjVtil_c::l_daObjVtil_scene_no_table[5] = {
    VTIL_BDL_VTIL1,
    VTIL_BDL_VTIL2,
    VTIL_BDL_VTIL3,
    VTIL_BDL_VTIL5,
    VTIL_BDL_VTIL4,
};

const dCcD_SrcCyl daObjVtil_c::M_co_cyl_data = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK8,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 52.0f,
        /* Height */ 160.0f,
    }},
};

const char daObjVtil_c::M_arcname[] = "Vtil";

/* 00000078-00000098       .text solidHeapCB__11daObjVtil_cFP10fopAc_ac_c */
BOOL daObjVtil_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjVtil_c*)(i_this))->create_heap();
}

/* 00000098-0000016C       .text create_heap__11daObjVtil_cFv */
BOOL daObjVtil_c::create_heap() {
    /* Nonmatching */
    BOOL ret = FALSE;

    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, l_daObjVtil_bdl_idx_table[m60C]));
    JUT_ASSERT(325, mdl_data != NULL);

    if (mdl_data != NULL) {
        J3DModel* model = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        mpModel = model;
        if (mpModel != NULL) {
            ret = TRUE;
        }
    }
    return ret;
}

/* 0000016C-000003C0       .text _create__11daObjVtil_cFv */
cPhs_State daObjVtil_c::_create() {
    cPhs_State state = cPhs_ERROR_e;
    fopAcM_SetupActor(this, daObjVtil_c);
    m60C = daObj::PrmAbstract(this, (Prm_e)PRM_TYPE_W, (Prm_e)PRM_TYPE_S);
    if (m60C == 0xF || m60C == -1) {
        m60C = 0;
    }

    if (check_ev_bit()) {
        state = dComIfG_resLoad(&mPhs, M_arcname);
        if (state == cPhs_COMPLEATE_e) {
            state = cPhs_ERROR_e;
            if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xCC0)) {
                fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
                init_mtx();
                fopAcM_setCullSizeBox(this, -50.0f, 0.0f, -50.0f, 50.0f, 160.0f, 50.0f);
                init_co();
                init_bgc();
                fopAcM_SetGravity(this, -6.0f);
                renew_attention_pos();
                eyePos = current.pos;
                eyePos.y += 110.0f;
                cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
                attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 0x17;
                m616 = 1;
                to_wait_mode();
                dKy_plight_set(&mPLight);
                model = mpModel;
                state = cPhs_COMPLEATE_e;
            }
        }
    }

    return state;
}

/* 000006CC-00000718       .text _delete__11daObjVtil_cFv */
BOOL daObjVtil_c::_delete() {
    dKy_plight_cut(&mPLight);
    this->model = NULL;
    dComIfG_resDelete(&mPhs, M_arcname);
    return TRUE;
}

/* 00000718-00000750       .text check_ev_bit__11daObjVtil_cCFv */
BOOL daObjVtil_c::check_ev_bit() const {
    return dComIfGs_isStageTbox(l_daObjVtil_scene_no_table[m60C], 0xF);
}

/* 00000750-00000770       .text tell_agb_attack__11daObjVtil_cFv */
void daObjVtil_c::tell_agb_attack() {
    daAgbsw0_c::incTclBeat();
}

/* 00000770-00000790       .text tell_agb_sink__11daObjVtil_cFv */
void daObjVtil_c::tell_agb_sink() {
    daAgbsw0_c::incTclDispose();
}

/* 00000790-0000082C       .text init_mtx__11daObjVtil_cFv */
void daObjVtil_c::init_mtx() {
    /* Nonmatching */
    J3DModel* pJVar1 = mpModel;
    pJVar1->setBaseScale(scale);
    PSMTXTrans(mDoMtx_stack_c::get(), current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_ZXYrotM(mDoMtx_stack_c::get(), shape_angle.x, shape_angle.y, shape_angle.z);
    PSMTXCopy(mDoMtx_stack_c::get(), mpModel->getBaseTRMtx());
    mpModel->calc();
}

/* 0000082C-000008CC       .text init_co__11daObjVtil_cFv */
void daObjVtil_c::init_co() {
    mStts.Init(200, 0xff, this);
    mCyl.Set(M_co_cyl_data);
    mCyl.SetStts(&mStts);
    mCyl.SetC(current.pos);
    mCyl.SetAtVec(*(cXyz*)&cXyz::Zero);
    mCyl.SetTgVec(*(cXyz*)&cXyz::Zero);
    mCyl.OnTgShield();
}

/* 000008CC-000009A4       .text init_bgc__11daObjVtil_cFv */
void daObjVtil_c::init_bgc() {
    /* Nonmatching */
    mAcchCir.SetWall(30.0f, 56.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    mAcch.ClrWaterNone();
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(160.0f);
    mAcch.OnSeaCheckOn();
    mAcch.OnSeaWaterHeight();
    fopAcM_posMoveF(this, NULL);
    mAcch.CrrPos(*dComIfG_Bgsp());
    mAcch.ClrGroundLanding();
}

/* 000009A4-000009CC       .text renew_attention_pos__11daObjVtil_cFv */
void daObjVtil_c::renew_attention_pos() {
    /* Nonmatching */
    attention_info.position.x = current.pos.x;
    attention_info.position.y = current.pos.y + 160.0f;
    attention_info.position.z = current.pos.z;
}

/* 000009CC-000009F8       .text make_smoke__11daObjVtil_cFv */
void daObjVtil_c::make_smoke() {
    /* Nonmatching */
    daObj::make_land_effect(this, &mAcch.m_gnd, 1.0f);
}

/* 000009F8-00000A88       .text se_smoke__11daObjVtil_cFv */
void daObjVtil_c::se_smoke() {
    /* Nonmatching */
    fopAcM_seStart(this, JA_SE_OBJ_PUT_STONE, dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd));
}

/* 00000A88-00000AD8       .text make_splash__11daObjVtil_cFv */
void daObjVtil_c::make_splash() {
    /* Nonmatching */
    cXyz pos(current.pos.x, mAcch.m_wtr.GetHeight(), current.pos.z);
    fopKyM_createWpillar(&pos, 1.0f, 0.75f, 0);
}

/* 00000AD8-00000BCC       .text se_splash__11daObjVtil_cFv */
void daObjVtil_c::se_splash() {
    /* Nonmatching */
    cBgS_PolyInfo* polyInfoArr[2] = {
        &mAcch.m_wtr,
        &mAcch.m_gnd,
    };
    u32 mtrlSndId = 0x13;
    for (int i = 0; i < ARRAY_SIZE(polyInfoArr); i++) {
        int bg_index = polyInfoArr[i]->GetBgIndex();
        if (bg_index >= 0 && bg_index < 0x100) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(*polyInfoArr[i]);
            break;
        }
    }

    fopAcM_seStart(this, JA_SE_OBJ_FALL_WATER_S, mtrlSndId);
    set_sound(0x7d, 5);
}

/* 00000BCC-00000C20       .text set_sound__11daObjVtil_cCFii */
void daObjVtil_c::set_sound(int param_1, int param_2) const {
    dKy_Sound_set(current.pos, param_1, fopAcM_GetID((void*)this), param_2);
}

/* 00000C20-00000CA0       .text to_wait_mode__11daObjVtil_cFv */
void daObjVtil_c::to_wait_mode() {
    /* Nonmatching */
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);
    speedF = 0.0f;
    gravity = -6.0f;
    mStts.Init(200, 0xff, this);
    mMode = MODE_WAIT;
}

/* 00000CA0-00000D70       .text mode_wait__11daObjVtil_cFv */
void daObjVtil_c::mode_wait() {
    /* Nonmatching */
    if (fopAcM_checkCarryNow(this)){
        to_carry_mode();
    } else {
        if (mAcch.ChkGroundLanding()){
            //'\0'
            if (m616 == 0) {
                make_smoke();
                se_smoke();
                make_vib();}
            else {
                m616 = 0;
            }
            mAcch.ClrGroundLanding();
        }
        
        if (mAcch.ChkGroundHit()){
            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        } else {
            cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        }
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    mSpeedY = speed.y;
    mAcch.CrrPos(*dComIfG_Bgsp());
}

/* 00000D70-00000DAC       .text to_carry_mode__11daObjVtil_cFv */
void daObjVtil_c::to_carry_mode() {
    /* Nonmatching */
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OffCoSPrmBit(cCcD_CoSPrm_Set_e);
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    mMode = MODE_CARRY;
}

/* 00000DAC-00000E7C       .text mode_carry__11daObjVtil_cFv */
void daObjVtil_c::mode_carry() {
    /* Nonmatching */
    cXyz temp = current.pos;
    cXyz temp2 = speed;

    if (!fopAcM_checkCarryNow(this)) {
        if (speedF > 0.0f){
            to_throw_mode();
        } else {
            to_wait_mode();
        }
    }
    mSpeedY = speed.y;
    mAcch.CrrPos(*dComIfG_Bgsp());
    current.pos = temp;
    speed = temp2;
}

/* 00000E7C-00000F14       .text to_throw_mode__11daObjVtil_cFv */
void daObjVtil_c::to_throw_mode() {
    /* Nonmatching */
    mCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);
    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OnLineCheckNone();
    fopAcM_OffStatus(this, fopAcStts_CARRY_e);
    fopAcM_GetSpeed(this).y = 27.0f;
    fopAcM_SetSpeedF(this, 36.0f);
    fopAcM_SetGravity(this, -6.0f);
    mMode = MODE_THROW;
}

/* 00000F14-00000FDC       .text calc_throw__11daObjVtil_cCFPfPfPf */
void daObjVtil_c::calc_throw(float* gravity, float* param_2, float* param_3) const {
    /* Nonmatching */
    float fVar1;
    if (const_cast<dBgS_Acch&>(mAcch).ChkSeaIn()){
        float fVar2 = current.pos.y - const_cast<dBgS_Acch&>(mAcch).GetSeaHeight();
        if (!(fVar2 >= 0.0f)) {
            fVar1 = 0.0f;
        } else {
            if (fVar2 <= -160.0f) {
                fVar1 = -fVar2 * (1.0f / 320.0f);
            } else {
                fVar1 = 0.5f;
            }
        }

        *param_2 = fVar1 * 0.2 + (1.0f - fVar1) * 0.002f;
        *param_3 = fVar1 * 0.02f + (1.0f - fVar1) * 0.0002f;
        *gravity = fVar1 * 4.0f + -6.0f;
    } else {
        *param_2 = 0.002f;
        *param_3 = 0.0002f;
        *gravity = -6.0f;
    }
}

/* 00000FDC-00001054       .text mode_throw__11daObjVtil_cFv */
void daObjVtil_c::mode_throw() {
    /* Nonmatching */
    float gravity, f14, f10;
    calc_throw(&gravity, &f14, &f10);
    fopAcM_SetGravity(this, gravity);
    daObj::posMoveF_stream(this, mStts.GetCCMoveP(), &cXyz::Zero, f14, f10);
    mSpeedY = speed.y;
    mAcch.CrrPos(*dComIfG_Bgsp());
}

/* 00001054-000011C8       .text to_sink_mode__11daObjVtil_cFv */
void daObjVtil_c::to_sink_mode() {
    /* Nonmatching */
    mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    mCyl.OnTgSPrmBit(cCcD_TgSPrm_Set_e);
    mCyl.OnCoSPrmBit(cCcD_CoSPrm_Set_e);
    mAcch.SetRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OnLineCheckNone();
    fopAcM_SetGravity(this, -2.0f);
    
    f32 sqrt = std::sqrtf(speed.y * speed.y + speedF * speedF);
    if (sqrt > 0.0f) {
        sqrt = 1.0f / sqrt;
        speed *= sqrt;
        speedF *= sqrt;
    }

    make_splash();
    se_splash();
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    mMode = MODE_SINK;
}

/* 000011C8-0000122C       .text mode_sink__11daObjVtil_cFv */
void daObjVtil_c::mode_sink() {
    /* Nonmatching */
    daObj::posMoveF_stream(this, mStts.GetCCMoveP(), &cXyz::Zero, 0.2,0.02);
    mSpeedY = speed.y;
    mAcch.CrrPos(*dComIfG_Bgsp());
}

/* 0000122C-000012F8       .text hit_co__11daObjVtil_cFv */
void daObjVtil_c::hit_co() {
    /* Nonmatching */
    mStts.Move();
    int hit = mCyl.ChkAtHit();
    if (hit) {
        mCyl.ClrAtHit();
        speedF *= 0.8f;
    } else {
        hit = mCyl.ChkTgHit();
        if (hit) {
            tell_agb_attack();
            daObj::HitSeStart(&current.pos, current.roomNo, &mCyl, 0xD);
            set_sound(0x96, 5);
            daObj::HitEff_hibana(this, &mCyl);
            mCyl.ClrTgHit();
        }
    }
}

/* 000012F8-00001330       .text check_sink__11daObjVtil_cFv */
BOOL daObjVtil_c::check_sink() {
    /* Nonmatching */
    BOOL ret = FALSE;

    if (mAcch.ChkSeaIn() && fopAcM_GetPosition_p(this)->y + 70.0f < mAcch.GetSeaHeight()) {
        ret = TRUE;
    }

    return ret;
}

/* 00001330-00001374       .text check_sink_end__11daObjVtil_cFv */
BOOL daObjVtil_c::check_sink_end() {
    /* Nonmatching */
    BOOL ret = FALSE;

    if (mAcch.ChkSeaIn() && fopAcM_GetPosition_p(this)->y + 160.0f + 50.0f < mAcch.GetSeaHeight()) {
        ret = TRUE;
    }

    return ret;
}

/* 00001374-000014E0       .text hit_bg__11daObjVtil_cFv */
void daObjVtil_c::hit_bg() {
    /* Nonmatching */

    //uVar3 = (this->mAcch).mFlags >> 5 & 1;
    BOOL groundHit = mAcch.ChkGroundHit();
    BOOL isSink = check_sink();
    Mode mode = mMode;
    
    if (mode == MODE_WAIT) {
        if (((isSink & 0xFF) != 0)) {
            to_sink_mode();
        }
    } else if (mode == MODE_THROW){
        if (!groundHit && !mAcch.ChkWallHit() && mAcch.ChkRoofHit()) {
            if (((isSink & 0xFF) == 0)) {
                return;
            }

            return;
        }

        if (fopAcM_GetGravity(this) - 1.0f < mSpeedY) {
            if (groundHit) {
                make_smoke();
                se_smoke();
                make_vib();
            }

            fopAcM_SetSpeedF(this, 0.0f);
            to_wait_mode();
            camera_class* camera = dComIfGp_getCamera(0);
            camera->mCamera.ForceLockOff(base.base.mBsPcId);
        }
        // fopAcM_SetSpeedF(this, fopAcM_GetSpeedF(this) * 0.6f);
    } else if (mode == MODE_SINK) {
        BOOL cVar4 = check_sink_end();
        if ((cVar4 & 0xFF) == 0) {
            if ((isSink & 0xFF) == 0) {
                return;
            }
                to_wait_mode();
                camera_class* camera = dComIfGp_getCamera(0);
                camera->mCamera.ForceLockOff(base.base.mBsPcId);
        } else {
            tell_agb_sink();
            m615 = 1;
        }
    }
}


/* 000014E0-0000153C       .text make_vib__11daObjVtil_cFv */
void daObjVtil_c::make_vib() {
    /* Nonmatching */
    BOOL temp = check_circle();
    dComIfGp_getVibration().StartShock(temp, 1, cXyz(0.0f, 1.0f, 0.0f));
}

/* 0000153C-00001634       .text check_circle__11daObjVtil_cFv */
BOOL daObjVtil_c::check_circle() {
    cXyz playerPos = dComIfGp_getPlayer(0)->current.pos - current.pos;
    cXyz circleCenter(playerPos.x, 0.0f, playerPos.z);
    return std::sqrtf(PSVECSquareMag(&circleCenter)) <= 190.0f;
}

/* 00001634-000017CC       .text _execute__11daObjVtil_cFv */
BOOL daObjVtil_c::_execute() {
    static void (daObjVtil_c::*mode_exe[])() = {
        &daObjVtil_c::mode_wait,
        &daObjVtil_c::mode_carry,
        &daObjVtil_c::mode_throw,
        &daObjVtil_c::mode_sink,
    };

    hit_co();
    hit_bg();

    if (m615 == 0) {
        (this->*mode_exe[mMode])();
        renew_attention_pos();
        init_mtx();
        mCyl.MoveCAtTg(current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
        mPLight.mPos = current.pos;
        mPLight.mPos.y += 70.0f;
        mPLight.mColor.r = 0x94;
        mPLight.mColor.g = 0x7F;
        mPLight.mColor.b = 0x34;
        mPLight.mPower = 230.0f;
        mPLight.mFluctuation = 250.0f;
    }

    if (m615 == 1) {
        fopAcM_delete(this);
        m615 = 2;
    }

    return TRUE;
}

/* 000017CC-00001864       .text _draw__11daObjVtil_cFv */
bool daObjVtil_c::_draw() {
    /* Nonmatching */
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    if (!fopAcM_checkCarryNow(this)){
        dComIfGd_setSimpleShadow2(&current.pos, mAcch.GetGroundH(), 57.0f, mAcch.m_gnd, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }
    return TRUE;
}

namespace {
/* 00001864-00001884       .text Mthd_Create__26@unnamed@d_a_obj_vtil_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVtil_c*)i_this)->_create();
}

/* 00001884-000018A8       .text Mthd_Delete__26@unnamed@d_a_obj_vtil_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVtil_c*)i_this)->_delete();
}

/* 000018A8-000018CC       .text Mthd_Execute__26@unnamed@d_a_obj_vtil_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVtil_c*)i_this)->_execute();
}

/* 000018CC-000018F0       .text Mthd_Draw__26@unnamed@d_a_obj_vtil_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVtil_c*)i_this)->_draw();
}

/* 000018F0-000018F8       .text Mthd_IsDelete__26@unnamed@d_a_obj_vtil_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Vtil_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Vtil = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Vtil,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVtil_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Vtil,
    /* Actor SubMtd */ &Vtil_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
