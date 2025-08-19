/**
 * d_a_player_bow.inc
 *
 * Code relating to the Bow item.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_arrow.h"
#include "d/actor/d_a_npc_so.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_procname.h"

/* 80149ECC-80149F88       .text bowJointCB__9daPy_lk_cFi */
BOOL daPy_lk_c::bowJointCB(int param_0) {
    if (checkBowReadyAnime()) {
        return true;
    }

    if (param_0 == 6) {
        mDoMtx_stack_c::transS(0.0f, 4.5f, 4.5f);
        mDoMtx_stack_c::revConcat(mpEquipItemModel->getAnmMtx(6));
        mpEquipItemModel->setAnmMtx(param_0, mDoMtx_stack_c::get());
    } else {
        mpEquipItemModel->setAnmMtx(11, mpEquipItemModel->getAnmMtx(6));
    }
    return true;
}

/* 80149F88-80149FD0       .text daPy_bowJointCB__FP7J3DNodei */
static BOOL daPy_bowJointCB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        if (i_this != 0) {
            i_this->bowJointCB(jntNo);
        }
    }
    return TRUE;
}

/* 80149FD0-8014A008       .text bowButton__9daPy_lk_cCFv */
BOOL daPy_lk_c::bowButton() const {
    if (checkBowMiniGame()) {
        return doButton();
    } else {
        return itemButton();
    }
}

/* 8014A008-8014A02C       .text checkBowReadyAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkBowReadyAnime() const {
    return checkBowReloadAnime() || checkBowWaitAnime();
}

/* 8014A02C-8014A080       .text checkBowAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkBowAnime() const {
    return checkBowReadyAnime() || checkBowShootAnime();
}

/* 8014A080-8014A180       .text makeArrow__9daPy_lk_cFv */
void daPy_lk_c::makeArrow() {
    if ((!checkBowMiniGame() && dComIfGs_getArrowNum() != 0) ||
        (checkBowMiniGame() && dComIfGp_event_getPt1() &&
         fopAcM_GetName(dComIfGp_event_getPt1()) == PROC_NPC_SO &&
         ((daNpc_So_c*)dComIfGp_event_getPt1())->getMiniGameRestArrow() > 0))
    {
        fopAc_ac_c* arrow_p = (fopAc_ac_c*)fopAcM_fastCreate(PROC_ARROW, 0, &current.pos, fopAcM_GetRoomNo(this));
        mActorKeepEquip.setData(arrow_p);
    }
    m355C = 0;
}

/* 8014A180-8014A1CC       .text deleteArrow__9daPy_lk_cFv */
void daPy_lk_c::deleteArrow() {
    fopAc_ac_c* equip_actor = mActorKeepEquip.getActor();

    if (equip_actor != NULL && fopAcM_GetName(equip_actor) == PROC_ARROW) {
        fopAcM_delete(equip_actor);
        mActorKeepEquip.clearData();
    }
}

/* 8014A1CC-8014A2A0       .text setBowReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::setBowReadyAnime() {
    setActAnimeUpper(
        LKANM_BCK_ARROWSHOOT,
        UPPER_MOVE2_e,
        1.0f,
        daPy_HIO_bow_c0::m.field_0x0 - 0.001f,
        daPy_HIO_bow_c0::m.field_0x0,
        10.0f
    );
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_ARROWSHOOTA));
    m35EC = daPy_HIO_bow_c0::m.field_0x0 - 0.001f;
    setPriTextureAnime(0x70, 0);
    m355E = 10;
    seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
}

/* 8014A2A0-8014A328       .text setBowReloadAnime__9daPy_lk_cFv */
void daPy_lk_c::setBowReloadAnime() {
    setActAnimeUpper(
        LKANM_BCK_ARROWRELORD,
        UPPER_MOVE2_e,
        daPy_HIO_bow_c0::m.field_0x10,
        daPy_HIO_bow_c0::m.field_0x14,
        daPy_HIO_bow_c0::m.field_0x2,
        daPy_HIO_bow_c0::m.field_0x18
    );
    setPriTextureAnime(0x8d, 0);
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_ARROWRELORDA));
    m35EC = 0.0f;
    seStartOnlyReverb(JA_SE_LK_DRAW_BOW);
}

/* 8014A328-8014A60C       .text checkNextActionBowReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionBowReady() {
    if (checkBowWaitAnime()) {
        daArrow_c* arrow = (daArrow_c*)mActorKeepEquip.getActor();
        if (m355C != 0) {
            setActAnimeUpper(
                LKANM_BCK_ARROWSHOOT,
                UPPER_MOVE2_e,
                daPy_HIO_bow_c0::m.field_0x4,
                daPy_HIO_bow_c0::m.field_0x8,
                daPy_HIO_bow_c0::m.field_0x0,
                daPy_HIO_bow_c0::m.field_0xC
            );
            setPriTextureAnime(0x70, 0);
            mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_ARROWSHOOTA));
            m35EC = 0.0f;
        } else if (bowButton() == NULL) {
            if (arrow != NULL) {
                fopAcM_SetParam(arrow, 1);
                if (!checkBowMiniGame()) {
                    dComIfGp_setItemArrowNumCount(-1);
                }
                mActorKeepEquip.clearData();
                seStartOnlyReverb(JA_SE_LK_SHOOT_ARROW);
                voiceStart(41);
                onResetFlg0(daPyRFlg0_ARROW_SHOOT);
            }
            m355C = 1;
        } else if (daArrow_c::changeArrowMp()) {
            if (mEquipItem != dItem_BOW_e) {
                dComIfGp_setRStatus(dActStts_SWAP_MODES_e);
                if (spActionTrigger() && arrow != NULL) {
                    mActorKeepEquip.setData(arrow->changeArrowType());
                    setBowReloadAnime();
                }
            }
        }
    } else if (checkBowReloadAnime()) {
        if (mFrameCtrlUpper[UPPER_MOVE2_e].getRate() < 0.01f) {
            setActAnimeUpper(LKANM_BCK_BOWWAIT, UPPER_MOVE2_e, 1.0f, 0.0f, -1, -1.0f);
            mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_BOWWAITA));
            m35EC = 0.0f;
            setPriTextureAnime(0x70, 0);
        }
    } else if (checkBowShootAnime()) {
        if (mFrameCtrlUpper[UPPER_MOVE2_e].getRate() < 0.01f) {
            if (m355E == 0 && bowButton() &&
                (checkBowMiniGame() || mEquipItem == getReadyItem()) &&
                !checkUseArrowEffect())
            {
                setBowReloadAnime();
                makeArrow();
                if (mActorKeepEquip.getActor() == NULL) {
                    seStartSystem(JA_SE_ITEM_TARGET_OUT);
                }
            } else if (daArrow_c::changeArrowMp()) {
                if (mEquipItem != dItem_BOW_e) {
                    dComIfGp_setRStatus(dActStts_SWAP_MODES_e);
                    if (spActionTrigger()) {
                        daArrow_c::changeArrowTypeNotReady();
                    }
                }
            }
        }
        if (m355E != 0) {
            m355E--;
        }
    }

    return cancelItemUpperReadyAnime();
}

/* 8014A60C-8014A680       .text checkNextActionBowFly__9daPy_lk_cFv */
void daPy_lk_c::checkNextActionBowFly() {
    if (checkBowAnime()) {
        checkNextActionBowReady();
    } else if (itemTrigger() && mEquipItem == getReadyItem()) {
        setBowReadyAnime();
        m355E = 0;
    }
}

/* 8014A680-8014A6F4       .text checkNextBowMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextBowMode() {
    if (checkAttentionLock()) {
        return procBowMove_init();
    } else {
        return procBowSubject_init();
    }
}

/* 8014A6F4-8014A834       .text setBowModel__9daPy_lk_cFv */
void daPy_lk_c::setBowModel() {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_ARROWRELORDA);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_BOW, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(394, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
    m35EC = 0.0f;
    J3DMaterial* lineMat_mtl = mpEquipItemModel->getModelData()->getJointNodePointer(0x00)->getMesh()->getNext();
    J3DMaterial* lineDamMAT_mtl = lineMat_mtl->getNext();
    lineMat_mtl->getShape()->show();
    lineDamMAT_mtl->getShape()->hide();
    tmp_modelData->getJointNodePointer(6)->setCallBack(daPy_bowJointCB);
    tmp_modelData->getJointNodePointer(11)->setCallBack(daPy_bowJointCB);
    mpEquipItemModel->setUserArea(reinterpret_cast<u32>(this));
}

/* 8014A834-8014A8D4       .text procBowSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowSubject_init() {
    if (mCurProc == daPyProc_BOW_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_BOW_SUBJECT_e);

    if (!checkBowAnime()) {
        setBowReadyAnime();
    }
    setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);

    mVelocity = 0.0f;

    dComIfGp_setPlayerStatus0(0, daPyStts0_BOW_AIM_e);

    return true;
}

/* 8014A8D4-8014A974       .text procBowSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowSubject() {
    dComIfGp_setDoStatus(dActStts_RETURN_e);

    if (checkAttentionLock()) {
        setSpeedAndAngleAtn();
    }

    if (!checkNextMode(0)) {
        setBodyAngleToCamera();
        m35EC = mFrameCtrlUpper[UPPER_MOVE2_e].getFrame();
    }

    return true;
}

/* 8014A974-8014AA2C       .text procBowMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowMove_init() {
    if (mCurProc == daPyProc_BOW_MOVE_e) {
        return false;
    }

    commonProcInit(daPyProc_BOW_MOVE_e);
    if (mDirection == DIR_LEFT) {
        current.angle.y = shape_angle.y + 0x4000;
    } else {
        mDirection = DIR_RIGHT;
        current.angle.y = shape_angle.y + -0x4000;
    }
    if (!checkBowAnime()) {
        setBowReadyAnime();
    }
    setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    dComIfGp_setPlayerStatus0(0, daPyStts0_BOW_AIM_e);
    return true;
}

/* 8014AA2C-8014AB5C       .text procBowMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowMove() {
    if (mpAttnActorLockOn != NULL) {
        setSpeedAndAngleAtnActor();
    } else if (!checkAttentionLock() && mActorKeepEquip.getActor() == NULL) {
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
    } else {
        setSpeedAndAngleAtn();
    }
    if (!checkNextMode(0)) {
        f32 fVar1 = -1.0f;
        if (std::fabsf(mVelocity) < 0.001f) {
            onModeFlg(ModeFlg_00000001);
            if (mDirection != DIR_RIGHT) {
                mDirection = DIR_RIGHT;
                fVar1 = daPy_HIO_basic_c0::m.field_0xC;
            }
            current.angle.y = shape_angle.y + -0x4000;
        } else {
            offModeFlg(ModeFlg_00000001);
        }
        setBlendAtnMoveAnime(fVar1);
        setBodyAngleXReadyAnime();
        m35EC = mFrameCtrlUpper[UPPER_MOVE2_e].getFrame();
    }
    return true;
}
