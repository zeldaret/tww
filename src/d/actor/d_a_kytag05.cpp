/**
 * d_a_kytag05.cpp
 * Tag - Weather Tag 5
 */

#include "d/actor/d_a_kytag05.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/actor/d_a_ykgr.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_audio.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000080       .text daKytag05_Draw__FP13kytag05_class */
static BOOL daKytag05_Draw(kytag05_class*) {
    return TRUE;
}

/* 00000080-000003F4       .text daKytag05_Execute__FP13kytag05_class */
static BOOL daKytag05_Execute(kytag05_class* a_this) {
    static const s16 wind_table[] = {
        0x0000,
        0x8001,
        0xC000,
        0x4000,
    };
    static const s16 mufuu_timer[] = {
        10,
        10,
        0,
        90,
    };
    static const s16 fuu_timer[] = {
        150,
        150,
        150,
        150,
    };
    
    camera_process_class *camera = dComIfGp_getCamera(0);
    fopAc_ac_c *player = dComIfGp_getPlayer(0);
    f32 windPow = dKyw_get_wind_pow();
    f32 blend = 1.0f;

    if (g_env_light.mWind.mEvtWindSet == 0xFF) {
        return TRUE;
    }
    
    if (dComIfGp_event_runCheck() != FALSE && dComIfGp_evmng_startCheck("demo41") && dComIfGp_demo_get()) {
        u32 demoFrame = dComIfGp_demo_get()->getFrame();
        if(demoFrame >= 0x186) {
            f32 fVar7 = ((f32)demoFrame - 390.0f) / 100.0f;
            if(fVar7 > 1.0f) {
                fVar7 = 1.0f;
            }
            blend = 1.0f - fVar7;
            g_env_light.mSnowCount = (int)(200.0f * blend);
        } else if (demoFrame == 0x187) {
            daYkgr_c::stop();
        }
    }
    dKy_custom_colset(0, 7, blend);
    
    if((a_this->mIndex & 1) == 0) {
        if (a_this->mTimer >= fuu_timer[a_this->mIndex >> 1]) {
            a_this->mTimer = 0;
            a_this->mIndex += 1;
            g_env_light.mWind.mEvtWindSet = 2;
        } else {
            a_this->mTimer += 1;
        }
    } else {
        if (a_this->mTimer >= mufuu_timer[a_this->mIndex >> 1]) {
            a_this->mIndex += 1;
            if(a_this->mIndex >> 1 >= 4) {
                a_this->mIndex = 0;
            }
            s16 windY = wind_table[a_this->mIndex >> 1];
            dKyw_evt_wind_set(0, windY);
            a_this->mTimer = 0;
            g_env_light.mWind.mEvtWindSet = 1;
        } else {
            a_this->mTimer += 1;
        }
    }
    
    if((camera->mLookat.mEye.z > 1445.0f || player->current.pos.z > 1445.0f) &&
       (camera->mLookat.mEye.x > 520.0f || player->current.pos.x > 520.0f)){
        if(camera->mLookat.mEye.z > 2100.0f || player->current.pos.z > 2100.0f) {
            dKyw_evt_wind_set(0, 0x61A8);
        } else if(camera->mLookat.mEye.z > 1970.0f || player->current.pos.z > 1970.0f) {
            dKyw_evt_wind_set(0, 0x4E20);
        } else {
            dKyw_evt_wind_set(0, 0x4650);
        }
    } else if(camera->mLookat.mEye.z < -4085.0f || player->current.pos.z < -4085.0f) {
        dKyw_evt_wind_set(0, -0x3E80);
    } else if(camera->mLookat.mEye.z < -3108.0f || player->current.pos.z < -3108.0f) {
        dKyw_evt_wind_set(0, -0x4B00);
    } else if(camera->mLookat.mEye.z < -1412.0f || player->current.pos.z < -1412.0f) {
        dKyw_evt_wind_set(0, -0x32C8);
    }

    mDoAud_seStart(JA_SE_ATM_WIND_VAR, NULL, windPow * 100.0f);
    
    return TRUE;
}

/* 000003F4-000003FC       .text daKytag05_IsDelete__FP13kytag05_class */
static BOOL daKytag05_IsDelete(kytag05_class*) {
    return TRUE;
}

/* 000003FC-00000404       .text daKytag05_Delete__FP13kytag05_class */
static BOOL daKytag05_Delete(kytag05_class*) {
    return TRUE;
}

/* 00000404-000004C0       .text daKytag05_Create__FP10fopAc_ac_c */
static cPhs_State daKytag05_Create(fopAc_ac_c* i_this) {
#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(i_this, kytag05_class);
#endif
    kytag05_class *a_this = (kytag05_class*)i_this;
    if (dComIfGs_isSymbol(1) != 0) {
        return cPhs_STOP_e;
    }

#if VERSION == VERSION_DEMO
    fopAcM_SetupActor(i_this, kytag05_class);
#endif

    a_this->mIndex = 0;
    a_this->mTimer = 0;
    a_this->mUnknownParam = fopAcM_GetParam(i_this) & 0xff;
    dKyw_evt_wind_set_go();
    dKyw_evt_wind_set(0, 0);
    g_env_light.mSnowCount = 200;
#if VERSION != VERSION_USA
    g_env_light.mMoyaMode = 3;
#else
    g_env_light.mMoyaMode = 0;
#endif
    g_env_light.mMoyaCount = 100;

    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daKytag05_Method = {
    (process_method_func)daKytag05_Create,
    (process_method_func)daKytag05_Delete,
    (process_method_func)daKytag05_Execute,
    (process_method_func)daKytag05_IsDelete,
    (process_method_func)daKytag05_Draw,
};

actor_process_profile_definition g_profile_KYTAG05 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KYTAG05,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kytag05_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KYTAG05,
    /* Actor SubMtd */ &l_daKytag05_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
