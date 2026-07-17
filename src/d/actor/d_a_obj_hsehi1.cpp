/**
 * d_a_obj_hsehi1.cpp
 * Object - Tower of the Gods - Command Melody monument & blue monument next to Companion Statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hsehi1.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "m_Do/m_Do_ext.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "d/actor/d_a_player.h"
#include "d/d_kankyo.h"

static daObj_hsh_HIO_c l_HIO;
static u32 l_hio_counter;
static fpc_ProcID l_msgId;
static msg_class* l_msg;

/* 000000EC-00000130       .text __ct__15daObj_hsh_HIO_cFv */
daObj_hsh_HIO_c::daObj_hsh_HIO_c() {
    mNo = -1;
    mAttentionDist = 250.0f;
    mAttentionOffsetY0 = 0.0f;
    mAttentionOffsetY1 = 0.0f;
    mAttentionAngle = 0x4000;
    m16 = 0;
}

/* 00000130-000002A4       .text __dt__11daObj_hsh_cFv */
daObj_hsh_c::~daObj_hsh_c() {
    if (argument == 0) {
        dComIfG_resDelete(&mPhs, "Hsehi1");
    } else {
        dComIfG_resDelete(&mPhs, "Hsehi2");
    }
    if (mpBgw != NULL) {
        dComIfG_Bgsp()->Release(mpBgw);
    }
    emitterDelete(&mpEmitter);
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
}

/* 000002A4-000002C4       .text daObj_hsh_XyCheckCB__FPvi */
static s16 daObj_hsh_XyCheckCB(void* i_this, int i_btn) {
    return ((daObj_hsh_c*)i_this)->XyCheckCB(i_btn);
}

/* 000002C4-000002E8       .text XyCheckCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyCheckCB(int) {
    /* Nonmatching */
    return 0;
}

/* 000002E8-00000308       .text daObj_hsh_XyEventCB__FPvi */
static s16 daObj_hsh_XyEventCB(void* i_this, int i_btn) {
    return ((daObj_hsh_c*)i_this)->XyEventCB(i_btn);
}

/* 00000308-00000390       .text XyEventCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyEventCB(int) {
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x8A7, &eyePos, 0, reverb);
    mFlags |= 1;
    mEventCutIdx = 0;
    return mEventIdx[0];
}

/* 00000390-000003F4       .text particle_set__11daObj_hsh_cFUs */
void daObj_hsh_c::particle_set(unsigned short i_id) {
    dComIfGp_particle_set(i_id, &current.pos, &current.angle);
}

void daObj_hsh_c::particle_set(JPABaseEmitter** ppEmitter, unsigned short i_id) {
    if (*ppEmitter == NULL) {
        *ppEmitter = dComIfGp_particle_set(i_id, &current.pos, &current.angle);
        if (*ppEmitter != NULL) {
            (*ppEmitter)->becomeImmortalEmitter();
        }
    }
}

/* 00000488-000004C4       .text emitterDelete__11daObj_hsh_cFPP14JPABaseEmitter */
void daObj_hsh_c::emitterDelete(JPABaseEmitter** ppEmitter) {
    if (*ppEmitter != NULL) {
        (*ppEmitter)->quitImmortalEmitter();
        (*ppEmitter)->becomeInvalidEmitter();
        *ppEmitter = NULL;
    }
}

/* 000004C4-00000568       .text setAttention__11daObj_hsh_cFb */
void daObj_hsh_c::setAttention(bool i_onOff) {
    if (!i_onOff) {
        return;
    }

    f32 upperY;
    f32 lowerY;
    if (argument == 0) {
        upperY = 90.0f + current.pos.y + l_HIO.mAttentionOffsetY1;
        lowerY = 180.0f + current.pos.y + l_HIO.mAttentionOffsetY0;
    } else {
        upperY = 80.0f + current.pos.y + l_HIO.mAttentionOffsetY1;
        lowerY = 120.0f + current.pos.y + l_HIO.mAttentionOffsetY0;
    }

    eyePos.set(current.pos.x, upperY, current.pos.z);
    attention_info.position.set(current.pos.x, lowerY, current.pos.z);
}

/* 00000568-000005AC       .text onOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::onOffDraw() {
    mFlags |= 8;
    if (mpBgw != NULL) {
        dComIfG_Bgsp()->Release(mpBgw);
    }
}

/* 000005AC-000005F4       .text offOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::offOffDraw() {
    mFlags &= ~8;
    if (mpBgw != NULL) {
        dComIfG_Bgsp()->Regist(mpBgw, this);
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
    MTXCopy(mDoMtx_stack_c::get(), mBaseMtx);
}

/* 000006C8-00000910       .text createHeap__11daObj_hsh_cFv */
BOOL daObj_hsh_c::createHeap() {
    if (argument == 0) {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi1", 4);
        JUT_ASSERT(0x1F9, modelData != 0);
        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return FALSE;
        }
        mpBgw = new dBgW();
        if (mpBgw != NULL) {
            if (mpBgw->Set((cBgD_t*)dComIfG_getObjectRes("Hsehi1", 7), dBgW::MOVE_BG_e, &mBaseMtx)) {
                return FALSE;
            } else {
                return TRUE;
            }
        }
        return FALSE;
    } else {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi2", 4);
        JUT_ASSERT(0x20F, modelData != 0);
        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return FALSE;
        }
        mpBgw = new dBgW();
        if (mpBgw != NULL) {
            if (mpBgw->Set((cBgD_t*)dComIfG_getObjectRes("Hsehi2", 7), dBgW::MOVE_BG_e, &mBaseMtx)) {
                return FALSE;
            } else {
                return TRUE;
            }
        }
        return FALSE;
    }
}

/* 00000910-00000930       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_this) {
    return ((daObj_hsh_c*)i_this)->createHeap();
}

/* 00000930-00000B44       .text create__11daObj_hsh_cFv */
cPhs_State daObj_hsh_c::create() {
    static u32 a_heap_size_tbl = 0x4000;

    fopAcM_SetupActor(this, daObj_hsh_c);

    cPhs_State phase;
    if (argument == 0 && dComIfGs_isEventBit(0x2510)) {
        phase = cPhs_ERROR_e;
    } else {
        if (argument == 0) {
            phase = dComIfG_resLoad(&mPhs, "Hsehi1");
        } else {
            phase = dComIfG_resLoad(&mPhs, "Hsehi2");
        }
        if (phase == cPhs_COMPLEATE_e) {
            if (!fopAcM_entrySolidHeap(this, checkCreateHeap, a_heap_size_tbl)) {
                mpBgw = NULL;
                phase = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
                if (l_HIO.mNo < 0) {
                    if (argument == 0) {
                        l_HIO.mNo = mDoHIO_createChild("\203^\203N\203g\220\316\224\305", &l_HIO);
                    } else {
                        l_HIO.mNo = mDoHIO_createChild("\203\201\203b\203Z\201[\203W\220\316\224\350", &l_HIO);
                    }
                    l_HIO.mpActor = this;
                }
                if (!init()) {
                    phase = cPhs_ERROR_e;
                }
            }
        }
    }
    return phase;
}

/* 00000C84-00000E60       .text init__11daObj_hsh_cFv */
BOOL daObj_hsh_c::init() {
    static char* event_name_tbl[2] = {
        "hsehi1_tact",
        "hsehi1_talk",
    };

    mSwitchNo = fopAcM_GetParam(this) & 0xFF;
    mMsgNo = (fopAcM_GetParam(this) >> 8) & 0xFFFF;
    mAttentionOn = 0;
    mEventState = -1;
    mEventCutIdx = -1;

    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    setBaseMtx();
    dComIfG_Bgsp()->Regist(mpBgw, this);
    mpBgw->Move();

    if (argument == 0) {
        if (dComIfGs_isEventBit(0x2B10)) {
            setAction(&daObj_hsh_c::waitAction, NULL);
        } else {
            onOffDraw();
            setAction(&daObj_hsh_c::offAction, NULL);
        }
    } else {
        setAction(&daObj_hsh_c::waitAction, NULL);
    }

    for (int i = 0; i < 2; i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(event_name_tbl[i], 0xFF);
    }

    eventInfo.setXyCheckCB(daObj_hsh_XyCheckCB);
    eventInfo.setXyEventCB(daObj_hsh_XyEventCB);
    return TRUE;
}

/* 00000E60-00000EF4       .text action__11daObj_hsh_cFPv */
void daObj_hsh_c::action(void* i_param) {
    if (mpActionFunc == NULL) {
        speedF = 0.0f;
        setAction(&daObj_hsh_c::waitAction, NULL);
    }
    (this->*mpActionFunc)(i_param);
}

/* 00000EF4-00000FBC       .text setAction__11daObj_hsh_cFM11daObj_hsh_cFPCvPvPv_iPv */
int daObj_hsh_c::setAction(int (daObj_hsh_c::*i_action)(void*), void* i_param) {
    if (mpActionFunc != i_action) {
        if (mpActionFunc != NULL) {
            mActionState = -1;
            (this->*mpActionFunc)(i_param);
        }
        mpActionFunc = i_action;
        mActionState = 0;
        m51C[0] = 0;
        m51C[1] = 0;
        m51C[2] = 0;
        m51C[3] = 0;
        m528 = 0.0f;
        (this->*mpActionFunc)(i_param);
    }
    return 1;
}

/* 00000FBC-000010E8       .text waitAction__11daObj_hsh_cFPv */
int daObj_hsh_c::waitAction(void*) {
    if (mActionState == 0) {
        mActionState++;
    } else if (mActionState != -1) {
        mAttentionOn = chkAttention(current.pos, shape_angle.y);
        if (argument == 0) {
            if (mAttentionOn != 0) {
                attention_info.flags |= 0x20000008;
                if (mEventState == -1) {
                    mEventState = 5;
                }
            } else {
                attention_info.flags &= ~0x20000008;
            }
        } else {
            if (mAttentionOn != 0) {
                attention_info.flags |= 0x20000008;
                if (mEventState == -1) {
                    mEventState = 3;
                }
            } else {
                attention_info.flags &= ~0x20000008;
            }
        }
        setAttention(true);
    }
    return 1;
}

/* 000010E8-00001214       .text talkAction__11daObj_hsh_cFPv */
int daObj_hsh_c::talkAction(void*) {
    s8 state = mActionState;
    if (state == 0) {
        l_msgId = -1;
        mMsgId = getMsg();
        mActionState++;
        if (argument == 0) {
            ((daPy_py_c*)dComIfGp_getLinkPlayer())->onNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
        }
    } else if (state != -1) {
        if (state == 1) {
            if (talk_init()) {
                mActionState++;
            }
        } else {
            if (talk(0)) {
                setAction(&daObj_hsh_c::waitAction, NULL);
                dComIfGp_event_reset();
                if (argument == 0) {
                    ((daPy_py_c*)dComIfGp_getLinkPlayer())->offNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
                }
            }
        }
        setAttention(true);
    }
    return 1;
}

/* 00001214-00001230       .text offAction__11daObj_hsh_cFPv */
int daObj_hsh_c::offAction(void*) {
    if (mActionState == 0) {
        mActionState++;
    }
    return 1;
}

/* 00001230-00001278       .text deleteAction__11daObj_hsh_cFPv */
int daObj_hsh_c::deleteAction(void*) {
    if (mActionState == 0) {
        mActionState++;
    } else if (mActionState != -1) {
        fopAcM_delete(this);
    }
    return 1;
}

/* 00001278-0000135C       .text eventOrder__11daObj_hsh_cFv */
void daObj_hsh_c::eventOrder() {
    if (!(mFlags & 1)) {
        s8 state = mEventState;
        if (state == 4 || state == 3) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
            if (mEventState == 4) {
                fopAcM_orderSpeakEvent(this);
            }
        } else if (state == 5) {
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
            if (argument == 0) {
                eventInfo.setEventName("hsehi1_talk");
            }
        } else if (state != -1 && state < 2) {
            mEventCutIdx = state;
            fopAcM_orderOtherEventId(this, mEventIdx[mEventCutIdx], 0xFF, 0xFFFF, 0, 1);
        }
    }
}

/* 0000135C-0000140C       .text checkOrder__11daObj_hsh_cFv */
void daObj_hsh_c::checkOrder() {
    if (eventInfo.getCommand() == dEvtCmd_INTALK_e && (mEventState == 4 || mEventState == 3 || mEventState == 5)) {
        mEventState = -1;
        if (!dComIfGp_event_chkTalkXY()) {
            setAction(&daObj_hsh_c::talkAction, NULL);
        }
    }
}

/* 0000140C-00001478       .text checkCommandTalk__11daObj_hsh_cFv */
BOOL daObj_hsh_c::checkCommandTalk() {
    if (eventInfo.getCommand() != dEvtCmd_INTALK_e) {
        return FALSE;
    }
    if (dComIfGp_event_chkTalkXY()) {
        if (mEventState == 5) {
            mEventState = -1;
        }
        return FALSE;
    }
    return TRUE;
}

/* 00001478-000015E0       .text chkAttention__11daObj_hsh_cF4cXyzs */
BOOL daObj_hsh_c::chkAttention(cXyz, short) {
    /* Nonmatching */
    return 0;
}

/* 000015E0-00001784       .text eventProc__11daObj_hsh_cFv */
BOOL daObj_hsh_c::eventProc() {
    /* Nonmatching */
    return 0;
}

/* 00001784-000017B0       .text eventEnd__11daObj_hsh_cFv */
void daObj_hsh_c::eventEnd() {
    dComIfGp_event_reset();
    mFlags &= ~1;
    mEventCutIdx = -1;
}

/* 000017B0-000017B4       .text initialDefault__11daObj_hsh_cFi */
void daObj_hsh_c::initialDefault(int) {
    /* Nonmatching */
}

/* 000017B4-000017BC       .text actionDefault__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionDefault(int) {
    /* Nonmatching */
    return 1;
}

/* 000017BC-00001938       .text initialLinkDispEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialLinkDispEvent(int) {
    /* Nonmatching */
}

/* 00001938-000019C0       .text initialMsgSetEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialMsgSetEvent(int) {
    /* Nonmatching */
}

/* 000019C0-000019E0       .text actionMsgSetEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionMsgSetEvent(int) {
    talk_init();
}

/* 000019E0-00001A40       .text actionMessageEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionMessageEvent(int i_staffIdx) {
    int* p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "MsgNo");
    int msgNo = 0;
    if (p != NULL) {
        msgNo = *p;
    }
    talk(msgNo);
}

/* 00001A40-00001ADC       .text actionTactEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionTactEvent(int) {
    /* Nonmatching */
}

/* 00001ADC-00001B3C       .text initialJudgeEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialJudgeEvent(int) {
    if (mFlags & 4) {
        mFlags &= ~4;
    } else if (mFlags & 2) {
        drawStart();
        mFlags &= ~2;
        eventEnd();
    }
}

/* 00001B3C-00001C1C       .text initialAppearEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialAppearEvent(int) {
    dComIfGs_onEventBit(0x2B10);
    particle_set(0x8270);
    particle_set(&mpEmitter, 0x8271);
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x6A05, &current.pos, 0, reverb);
    mTimer = 0x1E;
    setAction(&daObj_hsh_c::waitAction, NULL);
}

/* 00001C1C-00001C74       .text actionAppearEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionAppearEvent(int) {
    if (cLib_calcTimer(&mTimer) == 0) {
        offOffDraw();
        emitterDelete(&mpEmitter);
        return TRUE;
    }
    return FALSE;
}

/* 00001C74-00001D3C       .text initialDeleteEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialDeleteEvent(int) {
    particle_set(0x8270);
    particle_set(&mpEmitter, 0x8271);
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x6A05, &current.pos, 0, reverb);
    mTimer = 0x3C;
    setAction(&daObj_hsh_c::deleteAction, NULL);
}

/* 00001D3C-00001D88       .text actionDeleteEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionDeleteEvent(int) {
    if (cLib_calcTimer(&mTimer) == 0) {
        drawStop();
        return TRUE;
    }
    return FALSE;
}

/* 00001D88-00001DF4       .text talk_init__11daObj_hsh_cFv */
BOOL daObj_hsh_c::talk_init() {
    if (l_msgId == -1) {
        l_msgId = fopMsgM_messageSet(mMsgId, this);
    } else {
        l_msg = fopMsgM_SearchByID(l_msgId);
        if (l_msg != NULL) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00001DF4-00001F1C       .text talk__11daObj_hsh_cFi */
BOOL daObj_hsh_c::talk(int) {
    /* Nonmatching */
    return 0;
}

/* 00001F1C-00001F38       .text getMsg__11daObj_hsh_cFv */
u32 daObj_hsh_c::getMsg() {
    if (argument == 0) {
        return 0x1901;
    }
    return mMsgNo;
}

/* 00001F38-00001F78       .text next_msgStatus__11daObj_hsh_cFPUl */
u16 daObj_hsh_c::next_msgStatus(unsigned long* p) {
    u16 status = 0xF;
    u32 v = *p;
    if (v == 0 || v == 0xEF3 || v == mMsgNo) {
        status = 0x10;
    } else if (v == 0x1901) {
        status = 0x10;
    }
    return status;
}

/* 00001F78-00002098       .text execute__11daObj_hsh_cFv */
BOOL daObj_hsh_c::execute() {
    if (argument == 0) {
        if (dComIfGs_isEventBit(0x2B10)) {
            actor_status = (actor_status & ~0x3F) | 0x24;
        } else {
            actor_status &= ~0x20;
        }
    }
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    if (mObjAcch.GetGroundH() != -1000000000.0f) {
        current.roomNo = tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
        mPolyInfo = mObjAcch.m_gnd;
    }
    if (!eventProc()) {
        checkOrder();
        action(NULL);
    }
    eventOrder();
    setBaseMtx();
    return TRUE;
}

/* 00002098-00002158       .text draw__11daObj_hsh_cFv */
BOOL daObj_hsh_c::draw() {
    if (mFlags & 8) {
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdate(mpModel);
    cXyz pos = current.pos;
    mShadowKey = dComIfGd_setRealShadow2(mShadowKey, 1, mpModel, &pos, 800.0f, mObjAcch.GetGroundH(), &tevStr);
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
    /* Cull Type    */ 0,
};
