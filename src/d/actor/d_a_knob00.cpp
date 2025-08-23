/**
 * d_a_knob00.cpp
 * Object - Regular doors (with knobs, not sliding)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_knob00.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_obj_pirateship.h"
#include "d/actor/d_a_npc_mt.h"
#include "d/d_kankyo.h"
#include "d/res/res_knob.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_graphic.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "ctype.h"

const char daKnob00_c::M_arcname[] = "knob";

/* 00000078-000000B4       .text daKnob00_charactorExchange__FPc */
void daKnob00_charactorExchange(char* password) {
    while (*password) {
        u8 chr = *password;
        *password = std::tolower(chr);
        password++;
    }
}

/* 000000B4-000000D4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* a_this) {
    return ((daKnob00_c*)a_this)->CreateHeap();
}

/* 000000D4-000003B8       .text CreateHeap__10daKnob00_cFv */
BOOL daKnob00_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, KNOB_BDL_DOOR);
    JUT_ASSERT(VERSION_SELECT(145, 145, 163, 163), modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    J3DModel* model = mpModel;
    if (model == NULL) {
#if VERSION == VERSION_DEMO
        return cPhs_ERROR_e;
#else 
        return FALSE;
#endif
    }

    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    J3DAnmTransform* anmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, KNOB_BCK_DOOROPENADOOR);
    if (!mBckAnm.init(modelData, anmTransform, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
#if VERSION == VERSION_DEMO
        return cPhs_ERROR_e;
#else 
        return FALSE;
#endif
    }

    m_jnt = modelData->getJointName()->getIndex("DoorDummy");
    JUT_ASSERT(VERSION_SELECT(169, 169, 187, 187), m_jnt >= 0);

    s32 fileIndex;
    switch (getShapeType()) {
        case 1:
            fileIndex = KNOB_BDL_DOOR_B;
            break;

        case 2:
            fileIndex = KNOB_BDL_DOOR_C;
            break;

        case 3:
            fileIndex = KNOB_BDL_DOOR_D;
            break;

        case 4:
            fileIndex = KNOB_BDL_DOOR_E;
            break;

        case 5:
            fileIndex = KNOB_BDL_DOOR_F;
            break;

        case 6:
            fileIndex = KNOB_BDL_DOOR_G;
            break;

        case 7:
            fileIndex = KNOB_BDL_DOOR_H;
            break;
            
        default:
            fileIndex = KNOB_BDL_DOOR_A;
            break;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, fileIndex);
    mpModel2 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020002);
    if (mpModel2 == NULL) {
#if VERSION == VERSION_DEMO
        return cPhs_ERROR_e;
#else 
        return FALSE;
#endif
    }

    mpBgW = new dBgW();
    if (mpBgW == NULL) {
        return FALSE;
    }

    cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectRes(M_arcname, KNOB_DZB_DOOR);

    if (bgd == NULL) {
        return FALSE;
    }

    calcMtx();

    if (mpBgW->Set(bgd, cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx()) != 1) {
        return TRUE;
    }
    return FALSE;
}

/* 000003B8-000003D8       .text getShapeType__10daKnob00_cFv */
u8 daKnob00_c::getShapeType() {
    return getSwbit2();
}

/* 000003D8-000004B0       .text setEventPrm__10daKnob00_cFv */
void daKnob00_c::setEventPrm() {
    if (mFrontCheck == 0) {
        m2C6 = 7;
    } else {
        m2C6 = 8;
    }

    if ((mAction == 4) || (mAction == 5) || (mAction == 8) || (mAction == 10)) {
        m2C6 = 9;
    }

    if (!checkArea(SQUARE(80.0f), SQUARE(110.0f), SQUARE(250.0f))) {
        offFlag(4);
    } else {
        eventInfo.setEventId(mEventIdx[m2C6]);
        eventInfo.setToolId(mToolId[m2C6]);
        eventInfo.onCondition(dEvtCnd_CANDOOR_e);
    }
}

/* 000004B0-000004BC       .text getType2__10daKnob00_cFv */
u8 daKnob00_c::getType2() {
    return fopAcM_GetParam(this) >> 0x1c;
}

/* 000004BC-00000568       .text chkPassward__10daKnob00_cFv */
s32 daKnob00_c::chkPassward() {
    char acStack_24[17];
    char acStack_38[17];
    
#if VERSION <= VERSION_JPN
    char* password = dComIfGp_getInputPassword();
#else
    strcpy(acStack_24, dComIfGp_getInputPassword());
#endif

    if (!dComIfGs_isEventBit(0x2110)) {
        return -1;
    }

    s32 uVar3 = dComIfGs_getEventReg(0xba0f);
    fopMsgM_passwordGet(acStack_38, uVar3 + 0x1b37);
#if VERSION > VERSION_JPN
    daKnob00_charactorExchange(acStack_38);
    daKnob00_charactorExchange(acStack_24);
#endif

#if VERSION <= VERSION_JPN
    if (strcmp(acStack_38, password) != 0) {
#else
    if (strcmp(acStack_38, acStack_24) != 0) {
#endif
        return -1;
    }
    return uVar3;
}

/* 00000568-000005DC       .text msgDoor__10daKnob00_cFv */
BOOL daKnob00_c::msgDoor() {
    if (this->mDoorType == 1) {
        return 1;
    }

    if (dKy_daynight_check() == dKy_TIME_NIGHT_e) {
        if (mDoorType == 2) {
            return 1;
        }
    } else if (mDoorType == 3) {
        return 1;
    }
    return FALSE;
}

/* 000005DC-000006F0       .text openInit__10daKnob00_cFi */
void daKnob00_c::openInit(int arg1) {
    static s32 bck_table[] = { KNOB_BCK_DOOROPENADOOR, KNOB_BCK_DOOROPENBDOOR, KNOB_BCK_DOOROPENADOOR, KNOB_BCK_DOOROPENBDOOR };

    J3DModelData* modelData = mpModel->getModelData();
    s32 iVar2 = mBckAnm.init(modelData, (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, bck_table[arg1]), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true);
    if (iVar2 == 0) {
        JUT_ASSERT(VERSION_SELECT(382, 382, 396, 396), FALSE);
    }

    openInitCom(0);

    onFlag(1);

    if (arg1 >= 2) {
        mBckAnm.setFrame(34.0f);
    } else {
        dComIfG_Bgsp()->Release(mpBgW);
    }
}

/* 000006F0-000009F8       .text openProc__10daKnob00_cFi */
BOOL daKnob00_c::openProc(int arg1) {
    if (mBckAnm.play()) {
        return TRUE;
    }

    if ((arg1 == 0xc) || (arg1 == 0xd)) {
        u8 bVar3 = (dKy_daynight_check() == dKy_TIME_NIGHT_e);
        u8 bVar4 = (arg1 == 0xd);
        BOOL tmp;
        if (bVar4 == bVar3) {
            tmp = TRUE;
        } else {
            tmp = FALSE;
        }

        if (mBckAnm.checkFrame(15.0f)) {
            mDoGph_gInf_c::setFadeRate(0.0f);
            if (tmp) {
                mDoGph_gInf_c::fadeOut(0.05f, g_saftyWhiteColor);
            } else {
                mDoGph_gInf_c::fadeOut(0.05f, g_blackColor);
            }
        }
    }

    if (arg1 == 0xc || arg1 == 0xe) {
        if (mBckAnm.checkFrame(28.0f)) {
            fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_OPEN, 0);
        } else if (mBckAnm.checkFrame(60.0f)) {
            fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_CLOSE_1, 0);
        } else if (mBckAnm.checkFrame(67.0f) && arg1 == 0xe) {
            fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_CLOSE_2, 0);
        }
    } else if (mBckAnm.checkFrame(25.0f)) {
        fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_OPEN, 0);
    } else if (mBckAnm.checkFrame(49.0f)) {
            fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_CLOSE_1, 0);
    } else if (mBckAnm.checkFrame(64.0f) && arg1 == 0xf) {
        fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_CLOSE_2, 0);
    }

    return FALSE;
}

/* 000009F8-00000A90       .text openEnd__10daKnob00_cFv */
void daKnob00_c::openEnd() {
    offFlag(1);
    bool rt = dComIfG_Bgsp()->Regist(mpBgW, this);
    JUT_ASSERT(VERSION_SELECT(473, 473, 487, 487), !rt);

    dComIfGp_map_clrAGBMapSendStopFlg();
    closeEndCom();
}

/* 00000A90-00000C04       .text chkException__10daKnob00_cFv */
BOOL daKnob00_c::chkException() {
    switch (home.angle.z) {
        case 0x6A6:
            if (dComIfGs_isSymbol(0)) {
                return 1;
            }

            if (!dComIfGs_isEventBit(0x2110)) {
                return 1;
            }
            break;

        case 0x6A7:
            if (!dComIfGs_isEventBit(0x520)) {
                return 1;
            }
            break;

        case 0x6A8:
            if (!dComIfGs_isEventBit(0xa02)) {
                return 1;
            }

            if (dComIfGs_isEventBit(0x2110)) {
                return 1;
            }
            break;

        case 0x6A9:
            if (dComIfGs_isEventBit(0x1701)) {
                return 1;
            }
            break;

        case 0x6AA:
            if (!dComIfGs_isSymbol(1)) {
                return 1;
            }

            if (dComIfGs_isEventBit(0x1a80)) {
                return 1;
            }
            break;
    }

    return 0;
}

/* 00000C04-00000C68       .text calcMtx__10daKnob00_cFv */
void daKnob00_c::calcMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000C68-00000D84       .text CreateInit__10daKnob00_cFv */
BOOL daKnob00_c::CreateInit() {
    tevStr.mRoomNo = current.roomNo;
    setAction(0);

    attention_info.position.y += 150.0f;
    eyePos.y += 150.0f;
    attention_info.flags = fopAc_Attn_ACTION_DOOR_e;

    calcMtx();
    mpBgW->Move();
    initProc(0);

    mDoorType = getType();
    if (getShapeType() == 4 && mDoorType == 1) {
        mDoorType = 5;
        fopAcM_create(PROC_TAG_MK, 0xffffff03, &current.pos, fopAcM_GetRoomNo(this), &current.angle, NULL, 0, NULL);
        attention_info.position.y += 60.0f;
        eyePos.y += 60.0f;
    }

    if (getShapeType() == 6) {
        mDoorType = 6;
        home.angle.z = 0x366a;
    }
    return TRUE;
}

/* 00000D84-00000E70       .text create__10daKnob00_cFv */
cPhs_State daKnob00_c::create() {
    cPhs_State ret = dComIfG_resLoad(&mPhase, M_arcname);
#if VERSION == VERSION_DEMO
    if (ret != cPhs_COMPLEATE_e) {
        return ret;
    }
    fopAcM_SetupActor(this, daKnob00_c);
#else
    fopAcM_SetupActor(this, daKnob00_c);
    if (ret != cPhs_COMPLEATE_e) {
        return ret;
    }
#endif

    if (fopAcM_GetRoomNo(this) == -1) {
        fopAcM_SetRoomNo(this, getFRoomNo());
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2700)) {
        return cPhs_ERROR_e;
    }

    CreateInit();
    return cPhs_COMPLEATE_e;
}

/* 00000E70-00000F30       .text setStart__10daKnob00_cFff */
void daKnob00_c::setStart(float arg1, float arg2) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz sp14 = current.pos;
    s16 angle = shape_angle.y + 0x7FFF;

    sp14.x += cM_ssin(angle) * arg2 - cM_scos(angle) * arg1;
    sp14.z += cM_scos(angle) * arg2 + cM_ssin(angle) * arg1;

    player->setPlayerPosAndAngle(&sp14, player->shape_angle.y);
}

/* 00000F30-00000F4C       .text setAngle__10daKnob00_cFv */
void daKnob00_c::setAngle() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    player->changeDemoMoveAngle(shape_angle.y + 0x7FFF);
}

/* 00000F4C-0000108C       .text adjustmentProc__10daKnob00_cFv */
BOOL daKnob00_c::adjustmentProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 angle = shape_angle.y + 0x7FFF;
    cXyz sp14;
    cXyz sp08;

    sp08 = player->current.pos;
    sp14 = current.pos;

    sp14.x += cM_ssin(angle) * -70.0f;
    sp14.z += cM_scos(angle) * -70.0f;

    if (m314 > 0) {
        sp08.x = sp08.x * 0.8f + sp14.x * 0.2f;
        sp08.z = sp08.z * 0.8f + sp14.z * 0.2f;
        player->setPlayerPosAndAngle(&sp08, player->current.angle.y);
        m314--;
    } else {
        player->setPlayerPosAndAngle(&sp14, player->current.angle.y);
        return TRUE;
    }
    return FALSE;
}

/* 0000108C-00001334       .text demoProc__10daKnob00_cFv */
BOOL daKnob00_c::demoProc() {
    s32 demoAction;
    BOOL ret = FALSE;

    demoAction = getDemoAction();

    if (dComIfGp_evmng_getIsAddvance(mStaffId)) {
        switch(demoAction) {
            case 9:
                setStart(0.0f, -70.0f);
                break;

            case 0x11:
                setStart(-43.0f, -14.8f);
                if (mpBgW->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mpBgW);
                }
                break;

            case 0x12:
                setStart(46.0f, -86.0f);
                if (mpBgW->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mpBgW);
                }
                break;

            case 0xc:
                openInit(0);
                break;

            case 0xd:
                openInit(1);
                break;

            case 0xe:
                openInit(2);
                break;

            case 0xf:
                openInit(3);
                break;

            case 10:
                setAngle();
                break;

            case 0xb:
                m314 = 10;
                break;

            case 0x10:
                m2D0.init(home.angle.z);
                break;
        }
    }

    switch (demoAction) {
        case 12:
        case 13:
        case 14:
        case 15:
            if (checkFlag(1)) {
                if (openProc(demoAction)) {
                    openEnd();
                    dComIfGp_evmng_cutEnd(mStaffId);
                }
            } else {
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            break;

        case 11:
            if (adjustmentProc()) {
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            break;

        case 16:
            if (mAction == 9) {
                daNpcMt_c* mt = (daNpcMt_c*)fopAcM_searchFromName("Mt", 0, 0);
                if (mt != NULL) {
                    if (m2D0.proc(&mt->attention_info.position)) {
                        ret = 1;
                    }
                } else if (m2D0.proc(&attention_info.position)) {
                    ret = 1;
                }
            } else if (m2D0.proc(&attention_info.position)) {
                ret = 1;
            }
            break;
            
        default:
            dComIfGp_evmng_cutEnd(mStaffId);
            break;
    }

    return ret;
}

/* 00001334-00001398       .text demoProc2__10daKnob00_cFv */
BOOL daKnob00_c::demoProc2() {
    BOOL ret = FALSE;
    switch (getDemoAction()) {
        case 16:
            ret = TRUE;
            break;
        
        default:
            dComIfGp_evmng_cutEnd(mStaffId);
            break;
    }
    return ret;
}

/* 00001398-000013F0       .text actionWait__10daKnob00_cFv */
BOOL daKnob00_c::actionWait() {
    if (eventInfo.checkCommandDoor()) {
        initOpenDemo(0);
        setAction(2);
        demoProc();
    } else {
        setEventPrm();
    }
    return TRUE;
}

/* 000013F0-00001488       .text actionDemo__10daKnob00_cFv */
BOOL daKnob00_c::actionDemo() {
    if (dComIfGp_evmng_endCheck(mEventIdx[m2C6])) {
        if (m2C6 != 7 && m2C6 != 8) {
            setAction(1);
            dComIfGp_event_reset();
            shape_angle.y = current.angle.y;
        }
    } else {
        demoProc();
    }
    return TRUE;
}

/* 00001488-0000151C       .text actionTalk__10daKnob00_cFv */
BOOL daKnob00_c::actionTalk() {
    if (demoProc()) {
        if (mAction == 9) {
            daNpcMt_c* mt = (daNpcMt_c*)fopAcM_searchFromName("Mt", 0, 0);
            if (mt != NULL) {
                mt->attnOff();
            }
        }
        nextAction();
        dComIfGp_event_reset();
        shape_angle.y = current.angle.y;
    }
    return TRUE;
}

/* 0000151C-00001574       .text actionTalkWait__10daKnob00_cFv */
BOOL daKnob00_c::actionTalkWait() {
    if (eventInfo.checkCommandDoor()) {
        initOpenDemo(0);
        setAction(3);
        demoProc();
    } else {
        setEventPrm();
    }
    return TRUE;
}

/* 00001574-000017AC       .text actionPassward2__10daKnob00_cFv */
BOOL daKnob00_c::actionPassward2() {
    switch (m316) {
        case 0:
            if (demoProc2()) {
                m316++;
                if (!dComIfGs_isEventBit(0x3b20)) {
                    dComIfGs_onEventBit(0x3b20);
                    dComIfGs_setEventReg(0xba0f, (s8)cM_rndF(6.0f));
                }
#if VERSION == VERSION_DEMO
                s32 tmp = dComIfGs_getEventReg(0xba0f);
                m2D0.init(tmp + 0x1b1a);
#else
                s32 tmp = dComIfGs_getEventReg(0xba0f);
                tmp += 0x1b1a;
                m2D0.init(tmp);
#endif
            }
            break;

        case 1:
            if (m2D0.proc(&attention_info.position)) {
                m316++;
                dComIfGp_InputPasswordOpenOn();
            }
            break;
        
        case 2:
            switch (dComIfGp_InputPasswordOpenCheck()) {
                case 1:
                    if (chkPassward() == -1) {
                        m316 = 10;
                        m2D0.init(0x1b19);
                    } else {
                        dComIfGs_onEventBit(0x1910);
                        m316++;
                        m2D0.init(0x1b18);
                    }
                    break;

                case 0:
                    m316 = 10;
                    m2D0.init(0x1b19);
                    break;
            }
            break;

        case 3:
            if (m2D0.proc(&attention_info.position)) {
                setAction(1);
                dComIfGp_event_reset();
                shape_angle.y = current.angle.y;
            }
            break;

        case 10:
            if (m2D0.proc(&attention_info.position)) {
                setAction(5);
                dComIfGp_event_reset();
                shape_angle.y = current.angle.y;
            }
            break;
    }
    return TRUE;
}

/* 000017AC-00001830       .text actionVilla__10daKnob00_cFv */
BOOL daKnob00_c::actionVilla() {
    if (eventInfo.checkCommandDoor()) {
        initOpenDemo(0);
        setAction(7);
        demoProc();
    } else if (dComIfGs_isEventBit(0x2d80)) {
        setAction(1);
    } else {
        setEventPrm();
    }
    return TRUE;
}

/* 00001830-00001890       .text actionPassward__10daKnob00_cFv */
BOOL daKnob00_c::actionPassward() {
    if (eventInfo.checkCommandDoor()) {
        initOpenDemo(0);
        setAction(6);
        actionPassward2();
        m316 = 0;
    } else {
        setEventPrm();
    }
    return TRUE;
}

/* 00001890-00001A24       .text actionInit__10daKnob00_cFv */
BOOL daKnob00_c::actionInit() {
    if (!mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Regist(mpBgW, this);
    }

    if (mDoorType == 6 && !dComIfGs_isEventBit(0x3401)) {
        actionFigure();
        setAction(10);
        return TRUE;
    }
    
    if (mDoorType == 5 && !dComIfGs_isEventBit(0x2d80)) {
        actionVilla();
        setAction(8);
        return TRUE;
    }
    
    if (mDoorType == 4) {
        if (!dComIfGs_isEventBit(0x1910)) {
            setAction(5);
            actionPassward();
            return TRUE;
        }

        if (dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) {
            setAction(11);
            return TRUE;
        }
    }

    if (msgDoor() && !chkException()) {
        actionTalkWait();
        setAction(4);
        return TRUE;
    }

    actionWait();
    setAction(1);
    return TRUE;
}

/* 00001A24-00001B04       .text actionFigure__10daKnob00_cFv */
BOOL daKnob00_c::actionFigure() {
    if (eventInfo.checkCommandDoor()) {
        daNpcMt_c* mt = (daNpcMt_c*)fopAcM_searchFromName("Mt", 0, 0);
        if (mt != NULL) {
            dComIfGp_event_setTalkPartner(mt);
            fopAcM_OnStatus(mt, fopAcStts_UNK800_e);
            mt->attnOn();
        }

        initOpenDemo(0);
        setAction(9);
        demoProc();
    } else if (dComIfGs_isEventBit(0x3401)) {
        setAction(1);
    } else {
        setEventPrm();
    }
    return TRUE;
}

/* 00001B04-00001B0C       .text actionDead__10daKnob00_cFv */
BOOL daKnob00_c::actionDead() {
    return TRUE;
}

/* 00001B0C-00001CA0       .text draw__10daKnob00_cFv */
BOOL daKnob00_c::draw() {
    if (drawCheck(0) == 0) {
#if VERSION == VERSION_DEMO
        return TRUE;
    }
#else
        if (getShapeType() == 1) {
            fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
        }
        return TRUE;
    }

    if (getShapeType() == 1) {
        fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
    }
#endif

    fpc_ProcID iVar1 = fopAcM_GetLinkId(this);
    if (iVar1 != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* ac = fopAcM_SearchByID(iVar1);
        if (fopAcM_IsActor(ac) && fopAcM_GetName(ac) == PROC_Obj_Pirateship) {
            daObjPirateship::Act_c* pirateShip = (daObjPirateship::Act_c*)ac;
            if (pirateShip->m2CC == 0) {
                return TRUE;
            }
        }
    }

    if (getShapeType() == 5) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    } else {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    }

    g_env_light.setLightTevColorType(mpModel2, &tevStr);
    J3DModelData* modelData = mpModel->getModelData();
    mBckAnm.entry(modelData, mBckAnm.getFrame());
    mpModel->calc();
    mpModel2->setBaseTRMtx(mpModel->getAnmMtx(m_jnt));
    mDoExt_modelUpdateDL(mpModel2);
    return TRUE;
}

/* 00001CA0-00001CC0       .text daKnob00_Draw__FP10daKnob00_c */
static BOOL daKnob00_Draw(daKnob00_c* i_this) {
    return ((daKnob00_c*)i_this)->draw();
}

BOOL daKnob00_c::execute() {
    switch(checkExecute()) {
        case 0:
            setAction(0);
            break;
    
        case 2:
            switch(mAction) {
                case 0:
                    actionInit();
                    break;

                case 1:
                    actionWait();
                    break;

                case 2:
                    actionDemo();
                    break;

                case 4:
                    actionTalkWait();
                    break;

                case 3:
                    actionTalk();
                    break;

                case 5:
                    actionPassward();
                    break;

                case 6:
                    actionPassward2();
                    break;

                case 8:
                    actionVilla();
                    break;

                case 7:
                    actionTalk();
                    break;

                case 10:
                    actionFigure();
                    break;

                case 9:
                    actionTalk();
                    break;

                default:
                    actionDead();
                    break;
            }
            break;
    
        case 1:
            startDemoProc();
            demoProc();
            break;
    
        default:    
            JUT_ASSERT(VERSION_SELECT(1169, 1169, 1183, 1183), FALSE);
            break;
    
    }
    
    mRoomNo2 = dComIfGp_roomControl_getStayNo();
    if (getType2() == 1) {
        calcMtx();
        if (mpBgW != NULL && mpBgW->ChkUsed()) {
            mpBgW->Move();
        }
    }
    return TRUE;
}


/* 00001CC0-00001E78       .text daKnob00_Execute__FP10daKnob00_c */
static BOOL daKnob00_Execute(daKnob00_c* i_this) {
    return i_this->execute();
}

/* 00001E78-00001E80       .text daKnob00_IsDelete__FP10daKnob00_c */
static BOOL daKnob00_IsDelete(daKnob00_c*) {
    return TRUE;
}

/* 00001E80-00001F50       .text daKnob00_Delete__FP10daKnob00_c */
static BOOL daKnob00_Delete(daKnob00_c* i_this) {
#if VERSION > VERSION_DEMO
    if (i_this->heap != NULL) 
#endif
    {
        if (i_this->mpBgW != NULL && i_this->mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(i_this->mpBgW);
        }
    }

    dComIfG_resDeleteDemo(&i_this->mPhase, daKnob00_c::M_arcname);

    i_this->~daKnob00_c();
    return TRUE;
}

/* 00001F50-00001F70       .text daKnob00_Create__FP10fopAc_ac_c */
static cPhs_State daKnob00_Create(fopAc_ac_c* i_this) {
    return ((daKnob00_c*)i_this)->create();
}

static actor_method_class l_daKnob00_Method = {
    (process_method_func)daKnob00_Create,
    (process_method_func)daKnob00_Delete,
    (process_method_func)daKnob00_Execute,
    (process_method_func)daKnob00_IsDelete,
    (process_method_func)daKnob00_Draw,
};

actor_process_profile_definition g_profile_KNOB00 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KNOB00,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daKnob00_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KNOB00,
    /* Actor SubMtd */ &l_daKnob00_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
