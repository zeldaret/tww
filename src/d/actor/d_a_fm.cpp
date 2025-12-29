/**
 * d_a_fm.cpp
 * Enemy - Floormaster
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_fm.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_lib.h"
#include "d/d_jnt_hit.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_tsubo.h"
#include "d/actor/d_a_npc_cb1.h"
#include "d/actor/d_a_npc_md.h"
#include "d/d_s_play.h"
#include "d/d_a_obj.h"
#include "d/res/res_fm.h"
#include "d/actor/d_a_player_main_data.h"


const u32 daFm_c::m_heapsize = 0x2100;
const char daFm_c::m_arc_name[] = "Fm";

const dCcD_SrcSph daFm_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_UNK8 & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
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
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};


const dCcD_SrcCyl daFm_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
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
        /* Radius */ 60.0f,
        /* Height */ 0.0f,
    }},
};

class daFm_HIO_c : public mDoHIO_entry_c{
public:
    daFm_HIO_c();
    virtual ~daFm_HIO_c() {};
    void genMessage(JORMContext* ctx) {}

public:
    /* 0x004 */ s8 field_0x004;
    /* 0x005 */ s8 field_0x005;
    /* 0x006 */ s8 field_0x006;
    /* 0x007 */ s8 field_0x007;
    /* 0x008 */ s8 field_0x008;
    /* 0x009 */ u8 field_0x009;
    /* 0x00A */ s8 field_0x00A;
    /* 0x00B */ s8 field_0x00B;
    /* 0x00C */ s8 field_0x00C;
    /* 0x00D */ u8 field_0x00D;
    /* 0x00E */ s8 field_0x00E;
    /* 0x00F */ u8 field_0x00F[6];
    /* 0x015 */ s8 field_0x015[10];
    /* 0x01F */ u8 field_0x01F;
    /* 0x020 */ cXyz field_0x020;
    /* 0x02C */ cXyz field_0x02C;
    /* 0x038 */ cXyz field_0x038;
    /* 0x044 */ f32 field_0x044;
    /* 0x048 */ f32 field_0x048;
    /* 0x04C */ f32 field_0x04C;
    /* 0x050 */ f32 field_0x050;
    /* 0x054 */ f32 field_0x054;
    /* 0x058 */ f32 field_0x058;
    /* 0x05C */ s16 field_0x05C;
    /* 0x05E */ s16 field_0x05E;
    /* 0x060 */ s16 field_0x060;
    /* 0x062 */ s16 field_0x062;
    /* 0x064 */ s16 mMaxHealth;
    /* 0x066 */ s16 field_0x066;
    /* 0x068 */ s16 field_0x068;
    /* 0x06A */ s16 field_0x06A;
    /* 0x06C */ f32 mSpAttackVJumpHeight;
    /* 0x070 */ f32 mSpAttackVJumpRadius;
    /* 0x074 */ s16 mSpAttackVJumpStartFrame;
    /* 0x076 */ s16 mSpAttackVJumpEndFrame;
    /* 0x078 */ f32 mSpAttackJumpHeight;
    /* 0x07C */ f32 mSpAttackJumpRadius;
    /* 0x080 */ s16 mSpAttackJumpStartFrame;
    /* 0x082 */ s16 mSpAttackJumpEndFrame;
    /* 0x084 */ s16 field_0x084;
    /* 0x086 */ s16 field_0x086;
    /* 0x088 */ s16 field_0x088;
    /* 0x08A */ s16 field_0x08A;
    /* 0x08C */ s16 field_0x08C;
    /* 0x08E */ s16 field_0x08E;
    /* 0x090 */ s16 field_0x090;
    /* 0x092 */ s16 field_0x092;
    /* 0x094 */ s16 field_0x094;
    /* 0x096 */ s16 field_0x096;
    /* 0x098 */ s16 field_0x098;
    /* 0x09A */ s16 field_0x09A;
    /* 0x09C */ s16 field_0x09C;
    /* 0x09E */ s16 field_0x09E;
    /* 0x0A0 */ s16 field_0x0A0;
    /* 0x0A2 */ s16 field_0x0A2;
    /* 0x0A4 */ s16 field_0x0A4;
    /* 0x0A6 */ s16 field_0x0A6;
    /* 0x0A8 */ f32 field_0x0A8;
    /* 0x0AC */ f32 field_0x0AC;
    /* 0x0B0 */ f32 field_0x0B0;
    /* 0x0B4 */ f32 field_0x0B4;
    /* 0x0B8 */ f32 field_0x0B8;
    /* 0x0BC */ f32 field_0x0BC;
    /* 0x0C0 */ f32 field_0x0C0;
    /* 0x0C4 */ f32 field_0x0C4;
    /* 0x0C8 */ f32 field_0x0C8;
    /* 0x0CC */ f32 field_0x0CC;
    /* 0x0D0 */ f32 field_0x0D0;
    /* 0x0D4 */ f32 field_0x0D4;
    /* 0x0D8 */ f32 field_0x0D8;
    /* 0x0DC */ f32 field_0x0DC;
    /* 0x0E0 */ f32 field_0x0E0;
    /* 0x0E4 */ f32 field_0x0E4;
    /* 0x0E8 */ f32 field_0x0E8;
    /* 0x0EC */ f32 field_0x0EC;
    /* 0x0F0 */ f32 field_0x0F0;
    /* 0x0F4 */ f32 field_0x0F4;
    /* 0x0F8 */ f32 field_0x0F8;
    /* 0x0FC */ f32 field_0x0FC;
    /* 0x100 */ s16 field_0x100;
    /* 0x102 */ u8 field_0x102[0x104 - 0x102];
    /* 0x104 */ cXyz field_0x104;
    /* 0x110 */ f32 field_0x110;
    /* 0x114 */ f32 field_0x114;
    /* 0x118 */ f32 field_0x118;
    /* 0x11C */ s16 field_0x11C;
    /* 0x11E */ s16 field_0x11E;
    /* 0x120 */ f32 field_0x120;
    /* 0x124 */ f32 field_0x124;
    /* 0x128 */ f32 field_0x128;
    /* 0x12C */ f32 field_0x12C;
    /* 0x130 */ JntHit_HIO_c field_0x130;
};  // Size: 0x15C

static daFm_HIO_c l_HIO;

/* 000000EC-000003EC       .text __ct__10daFm_HIO_cFv */
daFm_HIO_c::daFm_HIO_c() {
    field_0x006 = 0;
    field_0x007 = 0;
    field_0x008 = 0;
    field_0x004 = 0;
    field_0x01F = 0;
    field_0x00B = 0;
    field_0x009 = 0;
    field_0x00A = 0;
    field_0x00C = 0;
    field_0x005 = 0;

    field_0x068 = 0x1e;
    mSpAttackVJumpHeight = 240.0f;
    mSpAttackVJumpRadius = 100.0f;
    mSpAttackVJumpStartFrame = 0;
    mSpAttackVJumpEndFrame = 0xF;
    mSpAttackJumpHeight = 120.0f;
    mSpAttackJumpRadius = 100.0f;
    mSpAttackJumpStartFrame = 5;
    mSpAttackJumpEndFrame = 0xF;
    field_0x11C = 100;
    field_0x00E = 0;
    field_0x00D = 0;
    field_0x062 = 0x78;

    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
                field_0x00F[i] = 1;
                break;

            case 4:
            default:
                field_0x00F[i] = 0;
                break;
        }
    }

    field_0x050 = 0.0f;
    field_0x054 = 0.0f;
    field_0x058 = 0.0f;
    field_0x05C = 0;
    field_0x05E = 0;
    field_0x060 = 0;
    field_0x020.x = -10.0f;
    field_0x020.y = 5.0f;
    field_0x020.z = -10.0f;
    field_0x02C.x = 0.0f;
    field_0x02C.y = 0.0f;
    field_0x02C.z = -30.0f;
    field_0x038.x = 40.0f;
    field_0x038.y = -20.0f;
    field_0x038.z = 0.0f;
    field_0x044 = 0.0f;
    field_0x048 = 0.0f;
    field_0x04C = 0.0f;
    field_0x104.set(0.0f, -20.0f, -0.0f);

    field_0x0A8 = 600.0f;
    mMaxHealth = 0xC;
    field_0x066 = 0x28;
    field_0x084 = 0x5A;
    field_0x086 = 0xF0;
    field_0x088 = 0x3C;
    field_0x08A = 1;
    field_0x08C = 0x3C;
    field_0x08E = 0x78;
    field_0x090 = 10;
    field_0x092 = 0x11;
    field_0x094 = 0;
    field_0x096 = 500;
    field_0x098 = 18000;
    field_0x09A = 7000;
    field_0x0C0 = 15.0f;
    field_0x120 = 0.01f;
    field_0x124 = 1.0f;
    field_0x128 = 0.1f;
    field_0x12C = 0.02f;
    field_0x0C4 = 290.0f;
    field_0x0C8 = 80.0f;
    field_0x0CC = 7.0f;
    field_0x0D0 = 2.0f;
    field_0x0D4 = 5.0f;
    field_0x0D8 = 80.0f;
    field_0x0DC = 100.0f;
    field_0x0E0 = 150.0f;
    field_0x0E4 = 500.0f;
    field_0x0E8 = 800.0f;
    field_0x0EC = 30.0f;
    field_0x0F0 = 25.0f;
    field_0x0F4 = 9.0f;
    field_0x0F8 = -2.5f;
    field_0x0FC = 16.0f;
    field_0x09C = 5;
    field_0x100 = 0x1e;
    field_0x110 = 20.0f;
    field_0x114 = 50.0f;
    field_0x118 = -20.0f;
    field_0x0B0 = 30.0f;
    field_0x0A0 = 0x14;
    field_0x0A2 = 0x96;
    field_0x0B4 = 1000.0f;
    field_0x0B8 = 1000.0f;
    field_0x09E = 0x96;
    field_0x0AC = 300.0f;
    field_0x0BC = 750.0f;
    field_0x0A6 = 10;

    // setall from csxyz
    /* Nonmatching */
}

/* 000003EC-00000438       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int arg1) {
    J3DJoint* joint = (J3DJoint*)node;
    if(arg1 == 0) {
        daFm_c* i_this = (daFm_c*)j3dSys.getModel()->getUserArea();
        if(i_this != NULL) {
            i_this->_nodeControl(joint, j3dSys.getModel());
        }
    }
    return TRUE;
    /* Nonmatching */
}

/* 00000438-00000690       .text _nodeControl__6daFm_cFP7J3DNodeP8J3DModel */
void daFm_c::_nodeControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = static_cast<J3DJoint*>(node);
    int jntNo = joint->getJntNo();

              
    cXyz temp;
    cXyz temp2;
    Mtx mtx;
    MTXCopy(model->getAnmMtx(jntNo), mtx);
    temp.x = mtx[0][3];
    temp.y = mtx[1][3];
    temp.z = mtx[2][3];

    mtx[2][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[0][3] = 0.0f;
    mDoMtx_stack_c::transS(temp);
    if (jntNo < 6 && jntNo >= field_0x390 && l_HIO.field_0x00F[jntNo] == 1) {
        mDoMtx_stack_c::quatM(&field_0x330[jntNo]);
    }
    mDoMtx_stack_c::concat(mtx);

    if (jntNo == 5) {
        if(cLib_calcTimer(&field_0x64C) != 0) {
            field_0x68A += REG12_S(2) + 0x1830;
            cLib_addCalcAngleS2(&field_0x68C, 0, 10, 0x1C8);
            s16 temp3 = field_0x68C *cM_ssin(field_0x68A);

            mDoMtx_stack_c::YrotM(temp3);
        }
        temp2.set(0.0f, 0.0f, 0.0f);

        temp2 = l_HIO.field_0x038;
        mDoMtx_stack_c::multVec(&temp2, &field_0x61C);

        temp2 = l_HIO.field_0x104;
        mDoMtx_stack_c::multVec(&temp2, &field_0x63C);
    }
    if (jntNo < 6) {
        mDoMtx_stack_c::multVecZero(&field_0x2E8[jntNo]); // not temp but as palceholder
    }
    
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    /* Nonmatching */
}

/* 00000690-000006B0       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daFm_c*>(i_this)->_createHeap();
    /* Nonmatching */
}

/* 000006B0-00000718       .text _createHeap__6daFm_cFv */
BOOL daFm_c::_createHeap() {
    if(holeCreateHeap() == false) {
        return false;
    }
    if(bodyCreateHeap() == false) {
        return false;
    }

    return jntHitCreateHeap() ? TRUE : FALSE;
    /* Nonmatching */
}

/* 00000718-0000086C       .text holeCreateHeap__6daFm_cFv */
bool daFm_c::holeCreateHeap() {

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, FM_BDL_YPIT00));
    JUT_ASSERT(0x2C7, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x19001222);
    if(mpModel == NULL) {
        return false;
    }

    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, FM_BTK_YPIT00));
    JUT_ASSERT(0x2D0, btk != NULL);

    if(!mBtkAnm.init(modelData, btk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return false;
    }
    
    return true;
    /* Nonmatching */
}

/* 0000086C-000009CC       .text bodyCreateHeap__6daFm_cFv */
bool daFm_c::bodyCreateHeap() {
    J3DModelData* fmModelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, FM_BDL_FM));
    JUT_ASSERT(0x2DD, fmModelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        fmModelData,
        NULL, NULL,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(m_arc_name, FM_BCK_MODORU)),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x37441422
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return false;
    }

    if (mInvisibleModel.create(mpMorf->getModel()) == 0) {
        return false;
    }
    mpMorf->getModel()->setUserArea((u32)this);
    return true;
    /* Nonmatching */
}

/* 000009CC-00000A30       .text jntHitCreateHeap__6daFm_cFv */
bool daFm_c::jntHitCreateHeap() {
    static Vec hand_sph_offset[] = {20.0f, 0.0f, 0.0f};
    static Vec ude_cyl_offset[] = {{0.0f, 0.0f, 0.0f},    {60.0f, 0.0f, 0.0f}};
    static Vec yubi_cyl_offset[]   = {{0.0f, 0.0f, 0.0f},    {15.0f, 0.0f, 0.0f}};
    static Vec te_cyl2_offset[]     = {{20.0f, 0.0f, 0.0f},    {20.0f, -5.0f, 0.0f}};

    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ JntHitType_CYL2_e,
            /* mJointIndex */ 0x05,
            /* mRadius     */ 22.0f,
            /* mpOffsets   */ te_cyl2_offset,
        },

        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x01,
            /* mRadius     */ 8.0f,
            /* mpOffsets   */ ude_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x02,
            /* mRadius     */ 8.0f,
            /* mpOffsets   */ ude_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x03,
            /* mRadius     */ 8.0f,
            /* mpOffsets   */ ude_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x04,
            /* mRadius     */ 8.0f,
            /* mpOffsets   */ ude_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x06,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x07,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x08,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x09,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0A,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0B,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0C,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0D,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0E,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x0F,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        
    };
    mpJntHit = JntHit_create(mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (mpJntHit) {
        jntHit = mpJntHit;
    } else {
        return false;
    }
    return true;
    /* Nonmatching */
}

/* 00000A30-00000A6C       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
BOOL pathMove_CB(cXyz* param_1, cXyz* param_2, cXyz* param_3, void* i_this) {
    return ((daFm_c*)i_this)->_pathMove(param_1, param_2, param_3   );
    /* Nonmatching */
}

/* 00000A6C-00000D40       .text _pathMove__6daFm_cFP4cXyzP4cXyzP4cXyz */
BOOL daFm_c::_pathMove(cXyz* param_1, cXyz* param_2, cXyz* param_3) {
    field_0x398 = *param_3;
    field_0x3A4 = *param_2;
    cXyz temp = (*param_3 - *param_2).normZP();

    if ((current.pos - *param_1).abs() < l_HIO.field_0x0D4 + 1.0f) {
        f32 temp2 = cM_rndF(9.0f) + 1.0f;
        field_0x394 = cM_rndF(9.0f) + 1.0f;
        *param_1 = *param_1 + temp * l_HIO.field_0x0D8 * temp2;
    }

    if (param_2->abs(*param_1) > param_2->abs(*param_3)) {
        *param_1 = *param_3;
        return true;
    }

    return false;
    /* Nonmatching */
}

/* 00000D40-00000D6C       .text searchNearOtherActor_CB__FPvPv */
void* searchNearOtherActor_CB(void* param_1, void* param_2) {
    return ((daFm_c*)param_2)->searchNearOtherActor((fopAc_ac_c*)param_1);

    /* Nonmatching */
}

/* 00000D6C-00000F18       .text searchNearOtherActor__6daFm_cFP10fopAc_ac_c */
fopAc_ac_c* daFm_c::searchNearOtherActor(fopAc_ac_c* i_actor) {
    if(dComIfGp_event_runCheck()) {
        return NULL;
    }
    if(fopAc_IsActor(i_actor)) {
        if(!checkHeight(i_actor)) {
            return NULL;
        }
        f32 dist = fopAcM_searchActorDistanceXZ(this, i_actor);

        if(dist < l_HIO.field_0x0E4) {
            if(fopAcM_GetName(i_actor) == PROC_BOMB) {
                mpActorTarget = i_actor;
                if(!((daBomb_c*)mpActorTarget)->chk_state(daBomb_c::STATE_0)) {
                    return i_actor;
                }
            } else if(fopAcM_GetName(i_actor) == PROC_TSUBO) {
                daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();

                f32 dist2 = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
                f32 dist3 = fopAcM_searchActorDistanceXZ(i_actor, dComIfGp_getPlayer(0));

                if(dist2 < l_HIO.field_0x0E8) {
                    if(dist3 > REG12_F(0) + 80.0f || fopAcM_GetID(i_actor) == pLink->getGrabActorID()) {
                            switch(((daTsubo::Act_c*)i_actor)->prm_get_type()) {
                                case 0:
                                case 1:
                                case 2:
                                case 4:
                                case 5:
                                case 6:
                                    mpActorTarget = i_actor;
                                    return i_actor;
                            }

                    }
                }
            }
        }
    }
    return NULL;
    /* Nonmatching */
}

/* 00000F18-00000F44       .text searchNearFm_CB__FPvPv */
static void* searchNearFm_CB(void* param_1, void* param_2) {
    ((daFm_c*)param_2)->searchNearFm((fopAc_ac_c*)param_1);
    /* Nonmatching */
}

/* 00000F44-00001150       .text searchNearFm__6daFm_cFP10fopAc_ac_c */
bool daFm_c::searchNearFm(fopAc_ac_c* i_actor) {
    cXyz temp;
    f32 dist;
    if(fopAc_IsActor(i_actor) && fopAc_IsActor(i_actor) && fopAcM_GetName(i_actor) == PROC_FM) { // redundant isactor check?
        // temp = field_0x3E4 - current.pos;
        f32 abs = (field_0x3E4 - current.pos).absXZ();
        dist = fopAcM_searchActorDistanceXZ(this, i_actor);
        if(dist != 0.0f) {
            temp.set(field_0x3E4.x, 0.0f, field_0x3E4.z);
            if(temp.abs() == 0.0) { // double?
                field_0x3E4 = i_actor->current.pos;
            } else if(dist < abs) {
                field_0x3E4 = i_actor->current.pos;
            }
        }
    }
    return false;
    /* Nonmatching */
}

/* 00001150-00001384       .text moveRndBack__6daFm_cFv */
void daFm_c::moveRndBack() {
    s16 angle = cLib_distanceAngleS(shape_angle.y, field_0x9D0); // unused angle
    f32 temp = 100000.0f;

    if(mpActorTarget != NULL) {
        temp = fopAcM_searchActorDistanceXZ(this, mpActorTarget);
    }

    if(field_0x9D4 <= l_HIO.field_0x0E0 || temp <= l_HIO.field_0x0E0) {
        if(!isGrabFoot()) {
            if(cLib_calcTimer(&field_0x648) == 0 || field_0xAE4 == 0 || mAcch.ChkWallHit()) {
                if(field_0xAE4 == 0 || mAcch.ChkWallHit()) {
                    field_0x680 += (s16)(0x5000 + field_0x680 + cM_rndF(3.0f) * 4096.0f);
                } else {
                    field_0x680 = shape_angle.y + 0x3000 + cM_rndF(5.0f) * 4096.0f;
                }
                field_0x394 = cM_rndF(9.0f) + 1.0f;
                field_0x660.z += l_HIO.field_0x0AC * cM_scos(field_0x680);
                field_0x660.x += l_HIO.field_0x0AC * cM_ssin(field_0x680);
                field_0x648 = l_HIO.field_0x0A0;
            }
        }

        
    }
    if(field_0xAE4 != 0 && !mAcch.ChkWallHit()) {
        cLib_addCalcPosXZ2(&current.pos, field_0x660, 0.1f, l_HIO.field_0x0B0);
    }
    /* Nonmatching */
}

/* 00001384-000015F8       .text moveRndEscape__6daFm_cFv */
void daFm_c::moveRndEscape() {
    f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));

    if(cLib_calcTimer(&field_0x648) == 0 || field_0xAE4 == 0 || mAcch.ChkWallHit()) {
        if(dist < l_HIO.field_0x0B4) {
            if(field_0xAE4 == 0 || mAcch.ChkWallHit()) {
                field_0x680 += (s16)(0x5000 + field_0x680 + cM_rndF(3.0f) * 4096.0f);
            } else {
                field_0x680 = shape_angle.y + 0x3000 + cM_rndF(5.0f) * 4096.0f;
            }
            field_0x660.set(field_0x690);
            field_0x660.z += l_HIO.field_0x0B8 * cM_scos(field_0x680);
            field_0x660.x += l_HIO.field_0x0B8 * cM_ssin(field_0x680);
            field_0x648 = l_HIO.field_0x0A0;
        }

        if(cM_rndF(100.0f) < 33.0f) {
            setAnm(0xC, false);
        }
    }

    if(mAnmPrmIdx != 0xc && field_0xAE4 != 0 && !mAcch.ChkWallHit()) {
        cLib_addCalcPosXZ2(&current.pos, field_0x660, (l_HIO.field_0x0CC + 1.0f) *0.005f * field_0x394, l_HIO.field_0x0B0);
        field_0x690.set(current.pos);
    }
    /* Nonmatching */
}

/* 000015F8-00001680       .text spAttackVJump__6daFm_cFv */
void daFm_c::spAttackVJump() {
    initBt(l_HIO.mSpAttackVJumpHeight, l_HIO.mSpAttackVJumpRadius);
    f32 frame = mpMorf->getFrame(); 

    setBtAttackData(l_HIO.mSpAttackVJumpStartFrame, l_HIO.mSpAttackVJumpEndFrame, 700.0f, 3);
    setBtNowFrame(frame);
    /* Nonmatching */
}

/* 00001680-00001708       .text spAttackJump__6daFm_cFv */
void daFm_c::spAttackJump() {
    initBt(l_HIO.mSpAttackJumpHeight, l_HIO.mSpAttackJumpRadius);
    f32 frame = mpMorf->getFrame(); 

    setBtAttackData(l_HIO.mSpAttackJumpStartFrame, l_HIO.mSpAttackJumpEndFrame, 700.0f, 1);
    setBtNowFrame(frame);
    /* Nonmatching */
}

/* 00001708-00001738       .text spAttackNone__6daFm_cFv */
void daFm_c::spAttackNone() {
    setBtAttackData(100.0f, 100.0f, 10000.0f, 0);
    setBtNowFrame(0.0f);
    /* Nonmatching */
}

/* 00001738-000017CC       .text iceProc__6daFm_cFv */
void daFm_c::iceProc() {
    setAttention();
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    if(mEnemyIce.mLightShrinkTimer != 0 || health <= 0) {
        setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x128);
    }

    holeSetMtx();
    cancelGrab();
    /* Nonmatching */
}

/* 000017CC-00001864       .text bodySetMtx__6daFm_cFv */
void daFm_c::bodySetMtx() {
    J3DModel* pModel = mpMorf->getModel();
    pModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::transM(field_0x610);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    /* Nonmatching */
}

/* 00001864-00001920       .text holeSetMtx__6daFm_cFv */
void daFm_c::holeSetMtx() {
    Vec scale = {field_0x3E0, field_0x3E0, field_0x3E0};
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::transM(l_HIO.field_0x020);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    /* Nonmatching */
}

/* 00001920-00001A50       .text setCollision__6daFm_cFv */
void daFm_c::setCollision() {
    if(isBodyAppear()) { 
        if(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK400_e | daPyStts0_UNK2_e)) {
            mSph.SetR(l_HIO.field_0x0C8 * 1.5f);
        } else {
            mSph.SetR(l_HIO.field_0x0C8);
        }
        mSph.SetC(field_0x61C);
        dComIfG_Ccsp()->Set(&mSph);
    }

    if(isHoleAppear()) {
        mCyl.SetR(field_0x3E0);
        mCyl.SetH(150.0f);
        mCyl.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
    }
    /* Nonmatching */
}

/* 00001A50-00001C90       .text setAttention__6daFm_cFv */
void daFm_c::setAttention() {
    if(field_0x2E4 != 0) {
        attention_info.position = current.pos;
        eyePos = current.pos;
        
    } else {
        if(mMode == 0xe || mMode == 0x10 || mMode == 0xf || (mMode == 0 || mMode == 0x11)) {
            attention_info.position = current.pos;
            eyePos = current.pos;
        } else {
            attention_info.position = field_0x61C;
            attention_info.position.y += 20.0f;
            daPy_py_c* pLink = daPy_getPlayerActorClass(); // maybe just put it immediately in
            f32 abs = (pLink->getHeadTopPos() - field_0x61C).abs();
            if(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK400_e | daPyStts0_UNK2_e)) {
                eyePos = field_0x61C;
            } else {
                if(mMode == 8) {
                    if(abs > l_HIO.field_0x0EC) {
                        eyePos = field_0x61C;
                    } else {
                        eyePos = current.pos;
                        eyePos.y += 200.0f;
                    }
                } else {
                    eyePos = field_0x61C;
                }
            }
        }
    }
    /* Nonmatching */
}

/* 00001C90-00002530       .text checkTgHit__6daFm_cFv */
bool daFm_c::checkTgHit() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    mStts2.Move();
    bool temp;

    if(cLib_calcTimer(&field_0x9C4) == 0 && mSph.ChkTgHit()) {
        temp = true;
        cXyz* hitPos = mSph.GetTgHitPosP();
        cCcD_Obj* hitObj = mSph.GetTgHitObj();
        field_0x9C4 = l_HIO.field_0x09C;

        if(hitObj == NULL) {
            return false;
        }
        switch (hitObj->GetAtType()) {
            case AT_TYPE_SWORD:
            case AT_TYPE_MACHETE:
            case AT_TYPE_UNK800:
            case AT_TYPE_DARKNUT_SWORD:
            case AT_TYPE_MOBLIN_SPEAR:
                fopAcM_seStart(this, JA_SE_LK_SW_HIT_S, 0x20);
                switch(player->getCutType()) {
                    case 0x10:
                        mHitType = 0xC;
                        break;
                    case 0x05:
                    case 0x06:
                    case 0x07:
                    case 0x08:
                    case 0x09:
                    case 0x0A:
                    case 0x0C:
                    case 0x0E:
                    case 0x0F:
                    case 0x15:
                    case 0x17:
                    case 0x19:
                    case 0x1A:
                    case 0x1B:
                        mHitType = 1;
                        break;
                    default:
                        mHitType = 0;
                        break;
                }
                break;
            case AT_TYPE_WIND:
                temp = false;
                mHitType = 3;
                break;

            case AT_TYPE_BOOMERANG:
            case AT_TYPE_BOKO_STICK:
                fopAcM_seStart(this, JA_SE_LK_W_WEP_HIT, 0x44);
                temp = false;
                mHitType = 4;
                dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &attention_info.position);
                fopAcM_monsSeStart(this, JA_SE_CV_FM_DAMAGE, 0);
                modeProcInit(0x13);
                break;

            case AT_TYPE_HOOKSHOT:
                fopAcM_seStart(this, JA_SE_LK_HS_SPIKE, 0x44);
                temp = false;
                mHitType = 5;
                modeProcInit(10);
                break;

            case AT_TYPE_SKULL_HAMMER:
            case AT_TYPE_STALFOS_MACE:
                fopAcM_seStart(this, JA_SE_LK_HAMMER_HIT, 0x20);
                mHitType = 8;
                if(player->getCutType() == 0x11) {
                    mHitType = 9;
                }
                break;
            case AT_TYPE_BOMB:
                mHitType = 7;
                break;

            case AT_TYPE_ICE_ARROW:
                temp = false;
                fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x20);
                mEnemyIce.mFreezeDuration = l_HIO.field_0x062; // likely freeze duration
                mHitType = 10;
                modeProcInit(7);
                break;

            case AT_TYPE_LIGHT_ARROW:
                temp = false;
                fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x20);
                mEnemyIce.mLightShrinkTimer = 1;
                mHitType = 0xB;
                break;

            case AT_TYPE_FIRE_ARROW:
            case AT_TYPE_NORMAL_ARROW:
                fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x20);
                mHitType = 6;
                break;

            case AT_TYPE_GRAPPLING_HOOK:
                fopAcM_monsSeStart(this, JA_SE_CV_FM_DAMAGE, 0);
                dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &attention_info.position);
                fopAcM_seStart(this, JA_SE_LK_W_WEP_HIT, 0x44);
                mHitType = 0xD;
                temp = false;
                break;

        }
        CcAtInfo atInfo;
        atInfo.pParticlePos = NULL;
        atInfo.mpObj = mSph.GetTgHitObj();

        if (temp) {
            cc_at_check(this, &atInfo);

            if (mHitType == 1 || mHitType == 8 || mHitType == 9 || mHitType== 0xc || health <= 0) { // maybe temp u8
                dComIfGp_particle_set(dPa_name::ID_COMMON_0010, hitPos);
                cXyz temp2(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, hitPos, &player->shape_angle, &temp2);

                if (health <= 0) {
                    fopAcM_monsSeStart(this, JA_SE_CV_FM_DIE, 0);
                } else {
                    fopAcM_monsSeStart(this, JA_SE_CV_FM_DAMAGE, 0);
                }

                if (mHitType == 0xc || mHitType == 8) {
                    modeProcInit(0x14);
                    return 1;
                }

                if (health <= 0) {
                    modeProcInit(0x0C);
                } else {
                    modeProcInit(10);
                }
            } else {
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, hitPos, &player->shape_angle);

                fopAcM_monsSeStart(this, JA_SE_CV_FM_DAMAGE, 0);
                modeProcInit(10);
            }
        } else if (mHitType == 0xD) {
            modeProcInit(10);
            s8 oldHealth = health;
            health = 10;
            cc_at_check(this, &atInfo);
            health = oldHealth;
            setAnm(1, false);
            field_0x64C = 0x28;
            field_0x68C = 0x2b00;
        }
        return true;
    }

    return false;
    /* Nonmatching */
}

/* 00002530-000026A0       .text setGrabPos__6daFm_cFv */
void daFm_c::setGrabPos() {
    daBomb_c* bomb = (daBomb_c*)mpActorTarget;
    if (bomb == NULL) {
        mGrabPos = current.pos;
    } else {
        if (fopAcM_GetName(bomb) == PROC_BOMB && bomb->chk_state(daBomb_c::STATE_0)) {
            mGrabPos = current.pos;
            return;
        }

        if (isLink(mpActorTarget)) {
            mGrabPos = daPy_getPlayerLinkActorClass()->getHeadTopPos() + getOffsetPos();
        } else {
            if (isNpc(mpActorTarget)) {
                mGrabPos = mpActorTarget->current.pos + getOffsetPos();
            }
            else {
                mGrabPos = mpActorTarget->current.pos + getOffsetPos();
            }
        }
    }
    /* Nonmatching */
}

/* 000026A0-00002868       .text getOffsetPos__6daFm_cFv */
cXyz daFm_c::getOffsetPos() {
    cXyz offset(0.0f, 0.0f, 0.0f);

    if(isLink(mpActorTarget)) {
        offset.set(0.0f, -10.0f, 0.0f);
    } else {

        s16 procName = fopAcM_GetName(mpActorTarget);
        if(procName == PROC_NPC_CB1) {
            if(fopAcM_checkCarryNow(mpActorTarget)) {
                offset.set(0.0f, 20.0f, 0.0f);
            } else {
                offset.set(0.0f, 80.0f, 0.0f);
            }

        } else if(procName == PROC_NPC_MD) {
            if(fopAcM_checkCarryNow(mpActorTarget)) {
                offset.set(0.0f, 20.0f, 0.0f);
            } else {
                offset.set(0.0f, 140.0f, 0.0f);
            }

        } else if(procName == PROC_BOMB) {
            offset.set(0.0f, 80.0f, 0.0f);

        } else if(procName == PROC_TSUBO) {

            switch(((daTsubo::Act_c*)mpActorTarget)->prm_get_type()) {
                case 5:
                case 0:
                    offset.set(0.0f, 80.0f, 0.0f);
                    break;

                case 4:
                case 6:
                    offset.set(0.0f, 80.0f, 0.0f);
                    break;
                    
                case 1:
                case 2:
                    offset.set(0.0f, 90.0f, 0.0f);
                    break;
            }
        }
    }
    return offset;
    /* Nonmatching */
}

/* 00002868-000028D4       .text checkPlayerGrabBomb__6daFm_cFv */
u8 daFm_c::checkPlayerGrabBomb() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    fopAc_ac_c* ac = fopAcM_SearchByID(pLink->getGrabActorID());
    if(ac == NULL) {
        return false;
    }
    return fopAcM_GetName(ac) == PROC_BOMB;
    /* Nonmatching */
}

/* 000028D4-00002954       .text checkPlayerGrabNpc__6daFm_cFv */
u8 daFm_c::checkPlayerGrabNpc() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    fopAc_ac_c* ac = fopAcM_SearchByID(pLink->getGrabActorID());
    if(ac == NULL) {
        return false;
    }
    return isNpc(ac) != 0; // is this real?
    /* Nonmatching */
}

/* 00002954-000029A8       .text checkPlayerGrabTarget__6daFm_cFv */
u8 daFm_c::checkPlayerGrabTarget() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    return pLink->getGrabActorID() == mProcId;
    /* Nonmatching */
}

/* 000029A8-00002CEC       .text isGrabPos__6daFm_cFv */
bool daFm_c::isGrabPos() {
    bool temp;
    if(mpActorTarget == NULL) {
        return false;
    }

    f32 abs = (mGrabPos - current.pos).absXZ();

    if(fopAcM_checkCarryNow(mpActorTarget)) {
        if(checkPlayerGrabBomb() == 1) {
            return false;
        }
        if(checkPlayerGrabTarget() != 1) {
            return false;
        }
    }

    if(isLink(mpActorTarget)) {
        daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();

        
        if(pLink->checkCarryActionNow() || pLink->getGrabActorID() != -1) {
            return false;
        }

        if(isLinkControl()) {
            return false;
        }
    }


    if(isLink(mpActorTarget)) {
        if(abs <= l_HIO.field_0x0E0) {
            return false;
        }
    } else if(abs <= l_HIO.field_0x0E0 || abs > l_HIO.field_0x0E4) {
        return false;
    }

    if(std::fabsf(mGrabPos.y - current.pos.y) > l_HIO.field_0x0A8) {
        return false;
    }
    if(cLib_distanceAngleS(shape_angle.y, cLib_targetAngleY(&current.pos, &mGrabPos)) > l_HIO.field_0x098) {
        return false;
    }
    if(field_0x2D0 == 0) {
        if((field_0x69C - mGrabPos).absXZ() > field_0x2E0) {
            return false;
        }
    }
    return true;

    /* Nonmatching */
}

/* 00002CEC-00002E7C       .text isGrab__6daFm_cFv */
bool daFm_c::isGrab() {
    if(mpActorTarget == NULL) {
        return false;
    }
    
    if(isLink(mpActorTarget) && (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK100_e) || checkPlayerGrabBomb())) {
        return false;
    }

    if(std::fabsf(mGrabPos.y - current.pos.y) > l_HIO.field_0x0A8) {
        return false;
    }

    cXyz temp = mGrabPos - field_0x61C;
    f32 temp2 = l_HIO.field_0x0EC;
    if(field_0x2E4 != 0) {
        temp2 = l_HIO.field_0x0EC * 2.0f;
    }
    if(temp.abs() > temp2) {
        return false;
    }
    return true;
    /* Nonmatching */
}

/* 00002E7C-00002F98       .text isGrabFoot__6daFm_cFv */
bool daFm_c::isGrabFoot() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    if(std::fabsf(current.pos.y - pLink->current.pos.y) > 10.0f) {
        return false;
    }
    if(fopAcM_searchActorDistanceXZ(this, pLink) > l_HIO.field_0x0DC) {
        return false;
    }
    if(pLink->speedF > 4.0f) {
        return false;
    }
    if(pLink->checkPlayerFly() || pLink->checkFrontRoll() || pLink->getGrabActorID() != -1 || isLinkControl()) {
        return false;
    }
    return true;
    /* Nonmatching */
}

/* 00002F98-00002FDC       .text modeSwWaitInit__6daFm_cFv */
void daFm_c::modeSwWaitInit() {
    setAnm(8, false);
    field_0x3E0 = l_HIO.field_0x120;
    /* Nonmatching */
}

/* 00002FDC-000031B0       .text modeSwWait__6daFm_cFv */
void daFm_c::modeSwWait() {
    resetInvKine();
    if(!dComIfGs_isSwitch(field_0x2D4, fopAcM_GetRoomNo(this))) {
        return;
    }

    if(field_0x2E4 != 0) {
        setHoleScale(l_HIO.field_0x124, 0.1f, l_HIO.field_0x128);
        if(eventInfo.mCommand == dEvtCmd_INDEMO_e) {
            if(field_0x2E4 != 0 && cLib_calcTimer(&field_0x650) != 0) {
                return;
            }
        } else {
            if(dComIfGp_evmng_startCheck("DEFAULT_FM_SW_APEEAR") == 0) {
                fopAcM_orderOtherEvent2(this,"DEFAULT_FM_SW_APEEAR",dEvtFlag_NOPARTNER_e);
                return;
            }
        }
    } else {
        if(dComIfGp_evmng_startCheck("DEFAULT_FM_SW_APEEAR") != 0) {
            field_0x2E5 = true;
        }
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    }

    switch(field_0x2D0) {
        case 0:
            modeProcInit(2);
            break;
        case 1:
            if(setHoleScale(l_HIO.field_0x124, 0.1f, l_HIO.field_0x128) != 0) {
                modeProcInit(3);
            }
            break;
        case 2:
            if(setHoleScale(l_HIO.field_0x124, 0.1f, l_HIO.field_0x128) != 0) {
                modeProcInit(4);
            }
            break;
    }

    /* Nonmatching */
}

/* 000031B0-00003200       .text modeHideInit__6daFm_cFv */
void daFm_c::modeHideInit() {
    setAnm(8, false);
    field_0x650 = setRnd(l_HIO.field_0x084,l_HIO.field_0x086);
    /* Nonmatching */
}

/* 00003200-000032E0       .text modeHide__6daFm_cFv */
void daFm_c::modeHide() {
    field_0x690 = current.pos;
    resetInvKine();
    if(setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x128) != 0) {
        current.pos.x = mBaseTarget->current.pos.x;
        current.pos.z = mBaseTarget->current.pos.z;
        if(cLib_calcTimer(&field_0x650) == 0) {
            if(std::fabsf(field_0x69C.y - mBaseTarget->current.pos.y) <=  l_HIO.field_0x0A8 && field_0xAE4 == 1) {
                modeProcInit(2);
            }
        }
    }
    /* Nonmatching */
}

/* 000032E0-00003344       .text modeUnderFootInit__6daFm_cFv */
void daFm_c::modeUnderFootInit() {
    setAnm(8, false);
    field_0x650 = l_HIO.field_0x066;
    current.pos.x = mBaseTarget->current.pos.x;
    current.pos.z = mBaseTarget->current.pos.z;
    field_0x3E0 = l_HIO.field_0x120;  
    /* Nonmatching */
}

/* 00003344-000034E4       .text modeUnderFoot__6daFm_cFv */
void daFm_c::modeUnderFoot() {
    if(cLib_calcTimer(&field_0x648) == 0) {
        field_0x660 = mBaseTarget->current.pos;
        field_0x648 = l_HIO.field_0x08A;
    }
    cLib_addCalcPosXZ2(&current.pos, field_0x660, 0.1f, l_HIO.field_0x0C0);

    field_0x690 = current.pos;
    resetInvKine();
    if(std::fabsf(field_0x69C.y - mBaseTarget->current.pos.y) >  l_HIO.field_0x0A8|| field_0xAE4 == 0) {
        modeProcInit(1);
    } else {
        if(setHoleScale(l_HIO.field_0x124, 0.1f, l_HIO.field_0x12C) != 0) {
            if(cLib_calcTimer(&field_0x650) == 0) {
                if(isGrabFoot() && !dComIfGp_event_runCheck()) {
                    modeProcInit(0xf);
                } else {
                    if(field_0x9D4 < l_HIO.field_0x0E4 && field_0xAE5 == 0) {
                        modeProcInit(5);
                    } else {
                        modeProcInit(1);
                    }
                }
            }
        }
    }
    /* Nonmatching */
}

/* 000034E4-00003528       .text modePathMoveInit__6daFm_cFv */
void daFm_c::modePathMoveInit() {
    setAnm(8, false);
    field_0x3E0 = l_HIO.field_0x124;
    /* Nonmatching */
}

/* 00003528-00003670       .text modePathMove__6daFm_cFv */
void daFm_c::modePathMove() {
    field_0x690 = current.pos;
    resetInvKine();
    turnToBaseTarget();
    if(isGrabFoot() && !dComIfGp_event_runCheck()) {
        modeProc(PROC_0_e,0xf);
    } else {
        
        dLib_pathMove(&field_0x3B0, &field_0x3BC, mpPath, 3.0f, pathMove_CB, this);
        cLib_addCalcPosXZ2(&current.pos, field_0x3B0, (l_HIO.field_0x0D0 + 1.0f) * 0.005f * field_0x394, 20.0f);

        daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
        
        if(field_0x9D4 < l_HIO.field_0x0E4  && std::fabsf(pLink->current.pos.y - current.pos.y) < l_HIO.field_0x0A8 && field_0xAE5 == 0) {
            modeProc(PROC_0_e,5);
        }
    }
    /* Nonmatching */
}

/* 00003670-000036B4       .text modeGoalKeeperInit__6daFm_cFv */
void daFm_c::modeGoalKeeperInit() {
    setAnm(8, false);
    field_0x3E0 = l_HIO.field_0x124;
    /* Nonmatching */
}

/* 000036B4-000038DC       .text modeGoalKeeper__6daFm_cFv */
void daFm_c::modeGoalKeeper() {

    if(field_0x2E5 && dComIfGp_evmng_endCheck("DEFAULT_FM_SUIKOMI_NPC")) {
        modeProc(PROC_0_e,6);
        return;
    }

    resetInvKine();
    turnToBaseTarget();
    if(isGrabFoot() && !dComIfGp_event_runCheck()) {
        modeProc(PROC_0_e, 0xf);
    } else {
        if(field_0x2E4 != 0) {
            modeProc(PROC_0_e, 5);
        } else {
            f32 temp = std::fabsf(current.pos.y - mBaseTarget->current.pos.y);
            if(field_0x9D4 < l_HIO.field_0x0E8 && temp < l_HIO.field_0x0A8) {
                if((mBaseTarget->current.pos - field_0x69C).absXZ() < field_0x2E0 && field_0xAE5 == 0) {
                    modeProc(PROC_0_e,5);
                }
            }
            field_0x690 = field_0x69C;
            cLib_addCalcPosXZ2(&current.pos, field_0x690, (l_HIO.field_0x0CC + 1.0f) *0.005f * field_0x394, 40.0f);
        }
    }
    /* Nonmatching */
}

/* 000038DC-00003938       .text modeAppearInit__6daFm_cFv */
void daFm_c::modeAppearInit() {
    setAnm(2, false);
    field_0x660 = current.pos;
    shape_angle.y = field_0x9D0;
    field_0x650 = 0x1e;
    /* Nonmatching */
}

/* 00003938-00003A00       .text modeAppear__6daFm_cFv */
void daFm_c::modeAppear() {
    if(field_0x2D0 == 0) {
        moveRndBack();
    }
    resetInvKine();
    if(!checkTgHit()) {
        searchTarget();
        if(mpActorTarget != NULL) {
            setGrabPos();
            if(field_0x2E4 != 0 && cLib_calcTimer(&field_0x650) != 0) {
                return;
            }
            if(isGrabPos()) {
                modeProc(PROC_0_e,8);
                return;
            }
        }
        if(mAnmPrmIdx == 1) {
            modeProc(PROC_0_e,7);
        }
    }
    /* Nonmatching */
}

/* 00003A00-00003A68       .text modeDisappearInit__6daFm_cFv */
void daFm_c::modeDisappearInit() {
    if(mAnmPrmIdx != 8 && mAnmPrmIdx != 6) {
        setAnm(3, false);
    }

    if(mAnmPrmIdx == 6) {
        setAnm(8, false);
    }
    /* Nonmatching */
}

/* 00003A68-00003BDC       .text modeDisappear__6daFm_cFv */
void daFm_c::modeDisappear() {
    if(field_0x2D0 != 2) {
        field_0x690 = current.pos;
    }
    resetInvKine();
    cancelGrab();
    if(mAnmPrmIdx == 8) {
        if(mpMorf->isStop()) {
            if(field_0x2E4 != 0 || field_0x2E5) {
                modeProc(PROC_0_e, 0x12);
            } else {
                fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
                if(isGrabFoot() && !dComIfGp_event_runCheck()) {
                    modeProc(PROC_0_e, 0xf);
                } else {
                    switch(field_0x2D0) {
                        case 0:
                            modeProc(PROC_0_e, 1);
                            break;
                        case 1:
                            modeProc(PROC_0_e, 3);
                            break;
                        case 2:
                            modeProc(PROC_0_e, 4);
                            break;
                    }
                }
            }
        }
    }
    /* Nonmatching */
}

/* 00003BDC-00003C5C       .text modeWaitInit__6daFm_cFv */
void daFm_c::modeWaitInit() {
    field_0x658 = l_HIO.field_0x088;
    field_0x650 = setRnd(l_HIO.field_0x08C,l_HIO.field_0x08E);

    field_0x654 = l_HIO.field_0x08A;
    field_0x65C = l_HIO.field_0x100;
    field_0x6B4 = 0;
    field_0x660 = current.pos;
    /* Nonmatching */
}

/* 00003C5C-00003F90       .text modeWait__6daFm_cFv */
void daFm_c::modeWait() {
    resetInvKine();
    cancelGrab();
    if(checkTgHit()) {
        return;
    }
    if(!areaCheck()) {
        modeProc(PROC_0_e, 6);
        return;
    }
    if(isGrabFoot()) {
        modeProc(PROC_0_e, 6);
        return;
    }

    searchTarget();
    s32 angle = cLib_distanceAngleS(shape_angle.y, field_0x9D0);
    if(mpActorTarget != NULL) {
        if(field_0x9D4 > l_HIO.field_0x0E0) {
            s16 angle2 = cLib_targetAngleY(&current.pos, &mGrabPos);
            if(isNpc(mpActorTarget) || isLink(mpActorTarget)) {
                cLib_addCalcAngleS2(&shape_angle.y, angle2, 8, 0x300);

            } else {
                cLib_addCalcAngleS2(&shape_angle.y, angle2, 4, 0x800);

            }
        }
        setGrabPos();
        if(isGrabPos()) {
            if(checkPlayerGrabTarget()) {
                if(cLib_calcTimer(&field_0x65C) == 0) {
                    modeProc(PROC_0_e, 8);
                    return;
                }
            } else {
                if(isNpc(mpActorTarget)) {
                    if(cLib_calcTimer(&field_0x65C) != 0) {
                        return;
                    }
                    modeProc(PROC_0_e,8);
                    return;
                }
                modeProc(PROC_0_e,8);
                return;
            }
        }
    } else {
        if(angle > l_HIO.field_0x09A) {
            cLib_addCalcAngleS2(&shape_angle.y, field_0x9D0, 10, 0x100);
        }
    }
    if(field_0x2D0 == 2 && (mBaseTarget->current.pos - field_0x69C).absXZ() > field_0x2E0) {
            modeProc(PROC_0_e, 6);
    } else {
        moveRndBack();
    }
    if(field_0x9D4 > l_HIO.field_0x0E4 && field_0x9D4 < l_HIO.field_0x0E8) {
        turnToBaseTarget();
    }
    if(field_0x9D4 > l_HIO.field_0x0E8) {
        if(cLib_calcTimer(&field_0x658) == 0) {
            modeProc(PROC_0_e,6);
        }
    } else {
        field_0x658 = l_HIO.field_0x088;
    }
    /* Nonmatching */
}

/* 00003F90-00003FF8       .text modeAttackInit__6daFm_cFv */
void daFm_c::modeAttackInit() {
    if(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK400_e | daPyStts0_UNK2_e)) {
        modeProc(PROC_0_e,7);
    } else {
        setAnm(4, false);
        field_0x650 = l_HIO.field_0x094;
    }
    /* Nonmatching */
}

/* 00003FF8-000049CC       .text modeAttack__6daFm_cFv */
void daFm_c::modeAttack() {
    
    f32 dist;
    if(mAnmPrmIdx != 5 && !isGrab()) {
        dist = (mGrabPos - current.pos).absXZ();
        if(!(dist > l_HIO.field_0x0E0 && dist < l_HIO.field_0x0C4) && dist < l_HIO.field_0x0E4 + 10.0f) {
            field_0x660 = mGrabPos;
            cLib_addCalcPosXZ2(&current.pos, field_0x660, (l_HIO.field_0x0CC + 1.0f) *0.005f * field_0x394, 40.0f);
        }
    }
    
    if (!checkTgHit()) {
        if (mAnmPrmIdx == 5) {
            if (mpMorf->isStop()) {
                modeProcInit(7);
                return;
            }
        }

        if (mpActorTarget == NULL) {
            setAnm(5, false);
        } else {
            calcInvKine(mpActorTarget);
            s16 actorAngle = fopAcM_searchActorAngleY(this, mpActorTarget);
            if (cLib_distanceAngleS(shape_angle.y, actorAngle) > l_HIO.field_0x09A) {
                cLib_addCalcAngleS2(&shape_angle.y, actorAngle, 4, l_HIO.field_0x096);
            }


            if (field_0xAE4 == 0) {
                modeProcInit(6);
            } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK400_e  | daPyStts0_UNK2_e)) {
                f32 oldGrabPosY = mGrabPos.y;
                mGrabPos = daPy_getPlayerLinkActorClass()->current.pos;
                mGrabPos.y = oldGrabPosY;
                
            } else {
                if (isGrabPos()) {
                    setGrabPos();
                } else {
                    setAnm(5, false);
                    return;
                }

                if (isGrab()) {
                    if(isLink(mpActorTarget) && mAnmPrmIdx == 4) {
                        if(mpMorf->isStop()) {
                            modeProcInit(0xD);
                            fopAcM_seStart(this, JA_SE_CM_FM_GRAB_HAND, 0);
                            daPy_getPlayerLinkActorClass()->voiceStart(0x1C);
                        } else {
                            daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();

                            if(pLink->speedF >= 1.0f){
                                dist = (mGrabPos - field_0x63C).absXZ(); // might share same temp var ias dist3
                                if(dist > l_HIO.field_0x110 && dist < l_HIO.field_0x114) {
                                    s16 targetAngle2 = cLib_targetAngleY(&field_0x63C, &mGrabPos);
                                    f32 dist2 = std::fabsf(l_HIO.field_0x114 -l_HIO.field_0x110);
                                    if (dist2 == 0.0f) {
                                        dist2 = 1.0f;
                                    }
                                    pLink->setOutPower(l_HIO.field_0x118 * (std::fabsf(dist - l_HIO.field_0x110) / dist2), targetAngle2, 0);
                                }
                            }
                        }
                    } else {
                        if (isNpc(mpActorTarget) == true) { 
                            if (!fopAcM_CheckStatus(mpActorTarget, fopAcStts_CARRY_e)) {
                                fopAcM_seStart(this, JA_SE_CM_FM_GRAB_HAND, 0);
                                fopAcM_setCarryNow(mpActorTarget, 0);
                                field_0x684 = 4;

                                if (fopAcM_GetName(mpActorTarget) == PROC_NPC_CB1) {
                                    ((daNpc_Cb1_c*)mpActorTarget)->noCarryAction();
                                }

                                if (fopAcM_GetName(mpActorTarget) == PROC_NPC_MD) {
                                    ((daNpc_Md_c*)mpActorTarget)->noCarryAction();
                                }

                                field_0x6B8 = 1;
                                if(field_0x2E4 != 0) {
                                    if (dComIfGp_evmng_startCheck("DEFAULT_FM_SW_APEEAR")) {
                                        dComIfGp_event_reset();
                                    }
                                    modeProcInit(0xD);
                                } else {
                                    f32 temp3 = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
                                    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();

                                    if ((temp3 > l_HIO.field_0x0BC || 
                                    std::fabsf(pLink->current.pos.y - current.pos.y) > l_HIO.field_0x0A8) && 
                                    !dComIfGp_event_runCheck()) {
                                        modeProcInit(0x10);
                                    } else {
                                        
                                        modeProcInit(0xD);
                                    }
                                }
                            } else {
                                fopAcM_cancelCarryNow(mpActorTarget);
                            }
                        } else {
                            fopAc_ac_c* actor = mpActorTarget;
                            s16 procName = fopAcM_GetName(actor);

                            if (procName == PROC_BOMB) {
                                if (!fopAcM_CheckStatus(actor, fopAcStts_CARRY_e)) {
                                    fopAcM_setCarryNow(actor, 0);
                                    field_0x684 = 2;
                                    fopAcM_seStart(this, JA_SE_CM_FM_GRAB, 0);

                                    modeProcInit(0xD);
                                } else {
                                    modeProcInit(7);
                                }
                            } else if (procName == PROC_TSUBO) {
                                if (!fopAcM_CheckStatus(actor, fopAcStts_CARRY_e)) {
                                    fopAcM_setCarryNow(actor, 0);
                                    field_0x684 = 3;
                                    fopAcM_seStart(this, JA_SE_CM_FM_GRAB, 0);

                                    modeProcInit(0xD);
                                } else {
                                    fopAcM_cancelCarryNow(actor);
                                }
                            }
                        }
                        
                    }
                } else if (isLink(mpActorTarget) && mAnmPrmIdx == 4) {
                    dist = (mGrabPos - field_0x63C).absXZ();

                    if (dist > l_HIO.field_0x110 && dist < l_HIO.field_0x114) {
                        daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();

                        if(pLink->speedF >= 1.0f) {
                            s16 targetAngle = cLib_targetAngleY(&field_0x63C, &mGrabPos);
                            f32 dist3 = std::fabsf(l_HIO.field_0x114 - l_HIO.field_0x110);
                            if (dist3 == 0.0f) {
                                dist3 = 1.0f;
                            }
                            pLink->setOutPower(l_HIO.field_0x118 * (std::fabsf(dist - l_HIO.field_0x110) / dist3), targetAngle, 0);
                        }
                        
                    } else if (mpMorf->isStop() && cLib_calcTimer(&field_0x650) == 0) {
                        setAnm(5, false);
                    }
                } else if (mAnmPrmIdx == 4){
                    if (mpMorf->isStop() && cLib_calcTimer(&field_0x650) == 0) {
                        setAnm(5, false);
                    }
                }
            }
        }
    }
    /* Nonmatching */
}

/* 000049CC-000049F4       .text modeThrowInit__6daFm_cFv */
void daFm_c::modeThrowInit() {
    setAnm(0xB, false);
    /* Nonmatching */
}

/* 000049F4-00004CE4       .text modeThrow__6daFm_cFv */
void daFm_c::modeThrow() {
    resetInvKine();
    if(mAnmPrmIdx == 1 && cLib_calcTimer(&field_0x650) == 0) {
        modeProc(PROC_0_e, 7);
    }
    if(field_0x684 != 0 && mpActorTarget == NULL) {
        modeProc(PROC_0_e, 10);
        return;
    }
    if(field_0x684 == 0) {
        return;
    }
    if(checkTgHit()) {
        return;
    }

    if(field_0x2D0 != 2 || isNpc(mpActorTarget) != true) {
        s16 angle = fopAcM_searchPlayerAngleY(this);
        cLib_addCalcAngleS2(&shape_angle.y, angle, 4, 0x800);
    }

    if(l_HIO.field_0x0FC == mpMorf->getFrame()) {
        if(isNpc(mpActorTarget)) {
            mpActorTarget->speedF = l_HIO.field_0x0F0;
            mpActorTarget->speed.y = l_HIO.field_0x0F4;
            fopAcM_cancelCarryNow(mpActorTarget);
            field_0x684 = 0;
            mGrabPos = current.pos;
        } else {
            if(fopAcM_GetName(mpActorTarget) == PROC_BOMB || fopAcM_GetName(mpActorTarget) == PROC_TSUBO) {
                mpActorTarget->current.angle.y = shape_angle.y;
                mpActorTarget->shape_angle.y = shape_angle.y;
                mpActorTarget->speedF = l_HIO.field_0x0F0;
                
                f32 temp = field_0x9D4 / (REG12_F(13) + 1000.0f);
                if (temp <= 0.0f) {
                    temp = 0.0f;
                } else if (temp >= 1.0f) {
                    temp = 1.0f;
                }

                f32 dropspeed = temp *= l_HIO.field_0x0F4;
                daTsubo::Act_c* tsubo = (daTsubo::Act_c*)mpActorTarget;
                
                if(fopAcM_GetName(mpActorTarget) == PROC_TSUBO) {
                    switch(tsubo->prm_get_type()) {
                        case 0:
                        case 1:
                        case 2:
                        case 4:
                        case 5:
                        case 6:
                            tsubo->set_drop_spd_y0(dropspeed);
                            tsubo->m810 = 1;
                            break;
                    }
                } else {
                    tsubo->set_drop_spd_y0(dropspeed);
                }
                mpActorTarget->gravity = l_HIO.field_0x0F8;
                fopAcM_cancelCarryNow(mpActorTarget);
                field_0x684 = 0;
                mGrabPos = current.pos;
            }
        }
    }

    if(mAnmPrmIdx == 11) {
        if(mpMorf->isStop()) {
            field_0x650 = 0x3c;
        }
    }
    /* Nonmatching */
}

/* 00004CE4-00004D20       .text modeGrabFootDemoInit__6daFm_cFv */
void daFm_c::modeGrabFootDemoInit() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    field_0x610.setall(0.0f);
    field_0x630.set(pLink->current.pos);
    /* Nonmatching */
}

/* 00004D20-000050B4       .text modeGrabFootDemo__6daFm_cFv */
void daFm_c::modeGrabFootDemo() {
    resetInvKine();
    if(l_HIO.field_0x00D != 0) {
        modeProc(PROC_0_e, 5);
    } else {
        if(eventInfo.mCommand == dEvtCmd_INDEMO_e) {
            int staffIdx = dComIfGp_evmng_getMyStaffId("Fmaster");
            char* cutName = dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx);
            if(strcmp(cutName, "Dummy") == 0 || strcmp(cutName, "WAIT") == 0) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
            if(strcmp(cutName, "GRAB_FOOT") == 0 && mAnmPrmIdx == 10 &&
                mpMorf->getFrame() == 10.0f) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
            daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
            fopAc_ac_c* ac = fopAcM_SearchByID(pLink->getGrabActorID());
            if(ac != NULL) {
                fopAcM_cancelCarryNow(ac);
            }
            pLink->changeOriginalDemo();

            if(mAnmPrmIdx != 10) {
                if(fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0)) < 3.0f) {
                    setAnm(10, false);
                }  else {
                    cLib_addCalcPosXZ2(&field_0x630, current.pos, 0.3f, 10.0f);
                    pLink->setPlayerPosAndAngle(&field_0x630, &pLink->current.angle);
                }
            } else {
                if(mpMorf->getFrame() == 25.0f) {
                    fopAcM_seStart(this, JA_SE_CM_FM_PULL_IN, 0);
                }
                if(mpMorf->getFrame() == 10.0f) {
                    fopAcM_seStart(this, JA_SE_CM_FM_GRAB_FOOT, 0);
                    pLink->voiceStart(28);
                }
                if(mpMorf->getFrame() == 10.0f) {
                    pLink->mDemo.setDemoMode(0x11);
                }
                if(mpMorf->getFrame() >= 10.0f && mpMorf->getFrame() <= 40.0f) {
                    pLink->setPlayerPosAndAngle(&field_0x61C, &pLink->current.angle);
                }
            }
            if(dComIfGp_evmng_endCheck("DEFAULT_FM_GRAB_FOOT")) {
                if(field_0x2C7 != 0xff) {
                    dLib_setNextStageBySclsNum(field_0x2C7, fopAcM_GetRoomNo(this));
                } else {
                    dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0, fopAcM_GetRoomNo(this), -1, 0.0f, 0);
                }
            }
        } else {
            fopAcM_orderOtherEvent2(this,"DEFAULT_FM_GRAB_FOOT", dEvtFlag_NOPARTNER_e);
        }
    }

    
    /* Nonmatching */
}

/* 000050B4-000050F8       .text modeParalysisInit__6daFm_cFv */
void daFm_c::modeParalysisInit() {
    setAnm(0xd, true);
    field_0x650 = l_HIO.field_0x11C;
    /* Nonmatching */
}

/* 000050F8-00005218       .text modeParalysis__6daFm_cFv */
void daFm_c::modeParalysis() {
    if(field_0x650 == l_HIO.field_0x11C - 0x14) {
        enemy_piyo_set(this);
    }
    if(field_0x650 <= l_HIO.field_0x11C - 0x14 && field_0x650 >= l_HIO.field_0x11C -0x3C) {
        fopAcM_seStart(this, JA_SE_CM_MD_PIYO, 0);
    }
    if(field_0x650 == l_HIO.field_0x11C - 0x3c) {
        setAnm(1, false);
        field_0x64C = 0x28;
        field_0x68C = 0x2b00;
    }
    if(cLib_calcTimer(&field_0x650) == 0) {
        modeProc(PROC_0_e, 7);
    }
    cancelGrab();
    if (checkTgHit()) {
        // comment below is from from d_a_Rd_c::modeParalysis, likely applies here too
        // This line setting speedF to itself gets optimized out and produces no code, but affects codegen.
        // It's not known what the original code that got optimized out here was, it could be speedF or something else.
        speedF = speedF;
    }
    /* Nonmatching */
}

/* 00005218-0000525C       .text modeDamageInit__6daFm_cFv */
void daFm_c::modeDamageInit() {
    setAnm(7, true);
    field_0x650 = l_HIO.field_0x0A6;
    /* Nonmatching */
}

/* 0000525C-00005308       .text modeDamage__6daFm_cFv */
void daFm_c::modeDamage() { // idk if bool tbh
    resetInvKine();
    cancelGrab();
    if(mAnmPrmIdx == 1 && field_0x64C == 0) {
        searchTarget();
        if(mpActorTarget != NULL && !isNpc(mpActorTarget)) {
            modeProc(PROC_0_e, 7);
        }
        if(!cLib_calcTimer(&field_0x650)) {
            modeProc(PROC_0_e, 7);
        }
    }
    if (checkTgHit()) {
        // comment below is from d_a_Rd_c::modeParalysis, likely applies here too
        // This line setting speedF to itself gets optimized out and produces no code, but affects codegen.
        // It's not known what the original code that got optimized out here was, it could be speedF or something else.
        speedF = speedF;
    }
    /* Nonmatching */
}

/* 00005308-000053E0       .text modeGrabInit__6daFm_cFv */
void daFm_c::modeGrabInit() {
    if (isLink(mpActorTarget)) {
        field_0x654 = l_HIO.field_0x090;
    } else {
        field_0x654 = l_HIO.field_0x09E;
    }
    field_0x650 = l_HIO.field_0x092;
    if (isNpc(mpActorTarget) == true) {
        setAnm(0xC, false);
    } else {
        s16 procName = fopAcM_GetName(mpActorTarget);
        if(procName == PROC_BOMB || procName == PROC_TSUBO) {
            setAnm(9, false);
        }
    }
    field_0x660 = field_0x690;
    /* Nonmatching */
}

/* 000053E0-00005A7C       .text modeGrab__6daFm_cFv */
void daFm_c::modeGrab() {
    cXyz temp;
    cXyz temp2;
    f32 dist;
    if (!isLink(mpActorTarget) && (field_0x2D0 == 0 || field_0x2D0 == 1) && isNpc(mpActorTarget) == true) {
        moveRndEscape();
    }
    if (mpActorTarget == NULL) {
        modeProcInit(10);
    } else {
        if(isLink(mpActorTarget)) {
            calcInvKine(mpActorTarget);
        } else {
            resetInvKine();
        }

        if (!checkTgHit()) {
            s16 angle;

            if (isLink(mpActorTarget)) {
                angle = cLib_targetAngleY(&current.pos,&mGrabPos);
                if (cLib_distanceAngleS(shape_angle.y, angle) > l_HIO.field_0x09A) {
                    cLib_addCalcAngleS2(&shape_angle.y, angle, 4, l_HIO.field_0x096);
                }
                
            } else {

                dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
                if (field_0x2D0 == 2 && isNpc(mpActorTarget) && dist < l_HIO.field_0x0C4) {
                    fopAcM_Search(searchNearFm_CB, this); // unused call?
                    temp2.set(field_0x3E4.x, 0.0f, field_0x3E4.z);
                    if (temp2.abs() != 0.0f) {
                        angle = cLib_targetAngleY(&current.pos, &field_0x3E4);
                    } else {
                        angle = (s16)fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
                    }
                } else {
                    angle = (s16)fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
                }
                cLib_addCalcAngleS2(&shape_angle.y, angle, 4, 0x800);
            }

            if (isLink(mpActorTarget)) {
                setGrabPos();
                if (checkPlayerGrabBomb()) {
                    setAnm(7, false);
                    modeProcInit(7);
                } else {
                    if (cLib_calcTimer(&field_0x654) == 0 && l_HIO.field_0x00D == 0 && !dComIfGp_event_runCheck()) { // check out if its in one line or in 2, line 2045
                        modeProcInit(0xE);
                        field_0x684 = 1;
                    } else {
                        dist = (mGrabPos - field_0x63C).absXZ();
                        if (dist > l_HIO.field_0x110 && dist < l_HIO.field_0x114) {
                            daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
                            angle = cLib_targetAngleY(&field_0x63C, &mGrabPos);
                            f32 temp4 = std::fabsf(l_HIO.field_0x114 - l_HIO.field_0x110);
                            if (temp4 == 0.0f) {
                                temp4 = 1.0f;
                            }
                            pLink->setOutPower(l_HIO.field_0x118 * (std::fabsf(dist - l_HIO.field_0x110) / temp4), angle, 0);

                        } else {
                            if (!isGrab()) {
                                setAnm(5, false);
                                modeProcInit(7);
                            }
                        }
                        if (isGrabFoot()) {
                            modeProcInit(6);
                        }
                    }
                }
                
            } else {
                if (isNpc(mpActorTarget) == true) {
                    mGrabPos = field_0x61C;
                    if (field_0x2E4 != 0) {
                        if (!isLinkControl()) {
                            modeProcInit(0x10);
                        }
                        
                    } else {
                        dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
                        if (dist < l_HIO.field_0x0B4 && field_0x2D0 == 2) {
                            angle = cLib_targetAngleY(&current.pos, &field_0x3E4);

                            if (cLib_distanceAngleS(shape_angle.y, angle) < 0x500 && dist < l_HIO.field_0x0C4) {
                                modeProcInit(9);
                                return;
                            }
                        }
                        if (cLib_calcTimer(&field_0x654) == 0) {
                            if (l_HIO.field_0x00D == 0 && !dComIfGp_event_runCheck()) { // maybe bool hio field
                                modeProcInit(0xE);
                            }
                        } else if (field_0x2DC == 1) {
                            modeProcInit(9);
                        }

                    }
                } else {
                    s16 procName = fopAcM_GetName(mpActorTarget);
                    if (procName == PROC_BOMB || procName == PROC_TSUBO) {
                        moveRndBack();
                        mGrabPos = field_0x61C;
                        if (!daPy_getPlayerLinkActorClass()->checkPlayerGuard()) {
                            if (cLib_calcTimer(&field_0x650) == 0 && l_HIO.field_0x00D == 0) { // hio maybe bool
                                modeProcInit(9);
                            }
                        } else {
                            field_0x650 = l_HIO.field_0x092;
                        }
                    }
                }
            }
        }
    }
    /* Nonmatching */
}

/* 00005A7C-00005AD8       .text modeGrabDemoInit__6daFm_cFv */
void daFm_c::modeGrabDemoInit() {
    setAnm(6, false);
    if (isLink(mpActorTarget)) {
        field_0x3FC = true;
    }
    else {
        field_0x3FC = false;
    }

    /* Nonmatching */
}

/* 00005AD8-00005EDC       .text modeGrabDemo__6daFm_cFv */
void daFm_c::modeGrabDemo() {
    resetInvKine();

    if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
        pLink->changeOriginalDemo();
        if (mAnmPrmIdx == 6 && mpMorf->getFrame() == 15.0f) {
            fopAcM_seStart(this, JA_SE_CM_FM_PULL_IN, 0);
        }
        if (field_0x3FC) {
            fopAc_ac_c* actor = fopAcM_SearchByID(pLink->getGrabActorID());
            if (actor != NULL) {
                fopAcM_cancelCarryNow(actor);
            }
            if (mAnmPrmIdx == 6 && mpMorf->getFrame() == 40.0f) {
                pLink->voiceStart(0xC);
            }
            pLink->changeDemoMode(0x1e);
            pLink->changeDemoParam0(1);
            cXyz temp(0.0f, 0.0f, 0.0f);
            cLib_chasePos(&field_0x610, temp, 5.0f);

            if (dComIfGp_evmng_endCheck("DEFAULT_FM_GRAB")) {
                if (field_0x2C7 != 0xff) {
                    dLib_setNextStageBySclsNum(field_0x2C7, fopAcM_GetRoomNo(this));
                } else {
                    dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0, fopAcM_GetRoomNo(this), -1, 0.0f, 0); // maybe able to remove args?
                }
            }
        } else {
            if (mAnmPrmIdx == 6 && mpMorf->getFrame() == 40.0f) {
                s16 procName = fopAcM_GetName(mpActorTarget);
                if (procName == PROC_NPC_MD) {
                    fopAcM_monsSeStart(this, JA_SE_CV_MD_DAMAGE, 0);
                } else if (procName == PROC_NPC_CB1) {
                    fopAcM_monsSeStart(this, JA_SE_CV_CB_DAMAGE, 0);
                }
            }
            if (fopAcM_GetName(mpActorTarget) == PROC_NPC_MD) { // maybe mpActorTarget gets casted here already
                ((daNpc_Md_c *)mpActorTarget)->changeCaught02();
                field_0x688 = 1;
            }

            if (dComIfGp_evmng_endCheck("DEFAULT_FM_SUIKOMI_NPC")) {
                if (field_0x2C8 != 0xff) {
                    cancelGrab();
                    if (fopAcM_GetName(mpActorTarget) == PROC_NPC_CB1) {
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3408);
                        ((daPy_npc_c *)mpActorTarget)->setPointRestart(field_0x2C8, 1); // maybe (daPy_npc_c *) cast
                    }
                    if (fopAcM_GetName(mpActorTarget) == PROC_NPC_MD) {
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3404);
                        ((daPy_npc_c *)mpActorTarget)->setPointRestart(field_0x2C8, 2); // maybe (daPy_npc_c *) cast
                    }
                }
                dComIfGp_event_reset();
                modeProcInit(0x12);
            }
        }
    } else {
        if (isLink(mpActorTarget)) {
            fopAcM_orderOtherEvent2(this, "DEFAULT_FM_GRAB", dEvtFlag_NOPARTNER_e);
        }
        else {
            if (isNpc(mpActorTarget)) {
                if (field_0x2E4 != 0) {
                    fopAcM_orderChangeEvent(this, "DEFAULT_FM_SUIKOMI_NPC", 0, 0xFFFF);
                } else {
                    fopAcM_orderOtherEvent2(this, "DEFAULT_FM_SUIKOMI_NPC", dEvtFlag_NOPARTNER_e);
                }
            }
        }
    }
    /* Nonmatching */
}

/* 00005EDC-00005F04       .text modeDeathInit__6daFm_cFv */
void daFm_c::modeDeathInit() {
    setAnm(3, false);
    /* Nonmatching */
}

/* 00005F04-00005FA4       .text modeDeath__6daFm_cFv */
void daFm_c::modeDeath() {
    resetInvKine();
    cancelGrab();
    if(mAnmPrmIdx == 8 && setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x128) != 0) {
        fopAcM_onActor(this);
        fopAcM_createDisappear(this, &current.pos, 5, daDisItem_IBALL_e);
        fopAcM_delete(this);
    }

    /* Nonmatching */
}

/* 00005FA4-00005FF0       .text modePrepareItemInit__6daFm_cFv */
void daFm_c::modePrepareItemInit() {
    setAnm(3, false);
    field_0x650 = l_HIO.field_0x092;
    cancelGrab();
    /* Nonmatching */
}

/* 00005FF0-000061A4       .text modePrepareItem__6daFm_cFv */
void daFm_c::modePrepareItem() {
    if(!checkTgHit()) {
        s8 temp = mAnmPrmIdx;
        if(temp == 3) {
            if(mpMorf->isStop()) {
                mProcId2 = fopAcM_create(PROC_TSUBO, 0x57f3f3f, &field_0x61C, tevStr.mRoomNo, NULL, NULL, 0xff);
                return;
            }
        }
        // prm_make_skull gets mentioned in debug and is likely to be called inside of fopacm_create, maybe the 0x57f3f3f arg
        if(temp == 8) {
            mpActorTarget = fopAcM_SearchByID(mProcId2);
            fopAcM_setCarryNow(mpActorTarget, 0);
            field_0x684 = 3;
            setAnm(2, false);
            setGrabPos();
        } else {
            if(temp == 2) {
                if(mpMorf->isStop()) {
                    setAnm(9, false);
                    return;
                }
            }

            if(temp == 9) {
                if(!daPy_getPlayerLinkActorClass()->checkPlayerGuard()) {
                    if(cLib_calcTimer(&field_0x650) == 0) {
                        modeProc(PROC_0_e,9);
                    }
                } else {
                    field_0x650 = l_HIO.field_0x092;
                }
            }
        }
    }
    /* Nonmatching */
}

/* 000061A4-000061CC       .text modeGrabNpcDemoInit__6daFm_cFv */
void daFm_c::modeGrabNpcDemoInit() {
    setAnm(9, false);
    /* Nonmatching */
}

/* 000061CC-0000638C       .text modeGrabNpcDemo__6daFm_cFv */
void daFm_c::modeGrabNpcDemo() {
    resetInvKine();
    mGrabPos = field_0x61C;
    if(eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("Fmaster");
        if(strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx), "YAYU") == 0) {
            setAnm(12, false);
            if(mpMorf->isStop()) {
                dComIfGp_evmng_cutEnd(staffIdx);

            }
        } else {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
        if(dComIfGp_evmng_endCheck("DEFAULT_FM_NPC_GRAB") != 0) {
            if(field_0x2E4 != 0) {
                dComIfGp_event_reset();
                modeProc(PROC_0_e, 0xE);
            } else {
                dComIfGp_event_reset();
                modeProc(PROC_0_e, 0xD);
            }
        }
    } else if(field_0x2E4 != 0) {
        fopAcM_orderChangeEvent(this,"DEFAULT_FM_NPC_GRAB", 0, 0xffff);
    } else {
        fopAcM_orderOtherEvent2(this, "DEFAULT_FM_NPC_GRAB", dEvtFlag_NOPARTNER_e);
    }
    /* Nonmatching */
}

/* 0000638C-000063C4       .text modePlayerStartDemoInit__6daFm_cFv */
void daFm_c::modePlayerStartDemoInit() {
    field_0x3E0 = l_HIO.field_0x120;
    current.pos = dComIfGp_getPlayer(0)->current.pos;
    /* Nonmatching */
}

/* 000063C4-000066A0       .text modePlayerStartDemo__6daFm_cFv */
void daFm_c::modePlayerStartDemo() {
    resetInvKine();
    if(dComIfGp_event_runCheck()) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("Fmaster");
        char* cutName = dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx);
        
        daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
        pLink->changeOriginalDemo();
        
        if(strcmp(cutName, "Dummy") == 0 || strcmp(cutName, "WAIT") == 0) {
            
            cXyz pos = current.pos;
            pos.y -= REG12_F(2);
            pLink->setPlayerPosAndAngle(&pos, &shape_angle);
            pLink->onPlayerNoDraw();
            dComIfGp_evmng_cutEnd(staffIdx);

        } else if(strcmp(cutName, "OPEN") == 0) {
            cXyz pos2 = current.pos;
            pos2.y -= REG12_F(2);
            pLink->setPlayerPosAndAngle(&pos2, &shape_angle);
            pLink->onPlayerNoDraw();
            if(setHoleScale(l_HIO.field_0x124, 0.1f, l_HIO.field_0x128)) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }

        } else if(strcmp(cutName, "PL_OUT") == 0) {
            pLink->offPlayerNoDraw();
            pLink->setThrowDamage(
                NULL,
                shape_angle.y,
                REG12_F(0) + 10.0f,
                REG12_F(1) + 50.0f,
                0
            );
            dComIfGp_evmng_cutEnd(staffIdx);

        } else if(strcmp(cutName, "CLOSE") == 0) {
            pLink->offPlayerNoDraw();
            if(setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x128)) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }

        } else if(strcmp(cutName, "DELETE") == 0) {
            modeProc(PROC_0_e, 0x12);
        }
    }
    /* Nonmatching */
}

/* 000066A0-000066A4       .text modeDeleteInit__6daFm_cFv */
void daFm_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 000066A4-00006744       .text modeDelete__6daFm_cFv */
void daFm_c::modeDelete() { // isholeappear?
    resetInvKine();
    bool temp = false;
    if(isHoleAppear()) {
        if(setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x128)) {
            temp = true;
        } else {
            temp = false;
        }
    }
    if(!dComIfGp_event_runCheck() && temp == true) {
        fopAcM_delete(this);
    }
    /* Nonmatching */
}

/* 00006744-000067A0       .text modeBikubikuInit__6daFm_cFv */
void daFm_c::modeBikubikuInit() {
    field_0x650 = l_HIO.field_0x068;
    field_0x654 = 5;
    setAnm(0xe,true);
    field_0x650 = l_HIO.field_0x068;
    /* Nonmatching */
}

/* 000067A0-000068D0       .text modeBikubiku__6daFm_cFv */
void daFm_c::modeBikubiku() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    mGrabPos = pLink->current.pos;
    if(mAnmPrmIdx == 1) {
        resetInvKine();
    } else if(mAnmPrmIdx != 0xe) {
        calcInvKine(pLink);
    } else {
        if(cLib_calcTimer(&field_0x654)!= 0) {
            calcInvKine(pLink);
        }
    }

    if(mAnmPrmIdx == 0xe) {
        if(cLib_calcTimer(&field_0x650) == 0) {
            if(health <= 0) {
                modeProc(PROC_0_e, 0xC);
                return;
            } else {
                setAnm(1, true);
                field_0x64C = REG12_S(3) + 0x28;
                field_0x68C = 0x2b00;
            }
        }
    } else if(mAnmPrmIdx == 1 && field_0x64C == 0) {
        modeProc(PROC_0_e,7);
    }
    /* Nonmatching */
}

/* 000068D0-00006D8C       .text modeProc__6daFm_cFQ26daFm_c6Proc_ei */
void daFm_c::modeProc(daFm_c::Proc_e proc, int newMode) {

    struct ModeEntry {
        ModeFunc init;
        ModeFunc run;
        const char* name;
    };

    static ModeEntry mode_tbl[] = {
        {
            &daFm_c::modeSwWaitInit,
            &daFm_c::modeSwWait,
            "SW_WAIT",
        },
        {
            &daFm_c::modeHideInit,
            &daFm_c::modeHide,
            "HIDE"
        },
        {
            &daFm_c::modeUnderFootInit,
            &daFm_c::modeUnderFoot,
            "UNDERFOOT"
        },
        {
            &daFm_c::modePathMoveInit,
            &daFm_c::modePathMove,
            "PATH_MOVE"
        },
        {
            &daFm_c::modeGoalKeeperInit,
            &daFm_c::modeGoalKeeper,
            "GOAL_KEEPER"
        },
        {
            &daFm_c::modeAppearInit,
            &daFm_c::modeAppear,
            "APPEAR"
        },
        {
            &daFm_c::modeDisappearInit,
            &daFm_c::modeDisappear,
            "DISAPPEAR"
        },
        {
            &daFm_c::modeWaitInit,
            &daFm_c::modeWait,
            "WAIT"
        },
        {
            &daFm_c::modeAttackInit,
            &daFm_c::modeAttack,
            "ATTACK"
        },
        {
            &daFm_c::modeThrowInit,
            &daFm_c::modeThrow,
            "THROW"
        },
        {
            &daFm_c::modeDamageInit,
            &daFm_c::modeDamage,
            "DAMAGE"
        },
        {
            &daFm_c::modePrepareItemInit,
            &daFm_c::modePrepareItem,
            "PREPARE_ITEM"
        },
        {
            &daFm_c::modeDeathInit,
            &daFm_c::modeDeath,
            "DEATH"
        },
        {
            &daFm_c::modeGrabInit,
            &daFm_c::modeGrab,
            "GRAB"
        },
        {
            &daFm_c::modeGrabDemoInit,
            &daFm_c::modeGrabDemo,
            "GRAB_DEMO"
        },
        {
            &daFm_c::modeGrabFootDemoInit,
            &daFm_c::modeGrabFootDemo,
            "GRAB_FOOT_DEMO"
        },
        {
            &daFm_c::modeGrabNpcDemoInit,
            &daFm_c::modeGrabNpcDemo,
            "GRAB_NPC_DEMO"
        },
        {
            &daFm_c::modePlayerStartDemoInit,
            &daFm_c::modePlayerStartDemo,
            "PLAYER_START_DEMO"
        },
        {
            &daFm_c::modeDeleteInit,
            &daFm_c::modeDelete,
            "DELETE"
        },
        {
            &daFm_c::modeParalysisInit,
            &daFm_c::modeParalysis,
            "PARALYSIS"
        },
        {
            &daFm_c::modeBikubikuInit,
            &daFm_c::modeBikubiku,
            "BIKUBIKU"
        }
    };

    if(proc == PROC_0_e) {
        switch(newMode) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
            case 0xB:
            case 0xC:
            case 0xE:
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12:
                attention_info.flags &= ~fopAc_Attn_LOCKON_BATTLE_e;
                break;
            default:
                attention_info.flags |= fopAc_Attn_LOCKON_BATTLE_e;
                break;
        }
        mMode = newMode;
        (this->*mode_tbl[mMode].init)();
    } else if(proc == PROC_1_e) {
        (this->*mode_tbl[mMode].run)();
    }
    /* Nonmatching */
}

/* 00006D8C-00006DE8       .text setAnm__6daFm_cFScb */
void daFm_c::setAnm(s8 anmPrmIdx, bool param_2) {
    static const int a_anm_bcks_tbl[] = {
        FM_BCK_WAIT,
        FM_BCK_DERU,
        FM_BCK_MODORU,
        FM_BCK_TUKAMU,
        FM_BCK_TUKAMU2WAIT,
        FM_BCK_HIKIKOMU,
        FM_BCK_DAMAGE,
        FM_BCK_TUMAMIWAIT,
        FM_BCK_ASITUKAMI,
        FM_BCK_NAGERU,
        FM_BCK_YAYU,
        FM_BCK_MAHI,
        FM_BCK_KUSIZASI
    };

    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {
            /* mAnmIdx     */ -1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 0,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 1,
            /* mNextPrmIdx */ 1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 2,
            /* mNextPrmIdx */ 8,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 3,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 4,
            /* mNextPrmIdx */ 1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 5,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 6,
            /* mNextPrmIdx */ 1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 0.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 7,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 8,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 9,
            /* mNextPrmIdx */ 1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 10,
            /* mNextPrmIdx */ 9,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 11,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 12,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
    };
    if(anmPrmIdx != 0xF) {
        mAnmPrmIdx = anmPrmIdx;
    }

    dLib_bcks_setAnm(m_arc_name, mpMorf, &mBckIdx, &mAnmPrmIdx, &mOldAnmPrmIdx, a_anm_bcks_tbl, a_anm_prm_tbl, param_2);

    /* Nonmatching */
}

/* 00006DE8-00006EA4       .text cancelGrab__6daFm_cFv */
void daFm_c::cancelGrab() {
    if(mpActorTarget != NULL) {
        if(field_0x684 != 0 && fopAcM_CheckStatus(mpActorTarget, fopAcStts_CARRY_e) && !checkPlayerGrabTarget()) {
            mpActorTarget->gravity = 0.0f;
            mpActorTarget->speedF = 0.0f;
            mpActorTarget->speed.x = 0.0f;
            mpActorTarget->speed.y = 0.0f;
            mpActorTarget->speed.z = 0.0f;
            mpActorTarget->current.angle.x = 0;
            mpActorTarget->current.angle.z = 0;
            mpActorTarget->shape_angle.x = 0;
            mpActorTarget->shape_angle.z = 0;
            fopAcM_cancelCarryNow(mpActorTarget);
        }
        field_0x684 = 0;
    }
    /* Nonmatching */
}

/* 00006EA4-0000702C       .text calcInvKine__6daFm_cFP10fopAc_ac_c */
void daFm_c::calcInvKine(fopAc_ac_c* i_this) {
    if (isBodyAppear() && i_this != NULL) {
        if (!(fopAcM_searchActorDistanceXZ(this, i_this) <= l_HIO.field_0x0DC)) { // weird but works?
            for(int i = 5; i >= 0; i--) {
                field_0x390 = i;
                cXyz temp(field_0x2E8[i]);
                if(l_HIO.field_0x00F[field_0x390] == 1) {
                    cXyz diff = mGrabPos - temp;
                    cXyz diff2 = field_0x61C - temp;
                    Quaternion quat;
                    
                    daObj::quat_rotVec(&quat, diff2, diff);
                    mDoMtx_quatSlerp(&field_0x330[i], &quat, &field_0x330[i], 0.75f - REG12_F(0x19));
                }
                mpMorf->calc();
            }
        }
    }
    /* Nonmatching */
}

/* 0000702C-000070F4       .text resetInvKine__6daFm_cFv */
void daFm_c::resetInvKine() {
    if (isBodyAppear()) {
        field_0x390 = 0;
        for(int i = 0; i < 6; i++) {
            mDoMtx_quatSlerp(&field_0x330[i], &ZeroQuat, &field_0x330[i], 0.05000000074505806f);
        }
        mpMorf->calc();
    }
    /* Nonmatching */
}

/* 000070F4-000071E0       .text grabBomb__6daFm_cFv */
void daFm_c::grabBomb() {
    if (fopAcM_GetName(mpActorTarget) == PROC_BOMB) {
        cXyz temp_pos(5.0f, -10.0f, 5.0f);
        cXyz pos = l_HIO.field_0x038 + temp_pos;
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(5));
        mDoMtx_stack_c::multVec(&pos, &mpActorTarget->current.pos);
        mpActorTarget->gravity = 0.0f;
        mpActorTarget->speedF = 0.0f;
        mpActorTarget->speed.x = 0.0f;
        mpActorTarget->speed.y = 0.0f;
        mpActorTarget->speed.z = 0.0f;
    }
    /* Nonmatching */
}
 
/* 000071E0-0000743C       .text grabTsubo__6daFm_cFv */
void daFm_c::grabTsubo() {
        if(fopAcM_GetName(mpActorTarget) == PROC_TSUBO) {
        daTsubo::Act_c* tsubo = (daTsubo::Act_c*)mpActorTarget;

        cXyz pos(0.0f, 0.0f, 0.0f);
        csXyz angle(0, 0, 0);
        switch(tsubo->prm_get_type()) {
            case 0:
                pos.set(25.0f, -25.0f, 0.0f);
                angle.set(0, 0, 5000);
                break;
            case 1:
            case 2:
                pos.set(55.0f, -55.0f, 0.0f);
                angle.set(0, 0, 5000);
                break;
            case 4:
                pos.set(50.0f, -45.0f, 0.0f);
                angle.set(0, 0, 7000);
                break;
            case 5:
                pos.set(0.0f, -15.0f, 0.0f);
                angle.set(0, 16000, 0);
                break;
            case 6:
                pos.set(40.0f, -20.0f, 0.0f);
                angle.set(0, 0, 7000);
                break;
        }

        cXyz pos2 = l_HIO.field_0x038 + pos;

        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(5));
        mDoMtx_stack_c::transM(pos2);
        mDoMtx_stack_c::ZXYrotM(angle);
        MTXCopy(mDoMtx_stack_c::get(), field_0x6BC);
        
        mDoMtx_stack_c::multVecZero(&mpActorTarget->current.pos);
        MtxToRot(mDoMtx_stack_c::get(), &mpActorTarget->shape_angle);
        
        tsubo->tevStr.mEnvrIdxOverride = tevStr.mEnvrIdxOverride;
    }
    /* Nonmatching */
}

/* 0000743C-00007680       .text grabPlayer__6daFm_cFv */
void daFm_c::grabPlayer() {
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    cXyz offset(pLink->getHeadTopPos() - pLink->current.pos);
    cXyz temp;
    cXyz temp2;
    temp.setall(0.0f);
    csXyz angle(0, 0, 0);
    switch (mAnmPrmIdx) {
        case 4:
        case 6:
            pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
            cXyz offset2 = pLink->getHeadTopPos() - pLink->current.pos;
            temp.set(5.0f, 0.0f, 10.0f);
            angle.set(-3000, 0, 7000);
            temp2 = l_HIO.field_0x038 + temp;
            temp2.y -= offset2.abs();

            mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(5));
            mDoMtx_stack_c::ZXYrotM(angle.x, angle.y, angle.z);
            mDoMtx_stack_c::transM(temp2);
            MTXCopy(mDoMtx_stack_c::get(), field_0x6BC);
            pLink->setPlayerPosAndAngle(mDoMtx_stack_c::get());

        case 5:
        default:
            break;
    }
    // switch(mAnmPrmIdx) {
        
    //     case 6:
    //         pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    //         cXyz offset2 = pLink->getHeadTopPos() - pLink->current.pos;
    //         temp.set(5.0f, 0.0f, 10.0f);
    //         csXyz angle2;
    //         angle2.set(-3000, 0, 7000);
    //         temp = l_HIO.field_0x038 + temp;
    //         temp.y -= offset2.abs();

    //         mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(5));
    //         mDoMtx_stack_c::ZXYrotM(angle2.x, angle2.y, angle2.z);
    //         mDoMtx_stack_c::transM(temp);
    //         MTXCopy(mDoMtx_stack_c::get(), field_0x6BC);
    //         pLink->setPlayerPosAndAngle(mDoMtx_stack_c::get());

    //         break;
    //     case 1:
    //     case 2:
    //     case 3:
    //         break;
    //     case 5:
    //         break;
        
    // }
    /* Nonmatching */
}

/* 00007680-00007828       .text grabNPC__6daFm_cFv */
void daFm_c::grabNPC() {
    if(isNpc(mpActorTarget) == true) {
        cXyz temp(0.0f, 0.0f, 0.0f);
        csXyz angle(0, 0, 0);
        if(fopAcM_GetName(mpActorTarget) == PROC_NPC_CB1) {
            temp.set(-15.0f, -10.0f, 8.0f);
            angle.x = 0;
            angle.y = 16000;
            angle.z = -4000;
        }

        if(fopAcM_GetName(mpActorTarget) == PROC_NPC_MD) {
            temp.set(10.0f, 0.0f, 5.0f);
            angle.x = 4000;
            angle.y = 18000;
            angle.z = -4000;
        }
        cXyz temp2 = l_HIO.field_0x038 + temp;
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(5));
        mDoMtx_stack_c::transM(temp2);
        mDoMtx_stack_c::ZXYrotM(angle.x, angle.y, angle.z);
        MTXCopy(mDoMtx_stack_c::get(), field_0x6BC);
        mDoMtx_stack_c::multVecZero(&mpActorTarget->current.pos);
        MtxToRot(mDoMtx_stack_c::get(), &mpActorTarget->shape_angle);
    }
    /* Nonmatching */
}

/* 00007828-00007A4C       .text searchTarget__6daFm_cFv */
void daFm_c::searchTarget() {
    if(!dComIfGp_event_runCheck() || field_0x2E4 != 0) {
        fopAc_ac_c* actor = mpActorTarget = (fopAc_ac_c*)fopAcM_Search(searchNearOtherActor_CB, this);
        if(mpActorTarget == NULL) {
            actor = fopAcM_SearchByName(PROC_NPC_CB1);
            if(actor == NULL) {
                actor = fopAcM_SearchByName(PROC_NPC_MD);
            }

            if(actor != NULL) {
                if(fopAcM_searchActorDistanceXZ(this, actor) < l_HIO.field_0x0E4 || checkHeight(actor)) {
                    if(field_0x2DC == 1) {
                        if(fopAcM_checkCarryNow(actor)) {
                            mpActorTarget = actor;
                        }
                    } else {
                        mpActorTarget = actor;
                    }
                }
            }
        }

        if(mpActorTarget == NULL && field_0x2DC != 2) {
            fopAc_ac_c* link_actor = dComIfGp_getLinkPlayer();
            daPy_lk_c* link_player = (daPy_lk_c*)link_actor;
            if(dComIfGp_getLinkPlayer() != NULL && !dComIfGp_checkPlayerStatus0(0, daPyStts0_HOOKSHOT_AIM_e | daPyStts0_UNK100_e)) {
                if(!checkPlayerGrabBomb()) {
                    if(!checkPlayerGrabNpc() && !isLinkControl()) {
                        if(!((daPy_lk_c*)dComIfGp_getLinkPlayer())->checkCarryActionNow() && link_player->getGrabActorID() == -1) {
                            if(fopAcM_searchActorDistanceXZ(this, link_actor) < l_HIO.field_0x0E4 || checkHeight(mpActorTarget)) {
                                mpActorTarget = link_actor;
                            }
                        }
                    }
                }
            }
        }
        
        actor = mpActorTarget;
        if(actor != NULL) {
            mProcId = fopAcM_GetID(actor);
        }
    }
    /* Nonmatching */
}

/* 00007A4C-00007C18       .text setBaseTarget__6daFm_cFv */
void daFm_c::setBaseTarget() {
    switch(field_0x2DC) {
        case 0:
            fopAcM_SearchByName(PROC_NPC_CB1); // unused?
            fopAc_ac_c* pMdActor = fopAcM_SearchByName(PROC_NPC_MD);
            daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();

            if (field_0x2D0 == 1 || field_0x2D0 == 2) {
                if (pMdActor == NULL) {
                    mBaseTarget = pLink;
                } else {
                    f32 dist = fopAcM_searchActorDistanceXZ(this, pLink);
                    f32 dist2 = fopAcM_searchActorDistanceXZ(this, pMdActor);
                    if (dist2 < l_HIO.field_0x0E8) {
                        mBaseTarget = pMdActor;
                    } else {
                        if (dist < l_HIO.field_0x0E8) {
                            mBaseTarget = pLink;
                        }
                    }
                }
            } else if (pMdActor != NULL) {
                mBaseTarget = pMdActor;
            } else {
                mBaseTarget = pLink;
            }
            break;
        case 1:
            mBaseTarget = daPy_getPlayerLinkActorClass();
            break;
        case 2:
            fopAc_ac_c* actor = fopAcM_SearchByName(PROC_NPC_CB1);

            if(actor != NULL) {
                mBaseTarget = actor;
            } else {
                actor = fopAcM_SearchByName(PROC_NPC_MD);
                if(actor != NULL) {
                    mBaseTarget = actor;
                }
            }
            break;
    }

    if (mBaseTarget == NULL) {
        field_0x9D0 = 0;
        field_0x9D4 = 0.0f;
    } else {
        field_0x9D0 = fopAcM_searchActorAngleY(this, mBaseTarget);
        field_0x9D4 = fopAcM_searchActorDistanceXZ(this, mBaseTarget);
    }
    /* Nonmatching */
}

/* 00007C18-00007C4C       .text turnToBaseTarget__6daFm_cFv */
void daFm_c::turnToBaseTarget() {
    cLib_addCalcAngleS2(&shape_angle.y, field_0x9D0, 4, 0x800);
    /* Nonmatching */
}

/* 00007C4C-00007C7C       .text isNpc__6daFm_cFP10fopAc_ac_c */
bool daFm_c::isNpc(fopAc_ac_c* i_actor) {
    if(i_actor == NULL) {
        return false;
    }
    return fopAcM_GetName(i_actor) == PROC_NPC_CB1 || fopAcM_GetName(i_actor) == PROC_NPC_MD; // suspicous if its BOOL or bool
    /* Nonmatching */
}

/* 00007C7C-00007CD0       .text checkHeight__6daFm_cFP10fopAc_ac_c */
bool daFm_c::checkHeight(fopAc_ac_c* i_actor) {
    if (i_actor == NULL) {
        return false;
    }

    f32 diff = std::fabsf(i_actor->current.pos.y - current.pos.y);
    f32 half = 0.5f;

    return !(diff > l_HIO.field_0x0A8 * half);  
}


/* 00007CD0-00007CEC       .text isLink__6daFm_cFP10fopAc_ac_c */
bool daFm_c::isLink(fopAc_ac_c* i_actor) {
    return i_actor == dComIfGp_getLinkPlayer();
    /* Nonmatching */
}

/* 00007CEC-00007D0C       .text isLinkControl__6daFm_cFv */
bool daFm_c::isLinkControl() {
    return dComIfGp_getPlayer(0) != dComIfGp_getLinkPlayer();
    /* Nonmatching */
}

/* 00007D0C-00007F5C       .text areaCheck__6daFm_cFv */
bool daFm_c::areaCheck() {
    bool ret = true;

    int i;
    s16 angle;

    for(i = 0, angle = 0; i < 12; i++, angle += 0x1555) {
        cXyz temp(l_HIO.field_0x0E0, -30.0f, 0.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM((s16)angle);
        mDoMtx_stack_c::transM(temp);
        
        mDoMtx_stack_c::multVecZero(&field_0xA48[i]);

        cXyz temp2 = field_0xA48[i];
        temp2.y += 60.0f;

        if(field_0x2D0 == 0 || field_0x2D0 == 1) {
            if((field_0xA48[i] - field_0x69C).absXZ() > field_0x2E0) {
                field_0xAD8[i] = false;
                ret = false;
            } else {
                field_0xAD8[i] = true;
            }
        }
        if(field_0xAD8[i] == true || field_0x2D0 == 2) {
            if(!lineCheck(&temp2, &field_0xA48[i])) {
                field_0xAD8[i] = false;
                ret = false;

            } else {
                field_0xAD8[i] = true;
            }
        }
    }
    return ret;
    /* Nonmatching */
}

/* 00007F5C-00007FDC       .text lineCheck__6daFm_cFP4cXyzP4cXyz */
bool daFm_c::lineCheck(cXyz* param_1, cXyz* param_2) {
    mLinChk.Set(param_1, param_2, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
        *param_2 = mLinChk.mLin.GetEnd();
        return true;
    }
    return false;
    /* Nonmatching */
}

/* 00007FDC-00008044       .text setRnd__6daFm_cFii */
int daFm_c::setRnd(int param_1, int param_2) {
    f32 rnd = cM_rndF(std::fabsf((f32)(param_2 - param_1)));
    return param_1 + (int)rnd;
    /* Nonmatching */
}

/* 00008044-00008114       .text setHoleEffect__6daFm_cFv */
void daFm_c::setHoleEffect() {
    if(mpFollowEcallBack.getEmitter() == NULL) {
        dComIfGp_particle_setShipTail(dPa_name::ID_SCENE_809E, &current.pos, NULL, NULL, 0xFF, &mpFollowEcallBack, fopAcM_GetRoomNo(this));
    }
    JPABaseEmitter* emitter = mpFollowEcallBack.getEmitter();
    
    if(emitter != NULL) {
        Vec scale = {field_0x3E0, field_0x3E0, field_0x3E0};
        emitter->setGlobalScale(scale);
    }
    /* Nonmatching */
}

/* 00008114-000081E0       .text holeExecute__6daFm_cFv */
void daFm_c::holeExecute() {
    
    if(isHoleAppear()) {
        mBtkAnm.play();
        fopAcM_seStart(this, JA_SE_CM_FM_SPOT, 0);
        fopAcM_SetStatusMap(this, 0x20);
        setHoleEffect();
    } else {
        fopAcM_ClearStatusMap(this);
        mpFollowEcallBack.end();
    }

    /* Nonmatching */
}

/* 000081E0-00008258       .text setHoleScale__6daFm_cFfff */
bool daFm_c::setHoleScale(f32 param_1, f32 param_2, f32 param_3) {
    cLib_addCalc2(&field_0x3E0, param_1, param_2, param_3);
    return std::fabsf(field_0x3E0 - param_1) <= param_3;
    /* Nonmatching */
}

/* 00008258-00008564       .text _execute__6daFm_cFv */
bool daFm_c::_execute() {
    holeExecute();
    fopAcM_SearchByID(mProcId, &mpActorTarget);
    daBomb_c* bomb = (daBomb_c*)mpActorTarget;
    if(bomb != NULL && fopAcM_GetName(bomb) == PROC_BOMB && bomb->chk_state(daBomb_c::STATE_0)) {
        mpActorTarget = NULL;
        mProcId = 0;
        modeProcInit(7);
    }

    if(enemy_ice(&mEnemyIce)) {
        iceProc();
        return true;
    }

    setBaseTarget();
    if(mBaseTarget == NULL) {
        bodySetMtx();
        holeSetMtx();
        mpMorf->calc();
        return true;
    } else {
        field_0xAE4 = areaCheck();
        field_0xAE5 = 0;

        cXyz temp = current.pos;
        temp.y += 100.0f;

        cXyz temp2 = mBaseTarget->current.pos;
        temp2.y += 100.0f;

        if (field_0x9D4 < l_HIO.field_0x0E8 && lineCheck(&temp, &temp2) == true) { // is linecheck BOOL?
            field_0xAE5 = 1;
        }
        if (field_0x2E4 != 0) {
            field_0xAE5 = 0;
        }
        
        if (mpActorTarget != NULL) {
            if (mMode == 8 && mAnmPrmIdx == 4 && isLink(mpActorTarget)) {
                spAttackVJump();
            } else if (mAnmPrmIdx == 0xB || mAnmPrmIdx == 0xC) {
                spAttackJump();
            } else {
                spAttackNone();
            }
        }
        modeProc(PROC_1_e, 0x15);
        setAnm(0xF, false);
        mpMorf->play(&current.pos, 0, 0);
        mpMorf->calc();

        if (field_0x684 != 0) {
            
            if (!fopAcM_SearchByID(mProcId, &mpActorTarget)) {
                field_0x684 = 0;
            }

            switch(field_0x684) {
                case 1:
                    grabPlayer();
                    break;
                case 4:
                    grabNPC();
                    break;
                case 2:
                    grabBomb();
                    break;
                case 3:
                    grabTsubo();
                    break;

            }
        }
        field_0x660.y = current.pos.y;
        fopAcM_posMoveF(this, mStts.GetCCMoveP());

        // f_op_actor_mng::fopAcM_posMoveF((fopAc_ac_c *)this,(cXyz *)&this->mStts);
        mAcch.CrrPos(*dComIfG_Bgsp());

        bodySetMtx();
        holeSetMtx();
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        setAttention();
        setCollision();
    }
    return true;

    /* Nonmatching */
}

/* 00008564-000085A4       .text MtxToRot__6daFm_cFPA4_fP5csXyz */
void daFm_c::MtxToRot(Mtx i_mtx, csXyz* angle) {
    Mtx mtx;
    mDoMtx_inverseTranspose(i_mtx, mtx);
    mDoMtx_MtxToRot(mtx, angle);
    /* Nonmatching */
}

static const u32 dummy[] = {
    0x0000FF80,
    0x00FF0080,
};

/* 000085A4-000089A4       .text debugDraw__6daFm_cFv */
void daFm_c::debugDraw() {


    static const GXColor color_ok = {0x00, 0xFF, 0x00, 0x80};
    static const GXColor color_ng = {0xFF, 0x00, 0x00, 0x80};

    Mtx mtx;
    cXyz temp;
    cXyz temp2;
    cXyz temp3;
    cXyz temp4;
    cXyz temp5;
    cXyz temp6;
    cXyz temp7;
    cXyz temp8;
    cXyz temp9;

    if (l_HIO.field_0x00C != 0) { // maybe bool field hio


        // iVar1 = 0;
        // iVar4 = 0xc;
        for (int i = 0; i != 12; i++) {
            temp = field_0xA48[i];
            temp.y += 60.0f;
        }

        if (field_0x9D4 < l_HIO.field_0x0E8 && mBaseTarget != NULL) {
            temp2 = current.pos;
            temp2.y += 100.0f;

            temp3 = mBaseTarget->current.pos;
            temp3.y += 100.0f;
        }
        temp4 = field_0x69C;
        temp4.y += 20.0f;
    if (l_HIO.field_0x00A != 0) {
        temp5 = current.pos;
        temp5.y += 20.0f;
        temp6 = field_0x690;
        temp6.y += 20.0f;
        // local_7c = (this->parent).parent.current.pos.x;
        // local_74 = (this->parent).parent.current.pos.z;
        // local_88 = (this->field85_0x690).x;
        // local_80 = (this->field85_0x690).z;
        // local_78 = (this->parent).parent.current.pos.y + 20.0;
        // local_84 = (this->field85_0x690).y + 20.0;
    }
    if (l_HIO.field_0x009 != 0) {
        temp7 = current.pos;
        temp8.set(field_0x690.x, temp7.y + 20.0f, field_0x690.z);
        // local_dc = (this->parent).parent.current.pos.x;
        // local_d8 = (this->parent).parent.current.pos.y;
        // local_d4 = (this->parent).parent.current.pos.z;
        // local_a0 = (this->field85_0x690).x;
        // local_98 = (this->field85_0x690).z;
        // local_90 = local_d8 + 20.0;
        // local_9c = (this->field85_0x690).y + 20.0;
        // iVar1 = (int)DAT_8065bdd4;
        // if ((iVar1 != 0x7ffff) || (DAT_8065bdd4 != 0)) {
        // iVar3 = (int)(this->parent).parent.shape_angle.y;
        // iVar4 = (int)(iVar3 + iVar1 & 0xffffU) >> (JKernel::JMath::jmaSinShift & 0x3f);
        // local_a4 = local_d4 + DAT_8065be00 * JKernel::JMath::jmaCosTable[iVar4];
        // local_ac = local_dc + DAT_8065be00 * JKernel::JMath::jmaSinTable[iVar4];
        // iVar1 = (int)(iVar3 - iVar1 & 0xffffU) >> (JKernel::JMath::jmaSinShift & 0x3f);
        // local_b0 = local_d4 + DAT_8065be00 * JKernel::JMath::jmaCosTable[iVar1];
        // local_b8 = local_dc + DAT_8065be00 * JKernel::JMath::jmaSinTable[iVar1];
        // local_b4 = local_d8;
        // local_a8 = local_d8;
        // }
        // iVar1 = (int)DAT_8065bdd6;
        // if ((iVar1 != 0x7ffff) || (DAT_8065bdd6 != 0)) {
        // iVar3 = (int)(this->parent).parent.shape_angle.y;
        // iVar4 = (int)(iVar3 + iVar1 & 0xffffU) >> (JKernel::JMath::jmaSinShift & 0x3f);
        // local_bc = local_d4 + DAT_8065be00 * JKernel::JMath::jmaCosTable[iVar4];
        // local_c4 = local_dc + DAT_8065be00 * JKernel::JMath::jmaSinTable[iVar4];
        // iVar1 = (int)(iVar3 - iVar1 & 0xffffU) >> (JKernel::JMath::jmaSinShift & 0x3f);
        // local_c8 = local_d4 + DAT_8065be00 * JKernel::JMath::jmaCosTable[iVar1];
        // local_d0 = local_dc + DAT_8065be00 * JKernel::JMath::jmaSinTable[iVar1];
        // local_cc = local_d8;
        // local_c0 = local_d8;
        // }
        // local_d8 = local_d8 + DAT_8065bde4;
        // local_94 = local_dc;
        // local_8c = local_d4;
    }
    }
    if (l_HIO.field_0x00B != 0) {
        for (int i = 6; i != 0; i--) {
            temp8 = field_0xA48[i - 6];
            temp8.y += 60.0f;
        }

    }
    if (l_HIO.field_0x006 != 0) {
        dLib_debugDrawAxis(field_0x6BC, 100.0f);
    }
    if (l_HIO.field_0x007 != 0) {
        MTXCopy(fopAcM_GetModel(this)->getAnmMtx(5), mtx);
        dLib_debugDrawAxis(mtx, 100.0f);
    }
    if (l_HIO.field_0x005 != 0) {
        daPy_getPlayerLinkActorClass()->getHeadTopPos();
    }
    /* Nonmatching */
}

    static const u32 dummy2[] = {
        0x0000FF80,
        0x0000FF80,
        0xFF000080,
        0x00FF0080,
        0xFF00FF80,
        0x00FFFF80,
        0xFF00FF80,
        0x0000FF80,
        0x00FF0080,
        0xFF000080,
        0xFFFF0080,
        0xFF000080,
        0xFF000080,
        0x00FF0080,
        0x00FF0080,
        0xFF000080,
        0xFF000080,
        0x00FF0080,
        0x00FF0080,
        0x00FF0080,
        0x0000FF80,
        0xFF000080,
        0x00FF0080,
        0x00FF0080,
        0xFF000080,
        0x00FF0080,
    };

/* 000089A4-00008A14       .text holeDraw__6daFm_cFv */
void daFm_c::holeDraw() {
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mBtkAnm.entry(mpModel->getModelData());
    mDoExt_modelUpdateDL(mpModel);
    mBtkAnm.remove(mpModel->getModelData());

    /* Nonmatching */
}

/* 00008A14-00008A88       .text bodyDraw__6daFm_cFv */
void daFm_c::bodyDraw() {
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    if(mEnemyIce.mFreezeTimer > 0x14) {
        dMat_control_c::iceEntryDL(mpMorf, -1, &mInvisibleModel);
    } else {
        mpMorf->entryDL();
    }

    /* Nonmatching */
}

/* 00008A88-00008B4C       .text _draw__6daFm_cFv */
bool daFm_c::_draw() {
    debugDraw();
    if(field_0x3E0 > 0.015f) {
        holeDraw();
    }

    if(isBodyAppear()) {
        bodyDraw();
        dSnap_RegistFig(DSNAP_TYPE_UNKB5, this, field_0x61C, shape_angle.y, 1.0f, 1.0f, 1.0f);
    }
    return true;
    /* Nonmatching */
}

/* 00008B4C-00008C78       .text getArg__6daFm_cFv */
void daFm_c::getArg() {
    u32 params = fopAcM_GetParam(this);

    s16 homeAngleX = home.angle.x;
    s16 homeAngleZ = home.angle.z;
    field_0x2C7 = params;
    field_0x2D0 = fopAcM_GetParamBit(params, 0x8, 2);
    field_0x2DC = fopAcM_GetParamBit(params, 0xa, 2);
    m_path_no = fopAcM_GetParamBit(params, 0x10, 8);
    field_0x2D4 = params >> 0x18;
    field_0x2D8 = homeAngleX & 0xff;
    field_0x2C8 = fopAcM_GetParamBit(homeAngleX, 0x08, 8);
    params = homeAngleZ & 0xff;

    if(params == 0xff) {
        field_0x2E0 = 0.0f;
    } else {
        field_0x2E0 = (f32)params * 100.0f;
    }

    if((f32)home.angle.y != 0.0f && field_0x2D4 != 0xff) {
        field_0x2E4 = 1;
    }

    if(field_0x2D0 == 3) {
        field_0x2D0 = 0;
    }

    if(field_0x2DC == 3) {
        field_0x2DC = 0;
    }

    if(field_0x2E0 == 0.0f) {
        field_0x2E0 = 3000.0f;
    }

    home.angle.z = 0;
    current.angle.z = 0;
    shape_angle.z = 0;
    home.angle.x = 0;
    current.angle.x = 0;
    shape_angle.x = 0;
    /* Nonmatching */
}

/* 00008C78-000090DC       .text createInit__6daFm_cFv */
void daFm_c::createInit() {
    mStts2.Init(200.0f, 0.0f, this);
    mSph.Set(m_sph_src);
    mSph.SetStts(&mStts2);
    mStts.Init(200.0f, 0.0f, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    mAcchCir.SetWall(30.0f, 200.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));

    mAcch.SetRoofNone();
    if(field_0x2E4 != 0) {
        mAcch.SetWallNone();
    }

    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        switch(i) {
            case 0: 
            case 1:
            case 2:
            case 3:
            case 5:
                modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
                break;

        }
    }

    for(int i = 0; i < 6; i++) {
        field_0x330[i] = ZeroQuat;
    }
    bodySetMtx();
    holeSetMtx();
    mpMorf->calc();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);

    if(field_0x2D0 == 0) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Fmaster", 0);
    } else if(field_0x2D0 == 1) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Fmastr1", 0);
    } else if(field_0x2D0 == 2) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Fmastr2", 0);
    }

    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -300.0f, -50.0f, -300.0f, 300.0f, 400.0f, 300.0f);
    if(m_path_no != 0xFF) {
        mpPath = dPath_GetRoomPath(m_path_no, fopAcM_GetRoomNo(this));
    }
    mEnemyIce.mpActor = this;
    mEnemyIce.m00C = 1;
    mEnemyIce.mWallRadius = 100.0f;
    mEnemyIce.mCylHeight = 200.0f;

    mBtHeight = 240.0f;
    mBtBodyR = 100.0f;
    attention_info.flags = 0;
    stealItemLeft = 3;
    max_health = l_HIO.mMaxHealth;
    health = max_health;
    mGrabPos = current.pos;
    
    field_0x684 = 0;
    mpActorTarget = NULL;
    field_0x69C = current.pos;
    setBaseTarget();
    field_0x690 = current.pos;
    setAnm(8, false);
    field_0x394 = cM_rndF(9.0f) + 1.0f;
    field_0x610 = l_HIO.field_0x02C;
    if(mMode != 0x11) {
        if(field_0x2D4 != 0xff && !dComIfGs_isSwitch(field_0x2D4, fopAcM_GetRoomNo(this))) {
            modeProc(PROC_0_e, 0);
        } else {
            switch(field_0x2D0) {
                case 0:
                    modeProc(PROC_0_e, 2);
                    break;
                case 1:
                    modeProc(PROC_0_e, 3);
                    JUT_ASSERT(0x1444, m_path_no != 0xff);
                    break;
                case 2:
                    modeProc(PROC_0_e, 4);
                    break;
            }
        }
    }
    /* Nonmatching */
}

/* 000090DC-00009258       .text _create__6daFm_cFv */
cPhs_State daFm_c::_create() {
    fopAcM_SetupActor(this, daFm_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, m_arc_name);
    if(phase_state == cPhs_COMPLEATE_e) {
        if(parentActorID != -1) {
            fopAc_ac_c* ac = fopAcM_SearchByID(parentActorID);

            if(ac != NULL && fopAc_IsActor(ac) && isLink(ac)) {
                modeProc(PROC_0_e, 0x11);
            }
        }

        if(mMode != 0x11) {
            getArg();
            if(field_0x2D8 != 0xff && dComIfGs_isSwitch(field_0x2D8, fopAcM_GetRoomNo(this))) {
                return cPhs_ERROR_e;
            }

            if(field_0x2D4 != 0xff && dComIfGs_isSwitch(field_0x2D4, fopAcM_GetRoomNo(this)) && field_0x2E4 != 0) {
                return cPhs_ERROR_e;
            }
        }

        if(!fopAcM_entrySolidHeap(this, createHeap_CB, 0x2100)) {
            return cPhs_ERROR_e;
        }
        createInit();
    }
    
    return phase_state;
    /* Nonmatching */
}

/* 0000A094-0000A0FC       .text _delete__6daFm_cFv */
bool daFm_c::_delete() {
    cancelGrab();
    dComIfG_resDelete(&mPhs, m_arc_name);
    mpFollowEcallBack.remove();
    if(heap != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
    /* Nonmatching */
}

/* 0000A0FC-0000A11C       .text daFmCreate__FPv */
static cPhs_State daFmCreate(void* i_this) {
    return ((daFm_c*)i_this)->_create();
}

/* 0000A11C-0000A140       .text daFmDelete__FPv */
static BOOL daFmDelete(void* i_this) {
    return ((daFm_c*)i_this)->_delete();
}

/* 0000A140-0000A164       .text daFmExecute__FPv */
static BOOL daFmExecute(void* i_this) {
    return ((daFm_c*)i_this)->_execute();
}

/* 0000A164-0000A188       .text daFmDraw__FPv */
static BOOL daFmDraw(void* i_this) {
    return ((daFm_c*)i_this)->_draw();
}

/* 0000A188-0000A190       .text daFmIsDelete__FPv */
static BOOL daFmIsDelete(void*) {
    return TRUE;
}

static actor_method_class daFmMethodTable = {
    (process_method_func)daFmCreate,
    (process_method_func)daFmDelete,
    (process_method_func)daFmExecute,
    (process_method_func)daFmIsDelete,
    (process_method_func)daFmDraw,
};

actor_process_profile_definition g_profile_FM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_FM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daFm_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_FM,
    /* Actor SubMtd */ &daFmMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
