/**
 * d_a_nh.cpp
 * Forest Firely / 森のほたる (Mori no Hotaru)
 */

#include "d/actor/d_a_nh.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/actor/d_a_player.h"
#include "d/d_item_data.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/JUtility/JUTAssert.h"

static daNh_HIO_c l_HIO;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK8 | CO_SPRM_VS_UNK2,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_HIT_MARK,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 10.0f,
        /* Height */ 20.0f,
    },
};

/* 800F95B8-800F9654       .text __ct__10daNh_HIO_cFv */
daNh_HIO_c::daNh_HIO_c() {
    mChildID = -1;
    static const hio_prm_c init_data = {
        /* field_0x08         */ 200.0f,
        /* field_0x0c         */ 100.0f,
        /* field_0x10         */ -50.0f,
        /* mGlowOffsetY       */ 140.0f,
        /* mGlowScale         */ 0.95f,
        /* mMinFrightenSpeed  */ 5.0f,
        /* mHeightAboveGround */ 50.0f,
        /* mAscentSpeed       */ 1.0f,
        /* mDescentSpeed      */ -1.0f,
        /* mGravity           */ 0.25f,
        /* mMaxHomeDist       */ 250.0f,
        /* field_0x34         */ 600.0f,
        /* mModelScale        */ 2.5f,
        /* field_0x3c         */ 0x2000,
        /* mDefaultGlowAlpha  */ 0x20,
        /* mBottleLifetime    */ 10*30,
    };
    prm = init_data;
}

/* 800F9654-800F9874       .text __dt__6daNh_cFv */
daNh_c::~daNh_c() {
    if (l_HIO.mChildID >= 0) {
        mDoHIO_root.mDoHIO_deleteChild(l_HIO.mChildID);
        l_HIO.mChildID = -1;
    }
}

/* 800F9874-800F9980       .text setBaseMtx__6daNh_cFv */
void daNh_c::setBaseMtx() {
    J3DModel* model = mpModel;
    scale.setall(l_HIO.prm.mModelScale);
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    
    cXyz glowOffset;
    glowOffset.z = 0.0f;
    glowOffset.x = 0.0f;
    glowOffset.y = l_HIO.prm.mGlowOffsetY;
    cXyz glowPos;
    cMtx_multVec(mDoMtx_stack_c::get(), &glowOffset, &glowPos);
    mDoMtx_stack_c::transS(glowPos);
    mDoMtx_stack_c::scaleM(l_HIO.prm.mGlowScale, l_HIO.prm.mGlowScale, l_HIO.prm.mGlowScale);
    cMtx_copy(mDoMtx_stack_c::get(), mGlowMtx);
}

/* 800F9980-800F9A54       .text createHeap__6daNh_cFv */
BOOL daNh_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Always", ALWAYS_BDL_NH);
    JUT_ASSERT(359, modelData != NULL);
    
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (!mpModel) {
        return FALSE;
    }
    if (!initBrkAnm(false)) {
        return FALSE;
    }
    return TRUE;
}

/* 800F9A54-800F9A74       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_this) {
    return ((daNh_c*)i_this)->createHeap();
}

/* 800F9A74-800F9C8C       .text create__6daNh_cFv */
s32 daNh_c::create() {
    static u32 a_heap_size_tbl = 0x4000;
    
    s32 phase_state = cPhs_COMPLEATE_e;
    
    fopAcM_SetupActor(this, daNh_c);
    
    if (!fopAcM_entrySolidHeap(this, checkCreateHeap, a_heap_size_tbl)) {
        return cPhs_ERROR_e;
    }
    
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    
    if (l_HIO.mChildID < 0) {
        l_HIO.mChildID = mDoHIO_root.mDoHIO_createChild("森のほたる", &l_HIO); // "Forest Firefly" (mori no hotaru)
        l_HIO.mpActor = this;
    }
    if (!init()) {
        phase_state = cPhs_ERROR_e;
    }
    
    return phase_state;
}

/* 800F9C8C-800F9D64       .text init__6daNh_cFv */
BOOL daNh_c::init() {
    mType = fopAcM_GetParam(this) & 0xFF;
    speed.y = 1.0f;
    gravity = l_HIO.prm.mGravity;
    mGlowAlpha = l_HIO.prm.mDefaultGlowAlpha;
    mPlayerDist = 0.0f;
    mAlpha = 0xFF;
    mBottleTimer = l_HIO.prm.mBottleLifetime;
    mGroundY = 0.0f;
    
    BGCheck();
    
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    
    setBaseMtx();
    eyePos = attention_info.position = current.pos;
    
    return TRUE;
}

/* 800F9D64-800F9DF4       .text action__6daNh_cFPv */
void daNh_c::action(void* arg) {
    if (mCurrActionFunc == NULL) {
        speedF = 0.0f;
        setAction(&daNh_c::waitAction, NULL);
    }
    (this->*mCurrActionFunc)(arg);
}

/* 800F9DF4-800F9EB8       .text setAction__6daNh_cFM6daNh_cFPCvPvPv_iPv */
BOOL daNh_c::setAction(ActionFunc actionFunc, void* arg) {
    if (mCurrActionFunc != actionFunc) {
        if (mCurrActionFunc != NULL) {
            mActionStatus = ACTION_ENDING;
            (this->*mCurrActionFunc)(arg);
        }
        mCurrActionFunc = actionFunc;
        mActionStatus = ACTION_STARTING;
        mEscapeTimer = 0;
        unk696 = 0;
        unk698 = 0;
        unk69A = 0;
        unk6A0 = 0.0f;
        (this->*mCurrActionFunc)(arg);
    }
    return TRUE;
}

/* 800F9EB8-800F9F3C       .text checkBinCatch__6daNh_cFv */
BOOL daNh_c::checkBinCatch() {
    if (eventInfo.checkCommandCatch()) {
        fopAcM_delete(this);
        return TRUE;
    }
    
    dComIfGp_getAttention().CatchRequest(
        this, FIREFLY_BOTTLE,
        l_HIO.prm.field_0x08, l_HIO.prm.field_0x0c,
        l_HIO.prm.field_0x10, l_HIO.prm.field_0x3c,
        1
    );
    eventInfo.onCondition(dEvtCnd_CANCATCH_e);
    
    return FALSE;
}

/* 800F9F3C-800FA108       .text searchPlayer__6daNh_cFv */
BOOL daNh_c::searchPlayer() {
    if (isTypeBottle()) {
        setAction(&daNh_c::escapeAction, NULL);
        return TRUE;
    }
    
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz playerDelta = player->old.pos - player->current.pos;
    f32 playerDist = fopAcM_searchPlayerDistance(this);
    f32 playerDistDelta = mPlayerDist - playerDist;
    mPlayerDist = playerDist;
    if (playerDelta.absXZ() > 0.001f && playerDist < 600.0f && playerDistDelta > l_HIO.prm.mMinFrightenSpeed) {
        // Player is nearby and moving closer. The Forest Firefly becomes frightened and tries to escape.
        setAction(&daNh_c::escapeAction, NULL);
        return TRUE;
    }
    
    return FALSE;
}

/* 800FA108-800FA19C       .text moveProc__6daNh_cFffs */
BOOL daNh_c::moveProc(f32 targetSpeed, f32 speedStep, s16 targetAngle) {
    cLib_chaseAngleS(&current.angle.y, targetAngle, 0x400);
    shape_angle.y = current.angle.y;
    if (cLib_chaseF(&speedF, targetSpeed, speedStep) && targetSpeed == 0.0f) {
        return TRUE;
    }
    return FALSE;
}

/* 800FA19C-800FA260       .text getHomeDistance__6daNh_cFv */
f32 daNh_c::getHomeDistance() {
    cXyz delta = home.pos - current.pos;
    return cXyz(delta.x, 0.0f, delta.z).abs();
}

/* 800FA260-800FA2E4       .text checkTimer__6daNh_cFv */
BOOL daNh_c::checkTimer() {
    // Count down after being released from a bottle.
    if (isTypeBottle() && cLib_calcTimer(&mBottleTimer) == 0) {
        // Timer finished, start fading out.
        mAlpha -= 4;
        if (mAlpha < 0) {
            mAlpha = 0;
        }
        if (mAlpha == 0) {
            fopAcM_delete(this);
            return TRUE;
        }
    }
    return FALSE;
}

/* 800FA2E4-800FA568       .text BGCheck__6daNh_cFv */
void daNh_c::BGCheck() {
    dBgS_ObjGndChk_All gndChk;
    gndChk.SetPos(&current.pos);
    f32 groundY = dComIfG_Bgsp()->GroundCross(&gndChk);
    if (groundY != -1000000000.0f) {
        mGroundY = groundY;
        tevStr.mRoomNo = current.roomNo = dComIfG_Bgsp()->GetRoomId(gndChk);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(gndChk);
    }
}

/* 800FA568-800FA5B4       .text airMove__6daNh_cFv */
void daNh_c::airMove() {
    f32 idealY = mGroundY + l_HIO.prm.mHeightAboveGround;
    if (current.pos.y < idealY - 10.0f) {
        maxFallSpeed = l_HIO.prm.mAscentSpeed;
    } else if (current.pos.y > idealY + 10.0f) {
        maxFallSpeed = l_HIO.prm.mDescentSpeed;
    }
}

/* 800FA5B4-800FA674       .text waitAction__6daNh_cFPv */
BOOL daNh_c::waitAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus += 1; // ACTION_ONGOING
        mPlayerDist = fopAcM_searchPlayerDistance(this);
    } else if (mActionStatus != ACTION_ENDING) {
        cLib_addCalc(&speedF, 0.0f, 0.1f, 10.0f, 1.0f);
        if (getHomeDistance() > 50.0f) {
            setAction(&daNh_c::returnAction, NULL);
        }
    }
    return TRUE;
}

/* 800FA674-800FA78C       .text checkEscapeEnd__6daNh_cFv */
BOOL daNh_c::checkEscapeEnd() {
    cXyz homeDelta = home.pos - current.pos;
    if (!isTypeBottle()) {
        if (cLib_calcTimer(&mEscapeTimer) == 0) {
            setAction(&daNh_c::waitAction, NULL);
            return TRUE;
        }
        if (homeDelta.abs2XZ() > l_HIO.prm.mMaxHomeDist*l_HIO.prm.mMaxHomeDist) {
            setAction(&daNh_c::returnAction, NULL);
            return TRUE;
        }
    }
    return FALSE;
}

/* 800FA78C-800FA880       .text escapeAction__6daNh_cFPv */
BOOL daNh_c::escapeAction(void*) {
    // Run away after being released from a bottle.
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus += 1; // ACTION_ONGOING
        mWobbleDir = 0;
        mWobbleTimer = 0;
        mEscapeTimer = 5*30;
    } else if (mActionStatus != ACTION_ENDING) {
        if (!checkEscapeEnd()) {
            s16 targetAngle = fopAcM_searchPlayerAngleY(this) + 0x8000;
            if (cLib_calcTimer(&mWobbleTimer) == 0) {
                mWobbleDir ^= 1;
                mWobbleTimer = cLib_getRndValue(15, 20);
            }
            targetAngle += mWobbleDir ? -0x2000 : 0x2000;
            moveProc(5.0f, 0.5f, targetAngle);
        }
    }
    return TRUE;
}

/* 800FA880-800FAA34       .text returnAction__6daNh_cFPv */
BOOL daNh_c::returnAction(void*) {
    // Try to head in the direction of home (the Forest Firefly's spawn position).
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus += 1; // ACTION_ONGOING
        mWobbleDir = 0;
        mWobbleTimer = 0;
        mEscapeTimer = 5*30;
    } else if (mActionStatus != ACTION_ENDING) {
        if (getHomeDistance() < 50.0f) {
            setAction(&daNh_c::waitAction, NULL);
        } else {
            s16 targetAngle = cLib_targetAngleY(&current.pos, &home.pos);
            cXyz homeDelta = home.pos - current.pos;
            if (homeDelta.abs2XZ() < l_HIO.prm.mMaxHomeDist*l_HIO.prm.mMaxHomeDist) {
                s16 angle = targetAngle - fopAcM_searchPlayerAngleY(this);
                if (abs(angle) < 0x1000) {
                    if (angle < 0) {
                        targetAngle -= 0x4000;
                    } else {
                        targetAngle += 0x4000;
                    }
                }
            }
            if (cLib_calcTimer(&mWobbleTimer) == 0) {
                mWobbleDir ^= 1;
                mWobbleTimer = cLib_getRndValue(15, 20);
            }
            targetAngle += mWobbleDir ? -0x2000 : 0x2000;
            moveProc(5.0f, 0.5f, targetAngle);
        }
    }
    return TRUE;
}

/* 800FAA34-800FABE0       .text execute__6daNh_cFv */
BOOL daNh_c::execute() {
    playBrkAnm();
    
    mGlowAlpha = l_HIO.prm.mDefaultGlowAlpha;
    
    if (maxFallSpeed < speed.y) {
        speed.y -= gravity;
        if (speed.y < maxFallSpeed) {
            speed.y = maxFallSpeed;
        }
    } else if (maxFallSpeed > speed.y) {
        speed.y += gravity;
        if (speed.y > maxFallSpeed) {
            speed.y = maxFallSpeed;
        }
    }
    
    speed.x = speedF * cM_ssin(current.angle.y);
    speed.z = speedF * cM_scos(current.angle.y);
    
    fopAcM_posMove(this, mStts.GetCCMoveP());
    
    BGCheck();
    
    cXyz pos = current.pos;
    pos.y -= 10.0f;
    mCyl.SetC(pos);
    dComIfG_Ccsp()->Set(&mCyl);
    
    checkTimer();
    
    if (!checkBinCatch()) {
        airMove();
        searchPlayer();
        action(NULL);
    }
    
    setBaseMtx();
    eyePos = attention_info.position = current.pos;
    
    return TRUE;
}

/* 800FABE0-800FACC4       .text initBrkAnm__6daNh_cFb */
BOOL daNh_c::initBrkAnm(bool i_modify) {
    J3DModelData* modelData = mpModel->getModelData();
    bool success = false;
    
    J3DAnmTevRegKey* a_brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Always", ALWAYS_BRK_TNH);
    JUT_ASSERT(883, a_brk != NULL);
    
    if (mBrkAnm.init(modelData, a_brk, true, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, i_modify, false)) {
        success = true;
    }
    return success;
}

/* 800FACC4-800FACE8       .text playBrkAnm__6daNh_cFv */
void daNh_c::playBrkAnm() {
    mBrkAnm.play();
}

/* 800FACE8-800FAE1C       .text draw__6daNh_cFv */
BOOL daNh_c::draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    
    J3DModelData* modelData = mpModel->getModelData();
    
    mBrkAnm.entry(modelData);
    mDoExt_modelUpdateDL(mpModel);
    modelData->getMaterialTable().removeTevRegAnimator(mBrkAnm.getBrkAnm());
    
    J3DMaterial* mat = modelData->getMaterialNodePointer(0);
    if (mat) {
        J3DTevBlock* tevBlock = mat->getTevBlock();
        if (tevBlock) {
            GXColorS10* color = &tevBlock->getTevColor(1)->mColor;
            if (color) {
                mGlowAlpha = ((color->r + color->g + color->b) / 3) >> 2;
            }
            
            GXColor* kColor = &tevBlock->getTevKColor(3)->mColor;
            if (kColor) {
                kColor->a = mAlpha;
            }
        }
    }
    
    dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_SPHERE, mGlowMtx, mGlowAlpha);
    
    return TRUE;
}

/* 800FAE1C-800FAE3C       .text daNh_Draw__FP6daNh_c */
static BOOL daNh_Draw(daNh_c* i_this) {
    return i_this->draw();
}

/* 800FAE3C-800FAE5C       .text daNh_Execute__FP6daNh_c */
static BOOL daNh_Execute(daNh_c* i_this) {
    return i_this->execute();
}

/* 800FAE5C-800FAE64       .text daNh_IsDelete__FP6daNh_c */
static BOOL daNh_IsDelete(daNh_c* i_this) {
    return TRUE;
}

/* 800FAE64-800FAE8C       .text daNh_Delete__FP6daNh_c */
static BOOL daNh_Delete(daNh_c* i_this) {
    i_this->~daNh_c();
    return TRUE;
}

/* 800FAE8C-800FAEAC       .text daNh_Create__FP10fopAc_ac_c */
static s32 daNh_Create(fopAc_ac_c* i_this) {
    return ((daNh_c*)i_this)->create();
}

static actor_method_class l_daNh_Method = {
    (process_method_func)daNh_Create,
    (process_method_func)daNh_Delete,
    (process_method_func)daNh_Execute,
    (process_method_func)daNh_IsDelete,
    (process_method_func)daNh_Draw,
};

actor_process_profile_definition g_profile_NH = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NH,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNh_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x013C,
    /* Actor SubMtd */ &l_daNh_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
