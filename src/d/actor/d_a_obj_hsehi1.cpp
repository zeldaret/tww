/**
 * d_a_obj_hsehi1.cpp
 * Object - Tower of the Gods - Command Melody monument & blue monument next to Companion Statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hsehi1.h"
#include "d/actor/d_a_player.h"

static daObj_hsh_HIO_c l_HIO;
static s32 l_hio_counter;

static msg_class* l_msg;
static fpc_ProcID l_msgId;

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
    if (this->argument == 0) {
        dComIfG_resDelete(&mPhs, "Hsehi1");
    }
    else {
        dComIfG_resDelete(&mPhs, "Hsehi2");
    }

    if (this->mpBgW != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }

    emitterDelete(&this->mpEmitter);

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
    this->mFlags = this->mFlags | 1;
    this->mEventSelector = 0;
    return mEventId[0];
}

/* 00000390-000003F4       .text particle_set__11daObj_hsh_cFUs */
void daObj_hsh_c::particle_set(unsigned short i_particleId) {
    dComIfGp_particle_set(i_particleId, &this->current.pos, &this->current.angle);
}

/* 000003F4-00000488       .text particle_set__11daObj_hsh_cFPP14JPABaseEmitterUs */
void daObj_hsh_c::particle_set(JPABaseEmitter** pEmitter, unsigned short i_particleId) {
    if (*pEmitter == NULL) {
        *pEmitter = dComIfGp_particle_set(i_particleId, &this->current.pos, &this->current.angle);
        if (*pEmitter != NULL) {
            (*pEmitter)->mFlags |= 0x40;
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

    float y1;
    float currZ;
    float y2;

    // Hsh variant
    if (this->argument == 0) {
        y1 = 90.0f + this->current.pos.y + l_HIO.prm.field_0x10;
        y2 = 180.0f + this->current.pos.y + l_HIO.prm.field_0x0c;
    // Hsh2 variant
    } else {
        y1 = 80.0f + this->current.pos.y + l_HIO.prm.field_0x10;
        y2 = 120.0f + this->current.pos.y + l_HIO.prm.field_0x0c;
    }

    currZ = this->current.pos.z;
    this->eyePos.set(this->current.pos.x, y1, currZ);
    this->attention_info.position.set(this->current.pos.x, y2, this->current.pos.z);
}

/* 00000568-000005AC       .text onOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::onOffDraw() {
    this->mFlags = this->mFlags | 8;
    if (this->mpBgW != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
}

/* 000005AC-000005F4       .text offOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::offOffDraw() {
    this->mFlags = this->mFlags & ~8;
    if (this->mpBgW != NULL) {
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
    J3DModel* model = this->mpModel;

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);

    model->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), this->mMtx);
}

/* 000006C8-00000910       .text createHeap__11daObj_hsh_cFv */
BOOL daObj_hsh_c::createHeap() {
    if (this->argument == 0) {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi1", 4);
        JUT_ASSERT(0x1f9, modelData != 0);

        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return FALSE;
        }

        mpBgW = new dBgW();
        if (mpBgW != NULL) {
            cBgD_t* dzb = (cBgD_t*)dComIfG_getObjectRes("Hsehi1", 7);
            if (mpBgW->Set(dzb, cBgW::MOVE_BG_e, &this->mMtx)) {
                return FALSE;
            }
        }
        else {
            return FALSE;
        }
    }
    else {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi2", 4);
        JUT_ASSERT(0x20f, modelData != 0);

        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return FALSE;
        }

        mpBgW = new dBgW();
        if (mpBgW != NULL) {
            cBgD_t* dzb = (cBgD_t*)dComIfG_getObjectRes("Hsehi2", 7);
            if (mpBgW->Set(dzb, cBgW::MOVE_BG_e, &this->mMtx)) {
                return FALSE;
            }
        }
        else {
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
    /* Nonmatching */
    static u32 a_heap_size_tbl;
    static s8 init;
    if (init == 0) {
        a_heap_size_tbl = 0x4000;
        init = 1;
    }

    fopAcM_ct(this, daObj_hsh_c);

    if (argument == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_2510)) {
        return cPhs_ERROR_e;
    }

    cPhs_State st;
    if (argument == 0) {
        st = dComIfG_resLoad(&mPhs, "Hsehi1");
    }
    else {
        st = dComIfG_resLoad(&mPhs, "Hsehi2");
    }
    //cPhs_State st = dComIfG_resLoad(&mPhs, argument == 0 ? "Hsehi1" : "Hsehi2");
    if (st == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, checkCreateHeap, a_heap_size_tbl)) {
            mpBgW = NULL;
            return cPhs_ERROR_e;
        } 
        fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
        if (l_HIO.mNo < 0) {
            if (argument == 0) {
                l_HIO.mNo = mDoHIO_createChild("タクト石版", &l_HIO);
            }
            else {
                l_HIO.mNo = mDoHIO_createChild("メッセージ石碑", &l_HIO);
            }
            l_HIO.mpActor = this;
        }
        if (this->init() == 0) {
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
    mSwitchNo = fpcM_GetParam(this) & 0xff;
    mMessage = (fpcM_GetParam(this) >> 8) & 0xffff;
    field_0x518 = 0;
    field_0x514 = -1;
    mEventSelector = -1;
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1,
             &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    setBaseMtx();
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mpBgW->Move();

    if (argument == 0) {
        if (dComIfGs_isEventBit(0x2b10)) {
            setAction(&daObj_hsh_c::waitAction, NULL);
        }
        else {
            onOffDraw();
            setAction(&daObj_hsh_c::offAction, NULL);
        }
    }
    else {
        setAction(&daObj_hsh_c::waitAction, NULL);
    }

    for (int i = 0; i < 2; i++) {
        mEventId[i] = dComIfGp_getPEvtManager()->getEventIdx(event_name_tbl[i], 0xff);
    }

    eventInfo.setXyCheckCB(daObj_hsh_XyCheckCB);
    eventInfo.setXyEventCB(daObj_hsh_XyEventCB);
    return TRUE;
}

/* 00000E60-00000EF4       .text action__11daObj_hsh_cFPv */
void daObj_hsh_c::action(void* fnArg) {
    if (!this->mAction) {
        this->speedF = 0.0;
        setAction(&daObj_hsh_c::waitAction, NULL);
    }
    (this->*mAction)(fnArg);
}

/* 00000EF4-00000FBC       .text setAction__11daObj_hsh_cFM11daObj_hsh_cFPCvPvPv_iPv */
BOOL daObj_hsh_c::setAction(ActionFunc i_action, void* fnArg) {
    if (mAction != i_action) {
        if (mAction) {
            this->field_0x517 = 0xff; 
            (this->*mAction)(fnArg);
        }

        this->mAction = i_action;

        this->field_0x517 = 0;
        this->field_0x51c = 0;
        this->field_0x51e = 0;
        this->field_0x520 = 0;
        this->field_0x522 = 0;
        this->field_0x528 = 0;

        (this->*mAction)(fnArg);
    }
    return 1;
}

/* 00000FBC-000010E8       .text waitAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::waitAction(void*) {
    if (this->field_0x517 == 0) {
        this->field_0x517++;
    }
    else if (this->field_0x517 != -1) {
        this->field_0x518 = chkAttention(this->current.pos, this->shape_angle.y);

        if (this->argument == 0) {
            if (this->field_0x518) {
                cLib_onBit<u32>(this->attention_info.flags, (fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e));
                if (this->field_0x514 == -1) {
                    this->field_0x514 = 5;
                }
            }
            else {
                cLib_offBit<u32>(this->attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
            }
        }
        else if (this->field_0x518) {
            cLib_onBit<u32>(this->attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
            if (this->field_0x514 == -1) {
                this->field_0x514 = 3;
            }
        }
        else {
            cLib_offBit<u32>(this->attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
        }
        setAttention(TRUE);
    }
    return 1;
}

/* 000010E8-00001214       .text talkAction__11daObj_hsh_cFPv */
bool daObj_hsh_c::talkAction(void*) {
    if (this->field_0x517 == 0) {
        l_msgId = -1;
        this->mMsgId = getMsg();
        this->field_0x517++;
        if (this->argument == 0) {
            ((daPy_py_c*)dComIfGp_getLinkPlayer())->onNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
        }
    }
    else if (this->field_0x517 != -1) {
        if (this->field_0x517 == 1) {
            BOOL success = talk_init();
            if (success) {
                this->field_0x517++;
            }
        }
        else {
            BOOL success = talk(0);
            if (success) {
                setAction(&daObj_hsh_c::waitAction, NULL);
                dComIfGp_event_onEventFlag(8);
                if (this->argument == 0) {
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
    if (this->field_0x517 == 0) {
        this->field_0x517++;
    }
    return TRUE;
}

/* 00001230-00001278       .text deleteAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::deleteAction(void*) {
    if (this->field_0x517 == 0) {
        this->field_0x517++;
    }
    else if (this->field_0x517 != -1) {
        fopAcM_delete(this);
    }
    return TRUE;
}

/* 00001278-0000135C       .text eventOrder__11daObj_hsh_cFv */
void daObj_hsh_c::eventOrder() {
    if (this->mFlags & 1) {
        if ((this->field_0x514 == 4) || (this->field_0x514 == 3)) {
            this->eventInfo.mCondition |= dEvtCnd_CANTALK_e;
            if (this->field_0x514 == 4) {
                fopAcM_orderSpeakEvent(this);
            }
        }
        else if (this->field_0x514 == 5) {
            this->eventInfo.mCondition |= dEvtCnd_CANTALKITEM_e;
            this->eventInfo.mCondition |= dEvtCnd_CANTALK_e;
            if (this->argument == 0) {
                this->eventInfo.setEventName("hseh1_talk");
            }
        }
        else if ((this->field_0x514 != -1) && (this->field_0x514 < 2)) {
            mEventSelector = this->field_0x514;
            fopAcM_orderOtherEventId(this, mEventId[mEventSelector]);
        }
    }
    return;
}

/* 0000135C-0000140C       .text checkOrder__11daObj_hsh_cFv */
void daObj_hsh_c::checkOrder() {
    if ((this->eventInfo.mCommand == dEvtCmd_INTALK_e) &&
    (this->field_0x514 == 4 || this->field_0x514 == 3 || this->field_0x514 == 5)) {
        this->field_0x514 = 0xff;
        if (!dComIfGp_event_chkTalkXY()) {
            setAction(&daObj_hsh_c::waitAction, NULL);
        }
    }
}

/* 0000140C-00001478       .text checkCommandTalk__11daObj_hsh_cFv */
BOOL daObj_hsh_c::checkCommandTalk() {
    if (this->eventInfo.mCommand == dEvtCmd_INTALK_e) {
        if (dComIfGp_event_chkTalkXY()) {
            if (this->field_0x514 == 5) {
                this->field_0x514 = 0xff;
            }
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

/* 00001478-000015E0       .text chkAttention__11daObj_hsh_cF4cXyzs */
BOOL daObj_hsh_c::chkAttention(cXyz i_pos, short i_angleY) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    f32 dist = l_HIO.prm.mAttnDist;
    int angle = l_HIO.prm.mAttnAngle;
    cXyz delta;
    delta.x = player->current.pos.x - i_pos.x;
    delta.z = player->current.pos.z - i_pos.z;
    f32 d = std::sqrtf(delta.x * delta.x + delta.z * delta.z);
    s16 targetAngle = cM_atan2s(delta.x, delta.z);
    delta.y = player->current.pos.y - i_pos.y;
    if (field_0x518 != 0) {
        dist += 40.0f;
        angle += 0x71C;
    }
    s16 diff = targetAngle - i_angleY;
    BOOL ret = FALSE;
    if (angle > abs(diff) && dist > d) {
        ret = TRUE;
    }
    return ret;
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
    "WAIT", "Disp", "MsgSet", "Talk", "Tact", "Judge", "Appear", "Delete",
};

/* 000015E0-00001784       .text eventProc__11daObj_hsh_cFv */
BOOL daObj_hsh_c::eventProc() {
    if ((eventInfo.mCommand == dEvtCmd_INDEMO_e) && this->field_0x514 != -1) {
        this->mFlags |= 1;
        this->field_0x514 = 0xff;
    }

    int staffIdx = dComIfGp_evmng_getMyStaffId("Hsh", NULL, 0);

    if ((dComIfGp_event_getMode() != dEvtMode_NONE_e) && (!checkCommandTalk())) {
        if (staffIdx != -1) {
            int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
            if (actIdx == -1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
            else {
                if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                    (this->*event_init_tbl[actIdx])(staffIdx);
                }
                BOOL res = (this->*event_action_tbl[actIdx])(staffIdx);
                if (res != 0) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }
        }
        if ((this->mFlags & 1) != 0) {
            if (dComIfGp_evmng_endCheck(this->mEventId[this->mEventSelector])) {
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
    dComIfGp_event_onEventFlag(8);
    this->mFlags &= ~1;
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
void daObj_hsh_c::initialLinkDispEvent(int) {
    /* Nonmatching */
}

/* 00001938-000019C0       .text initialMsgSetEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialMsgSetEvent(int staffIdx) {
    l_msgId = -1;
    this->mMsgId = 0x0;

    int* pMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if (pMsgNo != NULL) {
        this->mMsgId = *pMsgNo;
        if (this->mMsgId == 0x5b3) {
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
    int music = daPy_getPlayerActorClass()->getTactMusic();

    if(music == i_talkMode) {
        this->mFlags |= 4;
    }
    talk(1);
}

/* 00001ADC-00001B3C       .text initialJudgeEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialJudgeEvent(int) {
    if ((this->mFlags & 4) != 0) {
        this->mFlags &= ~4;
    }
    else {
        if ((this->mFlags & 2) != 0) {
            drawStart();
            this->mFlags &= ~2;
            eventEnd();
        }
    }
}

/* 00001B3C-00001C1C       .text initialAppearEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialAppearEvent(int) {
    /* Nonmatching */
}

/* 00001C1C-00001C74       .text actionAppearEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionAppearEvent(int) {
    if (cLib_calcTimer(&this->mpAppearDeleteTimer) == 0) {
        offOffDraw();
        emitterDelete(&this->mpEmitter);
        return TRUE;
    }
    return FALSE;
}

/* 00001C74-00001D3C       .text initialDeleteEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialDeleteEvent(int) {
    /* Nonmatching */
}

/* 00001D3C-00001D88       .text actionDeleteEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionDeleteEvent(int) {
    if (cLib_calcTimer(&this->mpAppearDeleteTimer) == 0) {
        drawStop();
        return TRUE;
    }

    return FALSE;
}

/* 00001D88-00001DF4       .text talk_init__11daObj_hsh_cFv */
BOOL daObj_hsh_c::talk_init() {
    if (l_msgId == -1) {
        l_msgId = fopMsgM_messageSet(this->mMsgId, this);
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
    // TODO: Rename parameter
    u16 status = l_msg->mStatus;
    if (status == fopMsgStts_MSG_DISPLAYED_e) {
        if (i_mode == 1) {
            if (g_dComIfG_gameInfo.play.mMesgCancelButton != 0) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
                this->mFlags |= 2;
            } 
            else {
                if ((this->mFlags & 4) != 0) {
                    l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                    fopMsgM_messageSendOn();
                    if (this->mMsgId == 0x5b3) {
                        s8 roomNo = fopAcM_GetRoomNo(this);
                        dComIfGs_onSwitch(this->mSwitchNo, roomNo);
                    }
                }
            }
        }
        else {
            u16 nextMsgStatus = next_msgStatus(&this->mMsgId);
            l_msg->mStatus = nextMsgStatus;
            if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(this->mMsgId);
            }
        }
    }
    else if (status == fopMsgStts_INPUT_e) {
        if (i_mode == 2) {
            return 1;
        }
    }
    
    else if ((status != fopMsgStts_MSG_TYPING_e) && (status == fopMsgStts_BOX_CLOSED_e)) {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
        return 1;
    }
    return 0;
}

/* 00001F1C-00001F38       .text getMsg__11daObj_hsh_cFv */
u32 daObj_hsh_c::getMsg() {
    if(this->argument == 0) {
        return 0x1901;
    }

    return this->mMessage;
}

/* 00001F38-00001F78       .text next_msgStatus__11daObj_hsh_cFPUl */
u32 daObj_hsh_c::next_msgStatus(unsigned long* pMsg) {
    fopMsg_MessageStatus_e nextStatus = fopMsgStts_MSG_CONTINUES_e;
    u32 msg = *pMsg;
    if ((msg == 0) || (msg == 0xef3) || (msg == this->mMessage)) {
        nextStatus = fopMsgStts_MSG_ENDS_e;
    }
    else if (msg == 0x1901) {
        nextStatus = fopMsgStts_MSG_ENDS_e;
    }
    return nextStatus;

    /* Nonmatching */
}

/* 00001F78-00002098       .text execute__11daObj_hsh_cFv */
BOOL daObj_hsh_c::execute() {
    /* Nonmatching */
}

/* 00002098-00002158       .text draw__11daObj_hsh_cFv */
BOOL daObj_hsh_c::draw() {
    /* Nonmatching */
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
