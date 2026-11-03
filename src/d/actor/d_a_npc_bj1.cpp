/**
 * d_a_npc_bj1.cpp
 * NPC - Generic Koroks
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bj1.h"
#include "d/actor/d_a_jbo.h"
#include "d/d_kankyo_wether.h"

static daNpc_Bj1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000108       .text __ct__20daNpc_Bj1_childHIO_cFv */
daNpc_Bj1_childHIO_c::daNpc_Bj1_childHIO_c() {
}

/* 00000150-0000020C       .text __ct__15daNpc_Bj1_HIO_cFv */
daNpc_Bj1_HIO_c::daNpc_Bj1_HIO_c() {
    static daNpc_Bj1_childHIO_c::hio_prm_c a_prm_tbl[] = {
        { 0x13881388, 0xE000EC78, 0x00001C70, 0x0000E390, 0x04000400, 0x43020000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x13881388, 0xFD44EC78, 0x00001C70, 0x0000E390, 0x04000400, 0x42C80000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x13881388, 0xE000EC78, 0x00001C70, 0x0000E390, 0x04000400, 0x43160000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x13881B58, 0xFF38F830, 0x00000000, 0x00000000, 0x04000400, 0x42C80000, 0x00000000, 0x43960000, 0x005A0006,
          0x04000000, 0x40800000, 0x40A00000, 0x3E4CCCCD, 0x40800000, 0x3E4CCCCD, 0x3f800000, 0x232800C8, 0x10001388,
          0x437A0000, 0x7FFF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x13880BB8, 0x0064F448, 0x00001388, 0x0000EC78, 0x04000400, 0x42DC0000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x13881388, 0xFF9CEC78, 0x000007D0, 0x0000F830, 0x04000400, 0x43020000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x13881388, 0xE000EC78, 0x00001C70, 0x0000E390, 0x04000400, 0x42FA0000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000006, 0x04000000, 0x3ECCCCCD, 0x40A00000, 0x3E4CCCCD, 0x42200000 },
        { 0x13880FA0, 0xF830F060, 0x00001C70, 0x0000E390, 0x04000400, 0x42F00000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x13881388, 0xF254EC78, 0x00001C70, 0x0000E390, 0x04000400, 0x43020000, 0x00000000, 0x43960000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
    };
    for (int i = 0; i < 9; i++) {
        children[i].field_0x68 = i;
        memcpy(&children[i].hio_prm, &a_prm_tbl[i], 0x64);
    }
    field_0x04 = -1;
    field_0x08 = -1;
}

static char* l_evn_tbl[] = {
    "Mak_Drg",
    "Get_Blu_Btl",
    "Calling",
};

/* 00000268-000002EC       .text searchActor_Jb__FPvPv */
static void* searchActor_Jb(void* i_actor, void*) {
    if (l_check_wrk < 0x14 && fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_JBO_e && ((jbo_class*)i_actor)->mType != daJbo_Type_NORMAL_e) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 000002EC-00000338       .text nodeCallBack_Bj1__FP7J3DNodei */
static BOOL nodeCallBack_Bj1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Bj1_c*>(j3dSys.getModel()->getUserArea())->nodeBj1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000338-000004C4       .text nodeBj1Control__11daNpc_Bj1_cFP7J3DNodeP8J3DModel */
void daNpc_Bj1_c::nodeBj1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(26.0f, 26.0f, 0.0f);
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jntNo));

    if (jntNo == field_0x6CC) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::scaleM(field_0x7F0.x, field_0x7F0.y, field_0x7F0.z);
        mDoMtx_stack_c::multVec(&field_0x7E4, &field_0x7C0);
    }

    if (jntNo == field_0x6CD) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
        mDoMtx_stack_c::scaleM(field_0x7FC.x, field_0x7FC.y, field_0x7FC.z);
    }

    if (jntNo == field_0x6CF) {
        cMtx_copy(mDoMtx_stack_c::get(), field_0x704);
    }

    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 00000500-0000054C       .text nodeCallBack_Prp__FP7J3DNodei */
static BOOL nodeCallBack_Prp(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Bj1_c*>(j3dSys.getModel()->getUserArea())->nodePrpControl(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000054C-00000664       .text nodePrpControl__11daNpc_Bj1_cFP7J3DNodeP8J3DModel */
void daNpc_Bj1_c::nodePrpControl(J3DNode* i_node, J3DModel* i_model) {
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();

    if (jntNo == field_0x6E9) {
        cMtx_copy(field_0x704, mDoMtx_stack_c::get());
        mDoMtx_stack_c::transM(-1.5f, 4.5f, -4.2f);
        mDoMtx_stack_c::XYZrotM(-0x4000, -0x5555, 0);
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        i_model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
    }
    if (jntNo == field_0x6E8) {
        mDoMtx_stack_c::YrotS(field_0x6F0);
        mDoMtx_stack_c::revConcat(i_model->getAnmMtx(jntNo));
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        i_model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
    }
}

/* 00000664-00000710       .text init_BJ4_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJ4_0() {
    bool result = dComIfGs_isSymbol(dSymbol_FARORE_e) == FALSE;
    if (result) {
        result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != FALSE;
        if (result) {
            set_action(&daNpc_Bj1_c::wait_action2, NULL);
        }
    }
    return result;
}

/* 00000710-000007D4       .text init_BJ6_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJ6_0() {
    bool result = dComIfGs_isSymbol(dSymbol_FARORE_e) == FALSE;
    if (result) {
        result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != FALSE;
        if (result) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
            set_action(&daNpc_Bj1_c::wait_action4, NULL);
        }
    }
    return result;
}

/* 000007D4-00000864       .text init_BJ7_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJ7_0() {
    bool result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != FALSE;
    if (result) {
        setPrtcl_drugPot_1();
        set_action(&daNpc_Bj1_c::wait_action3, NULL);
    }
    return result;
}

/* 00000864-00000910       .text init_BJX_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJX_0() {
    bool result = dComIfGs_isSymbol(dSymbol_FARORE_e) == FALSE;
    if (result) {
        result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != FALSE;
        if (result) {
            set_action(&daNpc_Bj1_c::wait_action1, NULL);
        }
    }
    return result;
}

/* 00000910-00000998       .text init_BJX_1__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJX_1() {
    bool result = dComIfGs_isSymbol(dSymbol_FARORE_e) != 0;
    if (result) {
        set_action(&daNpc_Bj1_c::wait_action1, NULL);
    }
    return result;
}

/* 00000998-00000C90       .text createInit__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::createInit() {
    static bj1_prm_c l_bj1_prm_tbl[] = {
        { { 1.0f, 1.0f, 1.0f }, { 1.1f, 1.0f, 1.0f }, { 40.0f, 10.0f, 0.0f } },  { { 0.9f, 1.0f, 1.0f }, { 0.9f, 1.0f, 1.0f }, { 30.0f, 10.0f, 0.0f } },
        { { 1.1f, 1.0f, 1.0f }, { 1.25f, 1.1f, 1.1f }, { 40.0f, 10.0f, 0.0f } }, { { 0.8f, 1.0f, 1.0f }, { 0.9f, 1.0f, 1.0f }, { 30.0f, 10.0f, 0.0f } },
        { { 0.8f, 1.0f, 1.0f }, { 0.8f, 1.0f, 1.0f }, { 30.0f, 10.0f, 0.0f } },  { { 1.0f, 1.0f, 1.0f }, { 1.15f, 1.0f, 1.05f }, { 40.0f, 10.0f, 0.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 40.0f, 10.0f, 0.0f } },  { { 1.0f, 1.0f, 1.0f }, { 1.1f, 1.2f, 1.05f }, { 40.0f, 10.0f, 0.0f } },
        { { 1.1f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 40.0f, 10.0f, 0.0f } },
    };
    static char* a_staff_tbl[] = {
        "Bj1", "Bj1", "Bj2", "Bj2", "Bj3", "Bj3", "Bj4", "Bj4", "Bj5", "Bj5", "Bj6", "Bj6", "Bj7", "Bj8", "Bj8", "Bj9", "Bj9",
    };

    for (int i = 0; i < 3; i++) {
        field_0x826[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], -1);
    }
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;

    switch (field_0x8B4) {
        case 4:
            attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA7;
            attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
            break;
        case 0:
        case 1:
        case 7:
            attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
            attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
            break;
        case 2:
        case 3:
        case 5:
        case 8:
            attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAA;
            attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAA;
            break;
        case 6:
            attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x5A;
            attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x5A;
            break;
        default:
            return false;
    }

    field_0x7F0 = l_bj1_prm_tbl[field_0x8B4].head_scale;
    field_0x7FC = l_bj1_prm_tbl[field_0x8B4].backbone_scale;
    field_0x7E4 = l_bj1_prm_tbl[field_0x8B4].eye_offset;
    gravity = -4.5f;
    field_0x7CC = current.pos;

    u32 pathIdx = (fpcM_GetParam(this) >> 16) & 0xFF;
    field_0x83F = pathIdx;

    if (pathIdx != 0xFF) {
        field_0x734.setInf(pathIdx, fopAcM_GetRoomNo(this), true);
        if (field_0x734.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        } else {
            return false;
        }
    }
    field_0x73C.setActorInfo2(a_staff_tbl[field_0x8B5], this);
    field_0x8AF = 0xB;

    bool init_success;
    switch (field_0x8B5) {
        case 0:
        case 2:
        case 4:
        case 8:
        case 13:
        case 15:
            init_success = init_BJ4_0();
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        case 11:
        case 14:
        case 16:
            init_success = init_BJ6_0();
            break;
        case 6:
            init_success = init_BJX_0();
            break;
        case 10:
            init_success = init_BJX_1();
            break;
        case 12:
            init_success = init_BJ7_0();
            break;
        default:
            init_success = false;
    }

    if (init_success) {
        shape_angle = current.angle;
    } else {
        return false;
    }

    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 00000C90-00000E00       .text setMtx_anmProc__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setMtx_anmProc() {
    switch (field_0x8AF) {
        case 4:
            if (field_0x8A9) {
                if (speed.y < 0.0f) {
                    if (mpMorf->getFrame() < 7.0f) {
                        mpMorf->setFrame(mpMorf->getEndFrame());
                    }
                } else {
                    if (mpMorf->getFrame() >= 7.0f) {
                        mpMorf->setFrame(7.0f);
                    }
                }
            }
            break;
        case 7:
            if (field_0x83C && !field_0x888 && !cLib_calcTimer(&field_0x894)) {
                s8 reverb = dComIfGp_getReverb(current.roomNo);
                mDoAud_seStart(JA_SE_OBJ_CRG_DRUG_MADE, &current.pos, 0, reverb);
                setAnm_NUM(0x5);
                setPrtcl_drugPot_2();
            }
            break;
    };
}

/* 00000E00-00001098       .text setMtx__11daNpc_Bj1_cFb */
void daNpc_Bj1_c::setMtx(bool i_param1) {
    if (!field_0x857) {
        int uVar5 = 0;
        if (mObjAcch.ChkGroundHit()) {
            uVar5 = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
        }
        s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
        field_0x83C = mpMorf->play(&eyePos, uVar5, reverb);
        if (mpMorf->getFrame() < field_0x808) {
            field_0x83C = true;
        }
        field_0x808 = mpMorf->getFrame();
        setMtx_anmProc();
        field_0x6E4->play(&eyePos, 0, 0);
        if (field_0x84D) {
            setPrtcl_peraProOpen();
            field_0x84D = 0;
        }
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    field_0x6E4->calc();

    if (field_0x6D4) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(field_0x6CE));
        field_0x6D4->setBaseTRMtx(mDoMtx_stack_c::get());
        field_0x6D4->calc();
    }

    if (field_0x6D8) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(field_0x6CF));
        field_0x6D8->setBaseTRMtx(mDoMtx_stack_c::get());
        field_0x6D8->calc();
    }

    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(field_0x6CC));
    field_0x6D0->setBaseTRMtx(mDoMtx_stack_c::get());
    field_0x6D0->calc();
    flwPrtcl_danceLR();
    setAttention(i_param1);
}

/* 00001098-000010AC       .text anmNum_toResID__11daNpc_Bj1_cFi */
u32 daNpc_Bj1_c::anmNum_toResID(int i_idx) {
    static const u32 a_bck_resID_tbl[] = { 10, 2, 7, 8, 3, 6, 0, 1, 11, 9, 42 };
    return a_bck_resID_tbl[i_idx];
}

/* 000010AC-00001188       .text setAnm_anm__11daNpc_Bj1_cFPQ211daNpc_Bj1_c9anm_prm_c */
BOOL daNpc_Bj1_c::setAnm_anm(anm_prm_c* i_anm_prm) {
    if (field_0x8AF == i_anm_prm->anmNum) {
        return TRUE;
    }
    field_0x8AF = i_anm_prm->anmNum;

    u32 resID = anmNum_toResID(field_0x8AF);
    dNpc_setAnmIDRes(mpMorf, i_anm_prm->loopMode, i_anm_prm->morf, i_anm_prm->speed, resID, -1, "Bj");

    switch (field_0x8AF) {
        case 7:
            setPrtcl_danceLR();
            field_0x888 = 0;
            field_0x894 = 0x1E;
            break;
        default:
            delPrtcl_danceLR();
    }

    field_0x808 = 0.0f;
    field_0x83D = 0;
    field_0x83C = 0;
    return TRUE;
}

/* 00001188-000011B8       .text setAnm_NUM__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::setAnm_NUM(int i_idx) {
    static anm_prm_c a_anm_prm_tbl[] = {
        { 0, 8.0f, 1.0f, 2 }, { 1, 8.0f, 1.0f, 0 }, { 2, 8.0f, 1.0f, 2 }, { 3, 8.0f, 1.0f, 2 }, { 4, 8.0f, 1.0f, 2 },  { 5, 8.0f, 1.0f, 0 },
        { 6, 8.0f, 1.0f, 0 }, { 7, 8.0f, 1.0f, 0 }, { 8, 8.0f, 1.0f, 2 }, { 9, 8.0f, 1.0f, 0 }, { 10, 8.0f, 1.0f, 2 }, { 0, 0.0f, 0.0f, 0 },
    };
    setAnm_anm(&a_anm_prm_tbl[i_idx]);
}

/* 000011B8-000011F4       .text setAnm__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = { { -1, 0.0f, 0.0f, -1 }, { 0, 8.0f, 1.0f, 2 }, { -1, 0.0f, 0.0f, -1 }, { 1, 8.0f, 1.0f, 0 }, { 10, 8.0f, 1.0f, 2 },
                                         { 0, 8.0f, 1.0f, 2 },   { 8, 8.0f, 1.0f, 2 }, { 0, 8.0f, 1.0f, 2 },   { 0, 8.0f, 1.0f, 2 } };

    setAnm_anm(&a_anm_prm_tbl[field_0x8B1]);
    return TRUE;
}

/* 000011F4-00001378       .text setAnm_prp__11daNpc_Bj1_cFSc */
void daNpc_Bj1_c::setAnm_prp(s8 i_param1) {
    s8 reverb;
    switch (i_param1) {
        case 1:
            field_0x6E4->setAnm((J3DAnmTransform*)dComIfG_getObjectIDRes("Bj", 0x28), 0, 0.0f, 1.0f, 0.0f, -1.0f, NULL);
            reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
            mDoAud_seStart(JA_SE_CM_PRAPELLO_OPEN, &current.pos, 0, reverb);
            field_0x84D = 1;
            break;
        case 2:
            field_0x6E4->setAnm((J3DAnmTransform*)dComIfG_getObjectIDRes("Bj", 0x28), 2, 0.0f, -1.0f, 0.0f, -1.0f, NULL);
            field_0x6E4->setFrame(7.0f);
            reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
            mDoAud_seStart(JA_SE_CM_PRAPELLO_CLOSE, &current.pos, 0, reverb);
            break;
    }
}

/* 00001378-0000137C       .text chg_anmTag__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::chg_anmTag() {
    return;
}

/* 0000137C-00001380       .text control_anmTag__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::control_anmTag() {
    return;
}

/* 00001380-000013C0       .text chg_anmAtr__11daNpc_Bj1_cFUc */
void daNpc_Bj1_c::chg_anmAtr(u8 i_param1) {
    if (i_param1 >= 0xB || i_param1 == field_0x8AD) {
        return;
    }
    field_0x8AD = i_param1;
    setAnm_ATR();
}

/* 000013C0-0000143C       .text control_anmAtr__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::control_anmAtr() {
    switch (field_0x8AD) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            break;
        case 6:
        case 7:
            if (field_0x83C) {
                field_0x8AD = 0;
                setAnm_NUM(0);
            }
            break;
        case 10:
            if (field_0x83C) {
                field_0x8AD = 2;
                setAnm_NUM(3);
            }
            break;
    }
}

/* 0000143C-00001470       .text setAnm_ATR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[] = {
        { 0, 8.0f, 1.0f, 2 }, { 2, 8.0f, 1.0f, 2 }, { 3, 8.0f, 1.0f, 2 }, { 4, 8.0f, 1.0f, 2 }, { 5, 8.0f, 1.0f, 0 }, { 6, 8.0f, 1.0f, 0 },
        { 6, 8.0f, 1.0f, 0 }, { 4, 8.0f, 1.0f, 2 }, { 7, 8.0f, 1.0f, 0 }, { 8, 8.0f, 1.0f, 2 }, { 5, 8.0f, 1.0f, 0 },
    };
    setAnm_anm(&a_anm_prm_tbl[field_0x8AD]);
}

/* 00001470-00001534       .text anmAtr__11daNpc_Bj1_cFUs */
void daNpc_Bj1_c::anmAtr(u16 i_param1) {
    u8 tag;
    switch (i_param1) {
        case 6:
            if (field_0x8B7 == 0) {
                field_0x8AD = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x8B7++;
            }
            tag = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if (tag != 0xFF && field_0x8AE != tag) {
                field_0x8AE = tag;
                chg_anmTag();
            }
            break;
        case 14:
            field_0x8B7 = 0;
            break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00001534-000015D8       .text eventOrder__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eventOrder() {
    if (field_0x8B0 == 1 || field_0x8B0 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x8B5 == 12) {
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        }
        if (field_0x8B0 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (field_0x8B0 >= 3) {
        field_0x82C = field_0x8B0 - 3;
        fopAcM_orderOtherEventId(this, field_0x826[field_0x82C]);
    }
}

/* 000015D8-00001690       .text checkOrder__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::checkOrder() {
    if (eventInfo.getCommand() == dEvtCmd_INDEMO_e) {
        if (dComIfGp_evmng_startCheck(field_0x826[field_0x82C])) {
            switch (field_0x82C) {
                case 0:
                case 1:
                    break;
                case 2:
                    fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
                    break;
            }
            field_0x8B0 = 0;
        }
    } else if (eventInfo.getCommand() == dEvtCmd_INTALK_e) {
        if (field_0x8B0 == 1 || field_0x8B0 == 2) {
            field_0x8B0 = 0;
            field_0x855 = 1;
        }
    }
}

/* 00001690-0000172C       .text chk_talk__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::chk_talk() {
    BOOL ret = TRUE;
    field_0x83E = 0xFF;

    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            field_0x83E = dComIfGp_event_getPreItemNo();
        } else {
            ret = FALSE;
        }
    }
    return ret;
}

/* 0000172C-000017C0       .text chk_drct__11daNpc_Bj1_cFf */
u32 daNpc_Bj1_c::chk_drct(f32 i_param1) {
    s16 target = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos) - current.angle.y;
    int cmp = abs(target);
    return cmp < cM_deg2s(i_param1);
}

/* 000017C0-000017F0       .text chk_partsNotMove__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::chk_partsNotMove() {
    BOOL ret = FALSE;
    if (field_0x822 != m_jnt.getBackbone_y() || field_0x820 != m_jnt.getHead_y()) {
        ret = TRUE;
    }
    return ret;
}

/* 000017F0-000019A0       .text lookBack__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::lookBack() {
    /* Nonmatching */
}

/* 000019A0-00001A44       .text getMaskInf__11daNpc_Bj1_cFPUc */
void daNpc_Bj1_c::getMaskInf(u8*) {
    /* Nonmatching */
}

/* 00001A44-00001AA8       .text chkReg__11daNpc_Bj1_cFUs */
bool daNpc_Bj1_c::chkReg(u16) {
    /* Nonmatching */
}

/* 00001AA8-00001B14       .text setReg__11daNpc_Bj1_cFUs */
void daNpc_Bj1_c::setReg(u16) {
    /* Nonmatching */
}

/* 00001B14-00001E84       .text next_msgStatus__11daNpc_Bj1_cFPUl */
u16 daNpc_Bj1_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00001E84-00001F14       .text getMsg_BJ1_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0604)) {
        return 0x140E;
    }
    if (dKyw_get_windsdir() == 1) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C80) ? 0x1414 : 0x1412;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0904) ? 0x1411 : 0x1410;
}

/* 00001F14-00001F54       .text getMsg_BJ2_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ2_0() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0920) ? 0x13F4 : 0x13F2;
}

/* 00001F54-00001FA8       .text getMsg_BJ3_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ3_0() {
    if (field_0x84B) {
        return 0x13FB;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C20) ? 0x13FA : 0x13F8;
}

/* 00001FA8-00001FE8       .text getMsg_BJ4_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ4_0() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C08) ? 0x13FF : 0x13FD;
}

/* 00001FE8-00002028       .text getMsg_BJ5_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ5_0() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C04) ? 0x13F7 : 0x13F5;
}

/* 00002028-00002068       .text getMsg_BJ6_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ6_0() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C02) ? 0x1405 : 0x1402;
}

/* 00002068-000021C4       .text getMsg_BJ7_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ7_0() {
    if (field_0x842) {
        field_0x842 = 0;
        return 0x142B;
    }
    if (field_0x843) {
        field_0x843 = 0;
        return 0x142C;
    }
    if (field_0x83E == 0x46) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1B80) ? 0x1424 : 0x1422;
    }
    if (field_0x83E != 0xFF) {
        return 0x1421;
    }
    if (dComIfGs_isSymbol(dSymbol_FARORE_e)) {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0D08)) {
            return 0x1433;
        }
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C80)) {
            return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1B80) ? 0x141E : 0x141F;
        }
        return 0x1431;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0D08)) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1B80) ? 0x141E : 0x141F;
    }
    return 0x1416;
}

/* 000021C4-00002254       .text getMsg_BJ8_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ8_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0D40)) {
        return 0x1406;
    }
    if (dKyw_get_windsdir() == 7) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0D10) ? 0x140D : 0x140B;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0D20) ? 0x140A : 0x1409;
}

/* 00002254-00002294       .text getMsg_BJ9_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ9_0() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C10) ? 0x13F0 : 0x13ED;
}

/* 00002294-0000242C       .text getMsg_Corog__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_Corog() {
    if (chkReg(dSv_event_flag_c::UNK_9AFF)) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0102)) {
            return chkReg(dSv_event_flag_c::UNK_99FF) ? 0x1486 : 0x1485;
        }
        if (!chkReg(dSv_event_flag_c::UNK_9EFF)) {
            return chkReg(dSv_event_flag_c::UNK_98FF) ? 0x149E : 0x1487;
        }
        if (chkReg(dSv_event_flag_c::UNK_96FF)) {
            return 0x1484;
        }

        u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_9EFF);
        s32 byte;
        s16 idx = 0;
        for (int i = 0; i < 8; i++) {
            byte = reg;
            if (reg & 1) {
                idx++;
            }
            reg = byte >> 1;
        }
        dComIfGp_setMessageCountNumber(8 - idx);
        return 0x1482;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E10)) {
        return chkReg(dSv_event_flag_c::UNK_97FF) ? 0x1494 : 0x1497;
    }
    return chkReg(dSv_event_flag_c::UNK_97FF) ? 0x1494 : 0x148A;
}

/* 0000242C-000024EC       .text getMsg__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg() {
    u32 msgNo = 0;
    switch (field_0x8B5) {
        case 0:
            msgNo = getMsg_BJ1_0();
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        case 11:
        case 14:
        case 16:
            msgNo = getMsg_BJ2_0();
            break;
        case 2:
            msgNo = getMsg_BJ3_0();
            break;
        case 4:
            msgNo = getMsg_BJ4_0();
            break;
        case 6:
            msgNo = getMsg_BJ5_0();
            break;
        case 8:
            msgNo = getMsg_BJ6_0();
            break;
        case 10:
            msgNo = getMsg_BJ7_0();
            break;
        case 12:
            msgNo = getMsg_BJ8_0();
            break;
        case 13:
            msgNo = getMsg_BJ9_0();
            break;
        case 15:
            msgNo = getMsg_Corog();
            break;
    }
    return msgNo;
}

/* 000024EC-0000256C       .text chkAttention__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::chkAttention() {
    /* Nonmatching */
}

/* 0000256C-000025D4       .text setAttention__11daNpc_Bj1_cFb */
void daNpc_Bj1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 000025D4-00002608       .text searchByID__11daNpc_Bj1_cFUi */
fopAc_ac_c* daNpc_Bj1_c::searchByID(fpc_ProcID) {
    /* Nonmatching */
}

/* 00002608-000026B8       .text partner_srch_sub__11daNpc_Bj1_cFPFPvPv_Pv */
bool daNpc_Bj1_c::partner_srch_sub(fpcLyIt_JudgeFunc) {
    /* Nonmatching */
}

/* 000026B8-00002724       .text partner_srch__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::partner_srch() {
    /* Nonmatching */
}

/* 00002724-000027B0       .text setCollision_SP___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setCollision_SP_() {
    static u32 l_chk_tbl[] = { 0x43020000, 40.0f,      0x42C80000, 40.0f,      0x43160000, 40.0f,      0x42C80000, 40.0f,      0x42C80000,
                               40.0f,      0x43020000, 40.0f,      0x43020000, 40.0f,      0x43020000, 40.0f,      0x43020000, 40.0f };
    /* Nonmatching */
}

/* 000027B0-00002840       .text set_pthPoint__11daNpc_Bj1_cFUc */
void daNpc_Bj1_c::set_pthPoint(u8) {
    /* Nonmatching */
}

/* 00002840-00002988       .text bj_clcFlySpd__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_clcFlySpd() {
    /* Nonmatching */
}

/* 00002988-00002B80       .text bj_movPass__11daNpc_Bj1_cFb */
void daNpc_Bj1_c::bj_movPass(bool) {
    /* Nonmatching */
}

/* 00002B80-00002EDC       .text bj_flyMove__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_flyMove() {
    /* Nonmatching */
}

/* 00002EDC-00002F5C       .text bj_clcMovSpd__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_clcMovSpd() {
    /* Nonmatching */
}

/* 00002F5C-000030A4       .text bj_nMove__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_nMove() {
    /* Nonmatching */
}

/* 000030A4-000031F4       .text setPrtcl_drugPot_1__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_drugPot_1() {
    /* Nonmatching */
}

/* 000031F4-000032B4       .text setPrtcl_drugPot_2__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_drugPot_2() {
    /* Nonmatching */
}

/* 000032B4-00003330       .text delPrtcl_drugPot__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::delPrtcl_drugPot() {
    /* Nonmatching */
}

/* 00003330-000033F4       .text setPrtcl_danceLR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_danceLR() {
    /* Nonmatching */
}

/* 000033F4-00003484       .text flwPrtcl_danceLR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::flwPrtcl_danceLR() {
    /* Nonmatching */
}

/* 00003484-000034D8       .text delPrtcl_danceLR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::delPrtcl_danceLR() {
    /* Nonmatching */
}

/* 000034D8-00003594       .text setPrtcl_peraProOpen__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_peraProOpen() {
    /* Nonmatching */
}

/* 00003594-00003774       .text createSeed__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::createSeed() {
    /* Nonmatching */
}

/* 00003774-000037E4       .text deleteSeed__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::deleteSeed() {
    /* Nonmatching */
}

/* 000037E4-00003998       .text charDecide__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::charDecide(int) {
    /* Nonmatching */
}

/* 00003998-000039DC       .text eInit_setLocFlag__11daNpc_Bj1_cFPi */
void daNpc_Bj1_c::eInit_setLocFlag(int*) {
    /* Nonmatching */
}

/* 000039DC-00003A14       .text eInit_setShapeAngleY__11daNpc_Bj1_cFPis */
void daNpc_Bj1_c::eInit_setShapeAngleY(int*, s16) {
    /* Nonmatching */
}

/* 00003A14-00003A30       .text eInit_setEvTimer__11daNpc_Bj1_cFPi */
void daNpc_Bj1_c::eInit_setEvTimer(int*) {
    /* Nonmatching */
}

/* 00003A30-00003B10       .text eInit_calcRelativPos__11daNpc_Bj1_cFP4cXyzPi */
void daNpc_Bj1_c::eInit_calcRelativPos(cXyz*, int*) {
    /* Nonmatching */
}

/* 00003B10-00003B20       .text eInit_prmFloat__11daNpc_Bj1_cFPff */
void daNpc_Bj1_c::eInit_prmFloat(f32*, f32) {
    /* Nonmatching */
}

/* 00003B20-00003D3C       .text eInit_ATTENTION___11daNpc_Bj1_cFPiPiPiP4cXyzPiPiPi */
void daNpc_Bj1_c::eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*) {
    /* Nonmatching */
}

/* 00003D3C-00003E24       .text eInit_PLYER_MOV_1___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_PLYER_MOV_1_() {
    /* Nonmatching */
}

/* 00003E24-00003F04       .text eInit_MOV___11daNpc_Bj1_cFPfPfPfPi */
void daNpc_Bj1_c::eInit_MOV_(f32*, f32*, f32*, int*) {
    /* Nonmatching */
}

/* 00003F04-00003F74       .text eInit_JMP___11daNpc_Bj1_cFPfPf */
void daNpc_Bj1_c::eInit_JMP_(f32*, f32*) {
    /* Nonmatching */
}

/* 00003F74-0000406C       .text eInit_CHG_PTH___11daNpc_Bj1_cFPiPi */
void daNpc_Bj1_c::eInit_CHG_PTH_(int*, int*) {
    /* Nonmatching */
}

/* 0000406C-000040BC       .text eInit_END_MOV___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_END_MOV_() {
    /* Nonmatching */
}

/* 000040BC-000040F4       .text eInit_SET_TNE___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_SET_TNE_() {
    /* Nonmatching */
}

/* 000040F4-00004114       .text eInit_DEL_TNE___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_DEL_TNE_() {
    /* Nonmatching */
}

/* 00004114-0000417C       .text eInit_SET_ANM___11daNpc_Bj1_cFPiPf */
void daNpc_Bj1_c::eInit_SET_ANM_(int*, f32*) {
    /* Nonmatching */
}

/* 0000417C-000044E4       .text event_actionInit__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::event_actionInit(int) {
    /* Nonmatching */
}

/* 000044E4-00004530       .text eMove_ATTENTION___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eMove_ATTENTION_() {
    /* Nonmatching */
}

/* 00004530-00004580       .text eMove_MOV___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eMove_MOV_() {
    /* Nonmatching */
}

/* 00004580-00004594       .text eMove_JMP___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eMove_JMP_() {
    /* Nonmatching */
}

/* 00004594-000045F0       .text eMove_SET_TNE___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eMove_SET_TNE_() {
    /* Nonmatching */
}

/* 000045F0-00004678       .text eMove_PTH_MOV___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eMove_PTH_MOV_() {
    /* Nonmatching */
}

/* 00004678-000046E8       .text event_action__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::event_action() {
    /* Nonmatching */
}

/* 000046E8-000047D4       .text privateCut__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::privateCut(int) {
    static char* a_cut_tbl[] = { "ACTION" };
    /* Nonmatching */
}

/* 000047D4-000047F4       .text endEvent__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::endEvent() {
    /* Nonmatching */
}

/* 000047F4-0000482C       .text isEventEntry__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::isEventEntry() {
    /* Nonmatching */
}

/* 0000482C-00004914       .text event_proc__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00004914-000049C0       .text set_action__11daNpc_Bj1_cFM11daNpc_Bj1_cFPCvPvPv_iPv */
void daNpc_Bj1_c::set_action(ActionFunc, void*) {
    /* Nonmatching */
}

/* 000049C0-00004B60       .text setStt__11daNpc_Bj1_cFSc */
void daNpc_Bj1_c::setStt(s8) {
    /* Nonmatching */
}

/* 00004B60-00004C30       .text wait_1__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::wait_1() {
    /* Nonmatching */
}

/* 00004C30-00004D10       .text wait_2__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::wait_2() {
    /* Nonmatching */
}

/* 00004D10-00004E2C       .text wait_3__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::wait_3() {
    /* Nonmatching */
}

/* 00004E2C-00004F48       .text wait_4__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::wait_4() {
    /* Nonmatching */
}

/* 00004F48-000050CC       .text flyMov__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::flyMov() {
    /* Nonmatching */
}

/* 000050CC-0000514C       .text fall01__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::fall01() {
    /* Nonmatching */
}

/* 0000514C-00005510       .text talk_1__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::talk_1() {
    /* Nonmatching */
}

/* 00005510-000055D8       .text walk_1__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::walk_1() {
    /* Nonmatching */
}

/* 000055D8-00005694       .text wait_action1__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00005694-0000577C       .text wait_action2__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action2(void*) {
    /* Nonmatching */
}

/* 0000577C-00005860       .text wait_action3__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action3(void*) {
    /* Nonmatching */
}

/* 00005860-00005928       .text wait_action4__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action4(void*) {
    /* Nonmatching */
}

/* 00005928-000059C4       .text demo__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::demo() {
    /* Nonmatching */
}

/* 000059C4-00005AC4       .text shadowDraw__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::shadowDraw() {
    /* Nonmatching */
}

/* 00005AC4-00005E38       .text _draw__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::_draw() {
    /* Nonmatching */
}

/* 00005E38-00006128       .text _execute__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::_execute() {
    /* Nonmatching */
}

/* 00006128-000061A4       .text _delete__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::_delete() {
    /* Nonmatching */
}

/* 000061A4-000061C4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000061C4-000062E4       .text _create__11daNpc_Bj1_cFv */
cPhs_State daNpc_Bj1_c::_create() {
    static u32 a_size_tbl[] = { 0x000272E0, 0x000272E0, 0x000272E0, 0x000272E0, 0x000272E0, 0x000272E0, 0x000272E0, 0x000272E0, 0x000272E0 };
    /* Nonmatching */
}

/* 00006734-00006A00       .text create_Anm__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::create_Anm() {
    /* Nonmatching */
}

/* 00006A00-00006C14       .text create_prp_Anm__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::create_prp_Anm() {
    /* Nonmatching */
}

/* 00006C14-00006F54       .text create_itm_Mdl__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::create_itm_Mdl() {
    static int l_arm_L_bmd_tbl[] = { -1, -1, -1, -1, -1, -1, 25, -1, -1 };
    static int l_arm_R_bmd_tbl[] = { -1, -1, -1, -1, -1, -1, 26, -1, -1 };
    static int l_bmd_tbl[] = { 29, 30, 31, 32, 33, 34, 35, 36, 37 };
    /* Nonmatching */
}

/* 00006F54-00007114       .text CreateHeap__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::CreateHeap() {
    /* Nonmatching */
}

/* 00007114-00007134       .text daNpc_Bj1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Bj1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_create();
}

/* 00007134-00007154       .text daNpc_Bj1_Delete__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_Delete(daNpc_Bj1_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_delete();
}

/* 00007154-00007174       .text daNpc_Bj1_Execute__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_Execute(daNpc_Bj1_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_execute();
}

/* 00007174-00007194       .text daNpc_Bj1_Draw__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_Draw(daNpc_Bj1_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_draw();
}

/* 00007194-0000719C       .text daNpc_Bj1_IsDelete__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_IsDelete(daNpc_Bj1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Bj1_Method = {
    (process_method_func)daNpc_Bj1_Create,   (process_method_func)daNpc_Bj1_Delete, (process_method_func)daNpc_Bj1_Execute,
    (process_method_func)daNpc_Bj1_IsDelete, (process_method_func)daNpc_Bj1_Draw,
};

actor_process_profile_definition g_profile_NPC_BJ1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ1_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ2_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ3 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ3_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ3_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ4 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ4_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ4_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ5 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ5_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ5_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ6 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ6_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ6_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ7 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ7_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ7_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ8 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ8_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ8_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ9 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ9_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ9_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
