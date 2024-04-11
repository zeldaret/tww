/**
 * d_a_npc_md.cpp
 * Player - Medli
 */

#include "d/actor/d_a_npc_md.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_mtx.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_snap.h"
#include "d/actor/d_a_ship.h"
#include "d/d_kankyo_wether.h"
#include "d/d_camera.h"
#include "d/d_detect.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static u8 temp[0x4C]; // TODO

static daNpc_Md_HIO_c l_HIO;

static cXyz l_ms_light_local_vec(0.0f, 0.0f, -10000.0f);
static cXyz l_ms_light_local_start(5.0f, 7.0f, 0.0f);

static char* l_arc_name = "Md";
static char* l_arc_name_ship = "Md_ship";
static char* l_staff_name = "Md1";

static char* event_name_tbl[] = {
    "Md_ItemGet",
    "Md_RopeGet",
    "MD_FLY",
    "md_cliff",
    "Md_Fly2",
    "Md_Tact",
    "Md_TactTrue",
    "Md_HarpTalk",
    "OPTION_CHAR_END",
    "DEFAULT_TALK_XY",
};

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_BOOMERANG | AT_TYPE_WIND | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_PLAYER,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK4 | CO_SPRM_VSGRP,
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};

static dCcD_SrcCyl l_light_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
        /* SrcObjCo  SPrm    */ 0,
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};

static dCcD_SrcCps l_fan_light_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_LIGHT,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_GRP,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ G_AT_SPRM_NO_HIT_MARK,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 70.0f,
    },
};

static dCcD_SrcCyl l_wind_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
        /* SrcObjCo  SPrm    */ 0,
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};


/* 000000EC-0000013C       .text __ct__15daNpc_Md_HIO6_cFv */
daNpc_Md_HIO6_c::daNpc_Md_HIO6_c() {
    m04 = 500.0f;
    m08 = 430;
    m0A = 9000;
    m0C = -5000;
    m0E = -9000;
    m10 = 0;
    m12 = 0;
    m14 = 0;
    m16 = 0;
}

/* 0000013C-00000164       .text __ct__15daNpc_Md_HIO5_cFv */
daNpc_Md_HIO5_c::daNpc_Md_HIO5_c() {
    m4 = 16.0f;
    m8 = 0.6f;
}

/* 00000164-00000188       .text __ct__15daNpc_Md_HIO4_cFv */
daNpc_Md_HIO4_c::daNpc_Md_HIO4_c() {
    /* Nonmatching */
    m4 = 86.0f;
    m8 = 0;
}

/* 00000188-000001F4       .text __ct__15daNpc_Md_HIO3_cFv */
daNpc_Md_HIO3_c::daNpc_Md_HIO3_c() {
    m04 = 0.8f;
    m08 = 0.2f;
    m0C = -5.0f;
    m10 = -5.0f;
    m14 = 0.0f;
    m18 = 0;
    m1A = 0;
    m1C = 0;
    m1E = 3800;
    m20 = 5800;
    m22 = 0x7FFF;
    m24 = -0x7FFF;
}

/* 000001F4-00000274       .text __ct__15daNpc_Md_HIO2_cFv */
daNpc_Md_HIO2_c::daNpc_Md_HIO2_c() {
    m26 = 0x19;
    m28 = 0x7FFF;
    m2A = 1;
    m04 = 5.0f;
    m08 = 17.0f;
    m0C = 7.0f;
    m10 = 6.0f;
    m14 = 0.7f;
    m20 = 3300;
    m22 = 2900;
    m24 = 5;
    m18 = 2.6f;
    m1C = 0.6f;
}

/* 00000274-00000574       .text __ct__14daNpc_Md_HIO_cFv */
daNpc_Md_HIO_c::daNpc_Md_HIO_c() {
    mNpc.m04 = -25.0f;
    mNpc.mMaxHeadX = 0x2328;
    mNpc.mMaxHeadY = 0x2328;
    mNpc.mMaxBackboneX = 0x0;
    mNpc.mMaxBackboneY = 0x1F40;
    mNpc.mMinHeadX = -0x2328;
    mNpc.mMinHeadY = -0x2328;
    mNpc.mMinBackboneX = 0x0;
    mNpc.mMinBackboneY = -0x1F40;
    mNpc.mMaxTurnStep = 0x1000;
    mNpc.mMaxHeadTurnVel = 0x800;
    mNpc.mAttnYOffset = 130.0f;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0x0;
    mNpc.mMaxAttnDistXZ = 150.0f;
    mpActor = NULL;
    m0B8 = 770.0f;
    m0BC = 250.0f;
    m0C0 = -450.0f;
    m0C4 = 90.0f;
    m0C8 = 400.0f;
    m0CC = 600.0f;
    m0D0 = 0.05f;
    m0D4 = 17.0f;
    m0D8 = 0.0f;
    m0DC = 0.5f;
    m0E0 = 0.3f;
    m0E4 = 0.9f;
    m0E8 = 15.0f;
    m0EC = 22.0f;
    m0F0 = 9.0f;
    m0F4 = 4.0f;
    m0F8 = -1.51367f;
    m0FC = -1.09863f;
    m100 = -0.56152f;
    m104 = 0.1f;
    m108 = 0.2f;
    m10C = 10.0f;
    m110 = -50.0f;
    m114 = 1.3f;
    m128 = 1200.0f;
    m12C = 1500.0f;
    m118 = 1.0f;
    m11C = 1.5f;
    m120 = 2.0f;
    m124 = 1.6f;
    m130 = 3.0f;
    m134 = 1.25f;
    m138 = 0.2f;
    m13C = 100.0f;
    m140 = 50.0f;
    m144 = 9.0f;
    m1B4 = 0x17;
    m1B6 = 0x14;
    m1C7 = 0x0;
    m148 = 0.9f;
    m1C6 = 0x1;
    m14C = 6.0f;
    m1B8 = 0x4000;
    m150 = 10.0f;
    m1BA = 0x78;
    m1BC = 0x1F4;
    m154 = 5.0f;
    m158 = 2.2f;
    m15C = -11.681f;
    m160 = 1.3f;
    m164 = 88.692f;
    m168 = 57.066f;
    m16C = 179.286f;
    m1C8 = 0x0;
    m170 = 0.0f;
    m174 = 1.0f;
    m178 = 1.5f;
    m17C = -100.0f;
    m180 = 100.0f;
    m184 = 10.0f;
    m188 = 1.0f;
    m18C = -10.0f;
    m1BE = 0x46;
    m1C0 = 0x5;
    m1C2 = 0x1C2;
    m1C4 = 0x96;
    m190 = 43.0f;
    m194 = 14.65f;
    m198 = 13.99f;
    m19C = 0.0f;
    m1A0 = -98.0f;
    m1A4 = 0.0f;
    m1A8 = 3.0f;
    m1AC = 1000.0f;
    m1B0 = 1000.0f;
    mChildID = -0x1;
}

/* 000006DC-000006FC       .text daNpc_Md_XyCheckCB__FPvi */
static s16 daNpc_Md_XyCheckCB(void* i_this, int param_1) {
    return static_cast<daNpc_Md_c*>(i_this)->XyCheckCB(param_1);
}

/* 000006FC-000007FC       .text XyCheckCB__10daNpc_Md_cFi */
s16 daNpc_Md_c::XyCheckCB(int equippedItemIdx) {
    u8 selectItemNo = dComIfGp_getSelectItem(equippedItemIdx);
    if (isTypeSea()) {
        if (selectItemNo == dItem_WIND_WAKER_e) {
            return TRUE;
        }
        if (selectItemNo == GOLDEN_FEATHER) {
            if (!dComIfGs_isEventBit(0x2E40) || (dComIfGs_isEventBit(0x2E40) && m_seaTalk)) {
                return TRUE;
            }
        }
    } else if (isTypeM_Dai() || isTypeEdaichi()) {
        if (selectItemNo == GOLDEN_FEATHER && !dComIfGs_isEventBit(0x3B80)) {
            return TRUE;
        }
    }
    if (selectItemNo == GOLDEN_FEATHER) {
        dComIfGs_onEventBit(0x2C08);
    }
    return FALSE;
}

/* 000007FC-0000081C       .text daNpc_Md_XyEventCB__FPvi */
static s16 daNpc_Md_XyEventCB(void* i_this, int param_1) {
    return static_cast<daNpc_Md_c*>(i_this)->XyEventCB(param_1);
}

/* 0000081C-00000864       .text XyEventCB__10daNpc_Md_cFi */
s16 daNpc_Md_c::XyEventCB(int equippedItemIdx) {
    u8 selectItemNo = dComIfGp_getSelectItem(equippedItemIdx);
    if (selectItemNo == dItem_WIND_WAKER_e) {
        offDefaultTalkXY();
        return mEventIdxTable[5];
    } else if (selectItemNo == GOLDEN_FEATHER) {
        onDefaultTalkXY();
    }
    return -1;
}

/* 00000864-00000884       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Md_c*>(i_this)->createHeap();
}

/* 00000884-00000D80       .text create__10daNpc_Md_cFv */
s32 daNpc_Md_c::create() {
    m313D = 0;
    strcpy(mModelArcName, l_arc_name);
    int heapSizeIdx = 0;
    
    fopAcM_SetupActor(this, daNpc_Md_c);
    
    mType = fopAcM_GetParam(this) >> 0x08;
    if (mType == -2) {
        dComIfGs_onEventBit(0x1620);
    } else {
        if (dComIfGs_isCollect(0, 2)) {
            if (strcmp(dComIfGp_getStartStageName(), "M_DaiB") != 0) {
                return cPhs_ERROR_e;
            } else {
                setTypeM_DaiB();
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "sea") == 0) {
            if (dComIfGs_isEventBit(0x2E04) || !dComIfGs_isEventBit(0x1820) ||
                !dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC))
            {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Atorizk") == 0) {
            if (dComIfGs_isEventBit(0x2E04) || dNpc_chkLetterPassed()) {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Adanmae") == 0) {
            if (dComIfGs_isEventBit(0x2E04) || !dNpc_chkLetterPassed()) {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "M_Dra09") == 0) {
            if (dComIfGs_isEventBit(0x2E04) || dComIfGs_isEventBit(0x1101)) {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Edaichi") == 0) {
            if (!dComIfGs_isEventBit(0x2E04) || dComIfGs_isEventBit(0x2920)) {
                return cPhs_ERROR_e;
            }
            setTypeEdaichi();
        } else if (strcmp(dComIfGp_getStartStageName(), "M_Dai") == 0) {
            if (!dComIfGs_isEventBit(0x2E04) || !dComIfGs_isEventBit(0x2920)) {
                return cPhs_ERROR_e;
            }
            setTypeM_Dai();
        } else if (strcmp(dComIfGp_getStartStageName(), "M_DaiB") == 0) {
            return cPhs_ERROR_e;
        }
    }
    
    if (!dComIfGs_isEventBit(0x2E04) && dComIfGs_isEventBit(0x1608)) {
        setTypeShipRide();
        strcpy(mModelArcName, l_arc_name_ship);
        heapSizeIdx = 1;
    }
    
    s32 phase_state = dComIfG_resLoad(&mPhase, mModelArcName);
    m313D = 1;
    if (phase_state == cPhs_COMPLEATE_e) {
        if (dComIfGp_getCb1Player() != NULL) {
            return cPhs_ERROR_e;
        }
        
        static int l_heep_size[] = {
            0x7660,
            0x61C0,
        };
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, l_heep_size[heapSizeIdx])) {
            mpMorf = NULL;
            mpArmMorf = NULL;
            mpWingMorf = NULL;
            return cPhs_ERROR_e;
        }
        
        if (isTypeM_Dai()) {
            u8 flag = dComIfGs_getPlayerPriestFlag();
            if (flag == 2) {
                s8 roomNo = dComIfGs_getPlayerPriestRoomNo();
                s16 angle = dComIfGs_getPlayerPriestRotate();
                cXyz& pos = dComIfGs_getPlayerPriestPos();
                dComIfGs_setRestartOption(&pos, angle, roomNo, 2);
            }
            checkRestart(2);
        }
        
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        
        if (l_HIO.mChildID < 0) {
            l_HIO.mChildID = mDoHIO_root.mDoHIO_createChild("リト族（メドリ）", &l_HIO); // "Rito (Medli)" (Ritozoku (Medli))
            l_HIO.mpActor = this;
        }
        
        if (!init()) {
            return cPhs_ERROR_e;
        }
        
        setBaseMtx();
        fopAcM_setStageLayer(this);
    }
    
    return phase_state;
}

/* 000012C0-00001444       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Md_c* i_this = (daNpc_Md_c*)model->getUserArea();
        if (i_this) {
            static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
            static cXyz l_offsetEyePos(15.0f, 0.0f, 0.0f);
            
            s32 jntNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->getAttentionBasePos());
            mDoMtx_stack_c::XrotM(i_this->getHead_y());
            mDoMtx_stack_c::ZrotM(-i_this->getHead_x());
            mDoMtx_stack_c::multVec(&l_offsetEyePos, &i_this->getEyePos());
            i_this->incAttnSetCount();
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

static Vec waistVecDat[4] = {
    {40.0f, -10.0f, -30.0f},
    {40.0f, -10.0f, 30.0f},
    {-30.0f, -10.0f, -30.0f},
    {-30.0f, -10.0f, 30.0f},
};

/* 00001444-0000154C       .text waistNodeCallBack__FP7J3DNodei */
static BOOL waistNodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Md_c* i_this = (daNpc_Md_c*)model->getUserArea();
        if (i_this) {
            s32 jntNo = joint->getJntNo();
            mDoMtx_multVecArray(model->getAnmMtx(jntNo), waistVecDat, i_this->getPHairWall(), ARRAY_SIZE(waistVecDat));
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            if (cLib_checkBit(i_this->m30F0, 0x4000UL)) {
                mDoMtx_stack_c::XrotM(i_this->getWaistRotY());
                mDoMtx_stack_c::ZrotM(i_this->getWaistRotX());
            } else {
                mDoMtx_stack_c::XrotM(i_this->getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 0000154C-0000160C       .text armNodeCallBack__FP7J3DNodei */
static BOOL armNodeCallBack(J3DNode* node, int param_1) {
    // This handles copying the matrices of Medli's arms and wings from the body model to the
    // separate arm/wing models.
    if (!param_1) {
        J3DModel* armModel = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Md_c* i_this = (daNpc_Md_c*)armModel->getUserArea();
        if (i_this) {
            s32 armJntNo = joint->getJntNo();
            s32 bodyJntNo;
            if (armJntNo == i_this->getArmRlocJntNum()) {
                bodyJntNo = i_this->getArmRJntNum();
            } else if (armJntNo == i_this->getArmLlocJntNum()) {
                bodyJntNo = i_this->getArmLJntNum();
            }
            J3DModel* bodyModel = i_this->getModel();
            cMtx_copy(bodyModel->getAnmMtx(bodyJntNo), J3DSys::mCurrentMtx);
            armModel->setAnmMtx(armJntNo, bodyModel->getAnmMtx(bodyJntNo));
        }
    }
    return TRUE;
}

/* 0000160C-00001C60       .text hairCross__FP4cXyzP4cXyzP4cXyz */
static BOOL hairCross(cXyz* i_r3, cXyz* i_r4, cXyz* i_r5) {
    cM3dGTri r1_198(&i_r3[0], &i_r3[1], &i_r3[2]);
    cM3dGTri r1_160(&i_r3[1], &i_r3[3], &i_r3[2]);
    
    cM3dGLin r1_144;
    r1_144.SetStartEnd(*i_r4, *i_r5);
    
    cXyz r1_138;
    if (r1_198.cross(&r1_144, &r1_138, true, false)) {
        r1_198.Up(2.0f);
        if (r1_198.cross(&r1_144, &r1_138, true, false)) {
            f32 f31 = r1_198.getSignedLenPos(i_r4);
            cXyz r1_12c = *r1_198.GetNP();
            cXyz r1_120 = *i_r4 + (r1_12c * -f31);
            cXyz r1_e4 = (*i_r4 - *i_r5);
            f32 f30 = r1_e4.abs();
            cXyz r1_108 = (r1_138 - r1_120);
            r1_108.normalizeZP();
            r1_108 = r1_108 * sqrtf(f30 * f30 - f31 * f31);
            *i_r5 = r1_120 + r1_108;
            return TRUE;
        }
    } else if (r1_160.cross(&r1_144, &r1_138, true, false)) {
        r1_160.Up(2.0f);
        if (r1_160.cross(&r1_144, &r1_138, true, false)) {
            f32 f31 = r1_160.getSignedLenPos(i_r4);
            cXyz r1_12c = *r1_160.GetNP();
            cXyz r1_120 = *i_r4 + (r1_12c * -f31);
            cXyz r1_e4 = (*i_r4 - *i_r5);
            f32 f30 = r1_e4.abs();
            cXyz r1_108 = (r1_138 - r1_120);
            r1_108.normalizeZP();
            r1_108 = r1_108 * sqrtf(f30 * f30 - f31 * f31);
            *i_r5 = r1_120 + r1_108;
            return TRUE;
        }
    }
    
    return FALSE;
}

/* 00001CBC-00001D0C       .text hairTopNodeCallBack__FP7J3DNodei */
static BOOL hairTopNodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Md_c* i_this = (daNpc_Md_c*)model->getUserArea();
        if (i_this) {
            J3DJoint* joint = (J3DJoint*)node;
            s32 jntNo = joint->getJntNo();
            MtxP mtx = model->getAnmMtx(jntNo);
            cXyz* hairTopPos = i_this->getPHairPos(0);
            hairTopPos->set(mtx[0][3], mtx[1][3], mtx[2][3]);
        }
    }
    return TRUE;
}

/* 00001D0C-00001F5C       .text vecChange__FP4cXyzP4cXyzs */
static void vecChange(cXyz* i_r3, cXyz* i_r4, s16 i_r5) {
    if (!cM3d_IsZero(i_r3->abs())) {
        if (!cM3d_IsZero(i_r4->abs())) {
            cXyz r1_4c = i_r3->norm();
            cXyz r1_40 = i_r4->norm();
            f32 dot = r1_4c.inprod(r1_40);
            if (dot < cM_scos(i_r5)) {
                cXyz r1_34 = r1_4c.outprod(r1_40);
                mDoMtx_stack_c::rotAxisRadS(&r1_34, cM_s2rad(i_r5));
                mDoMtx_stack_c::multVec(&r1_4c, i_r4);
            } else {
                *i_r4 = r1_40;
            }
        }
    }
}

static u8 HairModeMaskData[] = {
    0x01,
    0x02,
    0x04,
    0x08,
    0x10,
    0x20,
    0x40,
    0x80,
};

static s16 baseAngleX[] = {
    0x8000,
    0x9000,
    0xA000,
    0xB000,
    0xB000,
    0xC000,
    0xC000,
    0xC000,
};

/* 00001F5C-0000240C       .text hairNodeCallBack__FP7J3DNodei */
static BOOL hairNodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Md_c* i_this = (daNpc_Md_c*)model->getUserArea();
        if (i_this) {
            J3DJoint* joint = (J3DJoint*)node;
            s32 jntNo = joint->getJntNo();
            for (int i = 1; i < 8; i++) {
                if (i_this->getHairJntNum(i) != jntNo) {
                    continue;
                }
                
                MtxP mtx = model->getAnmMtx(jntNo);
                if (!i_this->checkBitHairMode(HairModeMaskData[i])) {
                    i_this->setBitHairMode(HairModeMaskData[i]);
                    cXyz* hairPos = i_this->getPHairPos(i);
                    hairPos->set(mtx[0][3], mtx[1][3], mtx[2][3]);
                    f32* hairDist = i_this->getPHairDist(i);
                    cXyz* r29 = i_this->getPHairVec(i);
                    *r29 = (*hairPos - *i_this->getPHairPos(i-1));
                    *hairDist = r29->abs();
                    break;
                }
                
                cXyz* r25 = i_this->getPHairPos(i-1);
                cXyz* r28 = i_this->getPHairPos(i);
                cXyz* r24 = i_this->getPHairVec(i);
                if (i <= 1) {
                    r28->x = mtx[0][3];
                    r28->y = mtx[1][3];
                    r28->z = mtx[2][3];
                    *r24 = (*r28 - *r25);
                    break;
                }
                
                f32* hairDist = i_this->getPHairDist(i);
                cXyz* r22 = i_this->getPHairVec(i-1);
                cXyz r1_e8;
                cXyz r1_dc;
                cXyz r1_d0 = *r28;
                cXyz r1_c4 = r1_d0 - *r25;
                r1_e8.set(0.0f, -1.0f, 0.0f);
                r1_e8 *= l_HIO.m14C;
                f32 power;
                dKyw_get_AllWind_vec(&i_this->current.pos, &r1_dc, &power);
                r1_e8 += r1_dc * power * 3.0f;
                r1_c4 += r1_e8;
                r1_c4 = r1_c4.normZP() * *hairDist;
                vecChange(r22, &r1_c4, 0x1000);
                *r24 = r1_c4 * *hairDist;
                *r28 = *r24 + *r25;
                if (hairCross(i_this->getPHairWall(), i_this->getPHairPos(1), r28)) {
                    *r24 = (*r28 - *r25);
                    r24->normalizeZP();
                    r1_c4 = *r24;
                    *r28 = r1_c4 * *hairDist + *r25;
                }
                
                s16 prevHaitJntNo = i_this->getHairJntNum(i-1);
                cXyz r1_b8 = r22->normZP();
                Mtx r1_124;
                cM3d_UpMtx_Base(r1_b8, r1_c4, r1_124);
                Mtx r1_f4;
                mDoMtx_copy(model->getAnmMtx(prevHaitJntNo), r1_f4);
                r1_f4[0][3] = 0.0f;
                r1_f4[1][3] = 0.0f;
                r1_f4[2][3] = 0.0f;
                mDoMtx_stack_c::copy(r1_f4);
                mDoMtx_stack_c::revConcat(r1_124);
                mDoMtx_copy(mDoMtx_stack_c::get(), mtx);
                mtx[0][3] = r28->x;
                mtx[1][3] = r28->y;
                mtx[2][3] = r28->z;
                cMtx_copy(mtx, J3DSys::mCurrentMtx);
                break;
            }
        }
    }
    return TRUE;
}

static char* hairName[] = {
    "hair1",
    "hair2",
    "hair3",
    "hair4",
    "hair5",
    "hair6",
    "hair7",
    "hair8",
};

/* 0000240C-00002F80       .text createHeap__10daNpc_Md_cFv */
BOOL daNpc_Md_c::createHeap() {
    char wait_anim_name[32];
    char arm_wait_anim_name[32];
    if (isTypeShipRide()) {
        strcpy(wait_anim_name, "md_shipwait.bck");
        strcpy(arm_wait_anim_name, "mdarm_shipwait.bck");
    } else {
        strcpy(wait_anim_name, "md_wait01.bck");
        strcpy(arm_wait_anim_name, "mdarm_wait01.bck");
    }
    
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(mModelArcName, "md.bdl");
    JUT_ASSERT(1995, modelData != 0);
    
    mpMorf = new mDoExt_McaMorf2(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes(mModelArcName, wait_anim_name),
        NULL,
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x11020022
    );
    if (!mpMorf || !mpMorf->getModel()) {
        return FALSE;
    }
    
    m_backbone1_jnt_num = modelData->getJointName()->getIndex("backbone1");
    JUT_ASSERT(2013, m_backbone1_jnt_num >= 0);
    m_backbone2_jnt_num = modelData->getJointName()->getIndex("backbone2");
    JUT_ASSERT(2016, m_backbone2_jnt_num >= 0);
    m_armR_jnt_num = modelData->getJointName()->getIndex("armR");
    JUT_ASSERT(2019, m_armR_jnt_num >= 0);
    m_armL_jnt_num = modelData->getJointName()->getIndex("armL");
    JUT_ASSERT(2022, m_armL_jnt_num >= 0);
    m_neck_jnt_num = modelData->getJointName()->getIndex("neck");
    JUT_ASSERT(2025, m_neck_jnt_num >= 0);
    
    s16 head_jnt_num = modelData->getJointName()->getIndex("head");
    if (head_jnt_num >= 0) {
        modelData->getJointNodePointer(head_jnt_num)->setCallBack(nodeCallBack);
    }
    modelData->getJointNodePointer(m_backbone1_jnt_num)->setCallBack(waistNodeCallBack);
    m_hair_jnt_nums[0] = modelData->getJointName()->getIndex(hairName[0]);
    if (m_hair_jnt_nums[0] >= 0) {
        modelData->getJointNodePointer(m_hair_jnt_nums[0])->setCallBack(hairTopNodeCallBack);
    }
    for (int i = 1; i < (int)ARRAY_SIZE(hairName); i++) {
        m_hair_jnt_nums[i] = modelData->getJointName()->getIndex(hairName[i]);
        if (m_hair_jnt_nums[i] >= 0) {
            modelData->getJointNodePointer(m_hair_jnt_nums[i])->setCallBack(hairNodeCallBack);
        }
    }
    
    mpMorf->getModel()->setUserArea((u32)this);
    
    modelData = (J3DModelData*)dComIfG_getObjectRes(mModelArcName, "mdarm.bdl");
    JUT_ASSERT(2051, modelData != 0);
    
    mpArmMorf = new mDoExt_McaMorf2(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes(mModelArcName, arm_wait_anim_name),
        NULL,
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 0,
        NULL,
        0x00000000,
        0x11020203
    );
    if (!mpArmMorf || !mpArmMorf->getModel()) {
        return FALSE;
    }
    
    m_armRloc_jnt_num = modelData->getJointName()->getIndex("armRloc");
    JUT_ASSERT(2065, m_armRloc_jnt_num >= 0);
    m_armLloc_jnt_num = modelData->getJointName()->getIndex("armLloc");
    JUT_ASSERT(2068, m_armLloc_jnt_num >= 0);
    m_handL_jnt_num = modelData->getJointName()->getIndex("handL");
    JUT_ASSERT(2071, m_handL_jnt_num >= 0);
    
    modelData->getJointNodePointer(m_armRloc_jnt_num)->setCallBack(armNodeCallBack);
    modelData->getJointNodePointer(m_armLloc_jnt_num)->setCallBack(armNodeCallBack);
    
    mpArmMorf->getModel()->setUserArea((u32)this);
    
    if (!isTypeShipRide()) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(mModelArcName, "mdwing.bdl");
        JUT_ASSERT(2083, modelData != 0);
        
        mpWingMorf = new mDoExt_McaMorf(
            modelData,
            NULL, NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes(mModelArcName, "mdwing_wait01.bck"),
            J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 0,
            NULL,
            0x00000000,
            0x11020203
        );
        if (!mpWingMorf || !mpWingMorf->getModel()) {
            return FALSE;
        }
        
        m_wingRloc_jnt_num = modelData->getJointName()->getIndex("wingRloc");
        JUT_ASSERT(2097, m_wingRloc_jnt_num >= 0);
        m_wingLloc_jnt_num = modelData->getJointName()->getIndex("wingLloc");
        JUT_ASSERT(2100, m_wingLloc_jnt_num >= 0);
        m_wingR2_jnt_num = modelData->getJointName()->getIndex("wingR2");
        JUT_ASSERT(2103, m_wingR2_jnt_num >= 0);
        m_wingL2_jnt_num = modelData->getJointName()->getIndex("wingL2");
        JUT_ASSERT(2106, m_wingL2_jnt_num >= 0);
        m_wingR3_jnt_num = modelData->getJointName()->getIndex("wingR3");
        JUT_ASSERT(2109, m_wingR3_jnt_num >= 0);
        m_wingL3_jnt_num = modelData->getJointName()->getIndex("wingL3");
        JUT_ASSERT(2112, m_wingL3_jnt_num >= 0);
        
        modelData->getJointNodePointer(m_wingRloc_jnt_num)->setCallBack(armNodeCallBack);
        modelData->getJointNodePointer(m_wingLloc_jnt_num)->setCallBack(armNodeCallBack);
        
        mpWingMorf->getModel()->setUserArea((u32)this);
    }
    
    modelData = (J3DModelData*)dComIfG_getObjectRes(mModelArcName, "md_harp.bdl");
    mpHarpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (!mpHarpModel) {
        return FALSE;
    }
    
    modelData = (J3DModelData*)dComIfG_getObjectRes(mModelArcName, "ymdhp00.bdl");
    mpHarpLightModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (!mpHarpLightModel) {
        return FALSE;
    }
    
    if (!initLightBtkAnm(false)) {
        return FALSE;
    }
    if (!initTexPatternAnm(0, 0)) {
        return FALSE;
    }
    
    mAcchCir[0].SetWall(20.0f, 20.0f);
    mAcchCir[1].SetWall(60.0f, 20.0f);
    mAcch.Set(&current.pos, &old.pos, this, ARRAY_SIZE(mAcchCir), mAcchCir, &speed);
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(120.0f);
    mAcch.OnLineCheck();
    mAcch.ClrWaterNone();
    
    return TRUE;
}

/* 00002F80-00003050       .text setAction__10daNpc_Md_cFPM10daNpc_Md_cFPCvPvPv_iM10daNpc_Md_cFPCvPvPv_iPv */
BOOL daNpc_Md_c::setAction(ActionFunc* pCurrActionFunc, ActionFunc newActionFunc, void* arg) {
    if (*pCurrActionFunc != newActionFunc) {
        if (*pCurrActionFunc) {
            mActionStatus = ACTION_ENDING;
            (this->**pCurrActionFunc)(arg);
        }
        *pCurrActionFunc = newActionFunc;
        mActionStatus = ACTION_STARTING;
        m3144 = 0;
        m3146 = 0;
        m3148 = 0;
        m314A = 0;
        m3150 = 0.0f;
        (this->**pCurrActionFunc)(arg);
    }
    return TRUE;
}

/* 00003050-00003124       .text npcAction__10daNpc_Md_cFPv */
void daNpc_Md_c::npcAction(void* arg) {
    if (mCurrNpcActionFunc == NULL) {
        speedF = 0.0f;
        if (m3104 == 0x20) {
            setNpcAction(&daNpc_Md_c::mwaitNpcAction);
        } else {
            setNpcAction(&daNpc_Md_c::waitNpcAction);
        }
    }
    
    (this->*mCurrNpcActionFunc)(arg);
}

/* 00003124-00003194       .text setNpcAction__10daNpc_Md_cFM10daNpc_Md_cFPCvPvPv_iPv */
void daNpc_Md_c::setNpcAction(ActionFunc actionFunc, void* arg) {
    m_flying = false;
    mCurrPlayerActionFunc = NULL;
    setAction(&mCurrNpcActionFunc, actionFunc, arg);
}

/* 00003194-00003360       .text playerAction__10daNpc_Md_cFPv */
void daNpc_Md_c::playerAction(void* arg) {
    if (mCurrPlayerActionFunc == NULL) {
        speedF = 0.0f;
        setPlayerAction(&daNpc_Md_c::waitPlayerAction);
    }
    
    if (mAcch.ChkGroundHit() && isOldLightBodyHit()) {
        dComIfGp_setRStatusForce(0x07); // Show "Return" on the R button
        if (chkPlayerAction(&daNpc_Md_c::mkamaePlayerAction)) {
            dComIfGp_setDoStatus(0x00); // Show the A button without anything on it
            dComIfGp_setAStatus(0x08); // TODO
        } else {
            dComIfGp_setDoStatus(0x2E); // TODO
            dComIfGp_setAStatus(0x3E); // Do not display the B button icon at all
            if (!m3140) {
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
        }
    } else {
        dComIfGp_setDoStatus(0x23); // Show "Fly" on the A button
        if (chkPlayerAction(&daNpc_Md_c::flyPlayerAction)) {
            dComIfGp_setRStatusForce(0x3E); // TODO
            dComIfGp_setAStatus(0x06); // Show "Let Go" on the B button icon
        } else {
            dComIfGp_setRStatusForce(0x07); // Show "Return" on the R button
            dComIfGp_setAStatus(0x3E); // Do not display the B button icon at all
        }
    }
    
    (this->*mCurrPlayerActionFunc)(arg);
}

/* 00003360-000033C4       .text setPlayerAction__10daNpc_Md_cFM10daNpc_Md_cFPCvPvPv_iPv */
void daNpc_Md_c::setPlayerAction(ActionFunc actionFunc, void* arg) {
    mCurrNpcActionFunc = NULL;
    setAction(&mCurrPlayerActionFunc, actionFunc, arg);
}

/* 000033C4-00003430       .text getStickAngY__10daNpc_Md_cFi */
s16 daNpc_Md_c::getStickAngY(BOOL param_1) {
    if (param_1) {
        return g_mDoCPd_cpadInfo[0].mMainStickAngle + 0x8000;
    } else {
        s16 angleY = dCam_getControledAngleY(dComIfGp_getCamera(0));
        return g_mDoCPd_cpadInfo[0].mMainStickAngle + 0x8000 + angleY;
    }
}

/* 00003430-00003588       .text calcStickPos__10daNpc_Md_cFsP4cXyz */
int daNpc_Md_c::calcStickPos(s16 param_1, cXyz* param_2) {
    // This temp variable for attention is probably a fakematch, but it fixes a regswap in dAttention_c::Lockon.
    dAttention_c& attention = dComIfGp_getAttention();
    dAttList_c* attList = attention.GetLockonList(0);
    
    bool r26 = attention.Lockon();
    
    int r31;
    if (!r26) {
        r31 = 0;
    } else {
        BOOL lockon = attention.LockonTruth();
        r31 = -1;
        if (lockon) {
            r31 = 1;
        }
    }
    
    if (attList == NULL) {
        attList = attention.GetActionList(0);
    }
    if (attList) {
        *param_2 = attList->getActor()->eyePos;
        return r31;
    }
    
    if (r26) {
        param_1 = shape_angle.y;
    }
    
    param_2->set(
        current.pos.x +  100.0f * cM_ssin(param_1),
        current.pos.y,
        current.pos.z +  100.0f * cM_scos(param_1)
    );
    
    return r31;
}

/* 00003588-0000362C       .text flyCheck__10daNpc_Md_cFv */
BOOL daNpc_Md_c::flyCheck() {
    if (!CPad_CHECK_TRIG_A(0)) {
        return FALSE;
    }
    if (isLightBodyHit()) {
        setPlayerAction(&daNpc_Md_c::mkamaePlayerAction);
    } else {
        setPlayerAction(&daNpc_Md_c::flyPlayerAction);
    }
    return TRUE;
}

/* 0000362C-00003648       .text mirrorCancelCheck__10daNpc_Md_cFv */
BOOL daNpc_Md_c::mirrorCancelCheck() {
    return CPad_CHECK_TRIG_B(0) ? TRUE : FALSE;
}

/* 00003648-00003674       .text setWingEmitter__10daNpc_Md_cFv */
void daNpc_Md_c::setWingEmitter() {
    particle_set(&m0508[0], 0x819B);
}

/* 00003674-000036C0       .text setHane02Emitter__10daNpc_Md_cFv */
void daNpc_Md_c::setHane02Emitter() {
    particle_set(&m0508[2], 0x8217);
    particle_set(&m0508[3], 0x8217);
}

/* 000036C0-000036FC       .text deleteHane02Emitter__10daNpc_Md_cFv */
void daNpc_Md_c::deleteHane02Emitter() {
    emitterDelete(&m0508[2]);
    emitterDelete(&m0508[3]);
}

/* 000036FC-00003748       .text setHane03Emitter__10daNpc_Md_cFv */
void daNpc_Md_c::setHane03Emitter() {
    particle_set(&m0508[4], 0x827D);
    particle_set(&m0508[5], 0x827D);
}

/* 00003748-00003784       .text deleteHane03Emitter__10daNpc_Md_cFv */
void daNpc_Md_c::deleteHane03Emitter() {
    emitterDelete(&m0508[4]);
    emitterDelete(&m0508[5]);
}

/* 00003784-000037C4       .text returnLinkPlayer__10daNpc_Md_cFv */
void daNpc_Md_c::returnLinkPlayer() {
    changePlayer(dComIfGp_getLinkPlayer());
    m_flying = false;
    m_mirror = false;
}

/* 000037C4-00003824       .text shipRideCheck__10daNpc_Md_cFv */
BOOL daNpc_Md_c::shipRideCheck() {
    if (isTypeShipRide()) {
        setNpcAction(&daNpc_Md_c::shipNpcAction);
        return TRUE;
    }
    return FALSE;
}

/* 00003824-00003908       .text isFallAction__10daNpc_Md_cFv */
BOOL daNpc_Md_c::isFallAction() {
    return chkPlayerAction(&daNpc_Md_c::jumpPlayerAction) ||
        chkNpcAction(&daNpc_Md_c::fallNpcAction) ||
        chkNpcAction(&daNpc_Md_c::fall02NpcAction);
}

/* 00003908-00003958       .text returnLinkCheck__10daNpc_Md_cFv */
BOOL daNpc_Md_c::returnLinkCheck() {
    if (!dComIfGp_event_runCheck()) {
        if (CPad_CHECK_TRIG_R(0) || CPad_CHECK_TRIG_START(0)) {
            if (mAcch.ChkGroundHit()) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

/* 00003958-00003D20       .text lightHitCheck__10daNpc_Md_cFv */
BOOL daNpc_Md_c::lightHitCheck() {
    BOOL lightHit = FALSE;
    cXyz lightVec;
    cMtx_multVecSR(mpHarpModel->getBaseTRMtx(), &l_ms_light_local_vec, &lightVec);
    offLightBodyHit();
    
    if (dComIfGp_getDetect().chk_light(&current.pos)) {
        onLightBodyHit();
        lightHit = TRUE;
    } else {
        cCcD_Obj* hitObj = mCyl3.GetTgHitObj();
        if (hitObj && hitObj->ChkAtType(AT_TYPE_LIGHT)) {
            onLightBodyHit();
            if (mCyl3.GetTgRVecP()->inprod(lightVec) < 0.0f) {
                lightHit = TRUE;
            }
        }
    }
    
    if (lightHit) {
        onLightHit();
        
        if (mCps.ChkAtHit()) {
            fopAc_ac_c* hitActor = mCps.GetAtHitAc();
            if (fopAcM_CheckStatus(this, fopAcStts_CARRY_e) && !isNoCarryAction()) {
                if (hitActor != dComIfGp_getLinkPlayer() && m3058.getEmitter() == NULL) {
                    dComIfGp_particle_set(0x8232, &current.pos, NULL, NULL, 0xFF, &m3058);
                }
            } else if (m3058.getEmitter() == NULL) {
                dComIfGp_particle_set(0x8232, &current.pos, NULL, NULL, 0xFF, &m3058);
            }
            
            cM3d_lineVsPosSuisenCross(mCps.GetStart(), mCps.GetEnd(), *mCps.GetAtHitPosP(), &m3058.getPos());
            s16 angleY = cM_atan2s(lightVec.x, lightVec.z);
            s16 angleX = cM_atan2s(-lightVec.y, lightVec.absXZ());
            m3058.setAngle(angleX, angleY, 0);
        } else {
            m3058.end();
        }
        
        if (!mCps.ChkAtSet()) {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_MIRROR_REFLECT, 0);
        } else {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_MIRROR_LIGHT, 0);
        }
        
        if (m304C.getEmitter() == NULL) {
            m304C.makeEmitter(0x8226, mpHarpLightModel->getBaseTRMtx(), &current.pos, NULL);
            JPABaseEmitter* emitter = m304C.getEmitter();
            JGeometry::TVec3<f32> temp;
            temp.set(1.0f, 1.0f, 1.0f);
            emitter->setEmitterScale(temp);
            temp.set(0.0f, 4.0f, 0.0f);
            emitter->setEmitterTranslation(temp);
        }
    } else {
        offLightHit();
        m3058.end();
        if (m304C.getEmitter()) {
            m304C.getEmitter()->setGlobalAlpha(0);
            m304C.end();
        }
    }
    
    return lightHit;
}

/* 00003D20-00003D68       .text wallHitCheck__10daNpc_Md_cFv */
int daNpc_Md_c::wallHitCheck() {
    if (mAcch.ChkWallHit()) {
        for (int i = 0; i < ARRAY_SIZE(mAcchCir); i++) {
            if (mAcchCir[i].ChkWallHit()) {
                return i;
            }
        }
    }
    return -1;
}

/* 00003D68-00003E74       .text NpcCall__10daNpc_Md_cFPi */
void daNpc_Md_c::NpcCall(int* r31) {
    if (!dComIfGs_isEventBit(0x1620)) {
        return;
    }
    f32 dist2 = fopAcM_searchPlayerDistance2(this);
    if (!checkNpcCallCommand()) {
        if (dist2 < l_HIO.m0C8*l_HIO.m0C8) {
            daPy_getPlayerLinkActorClass()->onNpcCallCommand();
            *r31 = 1;
        }
    } else {
        f32 temp = 2.0f*l_HIO.m0C4;
        if (dist2 >= temp*temp) {
            setNpcAction(&daNpc_Md_c::searchNpcAction);
        }
        *r31 = 1;
    }
}

/* 00003E74-00003FE0       .text checkCollision__10daNpc_Md_cFi */
BOOL daNpc_Md_c::checkCollision(int r30) {
    if ((isTypeM_Dai() || isTypeEdaichi()) && mCyl1.ChkTgHit()) {
        fopAc_ac_c* hit_actor = mCyl1.GetTgHitAc();
        if (hit_actor) {
            cXyz sp3C = current.pos - hit_actor->current.pos;
            sp3C.y = 0.0f;
            sp3C.normalizeZP();
            s16 sp08;
            if (fabsf(sp3C.x) < 0.001f && fabsf(sp3C.z) < 0.001f) {
                sp08 = 0;
            } else {
                sp08 = cM_atan2s(sp3C.x, sp3C.z);
            }
            if (r30 != 0) {
                setPlayerAction(&daNpc_Md_c::hitPlayerAction);
            } else {
                setNpcAction(&daNpc_Md_c::hitNpcAction, &sp08);
            }
            return TRUE;
        }
    }
    return FALSE;
}

/* 00003FE0-00004040       .text restartPoint__10daNpc_Md_cFs */
void daNpc_Md_c::restartPoint(s16 i_point) {
    setPointRestart(i_point, 2);
    setNpcAction(&daNpc_Md_c::waitNpcAction);
}

/* 00004040-00004174       .text isTagCheckOK__10daNpc_Md_cFv */
BOOL daNpc_Md_c::isTagCheckOK() {
    BOOL ret = FALSE;
    if (chkNpcAction(&daNpc_Md_c::waitNpcAction) || chkNpcAction(&daNpc_Md_c::searchNpcAction) || chkNpcAction(&daNpc_Md_c::searchNpcAction)) {
        ret = TRUE;
    } else if (chkNpcAction(&daNpc_Md_c::carryNpcAction) && !daPy_getPlayerLinkActorClass()->checkCarryActionNow()) {
        ret = TRUE;
    }
    return ret;
}

/* 00004174-00004230       .text setMessageAnimation__10daNpc_Md_cFUc */
void daNpc_Md_c::setMessageAnimation(u8 msgAnmAtr) {
    if (fopAcM_checkCarryNow(this)) {
        return;
    }
    if (!dComIfGp_event_runCheck()) {
        return;
    }
    int staffIdx = dComIfGp_evmng_getMyStaffId(l_staff_name);
    if (staffIdx != -1) {
        if (strcmp(dComIfGp_evmng_getMyActName(staffIdx), "WAIT") == 0) {
            int anmType = getAnmType(msgAnmAtr);
            if (anmType >= 0) {
                setAnm(anmType);
            }
        }
    }
}

/* 00004230-0000433C       .text waitGroundCheck__10daNpc_Md_cFv */
void daNpc_Md_c::waitGroundCheck() {
    /* Nonmatching */
}

/* 0000433C-000043D4       .text chkAdanmaeDemoOrder__10daNpc_Md_cFv */
void daNpc_Md_c::chkAdanmaeDemoOrder() {
    /* Nonmatching */
}

/* 000043D4-00004B04       .text waitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::waitNpcAction(void*) {
    /* Nonmatching */
}

/* 00004B04-00004CFC       .text harpWaitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::harpWaitNpcAction(void*) {
    /* Nonmatching */
}

static uint l_msgId;
static msg_class* l_msg;

/* 00004CFC-00004D40       .text XYTalkCheck__10daNpc_Md_cFv */
BOOL daNpc_Md_c::XYTalkCheck() {
    BOOL ret = TRUE;
    if (isXYTalk()) {
        ret = dComIfGp_evmng_ChkPresentEnd();
    }
    return ret;
}

/* 00004D40-0000504C       .text talkNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::talkNpcAction(void*) {
    /* Nonmatching */
}

/* 0000504C-000051FC       .text shipTalkNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::shipTalkNpcAction(void*) {
    /* Nonmatching */
}

/* 000051FC-00005308       .text kyohiNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::kyohiNpcAction(void*) {
    /* Nonmatching */
}

/* 00005308-00005534       .text shipNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::shipNpcAction(void*) {
    /* Nonmatching */
}

/* 00005534-000057B0       .text mwaitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::mwaitNpcAction(void*) {
    /* Nonmatching */
}

/* 000057B0-000058E0       .text squatdownNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::squatdownNpcAction(void*) {
    /* Nonmatching */
}

/* 000058E0-00005A74       .text sqwait01NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::sqwait01NpcAction(void*) {
    /* Nonmatching */
}

/* 00005A74-00005AB0       .text changeCaught02__10daNpc_Md_cFv */
void daNpc_Md_c::changeCaught02() {
    setAnm(0x25);
    cLib_onBit(m30F0, 0x01UL);
}

/* 00005AB0-000061A8       .text carryNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::carryNpcAction(void*) {
    /* Nonmatching */
}

/* 000061A8-00006450       .text throwNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::throwNpcAction(void*) {
    /* Nonmatching */
}

/* 00006450-00006764       .text glidingNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::glidingNpcAction(void*) {
    /* Nonmatching */
}

/* 00006764-00006B24       .text windProc__10daNpc_Md_cFv */
void daNpc_Md_c::windProc() {
    /* Nonmatching */
}

/* 00006B24-00006C80       .text fallNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::fallNpcAction(void*) {
    /* Nonmatching */
}

/* 00006C80-00006F70       .text fall02NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::fall02NpcAction(void*) {
    /* Nonmatching */
}

/* 00006F70-000071E4       .text wallHitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::wallHitNpcAction(void*) {
    /* Nonmatching */
}

/* 000071E4-000073BC       .text land01NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::land01NpcAction(void*) {
    /* Nonmatching */
}

/* 000073BC-000074C0       .text land02NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::land02NpcAction(void*) {
    /* Nonmatching */
}

/* 000074C0-000075C4       .text land03NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::land03NpcAction(void*) {
    /* Nonmatching */
}

/* 000075C4-00007824       .text piyo2NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::piyo2NpcAction(void*) {
    /* Nonmatching */
}

/* 00007824-0000786C       .text deleteNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::deleteNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus++; // ACTION_ONGOING_1
    } else if (mActionStatus != ACTION_ENDING) {
        fopAcM_delete(this);
    }
    return TRUE;
}

/* 0000786C-00007A98       .text demoFlyNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::demoFlyNpcAction(void*) {
    /* Nonmatching */
}

/* 00007A98-00007B64       .text routeAngCheck__10daNpc_Md_cFR4cXyzPs */
void daNpc_Md_c::routeAngCheck(cXyz&, s16*) {
    /* Nonmatching */
}

/* 00007B64-00007DC8       .text routeWallCheck__10daNpc_Md_cFR4cXyzR4cXyzPs */
void daNpc_Md_c::routeWallCheck(cXyz&, cXyz&, s16*) {
    /* Nonmatching */
}

/* 00007DC8-00008054       .text checkForwardGroundY__10daNpc_Md_cFs */
void daNpc_Md_c::checkForwardGroundY(s16) {
    /* Nonmatching */
}

/* 000081EC-000082C0       .text checkWallJump__10daNpc_Md_cFs */
void daNpc_Md_c::checkWallJump(s16) {
    /* Nonmatching */
}

/* 000082C0-00008858       .text routeCheck__10daNpc_Md_cFfPs */
void daNpc_Md_c::routeCheck(f32, s16*) {
    /* Nonmatching */
}

/* 00008858-00008CEC       .text searchNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::searchNpcAction(void*) {
    /* Nonmatching */
}

/* 00008CEC-00008E54       .text hitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::hitNpcAction(void* r29) {
    if (mActionStatus == ACTION_STARTING) {
        setDamageFogTimer(5*30);
        // Bug: Reverb is being passed to JAIZelBasic::monsSeStart as argument r7 when it should be argument r8.
        // The fopAcM_monsSeStart inline does not support passing reverb, but the programmer didn't realize this.
        fopAcM_monsSeStart(this, JA_SE_CV_MD_CRASH, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        s16 angle = 0;
        if (r29 != NULL) {
            angle = *(s16*)r29;
        }
        current.angle.y = angle;
        speedF = 10.0f;
        speed.y = 20.0f;
        attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        cLib_offBit(m30F0, 0x01UL | 0x04UL);
        cLib_onBit(m30F0, 0x02UL);
        m30F8 = 120.0f;
        setAnm(0xD);
        mActionStatus++; // ACTION_ONGOING_1
    } else if (mActionStatus != ACTION_ENDING) {
        if (mAcch.ChkGroundHit()) {
            speedF = 0.0f;
            setNpcAction(&daNpc_Md_c::land03NpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00008E54-00008FFC       .text setNormalSpeedF__10daNpc_Md_cFfffff */
void daNpc_Md_c::setNormalSpeedF(f32, f32, f32, f32, f32) {
    /* Nonmatching */
}

/* 00008FFC-000090EC       .text setSpeedAndAngleNormal__10daNpc_Md_cFfs */
void daNpc_Md_c::setSpeedAndAngleNormal(f32, s16) {
    /* Nonmatching */
}

/* 000090EC-00009180       .text walkProc__10daNpc_Md_cFfs */
void daNpc_Md_c::walkProc(f32, s16) {
    /* Nonmatching */
}

/* 00009180-000092E0       .text jumpNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::jumpNpcAction(void*) {
    /* Nonmatching */
}

/* 000092E0-000095C8       .text escapeNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::escapeNpcAction(void*) {
    /* Nonmatching */
}

/* 000095C8-00009894       .text waitPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::waitPlayerAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        cLib_offBit(m30F0, 0x10UL | 0x02UL | 0x01UL); // TODO
        cLib_onBit(m30F0, 0x04UL); // TODO
        setAnm(0);
        speedF = 0.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        m311A = 0;
        m310C = 0.0f;
        m3114 = 0;
        m3116 = 0;
        mActionStatus++; // ACTION_ONGOING_1
    } else if (mActionStatus != ACTION_ENDING && !flyCheck()) {
        dAttention_c& attention = dComIfGp_getAttention();
        if (g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.m104 || attention.Lockon()) {
            s16 stickAngle = getStickAngY(0);
            cLib_addCalcAngleS(&current.angle.y, stickAngle, l_HIO.m008.m26, l_HIO.m008.m28, l_HIO.m008.m2A);
            cXyz stickPos;
            int temp = calcStickPos(stickAngle, &stickPos);
            if (temp == 0) {
                shape_angle.y = current.angle.y;
            } else if (g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.m108) {
                shape_angle.y = current.angle.y;
            }
            s16 tempAngle = shape_angle.y;
            mJntCtrl.lookAtTarget(&tempAngle, &stickPos, current.pos, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);
            if (temp > 0) {
                shape_angle.y = tempAngle;
            }
            current.angle.y = shape_angle.y;
            if (g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.m108) {
                if (temp == 0) {
                    current.angle.y = stickAngle;
                    setPlayerAction(&daNpc_Md_c::walkPlayerAction);
                }
            }
        } else {
            mJntCtrl.lookAtTarget(&shape_angle.y, NULL, cXyz::Zero, shape_angle.y, 0, false);
            waitGroundCheck();
            current.angle.y = shape_angle.y;
        }
        
        setAttention(mpMorf->isMorf());
    }
    
    return TRUE;
}

/* 00009894-00009B08       .text walkPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::walkPlayerAction(void*) {
    /* Nonmatching */
}

/* 00009B08-00009CCC       .text hitPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::hitPlayerAction(void*) {
    /* Nonmatching */
}

/* 00009CCC-00009E7C       .text jumpPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::jumpPlayerAction(void*) {
    /* Nonmatching */
}

/* 00009E7C-0000A534       .text flyPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::flyPlayerAction(void*) {
    /* Nonmatching */
}

/* 0000A534-0000A698       .text landPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::landPlayerAction(void*) {
    /* Nonmatching */
}

/* 0000A698-0000A8D0       .text mkamaePlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::mkamaePlayerAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        cLib_offBit(m30F0, 0x01UL | 0x02UL | 0x04UL | 0x10UL);
        setAnm(0x1F);
        shape_angle.x = 0;
        shape_angle.z = 0;
        gravity = l_HIO.m0F4;
        maxFallSpeed = -100.0f;
        speedF = 0.0f;
        speed.y = 0.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++; // ACTION_ONGOING_1
    } else if (mActionStatus == ACTION_ENDING) {
        offMirror();
    } else {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (m312A != 0) {
                speedF = 0.0f;
                setAnm(0x20);
                onMirror();
                mActionStatus++; // ACTION_ONGOING_2
            }
        } else if (mActionStatus == ACTION_ONGOING_2) {
            if (mirrorCancelCheck() || !isLightBodyHit()) {
                setAnm(0x21);
                m312A = 0;
                offMirror();
                mActionStatus++; // ACTION_ONGOING_3
            } else {
                dAttention_c& attention = dComIfGp_getAttention();
                if (g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.m104 || attention.Lockon()) {
                    m311A = getStickAngY(FALSE);
                    m310C = g_mDoCPd_cpadInfo[0].mMainStickValue;
                } else {
                    m311A = 0;
                    m310C = 0.0f;
                }
                lookBackWaist(m311A, m310C);
            }
        } else if (m312A != 0) {
            setPlayerAction(&daNpc_Md_c::waitPlayerAction);
        }
        
        setAttention(true);
    }
    
    return TRUE;
}

/* 0000A8D0-0000A9BC       .text carryPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::carryPlayerAction(void*) {
    /* Nonmatching */
}

daNpc_Md_c::ActionFunc dummy_5931 = &daNpc_Md_c::mwaitNpcAction;
daNpc_Md_c::ActionFunc dummy_5934 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_5955 = &daNpc_Md_c::waitPlayerAction;
daNpc_Md_c::ActionFunc dummy_5960 = &daNpc_Md_c::mkamaePlayerAction;
daNpc_Md_c::ActionFunc dummy_5968 = &daNpc_Md_c::flyPlayerAction;
daNpc_Md_c::ActionFunc dummy_6061 = &daNpc_Md_c::mkamaePlayerAction;
daNpc_Md_c::ActionFunc dummy_6064 = &daNpc_Md_c::flyPlayerAction;
daNpc_Md_c::ActionFunc dummy_6110 = &daNpc_Md_c::shipNpcAction;
daNpc_Md_c::ActionFunc dummy_6118 = &daNpc_Md_c::jumpPlayerAction;
daNpc_Md_c::ActionFunc dummy_6120 = &daNpc_Md_c::fallNpcAction;
daNpc_Md_c::ActionFunc dummy_6122 = &daNpc_Md_c::fall02NpcAction;
daNpc_Md_c::ActionFunc dummy_6301 = &daNpc_Md_c::searchNpcAction;
daNpc_Md_c::ActionFunc dummy_6331 = &daNpc_Md_c::hitPlayerAction;
daNpc_Md_c::ActionFunc dummy_6334 = &daNpc_Md_c::hitNpcAction;
daNpc_Md_c::ActionFunc dummy_6367 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_6375 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_6377 = &daNpc_Md_c::searchNpcAction;
daNpc_Md_c::ActionFunc dummy_6379 = &daNpc_Md_c::searchNpcAction;
daNpc_Md_c::ActionFunc dummy_6386 = &daNpc_Md_c::carryNpcAction;
daNpc_Md_c::ActionFunc dummy_6440 = &daNpc_Md_c::fallNpcAction;
daNpc_Md_c::ActionFunc dummy_6587 = &daNpc_Md_c::demoFlyNpcAction;
daNpc_Md_c::ActionFunc dummy_6766 = &daNpc_Md_c::squatdownNpcAction;
daNpc_Md_c::ActionFunc dummy_6769 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_6776 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_6783 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_6836 = &daNpc_Md_c::shipNpcAction;
daNpc_Md_c::ActionFunc dummy_6874 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_6969 = &daNpc_Md_c::searchNpcAction;
daNpc_Md_c::ActionFunc dummy_6972 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_7006 = &daNpc_Md_c::sqwait01NpcAction;
daNpc_Md_c::ActionFunc dummy_7036 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_7114 = &daNpc_Md_c::throwNpcAction;
daNpc_Md_c::ActionFunc dummy_7117 = &daNpc_Md_c::land03NpcAction;
daNpc_Md_c::ActionFunc dummy_7125 = &daNpc_Md_c::fall02NpcAction;
daNpc_Md_c::ActionFunc dummy_7128 = &daNpc_Md_c::fallNpcAction;
daNpc_Md_c::ActionFunc dummy_7133 = &daNpc_Md_c::throwNpcAction;
daNpc_Md_c::ActionFunc dummy_7136 = &daNpc_Md_c::sqwait01NpcAction;
daNpc_Md_c::ActionFunc dummy_7292 = &daNpc_Md_c::land01NpcAction;
daNpc_Md_c::ActionFunc dummy_7297 = &daNpc_Md_c::wallHitNpcAction;
daNpc_Md_c::ActionFunc dummy_7302 = &daNpc_Md_c::glidingNpcAction;
daNpc_Md_c::ActionFunc dummy_7362 = &daNpc_Md_c::land01NpcAction;
daNpc_Md_c::ActionFunc dummy_7365 = &daNpc_Md_c::land01NpcAction;
daNpc_Md_c::ActionFunc dummy_7372 = &daNpc_Md_c::wallHitNpcAction;
daNpc_Md_c::ActionFunc dummy_7375 = &daNpc_Md_c::wallHitNpcAction;
daNpc_Md_c::ActionFunc dummy_7393 = &daNpc_Md_c::fall02NpcAction;
daNpc_Md_c::ActionFunc dummy_7396 = &daNpc_Md_c::fall02NpcAction;
daNpc_Md_c::ActionFunc dummy_7570 = &daNpc_Md_c::land01NpcAction;
daNpc_Md_c::ActionFunc dummy_7575 = &daNpc_Md_c::wallHitNpcAction;
daNpc_Md_c::ActionFunc dummy_7612 = &daNpc_Md_c::fall02NpcAction;
daNpc_Md_c::ActionFunc dummy_7633 = &daNpc_Md_c::land01NpcAction;
daNpc_Md_c::ActionFunc dummy_7638 = &daNpc_Md_c::wallHitNpcAction;
daNpc_Md_c::ActionFunc dummy_7685 = &daNpc_Md_c::land03NpcAction;
daNpc_Md_c::ActionFunc dummy_7690 = &daNpc_Md_c::wallHitNpcAction;
daNpc_Md_c::ActionFunc dummy_7695 = &daNpc_Md_c::land03NpcAction;
daNpc_Md_c::ActionFunc dummy_7700 = &daNpc_Md_c::wallHitNpcAction;
daNpc_Md_c::ActionFunc dummy_7763 = &daNpc_Md_c::land02NpcAction;
daNpc_Md_c::ActionFunc dummy_7768 = &daNpc_Md_c::land02NpcAction;
daNpc_Md_c::ActionFunc dummy_7826 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_7831 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_7865 = &daNpc_Md_c::piyo2NpcAction;
daNpc_Md_c::ActionFunc dummy_7884 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_7903 = &daNpc_Md_c::piyo2NpcAction;
daNpc_Md_c::ActionFunc dummy_7925 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_8240 = &daNpc_Md_c::jumpNpcAction;
daNpc_Md_c::ActionFunc dummy_8247 = &daNpc_Md_c::jumpNpcAction;
daNpc_Md_c::ActionFunc dummy_8446 = &daNpc_Md_c::kyohiNpcAction;
daNpc_Md_c::ActionFunc dummy_8455 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_8525 = &daNpc_Md_c::land03NpcAction;
daNpc_Md_c::ActionFunc dummy_8625 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_8667 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_8671 = &daNpc_Md_c::waitNpcAction;
daNpc_Md_c::ActionFunc dummy_8720 = &daNpc_Md_c::walkPlayerAction;
daNpc_Md_c::ActionFunc dummy_8771 = &daNpc_Md_c::waitPlayerAction;
daNpc_Md_c::ActionFunc dummy_8776 = &daNpc_Md_c::jumpPlayerAction;
daNpc_Md_c::ActionFunc dummy_8783 = &daNpc_Md_c::jumpPlayerAction;
daNpc_Md_c::ActionFunc dummy_8869 = &daNpc_Md_c::waitPlayerAction;
daNpc_Md_c::ActionFunc dummy_8914 = &daNpc_Md_c::jumpPlayerAction;
daNpc_Md_c::ActionFunc dummy_8949 = &daNpc_Md_c::landPlayerAction;
daNpc_Md_c::ActionFunc dummy_9045 = &daNpc_Md_c::waitPlayerAction;
daNpc_Md_c::ActionFunc dummy_9093 = &daNpc_Md_c::waitPlayerAction;

static daNpc_Md_c::EventActionInitFunc event_init_tbl[] = {
    &daNpc_Md_c::initialWaitEvent,
    &daNpc_Md_c::initialLetterEvent,
    &daNpc_Md_c::initialMsgSetEvent,
    &daNpc_Md_c::initialDefault,
    &daNpc_Md_c::initialMovePosEvent,
    &daNpc_Md_c::initialFlyEvent,
    &daNpc_Md_c::initialGlidingEvent,
    &daNpc_Md_c::initialLandingEvent,
    &daNpc_Md_c::initialWalkEvent,
    &daNpc_Md_c::initialWalkEvent,
    &daNpc_Md_c::initialEndEvent,
    &daNpc_Md_c::initialDefault,
    &daNpc_Md_c::initialTakeOffEvent,
    &daNpc_Md_c::initialOnetimeEvent,
    &daNpc_Md_c::initialQuake,
    &daNpc_Md_c::initialHarpPlayEvent,
    &daNpc_Md_c::initialOffLinkEvent,
    &daNpc_Md_c::initialOnLinkEvent,
    &daNpc_Md_c::initialTurnEvent,
    &daNpc_Md_c::initialSetAnmEvent,
    &daNpc_Md_c::initialLookDown,
    &daNpc_Md_c::initialLookUp,
};

static daNpc_Md_c::EventActionFunc event_action_tbl[] = {
    &daNpc_Md_c::actionWaitEvent,
    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionMsgSetEvent,
    &daNpc_Md_c::actionMsgEndEvent,
    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionFlyEvent,
    &daNpc_Md_c::actionGlidingEvent,
    &daNpc_Md_c::actionLandingEvent,
    &daNpc_Md_c::actionWalkEvent,
    &daNpc_Md_c::actionDashEvent,
    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionTactEvent,
    &daNpc_Md_c::actionTakeOffEvent,
    &daNpc_Md_c::actionOnetimeEvent,
    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionHarpPlayEvent,
    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionTurnEvent,
    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionLookDown,
    &daNpc_Md_c::actionLookDown,
};

static char* cut_name_tbl[] = {
    "WAIT",
    "CREATEITEM",
    "MSG_SET",
    "MSG_END",
    "POS_MOV",
    "FLY",
    "GLIDING",
    "LANDING",
    "WALK",
    "DASH",
    "END",
    "TACT",
    "TAKEOFF",
    "Onetime",
    "QUAKE",
    "HARPPLAY",
    "OFF_PLAYER",
    "ON_PLAYER",
    "TURN",
    "SET_ANM",
    "LOOK_DOWN",
    "LOOK_UP",
};

/* 0000A9BC-0000AC80       .text eventProc__10daNpc_Md_cFv */
BOOL daNpc_Md_c::eventProc() {
    if (eventInfo.checkCommandDemoAccrpt() && mCurEventMode != 0) {
        if (mCurEventMode == 0xC) {
            if (dComIfGp_evmng_startCheck("OPTION_CHAR_END") || dComIfGp_evmng_endCheck("OPTION_CHAR_END")) {
                dComIfGp_event_setTalkPartner(dComIfGp_getLinkPlayer());
                mDoAud_seStart(JA_SE_CTRL_NPC_TO_LINK);
            } else {
                offReturnLink();
                mCurEventMode = 0;
            }
        }
        if (mCurEventMode != 0) {
            onEventAccept();
            mCurEventMode = 0;
        }
    }
    int staffIdx = dComIfGp_evmng_getMyStaffId(l_staff_name);
    if (dComIfGp_event_runCheck() && !checkCommandTalk()) {
        if (staffIdx != -1) {
            int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), 1, 0);
            if (actIdx == -1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            } else {
                if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                    (this->*event_init_tbl[actIdx])(staffIdx);
                }
                if ((this->*event_action_tbl[actIdx])(staffIdx)) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }
        }
        if (isEventAccept()) {
            if (dComIfGp_evmng_endCheck(mEventIdxTable[mCurEvent])) {
                dComIfGp_event_reset();
                offEventAccept();
                if (mCurEvent == 8) {
                    returnLinkPlayer();
                    offReturnLink();
                }
                mCurEvent = -1;
            }
            return TRUE;
        }
        if (staffIdx != -1) {
            return TRUE;
        } else if (dComIfGp_getLinkPlayer()->eventInfo.checkCommandDoor() == FALSE) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 0000AC80-0000AC84       .text initialDefault__10daNpc_Md_cFi */
void daNpc_Md_c::initialDefault(int) {
}

/* 0000AC84-0000ACB4       .text actionDefault__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionDefault(int) {
    lookBack(0, 0, 1);
    return TRUE;
}

/* 0000ACB4-0000AD9C       .text initialWaitEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialWaitEvent(int) {
    /* Nonmatching */
}

/* 0000AD9C-0000ADCC       .text actionWaitEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionWaitEvent(int) {
    return cLib_calcTimer(&m3118) == 0 ? TRUE : FALSE;
}

/* 0000ADCC-0000AEB8       .text initialLetterEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialLetterEvent(int) {
    /* Nonmatching */
}

/* 0000AEB8-0000AFB0       .text initialMsgSetEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialMsgSetEvent(int) {
    /* Nonmatching */
}

/* 0000AFB0-0000AFFC       .text actionMsgSetEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionMsgSetEvent(int) {
    lookBack(1, 0, 0);
    setAttention(true);
    return talk_init();
}

/* 0000AFFC-0000B070       .text actionMsgEndEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionMsgEndEvent(int param_1) {
    BOOL ret = talk(0);
    if (ret) {
        initialEndEvent(param_1);
    }
    lookBack(1, 0, 0);
    setAttention(true);
    return ret;
}

/* 0000B070-0000B728       .text initialMovePosEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialMovePosEvent(int) {
    /* Nonmatching */
}

/* 0000B728-0000B79C       .text initialFlyEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialFlyEvent(int) {
    /* Nonmatching */
}

/* 0000B79C-0000B870       .text actionFlyEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionFlyEvent(int) {
    /* Nonmatching */
}

/* 0000B870-0000B890       .text initialGlidingEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialGlidingEvent(int) {
    gravity = l_HIO.m0F4;
    maxFallSpeed = -100.0f;
}

/* 0000B890-0000B934       .text actionGlidingEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionGlidingEvent(int) {
    /* Nonmatching */
}

/* 0000B934-0000B99C       .text initialLandingEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialLandingEvent(int) {
    /* Nonmatching */
}

/* 0000B99C-0000B9E0       .text actionLandingEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionLandingEvent(int) {
    if (m312A != 0) {
        setAnm(0);
        return true;
    }
    setAttention(true);
    return false;
}

/* 0000B9E0-0000B9F8       .text initialWalkEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialWalkEvent(int) {
    speedF = 0.0f;
    m3118 = 20*30;
}

/* 0000B9F8-0000BCC4       .text actionWalkEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionWalkEvent(int) {
    /* Nonmatching */
}

/* 0000BCC4-0000BF1C       .text actionDashEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionDashEvent(int) {
    /* Nonmatching */
}

/* 0000BF1C-0000C12C       .text initialEndEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialEndEvent(int) {
    /* Nonmatching */
}

/* 0000C12C-0000C250       .text actionTactEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionTactEvent(int) {
    /* Nonmatching */
}

/* 0000C250-0000C288       .text initialTakeOffEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialTakeOffEvent(int) {
    setAnm(0x18);
    m312A = 0;
}

/* 0000C288-0000C2C4       .text actionTakeOffEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionTakeOffEvent(int) {
    if (m312A != 0) {
        return TRUE;
    }
    setAttention(true);
    return FALSE;
}

/* 0000C2C4-0000C360       .text initialOnetimeEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialOnetimeEvent(int) {
    /* Nonmatching */
}

/* 0000C360-0000C3C4       .text actionOnetimeEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionOnetimeEvent(int) {
    if (m312A != 0) {
        if (m3104 == 0x1A) {
            setAnm(0);
        } else {
            return true;
        }
    }
    setAttention(true);
    return false;
}

/* 0000C3C4-0000C48C       .text initialQuake__10daNpc_Md_cFi */
void daNpc_Md_c::initialQuake(int) {
    /* Nonmatching */
}

/* 0000C48C-0000C4DC       .text setHarpPlayNum__10daNpc_Md_cFi */
void daNpc_Md_c::setHarpPlayNum(int) {
    /* Nonmatching */
}

/* 0000C4DC-0000C500       .text initialHarpPlayEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialHarpPlayEvent(int) {
    setHarpPlayNum(0);
}

/* 0000C500-0000C554       .text actionHarpPlayEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionHarpPlayEvent(int) {
    if (m312A != 0) {
        setHarpPlayNum(0);
    }
    if (daPy_getPlayerLinkActorClass()->checkEndTactMusic()) {
        return true;
    }
    return false;
}

/* 0000C554-0000C570       .text initialOffLinkEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialOffLinkEvent(int) {
    daPy_getPlayerLinkActorClass()->onPlayerNoDraw();
}

/* 0000C570-0000C58C       .text initialOnLinkEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialOnLinkEvent(int) {
    daPy_getPlayerLinkActorClass()->offPlayerNoDraw();
}

/* 0000C58C-0000C654       .text initialTurnEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialTurnEvent(int) {
    /* Nonmatching */
}

/* 0000C654-0000C7CC       .text actionTurnEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionTurnEvent(int) {
    /* Nonmatching */
}

/* 0000C7CC-0000CA5C       .text initialSetAnmEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialSetAnmEvent(int) {
    /* Nonmatching */
}

/* 0000CA5C-0000CA80       .text initialLookDown__10daNpc_Md_cFi */
void daNpc_Md_c::initialLookDown(int) {
    setAnm(0x2F);
}

/* 0000CA80-0000CAA4       .text initialLookUp__10daNpc_Md_cFi */
void daNpc_Md_c::initialLookUp(int) {
    setAnm(5);
}

/* 0000CAA4-0000CB8C       .text actionLookDown__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionLookDown(int) {
    /* Nonmatching */
}

/* 0000CB8C-0000CC10       .text talk_init__10daNpc_Md_cFv */
BOOL daNpc_Md_c::talk_init() {
    if (l_msgId == fpcM_ERROR_PROCESS_ID_e) {
        if (mMsgNo == 0x5AC) {
            l_msgId = fopMsgM_tactMessageSet();
        } else {
            l_msgId = fopMsgM_messageSet(mMsgNo, this);
        }
    } else {
        l_msg = fopMsgM_SearchByID(l_msgId);
        if (l_msg) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 0000CC10-0000CDCC       .text talk__10daNpc_Md_cFi */
BOOL daNpc_Md_c::talk(int r4) {
    u16 msgStatus = l_msg->mStatus;
    u8 msgAnmAtr = dComIfGp_getMesgAnimeAttrInfo();
    if (msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
        l_msg->mStatus = next_msgStatus(&mMsgNo);
        if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
            fopMsgM_messageSet(mMsgNo);
            m313A = 0;
        }
    } else if (msgStatus == fopMsgStts_UNK15_e) {
        if (r4 != 0) {
            if (dComIfGp_checkMesgCancelButton()) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
                cLib_onBit(m30F0, 0x200UL);
            }
            if (cLib_checkBit(m30F0, 0x400UL)) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
            }
        }
    } else if (msgStatus == fopMsgStts_MSG_TYPING_e) {
        if (m313A == 0 && !fopAcM_checkCarryNow(this) && !isShipRide() && mMsgNo != 0x05AC) {
            int anmType = getAnmType(msgAnmAtr);
            if (anmType >= 0) {
                setAnm(anmType);
            }
        }
    } else if (msgStatus == fopMsgStts_BOX_CLOSED_e) {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
        offXYTalk();
        return TRUE;
    }
    
    if (!fopAcM_checkCarryNow(this) && !isShipRide() && mMsgNo != 0x05AC) {
        if (m313A == 1 && msgAnmAtr == 0x14 && m312A != 0) {
            setAnm(0x1B);
            m313A = 1;
        }
    }
    
    return FALSE;
}

/* 0000CDCC-0000CDF4       .text getAnmType__10daNpc_Md_cFUc */
int daNpc_Md_c::getAnmType(u8 r4) {
    static const int anmTypeData_Talk[] = {
        0x00000000,
        0x00000002,
        0x00000002,
        0x00000003,
        0x00000004,
        0x00000005,
        0x00000006,
        0x0000000B,
        0x00000007,
        0x00000009,
        0x0000000C,
        0x0000000D,
        0x0000000E,
        0x0000000F,
        0x00000011,
        0x00000014,
        0x00000012,
        0x0000001B,
        0x0000001C,
        0x00000015,
        0x00000015,
        0x00000016,
        0x00000017,
        0x00000018,
        0x00000019,
        0x0000001D,
        0x0000001A,
        0x00000010,
        0x0000001F,
        0x00000020,
        0x00000022,
        0x0000001E,
        0x00000023,
        0x00000024,
        0x00000025,
        0x00000026,
        0x00000027,
        0x00000028,
        0x00000029,
        0x0000002A,
        0x0000002B,
        0x0000002C,
        0x0000002D,
        0x00000031,
    };
    
    if (r4 < ARRAY_SIZE(anmTypeData_Talk)) {
        return anmTypeData_Talk[r4];
    } else {
        return -1;
    }
}

/* 0000CDF4-0000CF18       .text initTexPatternAnm__10daNpc_Md_cFUcb */
BOOL daNpc_Md_c::initTexPatternAnm(u8 btpAnmTblIdx, bool param_2) {
    struct btp_anm_tbl {
        /* 0x00 */ char m00[0x20];
        /* 0x20 */ u8 m20;
    };
    static btp_anm_tbl btpAnmTbl[] = {
        {"maba.btp", 0},
        {"md_fall.btp", 0},
        {"md_fall02.btp", 0},
        {"md_fly02.btp", 0},
        {"md_kamae.btp", 1},
        {"md_kamaewait.btp", 0},
        {"md_land.btp", 1},
        {"md_land02.btp", 1},
        {"md_piyo2.btp", 1},
        {"md_harpplay.btp", 0},
        {"md_watasu.btp", 1},
        {"fuan.btp", 1},
        {"md_caught.btp", 0},
        {"md_komari.btp", 0},
        {"md_kyoro2.btp", 1},
        {"md_unazuki.btp", 1},
    };
    
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    bool ret = false;
    J3DAnmTexPattern* eyeTexPtrn = (J3DAnmTexPattern*)dComIfG_getObjectRes(mModelArcName, btpAnmTbl[btpAnmTblIdx].m00);
    JUT_ASSERT(7502, eyeTexPtrn != 0);
    if (m0520.init(modelData, eyeTexPtrn, 1, 1, 1.0f, 0, -1, param_2, 0)) {
        m3112 = eyeTexPtrn->getFrameMax();
        m3133 = 0;
        m3136 = btpAnmTbl[btpAnmTblIdx].m20;
        m3137 = btpAnmTblIdx;
        ret = true;
    }
    
    return ret;
}

/* 0000CF18-0000CFCC       .text playTexPatternAnm__10daNpc_Md_cFv */
void daNpc_Md_c::playTexPatternAnm() {
    if (m3136 == 1) {
        m0520.setFrame(m30D0);
        return;
    }
    if (m0520.play()) {
        if (cLib_calcTimer(&m3133) == 0) {
            m3133 = 30.0f + cM_rndF(60.0f);
            m0520.initPlay(m3112, J3DFrameCtrl::LOOP_ONCE_RESET_e, 1.0f, 0, -1, true);
        }
    }
}

/* 0000CFCC-0000D0B8       .text initLightBtkAnm__10daNpc_Md_cFb */
BOOL daNpc_Md_c::initLightBtkAnm(bool) {
    /* Nonmatching */
}

/* 0000D0B8-0000D0DC       .text playLightBtkAnm__10daNpc_Md_cFv */
void daNpc_Md_c::playLightBtkAnm() {
    mLightBtkAnm.play();
}

/* 0000D0DC-0000D4CC       .text setAnm__10daNpc_Md_cFi */
BOOL daNpc_Md_c::setAnm(int anmIdx) {
    struct anm_tbl {
        /* 0x00 */ char m00[0x20];
        /* 0x20 */ char m20[0x20];
    };
    struct anm_prm {
        /* 0x00 */ s8 anmTblIdx;
        /* 0x01 */ u8 armAnmTblIdx;
        /* 0x02 */ u8 btpAnmTblIdx;
        /* 0x04 */ int loopMode;
        /* 0x08 */ f32 morf;
        /* 0x0C */ f32 speed;
    };

    static anm_tbl l_anmTbl[] = {
        {"md_wait01.bck", ""},
        {"md_walk.bck", "md_run.bck"},
        {"md_squatdown.bck", ""},
        {"md_sqwait01.bck", ""},
        {"md_sqwait02.bck", ""},
        {"md_firing.bck", ""},
        {"md_fly01.bck", ""},
        {"md_fly02.bck", ""},
        {"md_gliding.bck", ""},
        {"md_fall.bck", ""},
        {"md_fall02.bck", ""},
        {"md_land.bck", ""},
        {"md_land02.bck", ""},
        {"md_land03.bck", ""},
        {"md_kamaewait.bck", ""},
        {"md_kamae.bck", ""},
        {"md_piyo2.bck", ""},
        {"md_ojigi.bck", ""},
        {"md_harpplay01.bck", ""},
        {"md_harpplay02.bck", ""},
        {"md_takeoff01.bck", ""},
        {"md_takeoff02.bck", ""},
        {"md_watasu.bck", ""},
        {"md_talk01.bck", ""},
        {"md_talk02.bck", ""},
        {"md_talk03.bck", ""},
        {"md_talk04.bck", ""},
        {"md_mkamae.bck", ""},
        {"md_mwait.bck", ""},
        {"md_oriwait.bck", ""},
        {"md_shipwait.bck", ""},
        {"md_caught01.bck", ""},
        {"md_caught02.bck", ""},
        {"md_kyohi.bck", ""},
        {"md_kyoro2.bck", ""},
        {"md_shipwait02.bck", ""},
        {"md_shiptalk01.bck", ""},
        {"md_talk05.bck", ""},
        {"md_unazuki.bck", ""},
    };
    static anm_prm l_anmPrm[] = {
        {0x00, 0x00, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x00, 0x00, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x01, 0x01, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 4.0f, 1.0f},
        {0x02, 0x02, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   4.0f, 1.0f},
        {0x03, 0x03, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 4.0f, 1.0f},
        {0x04, 0x04, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 4.0f, 1.0f},
        {0x05, 0x81, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   0.0f, 1.0f},
        {0x06, 0x82, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 3.0f, 1.0f},
        {0x06, 0x82, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   3.0f, 1.0f},
        {0x07, 0x83, 0x03, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x07, 0x83, 0x03, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x08, 0x84, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 4.0f, 1.0f},
        {0x09, 0x05, 0x01, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x0A, 0x06, 0x02, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x0B, 0x07, 0x06, J3DFrameCtrl::LOOP_ONCE_e,   0.0f, 1.0f},
        {0x0C, 0x08, 0x07, J3DFrameCtrl::LOOP_ONCE_e,   0.0f, 1.0f},
        {0x0D, 0x09, 0x06, J3DFrameCtrl::LOOP_ONCE_e,   0.0f, 1.0f},
        {0x0E, 0x0A, 0x05, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x0F, 0x0B, 0x04, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x0F, 0x0B, 0x04, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, -1.0f},
        {0x10, 0x0C, 0x08, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x11, 0x0D, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x12, 0x0E, 0x09, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x13, 0x0F, 0x09, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x14, 0x10, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x15, 0x85, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x16, 0x11, 0x0A, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x17, 0x12, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x18, 0x13, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x19, 0x14, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x1A, 0x15, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x1B, 0x16, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.4f},
        {0x1C, 0x17, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 0.0f},
        {0x1B, 0x16, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, -1.4f},
        {0x1D, 0x18, 0x0B, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x1E, 0x19, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x1F, 0x86, 0x0C, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x20, 0x87, 0x0C, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x17, 0x12, 0x05, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x21, 0x1A, 0x0D, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x22, 0x1B, 0x00, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x1A, 0x15, 0x05, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
        {0x23, 0x1C, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x24, 0x1D, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x25, 0x1E, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x25, 0x1E, 0x05, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x07, 0x83, 0x03, J3DFrameCtrl::LOOP_REPEAT_e, 8.0f, 1.0f},
        {0x04, 0x04, 0x05, J3DFrameCtrl::LOOP_REPEAT_e, 4.0f, 1.0f},
        {0x00, 0x00, 0x00, J3DFrameCtrl::LOOP_REPEAT_e, 0.0f, 1.0f},
        {0x26, 0x1F, 0x0F, J3DFrameCtrl::LOOP_ONCE_e,   8.0f, 1.0f},
    };
    static anm_tbl armAnmTbl[] = {
        {"mdarm_wait01.bck", ""},
        {"mdarm_walk.bck", "mdarm_run.bck"},
        {"mdarm_squatdown.bck", ""},
        {"mdarm_sqwait01.bck", ""},
        {"mdarm_sqwait02.bck", ""},
        {"mdarm_fall.bck", ""},
        {"mdarm_fall02.bck", ""},
        {"mdarm_land.bck", ""},
        {"mdarm_land02.bck", ""},
        {"mdarm_land03.bck", ""},
        {"mdarm_kamaewait.bck", ""},
        {"mdarm_kamae.bck", ""},
        {"mdarm_piyo2.bck", ""},
        {"mdarm_ojigi.bck", ""},
        {"mdarm_harpplay01.bck", ""},
        {"mdarm_harpplay02.bck", ""},
        {"mdarm_takeoff01.bck", ""},
        {"mdarm_watasu.bck", ""},
        {"mdarm_talk01.bck", ""},
        {"mdarm_talk02.bck", ""},
        {"mdarm_talk03.bck", ""},
        {"mdarm_talk04.bck", ""},
        {"mdarm_mkamae.bck", ""},
        {"mdarm_mwait.bck", ""},
        {"mdarm_oriwait.bck", ""},
        {"mdarm_shipwait.bck", ""},
        {"mdarm_kyohi.bck", ""},
        {"mdarm_kyoro2.bck", ""},
        {"mdarm_shipwait02.bck", ""},
        {"mdarm_shiptalk01.bck", ""},
        {"mdarm_talk05.bck", ""},
        {"mdarm_unazuki.bck", ""},
    };
    static anm_tbl wingAnmTbl[] = {
        {"mdwing_wait01.bck", ""},
        {"mdwing_firing.bck", ""},
        {"mdwing_fly01.bck", ""},
        {"mdwing_fly02.bck", ""},
        {"mdwing_gliding.bck", ""},
        {"mdwing_takeoff02.bck", ""},
        {"mdwing_caught01.bck", ""},
        {"mdwing_caught02.bck", ""},
    };
    
    BOOL ret = FALSE;
    
    m3104 = anmIdx;
    anm_prm* prm = &l_anmPrm[anmIdx];
    
    f32 speed = prm->speed;
    f32 morf = prm->morf;
    if (anmIdx == 6) {
        speed = l_HIO.m118;
    } else if (anmIdx == 9 || anmIdx == 0xA) {
        speed = l_HIO.m11C;
    } else if (anmIdx == 0x2E) {
        speed = l_HIO.m124;
    } else if (anmIdx == 0x28) {
        morf = l_HIO.m068.m4;
        speed = l_HIO.m068.m8;
    }
    if (anmIdx == 7 || anmIdx == 8) {
        morf = l_HIO.m1A8;
    }
    
    if (prm->anmTblIdx != m312D || mpMorf->getPlaySpeed() != prm->speed) {
        m312D = prm->anmTblIdx;
        anm_tbl* bodyAnm = &l_anmTbl[m312D];
        m312A = 0;
        dNpc_Md_setAnm(mpMorf, m30FC, prm->loopMode, morf, speed, bodyAnm->m00, bodyAnm->m20, mModelArcName);
        m30D0 = mpMorf->getFrame();
        
        if (prm->armAnmTblIdx < 0x80) {
            anm_tbl* armAnm = &armAnmTbl[prm->armAnmTblIdx];
            dNpc_Md_setAnm(mpArmMorf, m30FC, prm->loopMode, morf, speed, armAnm->m00, armAnm->m20, mModelArcName);
            ret = FALSE;
        } else {
            if (!isTypeShipRide()) {
                dNpc_Md_setAnm(mpWingMorf, prm->loopMode, morf, speed, wingAnmTbl[prm->armAnmTblIdx - 0x80].m00, mModelArcName);
            }
            ret = TRUE;
        }
        
        if (m3104 == 0x12 || m3104 == 0x1F) {
            fopAcM_seStartCurrent(this, JA_SE_CM_MD_HARP_SET_UP, 0);
        } else if (m3104 == 0x13 || m3104 == 0x21) {
            fopAcM_seStartCurrent(this, JA_SE_CM_MD_HARP_TAKE_OFF, 0);
        }
    }
    
    if (prm->btpAnmTblIdx != m3137) {
        initTexPatternAnm(prm->btpAnmTblIdx, true);
    }
    
    if (m312D == 0x0E || m312D == 0x12 || m312D == 0x13 || m312D == 0x1A || m312D == 0x1C || m312D == 0x25) {
        cLib_onBit(m30F0, 0x80UL); // TODO inline
    } else if (m312D != 0x0F && m312D != 0x1B) {
        cLib_offBit(m30F0, 0x80UL); // TODO inline
    }
    
    if (m312D == 0x1B || m312D == 0x1C) {
        cLib_onBit(m30F0, 0x4000UL); // TODO inline
    } else {
        cLib_offBit(m30F0, 0x4000UL); // TODO inline
    }
    
    if (m312D == 0x10) {
        if (m0508[1] == NULL) {
            m0508[1] = dComIfGp_particle_set(0x819D, &current.pos, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this), &tevStr.mColorK0, &tevStr.mColorK0);
            if (m0508[1]) {
                m0508[1]->becomeImmortalEmitter();
            }
        }
    } else {
        deletePiyoPiyo();
    }
    
    return ret;
}

/* 0000D4CC-0000D5E4       .text dNpc_Md_setAnm__10daNpc_Md_cFP15mDoExt_McaMorf2fiffPcPcPCc */
bool daNpc_Md_c::dNpc_Md_setAnm(mDoExt_McaMorf2* pMorf, f32 param_f1, int loopMode, f32 morf, f32 speed, char* fileName1, char* filename2, const char* arcName) {
    bool ret = false;
    J3DAnmTransform* bck1 = NULL;
    J3DAnmTransform* bck2 = NULL;
    if (pMorf) {
        bck1 = (J3DAnmTransform*)dComIfG_getObjectRes(arcName, fileName1);
        if (strcmp(filename2, "") != 0) {
            bck2 = (J3DAnmTransform*)dComIfG_getObjectRes(arcName, filename2);
        }
        pMorf->setAnm(bck1, bck2, param_f1, loopMode, morf, speed, 0.0f, -1.0f, NULL);
        ret = true;
    }
    return ret;
}

/* 0000D5E4-0000D614       .text dNpc_Md_setAnm__10daNpc_Md_cFP14mDoExt_McaMorfiffPcPCc */
bool daNpc_Md_c::dNpc_Md_setAnm(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, char* animFilename, const char* arcName) {
    return dNpc_setAnmFNDirect(pMorf, loopMode, morf, speed, animFilename, NULL, arcName);
}

/* 0000D614-0000D82C       .text chkAttention__10daNpc_Md_cF4cXyzsi */
void daNpc_Md_c::chkAttention(cXyz, s16, int) {
    /* Nonmatching */
}

/* 0000D82C-0000D8FC       .text chkArea__10daNpc_Md_cFP4cXyz */
void daNpc_Md_c::chkArea(cXyz*) {
    /* Nonmatching */
}

/* 0000D8FC-0000D950       .text carryCheck__10daNpc_Md_cFv */
void daNpc_Md_c::carryCheck() {
    if (fopAcM_checkCarryNow(this)) {
        setNpcAction(&daNpc_Md_c::carryNpcAction);
    }
}

/* 0000D950-0000DAD4       .text eventOrder__10daNpc_Md_cFv */
void daNpc_Md_c::eventOrder() {
    /* Nonmatching */
}

/* 0000DAD4-0000DC14       .text checkOrder__10daNpc_Md_cFv */
void daNpc_Md_c::checkOrder() {
    /* Nonmatching */
}

/* 0000DC14-0000DCB0       .text checkCommandTalk__10daNpc_Md_cFv */
BOOL daNpc_Md_c::checkCommandTalk() {
    if (eventInfo.checkCommandTalk()) {
        if (dComIfGp_event_chkTalkXY()) {
            onXYTalk();
            if (!isDefaultTalkXY()) {
                if (mCurEventMode == 3) {
                    mCurEventMode = 0;
                }
                return FALSE;
            }
        } else {
            offXYTalk();
        }
        return TRUE;
    } else {
        offXYTalk();
        return FALSE;
    }
}

/* 0000DCB0-0000E410       .text next_msgStatus__10daNpc_Md_cFPUl */
u16 daNpc_Md_c::next_msgStatus(u32* pCurrMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    switch (*pCurrMsgNo) {
    case 0x5AC:
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17D5:
    case 0x1805:
        *pCurrMsgNo = 0x17D6;
        break;
    case 0x17D6:
        *pCurrMsgNo = 0x17D7;
        break;
    case 0x17D7:
        *pCurrMsgNo = 0x17D8;
        break;
    case 0x17D8:
        mCurEventMode = 4;
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17D9:
        *pCurrMsgNo = 0x1802;
        break;
    case 0x1802:
        *pCurrMsgNo = 0x17DA;
        break;
    case 0x17DA:
        *pCurrMsgNo = 0x17DB;
        break;
    case 0x17DB:
        dComIfGs_onEventBit(dSv_evtBit_c::MEDLI_GAVE_FATHERS_LETTER);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17DD:
        *pCurrMsgNo = 0x17DE;
        break;
    case 0x17DE:
        mCurEventMode = 5;
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17DF:
        *pCurrMsgNo = 0x17E0;
        break;
    case 0x17E0:
        *pCurrMsgNo = 0x17E1;
        break;
    case 0x17E1:
        *pCurrMsgNo = 0x17E2;
        break;
    case 0x17E2:
        *pCurrMsgNo = 0x17E3;
        break;
    case 0x17E4:
        dComIfGs_onEventBit(0x1101);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17E5:
        dComIfGs_onEventBit(0x1280);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17E6:
        *pCurrMsgNo = 0x17E7;
        break;
    case 0x17E7:
        *pCurrMsgNo = 0x17E8;
        break;
    case 0x17E8:
        *pCurrMsgNo = 0x17E9;
        break;
    case 0x17E9:
        *pCurrMsgNo = 0x17EA;
        break;
    case 0x17EA:
        *pCurrMsgNo = 0x17EB;
        break;
    case 0x17EB:
        *pCurrMsgNo = 0x17EC;
        break;
    case 0x17EC:
        *pCurrMsgNo = 0x17ED;
        break;
    case 0x17ED:
        *pCurrMsgNo = 0x17EE;
        break;
    case 0x17EE:
        if (l_msg->mSelectNum == 1) {
            *pCurrMsgNo = 0x17EF;
        } else {
            *pCurrMsgNo = 0x17F0;
        }
        break;
    case 0x17EF:
        *pCurrMsgNo = 0x17ED;
        break;
    case 0x17F0:
        *pCurrMsgNo = 0x17F1;
        break;
    case 0x17F1:
        mCurEventMode = 7;
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17F3:
        *pCurrMsgNo = 0x17F4;
        break;
    case 0x17F4:
        dComIfGs_onEventBit(0x1104);
        // Fall-through
    case 0x17F8:
        cLib_onBit(m30F0, 0x40UL);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17F7:
        *pCurrMsgNo = 0x17F8;
        break;
    case 0x17FA:
        *pCurrMsgNo = 0x17FB;
        break;
    case 0x17FB:
        *pCurrMsgNo = 0x17FC;
        break;
    case 0x17FC:
        *pCurrMsgNo = 0x17FD;
        break;
    case 0x17FD:
        *pCurrMsgNo = 0x17FE;
        break;
    case 0x17FE:
        *pCurrMsgNo = 0x17FF;
        break;
    case 0x1800:
        *pCurrMsgNo = 0x1801;
        break;
    case 0x1801:
        dComIfGs_onEventBit(0x1102);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x19C9:
        *pCurrMsgNo = 0x19CA;
        break;
    case 0x19CA:
        *pCurrMsgNo = 0x19CB;
        break;
    case 0x19CB:
        *pCurrMsgNo = 0x19CC;
        break;
    case 0x19CC:
        *pCurrMsgNo = 0x19CD;
        break;
    case 0x19CD:
        *pCurrMsgNo = 0x19CE;
        break;
    case 0x19CE:
        *pCurrMsgNo = 0x19CF;
        break;
    case 0x19CF:
        *pCurrMsgNo = 0x19D0;
        break;
    case 0x19D0:
        *pCurrMsgNo = 0x19D1;
        break;
    case 0x19D1:
        dComIfGs_onEventBit(0x1402);
        onSeaTalk();
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x19D2:
        *pCurrMsgNo = 0x19D3;
        break;
    case 0x19D3:
        *pCurrMsgNo = 0x19D4;
        break;
    case 0x19D4:
        *pCurrMsgNo = 0x19D5;
        break;
    case 0x19D6:
        *pCurrMsgNo = 0x19D7;
        break;
    case 0x19D7:
        *pCurrMsgNo = 0x19D8;
        break;
    case 0x19D8:
        dComIfGs_onEventBit(0x1504);
    case 0x19D9:
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x19DA:
        *pCurrMsgNo = 0x19DB;
        break;
    case 0x19DD:
        *pCurrMsgNo = 0x19DE;
        break;
    case 0x19E0:
        *pCurrMsgNo = 0x19E1;
        break;
    case 0x19E1:
        *pCurrMsgNo = 0x19E2;
        break;
    case 0x19E2:
        *pCurrMsgNo = 0x19E3;
        break;
    case 0x19E3:
        *pCurrMsgNo = 0x19E4;
        break;
    case 0x19E5:
        *pCurrMsgNo = 0x19E6;
        break;
    case 0x19E7:
        *pCurrMsgNo = 0x19E8;
        break;
    case 0x19F6:
        *pCurrMsgNo = 0x19F7;
        break;
    case 0x19F7:
        *pCurrMsgNo = 0x19D2;
        break;
    case 0x19F8:
        *pCurrMsgNo = 0x19F9;
        break;
    case 0x19F9:
        *pCurrMsgNo = 0x19FA;
        break;
    case 0x19FA:
        *pCurrMsgNo = 0x19FB;
        break;
    case 0x19FB:
    case 0x19FF:
        dComIfGs_onEventBit(0x2E40);
        onSeaTalk();
        // Fall-through
    case 0x1A01:
        dComIfGs_onEventBit(0x2C08);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x19FC:
        *pCurrMsgNo = 0x19FD;
        break;
    case 0x19FD:
        *pCurrMsgNo = 0x19FE;
        break;
    case 0x19FE:
        *pCurrMsgNo = 0x19FF;
        break;
    case 0x1A00:
        *pCurrMsgNo = 0x1A01;
        break;
    case 0x1A02:
        dComIfGs_onEventBit(0x3B80);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    default:
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msgStatus;
}

/* 0000E410-0000E64C       .text getMsg__10daNpc_Md_cFv */
u32 daNpc_Md_c::getMsg() {
    u32 msgNo = 0;
    if (isShipRide()) {
        msgNo = 0x19EF;
    } else if (isTypeAtorizk()) {
        if (dComIfGs_isEventBit(dSv_evtBit_c::MEDLI_GAVE_FATHERS_LETTER)) {
            msgNo = 0x17DC;
        } else if (dComIfGs_getClearCount() != 0) {
            msgNo = 0x1805;
        } else {
            msgNo = 0x17D5;
        }
    } else if (isTypeAdanmae()) {
        if (cLib_checkBit(m30F0, 0x40UL)) {
            if (m312D == 0x10) {
                static const u32 l_msg_num[] = {
                    0x17F5,
                    0x1803,
                    0x1804,
                };
                msgNo = l_msg_num[getPiyo2TalkCNT()];
                countPiyo2TalkCNT();
            } else {
                msgNo = 0x17F6;
            }
        } else if (dComIfGs_isEventBit(0x1104)) {
            msgNo = 0x17F7;
        } else {
            msgNo = 0x17E6;
        }
    } else if (isTypeM_Dra09()) {
        if (dComIfGs_isEventBit(0x1101)) {
            msgNo = 0x17E5;
        } else {
            msgNo = 0x17DD;
        }
    } else if (isTypeSea()) {
        if (isXYTalk()) {
            if (isDefaultTalkXY()) {
                if (dComIfGs_isEventBit(0x2E40)) {
                    msgNo = 0x1A00;
                } else if (dComIfGs_isEventBit(0x2C08)) {
                    msgNo = 0x19F8;
                } else {
                    msgNo = 0x19FC;
                }
            } else {
                if (dComIfGs_isEventBit(0x1504)) {
                    msgNo = 0x19D9;
                } else {
                    msgNo = 0x19D6;
                }
            }
        } else {
            if (dComIfGs_isEventBit(0x1402)) {
                if (isSeaTalk()) {
                    msgNo = 0x19D2;
                } else {
                    msgNo = 0x19F6;
                    onSeaTalk();
                }
            } else {
                msgNo = 0x19C9;
            }
        }
    } else if (isTypeM_Dai() || isTypeEdaichi()) {
        msgNo = 0x1A02;
    }
    return msgNo;
}

/* 0000E64C-0000E95C       .text setCollision__10daNpc_Md_cFv */
void daNpc_Md_c::setCollision() {
    /* Nonmatching */
}

/* 0000E95C-0000E9F0       .text setAttention__10daNpc_Md_cFb */
void daNpc_Md_c::setAttention(bool) {
    /* Nonmatching */
}

/* 0000E9F0-0000EB28       .text lookBack__10daNpc_Md_cFiii */
void daNpc_Md_c::lookBack(int, int, int) {
    /* Nonmatching */
}

/* 0000EB28-0000EC38       .text lookBack__10daNpc_Md_cFP4cXyzii */
void daNpc_Md_c::lookBack(cXyz*, int, int) {
    /* Nonmatching */
}

/* 0000EC38-0000EDD0       .text lookBackWaist__10daNpc_Md_cFsf */
void daNpc_Md_c::lookBackWaist(s16, f32) {
    /* Nonmatching */
}

/* 0000EDD0-0000F100       .text setBaseMtx__10daNpc_Md_cFv */
void daNpc_Md_c::setBaseMtx() {
    /* Nonmatching */
}

/* 0000F100-0000F160       .text deletePiyoPiyo__10daNpc_Md_cFv */
void daNpc_Md_c::deletePiyoPiyo() {
    /* Nonmatching */
}

/* 0000F160-0000F4E0       .text init__10daNpc_Md_cFv */
BOOL daNpc_Md_c::init() {
    /* Nonmatching */
}

/* 0000F4E0-0000F8EC       .text draw__10daNpc_Md_cFv */
BOOL daNpc_Md_c::draw() {
    if (isShipRide()) {
        if (dComIfGp_getShipActor() && dComIfGp_getShipActor()->checkHeadNoDraw()) {
            return TRUE;
        }
    } else {
        if (fopAcM_GetHomeRoomNo(this) < 0) {
            return TRUE;
        }
        if (!dComIfGp_roomControl_checkStatusFlag(current.roomNo, 0x10)) {
            return TRUE;
        }
    }
    
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    drawDamageFog();
    g_env_light.setLightTevColorType(model, &tevStr);
    m0520.entry(modelData);
    mpMorf->entryDL();
    m0520.remove(modelData);
    
    if (!isTypeShipRide()) {
        if (cLib_checkBit(m30F0, 0x1UL)) {
            model = mpWingMorf->getModel();
            g_env_light.setLightTevColorType(model, &tevStr);
            mpWingMorf->entryDL();
        } else {
            model = mpArmMorf->getModel();
            g_env_light.setLightTevColorType(model, &tevStr);
            mpArmMorf->entryDL();
        }
    } else {
        model = mpArmMorf->getModel();
        g_env_light.setLightTevColorType(model, &tevStr);
        mpArmMorf->entryDL();
    }
    
    g_env_light.setLightTevColorType(mpHarpModel, &tevStr);
    mDoExt_modelUpdateDL(mpHarpModel);
    
    if (isLightHit()) {
        mLightBtkAnm.entry(mpHarpLightModel->getModelData());
        mDoExt_modelUpdateDL(mpHarpLightModel);
        mLightBtkAnm.remove(mpHarpLightModel->getModelData());
        
        mDoMtx_copy(mpHarpModel->getBaseTRMtx(), mDoMtx_stack_c::get());
        mDoMtx_stack_c::transM(l_HIO.m034.m0C, l_HIO.m034.m10, l_HIO.m034.m14);
        Mtx mtx;
        mDoMtx_copy(mDoMtx_stack_c::get(), mtx);
        mDoMtx_stack_c::transS(l_ms_light_local_start);
        mDoMtx_stack_c::YrotM(0x8000);
        f32 temp = mCps.GetAtVecP()->abs();
        mDoMtx_stack_c::scaleM(0.1f, 0.1f, temp * (1.0f/9600.0f));
        mDoMtx_stack_c::revConcat(mtx);
        m0B70.update(mDoMtx_stack_c::get(), 0xFF, 90.0f);
        dComIfGd_getXluList()->entryImm(&m0B70, 0x1F);
    }
    
    if (!isShipRide() && !fopAcM_CheckStatus(this, fopAcStts_CARRY_e) && cLib_checkBit(m30F0, 0x20000UL)) {
        cXyz shadowPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
        mShadowId = dComIfGd_setShadow(
            mShadowId, 0, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
            current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr,
            0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
        );
        
        if (mShadowId != 0) {
            dComIfGd_addRealShadow(mShadowId, model);
            dComIfGd_addRealShadow(mShadowId, mpHarpModel);
        }
    }
    
    dSnap_RegistFig(DSNAP_TYPE_MD, this, 1.0f, 1.0f, 1.0f);
    
    return TRUE;
}

/* 0000F8EC-0000FC18       .text animationPlay__10daNpc_Md_cFv */
void daNpc_Md_c::animationPlay() {
    /* Nonmatching */
}

/* 0000FC18-0000FC58       .text checkPlayerRoom__10daNpc_Md_cFv */
void daNpc_Md_c::checkPlayerRoom() {
    m_playerRoom = false;
    fopAc_ac_c* link = dComIfGp_getLinkPlayer();
    if (current.roomNo == link->current.roomNo) {
        m_playerRoom = true;
    }
}

/* 0000FC58-000108B0       .text execute__10daNpc_Md_cFv */
BOOL daNpc_Md_c::execute() {
    /* Nonmatching */
}

/* 000108B0-00010948       .text particle_set__10daNpc_Md_cFPP14JPABaseEmitterUs */
void daNpc_Md_c::particle_set(JPABaseEmitter** pEmitter, u16 particleID) {
    if (*pEmitter) {
        return;
    }
    (*pEmitter) = dComIfGp_particle_set(particleID, &current.pos, &current.angle, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this), &tevStr.mColorK0, &tevStr.mColorK0);
    if (*pEmitter) {
        (*pEmitter)->becomeImmortalEmitter();
    }
}

/* 00010948-000109A0       .text emitterTrace__10daNpc_Md_cFP14JPABaseEmitterPA4_fP5csXyz */
void daNpc_Md_c::emitterTrace(JPABaseEmitter* emitter, MtxP mtx, csXyz* angle) {
    if (emitter == NULL) {
        return;
    }
    JGeometry::TVec3<f32> pos;
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    emitter->setGlobalTranslation(pos);
    if (angle) {
        JGeometry::TVec3<s16> rot;
        rot.x = angle->x;
        rot.y = angle->y;
        rot.z = angle->z;
        emitter->setGlobalRotation(rot);
    }
}

/* 000109A0-000109DC       .text emitterDelete__10daNpc_Md_cFPP14JPABaseEmitter */
void daNpc_Md_c::emitterDelete(JPABaseEmitter** pEmitter) {
    if (*pEmitter == NULL) {
        return;
    }
    (*pEmitter)->quitImmortalEmitter();
    (*pEmitter)->becomeInvalidEmitter();
    (*pEmitter) = NULL;
}

/* 000109DC-000110BC       .text __dt__10daNpc_Md_cFv */
daNpc_Md_c::~daNpc_Md_c() {
    dComIfG_resDelete(&mPhase, mModelArcName);
    if (heap) {
        mpMorf->stopZelAnime();
    }
    deletePiyoPiyo();
    emitterDelete(&m0508[0]);
    deleteHane02Emitter();
    deleteHane03Emitter();
    m3058.end();
    m304C.end();
    m3074.remove();
    if (l_HIO.mChildID >= 0) {
        mDoHIO_root.mDoHIO_deleteChild(l_HIO.mChildID);
        l_HIO.mChildID = -1;
    }
    m_flying = false;
    m_mirror = false;
    m_playerRoom = false;
}

/* 000110BC-000110DC       .text daNpc_Md_Create__FP10fopAc_ac_c */
static s32 daNpc_Md_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Md_c*>(i_this)->create();
}

/* 000110DC-00011104       .text daNpc_Md_Delete__FP10daNpc_Md_c */
static BOOL daNpc_Md_Delete(daNpc_Md_c* i_this) {
    i_this->~daNpc_Md_c();
    return TRUE;
}

/* 00011104-00011124       .text daNpc_Md_Execute__FP10daNpc_Md_c */
static BOOL daNpc_Md_Execute(daNpc_Md_c* i_this) {
    return i_this->execute();
}

/* 00011124-00011144       .text daNpc_Md_Draw__FP10daNpc_Md_c */
static BOOL daNpc_Md_Draw(daNpc_Md_c* i_this) {
    return i_this->draw();
}

/* 00011144-0001114C       .text daNpc_Md_IsDelete__FP10daNpc_Md_c */
static BOOL daNpc_Md_IsDelete(daNpc_Md_c* i_this) {
    return TRUE;
}

/* 0001114C-0001119C       .text execute__26daNpc_Md_followEcallBack_cFP14JPABaseEmitter */
void daNpc_Md_followEcallBack_c::execute(JPABaseEmitter* emitter) {
    emitter->setGlobalTranslation(mPos.x, mPos.y, mPos.z);
    JGeometry::TVec3<s16> rot;
    rot.x = mAngle.x;
    rot.y = mAngle.y;
    rot.z = mAngle.z;
    emitter->setGlobalRotation(rot);
}

/* 0001119C-000111A4       .text setup__26daNpc_Md_followEcallBack_cFP14JPABaseEmitterPC4cXyzPC5csXyzSc */
void daNpc_Md_followEcallBack_c::setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, s8) {
    mpEmitter = emitter;
}

/* 000111A4-000111D8       .text end__26daNpc_Md_followEcallBack_cFv */
void daNpc_Md_followEcallBack_c::end() {
    if (mpEmitter) {
        mpEmitter->becomeInvalidEmitter();
        mpEmitter->setEmitterCallBackPtr(NULL);
        mpEmitter = NULL;
    }
}

static actor_method_class l_daNpc_Md_Method = {
    (process_method_func)daNpc_Md_Create,
    (process_method_func)daNpc_Md_Delete,
    (process_method_func)daNpc_Md_Execute,
    (process_method_func)daNpc_Md_IsDelete,
    (process_method_func)daNpc_Md_Draw,
};

actor_process_profile_definition g_profile_NPC_MD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_NPC_MD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Md_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0175,
    /* Actor SubMtd */ &l_daNpc_Md_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK2000000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
