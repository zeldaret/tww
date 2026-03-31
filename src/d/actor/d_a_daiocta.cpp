/**
 * d_a_daiocta.cpp
 * Mini-Boss - Big Octo (body)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_daiocta.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_daiocta_eye.h"
#include "d/actor/d_a_obj_auzu.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_ship.h"
#include "d/d_cc_d.h"
#include "d/d_jnt_hit.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_daiocta.h"

static daDaiocta_HIO_c l_HIO;

const s32 daDaiocta_c::m_heapsize = 63296; 
const char daDaiocta_c::m_arc_name[] = "daiocta";

const dCcD_SrcSph daDaiocta_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};


const dCcD_SrcCps daDaiocta_c::m_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};


/* 000000EC-000002B0       .text __ct__15daDaiocta_HIO_cFv */
daDaiocta_HIO_c::daDaiocta_HIO_c() {
    m004 = 0;
    m008 = 0;
    m006 = 0;
    m005 = 0;

    mSphRadii[0] = 600.0f;
    mSphRadii[1] = 500.0f;
    mSphRadii[2] = 450.0f;
    mSphRadii[3] = 350.0f;
    mSphRadii[4] = 350.0f;
    mSphRadii[5] = 300.0f;

    mCpsRadii[0] = 60.0f;
    mCpsRadii[1] = 60.0f;
    mCpsRadii[2] = 60.0f;
    mCpsRadii[3] = 60.0f;
    mCpsRadii[4] = 60.0f;
    mCpsRadii[5] = 60.0f;
    mCpsRadii[6] = 60.0f;
    mCpsRadii[7] = 60.0f;
    mCpsRadii[8] = 60.0f;
    mCpsRadii[9] = 60.0f;

    m05C = 100.0f;
    m060 = 100.0f;
    m064 = 250.0f;
    m068 = 100.0f;
    m06C = 150.0f;
    m070 = 100.0f;
    m074 = 150.0f;
    mRotEyeTimerMin = 0x1E;
    mRotEyeTimerAddMax = 0x3C;
    mDefaultAppearRadius = 5000.0f;
    mMinAppearRadius = 4500.0f;
    m080 = 30.0f;
    m010 = 0x100;
    m084 = 1800.0f;
    m012 = 0x1500;
    m088 = 40.0f;
    m08C = 1.0f;
    m090 = 0.02f;
    m094 = 150.0f;
    m014 = -0x800;

    m0FC.set(0.0f, 5.0f, 700.0f);

    m0BC[1] = 8.0f;
    m0BC[2] = 8.0f;
    m0BC[3] = 3.0f;
    m0BC[4] = 3.0f;
    m0BC[5] = 3.0f;
    m0BC[6] = 7.0f;
    m0BC[7] = 9.0f;

    m098[1] = 1.0f;
    m098[2] = 0.5f;
    m098[3] = 0.75f;
    m098[4] = 0.625f;
    m098[5] = 0.625f;
    m098[6] = 0.5f;
    m098[7] = 1.0f;
    m098[8] = 1.0f;

    m0E0 = 20.0f;
    m016 = 0x1E;
    m0E4 = 300.0f;
    m0E8 = 1200.0f;
    m0EC = 1.0f;
    m0F0 = 2.0f;
    m0F4 = 10.0f;
    m0F8 = 30.0f;
    m018 = 0x2D;
}

/* 00000334-00000358       .text coHit_CB__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
static void coHit_CB(fopAc_ac_c* i_this, dCcD_GObjInf*, fopAc_ac_c* i_actor, dCcD_GObjInf*) {
    ((daDaiocta_c*)i_this)->_coHit(i_actor);
}

/* 00000358-000003DC       .text _coHit__11daDaiocta_cFP10fopAc_ac_c */
void daDaiocta_c::_coHit(fopAc_ac_c* i_actor) {
    if (i_actor != NULL && fpcM_GetName(i_actor) == PROC_BOMB) {
        daBomb_c* bomb_p = (daBomb_c *) i_actor;
        if ((mMode == MODE_WAIT || mMode == MODE_DAMAGE_BOMB || 
            mMode == MODE_APPEAR || mMode == MODE_DAMAGE) && 
            bomb_p->chk_state(daBomb_c::STATE_4)) {
            modeProc(PROC_INIT_e, MODE_DAMAGE_BOMB);
        }
    }
}

/* 000003DC-00000470       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daDaiocta_c* daiocta = (daDaiocta_c *) model_p->getUserArea();
        JUT_ASSERT(420, daiocta != NULL);
        daiocta->_nodeControl(i_nodeP, model_p);
    }
    return TRUE;
}

/* 00000470-0000066C       .text _nodeControl__11daDaiocta_cFP7J3DNodeP8J3DModel */
void daDaiocta_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    J3DJoint* jnt_p = (J3DJoint *) i_nodeP;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jnt_no));
    mDoMtx_stack_c::multVecZero(&mSphCenters[jnt_no]);

    cXyz base;
    switch (jnt_no) {
        case 30:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m21A0);
            break;
        case 36:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m21AC);
            break;
        case 20:
            base.set(l_HIO.m094, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m2434);
            break;
        case 6:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m21B8);
            break;
        case 9:
            base.set(300.0f, -200.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m21C4);
            break; 
        case 7:
            base.set(300.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m21D0);
            break;
        case 10:
            base.set(300.0f, 200.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m21DC);
            break;
        case 8:
            base.set(300.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &m21E8);
            break;
    }

    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_modelP->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 0000066C-0000068C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daDaiocta_c *)i_this)->_createHeap();
}

/* 0000068C-00000708       .text _createHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::_createHeap() {
    if (!createBodyHeap()) {
        return FALSE;
    }

    if (!createSuikomiHeap()) {
        return FALSE;
    }

    if (!createAwaHeap()) {
        return FALSE;
    }

    if (!createArrowHitHeap()) {
        return FALSE;
    }

    return true;
}

/* 00000708-000009B8       .text createAwaHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::createAwaHeap() {  
    J3DModelData* modelData;
    J3DAnmTransform* bck;
    J3DAnmTextureSRTKey* btk;
    J3DAnmTevRegKey* brk;

    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BDL_GAWA00));
    JUT_ASSERT(516, modelData != NULL);

    bck = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BCK_GAWA00));
    JUT_ASSERT(520, bck != NULL);

    btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BTK_GAWA00));
    JUT_ASSERT(524, btk != NULL);

    brk = static_cast<J3DAnmTevRegKey *>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BRK_GAWA00));
    JUT_ASSERT(528, brk != NULL);


    for (int i = 0; i < ARRAY_SSIZE(mpAwaModels); i++) {
        // "awa" translates to bubbles
        mpAwaModels[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
        if (mpAwaModels[i] == NULL) {
            return FALSE;
        }

        if (!mAwaBckAnms[i].init(modelData, bck, TRUE, 
                                J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
            return FALSE;
        }

        if (!mAwaBtkAnms[i].init(modelData, btk, TRUE, 
                                J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }

        if (!mAwaBrkAnms[i].init(modelData, brk, TRUE, 
                                J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }
    }

    return TRUE;
}

/* 000009B8-00000ABC       .text createSuikomiHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::createSuikomiHeap() {
    J3DModelData* modelData = (J3DModelData * ) dComIfG_getObjectRes(m_arc_name, DAIOCTA_BDL_GDO_SUI00);
    JUT_ASSERT(551, modelData != NULL);

    // "suikomi" translates to suction
    mpSuikomiModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);

    if (!mpSuikomiModel) {
        return FALSE;
    }

    if (!dLib_brkInit(modelData, &mBrkAnm2, m_arc_name, DAIOCTA_BRK_GDO_SUI00) || 
        !dLib_btkInit(modelData, &mBtkAnm, m_arc_name, DAIOCTA_BTK_GDO_SUI00)) {
        return FALSE;
    }

    return TRUE;
}

/* 00000ABC-00000C04       .text createBodyHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::createBodyHeap() {
    J3DModelData* modelData = (J3DModelData *) dComIfG_getObjectRes(m_arc_name, DAIOCTA_BDL_DO_MAIN1);
    JUT_ASSERT(579, modelData != NULL);

    if (!dLib_brkInit(modelData, &mBrkAnm1, m_arc_name, DAIOCTA_BRK_WAIT1)) {
        return FALSE;
    }

    mpMorf = new mDoExt_McaMorf(
        modelData, 
        NULL, NULL, NULL, 
        ~J3DFrameCtrl::EMode_NONE, 
        1.0f, 0, -1, 1, NULL, 
        0x80000, 0x11000222
    );


    if (!mpMorf || !mpMorf->getModel()) {
        return FALSE;
    }

    mpMorf->getModel()->setUserArea((u32) this);

    return TRUE;
}

/* 00000C04-00000C64       .text createArrowHitHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::createArrowHitHeap() {
    static Vec ude_cyl_offset[] = {
        {   0.0f, 0.0f, 0.0f },
        { 400.0f, 0.0f, 0.0f }
    };

    static Vec te_cyl_offset[] = {
        {   0.0f, 10.0f, 0.0f },
        { 450.0f, 10.0f, 0.0f }
    };

    static Vec body_cyl_offset[] = {
        { -200.0f, 0.0f, 0.0f },
        {  200.0f, 0.0f, 0.0f }
    };

    static Vec body_top_cyl_offset[] = {
        { -200.0f, 0.0f, 0.0f },
        {  400.0f, 0.0f, 0.0f }
    };

    static Vec hire_cyl_offset[] = {
        { -200.0f, 0.0f, 0.0f },
        {  250.0f, 0.0f, 0.0f }
    };
    
    static __jnt_hit_data_c search_data[17] = { 
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 2,
            /* mRadius     */ 550.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 3,
            /* mRadius     */ 450.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 4,
            /* mRadius     */ 400.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 5,
            /* mRadius     */ 300.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 6,
            /* mRadius     */ 200.0f,
            /* mpOffsets   */ body_top_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 7,
            /* mRadius     */ 150.0f,
            /* mpOffsets   */ body_top_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 8,
            /* mRadius     */ 150.0f,
            /* mpOffsets   */ body_top_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 9,
            /* mRadius     */ 100.0f,
            /* mpOffsets   */ hire_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 10,
            /* mRadius     */ 100.0f,
            /* mpOffsets   */ hire_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 30,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ te_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 29,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 28,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 27,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 36,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ te_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 35,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ te_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 34,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 33,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        }
    };

    mpJntHit = JntHit_create(
        mpMorf->getModel(), search_data, 
        ARRAY_SSIZE(search_data)
    );

    if (!mpJntHit) {
        return FALSE;
    }

    jntHit = mpJntHit;

    return TRUE;
}

/* 00000C64-00000D94       .text setMtx__11daDaiocta_cFv */
void daDaiocta_c::setMtx() {
    for (int i = 0; i < ARRAY_SSIZE(mEyeAlloc); i++) {
        fopAc_ac_c* actor_p;
        if (mEyeAlloc[i] && fopAcM_SearchByID(mDaioctaEyePcId[i], &actor_p)) {
            Mtx mtx;
            mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(mAnmMtxIndices[i]));
            mDoMtx_stack_c::multVecZero(&actor_p->current.pos);
            cMtx_inverseTranspose(mDoMtx_stack_c::get(), mtx);
            mDoMtx_MtxToRot(mtx, &actor_p->shape_angle);
        }
    }

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    setSuikomiMtx();
    setAwaMtx();
}

/* 00000D94-00000E2C       .text setSuikomiMtx__11daDaiocta_cFv */
void daDaiocta_c::setSuikomiMtx() {
    cXyz pos = current.pos;
    pos.y = mWaterY;
    mDoMtx_stack_c::transS(pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::transM(l_HIO.m0FC);
    mpSuikomiModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000E2C-00000EDC       .text setAwaMtx__11daDaiocta_cFv */
void daDaiocta_c::setAwaMtx() {
    for (int i = 0; i < l_HIO.m016; i++) {
        mpAwaModels[i]->setBaseScale(mAwaScale[i]);
        mDoMtx_stack_c::transS(mAwaTranslation[i]);
        mpAwaModels[i]->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 00000EDC-00000F70       .text initMtx__11daDaiocta_cFv */
void daDaiocta_c::initMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mpSuikomiModel->setBaseScale(scale);
    setMtx();
    mpMorf->getModel()->calc();
    mpSuikomiModel->calc();
}

/* 00000F70-0000116C       .text setEffect__11daDaiocta_cFUs */
void daDaiocta_c::setEffect(u16 effect_name) {
    GXColor sea_color_ambient;
    GXColor sea_color_diffuse; // unused
    cXyz particle_pos;

    dKy_get_seacolor(&sea_color_ambient, &sea_color_diffuse);
    s32 r = sea_color_ambient.r + l_HIO.m018;
    s32 g = sea_color_ambient.g + l_HIO.m018;
    s32 b = sea_color_ambient.b + l_HIO.m018;

    if (r >= 0xFF) r = 0xFF;
    if (g >= 0xFF) g = 0xFF;
    if (b >= 0xFF) b = 0xFF; 

    sea_color_ambient.r = r;
    sea_color_ambient.g = g;
    sea_color_ambient.b = b;

    particle_pos = current.pos;
    particle_pos.y = mWaterY;
    csXyz particle_angle(shape_angle);

    switch (effect_name) {
        case dPa_name::ID_IT_SN_DO_APPSHIBUKI00:
#if VERSION > VERSION_DEMO
            if (!mParticleCallback.getEmitter()) {
                dComIfGp_particle_set(
                    effect_name, &particle_pos, 
                    NULL, NULL, 0xFF, &mParticleCallback, 
                    -1, &sea_color_ambient
                );
            }
#else
            mpEmitter = dComIfGp_particle_set(
                effect_name, &particle_pos, 
                NULL, NULL, 0xFF, NULL, -1, 
                &sea_color_ambient
            );
#endif
            break;
        case dPa_name::ID_IT_SN_DO_HITA_SHIBUKIA00:
        case dPa_name::ID_IT_SN_DO_HITA_SHIBUKIB00:
        case dPa_name::ID_IT_SN_DO_HITB_SHIBUKIA00:
        case dPa_name::ID_IT_SN_DO_HITB_SHIBUKIB00:
        case dPa_name::ID_IT_SN_DO_HITC_SHIBUKIA00:
        case dPa_name::ID_IT_SN_DO_HITC_SHIBUKIB00:
        case dPa_name::ID_IT_SN_DO_DOWNSHIBUKI00:
            dComIfGp_particle_set(
                effect_name, &particle_pos, NULL, NULL, 
                0xFF, NULL, -1, &sea_color_ambient
            );
            break;
        case dPa_name::ID_IT_SN_DO_SUIKOMIA00:
        case dPa_name::ID_IT_SN_DO_SUIKOMIB00:
        case dPa_name::ID_IT_SN_DO_SUIKOMIC00:
        case dPa_name::ID_IT_SN_DO_HAKIDASHI00:
            dComIfGp_particle_set(
                effect_name, &particle_pos, &particle_angle, NULL, 
                0xFF, NULL, -1, &sea_color_ambient
            );
            break;
        default:
            break;
    }
}

/* 0000116C-0000129C       .text setAwaRandom__11daDaiocta_cFi */
void daDaiocta_c::setAwaRandom(int i_awaIndex) {
#if VERSION > VERSION_DEMO
    f32 f31, f30, f29, f29_2;
    f30 = l_HIO.m0EC;
    f31 = l_HIO.m0E4;
    f29 = l_HIO.m0E8 - f31;
    mAwaScale[i_awaIndex].setall(f30 + cM_rndF(l_HIO.m0F0 - f30));

    f29_2 = f31 + cM_rndF(f29);
#else
    f32 f31, f1, f30, f29, f29_2;
    f31 = l_HIO.m0EC;
    f1 = l_HIO.m0F0 - f31;
    
    f30 = l_HIO.m0E4;
    f29 = l_HIO.m0E8 - f30;
    mAwaScale[i_awaIndex].setall(f31 + cM_rndF(f1));

    f29_2 = f30 + cM_rndF(f29);
#endif

    s16 random_theta = cM_rndF(65536.0f);

    mAwaTranslation[i_awaIndex].x = current.pos.x + f29_2 * cM_ssin(random_theta);
    mAwaTranslation[i_awaIndex].y = mWaterY;
    mAwaTranslation[i_awaIndex].z = current.pos.z + f29_2 * cM_scos(random_theta);
}

/* 0000129C-000013D8       .text initAwa__11daDaiocta_cFv */
void daDaiocta_c::initAwa() {
    for (int i = 0; i < l_HIO.m016; i++) {
        setAwaRandom(i);
        f32 tmp = l_HIO.m0F4;
        f32 tmp2 = cM_rndF(l_HIO.m0F8 - l_HIO.m0F4);
        mAwaTimers[i] = tmp + tmp2;
        mAwaBckAnms[i].setFrame(mAwaBckAnms[i].getEndFrame());
        mAwaBtkAnms[i].setFrame(mAwaBtkAnms[i].getEndFrame());
        mAwaBrkAnms[i].setFrame(mAwaBrkAnms[i].getEndFrame());
    }
}

/* 000013D8-00001548       .text execAwa__11daDaiocta_cFv */
void daDaiocta_c::execAwa() {
    for (int i = 0; i < l_HIO.m016; i++) {
        if (cLib_calcTimer<int>(&mAwaTimers[i]) == 0) {
            mAwaBckAnms[i].play();
            mAwaBtkAnms[i].play();
            mAwaBrkAnms[i].play();
            if (m31C4 || l_HIO.m008) {
                if (mAwaBckAnms[i].isStop()) {
                    mAwaBckAnms[i].setFrame(0.0f);
                    mAwaBckAnms[i].setPlaySpeed(1.0f);

                    mAwaBtkAnms[i].setFrame(0.0f);
                    mAwaBtkAnms[i].setPlaySpeed(1.0f);

                    mAwaBrkAnms[i].setFrame(0.0f);
                    mAwaBrkAnms[i].setPlaySpeed(1.0f);
                    
                    f32 fVar1 = l_HIO.m0F4;
                    mAwaTimers[i] = fVar1 + cM_rndF(l_HIO.m0F8 - fVar1);
                    setAwaRandom(i);
                }
            }
        }
    }
}

/* 00001548-000015E8       .text isLivingEye__11daDaiocta_cFv */
bool daDaiocta_c::isLivingEye() {
    bool is_alive = false;
    for (int i = 0; i < ARRAY_SSIZE(mDaioctaEyePcId); i++) {
        if (mEyeAlloc[i] == true) {
            daDaiocta_Eye_c* big_octo_eye_p = (daDaiocta_Eye_c *) fopAcM_SearchByID(mDaioctaEyePcId[i]);
            if (!big_octo_eye_p) {
                mEyeAlloc[i] = false;
            } else if (big_octo_eye_p->mbIsDead == false) {
                is_alive = true;
            }
        }
    }
    return is_alive;
}

/* 000015E8-00001684       .text isDead__11daDaiocta_cFv */
bool daDaiocta_c::isDead() {
    int count = 0;
    for (int i = 0; i < ARRAY_SSIZE(mEyeAlloc); i++) {
        if (mEyeAlloc[i] == true) {
            daDaiocta_Eye_c* big_octo_eye_p = (daDaiocta_Eye_c *) fopAcM_SearchByID(mDaioctaEyePcId[i]);
            if (big_octo_eye_p && big_octo_eye_p->mbIsDead == 0) {
                count++;
            }
        }
    }

    if (count == 0) {
        return true;
    }

    return false;
}

/* 00001684-0000171C       .text isDamageEye__11daDaiocta_cFv */
bool daDaiocta_c::isDamageEye() {
    bool is_damaged = false;
    for (int i = 0; i < ARRAY_SSIZE(mDaioctaEyePcId); i++) {
        if (mEyeAlloc[i] == true) {
            daDaiocta_Eye_c* big_octo_eye_p = (daDaiocta_Eye_c *) fopAcM_SearchByID(mDaioctaEyePcId[i]);
            if (big_octo_eye_p && big_octo_eye_p->mbIsDamaged) {
                is_damaged = true;
            }
        }
    }
    return is_damaged;
}

/* 0000171C-000017B4       .text isDamageBombEye__11daDaiocta_cFv */
bool daDaiocta_c::isDamageBombEye() {
    bool is_damaged = false;
    for (int i = 0; i < ARRAY_SSIZE(mDaioctaEyePcId); i++) {
        if (mEyeAlloc[i] == true) {
            daDaiocta_Eye_c* big_octo_eye_p = (daDaiocta_Eye_c *) fopAcM_SearchByID(mDaioctaEyePcId[i]);
            if (big_octo_eye_p && big_octo_eye_p->mbIsDamagedBomb != 0) {
                is_damaged = true;
            }
        }
    }
    return is_damaged;
}

/* 000017B4-00001A7C       .text setRotEye__11daDaiocta_cFv */
void daDaiocta_c::setRotEye() {
    if (cLib_calcTimer(&mRotEyeTimer) == 0) {
        for (int i = 0; i < ARRAY_SSIZE(mDaioctaEyePcId); i++) {
            if (mEyeAlloc[i] == true) {
                daDaiocta_Eye_c* big_octo_eye_p = (daDaiocta_Eye_c *) fopAcM_SearchByID(mDaioctaEyePcId[i]);
                if (big_octo_eye_p && big_octo_eye_p->mbIsDead == 0) {
                    big_octo_eye_p->mEyeNo = i;
                    big_octo_eye_p->rndRotEye();
                }
            }
        }
        mRotEyeTimer = l_HIO.mRotEyeTimerMin + cM_rndF(l_HIO.mRotEyeTimerAddMax);
    }
}

/* 00001A7C-00001EA0       .text setCollision__11daDaiocta_cFv */
void daDaiocta_c::setCollision() {
    for (int i = 0; i < ARRAY_SSIZE(mSph); i++) {
        int j;
        switch (i) {
            case 0:
                j = 2;
                break;
            case 1:
                j = 3;
                break;
            case 2:
                j = 4;
                break;
            case 3:
                j = 5;
                break;
            case 4:
                j = 6;
                break;
            case 5:
                j = 20;
                break;
        }

        mSph[i].SetR(l_HIO.mSphRadii[i]);
        mSph[i].SetC(mSphCenters[j]);
        dComIfG_Ccsp()->Set(&mSph[i]);
    }

    for (int i = 0; i < 10; i++) {
        int j, k;
        switch (i) {
            case 0:
                j = 25;
                k = 26;
                break;
            case 1:
                j = 26;
                k = 27;
                break;
            case 2:
                j = 27;
                k = 28;
                break;
            case 3:
                j = 28;
                k = 29;
                break;
            case 4:
                j = 29;
                k = 30;
                break;
            case 5:
                j = 31;
                k = 32;
                break;
            case 6:
                j = 32;
                k = 33;
                break;
            case 7:
                j = 33;
                k = 34;
                break;
            case 8:
                j = 34;
                k = 35;
                break;
            case 9:
                j = 35;
                k = 36;
                break;
        }

        mCps[i].set(mSphCenters[j], mSphCenters[k]);
        mCps[i].SetR(l_HIO.mCpsRadii[i]);
        dComIfG_Ccsp()->Set(&mCps[i]);
    }

    mCps[10].set(mSphCenters[36], m21AC);
    mCps[10].SetR(l_HIO.m05C);
    dComIfG_Ccsp()->Set(&mCps[10]);

    mCps[11].set(mSphCenters[30], m21A0);
    mCps[11].SetR(l_HIO.m060);
    dComIfG_Ccsp()->Set(&mCps[11]);

    mCps[12].set(mSphCenters[6], m21B8);
    mCps[12].SetR(l_HIO.m064);
    dComIfG_Ccsp()->Set(&mCps[12]);

    mCps[13].set(mSphCenters[10], m21DC);
    mCps[13].SetR(l_HIO.m068);
    dComIfG_Ccsp()->Set(&mCps[13]);

    mCps[14].set(mSphCenters[8], m21E8);
    mCps[14].SetR(l_HIO.m06C);
    dComIfG_Ccsp()->Set(&mCps[14]);

    mCps[15].set(mSphCenters[9], m21C4);
    mCps[15].SetR(l_HIO.m070);
    dComIfG_Ccsp()->Set(&mCps[15]);
    
    mCps[16].set(mSphCenters[7], m21D0);
    mCps[16].SetR(l_HIO.m074);
    dComIfG_Ccsp()->Set(&mCps[16]);
}

/* 00001EA0-00001EB8       .text modeHideInit__11daDaiocta_cFv */
void daDaiocta_c::modeHideInit() {
    current.pos.y = mWaterY - 3000.0f;
}

/* 00001EB8-00001F34       .text modeHide__11daDaiocta_cFv */
void daDaiocta_c::modeHide() {
    f32 dist_xz = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
    if ((dist_xz < mAppearRadius || dist_xz < l_HIO.mMinAppearRadius) && 
        dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        modeProc(PROC_INIT_e, MODE_APPEAR);
    }    
}

/* 00001F34-000020C8       .text modeAppearInit__11daDaiocta_cFv */
void daDaiocta_c::modeAppearInit() {
    fopAcM_SetStatusMap(this, 0);
    fopAc_ac_c* player_p = dComIfGp_getPlayer(0);
    cXyz dir_to_actor = current.pos - player_p->current.pos;
    cXyz new_pos = player_p->current.pos + (dir_to_actor.normZP() * l_HIO.mMinAppearRadius);
    current.pos.x = new_pos.x;
    current.pos.z = new_pos.z;
    attention_info.flags = 0;
    
    cXyz auzu_pos = current.pos;
    auzu_pos.y = mWaterY + 2.0f;

#if VERSION > VERSION_JPN
    fopAc_ac_c* auzu_p;

    if (fopAcM_SearchByID(mpAuzu, &auzu_p) && auzu_p) {
        auzu_p->current.pos = auzu_pos;
    }
#else 
    int auzu_parameters = 0x1100FF;
    mpAuzu = fopAcM_create(PROC_Obj_Auzu, auzu_parameters, &auzu_pos, tevStr.mRoomNo);
#endif

    setEffect(dPa_name::ID_IT_SN_DO_APPSHIBUKI00);
    mDoAud_bgmAllMute(90);
    for (int i = 0; i < ARRAY_SSIZE(mDaioctaEyePcId); i++) {
        daDaiocta_Eye_c* big_octo_eye_p;
        if (fopAcM_SearchByID(mDaioctaEyePcId[i], (fopAc_ac_c**)&big_octo_eye_p)) {
            big_octo_eye_p->mbAppear = true;
        }
    }
}

/* 000020C8-0000236C       .text modeAppear__11daDaiocta_cFv */
void daDaiocta_c::modeAppear() {
    if (isDamageEye()) {
        modeProc(PROC_INIT_e, MODE_DAMAGE);
    }

    if (DEMO_SELECT(mpEmitter, mParticleCallback.getEmitter())) {
        GXColor sea_color_ambient;
        GXColor sea_color_diffuse;
        dKy_get_seacolor(&sea_color_ambient, &sea_color_diffuse);

        int r = sea_color_ambient.r + l_HIO.m018;
        int g = sea_color_ambient.g + l_HIO.m018;
        int b = sea_color_ambient.b + l_HIO.m018;
    
        if (r >= 0xFF) r = 0xFF;
        if (g >= 0xFF) g = 0xFF;
        if (b >= 0xFF) b = 0xFF;

        sea_color_ambient.r = r;
        sea_color_ambient.g = g;
        sea_color_ambient.b = b;

        DEMO_SELECT(mpEmitter, mParticleCallback.getEmitter())->setGlobalPrmColor(
                sea_color_ambient.r, 
                sea_color_ambient.g, 
                sea_color_ambient.b
            );
    }

    daObjAuzu::Act_c* auzu_p = (daObjAuzu::Act_c *) fopAcM_SearchByID(mpAuzu);
    if (auzu_p) {
        auzu_p->to_appear();
        if (auzu_p->is_appear()) {
            cXyz sp2C = current.pos;
            sp2C.y = mWaterY;
            cLib_addCalcPos2(&current.pos, sp2C, 0.1f, l_HIO.m080);

            f32 dist = (current.pos - sp2C).abs();
            if (dist < 1900.0f && m26C0 == 0) {
                fopAcM_seStart(this, JA_SE_CM_DO_ENTER, 0);
                m26C0 = 1;
                mDoAud_subBgmStart(JA_BGM_DIOCTA_BATTLE);
            }

            if (dist <= 0.1) {
                modeProc(PROC_INIT_e, MODE_WAIT);
            } else {
                s16 target = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
                cLib_addCalcAngleS2(&shape_angle.y, target, 4, l_HIO.m010);
            }
        }
    }
}

/* 0000236C-000023B0       .text modeWaitInit__11daDaiocta_cFv */
void daDaiocta_c::modeWaitInit() {
    if (isDead()) {
        modeProc(PROC_INIT_e, MODE_DELETE);
    }
}

/* 000023B0-00002458       .text modeWait__11daDaiocta_cFv */
void daDaiocta_c::modeWait() {
    current.pos.y = mWaterY;
    if (isDead() || l_HIO.m006 != 0) {
        modeProc(PROC_INIT_e, MODE_DELETE);
    } else if (isDamageEye()) {
        modeProc(PROC_INIT_e, MODE_DAMAGE);
    } else if (isDamageBombEye()) {
        modeProc(PROC_INIT_e, MODE_DAMAGE_BOMB);
    }
}

/* 00002458-000024D8       .text modeDamageInit__11daDaiocta_cFv */
void daDaiocta_c::modeDamageInit() {
    if (isDead()) {
        modeProc(PROC_INIT_e, MODE_DELETE);
    } else {
        mPrmIdx = 2;
        setAnm();
        mPrmIdx = 4;

        setEffect(dPa_name::ID_IT_SN_DO_HITB_SHIBUKIA00);
        setEffect(dPa_name::ID_IT_SN_DO_HITB_SHIBUKIB00);
    }
}

/* 000024D8-000025C4       .text modeDamage__11daDaiocta_cFv */
void daDaiocta_c::modeDamage() {
    current.pos.y = mWaterY;
    if (isDead()) {
        modeProc(PROC_INIT_e, MODE_DELETE);
    } else if (isDamageEye()) {
        modeProc(PROC_INIT_e, MODE_DAMAGE);
    } else if (isDamageBombEye()) {
        modeProc(PROC_INIT_e, MODE_DAMAGE_BOMB);
    }

    if (mPrmIdx == 2) {
        if (std::fabsf(current.pos.y - mWaterY) <= 0.1) {
            modeProc(PROC_INIT_e, MODE_WAIT);
        } else {
            modeProc(PROC_INIT_e, MODE_APPEAR);
        }
    }
}

/* 000025C4-0000268C       .text modeDamageBombInit__11daDaiocta_cFv */
void daDaiocta_c::modeDamageBombInit() {
    if (isDead()) {
        modeProc(PROC_INIT_e, MODE_DELETE);
    } else {
        fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);
        mPrmIdx = 2;
        setAnm();
        mPrmIdx = 3;
        setEffect(dPa_name::ID_IT_SN_DO_HITA_SHIBUKIA00);
        setEffect(dPa_name::ID_IT_SN_DO_HITA_SHIBUKIB00);
    }
}

/* 0000268C-00002778       .text modeDamageBomb__11daDaiocta_cFv */
void daDaiocta_c::modeDamageBomb() {
    current.pos.y = mWaterY;
    if (isDead()) {
        modeProc(PROC_INIT_e, MODE_DELETE);
    } else if (isDamageEye()) {
        modeProc(PROC_INIT_e, MODE_DAMAGE);
    } else if (isDamageBombEye()) {
        modeProc(PROC_INIT_e, MODE_DAMAGE_BOMB);
    } 
    
    if (mPrmIdx == 2) {
        if (std::fabsf(current.pos.y - mWaterY) <= 0.1) {
            modeProc(PROC_INIT_e, MODE_WAIT);
        } else {
            modeProc(PROC_INIT_e, MODE_APPEAR);
        }
    }
}

/* 00002778-000028FC       .text modeDemoInit__11daDaiocta_cFv */
void daDaiocta_c::modeDemoInit() {
    attention_info.flags = 0;
    setEffect(dPa_name::ID_IT_SN_DO_SUIKOMIA00);
    setEffect(dPa_name::ID_IT_SN_DO_SUIKOMIB00);
    setEffect(dPa_name::ID_IT_SN_DO_SUIKOMIC00);
    J3DModelData* model_data_p = mpSuikomiModel->getModelData();
    
    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey *>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BRK_GDO_SUI00));
    JUT_ASSERT(VERSION_SELECT(1334, 1340, 1350, 1350), brk != NULL);
    
    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey *>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BTK_GDO_SUI00));
    JUT_ASSERT(VERSION_SELECT(1337, 1343, 1353, 1353), btk != NULL);

    mBrkAnm2.init(
        model_data_p, brk, true, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, true, FALSE
    );
    mBtkAnm.init(
        model_data_p, btk, true, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, true, FALSE
    );
}

/* 000028FC-00003150       .text modeDemo__11daDaiocta_cFv */
void daDaiocta_c::modeDemo() {
    current.pos.y = mWaterY;
    daShip_c* ship_p_1 = (daShip_c *) fopAcM_SearchByName(PROC_SHIP);
    m21F4 = ship_p_1->current.pos;
    m2200 = ship_p_1->current.angle;

    if (eventInfo.checkCommandDemoAccrpt()) {
        int staff_id = dComIfGp_evmng_getMyStaffId("Daiocta");
        char* cut_name = dComIfGp_getPEvtManager()->getMyNowCutName(staff_id);

        cXyz current_pos = current.pos;
        s16 o_angle;
        dComIfGp_getMapTrans(
            fopAcM_GetRoomNo(this), 
            &current_pos.x, 
            &current_pos.z, 
            &o_angle
        );

        s16 rot_y = cLib_targetAngleY(&current.pos, &current_pos);
        cLib_distanceAngleS(shape_angle.y, rot_y);

        if (strcmp(cut_name, "SUIKOMI1") == 0) {
            mPrmIdx = 6;
            if (mPrmIdx == 6) {
                mDoAud_seStart(
                    JA_SE_CM_DO_SUCK_IN, &m2434, 0, 
                    dComIfGp_getReverb(fopAcM_GetRoomNo(this))
                );
            } 

            if ((m2434 - m21F4).absXZ() < 80.0f) {
                dComIfGp_evmng_cutEnd(staff_id);
            } else if (mpMorf->getFrame() == 50.0f) {
                mpMorf->setFrame(40.0f);
            }

            if (REG12_S(0) != 0) {
                return;
            }

            s16 target_angle_y = cLib_targetAngleY(&current.pos, &ship_p_1->current.pos);
            s32 distance_angle_s = cLib_distanceAngleS(shape_angle.y + l_HIO.m014, target_angle_y);
            cLib_addCalc2(&m2208, l_HIO.m088, l_HIO.m090, l_HIO.m08C);
            cLib_chaseF(&m21F4.x, m2434.x, m2208 / 2.0f);
            cLib_chaseF(&m21F4.z, m2434.z, m2208);
            cLib_addCalcAngleS2(&m2200.y, target_angle_y + 0x8000, 8, 0x400);

            if (distance_angle_s < l_HIO.m012) {
                target_angle_y = target_angle_y + 0x4000;
                f32 dist = (current.pos - ship_p_1->current.pos).absXZ();
                m21F4.z += (dist / (REG12_F(1) + 60.0f)) * cM_scos(target_angle_y);
                m21F4.x += (dist / (REG12_F(1) + 60.0f)) * cM_ssin(target_angle_y);
            }

            daShip_c* ship_p_2 = (daShip_c *) fopAcM_SearchByName(PROC_SHIP);
            ship_p_2->initStartPos(&m21F4, m2200.y);
        }

        if (strcmp(cut_name, "SUIKOMI2") == 0) {
            if (mpMorf->getFrame() == 65.0f) {
                fopAcM_seStart(this, JA_SE_CM_DO_SUCK_IN_FIN, 0);
            }

            s16 target_angle_y = cLib_targetAngleY(&current.pos, &ship_p_1->current.pos); 
            cLib_distanceAngleS(shape_angle.y, target_angle_y);
            cLib_chasePosXZ(&m21F4, current.pos, m2208);
            cLib_addCalcAngleS2(&m2200.y, target_angle_y + 0x8000, 4, 0x800);
            
            daShip_c* ship_p_2 = (daShip_c *) fopAcM_SearchByName(PROC_SHIP);
            ship_p_2->initStartPos(&m21F4, m2200.y);

            if ((current.pos - m21F4).absXZ() < 10.0f && (mpMorf->isStop() || mPrmIdx == 2)) {
                shape_angle.y = rot_y;
                mpMorf->calc();
                current.pos = m220C;
                ship_p_2->initStartPos(&current.pos, rot_y);
                dComIfGp_evmng_cutEnd(staff_id);
            }
        }

        if (strcmp(cut_name, "HAKIDASU") == 0) {
            fopAc_ac_c* actor_p = fopAcM_SearchByID(mpAuzu);
            actor_p->current.pos = current.pos;
            actor_p->current.pos.y += 20.0f;
            if (s32(mpMorf->getFrame()) == 26) {
                mDoAud_seStart(
                    JA_SE_CV_DO_SPIT_SHIP, &m2434, 0, 
                    dComIfGp_getReverb(fopAcM_GetRoomNo(this))
                );
            }

            if (mPrmIdx == 8 && mpMorf->isStop()) {
                dComIfGp_evmng_cutEnd(staff_id);
#if VERSION > VERSION_DEMO
                mDoAud_subBgmStop();
#endif
            } else if (mpMorf->getFrame() < 10.0f) {
                ship_p_1->initStartPos(&m2434, rot_y);
            }
            mPrmIdx = 8;
        }

        if (strcmp(cut_name, "WAIT") == 0) {
            mPrmIdx = 2;
        }

        if (dComIfGp_evmng_endCheck("DAIOCTA_SUIKOMI")) {
#if VERSION == VERSION_DEMO
            mDoAud_subBgmStop();
#endif
            if (m575 == 0xFF) {
                daPy_getPlayerLinkActorClass()->startRestartRoom(6, 0xC9, -1.0f, 1);
            } else {
                dComIfGp_setNextStage(
                    dComIfGp_getStartStageName(), 
                    m575, fopAcM_GetRoomNo(this), 
                    -1, 0.0f, 6
                );
            }
        }
    } else {
        fopAcM_orderOtherEvent2(this, "DAIOCTA_SUIKOMI", dEvtFlag_NOPARTNER_e);
    }
}

/* 00003150-00003284       .text modeDeleteInit__11daDaiocta_cFv */
void daDaiocta_c::modeDeleteInit() {
    attention_info.flags = 0;
    fopAcM_seStart(this, JA_SE_CV_DO_DIE, 0);
    fopAcM_seStart(this, JA_SE_CM_DO_JITABATA, 0);
    fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);
    setEffect(dPa_name::ID_IT_SN_DO_HITC_SHIBUKIA00);
    setEffect(dPa_name::ID_IT_SN_DO_HITC_SHIBUKIB00);
}

/* 00003284-000036A8       .text modeDelete__11daDaiocta_cFv */
void daDaiocta_c::modeDelete() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        int staff_id = dComIfGp_evmng_getMyStaffId("Daiocta");
        char* cut_name = dComIfGp_getPEvtManager()->getMyNowCutName(staff_id);

        if (strcmp(cut_name, "DEATH1") == 0) {
            current.pos.y = mWaterY;
            mPrmIdx = 5;
            if (mPrmIdx == 5 && mpMorf->isStop()) {
                fopAcM_monsSeStart(this, JA_SE_CV_DO_SINK, 0);
                setEffect(dPa_name::ID_IT_SN_DO_DOWNSHIBUKI00);
                daObjAuzu::Act_c* auzu_p = (daObjAuzu::Act_c *) fopAcM_SearchByID(mpAuzu);
                auzu_p->to_disappear();
                dComIfGp_getVibration().StartQuake(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                dComIfGp_evmng_cutEnd(staff_id);
            }
        }

        if (strcmp(cut_name, "DEATH2") == 0) {
            cXyz target_pos = current.pos;
            target_pos.y = mWaterY - 3000.0f;
            mPrmIdx = 7;
            cLib_chasePos(&current.pos, target_pos, l_HIO.m0E0);
            
            if (std::fabsf(current.pos.y - mWaterY) > 600.0f && m26C1 == 0) {
                initAwa();
                fopAcM_seStart(this, JA_SE_CM_DO_SINK_IN_SEA, 0);
                m26C1 = 1;
                m31C4 = 1;
                mDoAud_subBgmStop();
            }

            if ((current.pos - target_pos).abs() < l_HIO.m0E0 * 3.0f) {
                if (mSwitchNo != 0xFF) {
                    m31C4 = 0;
                    dComIfGp_getVibration().StopQuake(-1);
                    dComIfGs_onSwitch(mSwitchNo, fopAcM_GetRoomNo(this));
                    if (m057C != 1) {
                        mDoAud_seStart(JA_SE_READ_RIDDLE_1);
                    }
                    fopAcM_ClearStatusMap(this);
                }
                dComIfGp_evmng_cutEnd(staff_id);
            }
        }

        if (m057C != 1 && dComIfGp_evmng_endCheck("DAIOCTA_DEAD")) {
            dComIfGp_event_reset();
            fopAcM_delete(this);
        }
    } else if (m057C == 1) {
        fopAcM_orderOtherEvent2(this, "DAIOCTA_DEAD_ELF", dEvtFlag_NOPARTNER_e);
    } else {
        fopAcM_orderOtherEvent2(this, "DAIOCTA_DEAD", dEvtFlag_NOPARTNER_e);
    }
}

/* 000036A8-00003888       .text modeProc__11daDaiocta_cFQ211daDaiocta_c6Proc_eQ211daDaiocta_c6Mode_e */
void daDaiocta_c::modeProc(daDaiocta_c::Proc_e i_procType, daDaiocta_c::Mode_e i_modeProc) {
    static ModeEntry mode_tbl[7] = {
        { &daDaiocta_c::modeHideInit,       &daDaiocta_c::modeHide,       "HIDE"        },
        { &daDaiocta_c::modeAppearInit,     &daDaiocta_c::modeAppear,     "APPEAR"      },
        { &daDaiocta_c::modeWaitInit,       &daDaiocta_c::modeWait,       "WAIT"        },
        { &daDaiocta_c::modeDamageInit,     &daDaiocta_c::modeDamage,     "DAMAGE"      },
        { &daDaiocta_c::modeDamageBombInit, &daDaiocta_c::modeDamageBomb, "DAMAGE_BOMB" },
        { &daDaiocta_c::modeDeleteInit,     &daDaiocta_c::modeDelete,     "DELETE"      },
        { &daDaiocta_c::modeDemoInit,       &daDaiocta_c::modeDemo,       "DEMO"        }
    };

    if (i_procType == PROC_INIT_e) {
        mMode = i_modeProc;
        (this->*mode_tbl[mMode].mInitFunc)();
    } else if (i_procType == PROC_EXEC_e) {
        (this->*mode_tbl[mMode].mUpdFunc)();
    }
}

/* 00003888-00003AF4       .text setAnm__11daDaiocta_cFv */
void daDaiocta_c::setAnm() {
    static const dLib_anm_idx_c a_anm_idx_tbl[] = {
        { 0xD, -1 }, 
        { 0x6, -1 },
        { 0x7, -1 }, 
        { 0x8, -1 },
        { 0xC, -1 }, 
        { 0x9, -1 },
        { 0xB, -1 }
    };

    dLib_anm_prm_c anm_prms[] = {
        { 0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE },
        { 0, -1, 0, 8.0f, 2.0f, J3DFrameCtrl::EMode_LOOP },
        { 0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP },
        { 1,  2, 0, 1.0f, 1.0f, J3DFrameCtrl::EMode_NONE },
        { 2,  2, 0, 1.0f, 1.0f, J3DFrameCtrl::EMode_NONE },
        { 3, -1, 0, 1.0f, 1.0f, J3DFrameCtrl::EMode_NONE },
        { 4,  2, 0, 1.0f, 1.0f, J3DFrameCtrl::EMode_NONE },
        { 5, -1, 0, 1.0f, 1.0f, J3DFrameCtrl::EMode_LOOP },
        { 6, -1, 0, 1.0f, 1.0f, J3DFrameCtrl::EMode_NONE }
    };

    for (int i = 1; i < 9; i++) {
        anm_prms[i].mMorf = l_HIO.m0BC[i];
        anm_prms[i].mPlaySpeed = l_HIO.m098[i];
    }

    J3DModel* morf_model_p = mpMorf->getModel();
    if (mAnmIdx == 3) { 
        f32 morf_frame = mpMorf->getFrame();
        if (morf_frame == 10.0f || morf_frame == 25.0f || morf_frame == 45.0f) {
            dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
    }

    if (mAnmIdx == 6) {
        if (mpMorf->getFrame() == 1.0f) {
            setEffect(dPa_name::ID_IT_SN_DO_HAKIDASHI00);
        }
        if (mpMorf->getFrame() == 26.0f) {
            dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
    }

    static const s32 a_brk_anm_idx_tbl[] = {
        DAIOCTA_BRK_WAIT1, 
        DAIOCTA_BRK_DAMAGE1, 
        DAIOCTA_BRK_DAMAGE2, 
        DAIOCTA_BRK_DEATH1, 
        DAIOCTA_BRK_SUIKOMU1, 
        DAIOCTA_BRK_DEATH2, 
        DAIOCTA_BRK_HAKIDASU1
    };
    
    static const s32 a_brk_anm_prm_tbl[] = {
        0, 0, 0, 1, 2, 
        3, 4, 5, 6
    };

    s32 idx = a_brk_anm_prm_tbl[mPrmIdx];

    if (mOldPrmIdx != mPrmIdx && idx != -1) {
        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arc_name, 
                                                    a_brk_anm_idx_tbl[a_brk_anm_prm_tbl[mPrmIdx]]);
        JUT_ASSERT(VERSION_SELECT(1760, 1772, 1782, 1782), brk != NULL);
        mBrkAnm1.init(
            morf_model_p->getModelData(), brk, 
            TRUE, J3DFrameCtrl::EMode_LOOP, 
            1.0f, 0, -1, true, FALSE
        ); 
    }
    dLib_setAnm(m_arc_name, mpMorf, &mAnmIdx, &mPrmIdx, &mOldPrmIdx, a_anm_idx_tbl, anm_prms, false);
    mBrkAnm1.setFrame(mpMorf->getFrame());
}

/* 00003AF4-00003B20       .text setWater__11daDaiocta_cFv */
void daDaiocta_c::setWater() {
    if (mAcch.GetSeaHeight() != -G_CM3D_F_INF) {
        mWaterY = mAcch.GetSeaHeight();
    } else {
        mWaterY = 0.0f;
    }
}

/* 00003B20-00003D20       .text _execute__11daDaiocta_cFv */
bool daDaiocta_c::_execute() {
    if (mMode == MODE_DELETE) {
        execAwa();
    }

    if (mMode != MODE_HIDE && DEMO_SELECT(true, mMode != MODE_APPEAR)) {
#if VERSION == VERSION_DEMO
        setWater();
        mBrkAnm2.play();
        mBtkAnm.play();
#endif        
        f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
        s16 angle_y = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
        s32 dist_angle_s = cLib_distanceAngleS(shape_angle.y + l_HIO.m014, angle_y);
        if (dist < l_HIO.m084 && 
            mMode != MODE_DEMO && 
            mMode != MODE_DELETE && 
            dist_angle_s < l_HIO.m012) {
            modeProc(PROC_INIT_e, MODE_DEMO);
        }
#if VERSION > VERSION_DEMO
    }

    if (mMode != MODE_HIDE) {
        setWater();
        mBrkAnm2.play();
        mBtkAnm.play();
#endif

        attention_info.position = current.pos;
        eyePos = current.pos;

        isLivingEye();
        mBrkAnm1.play();

        mpMorf->play(NULL, 0, 0);
        mpMorf->calc();

        setRotEye();

        mAcch.CrrPos(*dComIfG_Bgsp());
        tevStr.mRoomNo = fopAcM_GetRoomNo(this);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
    }

    modeProc(PROC_EXEC_e, MODE_NULL);

    if (mMode != MODE_HIDE) {
        setCollision();
        setAnm();
        setMtx();

        if (l_HIO.m007 != 0) {
            mPrmIdx = l_HIO.m00A;
            setAnm();
        }
    }

    return false;
}

/* 00003D20-00003E58       .text drawAwa__11daDaiocta_cFv */
void daDaiocta_c::drawAwa() {
    dComIfGd_setListBG();
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);

    for (int i = 0; i < l_HIO.m016; i++) {
        g_env_light.setLightTevColorType(mpAwaModels[i], &tevStr);
        mAwaBckAnms[i].entry(mpAwaModels[i]->getModelData());
        mAwaBtkAnms[i].entry(mpAwaModels[i]->getModelData());
        mAwaBrkAnms[i].entry(mpAwaModels[i]->getModelData());
        mDoExt_modelUpdateDL(mpAwaModels[i]);
    }

    dComIfGd_setList();
}

/* 00003E58-00003F4C       .text drawSuikomi__11daDaiocta_cFv */
void daDaiocta_c::drawSuikomi() {
    dComIfGd_setListBG();
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpSuikomiModel, &tevStr);
    mBtkAnm.entry(mpSuikomiModel->getModelData());
    mBrkAnm2.entry(mpSuikomiModel->getModelData());
    mDoExt_modelUpdateDL(mpSuikomiModel);
    mBtkAnm.remove(mpSuikomiModel->getModelData());
    mBrkAnm2.remove(mpSuikomiModel->getModelData());
    dComIfGd_setList();
}

/* 00003F4C-0000412C       .text drawDebug__11daDaiocta_cFv */
void daDaiocta_c::drawDebug() {
    GXColor dummy_1 = { 0x00, 0xFF, 0x00, 0x80 };
    GXColor dummy_2 = { 0xFF, 0xFF, 0x00, 0x80 };
    GXColor dummy_3 = { 0xFF, 0xFF, 0x00, 0x80 };
    GXColor dummy_4 = { 0x00, 0xFF, 0xFF, 0x80 };
    GXColor dummy_5 = { 0xFF, 0x00, 0x00, 0x80 };
    GXColor dummy_6 = { 0x00, 0xFF, 0x00, 0x80 };
    GXColor dummy_7 = { 0xFF, 0x00, 0x00, 0x80 };
    GXColor dummy_8 = { 0xFF, 0x00, 0x00, 0x80 };
    
    fopAc_ac_c* player_p;
    for (int i = 0; i < ARRAY_SSIZE(mSphCenters); i++) {
        player_p = dComIfGp_getPlayer(0);
        f32 fVar1 = (player_p->current.pos - mSphCenters[i]).abs();
    }
    cXyz sp30 = current.pos;
    sp30.y = 50.0f + mWaterY;

    u32 uVar1 = l_HIO.m012;
    if (uVar1 - 0x70000 != 0xFFFF || l_HIO.m012 != 0) {
        u32 uVar2 = shape_angle.y + l_HIO.m014;
        s16 sVar1 = shape_angle.y + l_HIO.m014 + uVar1;

        cXyz sp24 = current.pos;
        sp24.z += l_HIO.m084 * cM_scos(sVar1);
        sp24.x += l_HIO.m084 * cM_ssin(sVar1);

        cXyz sp18 = current.pos;
        sp18.z += l_HIO.m084 * cM_scos(uVar2 - uVar1);
        sp18.x += l_HIO.m084 * cM_ssin(uVar2 - uVar1);
    }
}

/* 0000412C-00004244       .text _draw__11daDaiocta_cFv */
bool daDaiocta_c::_draw() {
    if (l_HIO.m004) {
        drawDebug();
    }

    if (mMode == MODE_HIDE) {
        return true;
    } 
    
    if (mMode == MODE_DEMO) {
        drawSuikomi();
    }
    
    if (mMode == MODE_DELETE) {
        drawAwa();
    }

    J3DModel* morf_model_p = mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    mBrkAnm1.entry(morf_model_p->getModelData());

    if (l_HIO.m005 == 0) {
        mpMorf->entryDL();
    }

    mBrkAnm1.remove(morf_model_p->getModelData());

    dSnap_RegistFig(DSNAP_TYPE_UNKC6, this, 1.0f, 1.0f, 1.0f);

    return true;
}

/* 00004244-00004364       .text getArg__11daDaiocta_cFv */
void daDaiocta_c::getArg() {
    u8 appear_radius_multiplier;
    s16 prm2;
    u32 prm;

    prm = fopAcM_GetParam(this);
    prm2 = home.angle.z;

    mOctoType = prm;
    appear_radius_multiplier = prm >> 8;
    m575 = prm >> 16;
    mSwitchNo = prm >> 24;
    m057C = prm2;

    home.angle.z = 0;
    current.angle.z = 0;
    shape_angle.z = 0;

    if (appear_radius_multiplier == 0xFF) {
        mAppearRadius = l_HIO.mDefaultAppearRadius;
    } else {
        mAppearRadius = f32(appear_radius_multiplier) * 100.0f;
    }

    if (mOctoType > 3) {
        mOctoType = 0;
    }

    switch (mOctoType) {
        case FOUR_EYED:
            mEyeAlloc[0] = true;
            mEyeAlloc[1] = true;
            mEyeAlloc[2] = true;
            mEyeAlloc[5] = true;
            break;
        case EIGHT_EYED:
            for (int i = 0; i < 8; i++) {
                mEyeAlloc[i] = true;
            }
            break;
        case TWELVE_EYED:
            for (int i = 0; i < ARRAY_SSIZE(mEyeAlloc); i++) {
                mEyeAlloc[i] = true;
            }
            break;
    }
}

/* 00004364-00004660       .text createInit__11daDaiocta_cFv */
void daDaiocta_c::createInit() {
    m220C = current.pos;
    initAwa();
    modeProc(PROC_INIT_e, MODE_HIDE);
    initMtx();
    attention_info.flags = 0;
    shape_angle = current.angle;

    mAnmMtxIndices[0] = 21;
    mAnmMtxIndices[1] = 22;
    mAnmMtxIndices[2] = 15;
    mAnmMtxIndices[3] = 23;
    mAnmMtxIndices[4] = 24;
    mAnmMtxIndices[5] = 16;
    mAnmMtxIndices[6] = 17;
    mAnmMtxIndices[7] = 18;
    mAnmMtxIndices[8] = 14;
    mAnmMtxIndices[9] = 11;
    mAnmMtxIndices[10] = 12;
    mAnmMtxIndices[11] = 13;

    static const int NUM_JOINT_NODES = 37;
    for (int i = 0; i < NUM_JOINT_NODES; i++) {
        mpMorf->getModel()
            ->getModelData()
            ->getJointNodePointer(i)
            ->setCallBack(nodeControl_CB);
    }

    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(
        fopAcM_GetPosition_p(this), 
        fopAcM_GetOldPosition_p(this), 
        this, 1, &mAcchCir, 
        fopAcM_GetSpeed_p(this)
    );
    mAcch.SetWallNone();
    mAcch.SetRoofNone();
    mAcch.OnSeaCheckOn();
    mAcch.OnSeaWaterHeight();

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());

    fopAcM_setCullSizeBox(
        this, 
        -2300.0f, -500.0f, -2300.0f, 
        2300.0f, 2300.0f, 2300.0f
    );

    fopAcM_setCullSizeFar(this, 10.0f);

    for (int i = 0; i < ARRAY_SSIZE(mDaioctaEyePcId); i++) {
        if (mEyeAlloc[i] == true) {
            mDaioctaEyePcId[i] = fopAcM_createChild(
                PROC_DAIOCTA_EYE, fpcM_GetID(this), 
                -1, &current.pos, 
                tevStr.mRoomNo, NULL
            );
        }
    }

#if VERSION > VERSION_JPN
    mpAuzu = fopAcM_create(
        PROC_Obj_Auzu, 
        0x1100FF, 
        &current.pos, 
        tevStr.mRoomNo
    );
#endif
    mStts.Init(0, 0, this);

    for (int i = 0; i < ARRAY_SSIZE(mSph); i++) {
        mSph[i].Set(m_sph_src);
        mSph[i].SetStts(&mStts);
        mSph[i].SetCoHitCallback(coHit_CB);
    }

    for (int i = 0; i < ARRAY_SSIZE(mCps); i++) {
        mCps[i].Set(m_cps_src);
        mCps[i].SetStts(&mStts);
        mCps[i].SetCoHitCallback(coHit_CB);
    }

    mPrmIdx = 1;
}

/* 00004660-00004918       .text _create__11daDaiocta_cFv */
cPhs_State daDaiocta_c::_create() {
    fopAcM_SetupActor(this, daDaiocta_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, m_arc_name);

    if (state == cPhs_COMPLEATE_e) {
        getArg();

        if (mSwitchNo != 0xFF && dComIfGs_isSwitch(mSwitchNo, fopAcM_GetRoomNo(this))) {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }
    
    return state;
}

/* 00005098-0000513C       .text _delete__11daDaiocta_cFv */
bool daDaiocta_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
#if VERSION > VERSION_DEMO 
    mParticleCallback.remove();
#endif
    fopAc_ac_c* actor_p;
    for (int i = 0; i < ARRAY_SSIZE(mDaioctaEyePcId); i++) {
        if (fopAcM_SearchByID(mDaioctaEyePcId[i], &actor_p)) {
            fopAcM_delete(actor_p);
        }
    }

#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&m2434);
#endif 
    return true;
}

/* 0000513C-0000515C       .text daDaioctaCreate__FPv */
static cPhs_State daDaioctaCreate(void* i_this) {
    return ((daDaiocta_c*)i_this)->_create();
}

/* 0000515C-00005180       .text daDaioctaDelete__FPv */
static BOOL daDaioctaDelete(void* i_this) {
    return ((daDaiocta_c*)i_this)->_delete();
}

/* 00005180-000051A4       .text daDaioctaExecute__FPv */
static BOOL daDaioctaExecute(void* i_this) {
    return ((daDaiocta_c*)i_this)->_execute();
}

/* 000051A4-000051C8       .text daDaioctaDraw__FPv */
static BOOL daDaioctaDraw(void* i_this) {
    return ((daDaiocta_c*)i_this)->_draw();
}

/* 000051C8-000051D0       .text daDaioctaIsDelete__FPv */
static BOOL daDaioctaIsDelete(void*) {
    return TRUE;
}

static actor_method_class daDaioctaMethodTable = {
    (process_method_func)daDaioctaCreate,
    (process_method_func)daDaioctaDelete,
    (process_method_func)daDaioctaExecute,
    (process_method_func)daDaioctaIsDelete,
    (process_method_func)daDaioctaDraw,
};

actor_process_profile_definition g_profile_DAIOCTA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DAIOCTA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDaiocta_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DAIOCTA,
    /* Actor SubMtd */ &daDaioctaMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
