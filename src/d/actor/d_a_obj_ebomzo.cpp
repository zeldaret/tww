/**
 * d_a_obj_ebomzo.cpp
 * Object - Bombable statues (outside Dragon Roost Cavern entrance)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ebomzo.h"
#include "dolphin/types.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "d/res/res_ebomzo.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

typedef enum {
    /*0*/ Ebomzo_Mode_Check = 0,
    /*1*/ Ebomzo_Mode_Demo,
    /*2*/ Ebomzo_Mode_Fall,
} EbomzoMode;

Mtx daObjEbomzo::Act_c::M_tmp_mtx;
const char daObjEbomzo::Act_c::M_arcname[] = "Ebomzo";

dCcD_SrcSph sph_check_src = {
    //dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_BOMB,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 10.0f,
    }},
};

/* 00000078-0000012C       .text CreateHeap__Q211daObjEbomzo5Act_cFv */
BOOL daObjEbomzo::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, EBOMZO_BDL_EBOMZO);
    JUT_ASSERT(140, model_data != NULL);
    mpModel = mDoExt_J3DModel__create(model_data, 0, 0x11020203);
    return mpModel != NULL;
}

/* 0000012C-0000021C       .text Create__Q211daObjEbomzo5Act_cFv */
BOOL daObjEbomzo::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();

    fopAcM_setCullSizeBox(this, -1000.0f, -100.0f, -1000.0f, 1000.0f, 1000.0f, 1000.0f);

    mStts.Init(0xff, 0xff, this);
    mCollider.Set(sph_check_src);
    mCollider.SetStts(&mStts);

    mXRotRate = 0;
    mpParticleEmitter = NULL;

    if (fopAcM_isSwitch(this, prm_get_swSave())) {
        mMode = Ebomzo_Mode_Fall;
        current.angle.x = 0x4000;
    }
    else mMode = Ebomzo_Mode_Check;

    return TRUE;
}

/* 0000021C-000003A0       .text Mthd_Create__Q211daObjEbomzo5Act_cFv */
cPhs_State daObjEbomzo::Act_c::Mthd_Create() {
    fopAcM_SetupActor(this, daObjEbomzo::Act_c);
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, EBOMZO_DZB_EBOMZO, NULL, 0x1200);
        JUT_ASSERT(194, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 00000558-00000560       .text Delete__Q211daObjEbomzo5Act_cFv */
BOOL daObjEbomzo::Act_c::Delete() {
    return TRUE;
}

/* 00000560-000005AC       .text Mthd_Delete__Q211daObjEbomzo5Act_cFv */
BOOL daObjEbomzo::Act_c::Mthd_Delete() {
    u32 result = MoveBGDelete();
    dComIfG_resDelete(&mPhs, M_arcname);
    return result;
}

/* 000005AC-0000062C       .text set_mtx__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 0000062C-00000668       .text init_mtx__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000668-00000864       .text check__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::check() {
    if (mCollider.ChkTgHit()) {
        fopAc_ac_c* acActor = mCollider.GetTgHitAc();
        if (acActor) {
            cXyz diffVec = mCollider.GetC() - acActor->current.pos;
            if (diffVec.abs() < 100.0f) {
                mXRotRate = 8;
                current.angle.x += mXRotRate;

                fopAcM_seStartCurrent(this, JA_SE_OBJ_BOMB_DN_ST_S, 0);
                mMode = Ebomzo_Mode_Demo;

                fopAcM_onSwitch(this, prm_get_swSave());
                
                if (!mpParticleEmitter) {
                    const u8 r = tevStr.mColorK0.r;
                    const u8 g = tevStr.mColorK0.g;
                    const u8 b = tevStr.mColorK0.b;
                    mpParticleEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_828E, &current.pos, &current.angle);
                    if (mpParticleEmitter) mpParticleEmitter->setGlobalPrmColor(r, g, b);
                }
            }
        }
    }
}

/* 00000864-000009BC       .text demo__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::demo() {
    mXRotRate += mXRotRate / 8;
    current.angle.x += mXRotRate;

    if (current.angle.x >= 0x4000) {
        current.angle.x = 0x4000;
        mMode = Ebomzo_Mode_Fall;

        dComIfGp_getVibration().StartShock(4, -33, cXyz(0.0f, 1.0f, 0.0f));
        fopAcM_seStartCurrent(this, JA_SE_OBJ_BOMB_DN_ST_E, 0);

        if (mpParticleEmitter) {
            mpParticleEmitter->becomeInvalidEmitter();
            mpParticleEmitter = NULL;
        }

        dComIfGp_particle_set(dPa_name::ID_SCENE_828F, &current.pos, &current.angle);
    }
}

/* 000009BC-000009C0       .text fall__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::fall() {}

/* 000009C0-00000AFC       .text Execute__Q211daObjEbomzo5Act_cFPPA3_A4_f */
BOOL daObjEbomzo::Act_c::Execute(Mtx** matrix) {
    cXyz offset;

    offset.x = cM_ssin(current.angle.y) * 50.0f;
    offset.y = 320.0f;
    offset.z = cM_scos(current.angle.y) * 50.0f;

    mCollider.SetC(current.pos + offset);
    dComIfG_Ccsp()->Set(&mCollider);

    switch (this->mMode) {
    case Ebomzo_Mode_Check: check(); break;
    case Ebomzo_Mode_Demo: demo(); break;
    case Ebomzo_Mode_Fall: fall(); break;
    }

    shape_angle = current.angle;
    set_mtx();
    *matrix = &M_tmp_mtx;

    return TRUE;
}

/* 00000AFC-00000B9C       .text Draw__Q211daObjEbomzo5Act_cFv */
BOOL daObjEbomzo::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    dComIfG_Bgsp();
    return TRUE;
}

namespace daObjEbomzo {
    namespace {
        /* 00000B9C-00000BBC      .text Mthd_Create__Q211daObjEbomzo28@unnamed@d_a_obj_ebomzo_cpp@FPv */
        cPhs_State Mthd_Create(void* i_this) {
            return static_cast<Act_c*>(i_this)->Mthd_Create();
        }

        /* 00000BBC-00000BDC      .text Mthd_Delete__Q211daObjEbomzo28@unnamed@d_a_obj_ebomzo_cpp@FPv  */
        BOOL Mthd_Delete(void* i_this) {
            return static_cast<Act_c*>(i_this)->Mthd_Delete();
        }

        /* 00000BDC-00000BFC      .text Mthd_Execute__Q211daObjEbomzo28@unnamed@d_a_obj_ebomzo_cpp@FPv  */
        BOOL Mthd_Execute(void* i_this) {
            return static_cast<Act_c*>(i_this)->MoveBGExecute();
        }

        /* 00000BFC-00000C28      .text Mthd_Draw__Q211daObjEbomzo28@unnamed@d_a_obj_ebomzo_cpp@FPv  */
        BOOL Mthd_Draw(void* i_this) {
            return static_cast<Act_c*>(i_this)->MoveBGDraw();
        }

        /* 00000C28-00000C54      .text Mthd_IsDelete__Q211daObjEbomzo28@unnamed@d_a_obj_ebomzo_cpp@FPv  */
        BOOL Mthd_IsDelete(void* i_this) {
            return static_cast<Act_c*>(i_this)->MoveBGIsDelete();
        }

        static actor_method_class Mthd_Ebomzo = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    }
}

actor_process_profile_definition g_profile_Obj_Ebomzo = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ebomzo,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjEbomzo::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ebomzo,
    /* Actor SubMtd */ &daObjEbomzo::Mthd_Ebomzo,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
