/**
 * d_a_oship.cpp
 * Enemy - Warship (Great Sea enemy ship)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_oship.h"
#include "d/actor/d_a_ship.h"
#include "d/res/res_oship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"

const s32 daOship_c::m_heapsize = 0x1280;

const char daOship_c::m_arc_name[] = "Oship";

const dCcD_SrcCyl daOship_c::m_cyl_src = {
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 75.0f,
        /* Height */ 115.0f,
    }},
};

static daOship_HIO_c l_HIO;

/* 000000EC-00000234       .text __ct__13daOship_HIO_cFv */
daOship_HIO_c::daOship_HIO_c() {
    field_0x04 = 0;
    field_0x06 = 0;
    field_0x05 = 0;
    field_0x07 = 0;
    field_0x08 = 0;
    mTrackOffsY = -0.04;
    mTrackScaleY = 4.0;
    mAttentionOffsY = 900.0;
    mEyeOffsY = 300.0;
    mWaveOffsZ = 380.0;
    mTrackOffsZ = 0.0;
    mDistRangeA = 2500.0;
    mDistRangeB = 6000.0;
    mDistRangeC = 12000.0;
    mAttackDelayA = 0x1e;
    mAttackDelayB = 200;
    mSplashScaleTimerTarget = 200.0;
    mSplashMaxScaleTimer = 300.0;
    mWaveVelFade1 = 2.0;
    mTrackVel = 300.0;
    mWaveVelSpeed = 2.0;
    mWaveMaxVelocity = 15.0;
    mWaveVelFadeOffs = 0.0;
    mWaveCollapsePos0.set(-80.0f, -50.0f, -150.0f);
    mWaveCollapsePos1.set(-40.0f, -100.0f, -350.0f);
    mBombOffset.set(450.0f, 0.0f, 0.0f);
    mBombSpeed = 85.0;
    mBombAcceleration = -2.0;
    mBombNoGravityTime = 0x23;
    mBadAimAdjustDistanceStart = 3500.0;
    mBadAimMax = 0x3000;
    field_0x8E = 0x3000;
    field_0x90 = 0x3500;
    mNode2RotZ = 0x2800;
    mPathSpeed = 20.0;
    mSpecScale = 0.75;
}

/* 000002B8-000002D8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daOship_c *)i_this)->_createHeap();
}

/* 000002D8-00000324       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daOship_c* this_p = (daOship_c *) model_p->getUserArea();
        if (this_p) {
            this_p->_nodeControl(i_nodeP, model_p);
        }
    }
    return true;
}

/* 00000324-00000410       .text _nodeControl__9daOship_cFP7J3DNodeP8J3DModel */
void daOship_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    J3DJoint* jnt_p = (J3DJoint *) i_nodeP;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jnt_no));
    csXyz aim_rot(0, 0, 0);

    switch (jnt_no) {
        case 1:
            aim_rot.x = mAimRotY;
            break;
        case 2:
            mDoMtx_stack_c::ZrotM(l_HIO.mNode2RotZ);
            aim_rot.z = -mAimRotX;
            break;
        default:
            break;
    }

    mDoMtx_stack_c::ZXYrotM(aim_rot.x, aim_rot.y, aim_rot.z);
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_modelP->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 0000044C-00000488       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
int pathMove_CB(cXyz* param_1, cXyz* param_2, cXyz* param_3, void* i_this) {
    return ((daOship_c *)i_this)->_pathMove(param_1, param_2, param_3);
}

/* 00000488-00000718       .text _pathMove__9daOship_cFP4cXyzP4cXyzP4cXyz */
int daOship_c::_pathMove(cXyz*, cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00000718-000007E4       .text pathMove__9daOship_cFv */
void daOship_c::pathMove() {
    /* Instruction match */
    cLib_addCalc2(&speedF, mVelocityFwdTarget, 0.1f, 2.0f);
    dLib_pathMove(&mOrigPos, &m2D4, mpPath, speedF, pathMove_CB, this);
    cLib_addCalcPosXZ2(&current.pos, mOrigPos, REG12_F(0) + 0.01f, speedF);
    
    if (speedF !=0.0f && mVelocityFwdTarget != 0.0f) {
        s16 target = cLib_targetAngleY(&current.pos, &mOrigPos);
        cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x100);
    }
}

/* 000007E4-000008A0       .text plFireRepeat__9daOship_cFv */
bool daOship_c::plFireRepeat() {
    if (dComIfGp_getShipActor() && dComIfGp_getShipActor()->checkShootCannon()) {
        mPlFireTimer = cM_rndF(20.0f) + 10.0f;
        mAimCounter++;
    }

    if (mPlFireTimer != -1 && cLib_calcTimer(&mPlFireTimer) == 0) {
        modeProcInit(1);
        mPlFireTimer = -1;
        return true;
    }

    return false;
}

/* 000008A0-000008F8       .text lineCheck__9daOship_cFP4cXyzP4cXyz */
BOOL daOship_c::lineCheck(cXyz* param_1, cXyz* param_2) {
    mLinChk.Set(param_1, param_2, this);
    return dComIfG_Bgsp()->LineCross(&mLinChk) ? true : false;
}

/* 000008F8-00000990       .text changeModeByRange__9daOship_cFv */
void daOship_c::changeModeByRange() {
    /* Nonmatching */
    f32 search_ac_dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
    int proc_no;

    if (search_ac_dist < l_HIO.mDistRangeA) {
        proc_no = 4;
    } else if (search_ac_dist < l_HIO.mDistRangeB) {
        proc_no = 5;
    } else if (search_ac_dist < l_HIO.mDistRangeC) {
        proc_no = 6;
    } else {
        proc_no = 7;
    }

    if (mCurrentProc != proc_no) {
        modeProcInit(proc_no);
    } 
}

/* 00000990-00000C08       .text createWave__9daOship_cFv */
void daOship_c::createWave() {
    /* Nonmatching */
}

/* 00000C08-00000E50       .text setWave__9daOship_cFv */
void daOship_c::setWave() {
    /* Nonmatching */
}

/* 00000E50-00001184       .text checkTgHit__9daOship_cFv */
void daOship_c::checkTgHit() {
    /* Nonmatching */
}

/* 00001184-000011F4       .text setAttention__9daOship_cFv */
void daOship_c::setAttention() {
    attention_info.position = current.pos;
    eyePos = current.pos;
    if (dComIfGp_event_runCheck() == FALSE) {
        attention_info.position.y += l_HIO.mAttentionOffsY;
        eyePos.y += l_HIO.mEyeOffsY;
    }
}

/* 000011F4-00001330       .text setCollision__9daOship_cFv */
void daOship_c::setCollision() {
    /* Nonmatching */
}

/* 00001330-000014D4       .text attackCannon__9daOship_cFi */
void daOship_c::attackCannon(int) {
    /* Nonmatching */
}

/* 000014D4-000017CC       .text setMtx__9daOship_cFv */
void daOship_c::setMtx() {
    /* Nonmatching */
}

/* 000017CC-000017EC       .text modeWaitInit__9daOship_cFv */
void daOship_c::modeWaitInit() {
    changeModeByRange();
}

/* 000017EC-0000180C       .text modeWait__9daOship_cFv */
void daOship_c::modeWait() {
    changeModeByRange();
}

/* 0000180C-00001820       .text modeRangeAInit__9daOship_cFv */
void daOship_c::modeRangeAInit() {
    mAttackTimer = l_HIO.mAttackDelayA;
}

/* 00001820-00001900       .text modeRangeA__9daOship_cFv */
void daOship_c::modeRangeA() {
    /* Nonmatching */
}

/* 00001900-00001934       .text modeRangeBInit__9daOship_cFv */
void daOship_c::modeRangeBInit() {
    /* Nonmatching */
    if (mSubMode == 0) {
        mAttackTimer = l_HIO.mAttackDelayA;
        return;
    }
    
    mAttackTimer = l_HIO.mAttackDelayB;
}

/* 00001934-00001A14       .text modeRangeB__9daOship_cFv */
void daOship_c::modeRangeB() {
    /* Nonmatching */
}

/* 00001A14-00001A28       .text modeRangeCInit__9daOship_cFv */
void daOship_c::modeRangeCInit() {
    mAttackTimer = l_HIO.mAttackDelayB;
}

/* 00001A28-00001AFC       .text modeRangeC__9daOship_cFv */
void daOship_c::modeRangeC() {
    /* Nonmatching */
}

/* 00001AFC-00001B00       .text modeRangeDInit__9daOship_cFv */
void daOship_c::modeRangeDInit() {
}

/* 00001B00-00001B7C       .text modeRangeD__9daOship_cFv */
void daOship_c::modeRangeD() {
    /* Nonmatching */
}

/* 00001B7C-00001B90       .text modeDamageInit__9daOship_cFv */
void daOship_c::modeDamageInit() {
    /* Nonmatching */
    mAttackTimer = 0x3C;
    mAttackSwayAmount = 0x12C;
}

/* 00001B90-00001C98       .text modeDamage__9daOship_cFv */
void daOship_c::modeDamage() {
    /* Nonmatching */
}

/* 00001C98-00001EC8       .text modeAttackInit__9daOship_cFv */
void daOship_c::modeAttackInit() {
    /* Nonmatching */
}

/* 00001EC8-00002044       .text modeAttack__9daOship_cFv */
void daOship_c::modeAttack() {
    /* Nonmatching */
}

/* 00002044-00002104       .text modeDeleteInit__9daOship_cFv */
void daOship_c::modeDeleteInit() {
    fopAcM_seStart(this, 0x6A19, 0);

    for (int i = 0; i < 3; i++) {
        mSmokeFollowCallback[i].end();
    }

    fopAcM_createDisappear(this, &current.pos, 5, daDisItem_IBALL_e);
}

/* 00002104-00002414       .text modeDelete__9daOship_cFv */
void daOship_c::modeDelete() {
    /* Nonmatching */
}

/* 00002414-0000263C       .text modeProc__9daOship_cFQ29daOship_c6Proc_ei */
void daOship_c::modeProc(daOship_c::Proc_e i_procType, int i_procNo) {
    /* Instruction match */
    static const ActorModeTable mode_tbl[8] = {
        { &daOship_c::modeWaitInit,   &daOship_c::modeWait  , "WAIT"   },
        { &daOship_c::modeAttackInit, &daOship_c::modeAttack, "ATTACK" },
        { &daOship_c::modeDamageInit, &daOship_c::modeDamage, "DAMAGE" },
        { &daOship_c::modeDeleteInit, &daOship_c::modeDelete, "DELETE" },
        { &daOship_c::modeRangeAInit, &daOship_c::modeRangeA, "RANGE_A" },
        { &daOship_c::modeRangeBInit, &daOship_c::modeRangeB, "RANGE_B" },
        { &daOship_c::modeRangeCInit, &daOship_c::modeRangeC, "RANGE_C" },
        { &daOship_c::modeRangeDInit, &daOship_c::modeRangeD, "RANGE_D" },
    };
    
    if (i_procType == PROC_INIT) {
        fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
        mCurrentProc = i_procNo;
        (this->*mode_tbl[mCurrentProc].mInitFunc)();
    } else if (i_procType == PROC_EXEC) {
        (this->*mode_tbl[mCurrentProc].mUpdFunc)();
    }
}

/* 0000263C-00002AD4       .text _execute__9daOship_cFv */
bool daOship_c::_execute() {
    /* Nonmatching */
}

/* 00002AD4-00002B54       .text _draw__9daOship_cFv */
bool daOship_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dDlst_texSpecmapST(&eyePos, &tevStr, mpModel->getModelData(), l_HIO.mSpecScale);
    mDoExt_modelEntryDL(mpModel);
    return true;
}

/* 00002B54-00002DFC       .text createInit__9daOship_cFv */
void daOship_c::createInit() {
    /* Instruction match */
    bool no_majuu_flag;
    itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Oship", 0);
    mOrigPos = current.pos;
    max_health = 3;
    health = max_health;
    mPlFireTimer = -1;
    changeModeByRange();
    attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 34;
    mStts.Init(0xFF, 0, this);

    for (int i = 0; i < 5; i++) {
        mCyl[i].Set(m_cyl_src);
        mCyl[i].SetStts(&mStts);
    }

    mWave.mAnimX = cM_rndF(32768.0f);
    mWave.mAnimZ = cM_rndF(32768.0f);

    setMtx();

    mpModel->calc();
    cullMtx = mpModel->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, -300.0f, -100.0f, -650.0f, 300.0f, 700.0f, 800.0f);
    fopAcM_setCullSizeFar(this, 10.0f);


    no_majuu_flag = mModelType != 0xFF || REG12_S(0) != 0;

    if (!no_majuu_flag) {
        mFlagPcId = fopAcM_create(PROC_MAJUU_FLAG, 4, &current.pos, tevStr.mRoomNo, &current.angle);
        static cXyz flag_offset = cXyz(0.0f, 800.0f, 0.0f);
        mFlagOffset = flag_offset;
    }

    if (mPathId != 0xFF) {
        mpPath = dPath_GetRoomPath(mPathId, fopAcM_GetRoomNo(this));
    }

    createWave();

    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);

    mAcch.SetWallNone();
    mAcch.SetRoofNone();
}

/* 00002DFC-00002F44       .text _createHeap__9daOship_cFv */
BOOL daOship_c::_createHeap() {
    /* Instruction match */
    bool load_vbtst;
    s32 file_index;

    file_index = OSHIP_BDL_VBTSP;
    load_vbtst = mModelType != 0xFF || REG12_S(0) != 0;

    if (load_vbtst) {
        file_index = OSHIP_BDL_VBTST;
    }

    J3DModelData* modelData = (J3DModelData *) dComIfG_getObjectRes(m_arc_name, file_index);
    JUT_ASSERT(0x625, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x37441422);

    if (!mpModel) {
        return FALSE;
    }

    mpModel->setUserArea((u32) this);
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        switch (i) {
            case 1:
            case 2:
                modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
                break;
            default:
                break;
        }
    }

    return TRUE;
}

/* 00002F44-00002F90       .text getArg__9daOship_cFv */
void daOship_c::getArg() {
    u32 prms = fopAcM_GetParam(this);

    mSubMode = prms & 0xFF;
    mTriforce = (prms >> 8) & 0xF;
    mRandomSalvagePoint = (prms >> 12) & 0xF;
    mPathId = (prms >> 16) & 0xFF;
    mSwitchA = (prms >> 24) & 0xFF;

    s16 home_angle_x = home.angle.x; // they were storing non-angle data in this?

    mSwitchB = home_angle_x & 0xFF;
    mModelType = (home_angle_x >> 8) & 0xFF;

    home.angle.x = 0;
    current.angle.x = 0;
    shape_angle.x = 0;
}

/* 00002F90-000030EC       .text _create__9daOship_cFv */
cPhs_State daOship_c::_create() {
    fopAcM_SetupActor(this, daOship_c);

    cPhs_State state = dComIfG_resLoad(&mPhs, m_arc_name);
    
    if (state == cPhs_COMPLEATE_e) {
        getArg();

        if (mSwitchA != 0xFF && dComIfGs_isSwitch(mSwitchA, fopAcM_GetRoomNo(this))) {
            return cPhs_ERROR_e;
        }

        if (mSwitchB != 0xFF && !dComIfGs_isSwitch(mSwitchB, fopAcM_GetRoomNo(this))) {
            return cPhs_ERROR_e;
        }

        if (mTriforce != 0xF) {
            if (!dComIfGs_isCollectMapTriforce(mTriforce + 1)) {
                return cPhs_ERROR_e;
            }
            if (mRandomSalvagePoint != 0xF && mRandomSalvagePoint != dComIfGs_getRandomSalvagePoint()) {
                return cPhs_ERROR_e;
            }
        }
        
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }

    return state;
}

/* 00003E78-00003F20       .text _delete__9daOship_cFv */
bool daOship_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);

    for (int i = 0; i < 3; i++) {
        mSmokeFollowCallback[i].end();
    }

    mWaveCallback2.remove();
    mWaveCallback1.remove();
    mSplashCallback.remove();
    mTrackCallback.remove();
    mDoAud_seDeleteObject(&mBombSpawnPos);
    
    return true;
}

/* 00003F20-00003F40       .text daOshipCreate__FPv */
static cPhs_State daOshipCreate(void* i_this) {
    return ((daOship_c*)i_this)->_create();
}

/* 00003F40-00003F64       .text daOshipDelete__FPv */
static BOOL daOshipDelete(void* i_this) {
    return ((daOship_c*)i_this)->_delete();
}

/* 00003F64-00003F88       .text daOshipExecute__FPv */
static BOOL daOshipExecute(void* i_this) {
    return ((daOship_c*)i_this)->_execute();
}

/* 00003F88-00003FAC       .text daOshipDraw__FPv */
static BOOL daOshipDraw(void* i_this) {
    return ((daOship_c*)i_this)->_draw();
}

/* 00003FAC-00003FB4       .text daOshipIsDelete__FPv */
static BOOL daOshipIsDelete(void*) {
    return TRUE;
}

static actor_method_class daOshipMethodTable = {
    (process_method_func)daOshipCreate,
    (process_method_func)daOshipDelete,
    (process_method_func)daOshipExecute,
    (process_method_func)daOshipIsDelete,
    (process_method_func)daOshipDraw,
};

actor_process_profile_definition g_profile_OSHIP = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OSHIP,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daOship_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OSHIP,
    /* Actor SubMtd */ &daOshipMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
