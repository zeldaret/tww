/**
 * d_a_npc_md.cpp
 * Player - Medli / リト族（メドリ） ("Rito (Medli)" (Ritozoku (Medli)))
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_md.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_mtx.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_snap.h"
#include "f_op/f_op_camera.h"
#include "d/actor/d_a_ship.h"
#include "d/d_kankyo_wether.h"
#include "d/d_camera.h"
#include "d/d_detect.h"

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
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsPlayer_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
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
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};

static dCcD_SrcCyl l_light_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};

static dCcD_SrcCps l_fan_light_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_LIGHT,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoHitMark_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 70.0f,
    }},
};

static dCcD_SrcCyl l_wind_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
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
#if VERSION > VERSION_DEMO
    m26 = 0x19;
    m28 = 0x7FFF;
    m2A = 1;
#endif
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
    mNo = -1;
}

/* 000006DC-000006FC       .text daNpc_Md_XyCheckCB__FPvi */
static s16 daNpc_Md_XyCheckCB(void* i_this, int param_1) {
    return static_cast<daNpc_Md_c*>(i_this)->XyCheckCB(param_1);
}

/* 000006FC-000007FC       .text XyCheckCB__10daNpc_Md_cFi */
s16 daNpc_Md_c::XyCheckCB(int i_itemBtn) {
    u8 selectItemNo = dComIfGp_getSelectItem(i_itemBtn);
    if (isTypeSea()) {
        if (selectItemNo == dItem_WIND_WAKER_e) {
            return TRUE;
        }
        if (selectItemNo == dItem_GOLDEN_FEATHER_e) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E40) || (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E40) && m_seaTalk)) {
                return TRUE;
            }
        }
    } else if (isTypeM_Dai() || isTypeEdaichi()) {
        if (selectItemNo == dItem_GOLDEN_FEATHER_e && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3B80)) {
            return TRUE;
        }
    }
    if (selectItemNo == dItem_GOLDEN_FEATHER_e) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C08);
    }
    return FALSE;
}

/* 000007FC-0000081C       .text daNpc_Md_XyEventCB__FPvi */
static s16 daNpc_Md_XyEventCB(void* i_this, int param_1) {
    return static_cast<daNpc_Md_c*>(i_this)->XyEventCB(param_1);
}

/* 0000081C-00000864       .text XyEventCB__10daNpc_Md_cFi */
s16 daNpc_Md_c::XyEventCB(int i_itemBtn) {
    u8 selectItemNo = dComIfGp_getSelectItem(i_itemBtn);
    if (selectItemNo == dItem_WIND_WAKER_e) {
        offDefaultTalkXY();
        return mEventIdxTable[5];
    } else if (selectItemNo == dItem_GOLDEN_FEATHER_e) {
        onDefaultTalkXY();
    }
    return -1;
}

/* 00000864-00000884       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Md_c*>(i_this)->createHeap();
}

/* 00000884-00000D80       .text create__10daNpc_Md_cFv */
cPhs_State daNpc_Md_c::create() {
    m313D = 0;
    strcpy(mModelArcName, l_arc_name);
    int heapSizeIdx = 0;

#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(this, daNpc_Md_c);
#endif

    mType = fopAcM_GetParam(this) >> 0x08;
    if ((int)mType == -2) { // !@bug: Comparing unsigned value with -2 is always false.
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1620);
    } else {
        if (dComIfGs_isCollect(0, 2)) {
            if (strcmp(dComIfGp_getStartStageName(), "M_DaiB") != 0) {
                return cPhs_ERROR_e;
            } else {
                setTypeM_DaiB();
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "sea") == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) || !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820) ||
                !dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC))
            {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Atorizk") == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) || dNpc_chkLetterPassed()) {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Adanmae") == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) || !dNpc_chkLetterPassed()) {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "M_Dra09") == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) || dComIfGs_isEventBit(dSv_event_flag_c::UNK_1101)) {
                return cPhs_ERROR_e;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Edaichi") == 0) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) || dComIfGs_isEventBit(dSv_event_flag_c::UNK_2920)) {
                return cPhs_ERROR_e;
            }
            setTypeEdaichi();
        } else if (strcmp(dComIfGp_getStartStageName(), "M_Dai") == 0) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) || !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2920)) {
                return cPhs_ERROR_e;
            }
            setTypeM_Dai();
        } else if (strcmp(dComIfGp_getStartStageName(), "M_DaiB") == 0) {
            return cPhs_ERROR_e;
        }
    }

    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) && dComIfGs_isEventBit(dSv_event_flag_c::UNK_1608)) {
        setTypeShipRide();
        strcpy(mModelArcName, l_arc_name_ship);
        heapSizeIdx = 1;
    }

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, mModelArcName);
    m313D = 1;
    if (phase_state == cPhs_COMPLEATE_e) {
#if VERSION == VERSION_DEMO
        fopAcM_SetupActor(this, daNpc_Md_c);
#endif

        if (dComIfGp_getCb1Player() != NULL) {
            return cPhs_ERROR_e;
        }

        static int l_heep_size[] = {
            0x7660,
            0x61C0,
        };
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, l_heep_size[heapSizeIdx])) {
#if VERSION > VERSION_DEMO
            mpMorf = NULL;
            mpArmMorf = NULL;
            mpWingMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }

        if (isTypeM_Dai()) {
            u8 flag = dComIfGs_getPlayerPriestFlag();
            if (flag == 2) {
                dComIfGs_setRestartOption(&dComIfGs_getPlayerPriestPos(), dComIfGs_getPlayerPriestRotate(), dComIfGs_getPlayerPriestRoomNo(), 2);
            }
            checkRestart(2);
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());

        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_createChild("リト族（メドリ）", &l_HIO); // "Rito (Medli)" (Ritozoku (Medli))
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
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
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
static BOOL waistNodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Md_c* i_this = (daNpc_Md_c*)model->getUserArea();
        if (i_this) {
            s32 jntNo = joint->getJntNo();
            mDoMtx_multVecArray(model->getAnmMtx(jntNo), waistVecDat, i_this->getPHairWall(), ARRAY_SIZE(waistVecDat));
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            if (i_this->checkStatus(daNpc_Md_c::daMdStts_UNK4000)) {
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
static BOOL armNodeCallBack(J3DNode* node, int calcTiming) {
    // This handles copying the matrices of Medli's arms and wings from the body model to the
    // separate arm/wing models.
    if (calcTiming == J3DNodeCBCalcTiming_In) {
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
            r1_108 = r1_108 * std::sqrtf(f30 * f30 - f31 * f31);
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
            r1_108 = r1_108 * std::sqrtf(f30 * f30 - f31 * f31);
            *i_r5 = r1_120 + r1_108;
            return TRUE;
        }
    }

    return FALSE;
}

/* 00001CBC-00001D0C       .text hairTopNodeCallBack__FP7J3DNodei */
static BOOL hairTopNodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
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
static BOOL hairNodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
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
                    *r29 = (*hairPos - *i_this->getPHairPos(i - 1));
                    *hairDist = r29->abs();
                    break;
                }

                cXyz* r25 = i_this->getPHairPos(i - 1);
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
                cXyz* r22 = i_this->getPHairVec(i - 1);
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

                s16 prevHaitJntNo = i_this->getHairJntNum(i - 1);
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
    JUT_ASSERT(1995, modelData != NULL);

    mpMorf = new mDoExt_McaMorf2(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes(mModelArcName, wait_anim_name),
        NULL,
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
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
    JUT_ASSERT(2051, modelData != NULL);

    mpArmMorf = new mDoExt_McaMorf2(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes(mModelArcName, arm_wait_anim_name),
        NULL,
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        0,
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
        JUT_ASSERT(2083, modelData != NULL);

        mpWingMorf = new mDoExt_McaMorf(
            modelData,
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes(mModelArcName, "mdwing_wait01.bck"),
            J3DFrameCtrl::EMode_LOOP,
            1.0f,
            0,
            -1,
            0,
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
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, ARRAY_SIZE(mAcchCir), mAcchCir, fopAcM_GetSpeed_p(this));
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
#if VERSION > VERSION_DEMO
    m_flying = false;
#endif
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
        dComIfGp_setRStatusForce(dActStts_RETURN_e);
        if (chkPlayerAction(&daNpc_Md_c::mkamaePlayerAction)) {
            dComIfGp_setDoStatus(dActStts_BLANK_e);
            dComIfGp_setAStatus(dActStts_PUT_AWAY_e);
        } else {
            dComIfGp_setDoStatus(dActStts_ba_motu__dupe_2E);
            dComIfGp_setAStatus(dActStts_HIDDEN_e);
            if (!m3140) {
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
        }
    } else {
        dComIfGp_setDoStatus(dActStts_FLY_e);
        if (chkPlayerAction(&daNpc_Md_c::flyPlayerAction)) {
            dComIfGp_setRStatusForce(dActStts_HIDDEN_e);
            dComIfGp_setAStatus(dActStts_LET_GO_e);
        } else {
            dComIfGp_setRStatusForce(dActStts_RETURN_e);
            dComIfGp_setAStatus(dActStts_HIDDEN_e);
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

    int r31 = !r26 ? 0 : attention.LockonTruth() ? 1 : -1;

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

    param_2->set(current.pos.x + 100.0f * cM_ssin(param_1), current.pos.y, current.pos.z + 100.0f * cM_scos(param_1));

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
    particle_set(&m0508[0], dPa_name::ID_SCENE_819B);
}

/* 00003674-000036C0       .text setHane02Emitter__10daNpc_Md_cFv */
void daNpc_Md_c::setHane02Emitter() {
    particle_set(&m0508[2], dPa_name::ID_SCENE_8217);
    particle_set(&m0508[3], dPa_name::ID_SCENE_8217);
}

/* 000036C0-000036FC       .text deleteHane02Emitter__10daNpc_Md_cFv */
void daNpc_Md_c::deleteHane02Emitter() {
    emitterDelete(&m0508[2]);
    emitterDelete(&m0508[3]);
}

/* 000036FC-00003748       .text setHane03Emitter__10daNpc_Md_cFv */
void daNpc_Md_c::setHane03Emitter() {
    particle_set(&m0508[4], dPa_name::ID_SCENE_827D);
    particle_set(&m0508[5], dPa_name::ID_SCENE_827D);
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
    return chkPlayerAction(&daNpc_Md_c::jumpPlayerAction) || chkNpcAction(&daNpc_Md_c::fallNpcAction) || chkNpcAction(&daNpc_Md_c::fall02NpcAction);
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
                    dComIfGp_particle_set(dPa_name::ID_SCENE_8232, &current.pos, NULL, NULL, 0xFF, &m3058);
                }
            } else if (m3058.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_SCENE_8232, &current.pos, NULL, NULL, 0xFF, &m3058);
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
            m304C.makeEmitter(dPa_name::ID_SCENE_8226, mpHarpLightModel->getBaseTRMtx(), &current.pos, NULL);
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
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1620)) {
        return;
    }
    f32 dist_sq = fopAcM_searchPlayerDistance2(this);
    if (!checkNpcCallCommand()) {
        if (dist_sq < SQUARE(l_HIO.m0C8)) {
            daPy_getPlayerLinkActorClass()->onNpcCallCommand();
            *r31 = 1;
        }
    } else {
        f32 temp = 2.0f * l_HIO.m0C4;
        if (dist_sq >= temp * temp) {
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
            if (std::abs(sp3C.x) < 0.001f && std::abs(sp3C.z) < 0.001f) {
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
    if (mAcch.ChkGroundHit()) {
        if (mType != 2) {
            if (dComIfG_Bgsp()->GetSpecialCode(mAcch.m_gnd) == 1) {
                cLib_addCalcAngleS(&shape_angle.y, cM_atan2s(m32A4.x, m32A4.z), 8, 0x2000, 0x400);
                speedF += 0.5f;
                f32 f1 = l_HIO.m008.m08;
                f32 f0 = speedF;
                speedF = (f1 > f0) ? f1 : f0;
            } else {
                speedF = 0.0f;
            }
        }
    } else {
        if (daPy_getPlayerActorClass() != this) {
            setNpcAction(&daNpc_Md_c::fallNpcAction);
        }
    }
}

/* 0000433C-000043D4       .text chkAdanmaeDemoOrder__10daNpc_Md_cFv */
BOOL daNpc_Md_c::chkAdanmaeDemoOrder() {
    if (isTypeAdanmae()) {
        f32 groundH = mAcch.GetGroundH();
        if (checkStatusCamTagIn() && cLib_checkMinMaxLimit(groundH, 600.0f, 700.0f)) {
            mCurEventMode = 6;
            gravity = l_HIO.m0F4;
            maxFallSpeed = -100.0f;
            if (mAcch.ChkGroundHit()) {
                speedF = 0.0f;
            }
            return TRUE;
        }
    }
    return FALSE;
}

/* 000043D4-00004B04       .text waitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::waitNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        if (isTypeSea()) {
#if VERSION == VERSION_DEMO
            if (m3104 == 0x1E || m3104 == 0x29)
#else
            if (m3104 == 0x1E || m3104 == 0x29 || m312D == 0xE || m312D == 0x12 || m312D == 0x13 || m312D == 0x1A || m312D == 0x25)
#endif
            {
                setHarpPlayNum(1);
            } else {
                setAnm(0x12);
            }
        } else if (isTypeM_Dra09() && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1140)) {
            setAnm(0x22);
        } else if (isTypeM_Dai() || isTypeEdaichi()) {
            if (!checkStatus(0x80UL)) {
                setAnm(0);
            }
        } else {
            setAnm(0);
        }
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
#if VERSION == VERSION_DEMO
        setBitStatus(daMdStts_UNK4);
#else
        if (!isTypeSea()) {
            setBitStatus(daMdStts_UNK4);
        } else {
            clearStatus(daMdStts_UNK4);
        }
#endif
        shape_angle.x = 0;
        shape_angle.z = 0;
        speedF = 0.0f;
        m30F8 = 120.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        m3144 = 150;
        mActionStatus++; // ACTION_ONGOING_1
    } else if (mActionStatus != ACTION_ENDING) {
        if (m312A != 0) {
            if (m3104 == 0x12) {
                setHarpPlayNum(1);
            } else if (m3104 == 0x13 || m3104 == 0x21) {
                setAnm(0);
            } else if (m3104 == 0x16 || m3104 == 0x17 || m3104 == 0x11) {
                setHarpPlayNum(1);
            }
        }

        if (isTypeAdanmae() && dComIfGs_isEventBit(dSv_event_flag_c::UNK_1102)) {
            fopAcM_delete(this);
            return TRUE;
        }

        int sp08 = 0;

        if (isTypeSea() && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1402)) {
            daPy_lk_c* link = daPy_getPlayerLinkActorClass();
            f32 playerDistXZ2 = fopAcM_searchPlayerDistanceXZ2(this);
            f32 playerDistY = link->current.pos.y - current.pos.y;
            f32 f3 = l_HIO.m0BC;
            f32 f4 = l_HIO.m0C0;
            if (playerDistXZ2 < SQUARE(l_HIO.m0CC) && playerDistY < f3 && playerDistY > f4) {
                mCurEventMode = 0xB;
            }
        } else {
            s16 headAngle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
            cLib_offBit<u32>(attention_info.flags, (fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e));
            m312C = chkAttention(current.pos, headAngle, 1);
            sp08 = m312C;
            if (sp08 != 0) {
                if (isTypeAtorizk() || isTypeAdanmae() || isTypeSea()) {
                    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
                }
                if (isTypeAtorizk() || isTypeAdanmae()) {
                    mCurEventMode = 2;
                } else if (isTypeM_Dra09()) {
                    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1140)) {
                        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1101)) {
                            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e);
                            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK800000_e)) {
                                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1280);
                            }
                            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1280)) {
                                mCurEventMode = 2;
                            } else {
                                mCurEventMode = 1;
                            }
                        } else {
                            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
                            mCurEventMode = 2;
                        }
                    } else {
                        setAnm(0x22);
                    }
                } else if (isTypeSea()) {
                    if (mCurEventMode == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_1402)) {
                        mCurEventMode = 3;
                    }
                } else {
                    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
                }
            }
            NpcCall(&sp08);
        }

        if (isTypeM_Dra09() && dComIfGs_isEventBit(dSv_event_flag_c::UNK_1101) && dComIfGs_isSwitch(m3100, fopAcM_GetRoomNo(this))) {
            setNpcAction(&daNpc_Md_c::demoFlyNpcAction);
        }

        if (isTypeM_Dai() || isTypeEdaichi()) {
            if (m3104 == 0) {
                if (cLib_calcTimer(&m3144) == 0) {
                    setAnm(40);
                }
            } else if (m3104 == 0x28 && m312A != 0) {
                setAnm(0);
                m3144 = (s16)cM_rndF(180.0f) + 60;
            }
        }

        if (isTypeAtorizk()) {
            if (chkArea(&current.pos)) {
                lookBack(sp08, 0, 1);
            } else {
                lookBack(0, 0, 0);
            }
        } else if (isTypeM_Dra09()) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1140)) {
                lookBack(1, 0, 0);
                setAnm(0);
            } else {
                lookBack(1, 0, 1);
            }
        } else {
            if (m3104 == 0x16 || m3104 == 0x17) {
                mJntCtrl.lookAtTarget(&shape_angle.y, NULL, cXyz::Zero, shape_angle.y, 0, false);
            }
            if (chkArea(&current.pos)) {
                if (isTypeSea()) {
                    lookBack(sp08, 0, 1);
                } else {
                    lookBack(sp08, 0, 0);
                }
            } else {
                lookBack(0, 0, 0);
            }
        }
        waitGroundCheck();
        current.angle.y = shape_angle.y;
        setAttention(true);
    }
    return TRUE;
}

/* 00004B04-00004CFC       .text harpWaitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::harpWaitNpcAction(void*) {
    BOOL bVar2;

    if (mActionStatus == ACTION_STARTING) {
        setHarpPlayNum(1);
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        m30F0 = 0;
        setBitStatus(daMdStts_UNK80);
        shape_angle.x = 0;
        shape_angle.z = 0;
        speedF = 0.0f;
        m30F8 = 120.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
        m3144 = 0;
        m3146 = 0xc;
    } else if (mActionStatus != ACTION_ENDING) {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (m312A != 0) {
                m3146--;
                if (m3146 != 0) {
                    setHarpPlayNum(1);
                } else {
                    setAnm(0x11);
                    m3146 = 0x78;
                    mActionStatus++;
                }
            }
        } else {
            m3146--;
            if (m3146 == 0) {
                setHarpPlayNum(1);
                m3146 = 0xc;
                mActionStatus = ACTION_ONGOING_1;
            }
        }
        if ((mType == 6) && (m3146 == 0xc)) {
            bVar2 = false;
            if (m3104 == 0x16) {
                if (mpMorf->checkFrame(11.0f)) {
                    bVar2 = true;
                }
            } else if ((m3104 == 0x17) && (mpMorf->checkFrame(11.0f))) {
                bVar2 = true;
            }
            if (bVar2) {
                mDoAud_bgmStart(JA_BGM_MEDORI_TAKT_8);
            }
        }
        setAttention(true);
    }
    return TRUE;
}

static fpc_ProcID l_msgId;
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
    if (mActionStatus == ACTION_STARTING) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mMsgNo = getMsg();
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
        m312B = 0;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
        m312C = chkAttention(current.pos, angle, 0);
        if (mActionStatus == ACTION_ONGOING_1) {
            if (XYTalkCheck()) {
                mActionStatus = ACTION_ONGOING_2;
            }
        } else if (mActionStatus == ACTION_ONGOING_2) {
            if (talk_init()) {
                mActionStatus = ACTION_ONGOING_3;
            }
        } else if (mActionStatus == ACTION_ONGOING_3) {
            if (talk(0)) {
                if ((mType == 0) || (mType == 2)) {
                    mActionStatus = 4;
                } else if (mType == 1) {
                    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1104)) {
                        setNpcAction(&daNpc_Md_c::squatdownNpcAction);
                    }
                } else {
                    setNpcAction(&daNpc_Md_c::waitNpcAction);
                }
                dComIfGp_event_reset();
            }
        } else if (mType == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::MEDLI_GAVE_FATHERS_LETTER)) {
                setNpcAction(&daNpc_Md_c::waitNpcAction);
            }
        } else if ((mType == 2) && (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1101))) {
            setNpcAction(&daNpc_Md_c::waitNpcAction);
        }
        mJntCtrl.mbTrn = true;
        lookBack(1, 0, 0);
        current.angle.y = shape_angle.y;
        setAttention(mpMorf->isMorf());
    }
    return TRUE;
}

/* 0000504C-000051FC       .text shipTalkNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::shipTalkNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        onNpcNotChange();
        onShipRide();
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mMsgNo = getMsg();
        setAnm(0x2b);
        m312B = 0;
        mActionStatus++;
    } else if (mActionStatus == ACTION_ENDING) {
        offShipRide();
    } else {
        s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
        m312C = chkAttention(current.pos, angle, 0);
        if (mActionStatus == ACTION_ONGOING_1) {
            if (talk_init()) {
                mActionStatus = ACTION_ONGOING_2;
            }
        } else {
            if (talk(0)) {
                dComIfGp_event_reset();
                setNpcAction(&daNpc_Md_c::shipNpcAction);
            }
        }
        lookBack(1, 0, 1);
        current.angle.y = shape_angle.y;
        setAttention(mpMorf->isMorf());
    }
    return TRUE;
}

/* 000051FC-00005308       .text kyohiNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::kyohiNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
        setAnm(0x27);
        speedF = 0.0f;
        m30F8 = 120.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        m3144 = 2;
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (m312A != 0) {
            m3144--;
            if (m3144 == 0) {
                setNpcAction(&::daNpc_Md_c::waitNpcAction);
            }
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00005308-00005534       .text shipNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::shipNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        onNpcNotChange();
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
        setAnm(0x23);
        speedF = 0.0f;
        m30F8 = 120.0f;
        if (dComIfGp_getShipActor() != NULL) {
            onShipRide();
        }
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus == ACTION_ENDING) {
        offShipRide();
    } else {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
        daShip_c* ship = dComIfGp_getShipActor();
        if (ship != NULL) {
            onShipRide();
            if (std::fabsf(ship->speedF) < 0.001f) {
                setAnm(0x2a);
                if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                    s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
                    m312C = chkAttention(current.pos, angle, 0);
                    s32 r0 = m312C;
                    if (r0 != 0) {
                        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
                        mCurEventMode = 2;
                    }
                }
            } else {
                setAnm(0x23);
            }
        }
        if (m3104 == 0x23) {
            mJntCtrl.lookAtTarget(&shape_angle.y, NULL, cXyz::Zero, shape_angle.y, 0, false);
        } else {
            lookBack(1, 0, 1);
        }
        current.angle.y = shape_angle.y;
        setAttention(true);
    }
    return TRUE;
}

/* 00005534-000057B0       .text mwaitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::mwaitNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        offNpcCallCommand();
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        setAnm(0x20);
        shape_angle.x = 0;
        shape_angle.z = 0;
        gravity = l_HIO.m0F4;
        maxFallSpeed = -100.0f;
        speedF = 0.0f;
        speed.y = 0.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (!isLightBodyHit()) {
                mActionStatus = ACTION_ONGOING_3;
            } else {
                cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
                f32 dVar3 = fopAcM_searchPlayerDistance2(this);
                if (!checkNpcCallCommand()) {
                    if (dVar3 < (l_HIO.m0C8 * l_HIO.m0C8)) {
                        daPy_getPlayerLinkActorClass()->onNpcCallCommand();
                    }
                } else {
                    mActionStatus++;
                    if (dVar3 < ((l_HIO.m0C4 * 2.0f) * (l_HIO.m0C4 * 2.0f))) {
                        mActionStatus++;
                    }
                }
            }
            if (mActionStatus != ACTION_ONGOING_1) {
                m311A = 0;
                m310C = 0.0f;
                m3114 = 0;
                m3116 = 0;
                setAnm(0x21);
                m312A = 0;
            }
        } else {
            if ((lookBackWaist(m311A, m310C)) && (m312A != 0)) {
                m3114 = 0;
                m3116 = 0;
                if (mActionStatus == ACTION_ONGOING_2) {
                    setNpcAction(&daNpc_Md_c::searchNpcAction);
                } else {
                    setAnm(0);
                    setNpcAction(&daNpc_Md_c::waitNpcAction);
                }
            }
        }
        setAttention(true);
    }
    return TRUE;
}

/* 000057B0-000058E0       .text squatdownNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::squatdownNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
        setAnm(3);
        speedF = 0.0f;
        m30F8 = 75.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
        m312C = chkAttention(current.pos, angle, 0);
        if (m312A != 0) {
            setNpcAction(&daNpc_Md_c::sqwait01NpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 000058E0-00005A74       .text sqwait01NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::sqwait01NpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        if (dComIfGs_isEventBit(dSv_event_flag_c::MEDLI_GAVE_FATHERS_LETTER)) {
            cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
        }
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
        setAnm(4);
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        speedF = 0.0f;
        m30F8 = 75.0f;
        shape_angle.x = 0;
        shape_angle.z = 0;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
        m312C = chkAttention(current.pos, angle, 0);
        if ((s8)mType >= 4) {
            setNpcAction(&daNpc_Md_c::waitNpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00005A74-00005AB0       .text changeCaught02__10daNpc_Md_cFv */
void daNpc_Md_c::changeCaught02() {
    setAnm(0x25);
    setBitStatus(daMdStts_UNK1);
}

/* 00005AB0-000061A8       .text carryNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::carryNpcAction(void*) {
    BOOL bVar1;
    u32 sfxID;
    f32 dVar9;

    if (mActionStatus == ACTION_STARTING) {
        onNpcNotChange();
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        offNpcCallCommand();
        m3144 = shape_angle.y - dComIfGp_getPlayer(0)->shape_angle.y;
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        if (isNoCarryAction()) {
            setAnm(0x24);
            setBitStatus(daMdStts_UNK1);
            setHane02Emitter();
            sfxID = JA_SE_CV_MD_CRASH;
        } else {
            if (m3104 == 4) {
                setAnm(5);
            } else {
                setAnm(3);
                m312A = 0;
            }
            sfxID = JA_SE_CV_MD_LIFT_UP;
        }
        fopAcM_monsSeStart(this, sfxID, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        m30F8 = 75.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus == ACTION_ENDING) {
        offNpcNotChange();
        m3298.y = 0.0f;
        m3298.z = 0.0f;
        offNoCarryAction();
        deleteHane02Emitter();
        deleteHane03Emitter();
        emitterDelete(m0508);
    } else {
        m3131 = 0;
        bVar1 = false;
        if (fopAcM_CheckStatus(this, fopAcStts_CARRY_e)) {
            setRestart(2);
        }
        if (!isNoCarryAction()) {
            int iVar3 = daPy_getPlayerLinkActorClass()->checkAutoJumpFlying();
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            if (mActionStatus == ACTION_ONGOING_1) {
                if (iVar3 > 0) {
                    mActionStatus = ACTION_ONGOING_2;
                    setAnm(9);
                    setBitStatus(daMdStts_UNK1);
                    setWingEmitter();
                    setHane03Emitter();
                    m312A = 0;
                    fopAcM_monsSeStart(this, JA_SE_CV_MD_FLY_WITH_LINK, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_4001)) {
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_4180);
                    }
                } else if (m3104 == 5) {
                    dVar9 = mpMorf->getPlaySpeed();
                    if ((player->speedF == 0.0f) && (player->getBaseAnimeFrame() <= mpMorf->getEndFrame())) {
                        mpMorf->setFrame(player->getBaseAnimeFrame());
                        mpMorf->setPlaySpeed(0.0f);
                        mpArmMorf->setFrame(player->getBaseAnimeFrame());
                        mpArmMorf->setPlaySpeed(0.0f);
                    } else {
                        mpMorf->setPlaySpeed(1.0f);
                        mpArmMorf->setPlaySpeed(1.0f);
                    }
                    if (dVar9 != mpMorf->getPlaySpeed()) {
                        mpMorf->setMorf(4.0f);
                        mpArmMorf->setMorf(4.0f);
                    }
                    cLib_chaseF(&m3298.x, l_HIO.m0F8, 1.0f);
                    cLib_chaseF(&m3298.y, l_HIO.m0FC, 1.0f);
                    cLib_chaseF(&m3298.z, l_HIO.m100, 1.0f);
                } else if (m312A != 0) {
                    setAnm(5);
                }
            } else if (mActionStatus == ACTION_ONGOING_2) {
                if (iVar3 < 0x1e) {
                    mActionStatus = ACTION_ONGOING_3;
                    mpMorf->setPlaySpeed(l_HIO.m120);
                    mpWingMorf->setPlaySpeed(l_HIO.m120);
                }
            } else if (iVar3 <= 0) {
                mActionStatus = ACTION_ONGOING_1;
                m3135 = m3135 | 1;
                deleteHane03Emitter();
                setAnm(5);
                clearStatus(daMdStts_UNK1);
                bVar1 = true;
                fopAcM_monsSeStart(this, JA_SE_CV_MD_FLY_END, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            }
        }
        if (!fopAcM_CheckStatus(this, fopAcStts_CARRY_e)) {
            if (isNoCarryAction()) {
                if (speedF > 0.0f) {
                    setNpcAction(&daNpc_Md_c::throwNpcAction);
                } else {
                    setNpcAction(&daNpc_Md_c::land03NpcAction);
                }
            } else if ((checkStatus(daMdStts_UNK1)) || (bVar1)) {
                f32 f1 = mAcch.GetGroundH();
                f32 f0 = current.pos.y;
                if (f0 - f1 >= l_HIO.m1AC) {
                    setNpcAction(&daNpc_Md_c::fall02NpcAction);
                } else {
                    setNpcAction(&daNpc_Md_c::fallNpcAction);
                }
            } else if (speedF > 0.0f) {
                setNpcAction(&daNpc_Md_c::throwNpcAction);
            } else {
                setNpcAction(&daNpc_Md_c::sqwait01NpcAction);
            }
        }
        mJntCtrl.lookAtTarget(&shape_angle.y, NULL, cXyz::Zero, shape_angle.y, m3110, false);
        current.angle.y = shape_angle.y;
    }
    return TRUE;
}

/* 000061A8-00006450       .text throwNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::throwNpcAction(void*) {
    f32 fVar1;
    s16 sVar3;

    if (mActionStatus == ACTION_STARTING) {
        fopAcM_monsSeStart(this, JA_SE_CV_MD_THROW, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        m314C = 1;
        m314E = l_HIO.m1B4;
        m3148 = 0;
        m3154 = 0.0f;
        speedF = l_HIO.m0E8;
        speed.y = l_HIO.m0EC;
        maxFallSpeed = l_HIO.m110;
        gravity = l_HIO.m114;
        m30A0 = current.pos;
        clearStatus(daMdStts_UNK4);
        setBitStatus(daMdStts_UNK1 | daMdStts_FLY);
        setAnm(6);
        setWingEmitter();
        mAcchCir[1].SetWall(60.0f, 60.0f);
        mActionStatus++;
    } else if (mActionStatus == ACTION_ENDING) {
        emitterDelete(m0508);
    } else {
        fVar1 = mpWingMorf->getFrame();
        if ((fVar1 == 23.0f) && (speed.y < l_HIO.m0F0)) {
            speed.y = l_HIO.m0F0;
        }
        if (fVar1 > l_HIO.m154) {
            sVar3 = windProc();
            if (sVar3 == 0) {
                m314C = sVar3;
            }
        }
        if (mAcch.ChkGroundHit()) {
            setNpcAction(&daNpc_Md_c::land01NpcAction);
            dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
        } else if (mAcch.ChkWallHit()) {
            setNpcAction(&daNpc_Md_c::wallHitNpcAction);
            dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
        } else if (m312A != 0) {
            setNpcAction(&daNpc_Md_c::glidingNpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00006450-00006764       .text glidingNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::glidingNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        if (m314C == 1) {
            m3148 = 0;
            setAnm(0xb);
        } else {
            m3148 = 1;
            setAnm(10);
        }
        m314A = 2;
        clearStatus(daMdStts_UNK4);
        setBitStatus(daMdStts_UNK1 | daMdStts_FLY);
        mAcchCir[1].SetWall(60.0f, 60.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (!chkAdanmaeDemoOrder()) {
            if (mAcch.ChkGroundHit()) {
                if (mType == 1) {
                    setNpcAction(&daNpc_Md_c::land01NpcAction, &m3144);
                } else {
                    setNpcAction(&daNpc_Md_c::land01NpcAction);
                }
                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
            } else if (mAcch.ChkWallHit()) {
                if (mType == 1) {
                    setNpcAction(&daNpc_Md_c::wallHitNpcAction, &m3144);
                } else {
                    setNpcAction(&daNpc_Md_c::wallHitNpcAction);
                }
                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
            } else {
                if (m3148 == 0) {
                    s16 sVar3 = windProc();
                    if (m314C != sVar3) {
                        if (sVar3 == 0) {
                            setAnm(10);
                            m3148 = 1;
                        } else {
                            setAnm(0xb);
                        }
                    }
                    m314C = sVar3;
                } else if (m312A != 0) {
                    m314A--;
                    if (m314A != 0) {
                        setAnm(10);
                    } else {
                        if (mType == 1) {
                            setNpcAction(&daNpc_Md_c::fall02NpcAction, &m3144);
                        } else {
                            setNpcAction(&daNpc_Md_c::fall02NpcAction);
                        }
                        return TRUE;
                    }
                }
                // Required to match.
                cXyz cStack_68(current.pos - m30A0);
            }
        }
        setAttention(true);
    }
    return TRUE;
}

static void unused_7570_7575_7612() {
    daNpc_Md_c md;
    md.setNpcAction(&daNpc_Md_c::land01NpcAction);
    md.setNpcAction(&daNpc_Md_c::wallHitNpcAction);
    md.setNpcAction(&daNpc_Md_c::fall02NpcAction);
}

/* 00006764-00006B24       .text windProc__10daNpc_Md_cFv */
s16 daNpc_Md_c::windProc() {
    /* Nonmatching */
    f32 fVar1;
    int iVar2;
    cCcD_Obj* pcVar3;
    s16 sVar4;
    s16 sVar5;
    f32 dVar6;
    f32 fVar7;
    f32 local_a4;
    cXyz local_34;
    cXyz cStack_64;
    cXyz cStack_70;
    cXyz local_88;
    cXyz local_94;

    sVar5 = 1;
    if (checkStatus(daMdStts_UNK8)) {
        dKyw_get_AllWind_vec(&current.pos, &local_34, &local_a4);
    } else {
        local_34.x = 0.0f;
        local_34.y = 0.0f;
        local_34.z = 0.0f;
        local_a4 = 0.0f;
    }
    if ((l_HIO.m1C6 != 0) && (mCyl2.ChkTgHit())) {
        pcVar3 = mCyl2.GetTgHitObj();
        if ((pcVar3 != NULL) && (pcVar3->ChkAtType(AT_TYPE_WIND))) {
            local_34 = *mCyl2.GetTgRVecP();
            cStack_64.normalizeZP();
            local_a4 = l_HIO.m148;
        }
    }
    cStack_64.x = local_34.x;
    cStack_64.y = 0.0f;
    cStack_64.z = local_34.z;
    cStack_70.set(cM_ssin(shape_angle.y), 0.0f, cM_scos(shape_angle.y));
    dVar6 = l_HIO.m134;
    local_88.set(cStack_70.x, 0.0f, cStack_70.z);
    fVar7 = local_94.abs2();
    if (!(std::fabsf(fVar7) < G_CM3D_F_ABS_MIN)) {
        cStack_70.normalizeZP();
        if (!(cStack_70.x * local_94.x + cStack_70.z * local_94.z > 0.7071f)) {
            sVar5 = 0;
            dVar6 = l_HIO.m130;
        }
    }
    if (sVar5 == 0) {
        fVar1 = (local_a4 * dVar6);
        m3154 += l_HIO.m138;
        if (m3154 > fVar1) {
            m3154 = fVar1;
        }
        local_a4 = m3154;
    } else {
        local_a4 = (local_a4 * dVar6);
    }
    local_88 = speed + (local_34 * local_a4);
    iVar2 = cM_atan2s(local_88.x, local_88.z);
    current.angle.y = (s16)iVar2;
    fVar7 = local_88.absXZ();
    speedF = fVar7;
    f32 var_f1_2 = l_HIO.m13C;
    f32 temp_f0_4 = speedF;
    if (temp_f0_4 > var_f1_2) {
        var_f1_2 = fVar7;
    } else {
        var_f1_2 = temp_f0_4;
    }
    speedF = var_f1_2;
    speed.y = local_88.y;
    if (m3148 == 0) {
        maxFallSpeed = l_HIO.m110;
        gravity = l_HIO.m114;
    }
    if (!(std::fabsf(local_a4) < G_CM3D_F_ABS_MIN)) {
        sVar4 = cLib_calcTimer(&m314E);
        s16 sVar6 = l_HIO.m1B4 - l_HIO.m1B6;
        if ((sVar5 == 1) && (sVar4 > 0) && (sVar4 < sVar6) && (l_HIO.m1C7 != 0 || (m3148 == 0))) {
            maxFallSpeed = l_HIO.m140;
            gravity = l_HIO.m144;
        }
    }
    return sVar5;
}

/* 00006B24-00006C80       .text fallNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::fallNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK4);
        setBitStatus(daMdStts_FLY);
        setAnm(0xc);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (mAcch.ChkGroundHit()) {
            setNpcAction(&daNpc_Md_c::land01NpcAction);
            dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
        } else if (mAcch.ChkWallHit()) {
            setNpcAction(&daNpc_Md_c::wallHitNpcAction);
            dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00006C80-00006F70       .text fall02NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::fall02NpcAction(void* param_1) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK4);
        setBitStatus(daMdStts_FLY);
        maxFallSpeed = l_HIO.m110;
        gravity = l_HIO.m114;
        m30F8 = 120.0f;
        setAnm(0xd);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
        if (param_1 != NULL) {
            m3144 = 1;
        } else {
            m3144 = 0;
        }
        m3150 = current.pos.y;
    } else if (mActionStatus != ACTION_ENDING) {
        if ((mType == 5) && (mAcch.ChkGroundHit())) {
            if (m3150 - current.pos.y >= l_HIO.m1B0) {
                dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
        }
        if (m3144 != 0) {
            if (!chkAdanmaeDemoOrder()) {
                if (mAcch.ChkGroundHit()) {
                    setNpcAction(&daNpc_Md_c::land03NpcAction);
                    dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
                } else if (mAcch.ChkWallHit()) {
                    setNpcAction(&daNpc_Md_c::wallHitNpcAction);
                    dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
                }
            }
        } else {
            if (mAcch.ChkGroundHit()) {
                setNpcAction(&daNpc_Md_c::land03NpcAction);
                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
            } else if (mAcch.ChkWallHit()) {
                setNpcAction(&daNpc_Md_c::wallHitNpcAction);
                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
            }
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00006F70-000071E4       .text wallHitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::wallHitNpcAction(void* param_1) {
    int iVar1;

    if (mActionStatus == ACTION_STARTING) {
        fopAcM_monsSeStart(this, JA_SE_CV_MD_CRASH, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        setAnm(0xd);
        shape_angle.x = 0;
        shape_angle.z = 0;
        iVar1 = wallHitCheck();
        if (iVar1 >= 0) {
            current.angle.y = mAcchCir[iVar1].GetWallAngleY();
        }
        speedF = l_HIO.m150;
        clearStatus(daMdStts_UNK1 | daMdStts_UNK4);
        setBitStatus(daMdStts_UNK2 | daMdStts_FLY);
        m30F8 = 120.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
        dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
        if (param_1 != NULL) {
            m3144 = 1;
        } else {
            m3144 = 0;
        }
    } else if (mActionStatus != ACTION_ENDING) {
        if (m3144 != 0) {
            if ((!chkAdanmaeDemoOrder()) && (mAcch.ChkGroundHit())) {
                setNpcAction(&daNpc_Md_c::land02NpcAction);
                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
            }
        } else if (mAcch.ChkGroundHit()) {
            setNpcAction(&daNpc_Md_c::land02NpcAction);
            dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
        }
        setAttention(true);
    }
    return TRUE;
}

/* 000071E4-000073BC       .text land01NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::land01NpcAction(void* param_1) {
    if (mActionStatus == ACTION_STARTING) {
        fopAcM_monsSeStart(this, JA_SE_CV_MD_LANDING, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        if (checkStatus(daMdStts_UNK1)) {
            m3135 = m3135 | 1;
        }
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        setAnm(0xe);
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        shape_angle.x = 0;
        shape_angle.z = 0;
        speedF = 0.0f;
        m30F8 = 120.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
        if (param_1 != NULL) {
            m3144 = 1;
        } else {
            m3144 = 0;
        }
    } else if (mActionStatus != ACTION_ENDING) {
        if (m3144 != 0) {
            if ((!chkAdanmaeDemoOrder()) && (m312A != 0)) {
                setNpcAction(&daNpc_Md_c::waitNpcAction);
            }
        } else if (m312A != 0) {
            setNpcAction(&daNpc_Md_c::waitNpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 000073BC-000074C0       .text land02NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::land02NpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        setAnm(0xf);
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        shape_angle.x = 0;
        shape_angle.z = 0;
        speedF = 0.0f;
        m30F8 = 120.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (m312A != 0) {
            setNpcAction(&daNpc_Md_c::piyo2NpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 000074C0-000075C4       .text land03NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::land03NpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        setAnm(0xf);
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        shape_angle.x = 0;
        shape_angle.z = 0;
        speedF = 0.0f;
        m30F8 = 120.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (m312A != 0) {
            setNpcAction(&daNpc_Md_c::waitNpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

static void unused_7903() {
    daNpc_Md_c md;
    md.setNpcAction(&daNpc_Md_c::piyo2NpcAction);
}

/* 000075C4-00007824       .text piyo2NpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::piyo2NpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        setAnm(0x14);
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        shape_angle.x = 0;
        shape_angle.z = 0;
        speedF = 0.0f;
        m30F8 = 120.0f;
        m3144 = l_HIO.m1BA;
        if ((mType == 4) || (mType == 5)) {
            m3144 = m3144 >> 1;
        }
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        fopAcM_seStart(this, JA_SE_CM_MD_PIYO, 0);
        s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
        if (cLib_calcTimer(&m3144) == 0) {
            setNpcAction(&daNpc_Md_c::waitNpcAction);
        }
        m312C = chkAttention(current.pos, angle, 0);
        int local_28 = m312C;
        if (local_28 != 0) {
            if ((((mType == 0) || (mType == 1)) || (mType == 2)) || (mType == 3)) {
                cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
            } else {
                cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
            }
            if (mType == 1) {
                mCurEventMode = 2;
            }
        }
        NpcCall(&local_28);
        lookBack(1, 1, 0);
        current.angle.y = shape_angle.y;
        setAttention(true);
    }
    return TRUE;
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
    cXyz local_1c;

    if (mActionStatus == ACTION_STARTING) {
        attention_info.flags = 0;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
        current.angle.y = 0x5700;
    } else if (mActionStatus == ACTION_ENDING) {
        emitterDelete(m0508);
    } else {
        attention_info.flags = 0;
        if (mActionStatus == ACTION_ONGOING_1) {
            if (mJntCtrl.mbTrn != false) {
                cLib_addCalcAngleS2(&m3110, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
            } else {
                m3110 = 0;
                setAnm(0x18);
                mActionStatus++;
            }
            local_1c.x = -1511.0f;
            local_1c.y = 14500.0f;
            local_1c.z = 150.0f;
            mJntCtrl.lookAtTarget(&shape_angle.y, &local_1c, current.pos, current.angle.y, m3110, false);
        } else if (mActionStatus == ACTION_ONGOING_2) {
            if (m312A != 0) {
                setAnm(0x19);
                setBitStatus(daMdStts_UNK1);
                setWingEmitter();
                speed.y = 0.0f;
                gravity = 1.0f;
                maxFallSpeed = 100.0f;
                mActionStatus++;
            }
        } else if (mActionStatus == ACTION_ONGOING_3) {
            if (m312A != 0) {
                setAnm(10);
            }
            if (current.pos.y > 14500.0f) {
                setAnm(0xb);
                speed.y = 0.0f;
                gravity = 0.0f;
                maxFallSpeed = 0.0f;
                speedF = 17.0f;
                m3144 = 0x3c;
                mActionStatus++;
            }
        } else if ((mActionStatus == 4) && (cLib_calcTimer(&m3144) == 0)) {
            fopAcM_delete(this);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00007A98-00007B64       .text routeAngCheck__10daNpc_Md_cFR4cXyzPs */
void daNpc_Md_c::routeAngCheck(cXyz& param_1, s16* param_2) {
    cXyz temp = m32A4.outprod(param_1);
    s16 angle = cM_atan2s(temp.x, temp.z);
    if ((m32A4.y >= 1.0f && cLib_distanceAngleS(angle, *param_2) > 0x4000) || fopAcM_searchPlayerDistanceY(this) * temp.y < 0.0f) {
        angle += 0x8000;
    }
    *param_2 = angle;
}

/* 00007B64-00007DC8       .text routeWallCheck__10daNpc_Md_cFR4cXyzR4cXyzPs */
void daNpc_Md_c::routeWallCheck(cXyz& param_1, cXyz& param_2, s16* param_3) {
    dBgS_LinChk lin_chk;
    lin_chk.Set(&param_1, &param_2, NULL);
    if (dComIfG_Bgsp()->LineCross(&lin_chk)) {
        cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(lin_chk);
        if (pla) {
            routeAngCheck(pla->mNormal, param_3);
        }
    }
}

/* 00007DC8-00008054       .text checkForwardGroundY__10daNpc_Md_cFs */
f32 daNpc_Md_c::checkForwardGroundY(s16 param_1) {
    if (mAcchCir[0].ChkWallHit()) {
        cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(mAcchCir[0]);
        if (pla && cLib_distanceAngleS(param_1, cM_atan2s(pla->mNormal.x, pla->mNormal.z)) > 0x4000) {
            dBgS_GndChk gnd_chk;
            gnd_chk.OffWall();
            cXyz pos(current.pos.x + cM_ssin(param_1) * 80.0f, current.pos.y + 80.0f, current.pos.z + cM_scos(param_1) * 80.0f);
            gnd_chk.SetPos(&pos);
            return dComIfG_Bgsp()->GroundCross(&gnd_chk);
        }
    }
    return -10000000.0f;
}

/* 000081EC-000082C0       .text checkWallJump__10daNpc_Md_cFs */
f32 daNpc_Md_c::checkWallJump(s16 param_1) {
    f32 temp = checkForwardGroundY(param_1) - current.pos.y;
    if (0.0f < temp && temp < 80.0f) {
        return std::sqrtf(temp) * 3.6f;
    }
    return -1.0f;
}

/* 000082C0-00008858       .text routeCheck__10daNpc_Md_cFfPs */
BOOL daNpc_Md_c::routeCheck(f32 param_1, s16* param_2) {
    f32 temp2;
    if (!mAcch.ChkGroundHit()) {
        cXyz temp = current.pos;
        current.pos = old.pos;
        speedF = 0.0f;
        m3131 = 1;
        dBgS_LinChk lin_chk;
        lin_chk.Set(&temp, &current.pos, NULL);
        if (dComIfG_Bgsp()->LineCross(&lin_chk)) {
            cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(lin_chk);
            if (pla && cLib_distanceAngleS(*param_2, cM_atan2s(pla->mNormal.x, pla->mNormal.z)) > 0x4000) {
                return TRUE;
            }
        }
        if (mAcch.GetGroundH() - temp.y < -100.0f) {
            return FALSE;
        }
        temp2 = 20.0f;
        setNpcAction(&daNpc_Md_c::jumpNpcAction, &temp2);
    } else {
        if (mAcch.ChkWallHit()) {
            temp2 = checkWallJump(*param_2);
            if (temp2 >= 0.0f) {
                setNpcAction(&daNpc_Md_c::jumpNpcAction, &temp2);
                return TRUE;
            }
            if (param_1 > SQUARE(600.0f)) {
                return FALSE;
            }
        }
        cXyz temp(current.pos.x, current.pos.y + 80.0f, current.pos.z);
        cXyz temp2(cM_ssin(*param_2) * 80.0f + current.pos.x, current.pos.y + 80.0f, cM_scos(*param_2) * 80.0f + current.pos.z);
        routeWallCheck(temp, temp2, param_2);
    }

    return TRUE;
}

/* 00008858-00008CEC       .text searchNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::searchNpcAction(void*) {
    f32 fVar2;
    cXyz* dstPos = NULL;
    cXyz vec2;
    cXyz vec;

    if (mActionStatus == ACTION_STARTING) {
        setBitStatus(daMdStts_UNK4);
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        if (((m3104 == 0x11) || (m3104 == 0x16)) || (m3104 == 0x17)) {
            setAnm(0x13);
            mActionStatus++;
        } else if (m3104 == 0x20) {
            setAnm(0x21);
            m312A = 0;
            mActionStatus++;
        } else {
            setAnm(2);
            mActionStatus += 2;
        }
        if (!mAcch.ChkGroundHit()) {
            f32 gndY = mAcch.GetGroundH();
            f32 delta = gndY - current.pos.y;
            if (delta < 0.0f && delta >= -30.1f) {
                current.pos.y = gndY;
                mAcch.SetGroundHit();
                speed.y = 0.0f;
            }
        }
    } else if (mActionStatus != ACTION_ENDING) {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (m312A != 0) {
                setAnm(2);
                mActionStatus++;
            }
        } else {
            m312C = 1;
            daPy_py_c* player = daPy_getPlayerActorClass();
            BOOL door = player->eventInfo.checkCommandDoor();
            f32 dist_sq = fopAcM_searchPlayerDistanceXZ2(this);
            f32 temp;
            if (dist_sq < SQUARE(l_HIO.m0C4)) {
                temp = 0.0f;
            } else {
                fVar2 = dist_sq - SQUARE(l_HIO.m0C4);
                if (fVar2 > 90000.0f) {
                    fVar2 = 90000.0f;
                }
                temp = (fVar2 / 90000.0f);
                if (temp < 0.5f) {
                    temp = 0.5f;
                }
            }
            s16 angle, adjustedAngle;
            angle = adjustedAngle = fopAcM_searchPlayerAngleY(this);
            BOOL temp3 = routeCheck(dist_sq, &adjustedAngle) && cLib_distanceAngleS(angle, adjustedAngle) <= 0x2000;
            if (door || !temp3 ||
                (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000000_e | daPyStts0_UNK100_e | daPyStts0_UNK1_e) || player->checkAttentionLock()))
            {
                temp = 0.0f;
                offNpcCallCommand();
                fopAcM_monsSeStart(this, JA_SE_CV_MD_LEFT_ALONE, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                if (!temp3) {
                    setNpcAction(&daNpc_Md_c::kyohiNpcAction);
                    return TRUE;
                }
            } else {
                setRestart(2);
                if (!door) {
                    if (cLib_calcTimer(&m3130) == 0) {
                        m312F ^= 1;
                        m3130 = cLib_getRndValue(8, 20);
                    }
                }
            }
            walkProc(temp, adjustedAngle);
            cLib_addCalcAngleS(&shape_angle.y, current.angle.y, l_HIO.m008.m24, l_HIO.m008.m20 * 2, l_HIO.m008.m22 * 2);
            s16 temp4 = shape_angle.y;
            vec2 = dNpc_playerEyePos(l_HIO.mNpc.m04);
            dstPos = &vec2;
            vec = current.pos;
            vec.y = eyePos.y;
            mJntCtrl.lookAtTarget(&temp4, dstPos, vec, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);
            if (speedF < 0.001f) {
                setNpcAction(&daNpc_Md_c::waitNpcAction);
            } else {
                shape_angle.y = temp4;
            }
            lookBack(1, 0, 0);
            setAttention(true);
        }
    }
    return TRUE;
}

/* 00008CEC-00008E54       .text hitNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::hitNpcAction(void* r29) {
    if (mActionStatus == ACTION_STARTING) {
        setDamageFogTimer(5 * 30);
#if VERSION > VERSION_DEMO
        //! @bug: Reverb is being passed to JAIZelBasic::monsSeStart as argument r7 when it should be argument r8.
        //! The fopAcM_monsSeStart inline does not support passing reverb, but the programmer didn't realize this.
        fopAcM_monsSeStart(this, JA_SE_CV_MD_CRASH, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
#endif
        s16 angle = 0;
        if (r29 != NULL) {
            angle = *(s16*)r29;
        }
        current.angle.y = angle;
        speedF = 10.0f;
        speed.y = 20.0f;
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        clearStatus(daMdStts_UNK1 | daMdStts_UNK4);
        setBitStatus(daMdStts_UNK2);
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
void daNpc_Md_c::setNormalSpeedF(f32 f1, f32 f2, f32 i_scale, f32 i_maxStep, f32 i_minStep) {
    f32 f31 = mMaxNormalSpeed * f1;
    int r3 = wallHitCheck();
    if (r3 >= 0) {
        s16 angle = current.angle.y + 0x8000 - mAcchCir[r3].GetWallAngleY();
        if (abs(angle) < 0x4000) {
            f31 *= (1.0f - l_HIO.m008.m1C * cM_scos(angle));
        }
    }
    f32 targetSpeed;
    f32 maxStep;
    if (f31 < m3108) {
        f32 temp2 = m3108 - f31;
        if (temp2 > i_maxStep) {
            maxStep = i_maxStep;
        } else {
            maxStep = temp2;
        }
        if (maxStep < i_minStep) {
            maxStep = i_minStep;
        }
        f2 = 0.0f;
        targetSpeed = f31;
    } else {
        maxStep = i_maxStep;
        targetSpeed = 0.0f;
    }
    if (!cM3d_IsZero(f2)) {
        m3108 += f2;
        if (m3108 > f31) {
            m3108 = f31;
        }
    } else {
        cLib_addCalc(&m3108, targetSpeed, i_scale, maxStep, i_minStep);
    }
}

/* 00008FFC-000090EC       .text setSpeedAndAngleNormal__10daNpc_Md_cFfs */
void daNpc_Md_c::setSpeedAndAngleNormal(f32 f1, s16 r4) {
    f32 f2;
    if (f1 > 0.05f) {
        cLib_addCalcAngleS(&current.angle.y, r4, l_HIO.m008.m24, l_HIO.m008.m20, l_HIO.m008.m22);
        f32 temp = cM_scos(r4 - current.angle.y);
        if (temp < 0.0f) {
            temp = 0.0f;
        }
        f2 = l_HIO.m008.m04 * f1 * temp;
    } else {
        f2 = 0.0f;
    }
    setNormalSpeedF(f1, f2, l_HIO.m008.m14, l_HIO.m008.m0C, l_HIO.m008.m10);
}

/* 000090EC-00009180       .text walkProc__10daNpc_Md_cFfs */
void daNpc_Md_c::walkProc(f32 f1, s16 r3) {
    mMaxNormalSpeed = l_HIO.m008.m08;
    setSpeedAndAngleNormal(f1, r3);
    f32 temp = std::fabsf(m3108 / mMaxNormalSpeed);
    f32 temp2 = temp * l_HIO.m008.m18;
    mpMorf->setPlaySpeed(temp2);
    mpArmMorf->setPlaySpeed(temp2);
    setRunRate(temp);
    speedF = m3108;
}

/* 00009180-000092E0       .text jumpNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::jumpNpcAction(void* param_1) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
        if (param_1 != NULL) {
            speed.y = *(f32*)param_1;
        }
        shape_angle.x = 0;
        shape_angle.z = 0;
        speedF = 4.0f;
        gravity = l_HIO.m0F4;
        maxFallSpeed = -100.0f;
        setAnm(0xc);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (mAcch.ChkGroundHit()) {
                speedF = 0.0f;
                setAnm(0xe);
                m312A = 0;
                mActionStatus++;
            }
        } else if (m312A != 0) {
            speedF = 0.0f;
            setNpcAction(&daNpc_Md_c::waitNpcAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 000092E0-000095C8       .text escapeNpcAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::escapeNpcAction(void*) {
    /* Nonmatching */
    int sVar5;
    s16 local_38;

    if (mActionStatus == ACTION_STARTING) {
        setBitStatus(daMdStts_UNK4);
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        if (((m3104 == 0x11) || (m3104 == 0x16)) || (m3104 == 0x17)) {
            setAnm(0x13);
            mActionStatus++;
        } else if (m3104 == 0x20) {
            setAnm(0x21);
            m312A = 0;
            mActionStatus++;
        } else {
            setAnm(2);
            mActionStatus += 2;
        }
        if (!mAcch.ChkGroundHit()) {
            f32 gndY = mAcch.GetGroundH();
            f32 delta = gndY - current.pos.y;
            if (delta < 0.0f && delta >= -30.1f) {
                current.pos.y = gndY;
                mAcch.SetGroundHit();
                speed.y = 0.0f;
            }
        }
        m3144 = 0;
        m3146 = 0x1e;
    } else if (mActionStatus != ACTION_ENDING) {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (m312A != 0) {
                setAnm(2);
                mActionStatus++;
            }
        } else {
            m312C = 1;
            cLib_calcTimer(&m3146);
            if (m313F != 0) {
                sVar5 = (m313F < 0) ? -0x4000 : 0x4000;
                m3144 = (s16)sVar5 + cM_atan2s(m30C4.x, m30C4.z);
            } else if (m3146 == 0) {
                setNpcAction(&daNpc_Md_c::waitNpcAction);
                return TRUE;
            }
            local_38 = sVar5 = m3144;
            if (routeCheck(250000.0f, &local_38)) {
                cLib_distanceAngleS(sVar5, local_38);
            }
            walkProc(1.0f, local_38);
            cLib_addCalcAngleS(&shape_angle.y, current.angle.y, l_HIO.m008.m24, l_HIO.m008.m20 * 2, l_HIO.m008.m22 * 2);
            s16 temp4 = shape_angle.y;
            if (speedF < 0.001f) {
                setNpcAction(&daNpc_Md_c::waitNpcAction);
            } else {
                shape_angle.y = temp4;
            }
            lookBack(0, 0, 0);
            setAttention(true);
        }
    }
    return TRUE;
}

/* 000095C8-00009894       .text waitPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::waitPlayerAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
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
#if VERSION == VERSION_DEMO
            cLib_addCalcAngleS(&current.angle.y, stickAngle, 8, 0x2000, 0x400);
#else
            cLib_addCalcAngleS(&current.angle.y, stickAngle, l_HIO.m008.m26, l_HIO.m008.m28, l_HIO.m008.m2A);
#endif
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
#if VERSION > VERSION_DEMO
            current.angle.y = shape_angle.y;
#endif
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
    int iVar1;
    s16 sVar3;
    f32 dVar4;
    f32 local_64;
    cXyz cStack_30;

    if (mActionStatus == ACTION_STARTING) {
        setBitStatus(daMdStts_UNK4);
        setAnm(2);
        mMaxNormalSpeed = l_HIO.m008.m08;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if ((mActionStatus != ACTION_ENDING) && (!flyCheck())) {
        dVar4 = g_mDoCPd_cpadInfo[0].mMainStickValue;
        sVar3 = getStickAngY(0);
        walkProc(dVar4, sVar3);
        iVar1 = calcStickPos(sVar3, &cStack_30);
        if (iVar1 == 0) {
            cLib_addCalcAngleS(&shape_angle.y, current.angle.y, l_HIO.m008.m24, l_HIO.m008.m20 * 2, l_HIO.m008.m22 * 2);
        }
        s16 tempAngle = shape_angle.y;
        mJntCtrl.lookAtTarget(&tempAngle, &cStack_30, current.pos, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);
        if (iVar1 > 0) {
            shape_angle.y = tempAngle;
        }
        if ((speedF < 0.001f) || (iVar1 != 0)) {
            setPlayerAction(&daNpc_Md_c::waitPlayerAction);
        } else if (!mAcch.ChkGroundHit()) {
            local_64 = 10.0f;
            setPlayerAction(&daNpc_Md_c::jumpPlayerAction, &local_64);
        } else if (mAcch.ChkWallHit()) {
            local_64 = checkWallJump(current.angle.y);
            if (local_64 >= 0.0f) {
                setPlayerAction(&daNpc_Md_c::jumpPlayerAction, &local_64);
                return TRUE;
            }
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00009B08-00009CCC       .text hitPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::hitPlayerAction(void* param_1) {
    s16 sVar2;

    if (mActionStatus == ACTION_STARTING) {
        dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        setDamageFogTimer(5 * 30);
        fopAcM_monsSeStart(this, JA_SE_CV_MD_CRASH, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        sVar2 = 0;
        if (param_1 != NULL) {
            sVar2 = *(s16*)param_1;
        }
        current.angle.y = sVar2;
        speedF = 10.0f;
        speed.y = 20.0f;
        maxFallSpeed = -100.0f;
        gravity = l_HIO.m0F4;
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        clearStatus(daMdStts_UNK1 | daMdStts_UNK4);
        setBitStatus(daMdStts_UNK2);
        m30F8 = 120.0f;
        setAnm(0xd);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (mAcch.ChkGroundHit()) {
                speedF = 0.0f;
                setAnm(0xf);
                m312A = 0;
                mActionStatus++;
            }
        } else if (m312A != 0) {
            returnLink();
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00009CCC-00009E7C       .text jumpPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::jumpPlayerAction(void* param_1) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        setBitStatus(daMdStts_UNK4);
        if (param_1 != NULL) {
            speed.y = *(f32*)param_1;
        }
        shape_angle.x = 0;
        shape_angle.z = 0;
        gravity = l_HIO.m0F4;
        maxFallSpeed = -100.0f;
        setAnm(0xc);
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
        m3150 = current.pos.y;
    } else if (mActionStatus != ACTION_ENDING) {
        if (mActionStatus == ACTION_ONGOING_1) {
            if (mAcch.ChkGroundHit()) {
                if (m3150 - current.pos.y >= l_HIO.m1B0) {
                    dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                }
                speedF = 0.0f;
                setAnm(0xe);
                m312A = 0;
                mActionStatus++;
            }
        } else if (m312A != 0) {
            setPlayerAction(&daNpc_Md_c::waitPlayerAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 00009E7C-0000A534       .text flyPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::flyPlayerAction(void*) {
    s16 sVar2;
    int iVar3;
    f32 dVar8;
    f32 dVar7;
    cXyz cStack_44;

    if (mActionStatus == ACTION_STARTING) {
        setAnm(0x18);
        m3150 = current.pos.y + 1500.0f;
        m3144 = l_HIO.m1BE;
        m3146 = l_HIO.m1C0;
        m_flyingTimer = getMaxFlyingTimer();
        speedF = 0.0f;
        mAcchCir[1].SetWall(60.0f, 60.0f);
        m_flying = true;
        mActionStatus++;
    } else if (mActionStatus == ACTION_ENDING) {
        emitterDelete(m0508);
        deleteHane03Emitter();
        m_flying = false;
    } else {
        if (CPad_CHECK_TRIG_A(0)) {
            m3146 = l_HIO.m1C0;
        } else {
            cLib_calcTimer(&m3146);
        }
        if (CPad_CHECK_TRIG_A(0)) {
            m3144 = l_HIO.m1BE;
        } else {
            cLib_calcTimer(&m3144);
        }
        if (mActionStatus == ACTION_ONGOING_1) {
            if (m312A != 0) {
                setBitStatus(daMdStts_UNK1);
                setWingEmitter();
                setAnm(0x19);
                speedF = 0.0f;
                speed.y = 20.0f;
                gravity = l_HIO.m188;
                maxFallSpeed = l_HIO.m18C;
                m3144 = l_HIO.m1BE;
                m3146 = l_HIO.m1C0;
                mActionStatus++;
            }
        } else {
            cLib_calcTimer(&m_flyingTimer);
            iVar3 = dComIfGs_isEventBit(dSv_event_flag_c::UNK_3320);
            if ((iVar3 != 0) && (m_flyingTimer < 300)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3310);
            }
            if (((m_flyingTimer == 0) || (m3144 == 0)) || (CPad_CHECK_TRIG_B(0))) {
                if (checkStatus(daMdStts_UNK1)) {
                    m3135 = m3135 | 1;
                }
                setPlayerAction(&daNpc_Md_c::jumpPlayerAction);
                if (m_flyingTimer == 0) {
                    fopAcM_monsSeStart(this, JA_SE_CV_MD_FLY_END, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                }
                return TRUE;
            }
            if ((m3104 != 0x2e) && (m312A != 0)) {
                setAnm(7);
            }
            if ((m_flyingTimer < l_HIO.m1C4) && (m3104 == 7)) {
                setAnm(0x2e);
                setHane03Emitter();
            }
            dAttention_c& attention = dComIfGp_getAttention();
            if ((g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.m104) || attention.Lockon()) {
                dVar8 = (g_mDoCPd_cpadInfo[0].mMainStickValue * l_HIO.m10C);
                if ((0.0f < dVar8) && (dVar8 < l_HIO.m0D8)) {
                    dVar8 = l_HIO.m0D8;
                }
                sVar2 = getStickAngY(0);
                cLib_distanceAngleS(sVar2, current.angle.y);
                dVar7 = l_HIO.m0DC;
                if (g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.m104) {
                    cLib_addCalcAngleS(&current.angle.y, sVar2, 8, 0x2000, 0x400);
                }
                iVar3 = calcStickPos(sVar2, &cStack_44);
                if (iVar3 == 0) {
                    cLib_addCalcAngleS(&shape_angle.y, current.angle.y, 8, 0x2000, 0x400);
                }
                s16 tempAngle = shape_angle.y;
                mJntCtrl.lookAtTarget(&tempAngle, &cStack_44, current.pos, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);
                if (iVar3 > 0) {
                    shape_angle.y = tempAngle;
                } else {
                    if (g_mDoCPd_cpadInfo[0].mMainStickValue < l_HIO.m104) {
                        cLib_addCalcAngleS(&current.angle.y, shape_angle.y, 8, 0x2000, 0x400);
                    }
                }
                f32 temp = dVar8;
                if (temp > l_HIO.m0D4) {
                    dVar8 = l_HIO.m0D4;
                } else {
                    dVar8 = temp;
                }
                cLib_chaseF(&speedF, dVar8, dVar7);
            } else {
                mJntCtrl.lookAtTarget(&shape_angle.y, NULL, cXyz::Zero, shape_angle.y, 0, false);
                current.angle.y = shape_angle.y;
            }
            gravity = l_HIO.m188;
            if (m3146 != 0) {
                maxFallSpeed = 10.0f;
            } else {
                maxFallSpeed = l_HIO.m18C;
            }
            if (current.pos.y >= m3150) {
                current.pos.y = m3150;
            }
            if (mAcch.ChkGroundHit()) {
                m_flyingTimer = 0;
                setPlayerAction(&daNpc_Md_c::landPlayerAction);
            }
        }
        if (!checkStatus(daMdStts_UNK2)) {
            if (checkStatus(daMdStts_UNK1)) {
                sVar2 = shape_angle.y - current.angle.y;
                if ((sVar2 < 0x6000) && (sVar2 > -0x6000)) {
                    if (sVar2 > 0x2000) {
                        sVar2 = 0x2000;
                    } else if (sVar2 < -0x2000) {
                        sVar2 = -0x2000;
                    }
                    cLib_addCalcAngleS(&shape_angle.z, sVar2, 8, 0x2000, 0x400);
                    cLib_addCalcAngleS(&shape_angle.x, 0, 8, 0x2000, 0x400);
                } else {
                    cLib_addCalcAngleS(&shape_angle.z, 0, 8, 0x2000, 0x400);
                    cLib_addCalcAngleS(&shape_angle.x, -0x2000, 8, 0x2000, 0x400);
                }
            } else {
                current.angle.y = shape_angle.y;
                shape_angle.x = 0;
                shape_angle.z = 0;
            }
        }
        setAttention(true);
    }
    return TRUE;
}

/* 0000A534-0000A698       .text landPlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::landPlayerAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        fopAcM_monsSeStart(this, JA_SE_CV_MD_LANDING, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        if (checkStatus(daMdStts_UNK1)) {
            m3135 = m3135 | 1;
        }
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        setAnm(0xe);
        shape_angle.x = 0;
        shape_angle.z = 0;
        gravity = l_HIO.m0F4;
        maxFallSpeed = -100.0f;
        speedF = 0.0f;
        speed.y = 0.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        if (m312A != 0) {
            speedF = 0.0f;
            setPlayerAction(&daNpc_Md_c::waitPlayerAction);
        }
        setAttention(true);
    }
    return TRUE;
}

/* 0000A698-0000A8D0       .text mkamaePlayerAction__10daNpc_Md_cFPv */
BOOL daNpc_Md_c::mkamaePlayerAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
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
    if (mActionStatus == ACTION_STARTING) {
        clearStatus(daMdStts_UNK2 | daMdStts_UNK4 | daMdStts_FLY);
        setAnm(0x24);
        setBitStatus(daMdStts_UNK1);
        setHane02Emitter();
        fopAcM_monsSeStart(this, JA_SE_CV_MD_LIFT_UP, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        m30F8 = 75.0f;
        mAcchCir[1].SetWall(60.0f, 20.0f);
        mActionStatus++;
    } else if (mActionStatus == ACTION_ENDING) {
        deleteHane02Emitter();
    }
    return TRUE;
}

static daNpc_Md_c::EventActionInitFunc event_init_tbl[] = {
    &daNpc_Md_c::initialWaitEvent,    &daNpc_Md_c::initialLetterEvent,  &daNpc_Md_c::initialMsgSetEvent,  &daNpc_Md_c::initialDefault,
    &daNpc_Md_c::initialMovePosEvent, &daNpc_Md_c::initialFlyEvent,     &daNpc_Md_c::initialGlidingEvent, &daNpc_Md_c::initialLandingEvent,
    &daNpc_Md_c::initialWalkEvent,    &daNpc_Md_c::initialWalkEvent,    &daNpc_Md_c::initialEndEvent,     &daNpc_Md_c::initialDefault,
    &daNpc_Md_c::initialTakeOffEvent, &daNpc_Md_c::initialOnetimeEvent, &daNpc_Md_c::initialQuake,        &daNpc_Md_c::initialHarpPlayEvent,
    &daNpc_Md_c::initialOffLinkEvent, &daNpc_Md_c::initialOnLinkEvent,  &daNpc_Md_c::initialTurnEvent,    &daNpc_Md_c::initialSetAnmEvent,
    &daNpc_Md_c::initialLookDown,     &daNpc_Md_c::initialLookUp,
};

static daNpc_Md_c::EventActionFunc event_action_tbl[] = {
    &daNpc_Md_c::actionWaitEvent,    &daNpc_Md_c::actionDefault,      &daNpc_Md_c::actionMsgSetEvent,  &daNpc_Md_c::actionMsgEndEvent,
    &daNpc_Md_c::actionDefault,      &daNpc_Md_c::actionFlyEvent,     &daNpc_Md_c::actionGlidingEvent, &daNpc_Md_c::actionLandingEvent,
    &daNpc_Md_c::actionWalkEvent,    &daNpc_Md_c::actionDashEvent,    &daNpc_Md_c::actionDefault,      &daNpc_Md_c::actionTactEvent,
    &daNpc_Md_c::actionTakeOffEvent, &daNpc_Md_c::actionOnetimeEvent, &daNpc_Md_c::actionDefault,      &daNpc_Md_c::actionHarpPlayEvent,
    &daNpc_Md_c::actionDefault,      &daNpc_Md_c::actionDefault,      &daNpc_Md_c::actionTurnEvent,    &daNpc_Md_c::actionDefault,
    &daNpc_Md_c::actionLookDown,     &daNpc_Md_c::actionLookDown,
};

static char* cut_name_tbl[] = {
    "WAIT", "CREATEITEM", "MSG_SET", "MSG_END", "POS_MOV",  "FLY",        "GLIDING",   "LANDING", "WALK",    "DASH",      "END",
    "TACT", "TAKEOFF",    "Onetime", "QUAKE",   "HARPPLAY", "OFF_PLAYER", "ON_PLAYER", "TURN",    "SET_ANM", "LOOK_DOWN", "LOOK_UP",
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
            int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
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
    /* Empty function */
}

/* 0000AC84-0000ACB4       .text actionDefault__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionDefault(int) {
    lookBack(0, 0, 1);
    return TRUE;
}

/* 0000ACB4-0000AD9C       .text initialWaitEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialWaitEvent(int staffIdx) {
    int* pDisp = dComIfGp_evmng_getMyIntegerP(staffIdx, "Disp");
    if (pDisp) {
        if (*pDisp) {
            fopAcM_onDraw(this);
        } else {
            fopDwTg_DrawQTo(&draw_tag);
        }
    } else {
        fopAcM_onDraw(this);
    }
    int* pTimer = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    if (pTimer) {
        m3118 = *pTimer;
    } else {
        m3118 = 0;
    }
    speedF = 0.0f;
}

/* 0000AD9C-0000ADCC       .text actionWaitEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionWaitEvent(int) {
    return cLib_calcTimer(&m3118) == 0 ? TRUE : FALSE;
}

/* 0000ADCC-0000AEB8       .text initialLetterEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialLetterEvent(int staffIdx) {
    u8 itemNo;

    clearStatus(daMdStts_UNK1 | daMdStts_UNK2 | daMdStts_FLY);
    setBitStatus(daMdStts_UNK4);
    speedF = 0.0f;
    m30F8 = 75.0f;
    if (mCurEvent == 0) {
        itemNo = 0x98;
    } else if (mCurEvent == 1) {
        itemNo = 0x25;
    } else if (mCurEvent == 2) {
        itemNo = 0x50;
    } else {
        itemNo = 0x98;
    }
    fpc_ProcID itemID = fopAcM_createItemForPresentDemo(&current.pos, itemNo, 0, -1, fopAcM_GetRoomNo(this));
    if (itemID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemID);
    }
    dComIfGp_evmng_cutEnd(staffIdx);
}

/* 0000AEB8-0000AFB0       .text initialMsgSetEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialMsgSetEvent(int staffIdx) {
    if (mMsgNo == 0x19dd) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1620);
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1608);
        dComIfGp_setNextStage("sea", 0xE3, 13, 8);
    } else {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        int* pMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
        if (pMsgNo != NULL) {
            mMsgNo = *pMsgNo;
            if ((mMsgNo == 0x19d6) && (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1504))) {
                mMsgNo = 0x19d9;
            }
        }
    }
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
void daNpc_Md_c::initialMovePosEvent(int staffIdx) {
    /* Nonmatching */
    static char* cut_anm_tbl[] = {
        "WAIT",
    };
    static const s32 cut_anm_idx_tbl[] = {
        0,
    };
    f32 fVar4;
    s16 sVar5;
    char* pcVar6;
    int iVar7;
    u16 uVar9;
    f32* pfVar8;
    cXyz* pfVar9;
    daPy_lk_c* pdVar10;
    char acStack_ac[12];

    pdVar10 = NULL;
    pcVar6 = dComIfGp_evmng_getMyStringP(staffIdx, "Target");
    if (pcVar6 != NULL) {
        strcpy(acStack_ac, pcVar6);
        iVar7 = strcmp(acStack_ac, "@PLAYER");
        if (iVar7 == 0) {
            pdVar10 = daPy_getPlayerLinkActorClass();
        }
        if (pdVar10 != NULL) {
            pcVar6 = dComIfGp_evmng_getMyStringP(staffIdx, "Type");
            if (pcVar6 != NULL) {
                strcpy(acStack_ac, pcVar6);
            }
            iVar7 = strcmp(acStack_ac, "LINK_DIST");
            if (iVar7 == 0) {
                uVar9 = fopAcM_searchActorAngleY(this, pdVar10);
                pfVar8 = dComIfGp_evmng_getMyFloatP(staffIdx, "Dist");
                if (pfVar8 != NULL) {
                    cXyz pos(current.pos.x + *pfVar8 * cM_ssin(uVar9), current.pos.y + 50.0f, current.pos.z + *pfVar8 * cM_scos(uVar9));
                    dBgS_GndChk local_a0;
                    local_a0.SetPos(&pos);
                    f32 temp_f1 = dComIfG_Bgsp()->GroundCross(&local_a0);
                    if (temp_f1 != -G_CM3D_F_INF) {
                        pos.y = temp_f1;
                    } else {
                        pos.y = current.pos.y;
                    }
                    pdVar10->setPlayerPosAndAngle(&pos, pdVar10->shape_angle.y);
                }
                pfVar8 = dComIfGp_evmng_getMyFloatP(staffIdx, "Angle");
                if (pfVar8 != NULL) {
                    pdVar10->setPlayerPosAndAngle(0, ((s16)(*pfVar8 * 182.04445f) + -0x8000) + uVar9);
                }
            } else {
                iVar7 = strcmp(acStack_ac, "DIST");
                if (iVar7 == 0) {
                    pfVar8 = dComIfGp_evmng_getMyFloatP(staffIdx, "Dist");
                    if (pfVar8 != NULL) {
                        fVar4 = cM_ssin(pdVar10->shape_angle.y);
                        current.pos.set(
                            pdVar10->current.pos.x + *pfVar8 * fVar4, pdVar10->current.pos.y, pdVar10->current.pos.z + *pfVar8 * cM_scos(pdVar10->shape_angle.y)
                        );
                    }
                    pfVar8 = dComIfGp_evmng_getMyFloatP(staffIdx, "Angle");
                    if (pfVar8 != NULL) {
                        sVar5 = ((s16)(*pfVar8 * 182.04445f) + -0x8000) + pdVar10->shape_angle.y;
                        current.angle.y = sVar5;
                        shape_angle.y = sVar5;
                    }
                } else {
                    pfVar8 = dComIfGp_evmng_getMyFloatP(staffIdx, "Angle");
                    if (pfVar8 != NULL) {
                        sVar5 = (s16)(*pfVar8 * 182.04445f) + pdVar10->shape_angle.y;
                        current.angle.y = sVar5;
                        shape_angle.y = sVar5;
                    }
                    pfVar9 = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");
                    if (pfVar9 != NULL) {
                        current.pos.set(pdVar10->current.pos.x + pfVar9->x, pdVar10->current.pos.y + pfVar9->y, pdVar10->current.pos.z + pfVar9->z);
                    }
                }
            }
        }
    } else {
        pfVar8 = dComIfGp_evmng_getMyFloatP(staffIdx, "Angle");
        if (pfVar8 != NULL) {
            sVar5 = (s16)(int)(*pfVar8 * 182.04445f);
            current.angle.y = sVar5;
            shape_angle.y = sVar5;
        }
        pfVar9 = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");
        if (pfVar9 != NULL) {
            current.pos = *pfVar9;
        }
    }
    gravity = l_HIO.m0F4;
    maxFallSpeed = -100.0f;
    speedF = 0.0f;
    speed.y = 0.0f;
    pcVar6 = dComIfGp_evmng_getMyStringP(staffIdx, "Name");
    if (pcVar6 != NULL) {
        strcpy(acStack_ac, pcVar6);
        iVar7 = strcmp(*cut_anm_tbl, acStack_ac);
        if (iVar7 == 0) {
            setAnm(*cut_anm_idx_tbl);
        }
    }
    pcVar6 = dComIfGp_evmng_getMyStringP(staffIdx, "ShipRide");
    if (pcVar6 != NULL) {
        strcpy(acStack_ac, pcVar6);
        iVar7 = strcmp(acStack_ac, "on");
        if (iVar7 == 0) {
            onShipRide();
        } else {
            iVar7 = strcmp(acStack_ac, "off");
            if (iVar7 == 0) {
                offShipRide();
            }
        }
    }
}

/* 0000B728-0000B79C       .text initialFlyEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialFlyEvent(int) {
    setAnm(0x19);
    setBitStatus(daMdStts_UNK1);
    setWingEmitter();
    speed.y = 20.0f;
    gravity = l_HIO.m188;
    maxFallSpeed = 10.0f;
    m3118 = 60 * 30;
}

/* 0000B79C-0000B870       .text actionFlyEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionFlyEvent(int staffIdx) {
    f32 fVar1;
    f32* pfVar2;

    pfVar2 = dComIfGp_evmng_getMyFloatP(staffIdx, "HIGH");
    fVar1 = 0.0f;
    if (pfVar2 != NULL) {
        fVar1 = *pfVar2;
    }
    if (current.pos.y > fVar1) {
        emitterDelete(m0508);
        return TRUE;
    } else {
        if (m3104 == 0x19) {
            if (m312A != 0) {
                setAnm(9);
            }
        }
        setAttention(true);
        if (mAcch.ChkRoofHit()) {
            return TRUE;
        } else {
            return cLib_calcTimer(&m3118) == 0 ? TRUE : FALSE;
        }
    }
}

/* 0000B870-0000B890       .text initialGlidingEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialGlidingEvent(int) {
    gravity = l_HIO.m0F4;
    maxFallSpeed = -100.0f;
}

/* 0000B890-0000B934       .text actionGlidingEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionGlidingEvent(int) {
    if (mAcch.ChkGroundHit()) {
        fopAcM_monsSeStart(this, JA_SE_CV_MD_LANDING, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        return TRUE;
    } else {
        if (!checkStatusCamTagIn()) {
            speedF = 0.0f;
        }
        setAttention(true);
        return FALSE;
    }
}

/* 0000B934-0000B99C       .text initialLandingEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialLandingEvent(int) {
    maxFallSpeed = -100.0f;
    speedF = 0.0f;
    shape_angle.x = 0;
    shape_angle.z = 0;
    clearStatus(daMdStts_UNK1);
    setAnm(0x10);
    m312A = 0;
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
    m3118 = 20 * 30;
}

/* 0000B9F8-0000BCC4       .text actionWalkEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionWalkEvent(int staffIdx) {
    cXyz local_24;
    cXyz local_3c;

    cXyz* pfVar2 = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");
    f32* pfVar3 = dComIfGp_evmng_getMyFloatP(staffIdx, "Speed");
    f32* pfVar4 = dComIfGp_evmng_getMyFloatP(staffIdx, "RunRate");
    if (pfVar2 != NULL) {
        local_24 = *pfVar2;
        local_3c = local_24 - current.pos;
        if (local_3c.absXZ() < 10.0f) {
            speedF = 0.0f;
            return TRUE;
        }
        current.angle.y = cM_atan2s(local_3c.x, local_3c.z);
        if (mJntCtrl.mbTrn != false) {
            cLib_addCalcAngleS2(&m3110, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
        } else {
            m3110 = 0;
            if (pfVar3 != NULL) {
                speedF = *pfVar3;
            } else {
                speedF = 5.0f;
            }
            if (pfVar4 != NULL) {
                mRunRate = *pfVar4;
            } else {
                mRunRate = 0.0f;
            }
            setAnm(2);
        }
        mJntCtrl.mbTrn = true;
        mJntCtrl.lookAtTarget(&shape_angle.y, &local_24, current.pos, current.angle.y, m3110, false);
        setAttention(true);
        if (wallHitCheck() >= 0) {
            speedF = 0.0f;
            current.pos = local_24;
            return TRUE;
        }
        if (cLib_calcTimer(&m3118) != 0) {
            return FALSE;
        }
        speedF = 0.0f;
        current.pos = local_24;
    }
    return TRUE;
}

/* 0000BCC4-0000BF1C       .text actionDashEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionDashEvent(int staffIdx) {
    cXyz local_24;
    cXyz local_3c;

    cXyz* pfVar2 = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");
    if (pfVar2 != NULL) {
        local_24 = *pfVar2;
        local_3c = local_24 - current.pos;
        if (local_3c.absXZ() < 10.0f) {
            speedF = 0.0f;
            return TRUE;
        }
        current.angle.y = cM_atan2s(local_3c.x, local_3c.z);
        if (mJntCtrl.mbTrn != false) {
            cLib_addCalcAngleS2(&m3110, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
        } else {
            m3110 = 0;
            speedF = 17.0f;
            mRunRate = 1.0f;
            setAnm(2);
        }
        mJntCtrl.mbTrn = true;
        mJntCtrl.lookAtTarget(&shape_angle.y, &local_24, current.pos, current.angle.y, m3110, false);
        if (wallHitCheck() >= 0) {
            speedF = 0.0f;
            current.pos = local_24;
            return TRUE;
        }
        setAttention(true);
        if (cLib_calcTimer(&m3118) != 0) {
            return FALSE;
        }
        speedF = 0.0f;
        current.pos = local_24;
    }
    return TRUE;
}

/* 0000BF1C-0000C12C       .text initialEndEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialEndEvent(int staffIdx) {
    int iVar1;
    int* piVar2;

    piVar2 = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMode");
    if (piVar2 == NULL) {
        iVar1 = 0;
    } else {
        iVar1 = *piVar2;
    }
    switch (iVar1) {
    case -2:
        if (mMsgNo == 0x19de) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1620);
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1608);
            dComIfGp_setNextStage("sea", 0xE3, 13, 8);
        }
        // Fall-through
    case -1:
        dComIfGp_event_reset();
        if (checkStatus(daMdStts_UNK80)) {
            setHarpPlayNum(0);
        }
        setNpcAction(&daNpc_Md_c::waitNpcAction);
        break;
    case 3:
        setNpcAction(&daNpc_Md_c::deleteNpcAction);
        break;
    case 2:
        clearStatus(daMdStts_UNK1);
        setNpcAction(&daNpc_Md_c::squatdownNpcAction);
        break;
    default:
    case 0:
        clearStatus(daMdStts_UNK1);
        if (checkStatus(daMdStts_UNK80)) {
            setAnm(0);
        } else {
            setHarpPlayNum(0);
        }
        setNpcAction(&daNpc_Md_c::waitNpcAction);
        break;
    }
}

/* 0000C12C-0000C250       .text actionTactEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionTactEvent(int staffIdx) {
    int* pPrm0 = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm0");
    s32 prm = 0;

    if (pPrm0 != NULL) {
        prm = *pPrm0;
    }
    s32 song = daPy_getPlayerActorClass()->getTactMusic();
    if (song >= 0) {
        setBitStatus(daMdStts_UNK400);
    }
    BOOL result = talk(1);
    if (result) {
        if (checkStatus(daMdStts_UNK400)) {
            clearStatus(daMdStts_UNK400);
            if (song == prm) {
                mMsgNo = 0x19dd;
            } else {
                mMsgNo = 0x19da;
            }
        } else {
            mCurEventMode = 10;
            if (checkStatus(daMdStts_UNK200)) {
                mMsgNo = 0x19dc;
                clearStatus(daMdStts_UNK200);
            }
            fopAcM_onDraw(this);
            dComIfGp_event_reset();
        }
    }
    return result;
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
void daNpc_Md_c::initialOnetimeEvent(int staffIdx) {
    /* Nonmatching */
    static char* cut_anm_tbl[] = {
        "WATASU",
    };
    static const s32 cut_anm_idx_tbl[] = {
        0x1A,
    };
    char* __src;
    char acStack_18[16];
    s32 var_r31;

    var_r31 = 0x1A;
    __src = dComIfGp_evmng_getMyStringP(staffIdx, "Name");
    if (__src != NULL) {
        strcpy(acStack_18, __src);
        if (!strcmp(acStack_18, *cut_anm_tbl)) {
            var_r31 = *cut_anm_idx_tbl;
        }
    }
    setAnm(var_r31);
    m312A = 0;
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
void daNpc_Md_c::initialQuake(int staffIdx) {
    char* __src;
    char acStack_1c[12];

    __src = dComIfGp_evmng_getMyStringP(staffIdx, "Mode");
    if (__src != NULL) {
        strcpy(acStack_1c, __src);
        if (!strcmp(acStack_1c, "Start")) {
            dComIfGp_getVibration().StartQuake(7, 1, cXyz(0.0f, 1.0f, 0.0f));
        }
        if (!strcmp(acStack_1c, "Stop")) {
            dComIfGp_getVibration().StopQuake(1);
        }
    }
}

/* 0000C48C-0000C4DC       .text setHarpPlayNum__10daNpc_Md_cFi */
void daNpc_Md_c::setHarpPlayNum(int) {
    static const s32 l_harp_play_anm[] = {0x16, 0x17, 0x16, 0x17, 0x16, 0x17};

    int iVar1 = cLib_getRndValue(0, 4);
    setAnm(l_harp_play_anm[iVar1]);
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
void daNpc_Md_c::initialTurnEvent(int staffIdx) {
    int* puVar1 = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    if (puVar1 != NULL) {
        m3118 = (s16)*puVar1;
    } else {
        m3118 = 0;
    }
    cXyz* pfVar2 = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");
    if (pfVar2 != NULL) {
        m30B8 = *pfVar2;
    } else {
        m30B8.setall(0.0f);
    }
}

/* 0000C654-0000C7CC       .text actionTurnEvent__10daNpc_Md_cFi */
BOOL daNpc_Md_c::actionTurnEvent(int staffIdx) {
    char* __src;
    int* piVar1;
    int iVar2;
    s16 sVar3;
    int iVar4;

    setAttention(true);
    char local_20[10] = {
        "@PLAYER",
    };
    __src = dComIfGp_evmng_getMyStringP(staffIdx, "Target");
    if (__src != NULL) {
        strcpy(local_20, __src);
    }
    piVar1 = dComIfGp_evmng_getMyIntegerP(staffIdx, "Type");
    if (piVar1 == NULL) {
        iVar4 = 0;
    } else {
        iVar4 = *piVar1;
    }
    mJntCtrl.setParam(
        l_HIO.mNpc.mMaxBackboneX,
        l_HIO.mNpc.mMaxBackboneY,
        l_HIO.mNpc.mMinBackboneX,
        l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX,
        l_HIO.mNpc.mMaxHeadY,
        -500,
        l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep
    );
    if (iVar4 == 2) {
        mJntCtrl.mbTrn = true;
        iVar4 = 0;
    }
    iVar2 = strcmp(local_20, "@PLAYER");
    if (iVar2 == 0) {
        lookBack(1, 0, iVar4);
    } else {
        lookBack(&m30B8, 1, iVar4);
    }
    sVar3 = cLib_calcTimer(&m3118);
    if (sVar3 != 0) {
        return FALSE;
    }
    return TRUE;
}

/* 0000C7CC-0000CA5C       .text initialSetAnmEvent__10daNpc_Md_cFi */
void daNpc_Md_c::initialSetAnmEvent(int staffIdx) {
    int* puVar1 = dComIfGp_evmng_getMyIntegerP(staffIdx, "Number");
    if (puVar1 != NULL) {
        int iVar1 = setAnm(getAnmType(*puVar1));
        if (iVar1 != 0) {
            setBitStatus(daMdStts_UNK1);
        } else {
            clearStatus(daMdStts_UNK1);
        }
    }
    speedF = 0.0f;
    f32* pfVar2 = dComIfGp_evmng_getMyFloatP(staffIdx, "PlaySpeed");
    if (pfVar2 != NULL) {
        mpMorf->setPlaySpeed(*pfVar2);
        mpArmMorf->setPlaySpeed(*pfVar2);
        mpWingMorf->setPlaySpeed(*pfVar2);
        if (*pfVar2 < 0.0f) {
            mpMorf->setFrame(mpMorf->getEndFrame());
            mpArmMorf->setFrame(mpArmMorf->getEndFrame());
            mpWingMorf->setFrame(mpWingMorf->getEndFrame());
        }
        mpMorf->setLoopFrame(mpMorf->getFrame());
        mpArmMorf->setLoopFrame(mpArmMorf->getFrame());
        mpWingMorf->setLoopFrame(mpWingMorf->getFrame());
        m30D0 = mpMorf->getFrame();
    }
    pfVar2 = dComIfGp_evmng_getMyFloatP(staffIdx, "MorfFrame");
    if (pfVar2 != NULL) {
        mpMorf->setMorf(*pfVar2);
        mpArmMorf->setMorf(*pfVar2);
        mpWingMorf->setMorf(*pfVar2);
    }
    mJntCtrl.setHead_y(0);
    mJntCtrl.setHead_x(0);
    mJntCtrl.setBackBone_y(0);
    mJntCtrl.setBackBone_x(0);
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
    s16 desiredYRot;
    cXyz local_14;
    cXyz cStack_20;

    m30AC.y = -50.0f;
    cXyz local_38(0.0f, 0.0f, 0.0f);
    desiredYRot = shape_angle.y;
    local_38.set(current.pos.x, eyePos.y, current.pos.z);
    local_14 = local_38;
    mDoMtx_stack_c::YrotS(desiredYRot);
    mDoMtx_stack_c::multVec(&m30AC, &cStack_20);
    local_14 += cStack_20;
    mJntCtrl.lookAtTarget(&shape_angle.y, &local_14, local_38, desiredYRot, m3110, false);
    return TRUE;
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
    } else if (msgStatus == fopMsgStts_INPUT_e) {
        if (r4 != 0) {
            if (dComIfGp_checkMesgCancelButton()) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
                setBitStatus(daMdStts_UNK200);
            }
            if (checkStatus(daMdStts_UNK400)) {
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
        0x00000000, 0x00000002, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x0000000B, 0x00000007, 0x00000009, 0x0000000C,
        0x0000000D, 0x0000000E, 0x0000000F, 0x00000011, 0x00000014, 0x00000012, 0x0000001B, 0x0000001C, 0x00000015, 0x00000015, 0x00000016,
        0x00000017, 0x00000018, 0x00000019, 0x0000001D, 0x0000001A, 0x00000010, 0x0000001F, 0x00000020, 0x00000022, 0x0000001E, 0x00000023,
        0x00000024, 0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x0000002A, 0x0000002B, 0x0000002C, 0x0000002D, 0x00000031,
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
    JUT_ASSERT(7502, eyeTexPtrn != NULL);
    if (m0520.init(modelData, eyeTexPtrn, TRUE, J3DFrameCtrl::EMode_RESET, 1.0f, 0, -1, param_2, FALSE)) {
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
            m0520.initPlay(m3112, J3DFrameCtrl::EMode_RESET, 1.0f, 0, -1, true);
        }
    }
}

/* 0000CFCC-0000D0B8       .text initLightBtkAnm__10daNpc_Md_cFb */
BOOL daNpc_Md_c::initLightBtkAnm(bool param_1) {
    J3DModelData* pModelData = mpHarpLightModel->getModelData();
    bool ret = false;
    J3DAnmTextureSRTKey* a_lightBtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(mModelArcName, "ymdhp00.btk");
    JUT_ASSERT(7559, a_lightBtk != NULL);
    BOOL iVar2 = mLightBtkAnm.init(pModelData, a_lightBtk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, param_1, 0);
    if (iVar2) {
        ret = true;
    }
    return ret;
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
        {"md_wait01.bck", ""},     {"md_walk.bck", "md_run.bck"}, {"md_squatdown.bck", ""}, {"md_sqwait01.bck", ""},   {"md_sqwait02.bck", ""},
        {"md_firing.bck", ""},     {"md_fly01.bck", ""},          {"md_fly02.bck", ""},     {"md_gliding.bck", ""},    {"md_fall.bck", ""},
        {"md_fall02.bck", ""},     {"md_land.bck", ""},           {"md_land02.bck", ""},    {"md_land03.bck", ""},     {"md_kamaewait.bck", ""},
        {"md_kamae.bck", ""},      {"md_piyo2.bck", ""},          {"md_ojigi.bck", ""},     {"md_harpplay01.bck", ""}, {"md_harpplay02.bck", ""},
        {"md_takeoff01.bck", ""},  {"md_takeoff02.bck", ""},      {"md_watasu.bck", ""},    {"md_talk01.bck", ""},     {"md_talk02.bck", ""},
        {"md_talk03.bck", ""},     {"md_talk04.bck", ""},         {"md_mkamae.bck", ""},    {"md_mwait.bck", ""},      {"md_oriwait.bck", ""},
        {"md_shipwait.bck", ""},   {"md_caught01.bck", ""},       {"md_caught02.bck", ""},  {"md_kyohi.bck", ""},      {"md_kyoro2.bck", ""},
        {"md_shipwait02.bck", ""}, {"md_shiptalk01.bck", ""},     {"md_talk05.bck", ""},    {"md_unazuki.bck", ""},
    };
    static anm_prm l_anmPrm[] = {
        {0x00, 0x00, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x00, 0x00, 0x00, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f},
        {0x01, 0x01, 0x00, J3DFrameCtrl::EMode_LOOP, 4.0f, 1.0f}, {0x02, 0x02, 0x00, J3DFrameCtrl::EMode_NONE, 4.0f, 1.0f},
        {0x03, 0x03, 0x00, J3DFrameCtrl::EMode_LOOP, 4.0f, 1.0f}, {0x04, 0x04, 0x00, J3DFrameCtrl::EMode_LOOP, 4.0f, 1.0f},
        {0x05, 0x81, 0x00, J3DFrameCtrl::EMode_NONE, 0.0f, 1.0f}, {0x06, 0x82, 0x00, J3DFrameCtrl::EMode_LOOP, 3.0f, 1.0f},
        {0x06, 0x82, 0x00, J3DFrameCtrl::EMode_NONE, 3.0f, 1.0f}, {0x07, 0x83, 0x03, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x07, 0x83, 0x03, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f}, {0x08, 0x84, 0x00, J3DFrameCtrl::EMode_LOOP, 4.0f, 1.0f},
        {0x09, 0x05, 0x01, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x0A, 0x06, 0x02, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x0B, 0x07, 0x06, J3DFrameCtrl::EMode_NONE, 0.0f, 1.0f}, {0x0C, 0x08, 0x07, J3DFrameCtrl::EMode_NONE, 0.0f, 1.0f},
        {0x0D, 0x09, 0x06, J3DFrameCtrl::EMode_NONE, 0.0f, 1.0f}, {0x0E, 0x0A, 0x05, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x0F, 0x0B, 0x04, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f}, {0x0F, 0x0B, 0x04, J3DFrameCtrl::EMode_NONE, 8.0f, -1.0f},
        {0x10, 0x0C, 0x08, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x11, 0x0D, 0x00, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f},
        {0x12, 0x0E, 0x09, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x13, 0x0F, 0x09, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x14, 0x10, 0x00, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f}, {0x15, 0x85, 0x00, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f},
        {0x16, 0x11, 0x0A, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f}, {0x17, 0x12, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x18, 0x13, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x19, 0x14, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x1A, 0x15, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x1B, 0x16, 0x00, J3DFrameCtrl::EMode_NONE, 8.0f, 1.4f},
        {0x1C, 0x17, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 0.0f}, {0x1B, 0x16, 0x00, J3DFrameCtrl::EMode_NONE, 8.0f, -1.4f},
        {0x1D, 0x18, 0x0B, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x1E, 0x19, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x1F, 0x86, 0x0C, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x20, 0x87, 0x0C, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x17, 0x12, 0x05, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x21, 0x1A, 0x0D, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x22, 0x1B, 0x00, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f}, {0x1A, 0x15, 0x05, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f},
        {0x23, 0x1C, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x24, 0x1D, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x25, 0x1E, 0x00, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x25, 0x1E, 0x05, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f},
        {0x07, 0x83, 0x03, J3DFrameCtrl::EMode_LOOP, 8.0f, 1.0f}, {0x04, 0x04, 0x05, J3DFrameCtrl::EMode_LOOP, 4.0f, 1.0f},
        {0x00, 0x00, 0x00, J3DFrameCtrl::EMode_LOOP, 0.0f, 1.0f}, {0x26, 0x1F, 0x0F, J3DFrameCtrl::EMode_NONE, 8.0f, 1.0f},
    };
    static anm_tbl armAnmTbl[] = {
        {"mdarm_wait01.bck", ""},     {"mdarm_walk.bck", "mdarm_run.bck"},
        {"mdarm_squatdown.bck", ""},  {"mdarm_sqwait01.bck", ""},
        {"mdarm_sqwait02.bck", ""},   {"mdarm_fall.bck", ""},
        {"mdarm_fall02.bck", ""},     {"mdarm_land.bck", ""},
        {"mdarm_land02.bck", ""},     {"mdarm_land03.bck", ""},
        {"mdarm_kamaewait.bck", ""},  {"mdarm_kamae.bck", ""},
        {"mdarm_piyo2.bck", ""},      {"mdarm_ojigi.bck", ""},
        {"mdarm_harpplay01.bck", ""}, {"mdarm_harpplay02.bck", ""},
        {"mdarm_takeoff01.bck", ""},  {"mdarm_watasu.bck", ""},
        {"mdarm_talk01.bck", ""},     {"mdarm_talk02.bck", ""},
        {"mdarm_talk03.bck", ""},     {"mdarm_talk04.bck", ""},
        {"mdarm_mkamae.bck", ""},     {"mdarm_mwait.bck", ""},
        {"mdarm_oriwait.bck", ""},    {"mdarm_shipwait.bck", ""},
        {"mdarm_kyohi.bck", ""},      {"mdarm_kyoro2.bck", ""},
        {"mdarm_shipwait02.bck", ""}, {"mdarm_shiptalk01.bck", ""},
        {"mdarm_talk05.bck", ""},     {"mdarm_unazuki.bck", ""},
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
        dNpc_Md_setAnm(mpMorf, mRunRate, prm->loopMode, morf, speed, bodyAnm->m00, bodyAnm->m20, mModelArcName);
        m30D0 = mpMorf->getFrame();

        if (prm->armAnmTblIdx < 0x80) {
            anm_tbl* armAnm = &armAnmTbl[prm->armAnmTblIdx];
            dNpc_Md_setAnm(mpArmMorf, mRunRate, prm->loopMode, morf, speed, armAnm->m00, armAnm->m20, mModelArcName);
            ret = FALSE;
        } else {
            if (!isTypeShipRide()) {
                dNpc_Md_setAnm(mpWingMorf, prm->loopMode, morf, speed, wingAnmTbl[prm->armAnmTblIdx - 0x80].m00, mModelArcName);
            }
            ret = TRUE;
        }

#if VERSION > VERSION_DEMO
        if (m3104 == 0x12 || m3104 == 0x1F) {
            fopAcM_seStartCurrent(this, JA_SE_CM_MD_HARP_SET_UP, 0);
        } else if (m3104 == 0x13 || m3104 == 0x21) {
            fopAcM_seStartCurrent(this, JA_SE_CM_MD_HARP_TAKE_OFF, 0);
        }
#endif
    }

    if (prm->btpAnmTblIdx != m3137) {
        initTexPatternAnm(prm->btpAnmTblIdx, true);
    }

    if (m312D == 0x0E || m312D == 0x12 || m312D == 0x13 || m312D == 0x1A || m312D == 0x1C || m312D == 0x25) {
        setBitStatus(daMdStts_UNK80);
    } else if (m312D != 0x0F && m312D != 0x1B) {
        clearStatus(daMdStts_UNK80);
    }

    if (m312D == 0x1B || m312D == 0x1C) {
        setBitStatus(daMdStts_UNK4000);
    } else {
        clearStatus(daMdStts_UNK4000);
    }

    if (m312D == 0x10) {
        if (m0508[1] == NULL) {
            m0508[1] = dComIfGp_particle_set(
                dPa_name::ID_SCENE_819D, &current.pos, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this), &tevStr.mColorK0, &tevStr.mColorK0
            );
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
bool daNpc_Md_c::dNpc_Md_setAnm(
    mDoExt_McaMorf2* pMorf, f32 param_f1, int loopMode, f32 morf, f32 speed, char* fileName1, char* filename2, const char* arcName
) {
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
u8 daNpc_Md_c::chkAttention(cXyz pos, s16 angle, int param_3) {
    /* Nonmatching */
    daPy_lk_c* player = daPy_getPlayerLinkActorClass();
    f32 maxAttnDistXZ = l_HIO.mNpc.mMaxAttnDistXZ;
    f32 dVar9 = l_HIO.m0BC;
    f32 dVar8 = l_HIO.m0C0;
    int maxAttnAngleY = l_HIO.mNpc.mMaxAttnAngleY;
    if (isShipRide()) {
        maxAttnDistXZ = l_HIO.m074.m04;
    } else {
        if ((mType == 2) && (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1101))) {
            maxAttnDistXZ = l_HIO.m0B8;
        }
    }
    cXyz delta;
    delta.x = player->current.pos.x - pos.x;
    delta.z = player->current.pos.z - pos.z;
    f32 distXZ = std::sqrtf(delta.x * delta.x + delta.z * delta.z);
    s16 targetAngleY = cM_atan2s(delta.x, delta.z);
    delta.y = player->current.pos.y - pos.y;
    if (m312C != 0) {
        maxAttnDistXZ += 40.0f;
        maxAttnAngleY += 0x71c;
    }
    targetAngleY -= angle;
    u8 uVar5;
    if (param_3 != 0) {
        uVar5 = 0;
        if (maxAttnDistXZ > distXZ) {
            maxAttnDistXZ = delta.y;
            if ((maxAttnDistXZ < dVar9) && (maxAttnDistXZ > dVar8)) {
                return TRUE;
            }
        }
    } else {
        uVar5 = 0;
        if ((maxAttnAngleY > abs(targetAngleY)) && (maxAttnDistXZ > distXZ)) {
            maxAttnDistXZ = delta.y;
            if ((maxAttnDistXZ < dVar9) && (maxAttnDistXZ > dVar8)) {
                uVar5 = 1;
            }
        }
    }
    return uVar5;
}

/* 0000D82C-0000D8FC       .text chkArea__10daNpc_Md_cFP4cXyz */
bool daNpc_Md_c::chkArea(cXyz* param_1) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 maxDist = l_HIO.mNpc.mMaxAttnDistXZ;

    cXyz delta;
    delta.x = player->current.pos.x - param_1->x;
    delta.z = player->current.pos.z - param_1->z;
    f32 dist = std::sqrtf(delta.x * delta.x + delta.z * delta.z);

    maxDist += 40.0f;
    return maxDist > dist;
}

/* 0000D8FC-0000D950       .text carryCheck__10daNpc_Md_cFv */
void daNpc_Md_c::carryCheck() {
    if (fopAcM_checkCarryNow(this)) {
        setNpcAction(&daNpc_Md_c::carryNpcAction);
    }
}

/* 0000D950-0000DAD4       .text eventOrder__10daNpc_Md_cFv */
void daNpc_Md_c::eventOrder() {
    if (mCurEventMode == 1) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mCurEventMode == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mCurEventMode == 2 || mCurEventMode == 3) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
    } else if (mCurEventMode >= 4) {
        switch (mCurEventMode) {
        case 4:
            mCurEvent = 0;
            break;
        case 5:
            mCurEvent = 1;
            break;
        case 6:
            mCurEvent = 2;
            break;
        case 7:
            mCurEvent = 3;
            break;
        case 8:
            mCurEvent = 4;
            break;
        case 9:
            mCurEvent = 5;
            break;
        case 10:
            mCurEvent = 6;
            dComIfGp_event_order(dEvtType_OTHER_e, 0xFF, dEvtFlag_NOPARTNER_e, 0xFFFF, dComIfGp_getPlayer(0), this, mEventIdxTable[mCurEvent]);
            return;
        case 11:
            mCurEvent = 7;
            break;
        case 12:
            mCurEvent = 8;
            break;
        }
        fopAcM_orderOtherEventId(this, mEventIdxTable[mCurEvent]);
    }
}

/* 0000DAD4-0000DC14       .text checkOrder__10daNpc_Md_cFv */
void daNpc_Md_c::checkOrder() {
    if ((eventInfo.checkCommandTalk()) && ((mCurEventMode == 1 || (mCurEventMode == 2)) || (mCurEventMode == 3))) {
        mCurEventMode = 0;
        if (dComIfGp_event_chkTalkXY()) {
            onXYTalk();
            if (isDefaultTalkXY()) {
                setNpcAction(&daNpc_Md_c::talkNpcAction);
            }
        } else if (isShipRide()) {
            setNpcAction(&daNpc_Md_c::shipTalkNpcAction);
        } else {
            setNpcAction(&daNpc_Md_c::talkNpcAction);
        }
        fopAcM_cancelCarryNow(this);
    }
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
        dComIfGs_onEventBit(dSv_event_flag_c::MEDLI_GAVE_FATHERS_LETTER);
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
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1101);
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x17E5:
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1280);
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
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1104);
        // Fall-through
    case 0x17F8:
        setBitStatus(daMdStts_UNK40);
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
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1102);
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
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1402);
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
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1504);
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
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2E40);
        onSeaTalk();
        // Fall-through
    case 0x1A01:
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C08);
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
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3B80);
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
        if (dComIfGs_isEventBit(dSv_event_flag_c::MEDLI_GAVE_FATHERS_LETTER)) {
            msgNo = 0x17DC;
        } else if (dComIfGs_getClearCount() != 0) {
            msgNo = 0x1805;
        } else {
            msgNo = 0x17D5;
        }
    } else if (isTypeAdanmae()) {
        if (checkStatus(daMdStts_UNK40)) {
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
        } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1104)) {
            msgNo = 0x17F7;
        } else {
            msgNo = 0x17E6;
        }
    } else if (isTypeM_Dra09()) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1101)) {
            msgNo = 0x17E5;
        } else {
            msgNo = 0x17DD;
        }
    } else if (isTypeSea()) {
        if (isXYTalk()) {
            if (isDefaultTalkXY()) {
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E40)) {
                    msgNo = 0x1A00;
                } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C08)) {
                    msgNo = 0x19F8;
                } else {
                    msgNo = 0x19FC;
                }
            } else {
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1504)) {
                    msgNo = 0x19D9;
                } else {
                    msgNo = 0x19D6;
                }
            }
        } else {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1402)) {
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
    cXyz local_20;
    cXyz local_2c;
    cXyz local_38;
    cXyz local_44;
    cXyz local_50;

    local_20.setall(0.0f);
    local_2c = current.pos;
    if ((!isShipRide()) && (!fopAcM_CheckStatus(this, fopAcStts_CARRY_e))) {
        mCyl1.SetC(local_2c);
        mCyl1.SetR(30.0f);
        mCyl1.SetH(m30F8);
        dComIfG_Ccsp()->Set(&mCyl1);
    } else {
        mCyl1.ClrCoHit();
        mCyl1.ClrTgHit();
    }
    mCyl2.SetC(local_2c);
    mCyl2.SetR(30.0f);
    mCyl2.SetH(m30F8);
    dComIfG_Ccsp()->Set(&mCyl2);
    mCyl3.SetC(local_2c);
    mCyl3.SetR(30.0f);
    mCyl3.SetH(m30F8);
    dComIfG_Ccsp()->Set(&mCyl3);
    if (isLightHit()) {
        cMtx_copy(mpHarpModel->getBaseTRMtx(), mDoMtx_stack_c::now);
        mDoMtx_stack_c::transM(l_HIO.m034.m0C, l_HIO.m034.m10, l_HIO.m034.m14);
        mDoMtx_stack_c::XYZrotM(l_HIO.m034.m18, l_HIO.m034.m1A, l_HIO.m034.m1C);
        mDoMtx_stack_c::multVec(&l_ms_light_local_start, &local_44);
        mDoMtx_stack_c::multVecSR(&l_ms_light_local_vec, &local_38);
        local_50 = local_44 + local_38;
        mLinChk.Set(&local_44, &local_50, this);
        if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
            local_50 = *mLinChk.GetCrossP();
            local_38 = local_50 - local_44;
        }
        mCps.SetStartEnd(local_44, local_50);
        mCps.SetAtVec(local_38);
        mCps.OnAtSetBit();
        dComIfG_Ccsp()->Set(&mCps);
        dComIfG_Ccsp()->SetMass(&mCps, 1);
        fopAcM_OffStatus(this, fopAcStts_CULL_e);
    } else {
        mCps.ResetAtHit();
        mCps.OffAtSetBit();
        fopAcM_OnStatus(this, fopAcStts_CULL_e);
    }
}

/* 0000E95C-0000E9F0       .text setAttention__10daNpc_Md_cFb */
void daNpc_Md_c::setAttention(bool param_1) {
    if ((!param_1) && (m312B >= 2)) {
        return;
    }
    eyePos.set(m3088.x, m3088.y, m3088.z);
    f32 fVar1;
    if (m_flying != false) {
        fVar1 = 70.0f;
    } else if (daPy_getPlayerActorClass() == this) {
        fVar1 = 110.0f;
    } else {
        fVar1 = l_HIO.mNpc.mAttnYOffset;
    }
    attention_info.position.set(current.pos.x, current.pos.y + fVar1, current.pos.z);
}

/* 0000E9F0-0000EB28       .text lookBack__10daNpc_Md_cFiii */
void daNpc_Md_c::lookBack(int param_1, int param_2, int param_3) {
    cXyz local_30;
    cXyz local_3c;

    cXyz* dstPos = NULL;
    local_3c.setall(0.0f);
    s16 desiredYRot = shape_angle.y;
    s16 target;
    if (mJntCtrl.mbTrn != false) {
        if (param_2 != 0) {
            target = l_HIO.m1BC;
        } else {
            target = l_HIO.mNpc.mMaxHeadTurnVel;
        }
        cLib_addCalcAngleS2(&m3110, target, 4, 0x800);
    } else {
        m3110 = 0;
    }
    if (param_1 != 0) {
        local_30 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        dstPos = &local_30;
        local_3c = current.pos;
        local_3c.y = eyePos.y;
    }
    mJntCtrl.lookAtTarget(&shape_angle.y, dstPos, local_3c, desiredYRot, m3110, param_3);
}

/* 0000EB28-0000EC38       .text lookBack__10daNpc_Md_cFP4cXyzii */
void daNpc_Md_c::lookBack(cXyz* param_1, int param_2, int param_3) {
    cXyz local_30;
    cXyz local_3c;

    cXyz* dstPos = NULL;
    local_3c.setall(0.0f);
    s16 desiredYRot = shape_angle.y;
    if (mJntCtrl.mbTrn != false) {
        cLib_addCalcAngleS2(&m3110, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
    } else {
        m3110 = 0;
    }
    if (param_2 != 0) {
        local_30 = *param_1;
        dstPos = &local_30;
        local_3c = current.pos;
        local_3c.y = eyePos.y;
    }
    mJntCtrl.lookAtTarget(&shape_angle.y, dstPos, local_3c, desiredYRot, m3110, param_3);
}

/* 0000EC38-0000EDD0       .text lookBackWaist__10daNpc_Md_cFsf */
s32 daNpc_Md_c::lookBackWaist(s16 param_1, f32 param_2) {
    f32 fVar1;
    s16 iVar2;
    s16 sVar3;
    s16 sVar4;
    bool uVar5;
    f32 dVar6;

    iVar2 = (param_1 - shape_angle.y);
    fVar1 = l_HIO.m034.m04 * (param_2 * cM_scos(iVar2));
    dVar6 = l_HIO.m034.m08 * (param_2 * cM_ssin(iVar2));
    if (fVar1 < 0.0f) {
        sVar3 = l_HIO.m034.m20 * fVar1;
    } else {
        sVar3 = l_HIO.m034.m1E * fVar1;
    }
    sVar3 = cLib_addCalcAngleS(&m3114, sVar3, 4, 0xc00, 0x180);
    sVar4 = cLib_addCalcAngleS(&m3116, l_HIO.m034.m22 * dVar6, 4, 0xc00, 0x180);
    uVar5 = false;
    if ((sVar3 == 0) && (sVar4 == 0)) {
        uVar5 = true;
    }
    return uVar5;
}

/* 0000EDD0-0000F100       .text setBaseMtx__10daNpc_Md_cFv */
void daNpc_Md_c::setBaseMtx() {
    s16 sVar4;
    J3DModel* pJVar6;

    pJVar6 = mpMorf->getModel();
    if (fopAcM_CheckStatus(this, fopAcStts_CARRY_e)) {
        if (isNoCarryAction()) {
            mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
            mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
            mDoMtx_stack_c::transM(0.0f, -l_HIO.m05C.m4, 0.0f);
        } else {
            mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
            mDoMtx_stack_c::YrotM(shape_angle.y);
            mDoMtx_stack_c::transM(m3298.x, m3298.y, m3298.z);
            mDoMtx_stack_c::XrotM(shape_angle.x);
            mDoMtx_stack_c::ZrotM(shape_angle.z);
        }
    } else if (isShipRide()) {
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
        daShip_c* ship = dComIfGp_getShipActor();
        cMtx_copy(ship->mpBodyAnm->getModel()->getBaseTRMtx(), mDoMtx_stack_c::now);
        mDoMtx_stack_c::transM(43.0f, 14.65f, 13.99f);
        mDoMtx_stack_c::XYZrotM(0, -0x45b0, 0);
        current.pos.set(mDoMtx_stack_c::now[0][3], mDoMtx_stack_c::now[1][3], mDoMtx_stack_c::now[2][3]);
        sVar4 = ship->shape_angle.y + -0x4000;
        shape_angle.y = sVar4;
        current.angle.y = sVar4;
        setAttention(true);
        tevStr.mRoomNo = ship->tevStr.mRoomNo;
        tevStr.mEnvrIdxOverride = ship->tevStr.mEnvrIdxOverride;
    } else {
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 95.0f, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::transM(m3298.x, m3298.y, m3298.z);
        mDoMtx_stack_c::XrotM(shape_angle.x);
        mDoMtx_stack_c::ZrotM(shape_angle.z);
        mDoMtx_stack_c::transM(0.0f, -95.0f, 0.0f);
    }
    pJVar6->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if (mType != 7) {
        mpWingMorf->calc();
    }
    mpArmMorf->calc();
    if (checkStatus(daMdStts_UNK80)) {
        cMtx_copy(mpArmMorf->getModel()->getAnmMtx(m_handL_jnt_num), mDoMtx_stack_c::now);
        mDoMtx_stack_c::transM(0.37f, 3.81f, -11.13f);
        mDoMtx_stack_c::XYZrotM(0x1b24, -0x2913, -0x1982);
    } else {
        cMtx_copy(mpMorf->getModel()->getAnmMtx(m_backbone2_jnt_num), mDoMtx_stack_c::now);
        mDoMtx_stack_c::transM(2.2f, -11.681f, 1.3f);
        mDoMtx_stack_c::XYZrotM(0x3f11, 0x2894, 0x7f7e);
    }
    mpHarpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpHarpLightModel->setBaseTRMtx(mpHarpModel->getBaseTRMtx());
}

/* 0000F100-0000F160       .text deletePiyoPiyo__10daNpc_Md_cFv */
void daNpc_Md_c::deletePiyoPiyo() {
    JPABaseEmitter* pJVar2 = m0508[1];
    if (pJVar2 == NULL) {
        return;
    }
    pJVar2->quitImmortalEmitter();
    m0508[1]->becomeInvalidEmitter();
    JSUPtrLink* link = pJVar2->getParticleList()->getFirstLink();
    while (link != 0) {
        JPABaseParticle* ptcl = (JPABaseParticle*)link->getObjectPtr();
        ptcl->setDeleteParticleFlag();
        link = link->getNext();
    }
    m0508[1] = NULL;
}

/* 0000F160-0000F4E0       .text init__10daNpc_Md_cFv */
BOOL daNpc_Md_c::init() {
    /* Nonmatching */
    u8 uVar1;
    ResTIMG* ctx_00;
    cXyz local_30;

    local_30.x = 0.0f;
    local_30.y = 0.0f;
    local_30.z = 0.0f;
    uVar1 = (fopAcM_GetParam(this) >> 0x10 & 0xFF);
    m3100 = uVar1;
    m313E = 0;
    m30F4 = JA_SE_CM_MD_HARP_CN4;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x21;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x21;
    attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 0x27;
    mCurEventMode = 0;
    mCurEvent = 0;
    m0508[0] = NULL;
    m0508[1] = NULL;
    m0508[2] = NULL;
    m0508[3] = NULL;
    m0508[4] = NULL;
    m0508[5] = NULL;
    m30AC.x = 0.0f;
    m30AC.y = 0.0f;
    m30AC.z = 50.0f;
    m313C = 0;
    m30F0 = 0;
    gravity = l_HIO.m0F4;
    if (mType == 6) {
        setNpcAction(&daNpc_Md_c::harpWaitNpcAction);
    } else {
        setNpcAction(&daNpc_Md_c::waitNpcAction);
    }
    m3094 = current.pos;
    m3088 = current.pos;
    for (s32 i = 0; i < 4; i++) {
        m3234[i].setall(0.0f);
    }
    if ((uVar1 & 1) != 0) {
        m30F0 = 8;
    }
    m3135 = 0;
    mCurEvent = -1;
    m_flying = false;
    m_mirror = 0;
    m30F8 = 120.0f;
    mRunRate = 0.0f;
    mpMorf->setAnmRate(mRunRate);
    mpArmMorf->setAnmRate(mRunRate);
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1620)) {
        onNpcNotChange();
    } else {
        if (shipRideCheck()) {
            mpMorf->setMorf(0.0f);
            mpArmMorf->setMorf(0.0f);
        }
    }
    if ((mType == 5) || (mType == 4)) {
        mStts.Init(0xfe, 0xFF, this);
    } else {
        mStts.Init(0xFF, 0xFF, this);
    }
    mCyl1.Set(l_cyl_src);
    mCyl1.SetStts(&mStts);
    mCyl2.Set(l_wind_cyl_src);
    mCyl2.SetStts(&mStts);
    mCyl3.Set(l_light_cyl_src);
    mCyl3.SetStts(&mStts);
    mCps.Set(l_fan_light_cps_src);
    mCps.SetStts(&mStts);
    mCps.SetAtType(0x800000);
    mCps.SetR(20.0f);
    ctx_00 = (ResTIMG*)dComIfG_getObjectRes(mModelArcName, "md_spot.bti");
    m0B70.init(ctx_00);
    if (mType == 4) {
        onNpcCallCommand();
    }
    for (s32 i = 0; i < 10; i++) {
        mEventIdxTable[i] = dComIfGp_evmng_getEventIdx(event_name_tbl[i], 0xff);
    }
    eventInfo.mpCheckCB = daNpc_Md_XyCheckCB;
    eventInfo.mpEventCB = daNpc_Md_XyEventCB;
    return TRUE;
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

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    drawDamageFog();
    g_env_light.setLightTevColorType(model, &tevStr);
    m0520.entry(modelData);
    mpMorf->entryDL();
    m0520.remove(modelData);

    if (!isTypeShipRide()) {
        if (checkStatus(daMdStts_UNK1)) {
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

        mDoMtx_stack_c::copy(mpHarpModel->getBaseTRMtx());
        mDoMtx_stack_c::transM(l_HIO.m034.m0C, l_HIO.m034.m10, l_HIO.m034.m14);
        Mtx mtx;
        mDoMtx_copy(mDoMtx_stack_c::get(), mtx);
        mDoMtx_stack_c::transS(l_ms_light_local_start);
        mDoMtx_stack_c::YrotM(0x8000);
        f32 temp = mCps.GetAtVecP()->abs();
        mDoMtx_stack_c::scaleM(0.1f, 0.1f, temp * (1.0f / 9600.0f));
        mDoMtx_stack_c::revConcat(mtx);
#if VERSION == VERSION_DEMO
        m0B70.update(mDoMtx_stack_c::get(), 0xFF);
#else
        m0B70.update(mDoMtx_stack_c::get(), 0xFF, 90.0f);
#endif
        dComIfGd_getXluList()->entryImm(&m0B70, 0x1F);
    }

    if (!isShipRide() && !fopAcM_CheckStatus(this, fopAcStts_CARRY_e) && checkStatus(daMdStts_UNK20000)) {
        cXyz shadowPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
        mShadowId = dComIfGd_setShadow(mShadowId, 0, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f, current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr);

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
    static const u32 l_harp_play_se[] = {
        JA_SE_CM_MD_HARP_CN4,
        JA_SE_CM_MD_HARP_DN4,
        JA_SE_CM_MD_HARP_EN4,
        JA_SE_CM_MD_HARP_FS4,
        JA_SE_CM_MD_HARP_GN4,
        JA_SE_CM_MD_HARP_CN4,
        JA_SE_CM_MD_HARP_DN4,
        JA_SE_CM_MD_HARP_EN4,
        JA_SE_CM_MD_HARP_FS4,
        JA_SE_CM_MD_HARP_GN4,
        JA_SE_CM_MD_HARP_GN4,
        JA_SE_CM_MD_HARP_GN4
    };

    u32 mtrlSndId = 0;
    if (((checkStatus(daMdStts_UNK20000)) && (mAcch.ChkGroundHit())) && (dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd))) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);
    }
    s8 sVar5 = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    m312A = sVar5;
    BOOL bVar3 = true;
    if ((dComIfGp_event_runCheck()) && (dComIfGp_evmng_startCheck(event_name_tbl[5]) != 0 || (dComIfGp_evmng_endCheck(event_name_tbl[5])))) {
        bVar3 = false;
    }
    if (((mType == 3) && (bVar3)) && (m3104 == 0x16 || (m3104 == 0x17))) {
        BOOL bVar2 = false;
        if (m3104 == 0x16) {
            if ((mpMorf->checkFrame(11.0f)) || (mpMorf->checkFrame(38.0f))) {
                bVar2 = true;
            }
        } else {
            if ((mpMorf->checkFrame(11.0f)) || (mpMorf->checkFrame(35.0f))) {
                bVar2 = true;
            }
        }
        if (bVar2) {
            if (m313E == 0) {
                int iVar1 = cLib_getRndValue(0, 10);
                m30F4 = l_harp_play_se[iVar1];
                m313E = 2;
            } else {
                m313E = m313E - 1;
            }
            fopAcM_monsSeStart(this, m30F4, &current.pos, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        }
    } else {
        m313E = 0;
    }
    if (mType != 7) {
        if (checkStatus(daMdStts_UNK1)) {
            mpWingMorf->play(NULL, 0, 0);
        } else {
            mpArmMorf->play(NULL, 0, 0);
        }
    } else {
        mpArmMorf->play(NULL, 0, 0);
    }
    if (mpMorf->getPlaySpeed() < 0.0f) {
        f32 f1 = mpMorf->getFrame();
        f32 f0 = m30D0;
        if (f0 < f1) {
            m312A = 1;
        }
    } else {
        f32 f1 = mpMorf->getFrame();
        f32 f0 = m30D0;
        if (f0 > f1) {
            m312A = 1;
        }
    }
    m30D0 = mpMorf->getFrame();
    if ((m312D == 0x1b) || (m312D == 0xf)) {
        if (m30D0 < 10.0f) {
            clearStatus(daMdStts_UNK80);
        } else {
            setBitStatus(daMdStts_UNK80);
        }
    }
    playTexPatternAnm();
    playLightBtkAnm();
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
    f32 fVar1;
    f32 fVar2;
    u8 uVar3;
    s16 target;
    cM3dGPla* pcVar5;
    J3DModel* pJVar12;
    int iStack_88;
    cXyz local_30;
    cXyz local_3c;

    clearStatus(daMdStts_UNK20000);
    m3140 = (isLightBodyHit()) ? TRUE : FALSE;
    fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
    checkPlayerRoom();
    cLib_calcTimer(&mDamageFogTimer);
    if (isShipRide()) {
        mJntCtrl.setParam(
            l_HIO.m074.m10,
            l_HIO.m074.m12,
            l_HIO.m074.m14,
            l_HIO.m074.m16,
            l_HIO.m074.m08,
            l_HIO.m074.m0A,
            l_HIO.m074.m0C,
            l_HIO.m074.m0E,
            l_HIO.mNpc.mMaxTurnStep
        );
    } else if (mType != 6) {
        if (!check_initialRoom()) {
            if (dComIfGp_getCb1Player() == this) {
                dComIfGp_setCb1Player(NULL);
            }
            return TRUE;
        }
        uVar3 = (mType) == 5 ? TRUE : FALSE;
        initialRestartOption(2, uVar3);
        if ((dComIfGp_getCb1Player() == this) && ((!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1620) || (mType == 7)) || (mType == 6))) {
            dComIfGp_setCb1Player(NULL);
        }
        fopAcM_setStageLayer(this);
        if (check_moveStop()) {
            if (mType != 7) {
                setNpcAction(&daNpc_Md_c::waitNpcAction);
                setAnm(0x30);
                animationPlay();
                setBaseMtx();
            }
            m312B = 0;
            return TRUE;
        }
        if (((m3131 != 0) && (dComIfG_Bgsp()->ChkPolySafe(mPolyInfo))) && (dComIfG_Bgsp()->ChkMoveBG(mPolyInfo))) {
            local_30 = old.pos;
            dComIfG_Bgsp()->MoveBgCrrPos(mPolyInfo, true, &old.pos, NULL, NULL);
        }
        mJntCtrl.setParam(
            l_HIO.mNpc.mMaxBackboneX,
            l_HIO.mNpc.mMaxBackboneY,
            l_HIO.mNpc.mMinBackboneX,
            l_HIO.mNpc.mMinBackboneY,
            l_HIO.mNpc.mMaxHeadX,
            l_HIO.mNpc.mMaxHeadY,
            l_HIO.mNpc.mMinHeadX,
            l_HIO.mNpc.mMinHeadY,
            l_HIO.mNpc.mMaxTurnStep
        );
    }
    if (mType == 6) {
        mAcch.CrrPos(*dComIfG_Bgsp());
        setBitStatus(daMdStts_UNK20000);
        if (mAcch.GetGroundH() != -G_CM3D_F_INF) {
            pcVar5 = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
            if (pcVar5 != NULL) {
                m32A4 = *pcVar5->GetNP();
            }
            s8 roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
            current.roomNo = roomNo;
            tevStr.mRoomNo = roomNo;
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
            mStts.SetRoomId(roomNo);
            mPolyInfo.SetPolyInfo(mAcch.m_gnd);
        }
    } else if (((!isShipRide()) && (!isReturnLink())) && (!fopAcM_CheckStatus(this, fopAcStts_CARRY_e))) {
        if (checkNowPosMove(l_staff_name)) {
            fVar1 = maxFallSpeed;
            fVar2 = speed.y;
            if (fVar1 < fVar2) {
                speed.y = fVar2 - gravity;
                if (speed.y < maxFallSpeed) {
                    speed.y = maxFallSpeed;
                }
            } else {
                if (fVar1 > fVar2) {
                    speed.y = fVar2 + gravity;
                    if (speed.y > maxFallSpeed) {
                        speed.y = maxFallSpeed;
                    }
                }
            }
            speed.x = speedF * cM_ssin(current.angle.y);
            speed.z = speedF * cM_scos(current.angle.y);
            fopAcM_posMove(this, mStts.GetCCMoveP());
        }
        if (checkStatus(daMdStts_UNK4)) {
            objWindHitCheck(&mCyl2);
        }
        mAcch.CrrPos(*dComIfG_Bgsp());
        setBitStatus(daMdStts_UNK20000);
        BOOL bVar10 = false;
        if ((mAcch.ChkWaterIn()) && (mAcch.m_wtr.GetHeight() > current.pos.y + 5.0f)) {
            if (m3074.getEmitter() == NULL) {
                dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &current.pos, NULL, NULL, 0xFF, &m3074);
            }
            m3074.setRate(0.0f);
            bVar10 = true;
        }
        if ((!bVar10) && (m3074.getEmitter() != NULL)) {
            m3074.remove();
        }
        if (!(mAcch.ChkGroundHit())) {
            if (chkPlayerAction(&daNpc_Md_c::walkPlayerAction) || (chkNpcAction(&daNpc_Md_c::searchNpcAction) || (chkNpcAction(&daNpc_Md_c::waitNpcAction)))) {
                f32 gndY = mAcch.GetGroundH();
                f32 delta = gndY - current.pos.y;
                if (((delta < 0.001f) && (delta >= -30.1f)) && (speed.y < 0.001f)) {
                    current.pos.y = gndY;
                    mAcch.SetGroundHit();
                    speed.y = 0.0f;
                }
            }
        }
        if (mAcch.GetGroundH() != -G_CM3D_F_INF) {
            pcVar5 = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
            if (pcVar5 != NULL) {
                m32A4 = *pcVar5->GetNP();
            }
            s8 roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
            current.roomNo = roomNo;
            tevStr.mRoomNo = roomNo;
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
            mStts.SetRoomId(roomNo);
            mPolyInfo.SetPolyInfo(mAcch.m_gnd);
        }
        if ((mAcch.ChkGroundHit()) && (m3131 == 0)) {
            dComIfGp_particle_setSimpleLand(mAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f, &tevStr, &iStack_88, 7);
        }
        m3131 = (mAcch.ChkGroundHit()) ? TRUE : FALSE;
        if ((mAcch.GetGroundH() == -G_CM3D_F_INF) || (dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd) == 4)) {
            if (!isFallAction()) {
                m4E8 = 0;
            } else if (m4E8 < 30) {
                m4E8++;
            } else if (!(dComIfGp_roomControl_checkStatusFlag(fopAcM_GetHomeRoomNo(this), 0x10))) {
                current.pos = home.pos;
                current.angle = home.angle;
                current.roomNo = home.roomNo;
                current.field_0x13 = home.field_0x13;
                shape_angle = home.angle;
                speedF = 0.0f;
                m4E8 = 0;
            } else {
                daPy_getPlayerLinkActorClass()->npcStartRestartRoom();
            }
        } else {
            m4E8 = 0;
        }
    }
    lightHitCheck();
    setCollision();
    if (checkNowPosMove(l_staff_name)) {
        animationPlay();
    }
    if (!eventProc()) {
        if (daPy_getPlayerActorClass() == this) {
            fopAcM_SetStatusMap(this, 0x11);
            if (isReturnLink()) {
                mCurEventMode = 0xc;
            } else {
                if (isNoCarryAction()) {
                    setPlayerAction(&daNpc_Md_c::carryPlayerAction);
                    returnLink();
                }
                playerAction(NULL);
                if (returnLinkCheck()) {
                    returnLink();
                } else {
                    checkCollision(1);
                }
            }
        } else {
            m313F = chkMoveBlock(&m30C4);
            if (m313F != 0) {
                setNpcAction(&daNpc_Md_c::escapeNpcAction);
            }
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1620)) {
                fopAcM_SetStatusMap(this, 0xC);
            } else {
                fopAcM_SetStatusMap(this, 0x8);
            }
            carryCheck();
            checkOrder();
            npcAction(NULL);
            checkCollision(0);
            if (!checkStatus(daMdStts_UNK2)) {
                if (checkStatus(daMdStts_UNK1)) {
                    target = shape_angle.y - current.angle.y;
                    if ((target < 0x6000) && (target > -0x6000)) {
                        if (target > 0x2000) {
                            target = 0x2000;
                        } else if (target < -0x2000) {
                            target = -0x2000;
                        }
                        cLib_addCalcAngleS(&shape_angle.z, target, 8, 0x2000, 0x400);
                        cLib_addCalcAngleS(&shape_angle.x, 0, 8, 0x2000, 0x400);
                    } else {
                        cLib_addCalcAngleS(&shape_angle.z, 0, 8, 0x2000, 0x400);
                        cLib_addCalcAngleS(&shape_angle.x, -0x2000, 8, 0x2000, 0x400);
                    }
                } else {
                    current.angle.y = shape_angle.y;
                }
            }
        }
    }
    eventOrder();
    setBaseMtx();
    pJVar12 = mpMorf->getModel();
    emitterTrace(m0508[0], pJVar12->getAnmMtx(m_neck_jnt_num), &current.angle);
    emitterTrace(m0508[1], pJVar12->getAnmMtx(m_neck_jnt_num), NULL);
    if (mType != 7) {
        pJVar12 = mpWingMorf->getModel();
        emitterTrace(m0508[2], pJVar12->getAnmMtx(m_wingR3_jnt_num), NULL);
        emitterTrace(m0508[3], pJVar12->getAnmMtx(m_wingL3_jnt_num), NULL);
        emitterTrace(m0508[4], pJVar12->getAnmMtx(m_wingR3_jnt_num), NULL);
        emitterTrace(m0508[5], pJVar12->getAnmMtx(m_wingL3_jnt_num), NULL);
        if ((m3135 & 1) != 0) {
            pJVar12 = mpWingMorf->getModel();
            local_3c.set(pJVar12->getAnmMtx(m_wingR2_jnt_num)[0][3], pJVar12->getAnmMtx(m_wingR2_jnt_num)[1][3], pJVar12->getAnmMtx(m_wingR2_jnt_num)[2][3]);
            dComIfGp_particle_set(dPa_name::ID_SCENE_819C, &local_3c, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this), &tevStr.mColorK0, &tevStr.mColorK0, NULL);
            local_3c.set(pJVar12->getAnmMtx(m_wingL2_jnt_num)[0][3], pJVar12->getAnmMtx(m_wingL2_jnt_num)[1][3], pJVar12->getAnmMtx(m_wingL2_jnt_num)[2][3]);
            dComIfGp_particle_set(dPa_name::ID_SCENE_819C, &local_3c, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this), &tevStr.mColorK0, &tevStr.mColorK0, NULL);
        }
    }
    m3135 = 0;
    return TRUE;
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
    JGeometry::TVec3<f32> pos(mtx[0][3], mtx[1][3], mtx[2][3]);
    emitter->setGlobalTranslation(pos);
    if (angle) {
        JGeometry::TVec3<s16> rot(angle->x, angle->y, angle->z);
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
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    m_flying = false;
    m_mirror = false;
    m_playerRoom = false;
}

/* 000110BC-000110DC       .text daNpc_Md_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Md_Create(fopAc_ac_c* i_this) {
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
    JGeometry::TVec3<s16> rot(mAngle.x, mAngle.y, mAngle.z);
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
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_MD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Md_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_MD,
    /* Actor SubMtd */ &l_daNpc_Md_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK2000000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
