/**
 * d_a_obj_majyuu_door.cpp
 * Object - Forsaken Fortress - Large wooden barricade (blocks entrance, destroyed with Bombs)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_majyuu_door.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_math.h"
#include "d/d_bg_s_func.h"
#include "d/d_com_inf_game.h"
#include "d/d_particle_name.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_audio.h"

const u32 daObj_MjDoor_c::m_heapsize = 0x820;
const char daObj_MjDoor_c::m_arc_name[] = "S_MSPDo";

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 75.0f,
        /* Height */ 115.0f,
    }},
};

GXColor daObj_MjDoor_c::smoke_col = {0x86, 0x84, 0x6D, 0xC8};

inline void daObj_MjDoor_c::modeProcCall() {
    static ModeProc mode_proc[] = {
        &daObj_MjDoor_c::modeWait,
        &daObj_MjDoor_c::modeDelete,
    };
    (this->*mode_proc[mMode])();
}
static daObj_MjDoorHIO_c l_HIO;

struct mjdoor_smoke_scale {
    mjdoor_smoke_scale() {
        x = 1.25f;
        y = 1.25f;
        z = 1.25f;
    }

    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
};


/* 000000EC-0000010C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_actor) {
    return ((daObj_MjDoor_c*)i_actor)->_createHeap();
}

/* 0000010C-00000130       .text TgHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void TgHitCallback(fopAc_ac_c* i_actor, dCcD_GObjInf*, fopAc_ac_c* i_atActor,
                   dCcD_GObjInf*) {
    if (i_atActor != NULL && fopAcM_GetName(i_atActor) == fpcNm_BOMB_e) {
        ((daObj_MjDoor_c*)i_actor)->health--;
    }
}

/* 00000130-00000154       .text __ct__17daObj_MjDoorHIO_cFv */
daObj_MjDoorHIO_c::daObj_MjDoorHIO_c() {
    field_0x4 = 0;
}

/* 0000019C-00000240       .text set_mtx__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    if (mMode != 1) {
        MTXCopy(mDoMtx_stack_c::get(), mMtx);
        mpBgw->Move();
    }
}

/* 00000240-000003A0       .text _createHeap__14daObj_MjDoor_cFv */
BOOL daObj_MjDoor_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, 4);
    JUT_ASSERT(199, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpModel == NULL) {
        return FALSE;
    }

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    MTXCopy(mDoMtx_stack_c::get(), mMtx);

    mpBgw = new dBgW();
    if (mpBgw == NULL) {
        return FALSE;
    }

    return (TRUE - mpBgw->Set((cBgD_t*)dComIfG_getObjectRes(m_arc_name, 7), 1, &mMtx))
               ? TRUE
               : FALSE;
}

/* 000003A0-000003AC       .text getArg__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::getArg() {
    mSwitchNo = fopAcM_GetParam(this);
}

/* 000003AC-00000478       .text CreateInit__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::CreateInit() {
    mStts.Init(0xFF, 0, this);

    dCcD_Cyl* cyl = mCyl;
    for (int i = 0; i < 10; i++, cyl++) {
        cyl->Set(l_cyl_src);
        cyl->SetStts(&mStts);
        cyl->SetTgHitCallback(TgHitCallback);
    }
    mCyl[1].SetR(95.0f);

    dComIfG_Bgsp()->Regist(mpBgw, this);
    set_mtx();
    modeWaitInit();
    max_health = 30;
    health = max_health;
}

/* 00000478-000005B4       .text _create__14daObj_MjDoor_cFv */
cPhs_State daObj_MjDoor_c::_create() {
    fopAcM_ct_Retail(this, daObj_MjDoor_c);

    cPhs_State phase = dComIfG_resLoad(&mPhs, m_arc_name);
    fopAcM_ct_Demo(this, daObj_MjDoor_c);
    if (phase == cPhs_COMPLEATE_e) {
        getArg();
        if (mSwitchNo != 0xFF &&
            dComIfGs_isSwitch(mSwitchNo, DEMO_SELECT((char)current.roomNo, current.roomNo))) {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }

    return phase;
}

/* 000007F0-00000884       .text _delete__14daObj_MjDoor_cFv */
bool daObj_MjDoor_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);

    if (mpBgw != NULL && mpBgw->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgw);
    }
    mSmoke.remove();
    return true;
}

/* 00000884-000009D4       .text setCollision__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::setCollision() {
    f32 offsets[] = {
        -500.0f, -400.0f, -300.0f, -200.0f, -100.0f,
        0.0f,    100.0f,  200.0f,  300.0f,  400.0f,
    };
    f32 sin_y = cM_ssin(current.angle.y);
    f32 cos_y = cM_scos(current.angle.y);

    dCcD_Cyl* cyl = mCyl;
    for (int i = 0; i < 10; i++, cyl++) {
        cXyz center(current.pos.x + cos_y * offsets[i], current.pos.y - REG12_F(0),
                    current.pos.z + -sin_y * offsets[i]);
        cyl->SetC(center);
        cyl->SetR(100.0f);
        cyl->SetH(1350.0f);
        dComIfG_Ccsp()->Set(cyl);
    }
}

/* 000009D4-000009E0       .text modeWaitInit__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeWaitInit() {
    mMode = 0;
}

/* 000009E0-00000A34       .text modeWait__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeWait() {
    setCollision();
    if (health < 0 || l_HIO.field_0x4 != 0) {
        modeDeleteInit();
    }
}

/* 00000A34-00000AEC       .text smoke_set__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::smoke_set() {
    static mjdoor_smoke_scale smoke_scale;
#if VERSION == VERSION_DEMO
    s8 room_no = current.roomNo;
#else
    s8 room_storage = current.roomNo;
    s8* room_ptr = &room_storage;
    s8 room_no = *room_ptr;
#endif

    dComIfGp_particle_setToon(dPa_name::ID_IT_ST_MJMON_SMOKE00, &mSmokePos, &mSmokeAngle,
                              NULL, 0xB9, &mSmoke, room_no);
    if (mSmoke.getEmitter() != NULL) {
        mSmoke.getEmitter()->mGlobalPrmColor.a = 200;
    }
}

/* 00000AEC-00000D64       .text modeDeleteInit__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeDeleteInit() {
    if (mSwitchNo != 0xFF) {
        dComIfGs_onSwitch(mSwitchNo, DEMO_SELECT((char)current.roomNo, current.roomNo));
    }
    mMode = 1;

    mDoAud_seStart(
        JA_SE_OBJ_MJ_GATE_BREAK, &eyePos, 0,
        dComIfGp_getReverb(DEMO_SELECT((char)current.roomNo, current.roomNo)));

    cXyz scale(1.0f, 1.0f, 1.0f);
    dComIfGp_particle_set(dPa_name::ID_IT_SN_MJMON_HAHEN_L00, &current.pos, &current.angle,
                          &scale, 0xFF, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0);
    dComIfGp_particle_set(dPa_name::ID_IT_SN_MJMON_HAHEN_S00, &current.pos, &current.angle,
                          &scale, 0xFF, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0);

    cXyz water_pos = current.pos;
    water_pos.y = dBgS_GetWaterHeight(water_pos);
    dComIfGp_particle_set(dPa_name::ID_IT_SN_MJMON_HAMON00, &water_pos, &current.angle,
                          &scale);
    dComIfGp_particle_set(dPa_name::ID_IT_SN_MJMON_SHIBUKI00, &water_pos, &current.angle,
                          &scale);

    mSmokePos = current.pos;
    mSmokeAngle = current.angle;
    smoke_set();
    mSmokeTimer = 50;
    mDeleteTimer = 600;

    dComIfG_Bgsp()->Release(mpBgw);
    dCcD_Cyl* cyl = mCyl;
    for (int i = 0; i < 10; i++, cyl++) {
        cyl->OffCoSPrmBit(cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e |
                          cCcD_CoSPrm_VsGrpAll_e);
        cyl->OffTgSPrmBit(cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e);
    }
}

/* 00000D64-00000DF0       .text modeDelete__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeDelete() {
    if (mSmoke.getEmitter() != NULL) {
        if (cLib_calcTimer(&mSmokeTimer) != 0) {
            if (mSmokeTimer <= 40) {
#if VERSION == VERSION_DEMO
                u8 alpha = mSmokeTimer * 5;
                mSmoke.getEmitter()->mGlobalPrmColor.a = alpha;
#else
                JPABaseEmitter* emitter = mSmoke.getEmitter();
                emitter->mGlobalPrmColor.a = mSmokeTimer * 5;
#endif
            }
        } else {
            mSmoke.remove();
        }
    }

    if (cLib_calcTimer(&mDeleteTimer) == 0) {
        fopAcM_delete(this);
    }
}

/* 00000DF0-00000EB4       .text _execute__14daObj_MjDoor_cFv */
bool daObj_MjDoor_c::_execute() {
    modeProcCall();
    fopAcM_posMoveF(this, NULL);
    set_mtx();
    return false;
}

/* 00000EB4-00000F28       .text _draw__14daObj_MjDoor_cFv */
bool daObj_MjDoor_c::_draw() {
    if (mMode == 1) {
        return true;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

/* 00000F28-00000F48       .text daObj_MjDoorCreate__FPv */
static cPhs_State daObj_MjDoorCreate(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_create();
}

/* 00000F48-00000F6C       .text daObj_MjDoorDelete__FPv */
static BOOL daObj_MjDoorDelete(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_delete();
}

/* 00000F6C-00000F90       .text daObj_MjDoorExecute__FPv */
static BOOL daObj_MjDoorExecute(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_execute();
}

/* 00000F90-00000FB4       .text daObj_MjDoorDraw__FPv */
static BOOL daObj_MjDoorDraw(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_draw();
}

/* 00000FB4-00000FBC       .text daObj_MjDoorIsDelete__FPv */
static BOOL daObj_MjDoorIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_MjDoorMethodTable = {
    (process_method_func)daObj_MjDoorCreate,
    (process_method_func)daObj_MjDoorDelete,
    (process_method_func)daObj_MjDoorExecute,
    (process_method_func)daObj_MjDoorIsDelete,
    (process_method_func)daObj_MjDoorDraw,
};

actor_process_profile_definition g_profile_OBJ_MJDOOR = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_OBJ_MJDOOR_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_MjDoor_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_OBJ_MJDOOR_e,
    /* Actor SubMtd */ &daObj_MjDoorMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_4_e,
};
