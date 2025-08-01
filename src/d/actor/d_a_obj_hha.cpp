/**
 * d_a_obj_hha.cpp
 * Object - Tower of the Gods - Entrance waterfall
 */

#include "d/actor/d_a_obj_hha.h"
#include "d/actor/d_a_tag_waterlevel.h"
#include "d/d_bg_s_func.h"
#include "d/d_bg_s_wtr_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_hha.h"

#if VERSION == VERSION_DEMO
dCcD_SrcCyl l_daObjHha_cyl_data =
#else
const dCcD_SrcCyl daObjHha_c::M_cyl_data =
#endif
{
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

#if VERSION > VERSION_DEMO
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
#endif

const HHA_RES_FILE_ID l_daObjHha_bdl_idx_table[2] = {HHA_BDL_HHA1, HHA_BDL_HHA2};
const HHA_RES_FILE_ID l_daObjHha_dzb_idx_table[2] = {HHA_DZB_HHA1, HHA_DZB_HHA2};
const HHA_RES_FILE_ID l_daObjHha_btk_idx_table[2] = {HHA_BTK_YSWTR00_01, HHA_BTK_YSWTR00_02};
const J3DFrameCtrl::Attribute_e l_daObjHha_btk_mode_table[2] = {J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_NONE};
const u16 l_daObjHha_splash_id_table[] = {
    dPa_name::ID_SCENE_810D,
    dPa_name::ID_SCENE_810E,
};

/* 00000078-00000170       .text init_data__14daObjHhaPart_cFffUsUcUc */
void daObjHhaPart_c::init_data(float yPos, float yTar, u16 speed, u8 i, u8 isMiddle) {
    mPos.set(0.0f, yPos, 0.0f);
    mPosTarget.set(0.0f, yTar, 0.0f);
    mPartIdx = i;
    mDeltaY = (yTar - yPos) / speed;
    mPosDeltaDir = mPosTarget - mPos;
    mPosDeltaDir.normalizeRS();
    mCbExec = &daObjHhaPart_c::exe_normal;
    mCbDraw = &daObjHhaPart_c::draw_normal;
    mbMid = isMiddle;
}

/* 00000170-00000224       .text set_mdl_area__14daObjHhaPart_cFPCci */
BOOL daObjHhaPart_c::set_mdl_area(const char* arcname, int index) {
    J3DModelData* mdl_data;
    BOOL ret;
    ret = FALSE;
    mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(arcname, index));
    JUT_ASSERT(DEMO_SELECT(410, 473), mdl_data != NULL);
    if(mdl_data != NULL){
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203); 
        ret = TRUE;
    }

    return ret;
}

/* 00000224-000002A4       .text set_bgw__14daObjHhaPart_cFPCci */
BOOL daObjHhaPart_c::set_bgw(const char* arcname, int index) {
    BOOL ret = TRUE;
    mpBgw = dBgW_NewSet(
        static_cast<cBgD_t*>(dComIfG_getObjectRes(arcname, index)), 
        1,
        &mpModel->getBaseTRMtx()
    );

    if(mpBgw == NULL){
        ret = FALSE;
    }

    return ret;
}

/* 000002A4-0000035C       .text init_mtx__14daObjHhaPart_cF4cXyz5csXyz4cXyz */
void daObjHhaPart_c::init_mtx(cXyz currentPos, csXyz shapeAngle, cXyz scale) {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(currentPos);
    mDoMtx_stack_c::ZXYrotM(shapeAngle);
    mDoMtx_stack_c::transM(mPos);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 0000035C-0000040C       .text exe_normal__14daObjHhaPart_cFP10daObjHha_c */
void daObjHhaPart_c::exe_normal(daObjHha_c* parent) {
    init_mtx(parent->current.pos, parent->shape_angle, parent->scale);

    if (mpBgw != NULL && mpBgw->ChkUsed()) {
        mpBgw->Move();
    }

}

/* 0000040C-00000524       .text exe_move__14daObjHhaPart_cFP10daObjHha_c */
void daObjHhaPart_c::exe_move(daObjHha_c* parent) {
    mPos.y += mDeltaY;
    cXyz positionDelta = mPosTarget - mPos;
    if(mPosDeltaDir.getDotProduct(positionDelta) <= 0.0f){
        mPos = mPosTarget;
        setExeProc(&daObjHhaPart_c::exe_normal);
        if(mbMid == 0 && mPartIdx == 0){
            dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
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
void daObjHhaSplash_c::create_s(u16 particleID, cXyz* pPos, float offsetY, float offsetZ, csXyz* pAngle) {
    cXyz calcVec;

    mPos.set(pPos->x, pPos->y + offsetY, pPos->z);
    mDoMtx_stack_c::YrotS(pAngle->y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &calcVec);
    calcVec *= offsetZ;
    mPos += calcVec;
    mBasePos = mPos;
    mAngle = *pAngle;
#if VERSION == VERSION_DEMO
    mpEmitter =
#endif
    dComIfGp_particle_set(particleID, &mPos, &mAngle, NULL, 255, &mSplashCb);
    mbIsActive = true;
}

/* 00000698-000008AC       .text create_area__15daObjHhaYgush_cFPCc */
BOOL daObjHhaYgush_c::create_area(const char* arcname) {
    BOOL ret = FALSE;

    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(arcname, HHA_BDL_YGSTP00));
    JUT_ASSERT(DEMO_SELECT(577, 640), mdl_data != NULL);
    
    if(mdl_data != NULL){
        M_mdl = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000222);
        JUT_ASSERT(DEMO_SELECT(586, 649), M_mdl != NULL);

        if(M_mdl != NULL){
            J3DAnmTextureSRTKey* btk_data = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(arcname, HHA_BTK_YGSTP00));
            JUT_ASSERT(DEMO_SELECT(593, 656), btk_data != NULL);
            
            if(mBtk.init(M_mdl->getModelData(), btk_data, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, false) != false){  
                J3DAnmTransform* bck_data = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(arcname, HHA_BCK_YGSTP00));
                JUT_ASSERT(DEMO_SELECT(598, 661), bck_data != NULL);
                
                if(mBck.init(M_mdl->getModelData(), bck_data, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false) != false){
                    ret = TRUE;
                }
            }
        }
    }

    return ret;
}

/* 000008AC-00000AD8       .text init_data__15daObjHhaYgush_cFP4cXyzfP5csXyzP4cXyzP12dKy_tevstr_cUc */
void daObjHhaYgush_c::init_data(cXyz* pPos, f32 zScale, csXyz* pAngle, cXyz* pScale, dKy_tevstr_c* tev, u8 isVisible) {
    cXyz calcVec;
    mDoMtx_stack_c::YrotS(pAngle->y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &calcVec);
    calcVec *= zScale;
    mBasePos = *pPos + calcVec;
    mPos = mBasePos;
    mRot = *pAngle;
    mScale = *pScale;
    mTev = *tev;
    mbVisible = isVisible;
}

/* 00000AD8-00000B88       .text init_mtx__15daObjHhaYgush_cFv */
void daObjHhaYgush_c::init_mtx() {
    J3DModel* pModel = M_mdl;
    if(pModel != NULL){
        pModel->setBaseScale(mScale);
        mDoMtx_stack_c::transS(mPos);
        mDoMtx_stack_c::ZXYrotM(mRot);
        mDoMtx_stack_c::scaleM(13.0f, 1.0f, 11.0f);
        M_mdl->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 00000B88-00000C2C       .text draw__15daObjHhaYgush_cFv */
void daObjHhaYgush_c::draw() {
    if(mbVisible != false && M_mdl != NULL){
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG1, &mPos, &mTev);
        dKy_getEnvlight().setLightTevColorType(M_mdl, &mTev);
        mBtk.entry(M_mdl->getModelData());
        mBck.entry(M_mdl->getModelData());
        mDoExt_modelUpdateDL(M_mdl);
    }
}

const char daObjHha_c::M_arcname[] = "Hha";

/* 00000C2C-00000C4C       .text solidHeapCB__10daObjHha_cFP10fopAc_ac_c */
int daObjHha_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<daObjHha_c*>(i_this)->create_heap();
}

/* 00000C4C-00000E48       .text create_heap__10daObjHha_cFv */
BOOL daObjHha_c::create_heap() {
    int i;
    BOOL ret = TRUE;

    for(i = 0; i < 2; i++){
        if( (mPartA[i].set_mdl_area(M_arcname, l_daObjHha_bdl_idx_table[i]) == FALSE) || (mPartA[i].set_bgw(M_arcname, l_daObjHha_dzb_idx_table[i]) == FALSE) ){
            ret = FALSE;
            break;
        }
    }

    if(ret != FALSE){
        J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, HHA_BDL_YSWTR00));
        JUT_ASSERT(0x324, mdl_data != NULL);
        if(mdl_data != NULL){
            mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000222);
            for(i = 0; i < 2; i++){
                J3DAnmTextureSRTKey* btk_data = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(M_arcname, l_daObjHha_btk_idx_table[i]));
                JUT_ASSERT(0x32f, btk_data != NULL);
                if(mBtkA[i].init(mdl_data, btk_data, true, l_daObjHha_btk_mode_table[i], 1.0f, 0, -1, false, false) == FALSE){
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
cPhs_State daObjHha_c::_create() {
    static const float pos_y[4] = {150.0f, -150.0f, 0.0f, 0.0f};
    static const float tar_y[4] = {0.0f, 0.0f, 150.0f, -150.0f};
    static const u16 move_frame[2] = {55, 30};
    static const float splash_y[2] = {-1400.0f, -1450.0f};
    static const float splash_z[2] = {0.0f, 100.0f};


    fopAcM_SetupActor(this, daObjHha_c);
    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if(ret == cPhs_COMPLEATE_e){
        ret = cPhs_ERROR_e;
        if(fopAcM_entrySolidHeap(this, &solidHeapCB, 0x3C80) != false){
            mSwitchNo = fpcM_GetParam(this) & 0xFF;
            mIsMiddle = fpcM_GetParam(this) >> 8;
            mEventIdx = dComIfGp_evmng_getEventIdx("hha_close");

            if(mIsMiddle == 0xf)
                mIsMiddle = 0;

            if(check_sw() != FALSE){
                mIsMiddle = (mIsMiddle + 1) & 1; // Negate and make sure that mIsMiddle is just 0 or 1
                mState = State_CLOSED;
            }
            mPartTimer = -1;

            int posIdx = 2 * (mIsMiddle & 1);
            for(int i = 0; i < 2; i++){
                mPartA[i].init_data(pos_y[posIdx], tar_y[posIdx], move_frame[mIsMiddle], i, mIsMiddle);
                dComIfG_Bgsp()->Regist(mPartA[i].mpBgw, this);
                mPartA[i].init_mtx(current.pos, shape_angle, scale);
                posIdx++;
            }

            mPosOffset.set(0.0f, -1400.0f, 50.0f);
            mWtrScale = 1.0f;

            for(int i = 0; i < 2; i++){
                mSplashA[i].create_s(l_daObjHha_splash_id_table[i], &current.pos, splash_y[i], splash_z[i], &current.angle);
            }

            if(mIsMiddle == 0){
                set_tex(36.0f, 0.0f, 1);
                mHitboxActive = true;
                mYgush.init_data(&current.pos, 600.0f, &current.angle, &scale, &tevStr, true);
                mWaterSound = true;
            }
            else {
                set_tex(0.0f, 0.0f, 1);
                mSplashA[0].stop_particle();
                mSplashA[1].stop_particle();
                mYgush.init_data(&current.pos, 600.0f, &current.angle, &scale, &tevStr, false);
                mWaterSound = false;
            }
            mYgush.init_mtx();
            init_mtx();
            init_co();
            fopAcM_SetMtx(this, mPartA[0].mpModel->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -700.0f, -1600.0f, -400.0f, 700.0f, 120.0f, 1000.0f);
            ret = cPhs_COMPLEATE_e;
        }
    }

    return ret;
}

/* 000018EC-000019EC       .text _delete__10daObjHha_cFv */
bool daObjHha_c::_delete() {
    int i;
#if VERSION > VERSION_DEMO
    if(heap != NULL){
#endif
        for(i = 0; i < 2; i++){
            cBgW* bgw = mPartA[i].mpBgw;
            if(bgw != NULL && bgw->ChkUsed()) {
                dComIfG_Bgsp()->Release(bgw);
#if VERSION > VERSION_DEMO
                mPartA[i].mpBgw = NULL;
#endif
            }
        }
#if VERSION > VERSION_DEMO
    }
#endif

    for(i = 0; i < 2; i++){
        mSplashA[i].delete_s();
    }

    dComIfG_resDelete(&mPhs, M_arcname);

    return TRUE;
}

/* 000019EC-00001A24       .text check_sw__10daObjHha_cFv */
inline BOOL daObjHha_c::check_sw() {
    return fopAcM_isSwitch(this, mSwitchNo);
}

/* 00001A24-00001A40       .text set_tex__10daObjHha_cFffi */
void daObjHha_c::set_tex(float frame, float speed, int idx) {
    mBtkA[idx].setFrame(frame);
    mBtkA[idx].setPlaySpeed(speed);
}

/* 00001A40-00001B00       .text init_mtx__10daObjHha_cFv */
void daObjHha_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(  current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::transM(mPosOffset);
    mDoMtx_stack_c::scaleM(1.0f, 1.0f, mWtrScale);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 00001B00-00001C64       .text init_co__10daObjHha_cFv */
void daObjHha_c::init_co() {
    const float yOffset = -400.0f, zOffset = -110.0f;
    cXyz center;

    mDoMtx_stack_c::YrotS(current.angle.y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &center);
    center *= 460.0f;
    center.y = get_water_h();
    center += current.pos;

    mCylStts.Init(0xff, 0xff, this);
    mCyl.SetStts(&mCylStts);
#if VERSION == VERSION_DEMO
    mCyl.Set(l_daObjHha_cyl_data);
#else
    mCyl.Set(M_cyl_data);
#endif
    mCyl.SetC(center);

#if VERSION > VERSION_DEMO
    bool doSphInit = false;
    if(!check_sw() && mIsMiddle == 0){
        doSphInit = true;
    }

    if(doSphInit){
        mSphStts.Init(0xff, 0xff, this);
        mSph.SetStts(&mSphStts);
        mSph.Set(M_sph_data);
        center.set(current.pos.x, current.pos.y + yOffset, current.pos.z + zOffset);
        mSph.SetC(center);
        mSph.SetR(220.0f);
    }
#endif
}

/* 00001C64-00001E14       .text get_water_h__10daObjHha_cFv */
float daObjHha_c::get_water_h() {
    dBgS_WtrChk waterChk;
    cXyz chkPos = current.pos;
    float ret = current.pos.y;

    cXyz offVec = cXyz::BaseZ;
    mDoMtx_stack_c::YrotS(current.angle.y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &offVec);
    offVec *= 400.0f;
    chkPos += offVec;
    if(dBgS_SplGrpChk_In_ObjGnd(chkPos, &waterChk, 1.0f) != false){
        ret = waterChk.GetHeight();
    }
    return ret;
}

/* 00001F38-00001F68       .text set_splash_bottom_h__10daObjHha_cFv */
void daObjHha_c::set_splash_bottom_h() {
    mSplashA[0].set_pos_y(get_water_h());
}

/* 00001F68-0000201C       .text daObjHha_get_r__Fs */
cXyz daObjHha_get_r(short yAngle) {
    cXyz calcVec = cXyz::BaseZ;
    float waterLevel = daTagWaterlevel::Act_c::get_now() * -190.0f;
    mDoMtx_stack_c::YrotS(yAngle);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &calcVec);
    calcVec *= waterLevel;
    return calcVec;
}

/* 0000201C-000020C0       .text set_splash_bottom_r__10daObjHha_cFv */
void daObjHha_c::set_splash_bottom_r() {
    cXyz pos = cXyz::BaseZ;
    pos = daObjHha_get_r(current.angle.y);
    pos += mSplashA[0].get_base_pos();
    pos.y = mSplashA[0].get_pos_y();
    mSplashA[0].set_pos(pos);
}

/* 000020C0-000021CC       .text set_splash_bottom_stop_r__10daObjHha_cFv */
void daObjHha_c::set_splash_bottom_stop_r() {
    cXyz calcVec = cXyz::BaseZ;
    float scaling = (1.0f - (mWtrTimer - 15) / 75.0f) * -300.0f;
    mDoMtx_stack_c::YrotS(current.angle.y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &calcVec);
    calcVec *= scaling;
    calcVec += mSplashA[0].get_pos();
    calcVec.y = mSplashA[0].get_pos_y();
    mSplashA[0].set_pos(calcVec);
}

/* 000021CC-00002470       .text water_manager__10daObjHha_cFv */
void daObjHha_c::water_manager() {
    set_splash_bottom_h();
    set_splash_bottom_r();
    switch(mWtrState){
        case 0:
        break;

        case 1:
            mWtrScale -= 11.0f/1800;
            if(mWtrScale < mWtrScaleMin){
                mWtrScale = mWtrScaleMin;
            }
            if(mWtrTimer == 34){
                set_tex(37.0f,1.0f,1);
            }
            if(mWtrTimer == 15){
                mSplashA[1].stop_particle();
                mSplashA[1].delete_s();
            }
            else if(mWtrTimer > 15){
                set_splash_bottom_stop_r();
            }
            mWtrTimer--;
            if(mWtrTimer == 0){
                mWtrState = 0;
                mSplashA[0].stop_particle();
                mSplashA[0].delete_s();
                mHitboxActive = false;
                mYgush.disp_off();
                mWaterSound = false;
            }
        break;

        case 2:
            if(mWtrTimer == 35){
                mSplashA[1].play_particle();
                set_tex(0.0f,1.0f,1);
            }
            mWtrTimer--;
            if( mSplashA[0].chk_stop() && mWtrTimer <= daTagWaterlevel::Act_c::get_now() * 5.0f + 10.0f){
                mSplashA[0].play_particle();
                mYgush.disp_on();
                mWaterSound = true;
            }
            if(mWtrTimer == 0){
                set_tex(36.0f, 0.0f, 1);
                mWtrState = 0;
                mHitboxActive = true;
            }
        break;
    }

    for(int i = 0; i < 2; i++){
        mBtkA[i].play();
    }
    init_mtx();
}

/* 00002470-0000259C       .text part_manager__10daObjHha_cFv */
void daObjHha_c::part_manager() {
    if(mPartTimer == 0){
        mPartA[0].start_move();
        mPartA[1].start_move();
        mPartTimer = -1;
        if(mIsMiddle == 0){
            fopAcM_seStartCurrent(this, JA_SE_OBJ_F_WATERGATE_CL, 0);
        }
    }
    else if(mPartTimer > 0)
        mPartTimer -= 1;

    for(int i = 0; i < 2; i++){
        mPartA[i].execute(this);
    }
}

/* 0000259C-00002658       .text ygush_manager__10daObjHha_cFv */
void daObjHha_c::ygush_manager() {
    cXyz ygushPos;
    if(mYgush.check_draw()){
        ygushPos = daObjHha_get_r(current.angle.y);
        ygushPos += mYgush.get_base_pos();
        ygushPos.y = get_water_h();
        mYgush.anm_play(ygushPos);
    }
}

/* 00002658-000028E4       .text _execute__10daObjHha_cFv */
bool daObjHha_c::_execute() {
    switch(mState){
        case State_OPEN: if(check_sw()){
            if(mIsMiddle == 0){
                if(eventInfo.mCommand != dEvtCmd_INDEMO_e){
                    fopAcM_orderOtherEventId(this, mEventIdx);
                    eventInfo.onCondition(2);
                }
                else {
                    mDoAud_seStart(JA_SE_READ_RIDDLE_1);
                    mWtrState = 1;
                    mWtrTimer = 90;
                    mPartTimer = 65;
                    mState = State_SWITCHING;
                }
            }
            else {
                if(dComIfGp_evmng_startCheck(mEventIdx) != FALSE){
                    mWtrState = 2;
                    mWtrTimer = 35;
                    mPartTimer = 0;
                    mState = State_CLOSED;
                }
            }
        } break;


        case State_SWITCHING: if(dComIfGp_evmng_endCheck(mEventIdx)){
                dComIfGp_event_reset();
                mState = State_CLOSED;
            }
        break;

        case State_CLOSED:
        break;
    }

    part_manager();
    water_manager();
    ygush_manager();

    if(mWaterSound != false)
        fopAcM_seStartCurrent(this, JA_SE_ATM_WATER_GATE,0);
    
    if(mHitboxActive != false){
        cXyz calcVec = mCyl.GetC();
        calcVec.y = get_water_h();
        mCyl.SetC(calcVec);
        dComIfG_Ccsp()->Set(&mCyl);
#if VERSION > VERSION_DEMO
        bool isSphActive = (!check_sw() && mIsMiddle == 0);
        if(isSphActive){
            dComIfG_Ccsp()->Set(&mSph);
        }
#endif
    }

    return TRUE;
}

/* 000028E4-000029F4       .text _draw__10daObjHha_cFv */
bool daObjHha_c::_draw() {
    int i;

    dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    for(i = 0; i < 2; i++){
        mPartA[i].draw(this);
    }

    if(mpModel != NULL){
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        dKy_getEnvlight().setLightTevColorType(mpModel, &tevStr);
        for(i = 0; i < 2; i++){
            mBtkA[i].entry(mpModel->getModelData());
        }
        mDoExt_modelUpdateDL(mpModel);
    }
    mYgush.draw();
    return TRUE;
}

namespace {
/* 000029F4-00002A14       .text Mthd_Create__25@unnamed@d_a_obj_hha_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return static_cast<daObjHha_c*>(i_this)->_create();
}

/* 00002A14-00002A38       .text Mthd_Delete__25@unnamed@d_a_obj_hha_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<daObjHha_c*>(i_this)->_delete();
}

/* 00002A38-00002A5C       .text Mthd_Execute__25@unnamed@d_a_obj_hha_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return static_cast<daObjHha_c*>(i_this)->_execute();
}

/* 00002A5C-00002A80       .text Mthd_Draw__25@unnamed@d_a_obj_hha_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return static_cast<daObjHha_c*>(i_this)->_draw();
}

/* 00002A80-00002A88       .text Mthd_IsDelete__25@unnamed@d_a_obj_hha_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return TRUE;
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
    /* Priority     */ PRIO_Obj_Hha,
    /* Actor SubMtd */ &Hha_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
