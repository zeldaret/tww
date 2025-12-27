/**
 * d_a_tori_flag.cpp
 * Object - Great Sea - Small red flag (Flight Control Platform, Horseshoe Island)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_tori_flag.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_kankyo_wether.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "d/res/res_trflag.h"
#include "d/res/res_cloth.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_a_obj.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_BOOMERANG),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
        /* SrcGObjTg SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 400.0f,
    }},
};

/* 000000EC-00000118       .text __ct__17daTori_Flag_HIO_cFv */
daTori_Flag_HIO_c::daTori_Flag_HIO_c() {
    mNo = -1;
    m08 = 0.0f;
    m0C = 0;
}

static daTori_Flag_HIO_c l_HIO;

static cXyz l_flag_offset(0.0f, 350.0f, 0.0f);

const char daTori_Flag_c::M_arcname[7] = "Trflag";

/* 00000118-000001C4       .text set_mtx__13daTori_Flag_cFv */
void daTori_Flag_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(l_flag_offset);
    mpCloth->setMtx(mDoMtx_stack_c::get());
}

/* 000001C4-000001E4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daTori_Flag_c*)i_this)->CreateHeap();
}

/* 000001E4-0000030C       .text CreateHeap__13daTori_Flag_cFv */
BOOL daTori_Flag_c::CreateHeap() {
    BOOL ret;
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectRes(M_arcname, TRFLAG_BDL_ETHATA);
    JUT_ASSERT(0x120, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModel == NULL) {
        ret = FALSE;
    }
    else {
        ResTIMG* flagTimg = (ResTIMG *)dComIfG_getObjectRes(M_arcname, TRFLAG_BTI_ETHATA);
        ResTIMG* clothTimg = (ResTIMG *)dComIfG_getObjectRes("Cloth", CLOTH_BTI_CLOTHTOON);
        mpCloth = dCloth_packet_create(flagTimg, clothTimg, 5, 5, 210.0f, 105.0f, &mClothTevStr, NULL);
        ret = (mpCloth != NULL) ? TRUE : FALSE;
    }
    return ret;
}

/* 0000030C-000003A4       .text CreateInit__13daTori_Flag_cFv */
cPhs_State daTori_Flag_c::CreateInit() {
    mStts.Init(0xFF,0xFF,this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    cXyz* wind_vec = dKyw_get_wind_vec();
    mWindvec.x = wind_vec->x;
    mWindvec.y = wind_vec->y;
    mWindvec.z = wind_vec->z;
    set_mtx();
    dKy_tevstr_init(&mClothTevStr, current.roomNo, 0xFF);
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    return cPhs_COMPLEATE_e;
}

/* 000003C4-00000478       .text _create__13daTori_Flag_cFv */
cPhs_State daTori_Flag_c::_create() {
    fopAcM_SetupActor(this, daTori_Flag_c);
    cPhs_State result = dComIfG_resLoad(&mPhsTrflag, M_arcname);
    if (result != cPhs_COMPLEATE_e) {
        return result;
    }
    result = dComIfG_resLoad(&mPhsCloth, "Cloth");
    if (result != cPhs_COMPLEATE_e) {
        return result;
    }
    if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1020)) {
        result = CreateInit();
    }
    else {
        result = cPhs_ERROR_e;
    }
    return result;
}

/* 000003A4-000003C4       .text daTori_FlagCreate__FPv */
static cPhs_State daTori_FlagCreate(void* i_this) {
    return ((daTori_Flag_c*)i_this)->_create();
}

bool daTori_Flag_c::_delete() {
    dComIfG_resDelete(&mPhsTrflag, M_arcname);
    dComIfG_resDelete(&mPhsCloth, "Cloth");
    return TRUE;
}

/* 00000804-00000854       .text daTori_FlagDelete__FPv */
static BOOL daTori_FlagDelete(void* i_this) {
    return ((daTori_Flag_c*)i_this)->_delete();
}

/* 00000878-00000B1C       .text _execute__13daTori_Flag_cFv */
bool daTori_Flag_c::_execute() {
    set_mtx();
    mStts.Move();
    if (mCyl.ChkTgHit()) {
        daObj::HitSeStart(&current.pos, current.roomNo, &mCyl, 0x0B);
    }
    fopAcM_rollPlayerCrash(this, 40.0f, 7);
    cXyz wind;
    cXyz pt = current.pos + l_flag_offset;
    wind = dKyw_get_AllWind_vecpow(&pt);
    f32 windStrength = wind.abs();
    f32 currStrength = mWindvec.abs();
    if (windStrength > currStrength) {
        mWindvec.x = wind.x;
        mWindvec.y = wind.y;
        mWindvec.z = wind.z;
    }
    else {
        cLib_addCalcPos2(&mWindvec, wind, 0.05f, 0.05f);
    }
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
    mpCloth->setParam(0.4f, -1.5f, 0.75f, 0.9f, 0.9f, 0x400, 0, 900, -800, 7.0f, 6.0f);
    mpCloth->setWindPower(8.0f, 3.0f);
    mpCloth->setGlobalWind(&mWindvec);
    mpCloth->cloth_move();
    return 0;
}

/* 00000854-00000878       .text daTori_FlagExecute__FPv */
static BOOL daTori_FlagExecute(void* i_this) {
    return ((daTori_Flag_c*)i_this)->_execute();
}

bool daTori_Flag_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mClothTevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    mpCloth->cloth_draw();
    return TRUE;
}

/* 00000B1C-00000BB8       .text daTori_FlagDraw__FPv */
static BOOL daTori_FlagDraw(void* i_this) {
    return ((daTori_Flag_c*)i_this)->_draw();
}

/* 00000BB8-00000BC0       .text daTori_FlagIsDelete__FPv */
static BOOL daTori_FlagIsDelete(void*) {
    return TRUE;
}

static actor_method_class daTori_FlagMethodTable = {
    (process_method_func)daTori_FlagCreate,
    (process_method_func)daTori_FlagDelete,
    (process_method_func)daTori_FlagExecute,
    (process_method_func)daTori_FlagIsDelete,
    (process_method_func)daTori_FlagDraw,
};

actor_process_profile_definition g_profile_Tori_Flag = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Tori_Flag,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTori_Flag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Tori_Flag,
    /* Actor SubMtd */ &daTori_FlagMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
