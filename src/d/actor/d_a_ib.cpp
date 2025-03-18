//
// Generated by dtk
// Translation Unit: d_a_ib.cpp
//

#include "d/actor/d_a_ib.h"
#include "d/d_procname.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_item.h"
#include "d/d_item.h"
#include "d/d_item_data.h"
#include "global.h"
#include "m_Do/m_Do_mtx.h"

#include "weak_data_1811.h" // IWYU pragma: keep

struct daIball_c__data {
    /* 0x00 */ u8 m00;
    /* 0x01 */ u8 m01;
    /* 0x02 */ u8 m02;
    /* 0x03 */ u8 m03;
    /* 0x04 */ f32 mPlaySpeeds[4];
    /* 0x14 */ f32 mBounceSpeedMult;
    /* 0x18 */ f32 mGravity;
    /* 0x1C */ f32 mYOffset;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ s16 mMoveDelay;
    /* 0x2C */ f32 mSpeedF;
    /* 0x30 */ f32 mSpeedY;
    /* 0x34 */ f32 mRandSpeedF;
    /* 0x38 */ s16 m38;
    /* 0x3A */ s16 m3A;
};

const daIball_c__data m_data = {
    /* m00              */ 1,
    /* m01              */ 2,
    /* m02              */ 4,
    /* m03              */ 5,
    /* mPlaySpeeds      */ {1.0f, 2.0f, 4.0f, 8.0f},
    /* mBounceSpeedMult */ 0.5f,
    /* mGravity         */ -7.0f,
    /* mYOffset         */ 40.0f,
    /* m20              */ 0.5f,
    /* m24              */ 0.75f,
    /* mMoveDelay       */ 32,
    /* mSpeedF          */ 10.0f,
    /* mSpeedY          */ 53.0f,
    /* mRandSpeedF      */ 4.0f,
    /* m38              */ 80,
    /* m3A              */ 60,
};

/* 800F3228-800F3380       .text setPointLight__9daIball_cFv */
void daIball_c::setPointLight() {
    static const s16 light_color[3][3] = {
        {800, 120, 400},
        {120, 400, 600},
        {600, 600, 200},
    };
    int color_idx;
    f32 frame = mBrkAnm[0].getFrame();
    if (frame >= 0.0f && frame < 45.0f) {
        color_idx = 0;
    } else if (frame >= 45.0f && frame < 90.0f) {
        color_idx = 1;
    } else if (frame >= 90.0f && frame <= 135.0f) {
        color_idx = 2;
    }
    cLib_addCalc2(&mLightFlickerMult, 1.0f + cM_rndF(0.2f), 0.5f, 0.02f);
    mLight.mPos = current.pos;
    mLight.mColor.r = light_color[color_idx][0];
    mLight.mColor.g = light_color[color_idx][1];
    mLight.mColor.b = light_color[color_idx][2];
    s16 power = (80.0f + REG12_F(0)) * mLightFlickerMult;
    mLight.mPower = power;
    mLight.mFluctuation = 250.0f;
}

/* 800F3380-800F3608       .text createDisappearEffect__9daIball_cFii */
void daIball_c::createDisappearEffect(int param_1, int color_idx) {
    cXyz scale;
    scale.setall(1.0f);
    cXyz pos(current.pos);
    pos.y += m_data.mYOffset;
    switch (param_1) {
    case 0:
        dComIfGp_particle_set(dPa_name::ID_COMMON_001C, &pos, NULL, &scale, 0xFF, dPa_control_c::getLifeBallSetColorEcallBack(color_idx));
        dComIfGp_particle_set(dPa_name::ID_COMMON_001D, &pos, NULL, &scale);
        if (color_idx == 2) {
            dComIfGp_particle_set(dPa_name::ID_COMMON_0047, &pos);
        }
        fopAcM_seStartCurrent(this, JA_SE_OBJ_CUT_INOCHIDAMA, 0);
        break;
    case 1:
        dComIfGp_particle_set(dPa_name::ID_COMMON_0019, &pos, NULL, &scale);
        dComIfGp_particle_set(dPa_name::ID_COMMON_001A, &pos, NULL, &scale);
        dComIfGp_particle_set(dPa_name::ID_COMMON_001B, &pos, NULL, &scale);
        fopAcM_seStartCurrent(this, JA_SE_CM_INOCHIDAMA_BREAK, 0);
        break;
    }
}

/* 800F3608-800F3658       .text itemParamSet_CB__FPv */
static BOOL itemParamSet_CB(void* i_actor) {
    daItem_c* item = static_cast<daItem_c*>(i_actor);
    if (item && !isEmono(item->getItemNo())) {
        item->setItemTimerForIball(3*30, 2*30);
    }
    return TRUE;
}

/* 800F3658-800F3994       .text createItem__9daIball_cFv */
BOOL daIball_c::createItem() {
    // Fakematch: itemBitNo and itemTableIdx should really be separate variables as they aren't
    // related, but we need r27 to be used for both of them in order for the regalloc to match.
    int itemBitNo = daIball_prm::getAdId(this);
    int itemTableIdx = itemBitNo;
    u32 items[8];
    
    items[0] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM0(), itemTableIdx);
    items[1] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM1(), itemTableIdx);
    items[2] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM2(), itemTableIdx);
    items[3] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM3(), itemTableIdx);
    items[4] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM4(), itemTableIdx);
    items[5] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM5(), itemTableIdx);
    items[6] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM6(), itemTableIdx);
    items[7] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->GetITEM7(), itemTableIdx);
    
    for (int i = 0; i < 8; i++) {
        itemBitNo = -1;
        if (isLimitedItem(items[i])) {
            itemBitNo = daIball_prm::getItemBitNo(this);
            if ((itemBitNo == 0x1F || itemBitNo == 0xFF || itemBitNo == -1) || fopAcM_isItemForIb(itemBitNo, items[i], current.roomNo)) {
                itemBitNo = -1;
                items[i] = dItem_YELLOW_RUPEE_e;
            }
        } else if (isNonSavedEmono(items[i])) {
            if (daIball_prm::getItemBitNo(this) != 0) {
                items[i] = dItem_YELLOW_RUPEE_e;
            }
            itemBitNo = -1;
        }
        
        cXyz scale = cXyz::Zero;
        csXyz angle = csXyz::Zero;
        
        f32 speed_f = 1.0f;
        if (cM_rndFX(1.0f) < 0.0f) {
            speed_f = -1.0f;
        }
        speed_f = speed_f*m_data.mSpeedF + cM_rndFX(m_data.mRandSpeedF);
        
        angle.y = (s16)cM_rndF((f32)0x7FFF);
        
        items[i] = getItemNoByLife(items[i]);
        
        s8 roomNo = current.roomNo;
        fopAcM_fastCreateItem(
            &current.pos, items[i], roomNo, &angle, &scale,
            speed_f, m_data.mSpeedY + cM_rndF(10.0f), -6.0f, itemBitNo, itemParamSet_CB
        );
    }
    
    dead();
    
    return TRUE;
}

/* 800F3994-800F3A48       .text dead__9daIball_cFv */
BOOL daIball_c::dead() {
    int color_idx;
    f32 frame = mBrkAnm[0].getFrame();
    if (frame >= 0.0f && frame < 45.0f) {
        color_idx = 0;
    } else if (frame >= 45.0f && frame < 90.0f) {
        color_idx = 1;
    } else if (frame >= 90.0f && frame <= 135.0f) {
        color_idx = 2;
    }
    createDisappearEffect(0, color_idx);
    fopAcM_delete(this);
    return TRUE;
}

/* 800F3A48-800F3E78       .text checkGeo__9daIball_cFv */
void daIball_c::checkGeo() {
    static ModeFunc mode_proc[] = {
        &daIball_c::mode_wait,
        &daIball_c::mode_water,
    };
    
    mPrevSpeedY = speed.y;
    if (mTimer > m_data.mMoveDelay) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    mAcch.CrrPos(*dComIfG_Bgsp());
    
    (this->*mode_proc[mMode])();
    
    dBgS_ObjGndChk_Yogan lavaChk;
    cXyz pos(current.pos.x, old.pos.y + 30.0f + m_data.mYOffset, current.pos.z);
    lavaChk.SetPos(&pos);
    f32 lavaY = dComIfG_Bgsp()->GroundCross(&lavaChk);
    f32 groundH = mAcch.GetGroundH();
    if (lavaY != C_BG_MIN_HEIGHT) {
        f32 lava_depth = lavaY - groundH;
        if ((lava_depth < 20.0f && lavaY > current.pos.y) || (lava_depth >= 20.0f && lavaY > current.pos.y + 20.0f)) {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_FALL_MAGMA_S, 0);
            cXyz particle_scale;
            particle_scale.setall(0.25f);
            cXyz particle_pos(current.pos);
            particle_pos.y = lavaY;
            dComIfGp_particle_set(dPa_name::ID_SCENE_80D5, &particle_pos, NULL, &particle_scale);
            fopAcM_delete(this);
        }
    }
}

/* 800F3E78-800F3EB0       .text mode_wait_init__9daIball_cFv */
void daIball_c::mode_wait_init() {
    mRippleCb.end();
    mMode = MODE_WAIT;
}

/* 800F3EB0-800F3F6C       .text mode_wait__9daIball_cFv */
void daIball_c::mode_wait() {
    if (mAcch.ChkGroundLanding()) {
        mPrevSpeedY *= m_data.mBounceSpeedMult;
        if (mPrevSpeedY > gravity - 0.5f) {
            speedF = 0.0f;
        } else {
            speed.set(0.0f, -mPrevSpeedY, 0.0f);
        }
    }
    
    f32 seaHeight = mAcch.GetSeaHeight();
    if (seaHeight > current.pos.y && seaHeight != C_BG_MIN_HEIGHT) {
        mode_water_init();
        current.pos.y = seaHeight;
    }
}

/* 800F3F6C-800F3FE8       .text mode_water_init__9daIball_cFv */
void daIball_c::mode_water_init() {
    dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &current.pos, NULL, &scale, 0xFF, &mRippleCb);
    mRippleCb.setRate(0.0f);
    mMode = MODE_WATER;
}

/* 800F3FE8-800F4054       .text mode_water__9daIball_cFv */
void daIball_c::mode_water() {
    f32 seaHeight = mAcch.GetSeaHeight();
    if (seaHeight == C_BG_MIN_HEIGHT || seaHeight < current.pos.y) {
        mode_wait_init();
    }
    if (seaHeight != C_BG_MIN_HEIGHT) {
        current.pos.y = seaHeight;
    }
}

/* 800F4054-800F418C       .text animControl__9daIball_cFv */
void daIball_c::animControl() {
    BOOL isEventRun = FALSE;
    if (dComIfGp_event_runCheck()) {
        isEventRun = TRUE;
    }
    
    mBrkAnm[0].setPlaySpeed(m_data.mPlaySpeeds[mPlaySpeedIdx]);
    mBrkAnm[0].play();
    BOOL isLoop = mBrkAnm[0].isLoop();
    mBrkAnm[1].setPlaySpeed(1.0f);
    mBrkAnm[1].play();
    mBtkAnm.setPlaySpeed(1.0f);
    mBtkAnm.play();
    mBckAnm.play();
    
    if (!isEventRun) {
        f32 frame = mBrkAnm[0].getFrame();
        f32 prevFrame = frame - mBrkAnm[0].getPlaySpeed();
        if (isLoop ||
            (frame >= 45.0f && prevFrame < 45.0f) ||
            (frame >= 90.0f && prevFrame < 90.0f))
        {
            fopAcM_seStartCurrent(this, JA_SE_CM_INOCHIDAMA_BLINK, 0);
        }
    }
}

/* 800F418C-800F4250       .text damage__9daIball_cFv */
void daIball_c::damage() {
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj) {
            if (hitObj->ChkAtType(AT_TYPE_SWORD)         || hitObj->ChkAtType(AT_TYPE_BOKO_STICK)   ||
                hitObj->ChkAtType(AT_TYPE_MACHETE)       || hitObj->ChkAtType(AT_TYPE_SKULL_HAMMER) ||
                hitObj->ChkAtType(AT_TYPE_UNK2000000)    || hitObj->ChkAtType(AT_TYPE_STALFOS_MACE) ||
                hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD) || hitObj->ChkAtType(AT_TYPE_HOOKSHOT)     ||
                hitObj->ChkAtType(AT_TYPE_BOOMERANG)     || hitObj->ChkAtType(AT_TYPE_NORMAL_ARROW) ||
                hitObj->ChkAtType(AT_TYPE_FIRE_ARROW)    || hitObj->ChkAtType(AT_TYPE_ICE_ARROW)    ||
                hitObj->ChkAtType(AT_TYPE_LIGHT_ARROW)   || hitObj->ChkAtType(AT_TYPE_MOBLIN_SPEAR)
            ) {
                createItem();
            }
        }
    }
}

/* 800F4250-800F42E8       .text set_mtx__9daIball_cFv */
void daIball_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m_data.mYOffset, current.pos.z);
    mDoMtx_stack_c::XYZrotM(current.angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 800F42E8-800F441C       .text CreateInit__9daIball_cFv */
void daIball_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);
    mAcch.OnSeaCheckOn();
    mAcch.OnSeaWaterHeight();
    
    mbPlayedSe = false;
    gravity = m_data.mGravity;
    mMode = MODE_WAIT;
    current.pos.y -= m_data.mYOffset;
    
    mBckAnm.entry(mpModel->getModelData());
    
    set_mtx();
    
    mpModel->calc();
    dKy_plight_set(&mLight);
    setPointLight();
    
    mLightFlickerMult = 1.0f;
    regist(this);
}

/* 800F441C-800F4544       .text _daIball_draw__9daIball_cFv */
BOOL daIball_c::_daIball_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    
    for (int i = 0; i < (int)ARRAY_SIZE(mBrkAnm); i++) {
        mBrkAnm[i].entry(mpModel->getModelData());
    }
    mBtkAnm.entry(mpModel->getModelData());
    mBckAnm.entry(mpModel->getModelData());
    
    dComIfGd_setListMaskOff();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    
    dComIfGd_setSimpleShadow2(
        &current.pos, mAcch.GetGroundH(), 30.0f, mAcch.m_gnd,
        0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
    
    return TRUE;
}

/* 800F4544-800F4634       .text _daIball_execute__9daIball_cFv */
BOOL daIball_c::_daIball_execute() {
    eyePos = current.pos;
    eyePos.y = current.pos.y + 45.0f;
    
    mTimer++;
    
    setPointLight();
    
    if (!mbPlayedSe) {
        fopAcM_seStartCurrent(this, JA_SE_CM_INOCHIDAMA, 0);
        mbPlayedSe = true;
    }
    
    checkGeo();
    animControl();
    damage();
    set_mtx();
    
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
    
    return TRUE;
}

/* 800F4634-800F4678       .text _daIball_delete__9daIball_cFv */
BOOL daIball_c::_daIball_delete() {
    mRippleCb.end();
    dKy_plight_cut(&mLight);
    remove(this);
    return TRUE;
}

/* 800F4678-800F4698       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daIball_c*>(i_this)->CreateHeap();
}

/* 800F4698-800F4870       .text _daIball_create__9daIball_cFv */
cPhs_State daIball_c::_daIball_create() {
    fopAcM_SetupActor(this, daIball_c);
    
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x3500)) {
        return cPhs_ERROR_e;
    }
    
    CreateInit();
    
    return cPhs_COMPLEATE_e;
}

/* 800F489C-800F4B40       .text CreateHeap__9daIball_cFv */
BOOL daIball_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, ALWAYS_BDL_IB);
    JUT_ASSERT(1135, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
    if (!mpModel) { return FALSE; }
    
    J3DAnmTransform* pbck = (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, ALWAYS_BCK_START);
    JUT_ASSERT(1152, pbck != NULL);
    int ret = mBckAnm.init(modelData, pbck, 1, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);
    if (!ret) { return FALSE; }
    
    J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arcname, ALWAYS_BTK_IB);
    JUT_ASSERT(1164, pbtk != NULL);
    ret = mBtkAnm.init(modelData, pbtk, 1, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (!ret) { return FALSE; }
    
    int brkIds[ARRAY_SIZE(mBrkAnm)] = {
        ALWAYS_BRK_IB_01,
        ALWAYS_BRK_IB_02,
    };
    J3DAnmTevRegKey* pbrk;
    for (int i = 0; i < (int)ARRAY_SIZE(mBrkAnm); i++) {
        pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(m_arcname, brkIds[i]);
        JUT_ASSERT(1182, pbrk != NULL);
        ret = mBrkAnm[i].init(modelData, pbrk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
        if (!ret) { return FALSE; }
    }
    
    return TRUE;
}

/* 800F4B40-800F4B60       .text daIball_Create__FP10fopAc_ac_c */
static cPhs_State daIball_Create(fopAc_ac_c* i_this) {
    return static_cast<daIball_c*>(i_this)->_daIball_create();
}

/* 800F4B60-800F4B80       .text daIball_Draw__FP9daIball_c */
static BOOL daIball_Draw(daIball_c* i_this) {
    return i_this->_daIball_draw();
}

/* 800F4B80-800F4BA0       .text daIball_Delete__FP9daIball_c */
static BOOL daIball_Delete(daIball_c* i_this) {
    return i_this->_daIball_delete();
}

/* 800F4BA0-800F4BA8       .text daIball_IsDelete__FP9daIball_c */
static BOOL daIball_IsDelete(daIball_c* i_this) {
    return TRUE;
}

/* 800F4BA8-800F4BC8       .text daIball_Execute__FP9daIball_c */
static BOOL daIball_Execute(daIball_c* i_this) {
    return i_this->_daIball_execute();
}

// This symbol needs to go in .data, but as it's only 7 bytes long, it would normally go in .sdata or .sdata2.
// But if the array doesn't have a size specified in its declaration, and its definition comes *after* it gets used,
// that forces it into .data instead because the size is unknown when it's used. Even const is ignored.
const char daIball_c::m_arcname[] = "Always";

dCcD_SrcCyl daIball_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_StopNoConHit_e,
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};

static actor_method_class l_daIball_Method = {
    (process_method_func)daIball_Create,
    (process_method_func)daIball_Delete,
    (process_method_func)daIball_Execute,
    (process_method_func)daIball_IsDelete,
    (process_method_func)daIball_Draw,
};

actor_process_profile_definition g_profile_Iball = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Iball,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daIball_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0187,
    /* Actor SubMtd */ &l_daIball_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
