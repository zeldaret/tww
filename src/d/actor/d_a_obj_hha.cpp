//
// Generated by dtk
// Translation Unit: d_a_obj_hha.cpp
//

#include "d/actor/d_a_obj_hha.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_bg_w.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/res/res_hha.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

const dCcD_SrcCyl daObjHha_c::M_cyl_data = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 570.0f,
        /* Height */ 100.0f,
    },
};

const dCcD_SrcSph daObjHha_c::M_sph_data = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 220.0f,
    },
};

const HHA_RES_FILE_ID l_daObjHha_bdl_idx_table[2] = {HHA_BDL_HHA1, HHA_BDL_HHA2};
const HHA_RES_FILE_ID l_daObjHha_dzb_idx_table[2] = {HHA_DZB_HHA1, HHA_DZB_HHA2};
const HHA_RES_FILE_ID l_daObjHha_btk_idx_table[2] = {HHA_BTK_YSWTR00_01, HHA_BTK_YSWTR00_02};
const u16 l_daObjHha_splash_id_table[2] = {0x810D, 0x810E};
const J3DFrameCtrl::Attribute_e l_daObjHha_btk_mode_table[2] = {J3DFrameCtrl::LOOP_REPEAT_e, J3DFrameCtrl::LOOP_ONCE_e};

/* 00000078-00000170       .text init_data__14daObjHhaPart_cFffUsUcUc */
void daObjHhaPart_c::init_data(float yPos, float yTar, u16 param3, u8 i, u8 param5) {
    m08.set(0, yPos, 0);
    m14.set(0, yTar, 0);
    partIdx = i;
    f2C = (yTar - yPos) / param3;
    m20 = m14 - m08;
    m20.normalizeRS();
    m34 = &daObjHhaPart_c::exe_normal;
    m40 = &daObjHhaPart_c::draw_normal;
    u31 = param5;
}

/* 00000170-00000224       .text set_mdl_area__14daObjHhaPart_cFPCci */
BOOL daObjHhaPart_c::set_mdl_area(const char* arcname, int index) {
    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(arcname, index));
    JUT_ASSERT(0x1d9, mdl_data != 0);
    if(mdl_data != NULL){
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203); 
    }

    return (mdl_data != NULL);
}

/* 00000224-000002A4       .text set_bgw__14daObjHhaPart_cFPCci */
BOOL daObjHhaPart_c::set_bgw(const char* arcname, int index) {
    mpBgw = dBgW_NewSet(
        static_cast<cBgD_t*>(dComIfG_getObjectRes(arcname, index)), 
        1,
        &mpModel->getBaseTRMtx()
    );

    return (mpBgw != NULL);
}

/* 000002A4-0000035C       .text init_mtx__14daObjHhaPart_cF4cXyz5csXyz4cXyz */
void daObjHhaPart_c::init_mtx(cXyz currentPos, csXyz shapeAngle, cXyz scale) {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(currentPos);
    mDoMtx_stack_c::ZXYrotM(shapeAngle);
    mDoMtx_stack_c::transM(m08);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::now);
    mpModel->calc();
}

/* 0000035C-0000040C       .text exe_normal__14daObjHhaPart_cFP10daObjHha_c */
void daObjHhaPart_c::exe_normal(daObjHha_c* parent) {
    init_mtx(parent->current.pos, parent->shape_angle, parent->scale);

    bool doMove;
    if(mpBgw != NULL){
        if(0 <= mpBgw->GetId() && mpBgw->GetId() < 0x100){
            doMove = true;
        }
        else {
            doMove = false;
        }

        if(doMove){
            mpBgw->Move();
        }
    }

}

/* 0000040C-00000524       .text exe_move__14daObjHhaPart_cFP10daObjHha_c */
void daObjHhaPart_c::exe_move(daObjHha_c* parent) {
    m08.y += f2C;
    cXyz unk0 = m14 - m08;
    if(m20.getDotProduct(unk0) <= 0.0f){
        m08 = m14;
        m34 = &daObjHhaPart_c::exe_normal;
        if(u31 == 0 && partIdx == 0){
            dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0,1.0,0.0));
        }
    } 
    exe_normal(parent);
}

/* 00000524-0000056C       .text draw_normal__14daObjHhaPart_cFP10daObjHha_c */
void daObjHhaPart_c::draw_normal(daObjHha_c* parent) {
    dKy_getEnvlight().setLightTevColorType(mpModel, &parent->tevStr);
    mDoExt_modelUpdateDL(mpModel);
}

/* 0000056C-00000698       .text create_s__16daObjHhaSplash_cFUsP4cXyzffP5csXyz */
void daObjHhaSplash_c::create_s(unsigned short id, cXyz* pPos, float offsetY, float offsetZ, csXyz* pAngle) {
    cXyz acStack38;

    mPos.set(pPos->x, pPos->y + offsetY, pPos->z);
    mDoMtx_stack_c::YrotS(pAngle->y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &acStack38);
    acStack38 *= offsetZ;
    mPos += acStack38;
    m14 = mPos;
    mAngle = *pAngle;
    dComIfGp_particle_set(id, &mPos, &mAngle, NULL, 0xff, this);
    b32 = true;
}

/* 00000698-000008AC       .text create_area__15daObjHhaYgush_cFPCc */
BOOL daObjHhaYgush_c::create_area(const char* arcname) {
    BOOL ret = FALSE;

    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(arcname, HHA_BDL_YGSTP00));
    JUT_ASSERT(0x280, mdl_data != 0);
    
    if(mdl_data != NULL){
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000222);
        JUT_ASSERT(0x289, mpModel != 0);

        if((mpModel != 0)){
            J3DAnmTextureSRTKey* btk_data = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(arcname, HHA_BTK_YGSTP00));
            JUT_ASSERT(0x290, btk_data != 0);
            
            if(mBtk.init(mpModel->getModelData(), btk_data, true, J3DFrameCtrl::LOOP_REPEAT_e, 1.0, 0, -1, false, 0) != false){  
                J3DAnmTransform* bck_data = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(arcname, HHA_BCK_YGSTP00));
                JUT_ASSERT(0x295, bck_data != 0);
                
                if(mBck.init(mpModel->getModelData(), bck_data, true, J3DFrameCtrl::LOOP_REPEAT_e, 1.0, 0, -1, false) != false){
                    ret = TRUE;
                }
            }
        }
    }

    return ret;
}

/* 000008AC-00000AD8       .text init_data__15daObjHhaYgush_cFP4cXyzfP5csXyzP4cXyzP12dKy_tevstr_cUc */
void daObjHhaYgush_c::init_data(cXyz* pPos, f32 param2, csXyz* pAngle, cXyz* pScale, dKy_tevstr_c* param5, u8 isVisible) {
    cXyz cStack3C;
    mDoMtx_stack_c::YrotS(pAngle->y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &cStack3C);
    cStack3C *= param2;
    mD8 = *pPos + cStack3C;
    mTrans = mD8;
    mRot = *pAngle;
    mScale = *pScale;
    mTev = *param5;
    bVisible = isVisible;
}

/* 00000AD8-00000B88       .text init_mtx__15daObjHhaYgush_cFv */
void daObjHhaYgush_c::init_mtx() {
    J3DModel* pModel = mpModel;
    if(pModel != NULL){
        pModel->setBaseScale(mScale);
        mDoMtx_stack_c::transS(mTrans);
        mDoMtx_stack_c::ZXYrotM(mRot);
        mDoMtx_stack_c::scaleM(13.0f, 1.0f, 11.0f);
        mpModel->setBaseTRMtx(mDoMtx_stack_c::now);
    }
}

/* 00000B88-00000C2C       .text draw__15daObjHhaYgush_cFv */
BOOL daObjHhaYgush_c::draw() {
    if(bVisible != false && mpModel != NULL){
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG1, &mTrans, &mTev);
        dKy_getEnvlight().setLightTevColorType(mpModel, &mTev);
        mBtk.entry(mpModel->getModelData());
        mBck.entry(mpModel->getModelData());
        mDoExt_modelUpdateDL(mpModel);
    }
}

/* 00000C2C-00000C4C       .text solidHeapCB__10daObjHha_cFP10fopAc_ac_c */
int daObjHha_c::solidHeapCB(fopAc_ac_c* this_i) {
    return static_cast<daObjHha_c*>(this_i)->create_heap();
}

const char daObjHha_c::M_arcname[] = "Hha";
const float pos_y[4] = {150.0f, -150.0f, 0.0f, 0.0f};
const float tar_y[4] = {0.0f, 0.0f, 150.0f, -150.0f};
const u16 move_frame[2] = {0x37, 0x1E};
const float splash_y[2] = {-1400.0f, -1450.0f};
const float splash_z[2] = {0.0f, 100.0f};

/* 00000C4C-00000E48       .text create_heap__10daObjHha_cFv */
BOOL daObjHha_c::create_heap() {
    BOOL ret = TRUE;

    for(int i = 0; i < 2; i++){
        if( (mPartA[i].set_mdl_area(M_arcname, l_daObjHha_bdl_idx_table[i]) == FALSE) || (mPartA[i].set_bgw(M_arcname, l_daObjHha_dzb_idx_table[i]) == FALSE) ){
            ret = FALSE;
            break;
        }
    }

    if(ret != FALSE){
        J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, 12));
        JUT_ASSERT(0x324, mdl_data != 0);
        if(mdl_data != 0){
            mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000222);
            for(int i = 0; i < 2; i++){
                J3DAnmTextureSRTKey* btk_data = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(M_arcname, l_daObjHha_btk_idx_table[i]));
                JUT_ASSERT(0x32f, btk_data != 0);
                if(mBtkA[i].init(mdl_data, btk_data, true, l_daObjHha_btk_mode_table[i], 1.0, 0, -1, false, 0) == FALSE){
                    ret = FALSE;
                    break;
                }
            }
        }
    }

    if(ret != FALSE){
        ret = mYgush.create_area(M_arcname);
    }

    return ret;
}

/* 00000E48-000011AC       .text _create__10daObjHha_cFv */
s32 daObjHha_c::_create() {
    fopAcM_SetupActor(this, daObjHha_c);
    s32 ret = dComIfG_resLoad(&mPhs, M_arcname);
    if(ret == cPhs_COMPLEATE_e){
        ret = cPhs_ERROR_e;
        if(fopAcM_entrySolidHeap(this, &solidHeapCB, 0x3C80) != false){
            i7AC = fpcM_GetParam(this) & 0xFF;
            i7B0 = fpcM_GetParam(this) >> 8;
            m7C0 = dComIfGp_evmng_getEventIdx("hha_close");

            if(i7B0 == 0xf){
                i7B0 = 0;
            }

            if(check_sw() != 0){
                i7B0 = i7B0 + 1 & 1;
                i7C2 = 2;
            }
            i7B2 = -1;

            int floatIdx = 2 * (i7B0 & 1);
            for(int i = 0; i < 2; i++){
                mPartA[i].init_data(pos_y[floatIdx], tar_y[floatIdx], move_frame[i7B0], i, i7B0);
                dComIfG_Bgsp()->Regist(mPartA[i].mpBgw, this);
                mPartA[i].init_mtx(current.pos, shape_angle, scale);
                floatIdx++;
            }

            f7A0 = 0.0f;
            f7A4 = -1400.0f;
            f7A8 = 50.0f;
            f7B4 = 1.0f;

            for(int i = 0; i < 2; i++){
                mSplashA[i].create_s(l_daObjHha_splash_id_table[i], &current.pos, splash_y[i], splash_z[i], &current.angle);
            }

            if(i7B0 == 0){
                set_tex(36.0f, 0.0f, 1);
                b430 = true;
                mYgush.init_data(&current.pos, 600.0f, &current.angle, &scale, &tevStr, true);
                i7C3 = 1;
            }
            else {
                set_tex(0.0f, 0.0f, 1);

                // Following might be an inline for loop
                JPABaseEmitter* pSplashEmitter = mSplashA[0].getEmitter();
                if(pSplashEmitter != NULL){
                    pSplashEmitter->setStatus(1);
                    mSplashA[0].b32 = false;
                }

                pSplashEmitter = mSplashA[1].getEmitter();
                if(pSplashEmitter != NULL){
                    pSplashEmitter->setStatus(1);
                    mSplashA[1].b32 = false;
                }

                mYgush.init_data(&current.pos, 600.0f, &current.angle, &scale, &tevStr, false);
                i7C3 = 0;
            }
            mYgush.init_mtx();
            init_mtx();
            init_co();
            cullMtx = mPartA[0].mpModel->getBaseTRMtx();
            fopAcM_setCullSizeBox(this, -700.0f, -1600.0f, -400.0f, 700.0f, 120.0f, 1000.0f);
            ret = cPhs_COMPLEATE_e;
        }
    }

    return ret;
}

/* 000018EC-000019EC       .text _delete__10daObjHha_cFv */
BOOL daObjHha_c::_delete() {
    if(heap != NULL){
        for(int i = 0; i < 2; i++){
            cBgW* bgw = mPartA[i].mpBgw;
            if(bgw != NULL){
                bool toErase;
                if(bgw->GetId() >= 0 && bgw->GetId() < 0x100){
                    toErase = true;
                }
                else {
                    toErase = false;
                }

                if(toErase){
                    dComIfG_Bgsp()->Release(bgw);
                    mPartA[i].mpBgw = NULL;
                }
            }
        }
    }

    for(int i = 0; i < 2; i++){
        if(mSplashA[i].getEmitter() != NULL){
            mSplashA[i].end();
            mSplashA[i].b32 = 0;
        }
    }

    dComIfG_resDelete(&mPhs, M_arcname);

    return TRUE;
}

/* 000019EC-00001A24       .text check_sw__10daObjHha_cFv */
s32 daObjHha_c::check_sw() {
    /* Nonmatching */
}

/* 00001A24-00001A40       .text set_tex__10daObjHha_cFffi */
void daObjHha_c::set_tex(float, float, int) {
    /* Nonmatching */
}

/* 00001A40-00001B00       .text init_mtx__10daObjHha_cFv */
void daObjHha_c::init_mtx() {
    /* Nonmatching */
}

/* 00001B00-00001C64       .text init_co__10daObjHha_cFv */
void daObjHha_c::init_co() {
    /* Nonmatching */
}

/* 00001C64-00001E14       .text get_water_h__10daObjHha_cFv */
void daObjHha_c::get_water_h() {
    /* Nonmatching */
}

/* 00001F38-00001F68       .text set_splash_bottom_h__10daObjHha_cFv */
void daObjHha_c::set_splash_bottom_h() {
    /* Nonmatching */
}

/* 00001F68-0000201C       .text daObjHha_get_r__Fs */
void daObjHha_get_r(short) {
    /* Nonmatching */
}

/* 0000201C-000020C0       .text set_splash_bottom_r__10daObjHha_cFv */
void daObjHha_c::set_splash_bottom_r() {
    /* Nonmatching */
}

/* 000020C0-000021CC       .text set_splash_bottom_stop_r__10daObjHha_cFv */
void daObjHha_c::set_splash_bottom_stop_r() {
    /* Nonmatching */
}

/* 000021CC-00002470       .text water_manager__10daObjHha_cFv */
void daObjHha_c::water_manager() {
    /* Nonmatching */
}

/* 00002470-0000259C       .text part_manager__10daObjHha_cFv */
void daObjHha_c::part_manager() {
    /* Nonmatching */
}

/* 0000259C-00002658       .text ygush_manager__10daObjHha_cFv */
void daObjHha_c::ygush_manager() {
    /* Nonmatching */
}

/* 00002658-000028E4       .text _execute__10daObjHha_cFv */
BOOL daObjHha_c::_execute() {
    /* Nonmatching */
}

/* 000028E4-000029F4       .text _draw__10daObjHha_cFv */
BOOL daObjHha_c::_draw() {
    /* Nonmatching */
}

namespace {
/* 000029F4-00002A14       .text Mthd_Create__25@unnamed@d_a_obj_hha_cpp@FPv */
void Mthd_Create(void*) {
    /* Nonmatching */
}

/* 00002A14-00002A38       .text Mthd_Delete__25@unnamed@d_a_obj_hha_cpp@FPv */
void Mthd_Delete(void*) {
    /* Nonmatching */
}

/* 00002A38-00002A5C       .text Mthd_Execute__25@unnamed@d_a_obj_hha_cpp@FPv */
void Mthd_Execute(void*) {
    /* Nonmatching */
}

/* 00002A5C-00002A80       .text Mthd_Draw__25@unnamed@d_a_obj_hha_cpp@FPv */
void Mthd_Draw(void*) {
    /* Nonmatching */
}

/* 00002A80-00002A88       .text Mthd_IsDelete__25@unnamed@d_a_obj_hha_cpp@FPv */
void Mthd_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class Hha_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Hha = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Hha,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHha_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0049,
    /* Actor SubMtd */ &Hha_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
