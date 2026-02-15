/**
 * d_a_daiocta.cpp
 * Mini-Boss - Big Octo (body)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_daiocta.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_ship.h"
#include "d/d_cc_d.h"
#include "d/d_jnt_hit.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"

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
    field_0x004 = 0;
    field_0x008 = 0;
    field_0x006 = 0;
    field_0x005 = 0;
    field_0x01C = 600.0;
    field_0x020 = 500.0;
    field_0x024 = 450.0;
    field_0x028 = 350.0;
    field_0x02C = 350.0;
    field_0x030 = 300.0;
    field_0x034 = 60.0;
    field_0x038 = 60.0;
    field_0x03C = 60.0;
    field_0x040 = 60.0;
    field_0x044 = 60.0;
    field_0x048 = 60.0;
    field_0x04C = 60.0;
    field_0x050 = 60.0;
    field_0x054 = 60.0;
    field_0x058 = 60.0;
    field_0x05C = 100.0;
    field_0x060 = 100.0;
    field_0x064 = 250.0;
    field_0x068 = 100.0;
    field_0x06C = 150.0;
    field_0x070 = 100.0;
    field_0x074 = 150.0;
    field_0x00C = 0x1e;
    field_0x00E = 0x3c;
    field_0x078 = 5000.0;
    field_0x07C = 4500.0;
    field_0x080 = 30.0;
    field_0x010 = 0x100;
    field_0x084 = 1800.0;
    field_0x012 = 0x1500;
    field_0x088 = 40.0;
    field_0x08C = 1.0;
    field_0x090 = 0.02;
    field_0x094 = 150.0;
    field_0x014 = -0x800;
    field_0x0FC = 0.0;
    field_0x100 = 5.0;
    field_0x104 = 700.0;
    field_0x0C0 = 8.0;
    field_0x0C4 = 8.0;
    field_0x0C8 = 3.0;
    field_0x0CC = 3.0;
    field_0x0D0 = 3.0;
    field_0x0D4 = 7.0;
    field_0x0D8 = 9.0;
    field_0x09C = 1.0;
    field_0x0A0 = 0.5;
    field_0x0A4 = 0.75;
    field_0x0A8 = 0.625;
    field_0x0AC = 0.625;
    field_0x0B0 = 0.5;
    field_0x0B4 = 1.0;
    field_0x0B8 = 1.0;
    field_0x0E0 = 20.0;
    field_0x016 = 0x1e;
    field_0x0E4 = 300.0;
    field_0x0E8 = 1200.0;
    field_0x0EC = 1.0;
    field_0x0F0 = 2.0;
    field_0x0F4 = 10.0;
    field_0x0F8 = 30.0;
    field_0x018 = 0x2d;
}

/* 00000334-00000358       .text coHit_CB__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void coHit_CB(fopAc_ac_c* i_this, dCcD_GObjInf* i_unused1P, fopAc_ac_c* i_actor, dCcD_GObjInf* i_unused2P) {
    UNUSED(i_unused1P); UNUSED(i_unused2P);
    ((daDaiocta_c*)i_this)->_coHit(i_actor);
}

/* 00000358-000003DC       .text _coHit__11daDaiocta_cFP10fopAc_ac_c */
void daDaiocta_c::_coHit(fopAc_ac_c* i_actor) {
    if (i_actor != NULL && fpcM_GetName(i_actor) == PROC_BOMB) {
        daBomb_c* bomb_p = (daBomb_c *) i_actor;
        if ((field_0x056C == 2 || field_0x056C == 4 || field_0x056C == 1 || field_0x056C == 3) && 
            bomb_p->chk_state(daBomb_c::STATE_4)) {
            modeProc(PROC_INIT, MODE_DAMAGE_BOMB);
        }
    }
}

/* 000003DC-00000470       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daDaiocta_c* actor_p = (daDaiocta_c *) model_p->getUserArea();
        JUT_ASSERT(0x1A4, actor_p != NULL);
        actor_p->_nodeControl(i_nodeP, model_p);
    }
    return TRUE;
}

/* 00000470-0000066C       .text _nodeControl__11daDaiocta_cFP7J3DNodeP8J3DModel */
void daDaiocta_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    J3DJoint* jnt_p = (J3DJoint *) i_nodeP;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jnt_no));
    mDoMtx_stack_c::multVecZero(&field_0x0290[jnt_no]);

    cXyz base;
    switch (jnt_no) {
        case 30:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21A0);
            break;
        case 36:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21AC);
            break;
        case 20:
            base.set(l_HIO.field_0x094, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x2434);
            break;
        case 6:
            base.set(450.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21B8);
            break;
        case 9:
            base.set(300.0f, -200.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21C4);
            break; 
        case 7:
            base.set(300.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21D0);
            break;
        case 10:
            base.set(300.0f, 200.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21DC);
            break;
        case 8:
            base.set(300.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::multVec(&base, &field_0x21E8);
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

    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, 0x12));
    JUT_ASSERT(0x204, modelData != NULL);

    bck = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_arc_name, 0xA));
    JUT_ASSERT(0x208, bck != NULL);

    btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, 0x25));
    JUT_ASSERT(0x20C, btk != NULL);

    brk = static_cast<J3DAnmTevRegKey *>(dComIfG_getObjectRes(m_arc_name, 0x1C));
    JUT_ASSERT(0x210, brk != NULL);


    for (int i = 0; i < ARRAY_SSIZE(field_0x2774); i++) {
        field_0x26FC[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
        if (field_0x26FC[i] == NULL) {
            return FALSE;
        }

        if (!field_0x2774[i].init(modelData, bck, TRUE, 
                                J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
            return FALSE;
        }

        if (!field_0x2954[i].init(modelData, btk, TRUE, 
                                J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }

        if (!field_0x2BAC[i].init(modelData, brk, TRUE, 
                                J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }
    }

    return TRUE;
}

/* 000009B8-00000ABC       .text createSuikomiHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::createSuikomiHeap() {
    J3DModelData* modelData = (J3DModelData * ) dComIfG_getObjectRes(m_arc_name, 0x13);
    JUT_ASSERT(0x227, modelData != NULL);

    field_0x26CC = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);

    if (!field_0x26CC) {
        return FALSE;
    }

    if (!dLib_brkInit(modelData, &field_0x26D0, m_arc_name, 0x1D) || 
        !dLib_btkInit(modelData, &field_0x26E8, m_arc_name, 0x26)) {
        return FALSE;
    }

    return TRUE;
}

/* 00000ABC-00000C04       .text createBodyHeap__11daDaiocta_cFv */
BOOL daDaiocta_c::createBodyHeap() {
    J3DModelData* modelData = (J3DModelData *) dComIfG_getObjectRes(m_arc_name, 0x11);
    JUT_ASSERT(0x243, modelData != NULL);

    if (!dLib_brkInit(modelData, &field_0x058C, m_arc_name, 0x20)) {
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
            /* mShapeType  */ 0,
            /* mJointIndex */ 2,
            /* mRadius     */ 550.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 3,
            /* mRadius     */ 450.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 4,
            /* mRadius     */ 400.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 5,
            /* mRadius     */ 300.0f,
            /* mpOffsets   */ body_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 6,
            /* mRadius     */ 200.0f,
            /* mpOffsets   */ body_top_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 7,
            /* mRadius     */ 150.0f,
            /* mpOffsets   */ body_top_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 8,
            /* mRadius     */ 150.0f,
            /* mpOffsets   */ body_top_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 9,
            /* mRadius     */ 100.0f,
            /* mpOffsets   */ hire_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 10,
            /* mRadius     */ 100.0f,
            /* mpOffsets   */ hire_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 30,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ te_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 29,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 28,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 27,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 36,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ te_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 35,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ te_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 34,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        },
        {
            /* mShapeType  */ 0,
            /* mJointIndex */ 33,
            /* mRadius     */ 40.0f,
            /* mpOffsets   */ ude_cyl_offset
        }
    };

    field_0x26C8 = JntHit_create(
        mpMorf->getModel(), search_data, 
        ARRAY_SSIZE(search_data)
    );

    if (!field_0x26C8) {
        return FALSE;
    }

    jntHit = field_0x26C8;

    return TRUE;
}

/* 00000C64-00000D94       .text setMtx__11daDaiocta_cFv */
void daDaiocta_c::setMtx() {
    for (int i = 0; i < ARRAY_SSIZE(field_0x2470); i++) {
        fopAc_ac_c* actor_p;
        if (field_0x2470[i] != 0 && fopAcM_SearchByID(field_0x2440[i], &actor_p)) {
            Mtx mtx;
            mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(field_0x04E0[i]));
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
    cXyz base = current.pos;
    base.y = field_0x2430;
    mDoMtx_stack_c::transS(base);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::transM(l_HIO.field_0x0FC, l_HIO.field_0x100, l_HIO.field_0x104);
    field_0x26CC->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000E2C-00000EDC       .text setAwaMtx__11daDaiocta_cFv */
void daDaiocta_c::setAwaMtx() {
    for (int i = 0; i < l_HIO.field_0x016; i++) {
        field_0x26FC[i]->setBaseScale(field_0x305C[i]);
        mDoMtx_stack_c::transS(field_0x2EF4[i]);
        field_0x26FC[i]->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 00000EDC-00000F70       .text initMtx__11daDaiocta_cFv */
void daDaiocta_c::initMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    field_0x26CC->setBaseScale(scale);
    setMtx();
    mpMorf->getModel()->calc();
    field_0x26CC->calc();
}

/* 00000F70-0000116C       .text setEffect__11daDaiocta_cFUs */
void daDaiocta_c::setEffect(u16) {
    /* Nonmatching */
}

/* 0000116C-0000129C       .text setAwaRandom__11daDaiocta_cFi */
void daDaiocta_c::setAwaRandom(int) {
    /* Nonmatching */
}

/* 0000129C-000013D8       .text initAwa__11daDaiocta_cFv */
void daDaiocta_c::initAwa() {
    /* Nonmatching */
}

/* 000013D8-00001548       .text execAwa__11daDaiocta_cFv */
void daDaiocta_c::execAwa() {
    /* Nonmatching */
}

/* 00001548-000015E8       .text isLivingEye__11daDaiocta_cFv */
void daDaiocta_c::isLivingEye() {
    /* Nonmatching */
}

/* 000015E8-00001684       .text isDead__11daDaiocta_cFv */
void daDaiocta_c::isDead() {
    /* Nonmatching */
}

/* 00001684-0000171C       .text isDamageEye__11daDaiocta_cFv */
void daDaiocta_c::isDamageEye() {
    /* Nonmatching */
}

/* 0000171C-000017B4       .text isDamageBombEye__11daDaiocta_cFv */
void daDaiocta_c::isDamageBombEye() {
    /* Nonmatching */
}

/* 000017B4-00001A7C       .text setRotEye__11daDaiocta_cFv */
void daDaiocta_c::setRotEye() {
    /* Nonmatching */
}

/* 00001A7C-00001EA0       .text setCollision__11daDaiocta_cFv */
void daDaiocta_c::setCollision() {
    /* Nonmatching */
}

/* 00001EA0-00001EB8       .text modeHideInit__11daDaiocta_cFv */
void daDaiocta_c::modeHideInit() {
    /* Instruction match */
    current.pos.y = field_0x2430 - 3000.0f;
}

/* 00001EB8-00001F34       .text modeHide__11daDaiocta_cFv */
void daDaiocta_c::modeHide() {
    /* Nonmatching */
}

/* 00001F34-000020C8       .text modeAppearInit__11daDaiocta_cFv */
void daDaiocta_c::modeAppearInit() {
    /* Nonmatching */
}

/* 000020C8-0000236C       .text modeAppear__11daDaiocta_cFv */
void daDaiocta_c::modeAppear() {
    /* Nonmatching */
}

/* 0000236C-000023B0       .text modeWaitInit__11daDaiocta_cFv */
void daDaiocta_c::modeWaitInit() {
    /* Nonmatching */
}

/* 000023B0-00002458       .text modeWait__11daDaiocta_cFv */
void daDaiocta_c::modeWait() {
    /* Nonmatching */
}

/* 00002458-000024D8       .text modeDamageInit__11daDaiocta_cFv */
void daDaiocta_c::modeDamageInit() {
    /* Nonmatching */
}

/* 000024D8-000025C4       .text modeDamage__11daDaiocta_cFv */
void daDaiocta_c::modeDamage() {
    /* Nonmatching */
}

/* 000025C4-0000268C       .text modeDamageBombInit__11daDaiocta_cFv */
void daDaiocta_c::modeDamageBombInit() {
    /* Nonmatching */
}

/* 0000268C-00002778       .text modeDamageBomb__11daDaiocta_cFv */
void daDaiocta_c::modeDamageBomb() {
    /* Nonmatching */
}

/* 00002778-000028FC       .text modeDemoInit__11daDaiocta_cFv */
void daDaiocta_c::modeDemoInit() {
    /* Nonmatching */
}

/* 000028FC-00003150       .text modeDemo__11daDaiocta_cFv */
void daDaiocta_c::modeDemo() {
    /* Instruction match */
    current.pos.y = field_0x2430;
    fopAc_ac_c* ship_p_1 = fopAcM_SearchByName(PROC_SHIP);
    field_0x21F4 = ship_p_1->current.pos;
    field_0x2200 = ship_p_1->current.angle;

    if (eventInfo.checkCommandDemoAccrpt()) {
        int staff_id = dComIfGp_evmng_getMyStaffId("Daiocta");
        char* cut_name = dComIfGp_getPEvtManager()->getMyNowCutName(staff_id);

        cXyz pos = current.pos;
        s16 o_angle;
        dComIfGp_getMapTrans(fopAcM_GetRoomNo(this), &pos.x, &pos.z, &o_angle);

        s16 target = cLib_targetAngleY(&current.pos, &pos);
        cLib_distanceAngleS(shape_angle.y, target);

        if (strcmp(cut_name, "SUIKOMI1") == 0) {
            field_0x0571 = 6;
            if (field_0x0571 == 6) {
                mDoAud_seStart(JA_SE_CM_DO_SUCK_IN, &field_0x2434, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            } 
            f32 dist = (field_0x2434 - field_0x21F4).absXZ();
            if (dist < 80.0f) {
                dComIfGp_evmng_cutEnd(staff_id);
            } else if (mpMorf->getFrame() == 50.0f) {
                mpMorf->setFrame(40.0f);
            }

            if (REG12_S(0) != 0) {
                return;
            }

            s16 target_angle_y = cLib_targetAngleY(&current.pos, &ship_p_1->current.pos);
            s32 distance_angle_s = cLib_distanceAngleS(shape_angle.y + l_HIO.field_0x014, target_angle_y);
            cLib_addCalc2(&field_0x2208, l_HIO.field_0x088, l_HIO.field_0x090, l_HIO.field_0x08C);
            cLib_chaseF(&field_0x21F4.x, field_0x2434.x, field_0x2208 / 2.0f);
            cLib_chaseF(&field_0x21F4.z, field_0x2434.z, field_0x2208);
            cLib_addCalcAngleS2(&field_0x2200.y, target_angle_y + 0x8000, 8, 0x400);

            if (distance_angle_s < l_HIO.field_0x012) {
                target_angle_y = target_angle_y + 0x4000;
                f32 dist = (current.pos - ship_p_1->current.pos).absXZ();
                field_0x21F4.z += (dist / (REG12_F(1) + 60.0f)) * cM_scos(target_angle_y);
                field_0x21F4.x += (dist / (REG12_F(1) + 60.0f)) * cM_ssin(target_angle_y);
            }

            // again?
            daShip_c* ship_p_2 = (daShip_c *) fopAcM_SearchByName(PROC_SHIP);
            ship_p_2->initStartPos(&field_0x21F4, field_0x2200.y);
        }

        if (strcmp(cut_name, "SUIKOMI2") == 0) {
            if (mpMorf->getFrame() == 65.0f) {
                fopAcM_seStart(this, JA_SE_CM_DO_SUCK_IN_FIN, 0);
            }
            s16 target_angle_y = cLib_targetAngleY(&current.pos, &ship_p_1->current.pos); 
            cLib_distanceAngleS(shape_angle.y, target_angle_y);
            cLib_chasePosXZ(&field_0x21F4, current.pos, field_0x2208);
            cLib_addCalcAngleS2(&field_0x2200.y, target_angle_y + 0x8000, 4, 0x800);
            
            // here too?
            daShip_c* ship_p_2 = (daShip_c *) fopAcM_SearchByName(PROC_SHIP);
            ship_p_2->initStartPos(&field_0x21F4, field_0x2200.y);

            f32 dist = (current.pos - field_0x21F4).absXZ();
            if (dist < 10.0f && (mpMorf->isStop() || field_0x0571 == 2)) {
                shape_angle.y = target;
                mpMorf->calc();
                current.pos = field_0x220C;
                ship_p_2->initStartPos(&current.pos, target);
                dComIfGp_evmng_cutEnd(staff_id);
            }
        }

        if (strcmp(cut_name, "HAKIDASU") == 0) {
            fopAc_ac_c* actor_p = fopAcM_SearchByID(field_0x26C4);
            actor_p->current.pos = current.pos;
            actor_p->current.pos.y += 20.0f;
            if (s32(mpMorf->getFrame()) == 26) {
                mDoAud_seStart(JA_SE_CV_DO_SPIT_SHIP, &field_0x2434, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            }

            if (field_0x0571 == 8 && mpMorf->isStop()) {
                dComIfGp_evmng_cutEnd(staff_id);
                mDoAud_subBgmStop();
            } else if (mpMorf->getFrame() < 10.0f) {
                ((daShip_c *)ship_p_1)->initStartPos(&field_0x2434, target);
            }
            field_0x0571 = 8;
        }

        if (strcmp(cut_name, "WAIT") == 0) {
            field_0x0571 = 2;
        }

        if (dComIfGp_evmng_endCheck("DAIOCTA_SUIKOMI")) {
            if (field_0x0575 == 0xFF) {
                daPy_getPlayerLinkActorClass()->startRestartRoom(6, 0xC9, -1.0f, 1);
            } else {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), field_0x0575, fopAcM_GetRoomNo(this), -1, 0.0f, 6);
            }
        }
    } else {
        fopAcM_orderOtherEvent2(this, "DAIOCTA_SUIKOMI", dEvtFlag_NOPARTNER_e);
    }
}

/* 00003150-00003284       .text modeDeleteInit__11daDaiocta_cFv */
void daDaiocta_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 00003284-000036A8       .text modeDelete__11daDaiocta_cFv */
void daDaiocta_c::modeDelete() {
    /* Nonmatching */
}

/* 000036A8-00003888       .text modeProc__11daDaiocta_cFQ211daDaiocta_c6Proc_eQ211daDaiocta_c6Mode_e */
void daDaiocta_c::modeProc(daDaiocta_c::Proc_e i_procType, daDaiocta_c::Mode_e i_modeProc) {
    /* Instruction match */
    static ModeEntry mode_tbl[7] = {
        { &daDaiocta_c::modeWaitInit,       &daDaiocta_c::modeWait,       "WAIT"        },
        { &daDaiocta_c::modeHideInit,       &daDaiocta_c::modeHide,       "HIDE"        },
        { &daDaiocta_c::modeAppearInit,     &daDaiocta_c::modeAppear,     "APPEAR"      },
        { &daDaiocta_c::modeDamageInit,     &daDaiocta_c::modeDamage,     "DAMAGE"      },
        { &daDaiocta_c::modeDamageBombInit, &daDaiocta_c::modeDamageBomb, "DAMAGE_BOMB" },
        { &daDaiocta_c::modeDeleteInit,     &daDaiocta_c::modeDelete,     "DELETE"      },
        { &daDaiocta_c::modeDemoInit,       &daDaiocta_c::modeDemo,       "DEMO"        }
    };

    if (i_procType == PROC_INIT) {
        field_0x056C = i_modeProc;
        (this->*mode_tbl[field_0x056C].mInitFunc)();
    } else if (i_procType == PROC_EXEC) {
        (this->*mode_tbl[field_0x056C].mUpdFunc)();
    }
}

/* 00003888-00003AF4       .text setAnm__11daDaiocta_cFv */
void daDaiocta_c::setAnm() {
    /* Nonmatching */

}

/* 00003AF4-00003B20       .text setWater__11daDaiocta_cFv */
void daDaiocta_c::setWater() {
    if (field_0x2218.m_sea_height != -G_CM3D_F_INF) {
        field_0x2430 = field_0x2218.m_sea_height;
    } else {
        field_0x2430 = 0.0f;
    }
}

/* 00003B20-00003D20       .text _execute__11daDaiocta_cFv */
bool daDaiocta_c::_execute() {
    /* Nonmatching */
}

/* 00003D20-00003E58       .text drawAwa__11daDaiocta_cFv */
void daDaiocta_c::drawAwa() {
    /* Nonmatching */
}

/* 00003E58-00003F4C       .text drawSuikomi__11daDaiocta_cFv */
void daDaiocta_c::drawSuikomi() {
    /* Nonmatching */
}

/* 00003F4C-0000412C       .text drawDebug__11daDaiocta_cFv */
void daDaiocta_c::drawDebug() {
    /* Instruction match */
    fopAc_ac_c* player_p;
    for (int i = 0; i < ARRAY_SSIZE(field_0x0290); i++) {
        player_p = dComIfGp_getPlayer(0);
        f32 fVar1 = (player_p->current.pos - field_0x0290[i]).abs();
        (void) fVar1;
    }
    cXyz sp30 = current.pos;
    sp30.y = 50.0f + field_0x2430;

    u32 uVar1 = l_HIO.field_0x012;
    if (uVar1 - 0x70000 != 0xFFFF || l_HIO.field_0x012 != 0) {
        u32 uVar2 = shape_angle.y + l_HIO.field_0x014;
        s16 sVar1 = shape_angle.y + l_HIO.field_0x014 + uVar1;

        cXyz sp24 = current.pos;
        sp24.z += l_HIO.field_0x084 * cM_scos(sVar1);
        sp24.x += l_HIO.field_0x084 * cM_ssin(sVar1);

        cXyz sp18 = current.pos;
        sp18.z += l_HIO.field_0x084 * cM_scos(uVar2 - uVar1);
        sp18.x += l_HIO.field_0x084 * cM_ssin(uVar2 - uVar1);
    }
}

/* 0000412C-00004244       .text _draw__11daDaiocta_cFv */
bool daDaiocta_c::_draw() {
    if (l_HIO.field_0x004) {
        drawDebug();
    }

    if (field_0x056C == MODE_WAIT) {
        return true;
    } 
    
    if (field_0x056C == MODE_DEMO) {
        drawSuikomi();
    }
    
    if (field_0x056C == MODE_DELETE) {
        drawAwa();
    }

    J3DModel* morf_model_p = mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, fopAcM_GetPosition_p(this), &tevStr);
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    field_0x058C.entry(morf_model_p->getModelData());

    if (l_HIO.field_0x005 == 0) {
        mpMorf->entryDL();
    }

    field_0x058C.remove(morf_model_p->getModelData());

    dSnap_RegistFig(DSNAP_TYPE_UNKC6, this, 1.0f, 1.0f, 1.0f);

    return true;
}

/* 00004244-00004364       .text getArg__11daDaiocta_cFv */
void daDaiocta_c::getArg() {
    /* Instruction match */
    u8 temp;
    s16 prm2;
    u32 prm;

    prm = fopAcM_GetParam(this);
    prm2 = home.angle.z;

    field_0x0573 = prm;
    temp = prm >> 0x8;
    field_0x0575 = prm >> 0x10;
    mSwitchNo = prm >> 0x18;
    field_0x057C = prm2;

    home.angle.z = 0;
    current.angle.z = 0;
    shape_angle.z = 0;

    if (temp == 0xFF) {
        field_0x0578 = l_HIO.field_0x078;
    } else {
        field_0x0578 = f32(temp) * 100.0f;
    }

    if (field_0x0573 > 3) {
        field_0x0573 = 0;
    }

    switch (field_0x0573) {
        case 0:
            field_0x2470[0] = 1;
            field_0x2470[1] = 1;
            field_0x2470[2] = 1;
            field_0x2470[5] = 1;
            break;
        case 1:
            for (int i = 0; i < 8; i++) {
                field_0x2470[i] = 1;
            }
            break;
        case 2:
            for (int i = 0; i < ARRAY_SSIZE(field_0x2470); i++) {
                field_0x2470[i] = 1;
            }
            break;
    }
}

/* 00004364-00004660       .text createInit__11daDaiocta_cFv */
void daDaiocta_c::createInit() {
    /* Instruction match */
    field_0x220C = current.pos;
    initAwa();
    modeProc(PROC_INIT, MODE_WAIT);
    initMtx();
    attention_info.flags = 0;
    shape_angle = current.angle;

    field_0x04E0[0] = 21;
    field_0x04E0[1] = 22;
    field_0x04E0[2] = 15;
    field_0x04E0[3] = 23;
    field_0x04E0[4] = 24;
    field_0x04E0[5] = 16;
    field_0x04E0[6] = 17;
    field_0x04E0[7] = 18;
    field_0x04E0[8] = 14;
    field_0x04E0[9] = 11;
    field_0x04E0[10] = 12;
    field_0x04E0[11] = 13;

    static const int NUM_JOINT_NODES = 37;
    for (int i = 0; i < NUM_JOINT_NODES; i++) {
        mpMorf->getModel()
            ->getModelData()
            ->getJointNodePointer(i)
            ->setCallBack(nodeControl_CB);
    }

    field_0x23DC.SetWall(30.0f, 30.0f);
    field_0x2218.Set(
        fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), 
        this, 1, &field_0x23DC, fopAcM_GetSpeed_p(this)
    );
    field_0x2218.SetWallNone();
    field_0x2218.SetRoofNone();
    field_0x2218.OnSeaCheckOn();
    field_0x2218.OnSeaWaterHeight();

    cullMtx = mpMorf->getModel()->getBaseTRMtx();

    fopAcM_setCullSizeBox(
        this, 
        -2300.0f, -500.0f, -2300.0f, 
        2300.0f, 2300.0f, 2300.0f
    );

    fopAcM_setCullSizeFar(this, 10.0f);

    for (int i = 0; i < ARRAY_SSIZE(field_0x2440); i++) {
        if (field_0x2470[i] == 1) {
            field_0x2440[i] = fopAcM_createChild(
                PROC_DAIOCTA_EYE, fpcM_GetID(this), 
                -1, &current.pos, 
                tevStr.mRoomNo, NULL
            );
        }
    }
    
    field_0x26C4 = fopAcM_create(PROC_Obj_Auzu, 0x1100FF, &current.pos, tevStr.mRoomNo);
    field_0x2164.Init(0, 0, this);

    for (int i = 0; i < ARRAY_SSIZE(field_0x05A4); i++) {
        field_0x05A4[i].Set(m_sph_src);
        field_0x05A4[i].SetStts(&field_0x2164);
        field_0x05A4[i].SetCoHitCallback(coHit_CB);
    }

    for (int i = 0; i < ARRAY_SSIZE(field_0x0CAC); i++) {
        field_0x0CAC[i].Set(m_cps_src);
        field_0x0CAC[i].SetStts(&field_0x2164);
        field_0x0CAC[i].SetCoHitCallback(coHit_CB);
    }

    field_0x0571 = 1;
}

/* 00004660-00004918       .text _create__11daDaiocta_cFv */
cPhs_State daDaiocta_c::_create() {
    fopAcM_SetupActor(this, daDaiocta_c);
    cPhs_State state = dComIfG_resLoad(&field_0x0580, m_arc_name);

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
    dComIfG_resDelete(&field_0x0580, m_arc_name);
    field_0x241C.remove();
    fopAc_ac_c* actor_p;
    for (int i = 0; i < ARRAY_SSIZE(field_0x2440); i++) {
        if (fopAcM_SearchByID(field_0x2440[i], &actor_p)) {
            fopAcM_delete(actor_p);
        }
    }

    mDoAud_seDeleteObject(&field_0x2434);

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
