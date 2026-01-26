/**
 * d_a_bflower.cpp
 * Object - Bomb Flower - Flower
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bflower.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_vbakh.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_bomb2.h"

static cXyz bomb_offset(0.0f, 0.0f, 0.0f);

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WATER,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
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
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 50.0f,
        /* Height */ 10.0f,
    }},
};

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
    }},
};

static dCcD_SrcSph l_sph_src2 = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 15.0f,
    }},
};

const char daBFlower_c::m_arcname[] = "VbakH";

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daBFlower_c*>(i_this)->CreateHeap();
}

/* 0000010C-0000058C       .text CreateHeap__11daBFlower_cFv */
BOOL daBFlower_c::CreateHeap() {
    mState = daBFlower_prm::getKind(this);
    mSwitchNo = daBFlower_prm::getSwitchNo(this);

    if (fopAcM_isSwitch(this, mSwitchNo)) {
        mState = daBFlower_c::STATE_LIVE_E;
    }

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, VBAKH_BDL_VBAKH));
    JUT_ASSERT(0x1B2, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpModel == NULL) {
        return FALSE;
    }

    J3DAnmTransform* pbck = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_arcname, VBAKH_BCK_VBAHX));
    JUT_ASSERT(0x1C3, pbck != NULL);

    if (!mBck1.init(modelData, pbck, TRUE, J3DFrameCtrl::EMode_RESET, 1.0f, 0, -1, false)) {
        return FALSE;
    }
    mBck1.setFrame(mBck1.getEndFrame());

    J3DAnmTevRegKey* pbrk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arcname, VBAKH_BRK_VBAHX));
    JUT_ASSERT(0x1D9, pbrk != NULL);

    if (!mBrk1.init(modelData, pbrk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    mBrk1.setPlaySpeed(0.0f);

    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, VBAKH_BDL_VBAKM));
    JUT_ASSERT(0x1E7, modelData != NULL);

    mpModel2 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpModel2 == NULL) {
        return FALSE;
    }

    pbck = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_arcname, VBAKH_BCK_VBAMX));
    JUT_ASSERT(0x1F7, pbck != NULL);

    if (!mBck2.init(modelData, pbck, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
        return FALSE;
    }
    mBck2.setPlaySpeed(0.0f);

    pbrk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arcname, VBAKH_BRK_VBAMX));
    JUT_ASSERT(0x208, pbrk != NULL);

    if (!mBrk2.init(modelData, pbrk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    mBrk2.setPlaySpeed(0.0f);

    if (mState == daBFlower_c::STATE_LIVE_E) {
        mBrk1.setFrame(mBrk1.getEndFrame());
        mBrk2.setFrame(mBrk2.getEndFrame());
        mBck2.setFrame(mBck2.getEndFrame());

    } else if (mState == daBFlower_c::STATE_DEAD_e) {
        mBrk1.setFrame(0.0f);
        mBrk2.setFrame(0.0f);
        mBck2.setFrame(0.0f);
    }

    return TRUE;
}

/* 0000058C-00000750       .text CreateInit__11daBFlower_cFv */
void daBFlower_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

    fopAcM_setCullSizeBox(this, -50.0f, 0.0f, -50.0f, 50.0f, 100.0f, 50.0f);
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    if (mState == daBFlower_c::STATE_LIVE_E) {
        mSph.Set(l_sph_src);
    } else {
        mSph.Set(l_sph_src2);
    }
    mSph.SetStts(&mStts);

    current.angle = home.angle;
    set_mtx();
    eyePos.set(0.0f, 50.0f, 0.0f);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    mDoMtx_stack_c::multVec(&eyePos, &eyePos);
    attention_info.position = eyePos;

    if (current.angle.x == 0) {
        mGrabbable = FALSE;
    } else {
        mGrabbable = TRUE;
    }

    mpBombActor = NULL;
    m58C = 1;
    m5B8 = 0;
    mBombScale = scale;
    mAnimTimer = cM_rndF(150.0f) + 60.0f;
    m55C = -1;
}

/* 00000750-0000080C       .text init_bck_anm__11daBFlower_cFs */
int daBFlower_c::init_bck_anm(s16 param) {
    if (m55C != -1) {
        return 1;
    }

    m55C = param;

    J3DModelData* pModelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, VBAKH_BDL_VBAKH));
    J3DAnmTransform* pBck = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_arcname, param));

    return mBck1.init(pModelData, pBck, TRUE, J3DFrameCtrl::EMode_RESET, 1.0f, 0, -1, true);
}

/* 0000080C-000008AC       .text _create__11daBFlower_cFv */
cPhs_State daBFlower_c::_create() {
    fopAcM_SetupActor(this, daBFlower_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, m_arcname);

    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xFC0)) {
            return cPhs_ERROR_e;
        }

        CreateInit();
    }

    return phase_state;
}

/* 00000E94-00000F4C       .text set_mtx__11daBFlower_cFv */
void daBFlower_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    mpModel2->setBaseScale(mBombScale);
    mpModel2->setBaseTRMtx(mDoMtx_stack_c::get());
}

static daBFlower_c::ActionFunc action_tbl[] = {
    &daBFlower_c::actLive,
    &daBFlower_c::actDead,
};

/* 00000F4C-00001078       .text _execute__11daBFlower_cFv */
bool daBFlower_c::_execute() {
    daPy_py_c* player = daPy_getPlayerActorClass();

    (this->*action_tbl[mState])();

    animPlay();
    set_mtx();
    setCollision();

    f32 dist = (player->current.pos - current.pos).absXZ();

    mPrevPlayerDist = dist;
    mPrevGrabActorID = player->getGrabActorID();

    return TRUE;
}

/* 00001078-0000160C       .text actLive__11daBFlower_cFv */
BOOL daBFlower_c::actLive() {
    daPy_py_c* player = daPy_getPlayerActorClass();

    f32 dist = (player->current.pos - current.pos).absXZ();

    cLib_addCalc(&mBombScale.x, 1.0f, 0.05f, 0.1f, 0.05f);
    cLib_addCalc(&mBombScale.y, 1.0f, 0.05f, 0.1f, 0.05f);
    f32 tmp = cLib_addCalc(&mBombScale.z, 1.0f, 0.05f, 0.1f, 0.05f);

    if (m5B8 != 0 && tmp == 0.0f) {
        init_bck_anm(VBAKH_BCK_VBAKH);
    }

    // Play animation if player walks by bomb flower
    if (dist < 50.0f && std::abs(mPrevPlayerDist - dist) > 2.0f && std::abs(player->current.pos.y - current.pos.y) < 10.0f) {
        init_bck_anm(VBAKH_BCK_VBAKH);
    }

    // Play animation if player dropped held actor near bomb flower?
    if (dist < 200.0f && mPrevGrabActorID != player->getGrabActorID() && player->getGrabActorID() == fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* pActor = fopAcM_SearchByID(mPrevGrabActorID);

        if (pActor != NULL) {
            if ((pActor->current.pos - current.pos).absXZ() < 70.0f) {
                init_bck_anm(VBAKH_BCK_VBAKH);
            }
        }
    }

    mBrk2.play();

    if (mBck2.play()) {
        m58D = 1;
    }

    if (mGrabbable == TRUE) {
        m58D = 0;
    }

    if (fopAcM_IsExecuting(fopAcM_GetID(mpBombActor))) {
        m58D = 0;
    } else {
        if (m58C == 0) {
            mBombScale.setall(0.0f);
            fopAcM_seStart(this, JA_SE_OBJ_BAKURETU_RECOVER, 0);
        }
        m58C = 1;
    }

    if (m58D != 0) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    } else {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    }

    if (m58C != 0 && tmp == 0.0f) {
        if (mSph.ChkTgHit()) {
            cCcD_Obj* tg = mSph.GetTgHitObj();
            if (tg != NULL) {
                if (tg->ChkAtType(AT_TYPE_BOMB)) {
                    mpBombActor = static_cast<fopAc_ac_c*>(fopAcM_fastCreate(PROC_Bomb2, daBomb2::Act_c::prm_make(daBomb2::Start_UNK0_e, true), &current.pos, fopAcM_GetRoomNo(this), &current.angle));
                    m58C = 0;
                } else if (tg->ChkAtType(~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT))) {
                    // TODO: simplify
                    bool b = false;
                    if (mGrabbable == TRUE) {
                        b = true;
                    }
                    u32 prm = daBomb2::Act_c::prm_make(daBomb2::Start_UNK1_e, b);

                    mpBombActor = static_cast<fopAc_ac_c*>(fopAcM_fastCreate(PROC_Bomb2, prm, &current.pos, fopAcM_GetRoomNo(this), &current.angle));
                    m58C = 0;
                }
            }
        }

        mSph.ClrTgHit();
    }

    if (fopAcM_checkCarryNow(this) && m58D != 0) {
        m58C = 0;
        mpBombActor = static_cast<fopAc_ac_c*>(fopAcM_fastCreate(PROC_Bomb2, daBomb2::Act_c::prm_make(daBomb2::Start_UNK2_e, false), &current.pos, fopAcM_GetRoomNo(this), &current.angle));

        fopAcM_cancelCarryNow(this);
        if (mpBombActor != NULL) {
            fopAcM_setCarryNow(mpBombActor, FALSE);
            daPy_getPlayerLinkActorClass()->exchangeGrabActor(mpBombActor);
        }

        init_bck_anm(VBAKH_BCK_VBAKH);
    }

    if (m58C != 0 && tmp > 0.0f) {
        m5B8 = 1;
    } else {
        m5B8 = 0;
    }

    return TRUE;
}

/* 0000160C-0000185C       .text actDead__11daBFlower_cFv */
BOOL daBFlower_c::actDead() {
    daPy_py_c* player = daPy_getPlayerActorClass();

    f32 dist = (player->current.pos - current.pos).absXZ();

    if (mAnimTimer > 0) {
        mAnimTimer -= 1;
    }

    // Play animation if player walks by bomb flower
    if (dist < 50.0f && std::abs(mPrevPlayerDist - dist) > 2.0f) {
        init_bck_anm(VBAKH_BCK_VBAHX);
    }

    if (mAnimTimer == 0) {
        mAnimTimer = cM_rndF(100.0f) + 100.0f;
        init_bck_anm(VBAKH_BCK_VBAHX);
    }

    mBrk1.setPlaySpeed(0.0f);

    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj != NULL && hitObj->ChkAtType(AT_TYPE_WATER)) {
            fopAcM_seStart(this, JA_SE_OBJ_W_BOMB_F_RECOVER, 0);
            m594 = 0x46;
            mState = daBFlower_c::STATE_LIVE_E;
            fopAcM_onSwitch(this, mSwitchNo);

            init_bck_anm(VBAKH_BCK_VBAKH);
            mBrk1.setPlaySpeed(1.0f);
            mBrk2.setPlaySpeed(1.0f);
            mBck2.setPlaySpeed(1.0f);

            mSph.Set(l_sph_src);
        }
    }

    m58D = 0;
    m58C = 1;
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

    return TRUE;
}

/* 0000185C-000018A4       .text animPlay__11daBFlower_cFv */
void daBFlower_c::animPlay() {
    if (mBck1.play()) {
        m55C = -1;
    }

    mBrk1.play();
}

/* 000018A4-000019AC       .text setCollision__11daBFlower_cFv */
void daBFlower_c::setCollision() {
    if (mState == daBFlower_c::STATE_DEAD_e) {
        mCyl.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
        mSph.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mSph);
    } else if (m58C != 0) {
        cXyz center(0.0f, 30.0f, 0.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(current.angle);
        mDoMtx_stack_c::multVec(&center, &center);

        mSph.SetC(center);
        dComIfG_Ccsp()->Set(&mSph);
    }
}

/* 000019AC-00001AC4       .text _draw__11daBFlower_cFv */
bool daBFlower_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    mBck1.entry(mpModel->getModelData());
    mBrk1.entry(mpModel->getModelData());
    mDoExt_modelUpdateDL(mpModel);

    mBck1.remove(mpModel->getModelData());

    if (m58C != 0) {
        g_env_light.setLightTevColorType(mpModel2, &tevStr);

        mBck2.entry(mpModel2->getModelData());
        mBrk2.entry(mpModel2->getModelData());
        mDoExt_modelUpdateDL(mpModel2);

        mBck2.remove(mpModel2->getModelData());
    }

    return TRUE;
}

bool daBFlower_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arcname);
    return TRUE;
}

/* 00001AC4-00001AE4       .text daBFlower_Create__FPv */
static cPhs_State daBFlower_Create(void* i_this) {
    return static_cast<daBFlower_c*>(i_this)->_create();
}

/* 00001AE4-00001B14       .text daBFlower_Delete__FPv */
static BOOL daBFlower_Delete(void* i_this) {
    return static_cast<daBFlower_c*>(i_this)->_delete();
}

/* 00001B14-00001B38       .text daBFlower_Draw__FPv */
static BOOL daBFlower_Draw(void* i_this) {
    return static_cast<daBFlower_c*>(i_this)->_draw();
}

/* 00001B38-00001B5C       .text daBFlower_Execute__FPv */
static BOOL daBFlower_Execute(void* i_this) {
    return static_cast<daBFlower_c*>(i_this)->_execute();
}

/* 00001B5C-00001B64       .text daBFlower_IsDelete__FPv */
static BOOL daBFlower_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daBFlowerMethodTable = {
    (process_method_func)daBFlower_Create,
    (process_method_func)daBFlower_Delete,
    (process_method_func)daBFlower_Execute,
    (process_method_func)daBFlower_IsDelete,
    (process_method_func)daBFlower_Draw,
};

actor_process_profile_definition g_profile_BOMB_FLOWER = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BOMB_FLOWER,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBFlower_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BOMB_FLOWER,
    /* Actor SubMtd */ &daBFlowerMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
