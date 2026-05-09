/**
 * d_a_npc_so.cpp
 * NPC - Fishman (blue fish)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_so.h"
#include "d/d_npc.h"
#include "d/d_procname.h"
#include "d/d_snap.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_tag_so.h"
#include "d/actor/d_a_esa.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_camera.h"
#include "d/res/res_so.h"

class daNpc_So_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_So_HIO_c();
    virtual ~daNpc_So_HIO_c() {}

public:
    /* 0x08 */ dNpc_HIO_c mNpc;
    /* 0x2C */ u8 m2C;
    /* 0x2D */ u8 m2D;
    /* 0x2E */ u8 m2E;
    /* 0x2F */ u8 m2F;
    /* 0x30 */ u8 m30;
    /* 0x31 */ u8 m31;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ f32 m54;
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
    /* 0x60 */ f32 m60;
    /* 0x64 */ s16 m64;
    /* 0x66 */ s16 m66;
    /* 0x68 */ s16 m68;
    /* 0x6A */ s16 m6A;
    /* 0x6C */ f32 m6C;
    /* 0x70 */ f32 m70;
    /* 0x74 */ f32 m74;
    /* 0x78 */ f32 m78;
    /* 0x7C */ s16 m7C;
    /* 0x80 */ f32 m80;
    /* 0x84 */ f32 m84;
    /* 0x88 */ f32 m88;
    /* 0x8C */ f32 m8C;
    /* 0x90 */ f32 m90;
    /* 0x94 */ u8 m94;
    /* 0x98 */ JntHit_HIO_c jntHit;
}; // size = 0xC4

static daNpc_So_HIO_c l_HIO;

const s32 daNpc_So_c::m_heapsize = DEMO_SELECT(0x1CC0, 0x1C00);
const char daNpc_So_c::m_arc_name[] = "So";
const dCcD_SrcSph daNpc_So_c::m_sph_src = {
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

/* 000000EC-000002A4       .text __ct__14daNpc_So_HIO_cFv */
daNpc_So_HIO_c::daNpc_So_HIO_c() {
    m2C = 0;
    m2D = 0;
    m2E = 0;
    m2F = 0;
    m30 = 0;
    m31 = 0;
    m34 = 3.0f;
    m38 = 0.9f;
    m3C = 100.0f;
    m40 = 2000.0f;
    m54 = 20000.0f;
    m5C = 30.0f;
    m44 = 0.7f;
    m48 = 2000.0f;
    m4C = 2.0f;
    m50 = 150.0f;
    m64 = 8000;
    m66 = 4000;
    m68 = 0xE0C0;
    m6A = 0xF060;
    m6C = 10.0f;

    mNpc.m04 = -33.0f;
    mNpc.mMaxHeadX = 0x1ffe;
    mNpc.mMaxHeadY = 0x1000;
    mNpc.mMaxBackboneX = 0x1000;
    mNpc.mMaxBackboneY = 0x2000;
    mNpc.mMinHeadX = -3000;
    mNpc.mMinHeadY = -0x1000;
    mNpc.mMinBackboneX = -0x1000;
    mNpc.mMinBackboneY = -0x2000;
    mNpc.mMaxTurnStep = 0x250;
    mNpc.mMaxHeadTurnVel = 0x150;
    mNpc.mAttnYOffset = 50.0f;
    mNpc.mMaxAttnAngleY = 0x7fff;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0f;

    m58 = 250.0f;
    m60 = 700.0f;
    m70 = 600.0f;
    m74 = 300.0f;
    m78 = 100.0f;
    m7C = 5;
    m80 = -1.4f;
    m84 = 18.0f;
    m88 = 120.0f;
    m8C = 300.0f;
    m90 = 15.0f;
    m94 = 0;
}

/* 000002A4-000002D0       .text searchEsa_CB__FPvPv */
static void* searchEsa_CB(void* arg1, void* i_this) {
    daNpc_So_c* a_this = static_cast<daNpc_So_c*>(i_this);
    fopAc_ac_c* ac = static_cast<fopAc_ac_c*>(arg1);
    return a_this->_searchEsa(ac);
}

/* 000002D0-000002F8       .text _searchEsa__10daNpc_So_cFP10fopAc_ac_c */
void* daNpc_So_c::_searchEsa(fopAc_ac_c* arg1) {
    if (fopAcM_GetName(arg1) == PROC_ESA) {
        esa_class* esa = static_cast<esa_class*>(arg1);
        if (esa->field_0x298 == 0) {
            return esa;
        }
    }
    return NULL;
}

/* 000002F8-00000344       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* pNode, int calcTiming) {
    J3DJoint* pJnt = static_cast<J3DJoint*>(pNode);

    if (calcTiming == J3DNodeCBCalcTiming_In) {
        daNpc_So_c* i_this = (daNpc_So_c*)j3dSys.getModel()->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeControl(pJnt, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000344-00000474       .text _nodeControl__10daNpc_So_cFP7J3DNodeP8J3DModel */
void daNpc_So_c::_nodeControl(J3DNode* pNode, J3DModel* pModel) {
    J3DJoint* pJnt = static_cast<J3DJoint*>(pNode);
    s32 jntNo = pJnt->getJntNo();

    mDoMtx_stack_c::copy(pModel->getAnmMtx(jntNo));
    if (jntNo == m_jnt.getHeadJntNum()) {
        cXyz local_2C(0.0f, 0.0f, 0.0f);
        cXyz local_38(24.0f, -16.0f, 0.0f);
        local_38.y += DEMO_SELECT(REG12_F(1), 0.0f);

        mDoMtx_stack_c::multVec(&local_2C, &mB60);
        if (DEMO_SELECT(REG12_S(1) != 0, false)) {
            mDoMtx_stack_c::XrotM(REG12_S(2));
            mDoMtx_stack_c::YrotM(REG12_S(3));
            mDoMtx_stack_c::ZrotM(REG12_S(4));
        } else {
            mDoMtx_stack_c::YrotM((s16)m_jnt.getHead_y());
            mDoMtx_stack_c::ZrotM((s16)m_jnt.getHead_x());
        }
        mDoMtx_stack_c::multVec(&local_38, &mB54);
    } else if (jntNo == m_jnt.getBackboneJntNum()) {
        if (DEMO_SELECT(REG12_S(0) != 0, false)) {
            mDoMtx_stack_c::XrotM(REG12_S(2));
            mDoMtx_stack_c::YrotM(REG12_S(3));
            mDoMtx_stack_c::ZrotM(REG12_S(4));
        } else {
            mDoMtx_stack_c::XrotM((s16)m_jnt.getBackbone_y());
            mDoMtx_stack_c::ZrotM((s16)m_jnt.getBackbone_x());
        }
    }

    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    pModel->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 000004B0-000004DC       .text searchTagSo_CB__FPvPv */
static void* searchTagSo_CB(void* arg1, void* i_this) {
    daNpc_So_c* a_this = static_cast<daNpc_So_c*>(i_this);
    fopAc_ac_c* ac = static_cast<fopAc_ac_c*>(arg1);
    return a_this->_searchTagSo(ac);
}

/* 000004DC-0000054C       .text _searchTagSo__10daNpc_So_cFP10fopAc_ac_c */
void* daNpc_So_c::_searchTagSo(fopAc_ac_c* arg1) {
    if (fopAcM_GetName(arg1) == PROC_TAG_SO) {
        daTag_So_c* tag_so = static_cast<daTag_So_c*>(arg1);
        u8 tmp = tag_so->m290;
        if (mA79 == tmp && tag_so->m298 != 1) {
            mA7C = tag_so->mRadius;
            mA80 = tag_so->current.pos;
            current.pos = mA80;
            return arg1;
        }
    }
    return NULL;
}

/* 0000054C-00000578       .text searchMinigameTagSo_CB__FPvPv */
void* searchMinigameTagSo_CB(void* arg1, void* i_this) {
    daNpc_So_c* a_this = static_cast<daNpc_So_c*>(i_this);
    fopAc_ac_c* ac = static_cast<fopAc_ac_c*>(arg1);
    return a_this->_searchMinigameTagSo(ac);
}

/* 00000578-000005C8       .text _searchMinigameTagSo__10daNpc_So_cFP10fopAc_ac_c */
void* daNpc_So_c::_searchMinigameTagSo(fopAc_ac_c* arg1) {
    if (fopAcM_GetName(arg1) == PROC_TAG_SO) {
        daTag_So_c* tag_so = static_cast<daTag_So_c*>(arg1);
        if (tag_so->m298 == 1) {
            mB90 = tag_so->current.pos;
            mB9C = tag_so->shape_angle.y;
            mBAE = 1;
            return arg1;
        }
    }
    return NULL;
}

/* 000005C8-000005E8       .text daNpc_So_XyCheckCB__FPvi */
static s16 daNpc_So_XyCheckCB(void* i_this, int arg2) {
    daNpc_So_c* a_this = static_cast<daNpc_So_c*>(i_this);
    return a_this->XyCheckCB(arg2);
}

/* 000005E8-00000680       .text XyCheckCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyCheckCB(int arg1) {
    fopAc_ac_c* pfVar1 = fopAcM_Search(searchEsa_CB, this);

    if (pfVar1 != NULL) {
        return 0;
    }

    if (m6D3 != 2) {
        return 0;
    }

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && dComIfGp_getSelectItem(arg1) == dItem_BIRD_BAIT_5_e) {
        return 1;
    }

    return 0;
}

/* 00000680-000006A0       .text daNpc_So_XyEventCB__FPvi */
static s16 daNpc_So_XyEventCB(void* i_this, int arg2) {
    daNpc_So_c* a_this = static_cast<daNpc_So_c*>(i_this);
    return a_this->XyEventCB(arg2);
}

/* 000006A0-000006EC       .text XyEventCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyEventCB(int) {
    mBDC = dComIfGp_evmng_getEventIdx("SO_ESA_XY");
    return mBDC;
}

/* 000006EC-0000070C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    daNpc_So_c* a_this = static_cast<daNpc_So_c*>(i_this);
    return a_this->_createHeap();
}

/* 0000070C-00000A20       .text _createHeap__10daNpc_So_cFv */
BOOL daNpc_So_c::_createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, SO_BDL_SO));
    JUT_ASSERT(DEMO_SELECT(537, 509), modelData != NULL);

    mpMorf = new mDoExt_McaMorf(modelData, NULL, NULL, NULL, ~J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022);
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    mpMorf->getModel()->setUserArea(reinterpret_cast<u32>(this));

#if VERSION > EVRSION_DEMO
    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes(m_arc_name, SO_BTP_SO));
    JUT_ASSERT(528, btp != NULL);

    if (!mBtpAnm.init(modelData, btp, 1, 0, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
#endif

    m_jnt.setHeadJntNum(11);
    JUT_ASSERT(DEMO_SELECT(556, 533), m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(1);
    JUT_ASSERT(DEMO_SELECT(558, 535), m_jnt.getBackboneJntNum() >= 0);

    modelData->getJointTree().getJointNodePointer(11)->setCallBack(nodeControl_CB);
    modelData->getJointTree().getJointNodePointer(1)->setCallBack(nodeControl_CB);

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, SO_BDL_SO_FUDE);
    JUT_ASSERT(DEMO_SELECT(568, 545), modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpModel == NULL) {
        return FALSE;
    }

    if (!jntHitCreateHeap()) {
        return FALSE;
    }

    return TRUE;
}

/* 00000A20-00000A84       .text jntHitCreateHeap__10daNpc_So_cFv */
bool daNpc_So_c::jntHitCreateHeap() {
    static int sph_offset[] = {0, 0, 0};
    static Vec cyl_offset_A[] = {
        {
            20.0f,
            -10.0f,
            0.0f,
        },
        {
            -20.0f,
            -10.0f,
            0.0f,
        },
    };
    static Vec cyl_offset_B[] = {
        {
            15.0f,
            0.0f,
            0.0f,
        },
        {
            -15.0f,
            0.0f,
            0.0f,
        },
    };

#if VERSION == VERSION_DEMO
    static __jnt_hit_data_c search_data[] = {
        {
            JntHitType_CYL_e,
            1,
            20.0f,
            cyl_offset_A,
        },
        {
            JntHitType_CYL_e,
            2,
            2.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            3,
            2.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            4,
            2.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            6,
            2.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            7,
            2.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            8,
            2.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            17,
            15.0f,
            cyl_offset_A,
        },
        {
            JntHitType_CYL_e,
            18,
            15.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            19,
            5.0f,
            cyl_offset_B,
        },
    };
#else
    static __jnt_hit_data_c search_data[] = {
        {
            JntHitType_CYL_e,
            4,
            2.0f,
            cyl_offset_B,
        },
        {
            JntHitType_CYL_e,
            8,
            2.0f,
            cyl_offset_B,
        },
    };
#endif

    mJntHit = JntHit_create(mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (mJntHit != NULL) {
        jntHit = mJntHit;
    } else {
        return false;
    }
    return true;
}

#include "d/actor/d_a_npc_so_cut.inc"

/* 00000A84-00000C8C       .text checkTgHit__10daNpc_So_cFv */
bool daNpc_So_c::checkTgHit() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    bool ret;

    mStts2.Move();
    if (cLib_calcTimer(&m6D8) == 0 && mSph.ChkTgHit()) {
        cXyz* pPos = mSph.GetTgHitPosP();
        cCcD_Obj* pcVar3 = mSph.GetTgHitObj();
        m6D8 = l_HIO.m7C;

        if (pcVar3 == NULL) {
            ret = FALSE;
        } else {
            switch (pcVar3->GetAtType()) {
            case AT_TYPE_NORMAL_ARROW:
                fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x20);
                break;
            }

            bool tmp = true;
            if (tmp) {
#if VERSION > VERSION_DEMO
                fopAcM_monsSeStart(this, JA_SE_CV_SO_DAMAGE, 0);
#endif
                dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, pPos);
                cXyz local_28(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, pPos, &player->shape_angle, &local_28);

                fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);
            }
            ret = true;
        }
    } else {
        ret = false;
    }

    return ret;
}

/* 00000C8C-00000CB0       .text offsetZero__10daNpc_So_cFv */
void daNpc_So_c::offsetZero() {
    mB38.z = 0.1f;
    mB38.y = 20.0f;
    mB38.x = -1.0f;
}

/* 00000CB0-00000CD4       .text offsetDive__10daNpc_So_cFv */
void daNpc_So_c::offsetDive() {
    mB38.z = 0.3f;
    mB38.y = 10.0f;
    mB38.x = -150.0f;
}

/* 00000CD4-00000CF8       .text offsetSwim__10daNpc_So_cFv */
void daNpc_So_c::offsetSwim() {
    mB38.z = 0.3f;
    mB38.y = 10.0f;
    mB38.x = -40.0f;
}

/* 00000CF8-00000D1C       .text offsetAppear__10daNpc_So_cFv */
void daNpc_So_c::offsetAppear() {
    mB38.z = 0.4f;
    mB38.y = 22.0f;
    mB38.x = DEMO_SELECT(110.0f + REG12_F(0), 110.0f);
}

/* 00000D1C-00000E40       .text getMsg__10daNpc_So_cFv */
u32 daNpc_So_c::getMsg() {
    if (mB0C) {
        if (l_HIO.m2E || DEMO_SELECT(mB7C == 10, mB7C >= 10)) {
            if (mBD9) {
                return 0x32E2;
            } else {
                return 0x32DD;
            }
        } else {
            if (mB7C == 0) {
                return 0x32E1;
            } else if (mB7C == 1) {
                return 0x32E0;
            } else {
                dComIfGp_setMessageCountNumber(mB7C);
                return 0x32DF;
            }
        }
    } else {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0901) && strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
            fopAcM_GetRoomNo(this) == dIsleRoom_DragonRoostIsland_e)
        {
            if (mBD8) {
                return m6D0;
            } else {
                return 0x32CA;
            }
        } else if (mBD8) {
            return m6D0;
        }
    }
    return 0x32d0;
}

/* 00000E40-00001214       .text next_msgStatus__10daNpc_So_cFPUl */
u16 daNpc_So_c::next_msgStatus(u32* param_1) {
    u16 ret = 0xF;

    if (*param_1 == m6D0) {
        if (mBD8) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0901) && strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
                fopAcM_GetRoomNo(this) == dIsleRoom_DragonRoostIsland_e)
            {
                *param_1 = 0x32CE;
            } else {
                *param_1 = 0x32D2;
            }
        } else {
            *param_1 = 0x32D6;
        }

        return ret;
    }

    switch (*param_1) {
    case 0x32CA:
        *param_1 = 0x32CB;

        break;
    case 0x32CB:
        *param_1 = 0x32CC;

        break;

    case 0x32CC:
        *param_1 = 0x32CD;
        break;

    case 0x32CE:
        ret = 0x10;
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_EVENT_FIRST_END_e);
        break;

    case 0x32D0:
        if (dComIfGs_isSaveArriveGrid(fopAcM_GetRoomNo(this) - 1) || l_HIO.m2F != 0) {
            *param_1 = 0x32D4;
            break;
        }
        *param_1 = 0x32D1;
        break;

    case 0x32CD:
    case 0x32D1:
        ret = 0x10;
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_EVENT_MAPOPEN_e);
        break;

    case 0x32D4:
        *param_1 = m6D0;
        break;

    case 0x32D2:
        *param_1 = 0x32D3;
        break;

    case 0x32D6:
        fopAcM_Search(searchMinigameTagSo_CB, this);

        if (l_HIO.m30 != 0 || mBAE != 0) {
            if (dComIfGs_getItem(dInvSlot_BOW_e) != dInvSlot_NONE_e && dComIfG_getTimerPtr() == NULL) {
#if VERSION > VERSION_DEMO
                if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A10)) {
                    *param_1 = 0x32D8;
                    break;
                }
#endif
                *param_1 = DEMO_SELECT(dLib_setFirstMsg(0x3A10, 0x32D8, 0x32DC), 0x32DC);
                break;
            }
            *param_1 = 0x32D7;
            break;
        } else {
            *param_1 = 0x32D7;
            break;
        }

    case 0x32D8:
        if (mpCurrMsg->mSelectNum == 0) {
            *param_1 = 0x32DA;
            break;
        }
        *param_1 = 0x32D9;
        break;

    case 0x32DC:
        if (mpCurrMsg->mSelectNum == 0) {
            *param_1 = 0x32DB;
            break;
        }
        *param_1 = 0x32D9;
        break;

    case 0x32DA:
        *param_1 = 0x32DB;
        break;

    case 0x32DB:
        ret = 0x10;
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_EVENT_BOW_e);
        break;

    case 0x32DD:
        *param_1 = 0x32DE;
        break;

    case 0x32DE:
        ret = 0x10;
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_GET_RUPEE_e);
        break;

    case 0x32DF:
    case 0x32E0:
        dComIfGp_setItemRupeeCount(mB7C * 10);
        *param_1 = 0x32E2;
        break;

    case 0x32E1:
        *param_1 = 0x32E2;
        break;

    case 0x633:
        if (dComIfGs_getTriforceNum() == 8) {
            *param_1 = 0x635;
            break;
        }
        *param_1 = 0x634;
        break;

    case 0x32D9:
        *param_1 = 0x32D7;
        break;

    default:
        ret = 0x10;
        break;
    }

    return ret;
}

/* 00001214-000013A0       .text lookBack__10daNpc_So_cFv */
void daNpc_So_c::lookBack() {
#if VERSION > VERSION_DEMO
    if (dComIfGp_event_runCheck()) {
#endif
        if (mEventCut.getAttnFlag()) {
            if (m6D3 == 4) {
                m_jnt.clrTrn();
            } else {
                m_jnt.setTrn();
                mB44 = mEventCut.getAttnPos();
            }
        } else {
            mB44 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        }
#if VERSION > VERSION_DEMO
    } else {
#if VERSION > VERSION_JPN
        m_jnt.clrTrn();
#endif
        mB44 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    }
#endif

    if (m_jnt.trnChk()) {
        s16 target = l_HIO.mNpc.mMaxHeadTurnVel;
        if (mEventCut.getTurnSpeed() != 0) {
            target = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&mB50, target, 4, 0x800);
    } else {
        mB50 = 0;
    }

    cXyz tmp = mB54;
    tmp.y += 200.0f + DEMO_SELECT(REG12_F(0), 0.0f);
    m_jnt.lookAtTarget(&shape_angle.y, &mB44, tmp, shape_angle.y, mB50, mBDA);
}

/* 000013A0-00001430       .text setAttention__10daNpc_So_cFv */
void daNpc_So_c::setAttention() {
    attention_info.position = mB60;
    attention_info.position.y += l_HIO.mNpc.mAttnYOffset;

    f32 dVar1 = dLib_getWaterY(attention_info.position, mAcch);
    if (attention_info.position.y <= dVar1) {
        attention_info.position.y = dVar1;
    }

    eyePos = mB54;
}

/* 00001430-00001524       .text setAnm__10daNpc_So_cFScb */
void daNpc_So_c::setAnm(signed char arg1, bool arg2) {
    static const int a_anm_bcks_tbl[] = {SO_BCK_SO_WAIT01, SO_BCK_SO_SWIM01, SO_BCK_SO_TALK01, SO_BCK_SO_JUMP, SO_BCK_SO_TALK02};
    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

#if VERSION == VERSION_DEMO
    if (REG12_S(6) != 0) {
        arg1 = REG12_S(7);
    }
#endif

    if (arg1 != 6) {
        m6D3 = arg1;
    }

    if (mpMorf->getFrame() >= mpMorf->getEndFrame() - 1.0f && cM_rndF(100.0f) < l_HIO.m5C) {
        if (m6D3 == 5) {
            m6D3 = 3;
        } else if (m6D3 == 3) {
            m6D3 = 5;
        }
    }

    dLib_bcks_setAnm(m_arc_name, mpMorf, &m6D2, &m6D3, &m6D4, a_anm_bcks_tbl, a_anm_prm_tbl, arg2);
}

/* 00001524-00001644       .text setAnmSwimSpeed__10daNpc_So_cFv */
void daNpc_So_c::setAnmSwimSpeed() {
    if (m6D3 == 2) {
        f32 abs = (current.pos - old.pos).abs() / (10.0f + DEMO_SELECT(REG12_F(6), 0.0f));

        f32 fVar1;
        if (abs <= 0.0f) {
            fVar1 = 0.0f;
        } else if (abs >= 1.0f) {
            fVar1 = 1.0;
        } else {
            fVar1 = abs;
        }

        fVar1 *= l_HIO.m34;
        if (fVar1 < l_HIO.m38) {
            fVar1 = l_HIO.m38;
        } else {
            fVar1 = fVar1;
        }

        mpMorf->setPlaySpeed(fVar1);
    }
}

/* 00001644-000016E8       .text setMtx__10daNpc_So_cFv */
void daNpc_So_c::setMtx() {
    J3DModel* pJVar1 = mpMorf->getModel();

    pJVar1->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::transM(0.0f, mB34, 0.0f);
    pJVar1->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000016E8-00001718       .text modeWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeWaitInit() {
    fopAcM_SetSpeedF(this, 0.0f);
    mAFC = 0.0f;
    offsetAppear();
}

/* 00001718-0000171C       .text modeWait__10daNpc_So_cFv */
void daNpc_So_c::modeWait() {
}

/* 0000171C-0000175C       .text modeHideInit__10daNpc_So_cFv */
void daNpc_So_c::modeHideInit() {
#if VERSION == VERSION_DEMO
    offsetDive();
#else
    mBDB = 1;
    offsetDive();
    mA7C = 0.0f;
#endif
}

/* 0000175C-00001778       .text modeHide__10daNpc_So_cFv */
void daNpc_So_c::modeHide() {
    current.pos = mA80;
}

/* 00001778-00001880       .text modeJumpInit__10daNpc_So_cFv */
void daNpc_So_c::modeJumpInit() {
    mAFC = (cM_rndF(5.0f) + 5.0f) * mB08;
    fopAcM_SetSpeedF(this, mAFC);
    speed.y = mB08 * 30.0f + speedF * 4.0f;

    if (speed.y > l_HIO.m50) {
        speed.y = l_HIO.m50;
    }

    mB00 = speed.y;
    shape_angle.x = l_HIO.m68;
    setAnm(4, false);
    m_jnt.onBackBoneLock();

    fopAcM_seStart(this, JA_SE_CM_SO_JUMP_L, 0);
}

/* 00001880-000019F0       .text modeJump__10daNpc_So_cFv */
void daNpc_So_c::modeJump() {
    if (current.pos.y < dLib_getWaterY(current.pos, mAcch)) {
        fopAcM_seStart(this, JA_SE_CM_SO_LANDING_L, 0);

        fopKyM_createWpillar(fopAcM_GetPosition_p(this), scale.x * 1.4f, 1.4f, 0);

#if VERSION > VERSION_DEMO
        f32 abs = (mA80 - current.pos).absXZ();
        if (abs > mA7C) {
            current.pos = mA80;
        }
#endif

        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_SWIM_e);
    }
}

/* 000019F0-00001A6C       .text modeSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeSwimInit() {
#if VERSION > VERSION_DEMO
    attention_info.flags = fopAc_Attn_TALKFLAG_NOTALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
#endif

    mA90 = cM_rndF(90.0f) + 30.0f + DEMO_SELECT(REG12_F(1), 0.0f);
    setAnm(2, false);

#if VERSION == VERSION_DEMO
    offsetSwim();
    m_jnt.onBackBoneLock();
#else
    m_jnt.onBackBoneLock();
    offsetDive();
#endif
}

/* 00001A6C-00001DB8       .text modeSwim__10daNpc_So_cFv */
void daNpc_So_c::modeSwim() {
    mBDB = 0;

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 abs = (player->current.pos - mA80).absXZ();

    daShip_c* ship = dComIfGp_getShipActor();

    if (ship != NULL) {
        cLib_addCalc2(&mB10.mRadius, 200.0f, 0.1f, 10.0f);
        mB10.mWobbleAmplitude = 50.0f;
        mB10.mAngleSpeed = 0x150;
        mB10.mTranslation = mA80;

        mB10.mTranslation.y = dLib_getWaterY(mB10.mTranslation, mAcch);
        dLib_setCirclePath(&mB10);
        mB10.mPos.y = dLib_getWaterY(mB10.mPos, mAcch);
        mB10.mPos.y += mB34;

        f32 abs2 = (current.pos - mB10.mPos).absXZ();
        if (abs2 > 150.0f + DEMO_SELECT(REG12_F(7), 0.0f) || fopAcM_GetSpeedF(ship) > 10.0f) {
            mAFC = 12.0f + DEMO_SELECT(REG12_F(10), 0.0f);
            s16 target = cLib_targetAngleY(fopAcM_GetPosition_p(this), &mB10.mPos);
            cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);
            mB04 = 0.0f;
        } else {
            cLib_addCalc2(&mB04, 1.0f, 0.01f, 0.05f);
            cXyz local_50 = mB10.mPos - current.pos;

            current.pos = current.pos + local_50 * mB04;
            cLib_addCalcAngleS2(&shape_angle.y, mB10.mAngle + 0x8000, 4, 0x400);
        }

        if (abs < mA7C && dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_NEAR_SWIM_e);
        } else if (cLib_calcTimer(&mA90) == 0) {
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_JUMP_e);
        }
    }
}

/* 00001DB8-00001DFC       .text modeNearSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwimInit() {
    setAnm(2, false);
    offsetDive();
    m_jnt.onBackBoneLock();
}

/* 00001DFC-00002144       .text modeNearSwim__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwim() {
    dCam_getBody()->SetTypeForce("BoatBattle", NULL);
    mB70 = 2;

    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();

    if (ship != NULL) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        f32 abs1 = (player->current.pos - mA80).absXZ();

        cLib_addCalc2(&mB10.mRadius, 400.0f, 0.1f, 10.0f);
        mB10.mWobbleAmplitude = 50.0f;
        mB10.mAngleSpeed = 0x100;
        mB10.mTranslation = player->current.pos;
        mB10.mTranslation.y = dLib_getWaterY(mB10.mTranslation, mAcch);
        dLib_setCirclePath(&mB10);
        mB10.mPos.y = dLib_getWaterY(mB10.mPos, mAcch);
        mB10.mPos.y += mB34;

        f32 abs2 = (current.pos - mB10.mPos).absXZ();

        if (abs2 > 150.0f + DEMO_SELECT(REG12_F(7), 0.0f) || fopAcM_GetSpeedF(ship) > 10.0f) {
            mAFC = 12.0f + DEMO_SELECT(REG12_F(11), 0.0f);
            s16 target = cLib_targetAngleY(fopAcM_GetPosition_p(this), &mB10.mPos);
            cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);
            mB04 = 0.0f;
            current.pos.y += mB34;
        } else {
            cLib_addCalc2(&mB04, 1.0f, 0.01f, 0.05f);

            cXyz local_50 = mB10.mPos - current.pos;
            current.pos = current.pos + local_50 * mB04;

            cLib_addCalcAngleS2(&shape_angle.y, mB10.mAngle + 0x8000, 4, 0x400);
            current.pos.y += mB34;
        }

        if (abs1 >= mA7C) {
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_SWIM_e);
        }
    }
}

/* 00002144-0000217C       .text modeEventFirstWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWaitInit() {
    mA90 = 150;
    mAFC = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    offsetDive();
}

/* 0000217C-000022D0       .text modeEventFirstWait__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWait() {
    daShip_c* ship = dComIfGp_getShipActor();

    if (ship != NULL) {
        current.pos = ship->current.pos;
        f32 abs = (ship->current.pos - mAAC).absXZ();

        if (abs >= l_HIO.m54 && dComIfGs_checkGetItem(NORMAL_SAIL)) {
            if (dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC) && dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_EVENT_FIRST_e);
            }
        }
    }
}

/* 000022D0-00002314       .text modeEventFirstInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstInit() {
    offsetSwim();
    mAFC = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    m_jnt.offBackBoneLock();
}

/* 00002314-000023C8       .text modeEventFirst__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirst() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        if (dComIfGp_evmng_endCheck("SO_1ST_MEET")) {
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
            mB70 = 1;
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_TALK_e);
            attention_info.flags = fopAc_Attn_TALKFLAG_NOTALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
        }
    } else {
        mB70 = 3;
    }
}

/* 000023C8-0000240C       .text modeEventFirstEndInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEndInit() {
    offsetAppear();
    mAFC = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    m_jnt.offBackBoneLock();
}

/* 0000240C-000024C0       .text modeEventFirstEnd__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEnd() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        if (dComIfGp_evmng_endCheck("SO_1ST_MEET_END")) {
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_DISAPPEAR_e);
        }
    } else if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        mB70 = 4;
    }
}

/* 000024C0-00002504       .text modeEventEsaInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsaInit() {
    offsetSwim();
    mAFC = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    m_jnt.offBackBoneLock();
}

/* 00002504-00002594       .text modeEventEsa__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsa() {
    if (!mEventCut.cutProc()) {
        cutProc();
    }

    if (dComIfGp_evmng_endCheck(mBDC)) {
        dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
        mBDC = -1;
        mB70 = 1;
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_TALK_e);
    }
}

/* 00002594-000025B0       .text modeEventMapopenInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopenInit() {
    mAFC = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    m_jnt.offBackBoneLock();
}

/* 000025B0-00002670       .text modeEventMapopen__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopen() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        if (dComIfGp_evmng_endCheck("SO_MAPOPEN")) {
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
            mB70 = 1;
            mBD8 = true;
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_TALK_e);
        }
    } else if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        mB70 = 5;
    }
}

/* 00002670-000026B4       .text modeEventBowInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventBowInit() {
    offsetSwim();
    mAFC = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    m_jnt.offBackBoneLock();
}

/* 000026B4-000027F8       .text modeEventBow__10daNpc_So_cFv */
void daNpc_So_c::modeEventBow() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        if (dComIfGp_evmng_endCheck("SO_BOW")) {
            mB0C = true;
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
            mBDB = 0;

#if VERSION > VERSION_DEMO
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3A10);
#endif

            camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
            camera->mCamera.Reset(mBCC, mBC0);
            camera->mCamera.Start();

            mB70 = 1;
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_TALK_e);
        }
    } else if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        mB70 = 6;
    }
}

/* 000027F8-0000283C       .text modeTalkInit__10daNpc_So_cFv */
void daNpc_So_c::modeTalkInit() {
    offsetAppear();
    setAnm(3, false);
    m_jnt.offBackBoneLock();
}

/* 0000283C-0000289C       .text modeTalk__10daNpc_So_cFv */
void daNpc_So_c::modeTalk() {
    if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
#if VERSION == VERSION_DEMO
        if (mBD8 || mB0C || dComIfGs_isSaveArriveGrid(fopAcM_GetRoomNo(this) - 1)) {
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_DISAPPEAR_e);
        } else {
            modeProc(daNpc_So_c::PROC_INIT_e, DEMO_SELECT(daNpc_So_c::MODE_WAIT_e, daNpc_So_c::MODE_DISAPPEAR_e));
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
        }
#else
        dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
        modeProc(daNpc_So_c::PROC_INIT_e, DEMO_SELECT(daNpc_So_c::MODE_WAIT_e, daNpc_So_c::MODE_DISAPPEAR_e));
#endif
    }
}

/* 0000289C-0000296C       .text modeDisappearInit__10daNpc_So_cFv */
void daNpc_So_c::modeDisappearInit() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0901)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0901);
    }

    offsetDive();

    fopAcM_seStart(this, JA_SE_CM_SO_DIVE, 0);
    fopKyM_createWpillar(fopAcM_GetPosition_p(this), scale.x * 1.2f, 1.4f, 0);
    m_jnt.offBackBoneLock();
}

/* 0000296C-00002A90       .text modeDisappear__10daNpc_So_cFv */
void daNpc_So_c::modeDisappear() {
    if (std::abs(mB34 - mB38.x) < 10.0f) {
        fopAc_ac_c* pfVar2;
        s32 uVar1 = mA79;

        do {
            do {
                mA79 = cM_rndF(4.9f);
            } while (mA79 == uVar1);

            pfVar2 = fopAcM_Search(searchTagSo_CB, this);
        } while (pfVar2 == NULL);

        current.pos = pfVar2->current.pos;
        mB74 = 0;
        mB78 = 0;
        mB7C = 0;
        mB80 = 0;
        mB84 = 0;
        mB88 = 0.0f;
        mB8C = 0.0f;
        mB90.setall(0.0f);
        mB9C = 0;
        mBA0.setall(0.0f);
        mBAC = 0;
        mB0C = false;
        mBD9 = false;
        mBD8 = false;
        mBDB = 1;

        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_HIDE_e);

#if VERSION == VERSION_DEMO
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_SWIM_e);
#elif VERSION > VERSION_JPN
        gravity = -2.5f;
#endif
    }
}

/* 00002A90-00002B60       .text modeDebugInit__10daNpc_So_cFv */
void daNpc_So_c::modeDebugInit() {
    fopAcM_SetSpeedF(this, 0.0f);
    mAFC = 0.0f;
    setAnm(1, false);

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz tmp = player->current.pos;
    tmp.x += cM_scos(player->shape_angle.y) * 100.0f;
    tmp.z += cM_ssin(player->shape_angle.y) * 100.0f;
    current.pos = tmp;

    offsetAppear();
}

/* 00002B60-00002B64       .text modeDebug__10daNpc_So_cFv */
void daNpc_So_c::modeDebug() {
}

/* 00002B64-00002B68       .text modeGetRupeeInit__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupeeInit() {
}

/* 00002B68-00002C6C       .text modeGetRupee__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupee() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        if (dComIfGp_evmng_endCheck("SO_GET_RUPEE")) {
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
            mB70 = 1;
            mBD9 = true;
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_TALK_e);
        }
    } else if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
#if VERSION > VERSION_DEMO
        if (REG12_S(9) != 0) {
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
        }

        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        player->cancelOriginalDemo();
#endif
        mB70 = 7;
    }
}

/* 00002C6C-00002CC0       .text modeEventTriForceInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForceInit() {
    mAFC = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    m_jnt.offBackBoneLock();
    offsetAppear();
    setAnm(1, false);
}

/* 00002CC0-00002D80       .text modeEventTriForce__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForce() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        if (dComIfGp_evmng_endCheck("SO_TRIFORCE_CHECK")) {
            attention_info.flags = fopAc_Attn_TALKFLAG_NOTALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
            dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_DISAPPEAR_e);
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3A20);
        }
    } else {
        mB70 = 8;
    }
}

/* 00002D80-00003110       .text modeProc__10daNpc_So_cFQ210daNpc_So_c6Proc_ei */
void daNpc_So_c::modeProc(daNpc_So_c::Proc_e mode, int index) {
    struct ModeEntry {
        daNpc_So_c::ModeFunc init;
        daNpc_So_c::ModeFunc run;
        const char* name;
    };

    static ModeEntry mode_tbl[] = {
        {
            &daNpc_So_c::modeWaitInit,
            &daNpc_So_c::modeWait,
            "WAIT",
        },
        {
            &daNpc_So_c::modeHideInit,
            &daNpc_So_c::modeHide,
            "HIDE",
        },
        {
            &daNpc_So_c::modeJumpInit,
            &daNpc_So_c::modeJump,
            "JUMP",
        },
        {
            &daNpc_So_c::modeSwimInit,
            &daNpc_So_c::modeSwim,
            "SWIM",
        },
        {
            &daNpc_So_c::modeNearSwimInit,
            &daNpc_So_c::modeNearSwim,
            "NEAR_SWIM",
        },
        {
            &daNpc_So_c::modeEventFirstWaitInit,
            &daNpc_So_c::modeEventFirstWait,
            "EVENT_FIRST_WAIT",
        },
        {
            &daNpc_So_c::modeEventFirstInit,
            &daNpc_So_c::modeEventFirst,
            "EVENT_FIRST",
        },
        {
            &daNpc_So_c::modeEventFirstEndInit,
            &daNpc_So_c::modeEventFirstEnd,
            "EVENT_FIRST_END",
        },
        {
            &daNpc_So_c::modeEventEsaInit,
            &daNpc_So_c::modeEventEsa,
            "EVENT_ESA",
        },
        {
            &daNpc_So_c::modeEventMapopenInit,
            &daNpc_So_c::modeEventMapopen,
            "EVENT_MAPOPEN",
        },
        {
            &daNpc_So_c::modeEventBowInit,
            &daNpc_So_c::modeEventBow,
            "EVENT_BOW",
        },
        {
            &daNpc_So_c::modeTalkInit,
            &daNpc_So_c::modeTalk,
            "TALK",
        },
        {
            &daNpc_So_c::modeDisappearInit,
            &daNpc_So_c::modeDisappear,
            "DISAPPEAR",
        },
        {
            &daNpc_So_c::modeDebugInit,
            &daNpc_So_c::modeDebug,
            "DEBUG",
        },
        {
            &daNpc_So_c::modeGetRupeeInit,
            &daNpc_So_c::modeGetRupee,
            "GETRUPEE",
        },
        {
            &daNpc_So_c::modeEventTriForceInit,
            &daNpc_So_c::modeEventTriForce,
            "EVENT_TRIFORCE",
        },
    };

    if (mode == daNpc_So_c::PROC_INIT_e) {
        m6CC = index;
        (this->*mode_tbl[m6CC].init)();
    } else if (mode == daNpc_So_c::PROC_RUN_e) {
        (this->*mode_tbl[m6CC].run)();
    }
}

/* 00003110-00003264       .text eventOrder__10daNpc_So_cFv */
void daNpc_So_c::eventOrder() {
    static char* a_demo_name_tbl[] = {"SO_1ST_MEET", "SO_1ST_MEET_END", "SO_MAPOPEN", "SO_BOW", "SO_GET_RUPEE", "SO_TRIFORCE_CHECK"};

#if VERSION == VERSION_DEMO
    if (mB70 == 1 || mB70 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mB70 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mB70 == 5 || mB70 == 4 || mB70 == 6 || mB70 == 7) {
        fopAcM_orderChangeEvent(this, a_demo_name_tbl[mB70 - 3], 1, 0xffff);
    } else if (mB70 >= 3) {
        fopAcM_orderOtherEvent(this, a_demo_name_tbl[mB70 - 3]);
    }
#else
    if (mB70 == 1 || mB70 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mB70 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mB70 == 5 || mB70 == 4 || mB70 == 6) {
        fopAcM_orderChangeEvent(this, a_demo_name_tbl[mB70 - 3], 0, 0xffff);
    } else if (mB70 == 7) {
        if (REG12_S(9) == 0) {
            fopAcM_orderChangeEvent(this, a_demo_name_tbl[mB70 - 3], 0, 0xffff);
            eventInfo.onCondition(dEvtCnd_CANGETITEM_e);
        } else {
            fopAcM_orderOtherEvent(this, a_demo_name_tbl[mB70 - 3]);
        }
    } else if (mB70 >= 3) {
        fopAcM_orderOtherEvent(this, a_demo_name_tbl[mB70 - 3]);
    }
#endif
}

/* 00003264-0000330C       .text checkOrder__10daNpc_So_cFv */
void daNpc_So_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        mB70 = 0;
    } else if (eventInfo.checkCommandTalk() && (mB70 == 1 || mB70 == 2)) {
        if (dComIfGp_event_chkTalkXY()) {
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_EVENT_ESA_e);
        }
        mB70 = 0;
    }
}

/* 0000330C-000033F4       .text setScale__10daNpc_So_cFv */
void daNpc_So_c::setScale() {
    f32 dVar2 = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));

    if (dVar2 > l_HIO.m48) {
        f32 tmp = dVar2 - l_HIO.m48;
        f32 tmp2 = (100000.0f - l_HIO.m48) / l_HIO.m4C;
        mB08 = tmp / tmp2 + 1.0f;
        if (mB08 > l_HIO.m4C) {
            mB08 = l_HIO.m4C;
        }
    } else {
        mB08 = l_HIO.m44;
    }

#if VERSION > VERSION_DEMO
    if (m6CC == 0xf) {
        mB08 = 1.0f;
        scale.setall(mB08);
    }
#endif

    cXyz tmp;
    tmp.setall(mB08);
    cLib_addCalcPos2(&scale, tmp, 0.1f, 0.5f);
}

/* 000033F4-00003844       .text _execute__10daNpc_So_cFv */
bool daNpc_So_c::_execute() {
    f32 fVar6 = scale.x;
    f32 dVar5 = fVar6 * 100.0f;
    f32 dVar4 = fVar6 * -100.0f;

    fopAcM_setCullSizeBox(this, dVar4, dVar4, dVar4, dVar5, dVar5, dVar5);

    if (!dComIfGp_event_runCheck() && mAcch.ChkGroundHit()) {
        current.pos.y = 0.0f;
        fopAcM_SetSpeedF(this, 0.0f);
        mAFC = 0.0f;
        speed.y = 0.0f;
        mAFC = 0.0f;
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_HIDE_e);
        return true;
    }

    m_jnt.setParam(
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

    current.angle.y = shape_angle.y;

    if (m6CC == 1) {
        if (mA7C == 0.0f) {
            fopAcM_Search(searchTagSo_CB, this);
        } else {
            modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_SWIM_e);
        }
    }
#if VERSION > VERSION_DEMO
    else if (mA7C == 0.0f)
    {
        fopAcM_Search(searchTagSo_CB, this);
    }

    if (cLib_calcTimer(&m868) == 0) {
        m86C++;
        if (m86C > mBtpAnm.getEndFrame()) {
            s16 tmp = cM_rndF(100.0f) + 100.0f;
            m868 = tmp;
            m86C = 0;
        }
    }
#endif

    setScale();
    setAttention();
    cLib_addCalc2(&speedF, mAFC, 0.3f, 4.0f);
    cLib_addCalc2(&mB34, mB38.x, mB38.z, mB38.y);
    lookBack();
    checkOrder();
    modeProc(daNpc_So_c::PROC_RUN_e, 0x10);
    eventOrder();

    s16 target = 0;
    if (current.pos.y < dLib_getWaterY(current.pos, mAcch)) {
        current.pos.y = dLib_getWaterY(current.pos, mAcch);
        if (mB34 > 0.0f && mAE8.mpBaseEmitter == NULL) {
            static cXyz ripple_scale(0.8f, 0.8f, 0.8f);

            dComIfGp_particle_setShipTail(dPa_name::ID_AK_JN_HAMON00, &current.pos, NULL, &ripple_scale, -1, &mAE8);

            if (mAE8.getEmitter() != NULL) {
                mAE8.setRate(0.0f);
            }
        }
    } else {
        if (speed.y < -(mB00 / 4)) {
            if (speed.y < -(mB00 / 2)) {
                target = l_HIO.m64;
            } else {
                target = l_HIO.m66;
            }
        } else if (speed.y > mB00 / 4) {
            if (speed.y > mB00 / 2) {
                target = l_HIO.m68;
            } else {
                target = l_HIO.m6A;
            }
        } else {
            target = 0;
        }
        mAE8.end();
    }

    cLib_addCalcAngleS2(&shape_angle.x, target, 4, 0x800);

    if (
        m6CC != 1 && m6CC != 5 && !mBDB
#if VERSION > VERSION_DEMO
        && cLib_calcTimer(&mBE0) == 0
#endif
    )
    {
        fopAcM_posMoveF(this, NULL);
        mAcch.CrrPos(*dComIfG_Bgsp());
    }

    mpMorf->play(NULL, 0, 0);
    mpMorf->calc();

    setMtx();
    setAnm(6, false);
    setAnmSwimSpeed();

    current.angle.y = shape_angle.y;
    return false;
}

/* 00003844-000038E0       .text debugDraw__10daNpc_So_cFv */
void daNpc_So_c::debugDraw() {
    cXyz tmp = mA80;
    tmp.y += 20.0f;

    cXyz tmp2 = dComIfGp_getPlayer(0)->current.pos;
    tmp2.y += 20.0f;

    cXyz tmp3 = current.pos;
    tmp3.y = tmp2.y;

    cXyz tmp4 = mAAC;
    tmp4.y += 20.0f;
}

/* 000038E0-00003954       .text hudeDraw__10daNpc_So_cFv */
void daNpc_So_c::hudeDraw() {
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(11));
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoExt_modelUpdateDL(mpModel);
}

/* 00003954-00003B00       .text _draw__10daNpc_So_cFv */
bool daNpc_So_c::_draw() {
    static const GXColor unused[] = {
        {0x00, 0xFF, 0x00, 0x80},
        {0xFF, 0x00, 0x00, 0x80},
        {0x00, 0xFF, 0x00, 0x80},
        {0xFF, 0x00, 0x00, 0x80},
        {0x00, 0xFF, 0x00, 0x80},
        {0xFF, 0x00, 0x00, 0x80},
        {0x00, 0xFF, 0xFF, 0x80},
        {0xFF, 0xFF, 0x00, 0x80},
        {0xFF, 0xFF, 0x00, 0x80},
        {0x00, 0x00, 0xFF, 0x80},
        {0x00, 0x00, 0xFF, 0x80},
    };

    if (l_HIO.mNpc.m22 != 0) {
        debugDraw();
    }

    if (m6CC == 5) {
        return 1;
    }

    if (l_HIO.m31 == 0) {
        J3DModel* pJVar4 = mpMorf->getModel();
#if VERSION > VERSION_DEMO
        J3DModelData* pJVar3 = pJVar4->getModelData();
#endif

        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(pJVar4, &tevStr);

#if VERSION > VERSION_DEMO
        mBtpAnm.entry(pJVar3, m86C);
        mpMorf->entryDL();
        pJVar3->getMaterialTable().removeTexNoAnimator(mBtpAnm.getBtpAnm());
#else
        mpMorf->entryDL();
#endif

        if (mA78 != 0 || l_HIO.m2C != 0) {
            hudeDraw();
        }
    }

    cXyz tmp = current.pos;
    tmp.y += mB34;
    dSnap_RegistFig(DSNAP_TYPE_UNK7D, this, tmp, shape_angle.y, 1.0f, 1.0f, 1.0f);

    cXyz tmp2(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mA74 = dComIfGd_setShadow(mA74, 0, mpMorf->getModel(), &tmp2, 800.0f, 40.0f, current.pos.y + mB34, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr);
    return true;
}

/* 00003B00-00003DF8       .text createInit__10daNpc_So_cFv */
void daNpc_So_c::createInit() {
    mBDA = 0;

    mStts.Init(DEMO_SELECT(0x64, 0xFF), DEMO_SELECT(0x64, 0xFF), this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    mStts2.Init(DEMO_SELECT(0xC8, 0xFF), DEMO_SELECT(0x00, 0xFF), this);
    mSph.Set(m_sph_src);
    mSph.SetStts(&mStts2);

#if VERSION > VERSION_DEMO
    current.pos.y -= 500.0f;
#endif

    setMtx();
    mpMorf->calc();
    mAAC = current.pos;

    offsetZero();
    setAnm(1, false);
    mA79 = cM_rndF(4.9f);

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0901) == 0 && strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
        (fopAcM_GetRoomNo(this) == dIsleRoom_DragonRoostIsland_e) && dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC))
    {
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_EVENT_FIRST_WAIT_e);
    } else if (
        strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(this) == dIsleRoom_GaleIsle_e && dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_WT) &&
        dComIfGs_isCollect(0, 3) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A20)
    )
    {
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_EVENT_TRIFORCE_e);
    } else {
        attention_info.flags = fopAc_Attn_TALKFLAG_NOTALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
        modeProc(daNpc_So_c::PROC_INIT_e, daNpc_So_c::MODE_HIDE_e);
    }

#if VERSION > VERSION_DEMO
    mBE0 = 30;
#endif

    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    mAcch.SetWallNone();
    mAcch.SetRoofNone();

    cullMtx = mpMorf->getModel()->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, scale.x * -100.0f, scale.x * -100.0f, scale.x * -100.0f, scale.x * 100.0f, scale.x * 100.0f, scale.x * 100.0f);
    cullSizeFar = 10.0f;
    gravity = -2.5f;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x22;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x22;
    eventInfo.mpCheckCB = daNpc_So_XyCheckCB;
    eventInfo.mpEventCB = daNpc_So_XyEventCB;
    mEventCut.setActorInfo2("NpcSo", this);
}

/* 00003DF8-00003E24       .text getArg__10daNpc_So_cFv */
void daNpc_So_c::getArg() {
    m6D0 = home.angle.x;
    if (m6D0 == 0xFFFF || m6D0 == 0) {
        m6D0 = 1;
    }
}

/* 00003E24-00003F38       .text _create__10daNpc_So_cFv */
cPhs_State daNpc_So_c::_create() {
    fopAcM_SetupActor(this, daNpc_So_c);

    cPhs_State PVar1 = dComIfG_resLoad(&mPhase, m_arc_name);
    if (PVar1 == cPhs_COMPLEATE_e) {
        getArg();

        if (strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(this) == dIsleRoom_ToweroftheGods_e &&
            !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E40))
        {
            return cPhs_ERROR_e;
        }

#if VERSION == VERSION_DEMO
        if ((strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(this) != dIsleRoom_DragonRoostIsland_e &&
             !dComIfGs_checkGetItem(NORMAL_SAIL)) ||
            dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC) == 0)
        {
            return cPhs_ERROR_e;
        }
#else
        if (dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC) == 0) {
            return cPhs_ERROR_e;
        }
#endif

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, daNpc_So_c::m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }
    return PVar1;
}

/* 000046E4-00004754       .text _delete__10daNpc_So_cFv */
bool daNpc_So_c::_delete() {
    if (dComIfGp_getMiniGameType() == 8) {
        dComIfGp_endMiniGame(8);
    }
    dComIfG_resDelete(&mPhase, m_arc_name);
    mAE8.end();
    return true;
}

/* 00004754-00004774       .text daNpc_SoCreate__FPv */
static cPhs_State daNpc_SoCreate(void* i_this) {
    return ((daNpc_So_c*)i_this)->_create();
}

/* 00004774-00004798       .text daNpc_SoDelete__FPv */
static BOOL daNpc_SoDelete(void* i_this) {
    return ((daNpc_So_c*)i_this)->_delete();
}

/* 00004798-000047BC       .text daNpc_SoExecute__FPv */
static BOOL daNpc_SoExecute(void* i_this) {
    return ((daNpc_So_c*)i_this)->_execute();
}

/* 000047BC-000047E0       .text daNpc_SoDraw__FPv */
static BOOL daNpc_SoDraw(void* i_this) {
    return ((daNpc_So_c*)i_this)->_draw();
}

/* 000047E0-000047E8       .text daNpc_SoIsDelete__FPv */
static BOOL daNpc_SoIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_SoMethodTable = {
    (process_method_func)daNpc_SoCreate,
    (process_method_func)daNpc_SoDelete,
    (process_method_func)daNpc_SoExecute,
    (process_method_func)daNpc_SoIsDelete,
    (process_method_func)daNpc_SoDraw,
};

actor_process_profile_definition g_profile_NPC_SO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_SO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_So_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_SO,
    /* Actor SubMtd */ &daNpc_SoMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
