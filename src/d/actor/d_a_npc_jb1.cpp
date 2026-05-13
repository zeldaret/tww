/**
 * d_a_npc_jb1.cpp
 * NPC - Jabun
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_jb1.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_jb.h"

class daNpc_Jb1_HIO_c : public JORReflexible{
public:
    struct hio_prm_c {
        f32 field_0x00;
        s16 field_0x04;
        s16 field_0x06;
        s16 field_0x08;
        s16 field_0x0A;
        f32 field_0x0C;
        f32 field_0x10;
    };  // Size: 0x14
    daNpc_Jb1_HIO_c();
    virtual ~daNpc_Jb1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}
public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

static daNpc_Jb1_HIO_c l_HIO;

/* 000000EC-00000144       .text __ct__15daNpc_Jb1_HIO_cFv */
daNpc_Jb1_HIO_c::daNpc_Jb1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        100.0f,
        0,
        1000,
        1000,
        0,
        VERSION_SELECT(2050.0f, 2050.0f, 1200.0f, 2050.0f),
        50.0f,

    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

/* 00000144-00000190       .text init_JB1_0__11daNpc_Jb1_cFv */
bool daNpc_Jb1_c::init_JB1_0() {
    set_action(&daNpc_Jb1_c::wait_action1, NULL);
    return true;
}

/* 00000190-00000264       .text createInit__11daNpc_Jb1_cFv */
bool daNpc_Jb1_c::createInit() {
    cXyz unused(0.0f, 0.0f, -400.0f);
    gravity = 0.0f;

    mEventCut.setActorInfo2("Jb1", this);
    field_0x91C = 2;
    bool temp;
    switch(field_0x921) {
        case 0:
            temp = init_JB1_0();
            break;
        default:
            temp = false;
            break;
    }

    if(temp) {
        shape_angle = current.angle;
    } else {
        return false;
    }
    dKy_plight_set(&field_0x7F8);
    mpMorf->setMorf(0.0f);
    setMtx();
    return true;
}

/* 00000264-0000049C       .text setMtx__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::setMtx() {
    cXyz temp(0.0f, -150.0f, 0.0f);

    playBrkAnm(m_lmp_brk, &field_0x834);
    playBrkAnm(m_lgt_brk, &field_0x858);

    if (!field_0x917) {
        field_0x908 = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mFrame) {
            field_0x908 = true;
        }
        mFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_cse_jnt_num));
    mDoMtx_stack_c::multVec(&temp, &field_0x6D0);
    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_cse_jnt_num));

    mDoMtx_stack_c::transM(0.0f, -150.0f, 0.0f);
    mDoMtx_stack_c::scaleM(2.0f, 2.0f, 2.0f);
    m_lgt_mdl->setBaseTRMtx(mDoMtx_stack_c::get());
    m_lgt_mdl->calc();

    field_0x7F8.mPos.set(field_0x6D0);

    field_0x7F8.mColor.r = l_HIO.mPrmTbl.field_0x06;
    field_0x7F8.mColor.g = l_HIO.mPrmTbl.field_0x08;
    field_0x7F8.mColor.b = l_HIO.mPrmTbl.field_0x0A;
    field_0x7F8.mPower = l_HIO.mPrmTbl.field_0x0C;
    field_0x7F8.mFluctuation = l_HIO.mPrmTbl.field_0x10;
    setAttention();
}

/* 0000049C-000004CC       .text playBrkAnm__11daNpc_Jb1_cFP15J3DAnmTevRegKeyPs */
void daNpc_Jb1_c::playBrkAnm(J3DAnmTevRegKey* param_1, s16* param_2) {
    if (param_1 == NULL) {
        return;
    }
    *param_2 = *param_2 + 1;
    if (*param_2 < param_1->getFrameMax()) {
        return;
    }
    *param_2 = 0;
}

/* 000004CC-000004E0       .text anmNum_toResID__11daNpc_Jb1_cFi */
int daNpc_Jb1_c::anmNum_toResID(int param_1) {
    static const int a_bck_resID_tbl[] = {
        1,
        0
    };
    return a_bck_resID_tbl[param_1];
}

/* 000004E0-00000588       .text setAnm_anm__11daNpc_Jb1_cFPQ211daNpc_Jb1_c9anm_prm_c */
BOOL daNpc_Jb1_c::setAnm_anm(daNpc_Jb1_c::anm_prm_c* i_anmPrmP) {
    if (field_0x91C == i_anmPrmP->field_0x0) {
        return TRUE;
    }

    field_0x91C = i_anmPrmP->field_0x0;

    dNpc_setAnmIDRes(
        mpMorf,
        i_anmPrmP->mLoopMode,
        i_anmPrmP->mMorf,
        i_anmPrmP->mPlaySpeed,
        anmNum_toResID(field_0x91C),
        -1,
        "Jb"
    );
    mFrame = 0.0f;
    field_0x909 = 0;
    field_0x908 = 0;
    return TRUE;
}

/* 00000588-000005D0       .text setAnm__11daNpc_Jb1_cFv */
BOOL daNpc_Jb1_c::setAnm() {
    static daNpc_Jb1_c::anm_prm_c a_anm_prm_tbl[2] = {
        {-1, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},

    };

    if(a_anm_prm_tbl[field_0x91E].field_0x0 >= 0){
        setAnm_anm(&a_anm_prm_tbl[field_0x91E]);
    }
    return TRUE;
}

/* 000005D0-000005D4       .text chg_anmTag__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::chg_anmTag() {
}

/* 000005D4-000005D8       .text control_anmTag__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::control_anmTag() {
}

/* 000005D8-00000618       .text chg_anmAtr__11daNpc_Jb1_cFUc */
void daNpc_Jb1_c::chg_anmAtr(u8 param_1) {
    if(param_1 >= 1 || param_1 == field_0x91A) {
        return;
    }

    field_0x91A = param_1;
    setAnm_ATR();
}

/* 00000618-00000624       .text control_anmAtr__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::control_anmAtr() {
    switch(field_0x91A) {
        case 0:
            break;
    }
}

/* 00000624-00000658       .text setAnm_ATR__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::setAnm_ATR() {
    static daNpc_Jb1_c::anm_prm_c a_anm_prm_tbl[1] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    setAnm_anm(&a_anm_prm_tbl[field_0x91A]);
}

/* 00000658-0000071C       .text anmAtr__11daNpc_Jb1_cFUs */
void daNpc_Jb1_c::anmAtr(u16 param_1) {
    switch(param_1) {
        case 6: {
            if (field_0x923 == 0) {
                field_0x91A = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x923++;
            }

            u8 mesgTagInfo = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if (mesgTagInfo != 0xFF && field_0x91B != mesgTagInfo) {
                field_0x91B = mesgTagInfo;
                chg_anmTag();
            }
            break;
        }
        case 0xE:
            field_0x923 = 0;
            break;
    }

    control_anmTag();
    control_anmAtr();
}

/* 0000071C-0000076C       .text eventOrder__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::eventOrder() {
    if ((field_0x91D == 1 || field_0x91D == 2)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(field_0x91D == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 0000076C-000007AC       .text checkOrder__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::checkOrder() {
    if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        return;
    }

    if (eventInfo.mCommand != dEvtCmd_INTALK_e) {
        return;
    }

    if (field_0x91D != 1 && field_0x91D != 2) {
        return;
    }
    field_0x91D = 0;
    field_0x915 = 1;
}

/* 000007AC-000007B4       .text next_msgStatus__11daNpc_Jb1_cFPUl */
u16 daNpc_Jb1_c::next_msgStatus(u32* pMsgNo) {
    return 0x10;
}

/* 000007B4-000007BC       .text getMsg_JB1_0__11daNpc_Jb1_cFv */
u32 daNpc_Jb1_c::getMsg_JB1_0() {
    return 0;
}

/* 000007BC-000007F8       .text getMsg__11daNpc_Jb1_cFv */
u32 daNpc_Jb1_c::getMsg() {
    u32 msg = 0;
    switch(field_0x921) {
        case 0:
            msg = getMsg_JB1_0();
            break;
    }

    return msg;
}

/* 000007F8-00000878       .text chkAttention__11daNpc_Jb1_cFv */
bool daNpc_Jb1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();

    if(attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }

    return this == attention.ActionTarget(0);
}

/* 00000878-0000093C       .text setAttention__11daNpc_Jb1_cFv */
void daNpc_Jb1_c::setAttention() {
    cXyz temp(0.0f, 1100.0f, 700.0f);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&temp, &field_0x8F4);
    attention_info.position.set(field_0x8F4.x, field_0x8F4.y + l_HIO.mPrmTbl.field_0x00, field_0x8F4.z);
    eyePos.set(field_0x8F4.x, field_0x8F4.y, field_0x8F4.z);
}

/* 0000093C-00000958       .text charDecide__11daNpc_Jb1_cFi */
bool daNpc_Jb1_c::charDecide(int) {
    field_0x920 = 0;
    field_0x921 = -1;
    field_0x921 = 0;
    return true;
}

/* 00000958-000009B0       .text event_actionInit__11daNpc_Jb1_cFi */
void daNpc_Jb1_c::event_actionInit(int staffIdx) {
    int* actNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "ActNo");
    if(actNo != NULL){
        mActNo = *actNo;
    }
}

/* 000009B0-000009D0       .text event_action__11daNpc_Jb1_cFv */
bool daNpc_Jb1_c::event_action() {
    switch(mActNo) {
        case 0:
            return true;
    }
    return true;
}

/* 000009D0-00000ABC       .text privateCut__11daNpc_Jb1_cFi */
void daNpc_Jb1_c::privateCut(int staffIdx) {
    static char* a_cut_tbl[] = {
        "ACTION"
    };

    if(staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(staffIdx, a_cut_tbl, ARRAY_SSIZE(a_cut_tbl), TRUE, 0);
        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch(mActIdx) {
                    case 0:
                        event_actionInit(staffIdx);
                        break;
                }
            }
            bool temp;
            switch(mActIdx) {
                case 0:
                    temp = event_action();
                    break;
                default:
                    temp = true;
                    break;
            }
            if(temp) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }   

    }
}

/* 00000ABC-00000AF4       .text isEventEntry__11daNpc_Jb1_cFv */
int daNpc_Jb1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00000AF4-00000B44       .text event_proc__11daNpc_Jb1_cFi */
void daNpc_Jb1_c::event_proc(int param_1) {
    if (!mEventCut.cutProc()) {
        privateCut(param_1);
    }
}

/* 00000B44-00000BF0       .text set_action__11daNpc_Jb1_cFM11daNpc_Jb1_cFPCvPvPv_iPv */
BOOL daNpc_Jb1_c::set_action(ActionFunc actionFunc, void* arg) {
    if (mCurrActionFunc != actionFunc) {
        if (mCurrActionFunc != NULL) {
            field_0x922 = 9;
            (this->*mCurrActionFunc)(arg);
        }
        mCurrActionFunc = actionFunc;
        field_0x922 = 0;
        (this->*mCurrActionFunc)(arg);
    }
    return TRUE;
}

/* 00000BF0-00000C20       .text setStt__11daNpc_Jb1_cFSc */
void daNpc_Jb1_c::setStt(s8 param_1) {
    field_0x91E = param_1;
    switch (field_0x91E) {
        case 0:
        case 1:
            break;
    }

    setAnm();
}

/* 00000C20-00000C28       .text wait_1__11daNpc_Jb1_cFv */
BOOL daNpc_Jb1_c::wait_1() {
    return TRUE;
}

/* 00000C28-00000CBC       .text wait_action1__11daNpc_Jb1_cFPv */
BOOL daNpc_Jb1_c::wait_action1(void*) {
    switch(field_0x922) {
        case 9:
            break;
        case 0:
            setStt(1);
            field_0x922++;
            break;
        case 1:
        case 2:
        case 3:
            mHasAttention = chkAttention();
            switch(field_0x91E) {
                case 1:
                    field_0x910 = wait_1();
                    break;
            }
            break;
    }
    return TRUE;
}

/* 00000CBC-00000D58       .text demo__11daNpc_Jb1_cFv */
bool daNpc_Jb1_c::demo() {
    if (demoActorID == 0) {
        if (field_0x917) {
            field_0x917 = false;
        }
    } else {
        field_0x917 = true;
        dComIfGp_demo_getActor(demoActorID);
        dDemo_setDemoData(
            this,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf,
            "Jb"
        );
    }
    return field_0x917;
}

static const u32 dummyColor[] = {
    0xFFFFFF80,
    0xFF000080,
    0x0000FF80,
    0x00000000,
};

/* 00000D58-00000E74       .text _draw__11daNpc_Jb1_cFv */
BOOL daNpc_Jb1_c::_draw() {
    J3DModelData* lgtModelData;
    J3DModel* pModel;
    J3DModelData* modelData;
    
    lgtModelData = m_lgt_mdl->getModelData();
    pModel = mpMorf->getModel();
    modelData = pModel->getModelData();

    if (field_0x90C || field_0x90E) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBrkAnm.entry(modelData, field_0x834);
    mpMorf->entryDL();
    mBrkAnm.remove(modelData);
    mBrkAnm2.entry(lgtModelData, field_0x858);
    mDoExt_modelEntryDL(m_lgt_mdl);
    mBrkAnm2.remove(lgtModelData);
    return TRUE;
}

/* 00000E74-00000FBC       .text _execute__11daNpc_Jb1_cFv */
BOOL daNpc_Jb1_c::_execute() {
    if (!field_0x90F) {
        mCurrentPos.set(current.pos);
        mCurrentRot = current.angle;
        field_0x90F = true;
    }

    if (field_0x90C && demoActorID == 0) {
        return TRUE;
    }

    field_0x90C = false;
    checkOrder();
    if (!demo()) {
        int temp = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
            temp = isEventEntry();
        }

        if(temp >= 0) {
            event_proc(temp);
        } else {
            (this->*mCurrActionFunc)(NULL);
        }
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        if (!field_0x90D) {
            shape_angle = current.angle;
        }
    }
    eventOrder();
    setMtx();
    return TRUE;
}

/* 00000FBC-00001054       .text _delete__11daNpc_Jb1_cFv */
BOOL daNpc_Jb1_c::_delete() {
    fopAcM_RegisterDeleteID(this);

    dComIfG_resDeleteDemo(&mPhs, "Jb");
    dKy_plight_cut(&field_0x7F8);

    if(
#if VERSION > VERSION_DEMO
        heap != NULL &&
#endif
        mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }

    if(l_HIO.field_0x8 >= 0) {
        l_HIO.field_0x8--;
        if(l_HIO.field_0x8 < 0) {
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return TRUE;
}

/* 00001054-00001074       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Jb1_c*)i_this)->CreateHeap();
}

/* 00001074-000011B8       .text _create__11daNpc_Jb1_cFv */
cPhs_State daNpc_Jb1_c::_create() {
    fopAcM_RegisterCreateID(this);

    static u32 a_size_tbl[] = {
        0x000272E0
    };

    fopAcM_ct_Retail(this, daNpc_Jb1_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, "Jb");
    switch(phase_state) {
        case cPhs_COMPLEATE_e:
            u8 param = fopAcM_GetParam(this);
            if (!charDecide(param)) {
                return cPhs_ERROR_e;
            }

            if(l_HIO.field_0x8 < 0) {
                l_HIO.mNo = mDoHIO_createChild("ジャブ−", &l_HIO);
            }
            l_HIO.field_0x8++;

            fopAcM_ct_Demo(this, daNpc_Jb1_c);

            if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[field_0x920])) {
                return cPhs_ERROR_e;
            }
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            if(createInit() == 0) {
                return cPhs_ERROR_e;
            }
            return phase_state;
    }
    return phase_state;
}

daNpc_Jb1_c::daNpc_Jb1_c() {}

/* 00001780-00001A0C       .text create_Anm__11daNpc_Jb1_cFv */
J3DModelData* daNpc_Jb1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Jb", JB_BDL_JB);
    JUT_ASSERT(VERSION_SELECT(0x450, 0x45A, 0x45F, 0x45F), a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectIDRes("Jb", JB_BCK_JB_WAIT01),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x11020022
    );

    if(mpMorf == NULL) {
        return NULL;
    } else if(mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    } else {
        m_lmp_brk = (J3DAnmTevRegKey*)dComIfG_getObjectIDRes("Jb", JB_BRK_JB_LAMP);
        JUT_ASSERT(VERSION_SELECT(0x464, 0x46E, 0x473, 0x473), m_lmp_brk != NULL);
        bool temp = mBrkAnm.init(mpMorf->getModel()->getModelData(), m_lmp_brk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
        if(temp == false) {
            mpMorf = NULL;
            return NULL;
        } else {
            field_0x834 = 0;
            m_cse_jnt_num = mpMorf->getModel()->getModelData()->getJointName()->getIndex("jb_case");
            JUT_ASSERT(VERSION_SELECT(0x46F, 0x479, 0x47E, 0x47E), m_cse_jnt_num >= 0);
        }
    }
    return a_mdl_dat;
}

// Probably unused JUT_ASSERTS
static void dummy() {
    OSReport("m_app_mdl != 0");
    OSReport("m_app_bck != 0");
    OSReport("m_app_btk != 0");
    OSReport("m_app_brk != 0");
    OSReport("splash");
    OSReport("m_spl_jnt_num >= 0");
}

/* 00001A0C-00001B78       .text create_lgt__11daNpc_Jb1_cFv */
bool daNpc_Jb1_c::create_lgt() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectIDRes("Jb", JB_BMD_LF);
    m_lgt_mdl = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    JUT_ASSERT(VERSION_SELECT(0x4B6, 0x4C0, 0x4C5, 0x4C5), m_lgt_mdl != NULL);

    m_lgt_brk = (J3DAnmTevRegKey*)dComIfG_getObjectIDRes("Jb", JB_BRK_LF);
    JUT_ASSERT(VERSION_SELECT(0x4BB, 0x4C5, 0x4CA, 0x4CA), m_lgt_brk != NULL);
    bool temp = mBrkAnm2.init(m_lgt_mdl->getModelData(), m_lgt_brk, true, J3DFrameCtrl::EMode_LOOP);

    if (!temp) {
        return temp;
    }

    field_0x858 = 0;
    return temp;
}

/* 00001B78-00001C20       .text CreateHeap__11daNpc_Jb1_cFv */
BOOL daNpc_Jb1_c::CreateHeap() {
    if(create_Anm() == NULL) {
        return false;
    }
    if(!create_lgt()) {
        return false;
    }
    
    mpMorf->getModel()->setUserArea(NULL);
    mAcchCir.SetWall(0.0f, 0.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    return true;
}

/* 00001C20-00001C40       .text daNpc_Jb1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Jb1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Jb1_c*)i_this)->_create();
}

/* 00001C40-00001C60       .text daNpc_Jb1_Delete__FP11daNpc_Jb1_c */
static BOOL daNpc_Jb1_Delete(daNpc_Jb1_c* i_this) {
    return ((daNpc_Jb1_c*)i_this)->_delete();
}

/* 00001C60-00001C80       .text daNpc_Jb1_Execute__FP11daNpc_Jb1_c */
static BOOL daNpc_Jb1_Execute(daNpc_Jb1_c* i_this) {
    return ((daNpc_Jb1_c*)i_this)->_execute();
}

/* 00001C80-00001CA0       .text daNpc_Jb1_Draw__FP11daNpc_Jb1_c */
static BOOL daNpc_Jb1_Draw(daNpc_Jb1_c* i_this) {
    return ((daNpc_Jb1_c*)i_this)->_draw();
}

/* 00001CA0-00001CA8       .text daNpc_Jb1_IsDelete__FP11daNpc_Jb1_c */
static BOOL daNpc_Jb1_IsDelete(daNpc_Jb1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Jb1_Method = {
    (process_method_func)daNpc_Jb1_Create,
    (process_method_func)daNpc_Jb1_Delete,
    (process_method_func)daNpc_Jb1_Execute,
    (process_method_func)daNpc_Jb1_IsDelete,
    (process_method_func)daNpc_Jb1_Draw,
};

actor_process_profile_definition g_profile_NPC_JB1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_JB1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Jb1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_JB1,
    /* Actor SubMtd */ &l_daNpc_Jb1_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
