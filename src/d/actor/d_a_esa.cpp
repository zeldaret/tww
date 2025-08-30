/**
 * d_a_esa.cpp
 * Item - All-Purpose Bait
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_sea.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_s_play.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_s_func.h"
#include "d/res/res_link.h"
#include "f_op/f_op_actor_mng.h"

/* 800E7E60-800E7EA8       .text daEsa_Draw__FP9esa_class */
static BOOL daEsa_Draw(esa_class* i_this) {
    g_env_light.setLightTevColorType(i_this->mpModel, &i_this->tevStr);
    mDoExt_modelUpdateDL(i_this->mpModel);

    return true;
}

/* 800E7EA8-800E849C       .text bg_check__FP9esa_class */
void bg_check(esa_class* i_this) {
    dBgS_GndChk gndChk;
    Vec temp;
    temp.x = i_this->current.pos.x;
    temp.y = i_this->current.pos.y;
    temp.z = i_this->current.pos.z;
    temp.y += 100.0f;
    gndChk.SetPos(&temp);

    i_this->mGroundHeight = dComIfG_Bgsp()->GroundCross(&gndChk) + 5.0f;
    s8 state = 1;
    if(daSea_ChkArea(i_this->current.pos.x, i_this->current.pos.z)) {
        f32 wave = daSea_calcWave(i_this->current.pos.x, i_this->current.pos.z);
        if(i_this->mGroundHeight <= wave) {
            i_this->mGroundHeight = wave;
            state = 2;
        }
    }

    cXyz sp6C;
    cXyz sp60;
    
    cXyz sp54 = i_this->current.pos;
    sp54.y += 100.0f;
    f32 waterHeight = dBgS_GetWaterHeight(sp54);
    if(waterHeight != -G_CM3D_F_INF && i_this->mGroundHeight <= waterHeight) {
        i_this->mGroundHeight = waterHeight;
        state = 2;
    }

    if(i_this->speed.y <= 0.0f && i_this->current.pos.y <= i_this->mGroundHeight) {
        i_this->current.pos.y = i_this->mGroundHeight;
        i_this->mState = state;
    }
    else {
        i_this->mState = 0;
    }

    dBgS_LinChk linChk;
    cXyz sp48 = i_this->old.pos + (i_this->current.pos - i_this->old.pos) * 1.5f;
    sp48.y = i_this->old.pos.y;
    cXyz temp5 = i_this->old.pos - sp48;
    if(temp5.abs() > 1.0f) {
        linChk.Set(&i_this->old.pos, &sp48, i_this);
        if(dComIfG_Bgsp()->LineCross(&linChk)) {
            i_this->current.pos.x = i_this->old.pos.x;
            i_this->current.pos.z = i_this->old.pos.z;
            i_this->speedF *= 0.5f;
            i_this->current.angle.y -= 0x8000;
            sp6C.x = 0.0f;
            sp6C.y = 0.0f;
            sp6C.z = i_this->speedF;
            mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
            MtxPosition(&sp6C, &sp60);
            i_this->speed.x = sp60.x;
            i_this->speed.z = sp60.z;
        }
    }
    else {
        fopAcM_OffStatus(i_this, fopAcStts_UNK4000_e);
    }
}

/* 800E849C-800E88F8       .text esa_1_move__FP9esa_class */
void esa_1_move(esa_class* i_this) {
    cXyz sp24;
    switch(i_this->mActionState) {
        case 0:
            i_this->current.angle.y += (s16)cM_rndFX(4000.0f);
            i_this->current.angle.z = cM_rndFX(32768.0f);
            sp24.x = 0.0f;
            sp24.y = cM_rndF(8.0f) + 15.0f;
            sp24.z = cM_rndF(5.0f) + 10.0f;
            i_this->speedF = sp24.z;
            mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
            MtxPosition(&sp24, &i_this->speed);

            i_this->mActionState = 1;
        case 1:
            if(i_this->mState != 0) {
                if(i_this->mState == 2) {
                    i_this->mTimer[0] = cM_rndF(50.0f) + 200.0f;
                    i_this->mActionState = 3;
                    if(i_this->field_0x2A4.getEmitter() == NULL) {
                        static cXyz ripple_scale(0.2f, 0.2f, 0.2f);
                        dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &i_this->current.pos, 0, &ripple_scale, 0xFF, &i_this->field_0x2A4);
                        if(i_this->field_0x2A4.getEmitter()) {
                            i_this->field_0x2A4.setRate(0.4f);
                        }
                    }
                }
                else {
                    if(i_this->speed.y < 5.0f) {
                        i_this->speed.y *= -(cM_rndF(0.05f) + 0.15f);
                        i_this->current.angle.z = cM_rndFX(32768.0f);
                    }

                    i_this->current.angle.y += (s16)cM_rndFX(8000.0f);
                    i_this->speedF *= cM_rndF(0.3f) + 0.3f;
                    sp24.x = 0.0f;
                    sp24.y = 0.0f;
                    sp24.z = i_this->speedF;
                    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
                    cXyz sp18;
                    MtxPosition(&sp24, &sp18);
                    i_this->speed.x = sp18.x;
                    i_this->speed.z = sp18.z;
                    if(i_this->speedF < 0.1f) {
                        i_this->mActionState = 2;
                        i_this->mTimer[0] = cM_rndF(50.0f) + 200.0f;
                        
                        break;
                    }
                }
            }

            i_this->current.pos.x += i_this->speed.x;
            i_this->current.pos.y += i_this->speed.y;
            i_this->current.pos.z += i_this->speed.z;
            i_this->speed.y -= 3.0f;
            bg_check(i_this);

            break;
        case 2:
            if(i_this->mTimer[0] == 0) {
                fopAcM_delete(i_this);
            }
            
            break;
        case 3:
            if(dComIfGp_evmng_startCheck("SO_ESA_XY")) {
                i_this->mTimer[0] = 10000;
            }

            i_this->field_0x2A4.end();
            i_this->current.pos.y = daSea_calcWave(i_this->current.pos.x, i_this->current.pos.z);

            if(i_this->mTimer[0] == 0) {
                i_this->mTimer[0] = 10;
                i_this->mActionState = 4;
            }

            if(i_this->field_0x298) {
                i_this->mTimer[0] = 10;
                i_this->mActionState = 4;

                if(i_this->field_0x2A4.getEmitter() == NULL) {
                    static cXyz ripple_scale(0.2f, 0.2f, 0.2f);
                    dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &i_this->current.pos, 0, &ripple_scale, 0xFF, &i_this->field_0x2A4);
                    if(i_this->field_0x2A4.getEmitter()) {
                        i_this->field_0x2A4.setRate(0.4f);
                    }
                }
            }

            break;
        case 4:
            if(i_this->mTimer[0] == 0) {
                fopAcM_delete(i_this);
            }
            
            break;
    }
}

/* 800E88F8-800E89B8       .text daEsa_Execute__FP9esa_class */
static BOOL daEsa_Execute(esa_class* i_this) {
    for(int i = 0; i < 2; i++) {
        if(i_this->mTimer[i] != 0) {
            i_this->mTimer[i]--;
        }
    }
    
    esa_1_move(i_this);

    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, false);
    mDoMtx_YrotM(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    mDoMtx_ZrotM(*calc_mtx, i_this->current.angle.z);
    i_this->mpModel->setBaseTRMtx(*calc_mtx);

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);

    return true;
}

/* 800E89B8-800E89C0       .text daEsa_IsDelete__FP9esa_class */
static BOOL daEsa_IsDelete(esa_class* i_this) {
    return true;
}

/* 800E89C0-800E89E8       .text daEsa_Delete__FP9esa_class */
static BOOL daEsa_Delete(esa_class* i_this) {
    i_this->field_0x2A4.end();

    return true;
}

/* 800E89E8-800E8AB0       .text daEsa_CreateHeap__FP10fopAc_ac_c */
static BOOL daEsa_CreateHeap(fopAc_ac_c* i_actor) {
    esa_class* i_this = static_cast<esa_class*>(i_actor);

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Link", LINK_BDL_ESA));
    JUT_ASSERT(0x1E8, modelData != NULL);
    i_this->mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);

    if(i_this->mpModel == NULL) {
        return false;
    }

    return true;
}

/* 800E8AB0-800E8CA4       .text daEsa_Create__FP10fopAc_ac_c */
static cPhs_State daEsa_Create(fopAc_ac_c* i_actor) {
    daPy_py_c* player = daPy_getPlayerActorClass();

    fopAcM_SetupActor(i_actor, esa_class);

    esa_class* i_this = static_cast<esa_class*>(i_actor);

    i_this->field_0x2B9 = fopAcM_GetParam(i_this) & 0xFF;
    i_this->field_0x2BA = fopAcM_GetParam(i_this) >> 8 & 0xFF;
    if(REG0_S(0) != 0) {
        i_this->field_0x2BA = 1;
    }

    if(!fopAcM_entrySolidHeap(i_this, daEsa_CreateHeap, 0x4C0)) {
        return cPhs_ERROR_e;
    }

    if(i_this->field_0x2BA == 0) {
        s8 num = i_this->field_0x2B9;
        if(num > 0) {
            for(int i = 0; i < num; i++) {
                fopAcM_prm_class* params = fopAcM_CreateAppend();
                cXyz pos = player->getLeftHandPos();
                params->base.position = pos;
                params->base.angle.x = 0;
                params->base.angle.y = i_this->current.angle.y;
                params->base.angle.z = cM_rndF(65536.0f);
                params->base.parameters = 0x000000FF;
                fpcM_Create(PROC_ESA, 0, params);
            }
        }
    }

    f32 temp = REG0_F(6) + 0.65f;
    f32 scaleF = temp + cM_rndF(REG0_F(5) + 1.0f - temp);
    cXyz scale(scaleF, scaleF, scaleF);
    i_this->mpModel->setBaseScale(scale);
    fopAcM_SetMtx(i_this, i_this->mpModel->getBaseTRMtx());

    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daEsa_Method = {
    (process_method_func)daEsa_Create,
    (process_method_func)daEsa_Delete,
    (process_method_func)daEsa_Execute,
    (process_method_func)daEsa_IsDelete,
    (process_method_func)daEsa_Draw,
};

actor_process_profile_definition g_profile_ESA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ESA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(esa_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_ESA,
    /* Actor SubMtd */ &l_daEsa_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
