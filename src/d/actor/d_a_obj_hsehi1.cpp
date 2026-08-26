/**
 * d_a_obj_hsehi1.cpp
 * Object - Tower of the Gods - Command Melody monument & blue monument next to Companion Statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hsehi1.h"
#include "d/actor/d_a_player.h"
#include "res/Object/Hsehi1.h"
#include "res/Object/Hsehi2.h"

static daObj_hsh_HIO_c l_HIO;
static s32 l_hio_counter;

static fpc_ProcID l_msgId;
static msg_class* l_msg;

/* 000000EC-00000130       .text __ct__15daObj_hsh_HIO_cFv */
daObj_hsh_HIO_c::daObj_hsh_HIO_c() {
    mNo = -1;
    static const hio_prm_c init_data = {
        /* mAttnDist   */ 250.0f,
        /* field_0x0c  */ 0.0f,
        /* field_0x10  */ 0.0f,
        /* mAttnAngle  */ 0x4000,
        /* field_0x16  */ 0,
    };
    prm = init_data;
}

/* 00000130-000002A4       .text __dt__11daObj_hsh_cFv */
daObj_hsh_c::~daObj_hsh_c() {
    if (argument == 0) {
        dComIfG_resDelete(&mPhase, "Hsehi1");
    } else {
        dComIfG_resDelete(&mPhase, "Hsehi2");
    }

    if (mpBgW != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }

    emitterDelete(&mpEmitter);

    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
}

/* 000002A4-000002C4       .text daObj_hsh_XyCheckCB__FPvi */
static s16 daObj_hsh_XyCheckCB(void* i_this, int i_itemBtn) {
    return static_cast<daObj_hsh_c*>(i_this)->XyCheckCB(i_itemBtn);
}

/* 000002C4-000002E8       .text XyCheckCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyCheckCB(int i_itemBtn) {
    if (dComIfGp_getSelectItem(i_itemBtn) == dItemNo_WIND_WAKER_e) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 000002E8-00000308       .text daObj_hsh_XyEventCB__FPvi */
static s16 daObj_hsh_XyEventCB(void* i_this, int i_itemBtn) {
    return static_cast<daObj_hsh_c*>(i_this)->XyEventCB(i_itemBtn);
}

/* 00000308-00000390       .text XyEventCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyEventCB(int) {
    fopAcM_seStart(this, JA_SE_PRE_TAKT, 0);
    onEventAccept();
    mEventSelector = 0;
    return mEventId[0];
}

/* 00000390-000003F4       .text particle_set__11daObj_hsh_cFUs */
void daObj_hsh_c::particle_set(u16 i_particleId) {
    dComIfGp_particle_set(i_particleId, &current.pos, &current.angle);
}

/* 000003F4-00000488       .text particle_set__11daObj_hsh_cFPP14JPABaseEmitterUs */
void daObj_hsh_c::particle_set(JPABaseEmitter** pEmitter, u16 i_particleId) {
    if (*pEmitter == NULL) {
        *pEmitter = dComIfGp_particle_set(i_particleId, &current.pos, &current.angle);
        if (*pEmitter != NULL) {
            (*pEmitter)->becomeImmortalEmitter();
        }
    }
}

/* 00000488-000004C4       .text emitterDelete__11daObj_hsh_cFPP14JPABaseEmitter */
void daObj_hsh_c::emitterDelete(JPABaseEmitter** pEmitter) {
    if (*pEmitter != NULL) {
        (*pEmitter)->quitImmortalEmitter();
        (*pEmitter)->becomeInvalidEmitter();
        *pEmitter = NULL;
    }
}

/* 000004C4-00000568       .text setAttention__11daObj_hsh_cFb */
void daObj_hsh_c::setAttention(bool set) {
    if (!set) {
        return;
    }

    f32 y1;
    f32 currZ;
    f32 y2;

    if (argument == 0) {
        y1 = 90.0f + current.pos.y + l_HIO.prm.field_0x10;
        y2 = 180.0f + current.pos.y + l_HIO.prm.field_0x0c;
    } else {
        y1 = 80.0f + current.pos.y + l_HIO.prm.field_0x10;
        y2 = 120.0f + current.pos.y + l_HIO.prm.field_0x0c;
    }

    currZ = current.pos.z;
    eyePos.set(current.pos.x, y1, currZ);
    attention_info.position.set(current.pos.x, y2, current.pos.z);
}

/* 00000568-000005AC       .text onOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::onOffDraw() {
    cLib_onBit<u32>(mFlags, 8);
    if (mpBgW != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
}

/* 000005AC-000005F4       .text offOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::offOffDraw() {
    cLib_offBit<u32>(mFlags, 8);
    if (mpBgW != NULL) {
        dComIfG_Bgsp()->Regist(mpBgW, this);
    }
}

/* 000005F4-0000062C       .text drawStop__11daObj_hsh_cFv */
void daObj_hsh_c::drawStop() {
    onOffDraw();
    emitterDelete(&mpEmitter);
}

/* 0000062C-0000064C       .text drawStart__11daObj_hsh_cFv */
void daObj_hsh_c::drawStart() {
    offOffDraw();
}

/* 0000064C-000006C8       .text setBaseMtx__11daObj_hsh_cFv */
void daObj_hsh_c::setBaseMtx() {
    J3DModel* model = mpModel;

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);

    model->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
}

/* 000006C8-00000910       .text createHeap__11daObj_hsh_cFv */
BOOL daObj_hsh_c::createHeap() {
    if (argument == 0) {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi1", dRes_INDEX_HSEHI1_BDL_HSEHI1_e);
        JUT_ASSERT(0x1f9, modelData != NULL);

        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return FALSE;
        }

        mpBgW = new dBgW();
        if (mpBgW != NULL) {
            cBgD_t* dzb = (cBgD_t*)dComIfG_getObjectRes("Hsehi1", dRes_INDEX_HSEHI1_DZB_HSEHI1_e);
            if (mpBgW->Set(dzb, cBgW::MOVE_BG_e, &mMtx)) {
                return FALSE;
            }
        } else {
            return FALSE;
        }
    } else {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi2", dRes_INDEX_HSEHI2_BDL_HSEHI2_e);
        JUT_ASSERT(0x20f, modelData != NULL);

        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return FALSE;
        }

        mpBgW = new dBgW();
        if (mpBgW != NULL) {
            cBgD_t* dzb = (cBgD_t*)dComIfG_getObjectRes("Hsehi2", dRes_INDEX_HSEHI2_DZB_HSEHI2_e);
            if (mpBgW->Set(dzb, cBgW::MOVE_BG_e, &mMtx)) {
                return FALSE;
            }
        } else {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00000910-00000930       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daObj_hsh_c*>(i_this)->createHeap();
}

/* 00000930-00000B44       .text create__11daObj_hsh_cFv */
cPhs_State daObj_hsh_c::create() {
    static u32 a_heap_size_tbl = 0x4000;

    fopAcM_ct_Retail(this, daObj_hsh_c);

#if VERSION <= VERSION_JPN
    if (argument == 0 && dComIfGs_isTact(2)) {
        return cPhs_ERROR_e;
    }
#else
    if (argument == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_2510)) {
        return cPhs_ERROR_e;
    }
#endif

    cPhs_State st;
    if (argument == 0) {
        st = dComIfG_resLoad(&mPhase, "Hsehi1");
    } else {
        st = dComIfG_resLoad(&mPhase, "Hsehi2");
    }
    if (st == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(this, daObj_hsh_c);
        if (!fopAcM_entrySolidHeap(this, checkCreateHeap, a_heap_size_tbl)) {
#if VERSION > VERSION_DEMO
            mpBgW = NULL;
#endif
            return cPhs_ERROR_e;
        }
        fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
        if (l_HIO.mNo < 0) {
            if (argument == 0) {
                // "Takuto (wind waker) stone monument"
                l_HIO.mNo = mDoHIO_createChild("タクト石版", &l_HIO);
            } else {
                // "Message stone monument"
                l_HIO.mNo = mDoHIO_createChild("メッセージ石碑", &l_HIO);
            }
            l_HIO.mpActor = this;
        }
        if (init() == 0) {
            st = cPhs_ERROR_e;
        }
    }
    return st;
}

static char* event_name_tbl[] = {
    "hsehi1_tact",
    "hsehi1_talk",
};

/* 00000C84-00000E60       .text init__11daObj_hsh_cFv */
BOOL daObj_hsh_c::init() {
    mSwitchNo = fopAcM_GetParam(this) & 0xff;
    mPrmMsgNo = (fopAcM_GetParam(this) >> 8) & 0xffff;
    mAttentionLatch = 0;
    field_0x514 = -1;
    mEventSelector = -1;
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    setBaseMtx();
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mpBgW->Move();

    if (argument == 0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2B10)) {
            setAction(&daObj_hsh_c::waitAction, NULL);
        } else {
            onOffDraw();
            setAction(&daObj_hsh_c::offAction, NULL);
        }
    } else {
        setAction(&daObj_hsh_c::waitAction, NULL);
    }

    for (int i = 0; i < 2; i++) {
        mEventId[i] = dComIfGp_evmng_getEventIdx(event_name_tbl[i], 0xff);
    }

    eventInfo.setXyCheckCB(daObj_hsh_XyCheckCB);
    eventInfo.setXyEventCB(daObj_hsh_XyEventCB);
    return TRUE;
}

/* 00000E60-00000EF4       .text action__11daObj_hsh_cFPv */
void daObj_hsh_c::action(void* fnArg) {
    if (!mAction) {
        speedF = 0.0;
        setAction(&daObj_hsh_c::waitAction, NULL);
    }
    (this->*mAction)(fnArg);
}

/* 00000EF4-00000FBC       .text setAction__11daObj_hsh_cFM11daObj_hsh_cFPCvPvPv_iPv */
BOOL daObj_hsh_c::setAction(ActionFunc i_action, void* fnArg) {
    if (mAction != i_action) {
        if (mAction) {
            mActionMode = -1;
            (this->*mAction)(fnArg);
        }

        mAction = i_action;

        mActionMode = 0;
        field_0x51c = 0;
        field_0x51e = 0;
        field_0x520 = 0;
        field_0x522 = 0;
        field_0x528 = 0;

        (this->*mAction)(fnArg);
    }
    return 1;
}

/* 00000FBC-000010E8       .text waitAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::waitAction(void*) {
    if (mActionMode == 0) {
        mActionMode++;
    } else if (mActionMode != -1) {
        mAttentionLatch = chkAttention(current.pos, shape_angle.y);

        if (argument == 0) {
            if (mAttentionLatch) {
                cLib_onBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
                if (field_0x514 == -1) {
                    field_0x514 = 5;
                }
            } else {
                cLib_offBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
            }
        } else if (mAttentionLatch) {
            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
            if (field_0x514 == -1) {
                field_0x514 = 3;
            }
        } else {
            cLib_offBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
        }
        setAttention(TRUE);
    }
    return 1;
}

/* 000010E8-00001214       .text talkAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::talkAction(void*) {
    if (mActionMode == 0) {
        l_msgId = -1;
        mMsgNo = getMsg();
        mActionMode++;
        if (argument == 0) {
            ((daPy_py_c*)dComIfGp_getLinkPlayer())->onPlayerNoDraw();
        }
    } else if (mActionMode != -1) {
        if (mActionMode == 1) {
            BOOL success = talk_init();
            if (success) {
                mActionMode++;
            }
        } else {
            BOOL success = talk(0);
            if (success) {
                setAction(&daObj_hsh_c::waitAction, NULL);
                dComIfGp_event_reset();
                if (argument == 0) {
                    ((daPy_py_c*)dComIfGp_getLinkPlayer())->offNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
                }
            }
        }
        setAttention(true);
    }
    return true;
}

/* 00001214-00001230       .text offAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::offAction(void*) {
    if (mActionMode == 0) {
        mActionMode++;
    }
    return TRUE;
}

/* 00001230-00001278       .text deleteAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::deleteAction(void*) {
    if (mActionMode == 0) {
        mActionMode++;
    } else if (mActionMode != -1) {
        fopAcM_delete(this);
    }
    return TRUE;
}

/* 00001278-0000135C       .text eventOrder__11daObj_hsh_cFv */
void daObj_hsh_c::eventOrder() {
    if (!isEventAccept()) {
        if ((field_0x514 == 4) || (field_0x514 == 3)) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
            if (field_0x514 == 4) {
                fopAcM_orderSpeakEvent(this);
            }
        } else if (field_0x514 == 5) {
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
            if (argument == 0) {
                eventInfo.setEventName("hsehi1_talk");
            }
        } else if ((field_0x514 != -1) && (field_0x514 < 2)) {
            mEventSelector = field_0x514;
            fopAcM_orderOtherEventId(this, mEventId[mEventSelector]);
        }
    }
    return;
}

/* 0000135C-0000140C       .text checkOrder__11daObj_hsh_cFv */
void daObj_hsh_c::checkOrder() {
    if (eventInfo.checkCommandTalk() && (field_0x514 == 4 || field_0x514 == 3 || field_0x514 == 5)) {
        field_0x514 = 0xff;
        if (!dComIfGp_event_chkTalkXY()) {
            setAction(&daObj_hsh_c::talkAction, NULL);
        }
    }
}

/* 0000140C-00001478       .text checkCommandTalk__11daObj_hsh_cFv */
BOOL daObj_hsh_c::checkCommandTalk() {
    if (eventInfo.checkCommandTalk()) {
        if (dComIfGp_event_chkTalkXY()) {
            if (field_0x514 == 5) {
                field_0x514 = 0xff;
            }
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

/* 00001478-000015E0       .text chkAttention__11daObj_hsh_cF4cXyzs */
bool daObj_hsh_c::chkAttention(cXyz i_pos, s16 i_angleY) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 dist = l_HIO.prm.mAttnDist;
    int angle = l_HIO.prm.mAttnAngle;
    cXyz delta;
    delta.x = player->current.pos.x - i_pos.x;
    delta.z = player->current.pos.z - i_pos.z;
    f32 d = std::sqrtf(delta.x * delta.x + delta.z * delta.z);
    s16 targetAngle = cM_atan2s(delta.x, delta.z);
    delta.y = player->current.pos.y - i_pos.y;
    if (mAttentionLatch != 0) {
        dist += 40.0f;
        angle += 0x71C;
    }
    s16 diff = targetAngle;
    diff -= i_angleY;

    return angle > abs(diff) && dist > d;
}

static daObj_hsh_c::EventActionInitFunc event_init_tbl[] = {
    &daObj_hsh_c::initialDefault,
    &daObj_hsh_c::initialLinkDispEvent,
    &daObj_hsh_c::initialMsgSetEvent,
    &daObj_hsh_c::initialDefault,
    &daObj_hsh_c::initialDefault,
    &daObj_hsh_c::initialJudgeEvent,
    &daObj_hsh_c::initialAppearEvent,
    &daObj_hsh_c::initialDeleteEvent,
};

static daObj_hsh_c::EventActionFunc event_action_tbl[] = {
    &daObj_hsh_c::actionDefault,
    &daObj_hsh_c::actionDefault,
    &daObj_hsh_c::actionMsgSetEvent,
    &daObj_hsh_c::actionMessageEvent,
    &daObj_hsh_c::actionTactEvent,
    &daObj_hsh_c::actionDefault,
    &daObj_hsh_c::actionAppearEvent,
    &daObj_hsh_c::actionDeleteEvent,
};

static char* cut_name_tbl[] = {
    "WAIT",
    "Disp",
    "MsgSet",
    "Talk",
    "Tact",
    "Judge",
    "Appear",
    "Delete",
};

/* 000015E0-00001784       .text eventProc__11daObj_hsh_cFv */
BOOL daObj_hsh_c::eventProc() {
    if (eventInfo.checkCommandDemoAccrpt() && field_0x514 != -1) {
        onEventAccept();
        field_0x514 = 0xff;
    }

    int staffIdx = dComIfGp_evmng_getMyStaffId("Hsh", NULL, 0);

    if ((dComIfGp_event_runCheck()) && (!checkCommandTalk())) {
        if (staffIdx != -1) {
            int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
            if (actIdx == -1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            } else {
                if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                    (this->*event_init_tbl[actIdx])(staffIdx);
                }
                BOOL res = (this->*event_action_tbl[actIdx])(staffIdx);
                if (res != 0) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }
        }
        if (isEventAccept()) {
            if (dComIfGp_evmng_endCheck(mEventId[mEventSelector])) {
                eventEnd();
            }
            return TRUE;
        }
        if (staffIdx != -1) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00001784-000017B0       .text eventEnd__11daObj_hsh_cFv */
void daObj_hsh_c::eventEnd() {
    dComIfGp_event_reset();
    offEventAccept();
    mEventSelector = -1;
}

/* 000017B0-000017B4       .text initialDefault__11daObj_hsh_cFi */
void daObj_hsh_c::initialDefault(int) {
}

/* 000017B4-000017BC       .text actionDefault__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionDefault(int) {
    return TRUE;
}

/* 000017BC-00001938       .text initialLinkDispEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialLinkDispEvent(int i_staffId) {
    char buf[10];
    char* p = dComIfGp_evmng_getMyStringP(i_staffId, "target");

    BOOL isPlayer = FALSE;

    if (p != NULL) {
        strcpy(buf, p);
        if (strcmp(buf, "@PLAYER") == 0) {
            isPlayer = TRUE;
        }
    }

    p = dComIfGp_evmng_getMyStringP(i_staffId, "disp");

    if (isPlayer == TRUE) {
        if (p != NULL) {
            strcpy(buf, p);
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
            if (strcmp(buf, "on") == 0)
                player->offPlayerNoDraw();
            if (strcmp(buf, "off") == 0)
                player->onPlayerNoDraw();
        }
    } else {
        if (p != NULL) {
            strcpy(buf, p);
            if (strcmp(buf, "on") == 0)
                drawStart();
            if (strcmp(buf, "off") == 0)
                drawStop();
        }
    }
}

/* 00001938-000019C0       .text initialMsgSetEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialMsgSetEvent(int staffIdx) {
    l_msgId = -1;
    mMsgNo = 0x0;

    int* pMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if (pMsgNo != NULL) {
        mMsgNo = *pMsgNo;
        if (mMsgNo == 0x5b3) {
            dComIfGp_setMelodyNum(2); // Command melody
        }
    }
}

/* 000019C0-000019E0       .text actionMsgSetEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionMsgSetEvent(int) {
    talk_init();
}

/* 000019E0-00001A40       .text actionMessageEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionMessageEvent(int staffIdx) {
    int* p_talkMode = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm0");
    int i_talkMode = 0;
    if (p_talkMode != NULL) {
        i_talkMode = *p_talkMode;
    }
    talk(i_talkMode);
}

/* 00001A40-00001ADC       .text actionTactEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionTactEvent(int staffIdx) {
    int* p_talkMode = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm0");
    int i_talkMode = 0;
    if (p_talkMode != NULL) {
        i_talkMode = *p_talkMode;
    }
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    int music = player->getTactMusic();

    if (music == i_talkMode) {
        onTactCorrect();
    }
    talk(1);
}

/* 00001ADC-00001B3C       .text initialJudgeEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialJudgeEvent(int) {
    if (isTactCorrect()) {
        offTactCorrect();
    } else {
        if (isTactCancel()) {
            drawStart();
            offTactCancel();
            eventEnd();
        }
    }
}

/* 00001B3C-00001C1C       .text initialAppearEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialAppearEvent(int) {
    dComIfGs_onEventBit(dSv_event_flag_c::UNK_2B10);
    particle_set(dPa_name::ID_AK_SN_OTOMOSEKIHILIGHT00);
    particle_set(&mpEmitter, dPa_name::ID_AK_SN_OTOMOSEKIHILIGHT01);

    fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_TAKT_GR_ON, 0);

    mAppearDeleteTimer = 30;
    setAction(&daObj_hsh_c::waitAction, NULL);
}

/* 00001C1C-00001C74       .text actionAppearEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionAppearEvent(int) {
    if (cLib_calcTimer(&mAppearDeleteTimer) == 0) {
        offOffDraw();
        emitterDelete(&mpEmitter);
        return TRUE;
    }
    return FALSE;
}

/* 00001C74-00001D3C       .text initialDeleteEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialDeleteEvent(int) {
    particle_set(dPa_name::ID_AK_SN_OTOMOSEKIHILIGHT00);
    particle_set(&mpEmitter, dPa_name::ID_AK_SN_OTOMOSEKIHILIGHT01);

    fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_TAKT_GR_ON, 0);

    mAppearDeleteTimer = 60;
    setAction(&daObj_hsh_c::deleteAction, NULL);
}

/* 00001D3C-00001D88       .text actionDeleteEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionDeleteEvent(int) {
    if (cLib_calcTimer(&mAppearDeleteTimer) == 0) {
        drawStop();
        return TRUE;
    }

    return FALSE;
}

/* 00001D88-00001DF4       .text talk_init__11daObj_hsh_cFv */
BOOL daObj_hsh_c::talk_init() {
    if (l_msgId == -1) {
        l_msgId = fopMsgM_messageSet(mMsgNo, this);
    } else {
        l_msg = fopMsgM_SearchByID(l_msgId);
        if (l_msg != NULL) {
            return 1;
        }
    }
    return 0;
}

/* 00001DF4-00001F1C       .text talk__11daObj_hsh_cFi */
BOOL daObj_hsh_c::talk(int i_mode) {
    u16 status = l_msg->mStatus;
    if (status == fopMsgStts_MSG_DISPLAYED_e) {
        if (i_mode == 1) {
            if (dComIfGp_checkMesgCancelButton() != 0) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
                onTactCancel();
            } else if (isTactCorrect()) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
                if (mMsgNo == 0x5b3) {
                    s8 roomNo = fopAcM_GetRoomNo(this);
                    dComIfGs_onSwitch(mSwitchNo, roomNo);
                }
            }
        } else {
            u16 nextMsgStatus = next_msgStatus(&mMsgNo);
            l_msg->mStatus = nextMsgStatus;
            if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(mMsgNo);
            }
        }
    } else if (status == fopMsgStts_INPUT_e) {
        if (i_mode == 2) {
            return 1;
        }
    }

    else if ((status != fopMsgStts_MSG_TYPING_e) && (status == fopMsgStts_BOX_CLOSED_e))
    {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
        return 1;
    }
    return 0;
}

/* 00001F1C-00001F38       .text getMsg__11daObj_hsh_cFv */
u32 daObj_hsh_c::getMsg() {
    if (argument == 0) {
        return 0x1901;
    }

    return mPrmMsgNo;
}

/* 00001F38-00001F78       .text next_msgStatus__11daObj_hsh_cFPUl */
u32 daObj_hsh_c::next_msgStatus(u32* pMsg) {
    fopMsg_MessageStatus_e nextStatus = fopMsgStts_MSG_CONTINUES_e;
    u32 msg = *pMsg;
    if ((msg == 0) || (msg == 0xef3) || (msg == mPrmMsgNo)) {
        nextStatus = fopMsgStts_MSG_ENDS_e;
    } else if (msg == 0x1901) {
        nextStatus = fopMsgStts_MSG_ENDS_e;
    }
    return nextStatus;
}

/* 00001F78-00002098       .text execute__11daObj_hsh_cFv */
BOOL daObj_hsh_c::execute() {
    if (argument == 0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2B10)) {
            fopAcM_SetStatusMap(this, 0x4);
        } else {
            fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
        }
    }

    mObjAcch.CrrPos(*dComIfG_Bgsp());

    if (mObjAcch.GetGroundH() != -G_CM3D_F_INF) {
        s32 roomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
        fopAcM_SetRoomNo(this, roomNo);
        tevStr.mRoomNo = roomNo;
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
        mPolyInfo.SetPolyInfo(mObjAcch.m_gnd);
    }

    if (eventProc() == 0) {
        checkOrder();
        action(NULL);
    }

    eventOrder();
    setBaseMtx();
    return TRUE;
}

/* 00002098-00002158       .text draw__11daObj_hsh_cFv */
BOOL daObj_hsh_c::draw() {
    if (isOffDraw()) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    mDoExt_modelUpdate(mpModel);
    cXyz shadowPos(current.pos.x, current.pos.y, current.pos.z);

    mShadowId = dComIfGd_setRealShadow2(mShadowId, TRUE, mpModel, &shadowPos, 800.0, mObjAcch.GetGroundH(), &tevStr);

    // dDbVw_drawCylinderXlu

    return TRUE;
}

/* 00002158-00002178       .text daObj_hsh_Draw__FP11daObj_hsh_c */
static BOOL daObj_hsh_Draw(daObj_hsh_c* i_this) {
    return ((daObj_hsh_c*)i_this)->draw();
}

/* 00002178-00002198       .text daObj_hsh_Execute__FP11daObj_hsh_c */
static BOOL daObj_hsh_Execute(daObj_hsh_c* i_this) {
    return ((daObj_hsh_c*)i_this)->execute();
}

/* 00002198-000021A0       .text daObj_hsh_IsDelete__FP11daObj_hsh_c */
static BOOL daObj_hsh_IsDelete(daObj_hsh_c*) {
    return TRUE;
}

/* 000021A0-000021C8       .text daObj_hsh_Delete__FP11daObj_hsh_c */
static BOOL daObj_hsh_Delete(daObj_hsh_c* i_this) {
    ((daObj_hsh_c*)i_this)->~daObj_hsh_c();
    return TRUE;
}

/* 000021C8-000021E8       .text daObj_hsh_Create__FP10fopAc_ac_c */
static cPhs_State daObj_hsh_Create(fopAc_ac_c* i_this) {
    return ((daObj_hsh_c*)i_this)->create();
}

static actor_method_class l_daObj_hsh_Method = {
    (process_method_func)daObj_hsh_Create,
    (process_method_func)daObj_hsh_Delete,
    (process_method_func)daObj_hsh_Execute,
    (process_method_func)daObj_hsh_IsDelete,
    (process_method_func)daObj_hsh_Draw,
};

actor_process_profile_definition g_profile_Obj_HSH = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_HSH_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_hsh_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_HSH_e,
    /* Actor SubMtd */ &l_daObj_hsh_Method,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
