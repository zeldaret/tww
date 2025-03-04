//
// Generated by dtk
// Translation Unit: d_attention.cpp
//

#include "d/d_attention.h"
#include "d/d_procname.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_s_play.h"
#include "SSystem/SComponent/c_angle.h"

s32 dAttention_c::loc_type_num = 3;
u32 dAttention_c::act_type_num = 5;

dAttention_c::LocTbl dAttention_c::loc_type_tbl[3] = {
    { 0, 1 },
    { 1, 2 },
    { 2, 4 },
};

dAttention_c::LocTbl dAttention_c::act_type_tbl[5] = {
    { 3, 0x08 },
    { 4, 0x10 },
    { 5, 0x20 },
    { 6, 0x40 },
    { 7, 0x80 },
};

/* 8009D220-8009D268       .text __ct__11dAttParam_cFl */
dAttParam_c::dAttParam_c(s32) {
    field_0x04 = 45.0f;
    field_0x08 = 30.0f;
    field_0x0c = 90.0f;
    mFlags = 1;
    mSWModeDisable = -0.9f;
    mDangerBGMDistance = 3000.0f;
    mBGMDistMargin = 1000.0f;
}

/* 8009D268-8009D2B0       .text __dt__11dAttParam_cFv */
dAttParam_c::~dAttParam_c() {
}

/* 8009D2B0-8009D2E0       .text execute__19dAttDraw_CallBack_cFUsP16J3DTransformInfo */
bool dAttDraw_CallBack_c::execute(u16 timing, J3DTransformInfo* xform) {
    if (timing == 0) {
        xform->mTranslate.y *= REG6_F(17) + 0.6f;
    }
    return true;
}

/* 8009D2E0-8009D654       .text __ct__12dAttention_cFP10fopAc_ac_cUl */
dAttention_c::dAttention_c(fopAc_ac_c* player, u32 playerNo) {
    mpPlayer = (daPy_lk_c*)player;
    mPlayerNo = playerNo;
    initList(0xFFFFFFFF);
    mFlagMask = 0;
    field_0x01c = -1;
    field_0x019 = 0;
    mLockOnState = 0;
    field_0x01a = 0;
    field_0x01b = 0;
    mLockOnTargetBsPcID = fpcM_ERROR_PROCESS_ID_e;
    heap = mDoExt_createSolidHeapFromGameToCurrent(0x3600, 0);
    JUT_ASSERT(0xb9, heap != NULL);

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Always", ALWAYS_BDL_YAZIRUSHI_01);
    JUT_ASSERT(0xbe, modelData != NULL);

    int anmColNum = 0;
    for (u32 i = 0; i < 5; i++) {
        static u16 l_bpkIdx[] = {
            ALWAYS_BPK_YJ_IN, ALWAYS_BPK_YJ_OUT, ALWAYS_BPK_YJ_SCALE, ALWAYS_BPK_YJ_LOOP, ALWAYS_BPK_YJ_DELETE,
        };
        J3DAnmColor* anmCol = (J3DAnmColor*)dComIfG_getObjectRes("Always", l_bpkIdx[i]);
        JUT_ASSERT(0xcc, anmCol != NULL);

        anmCol->searchUpdateMaterialID(modelData);
        if (anmCol->getUpdateMaterialNum() > anmColNum)
            anmColNum = anmCol->getUpdateMaterialNum();
    }

    for (s32 i = 0; i < (s32)ARRAY_SIZE(draw); i++) {
        draw[i].anm = new mDoExt_McaMorf(
            modelData,
            &mCallBack, NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("Always", ALWAYS_BCK_YJ_LOOP),
            J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
            NULL,
            0x00080000,
            0x01000003
        );
        JUT_ASSERT(0xe3, draw[i].anm != NULL && draw[i].anm->getModel() != NULL);
        draw[i].mpAnmClr = NULL;
        draw[i].mpAnmMatClr = new J3DMatColorAnm[anmColNum];
    }

    mDoExt_restoreCurrentHeap();
    if (mDoExt_adjustSolidHeap(heap) >= 0)
        DCStoreRangeNoSync(heap->getStartAddr(), heap->getSize());

    field_0x028 = -1;
    mFlags = 0;
    mHint.init();
    mCatch.init();
    mLook[0].init();
    mLook[1].init();
    new(&mAttParam) dAttParam_c(0);
}

/* 8009D654-8009D6EC       .text __dt__12dAttention_cFv */
dAttention_c::~dAttention_c() {
    if (heap != NULL) {
        mDoExt_destroySolidHeap(heap);
        heap = NULL;
    }
}

/* 8009D6EC-8009D728       .text GetActionList__12dAttention_cFl */
dAttList_c* dAttention_c::GetActionList(s32 idx) {
    if (mActionNum != 0)
        return &mActionList[(mActionOffs + idx) % mActionNum];
    else
        return NULL;
}

/* 8009D728-8009D764       .text GetLockonList__12dAttention_cFl */
dAttList_c* dAttention_c::GetLockonList(s32 idx) {
    if (mLockOnNum != 0)
        return &mLockOnList[(mLockOnOffs + idx) % mLockOnNum];
    else
        return NULL;
}

/* 8009D764-8009D858       .text getActionBtnB__12dAttention_cFv */
dAttList_c* dAttention_c::getActionBtnB() {
    int i;
    dAttList_c* list = GetLockonList(0);
    if (list != NULL && list->getActor() != NULL &&
            list->mType == fopAc_Attn_TYPE_TALK_e &&
            LockonTruth() &&
            !(list->getActor()->attention_info.flags & fopAc_Attn_TALKFLAG_NOTALK_e))
        return list;

    if (mActionNum == 0)
        return NULL;

    for (i = 0; i < mActionNum; i++) {
        if (mActionList[i].mType == fopAc_Attn_TYPE_SPEAK_e) {
            if (!(mActionList[i].getActor()->attention_info.flags & fopAc_Attn_TALKFLAG_NOTALK_e))
                return &mActionList[i];
        } else {
            return &mActionList[i];
        }
    }

    return NULL;
}

/* 8009D858-8009D9A8       .text getActionBtnXYZ_local__12dAttention_cFi */
dAttList_c* dAttention_c::getActionBtnXYZ_local(int button) {
    int i;
    dAttList_c* list = GetLockonList(0);
    if (list != NULL && list->getActor() != NULL && list->mType == 1 && LockonTruth() != 0) {
        fopAc_ac_c* actor = list->getActor();
        if (actor->eventInfo.chkCondition(dEvtCnd_CANTALKITEM_e)) {
            s16 rt;
            if (actor->eventInfo.mpCheckCB == NULL)
                rt = 1;
            else
                rt = actor->eventInfo.mpCheckCB(actor, button);

            if (rt)
                return list;
        }

        return NULL;
    } else {
        if (mActionNum == 0)
            return NULL;

        for (i = 0; i < mActionNum; i++) {
            if (mActionList[i].mType == 3) {
                fopAc_ac_c* actor = mActionList[i].getActor();
                if (actor->eventInfo.chkCondition(dEvtCnd_CANTALKITEM_e)) {
                    s16 rt;
                    if (actor->eventInfo.mpCheckCB == NULL)
                        rt = 1;
                    else
                        rt = actor->eventInfo.mpCheckCB(actor, button);

                    if (rt)
                        return &mActionList[i];
                }
            }
        }

        return NULL;
    }
}

/* 8009D9A8-8009D9FC       .text getActionBtnX__12dAttention_cFv */
dAttList_c* dAttention_c::getActionBtnX() {
    if (!dComIfGs_checkGetItemNum(dComIfGp_getSelectItem(dItemBtn_X_e)))
        return NULL;

    return getActionBtnXYZ_local(0);
}

/* 8009D9FC-8009DA50       .text getActionBtnY__12dAttention_cFv */
dAttList_c* dAttention_c::getActionBtnY() {
    if (!dComIfGs_checkGetItemNum(dComIfGp_getSelectItem(dItemBtn_Y_e)))
        return NULL;

    return getActionBtnXYZ_local(1);
}

/* 8009DA50-8009DAA4       .text getActionBtnZ__12dAttention_cFv */
dAttList_c* dAttention_c::getActionBtnZ() {
    if (!dComIfGs_checkGetItemNum(dComIfGp_getSelectItem(dItemBtn_Z_e)))
        return NULL;

    return getActionBtnXYZ_local(2);
}

/* 8009DAA4-8009DAF4       .text chkAttMask__12dAttention_cFUlUl */
s32 dAttention_c::chkAttMask(u32 type, u32 mask) {
    for (s32 i = 0; i < loc_type_num; i++) {
        if (type == loc_type_tbl[i].mType) {
            return mask & loc_type_tbl[i].mMask;
        }
    }

    return 1;
}

/* 8009DAF4-8009DB60       .text check_event_condition__FUlUs */
s32 check_event_condition(u32 attnType, u16 flags) {
    switch(attnType) {
        case fopAc_Attn_TYPE_SPEAK_e:
        case fopAc_Attn_TYPE_TALK_e:
            if ((flags & dEvtCnd_CANTALK_e) != dEvtCnd_NONE_e) {
                break;
            }
            return true;

        case fopAc_Attn_TYPE_DOOR_e:
            if ((flags & dEvtCnd_CANDOOR_e) != dEvtCnd_NONE_e) {
                break;
            }
            return true;
        case fopAc_Attn_TYPE_TREASURE_e:
            if ((flags & dEvtCnd_CANDOOR_e) != dEvtCnd_NONE_e) {
                break;
            }
            return true;
    }
    return false;
}


/* 8009DB60-8009DC28       .text check_flontofplayer__FUlss */
s32 check_flontofplayer(u32 checkMask, s16 angle1, s16 angle2) {
    /// merged from TP
    static uint ftp_table[] = {
        0x04, 0x01, 0x02, 0x08, 0x10, 0x20, 0x40, 0x80, 0x100,
    };
    static s16 ang_table[3] = {
        0x4000,
        0x2000,
        0x0AAA,
    };
    static s16 ang_table2[] = {
        0x0AAA, 0x2000, 0x2AAA, 0x4000, 0x4E38, 0x6000,
    };

    if (angle1 < 0) {
        angle1 = -angle1;
    }

    if (angle2 < 0) {
        angle2 = -angle2;
    }

    for (int i = 0; i < 3; i++) {
        if (checkMask & ftp_table[i]) {
            if (angle1 > ang_table[i]) {
                return true;
            }
        }
    }

    for (int i = 8; i > 2; i--) {
        if (checkMask & ftp_table[i]) {
            if (angle2 > ang_table2[i - 3]) {
                return true;
            }
        }
    }

    return false;
}

/* 8009DC28-8009DC74       .text distace_weight__Ffsf */
f32 distace_weight(f32 distance, s16 angle, f32 ratio) {
    f32 turns = (f32)angle / 32768.0F;
    return distance * (f32)((1.0F - ratio) + (f32)(ratio * (turns * turns)));
}

/* 8009DC74-8009DCD4       .text distace_angle_adjust__Ffsf */
f32 distace_angle_adjust(f32 distance, s16 angle, f32 ratio) {
    f32 turns = angle / (f32)0x8000;
    if (turns < 0.0f) {
        turns = -turns;
    }

    return distance * ((1.0f - ratio) + (ratio * ((1.0f - turns) * (1.0f - turns))));
}

/* 8009DCD4-8009DE44       .text check_distace__FP4cXyzsP4cXyzffff */
s32 check_distace(cXyz* playerPos, s16 angle, cXyz* actorPos, f32 maxDistXZBase, f32 maxDistAngleMul, f32 maxDeltaY, f32 minDeltaY) {
    cXyz dist = *actorPos - *playerPos;

    if (dist.y <= minDeltaY || dist.y >= maxDeltaY) {
        return false;
    }

    f32 adjust = maxDistXZBase + distace_angle_adjust(maxDistAngleMul, angle, 1.0f);
    if (adjust < dist.absXZ()) {
        return false;
    }

    return true;
}

/* 8009DE44-8009E03C       .text calcWeight__12dAttention_cFiP10fopAc_ac_cfssPUl */
f32 dAttention_c::calcWeight(int, fopAc_ac_c*, f32, s16, s16, u32*) {
    /* Nonmatching */
}

/* 8009E03C-8009E128       .text setLList__12dAttention_cFP10fopAc_ac_cffUl */
void dAttention_c::setLList(fopAc_ac_c* i_actor, f32 i_weight, f32 i_distance, u32 i_attnType) {
    if (i_weight > 0.0f) {
        int i, maxIndex;
        if (mLockOnNum < (s32)ARRAY_SIZE(mLockOnList)) {
            maxIndex = mLockOnNum;
            mLockOnNum++;
        } else {
            f32 bestWeight = 0.0f;
            for (i = 0, maxIndex = 0; i < (s32)ARRAY_SIZE(mLockOnList); i++) {
                if (mLockOnList[i].mWeight > bestWeight) {
                    bestWeight = mLockOnList[i].mWeight;
                    maxIndex = i;
                }
            }
        }

        if (mLockOnList[maxIndex].mWeight > i_weight) {
            mLockOnList[maxIndex].setActor(i_actor);
            mLockOnList[maxIndex].mWeight = i_weight;
            mLockOnList[maxIndex].mDistance = i_distance;
            mLockOnList[maxIndex].mType = i_attnType;
        }
    }
}

/* 8009E128-8009E214       .text setAList__12dAttention_cFP10fopAc_ac_cffUl */
void dAttention_c::setAList(fopAc_ac_c* i_actor, f32 i_weight, f32 i_distance, u32 i_attnType) {
    if (i_weight > 0.0f) {
        int i, maxIndex;
        if (mActionNum < (s32)ARRAY_SIZE(mActionList)) {
            maxIndex = mActionNum;
            mActionNum++;
        } else {
            f32 bestWeight = 0.0f;
            for (i = 0, maxIndex = 0; i < (s32)ARRAY_SIZE(mActionList); i++) {
                if (mActionList[i].mWeight > bestWeight) {
                    bestWeight = mActionList[i].mWeight;
                    maxIndex = i;
                }
            }
        }

        if (mActionList[maxIndex].mWeight > i_weight) {
            mActionList[maxIndex].setActor(i_actor);
            mActionList[maxIndex].mWeight = i_weight;
            mActionList[maxIndex].mDistance = i_distance;
            mActionList[maxIndex].mType = i_attnType;
        }
    }
}

/* 8009E214-8009E2CC       .text initList__12dAttention_cFUl */
void dAttention_c::initList(u32 flagMask) {
    int i;

    mFlagMask = flagMask;

    for (i = 0; i < (s32)ARRAY_SIZE(mLockOnList); i++) {
        mLockOnList[i].setActor(NULL);
        mLockOnList[i].mWeight = 3.4028235E38f;
    }
    mLockOnOffs = 0;
    mLockOnNum = 0;

    for (i = 0; i < (s32)ARRAY_SIZE(mActionList); i++) {
        mActionList[i].setActor(NULL);
        mActionList[i].mWeight = 3.4028235E38f;
    }
    mActionOffs = 0;
    mActionNum = 0;
}

/* 8009E2CC-8009E2F8       .text select_attention__FP10fopAc_ac_cPv */
int select_attention(fopAc_ac_c* pActor, void* i_attention) {
    dAttention_c * pAttention = (dAttention_c*)i_attention;
    return pAttention->SelectAttention(pActor);
}

/* 8009E2F8-8009E33C       .text makeList__12dAttention_cFv */
s32 dAttention_c::makeList() {
    fopAcIt_Executor((fopAcIt_ExecutorFunc)select_attention, this);
    return mLockOnNum + mActionNum;
}

/* 8009E33C-8009E474       .text SelectAttention__12dAttention_cFP10fopAc_ac_c */
int dAttention_c::SelectAttention(fopAc_ac_c* ac) {
    if (ac == mpPlayer || mpPlayer == NULL)
        return 0;

    mFlagMask = mpPlayer->attention_info.flags;

    cSGlobe globe1(ac->attention_info.position - mpPlayer->attention_info.position);
    cSAngle angle1;
    angle1 = globe1.U() - fopAcM_GetShapeAngle_p(mpPlayer)->y;

    cSGlobe globe2(mpPlayer->attention_info.position - ac->attention_info.position);
    cSAngle angle2;
    angle2 = globe2.U() - fopAcM_GetShapeAngle_p(ac)->y;

    u32 type;
    f32 weight = calcWeight('L', ac, globe1.R(), angle1, angle2, &type);
    setLList(ac, weight, globe1.R(), type);
    weight = calcWeight('A', ac, globe1.R(), angle1, angle2, &type);
    setAList(ac, weight, globe1.R(), type);
    return 0;
}

/* 8009E474-8009E5C4       .text sortList__12dAttention_cFv */
void dAttention_c::sortList() {
    /* Nonmatching */
}

/* 8009E5C4-8009E684       .text stockAttention__12dAttention_cFUl */
void dAttention_c::stockAttention(u32 interactMask) {
    fopAc_ac_c * pTarget = LockonTarget(0);
    initList(interactMask);
    if (makeList())
        sortList();

    if (pTarget != mLockOnList[0].getActor()) {
        if (pTarget != NULL) {
            if (mLockOnList[0].getActor() != NULL)
                setFlag(0x02);
        } else {
            setFlag(0x01);
        }

        setFlag(0x04);
    }

    LockonTarget(0);
}

/* 8009E684-8009E728       .text nextAttention__12dAttention_cFUl */
fopAc_ac_c *dAttention_c::nextAttention(u32 interactMask) {
    fopAc_ac_c * pTarget = fopAcM_SearchByID(mLockOnTargetBsPcID);
    initList(interactMask);
    if (makeList())
        sortList();

    if (pTarget == mLockOnList[0].getActor() && mLockOnNum > 1)
        mLockOnOffs = 1;

    return LockonTarget(0);
}

/* 8009E728-8009E764       .text freeAttention__12dAttention_cFv */
s32 dAttention_c::freeAttention() {
    mLockOnOffs = 0;
    mLockOnNum = 0;
    mActionOffs = 0;
    mActionNum = 0;
    initList(0xFFFFFFFF);
    return 0;
}

/* 8009E764-8009E978       .text chaseAttention__12dAttention_cFv */
void dAttention_c::chaseAttention() {
    /* Nonmatching */
}

/* 8009E978-8009EA24       .text EnemyDistance__12dAttention_cFP10fopAc_ac_c */
f32 dAttention_c::EnemyDistance(fopAc_ac_c* actor) {
    if (actor == mpPlayer || mpPlayer == NULL)
        return -1.0f;

    if (fopAcM_GetProfName(actor) == PROC_PLAYER)
        return -1.0f;

    if (!(actor->attention_info.flags & fopAc_Attn_LOCKON_BATTLE_e) && !(actor->attention_info.flags & fopAc_Attn_ENEMYFLAG_NOLOCKON_e))
        return -1.0f;

    f32 dist = fopAcM_searchActorDistance(mpPlayer, actor);
    if (dist < (dist_table[actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e]].mDistXZMax + dist_table[actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e]].mDistXZAngleAdjust))
        return dist;
    return -1.0f;
}

/* 8009EA24-8009EAA4       .text sound_attention__FP10fopAc_ac_cPv */
BOOL sound_attention(fopAc_ac_c* actor, void* userWork) {
    dAttention_c* i_this = (dAttention_c*)userWork;
    f32 dist = i_this->EnemyDistance(actor);
    if (dist < 0.0f)
        return FALSE;
    if (dist < i_this->mEnemyDistance) {
        i_this->mEnemyBsPcId = fopAcM_GetID(actor);
        i_this->mEnemyDistance = dist;
    }
    return FALSE;
}

/* 8009EAA4-8009EB38       .text runSoundProc__12dAttention_cFv */
void dAttention_c::runSoundProc() {
    mEnemyBsPcId = fpcM_ERROR_PROCESS_ID_e;
    mEnemyDistance = 10000.0f;
    if (!chkFlag(0x80000000)) {
        fopAcIt_Executor((fopAcIt_ExecutorFunc)sound_attention, this);
        fopAc_ac_c* actor = fopAcM_SearchByID(mEnemyBsPcId);
        if (actor != NULL) {
            mDoAud_bgmNowBattle(mEnemyDistance * 0.1f);
            setFlag(0x100);
        }
    }
}

/* 8009EB38-8009EDB8       .text runDrawProc__12dAttention_cFv */
void dAttention_c::runDrawProc() {
    /* Nonmatching */
}

/* 8009EDB8-8009EDBC       .text runDebugDisp0__12dAttention_cFv */
void dAttention_c::runDebugDisp0() {
}

/* 8009EDBC-8009EDC0       .text runDebugDisp__12dAttention_cFv */
void dAttention_c::runDebugDisp() {
}

/* 8009EDC0-8009EE90       .text judgementButton__12dAttention_cFv */
void dAttention_c::judgementButton() {
    /* Nonmatching */
}

/* 8009EE90-8009EED8       .text judgementTriggerProc__12dAttention_cFv */
void dAttention_c::judgementTriggerProc() {
    /* Nonmatching */
}

/* 8009EED8-8009EF40       .text judgementLostCheck__12dAttention_cFv */
void dAttention_c::judgementLostCheck() {
    /* Nonmatching */
}

/* 8009EF40-8009F0A4       .text judgementStatusSw__12dAttention_cFUl */
void dAttention_c::judgementStatusSw(u32) {
    /* Nonmatching */
}

/* 8009F0A4-8009F1D4       .text judgementStatusHd__12dAttention_cFUl */
void dAttention_c::judgementStatusHd(u32) {
    /* Nonmatching */
}

/* 8009F1D4-8009F460       .text Run__12dAttention_cFUl */
void dAttention_c::Run(u32) {
    /* Nonmatching */
}

/* 8009F460-8009F5FC       .text Draw__12dAttention_cFv */
void dAttention_c::Draw() {
    /* Nonmatching */
}

/* 8009F5FC-8009F6B4       .text setAnm__10dAttDraw_cFiii */
void dAttDraw_c::setAnm(int, int, int) {
    /* Nonmatching */
}

/* 8009F6B4-8009F834       .text draw__10dAttDraw_cFR4cXyzPA4_f */
void dAttDraw_c::draw(cXyz&, Mtx) {
    /* Nonmatching */
}

/* 8009F834-8009F88C       .text LockonTarget__12dAttention_cFl */
fopAc_ac_c* dAttention_c::LockonTarget(s32 idx) {
    if (idx >= mLockOnNum)
        return NULL;

    s32 listIdx = mLockOnOffs + idx;
    if (listIdx >= mLockOnNum)
        listIdx -= mLockOnNum;

    return mLockOnList[listIdx].getActor();
}

/* 8009F88C-8009F980       .text LockonReleaseDistanse__12dAttention_cFv */
f32 dAttention_c::LockonReleaseDistanse() {
    if (!LockonTruth()) {
        return 0.0f;
    }

    fopAc_ac_c* actor = mLockOnList[mLockOnOffs].getActor();
    if (actor == NULL) {
        return 0.0f;
    }

    int idx =  actor->attention_info.distances[mLockOnList[mLockOnOffs].mType];
    cSGlobe globe(actor->attention_info.position - mpPlayer->attention_info.position);
    cSAngle angle(globe.U() - fopAcM_GetShapeAngle_p(mpPlayer)->y);

    return distace_angle_adjust(dist_table[idx].mDistXZAngleAdjust, angle, 1.0f) + dist_table[idx].mDistXZMaxRelease;
}

/* 8009F980-8009F9B8       .text LockonTargetPId__12dAttention_cFl */
fpc_ProcID dAttention_c::LockonTargetPId(s32 idx) {
    if (idx >= mLockOnNum)
        return NULL;

    s32 listIdx = mLockOnOffs + idx;
    if (listIdx >= mLockOnNum)
        listIdx -= mLockOnNum;

    return mLockOnList[listIdx].getPid();
}

/* 8009F9B8-8009FA10       .text ActionTarget__12dAttention_cFl */
fopAc_ac_c* dAttention_c::ActionTarget(s32 idx) {
    if (idx >= mActionNum)
        return NULL;

    s32 listIdx = mActionOffs + idx;
    if (listIdx >= mActionNum)
        listIdx -= mActionNum;

    return mActionList[listIdx].getActor();
}

/* 8009FA10-8009FA64       .text LockonTruth__12dAttention_cFv */
bool dAttention_c::LockonTruth() {
    return mLockOnState == 1 || (mLockOnState == 2 && LockonTarget(0));
}

/* 8009FA64-8009FA98       .text getActor__10dAttList_cFv */
fopAc_ac_c* dAttList_c::getActor() {
    return fopAcM_SearchByID(mActorID);
}

/* 8009FA98-8009FAB4       .text setActor__10dAttList_cFP10fopAc_ac_c */
void dAttList_c::setActor(fopAc_ac_c* i_actor) {
    mActorID = fopAcM_GetID(i_actor);
}

/* 8009FAB4-8009FACC       .text getPId__10dAttHint_cFPv */
fpc_ProcID dAttHint_c::getPId(void* i_proc) {
    return fopAcM_GetID(i_proc);
}

/* 8009FACC-8009FAFC       .text convPId__10dAttHint_cFUi */
fopAc_ac_c* dAttHint_c::convPId(fpc_ProcID i_procID) {
    return fopAcM_SearchByID(i_procID);
}

/* 8009FAFC-8009FB58       .text request__10dAttHint_cFP10fopAc_ac_ci */
int dAttHint_c::request(fopAc_ac_c* i_actor, int priority) {
    if (priority < 0)
        priority = 0x1FF;

    if (priority <= mPriority) {
        mHintActorID = getPId(i_actor);
        mPriority = priority;
    }

    return TRUE;
}

/* 8009FB58-8009FB70       .text init__10dAttHint_cFv */
void dAttHint_c::init() {
    mHintActorID = fpcM_ERROR_PROCESS_ID_e;
    mZHintTargetID = fpcM_ERROR_PROCESS_ID_e;
    mPriority = 0x200;
}

/* 8009FB70-8009FB8C       .text proc__10dAttHint_cFv */
void dAttHint_c::proc() {
    mZHintTargetID = mHintActorID;
    mHintActorID = fpcM_ERROR_PROCESS_ID_e;
    mPriority = 0x200;
}

/* 8009FB8C-8009FBBC       .text convPId__11dAttCatch_cFUi */
fopAc_ac_c* dAttCatch_c::convPId(fpc_ProcID i_procID) {
    return fopAcM_SearchByID(i_procID);
}

/* 8009FBBC-8009FBDC       .text init__11dAttCatch_cFv */
void dAttCatch_c::init() {
    mCatchItemNo = 0x56;
    mRequestActorID = fpcM_ERROR_PROCESS_ID_e;
    mCatghTargetID = fpcM_ERROR_PROCESS_ID_e;
    field_0x4 = 3;
}

/* 8009FBDC-8009FC08       .text proc__11dAttCatch_cFv */
void dAttCatch_c::proc() {
    mCatghTargetID = mRequestActorID;
    mChangeItem = mCatchItemNo;
    mRequestActorID = fpcM_ERROR_PROCESS_ID_e;
    field_0x4 = 3;
    mCatchItemNo = 0x56;
}


/* 8009FC08-8009FE10       .text request__11dAttCatch_cFP10fopAc_ac_cUcfffsi */
bool dAttCatch_c::request(fopAc_ac_c* reqActor, u8 itemNo, f32 horizontalDist, f32 upDist, f32 downDist, s16 angle, int param_7) {
    // TODO: what is param_7?
    fopAc_ac_c* player = g_dComIfG_gameInfo.play.mpPlayer[0];
    if (param_7 > field_0x4) {
        return false;
    } 

    cXyz vec_to_player = reqActor->attention_info.position - player->attention_info.position;
    if (vec_to_player.y < downDist || vec_to_player.y > upDist) {
        return false;
    }

    f32 player_xz_dist = vec_to_player.absXZ();
    if (player_xz_dist > horizontalDist) {
        return false;
    }

    if (angle != 0) {
        cSGlobe globe(vec_to_player);
        csXyz* player_angle_p = fopAcM_GetShapeAngle_p(player);

        s16 angle2 = globe.U() - player_angle_p->y;
        if (angle2 < 0) {
            angle2 = -angle2;
        }
        if (angle2 > angle) {
            return false;
        }
    }

    if (param_7 < field_0x4 || player_xz_dist < mDistance) {
        field_0x4 = param_7;
        mCatchItemNo = itemNo;
        mRequestActorID = fopAcM_GetID(reqActor);
        mDistance = player_xz_dist;
        return true;
    }

    return false;
}

/* 8009FE10-8009FE40       .text convPId__10dAttLook_cFUi */
fopAc_ac_c* dAttLook_c::convPId(fpc_ProcID i_procID) {
    return fopAcM_SearchByID(i_procID);
}

/* 8009FE40-8009FE58       .text init__10dAttLook_cFv */
void dAttLook_c::init() {
    mRequestActorID = fpcM_ERROR_PROCESS_ID_e;
    mLookTargetID = fpcM_ERROR_PROCESS_ID_e;
    field_0x4 = 3;
}

/* 8009FE58-8009FE74       .text proc__10dAttLook_cFv */
void dAttLook_c::proc() {
    mLookTargetID = mRequestActorID ;
    mRequestActorID = fpcM_ERROR_PROCESS_ID_e;
    field_0x4 = 3;
}

/* 8009FE74-800A009C       .text request__10dAttLook_cFP10fopAc_ac_cfffsi */
bool dAttLook_c::request(fopAc_ac_c* reqActor, f32 horizontalDist, f32 upDist, f32 downDist, s16 angle, int param_6) {
    // TODO: what is param_6
    fopAc_ac_c* player = g_dComIfG_gameInfo.play.mpPlayer[0];
    if (param_6 > field_0x4) {
        return false;
    }

    cXyz vec_to_player = reqActor->eyePos - player->eyePos;
    if (vec_to_player.y < downDist || vec_to_player.y > upDist) {
        return false;
    }

    f32 player_xz_dist = vec_to_player.absXZ();
    if (player_xz_dist > horizontalDist) {
        return false;
    }

    if (angle != 0) {
        vec_to_player = reqActor->current.pos - player->current.pos;
        cSGlobe globe(vec_to_player);
        s16 angle2 = globe.U() - fopAcM_GetShapeAngle_p(player)->y;
        if (angle2 < 0) {
            angle2 = -angle2;
        }
        if (angle2 > angle) {
            return false;
        }
    }

    if (param_6 < field_0x4 || player_xz_dist < mDistance) {
        field_0x4 = param_6;
        mRequestActorID = fopAcM_GetID(reqActor);
        mDistance = player_xz_dist;
        return true;
    }

    return false;
}

/* 800A009C-800A0270       .text requestF__10dAttLook_cFP10fopAc_ac_csi */
bool dAttLook_c::requestF(fopAc_ac_c* reqActor, s16 angle, int param_3) {
    // TODO: what is param_3?
    fopAc_ac_c* player = g_dComIfG_gameInfo.play.mpPlayer[0];
    if (param_3 > this->field_0x4) {
        return false;
    }
    cXyz vec_to_player = reqActor->eyePos - player->eyePos;
    f32 player_xz_dist = vec_to_player.absXZ();

    if (angle != 0) {
        vec_to_player = reqActor->current.pos - player->current.pos;
        cSGlobe globe(vec_to_player);
        s16 angle2 = globe.U() - fopAcM_GetShapeAngle_p(player)->y;
        if (angle2 < 0) {
            angle2 = -angle2;
        }
        if (angle2 > angle) {
            return false;
        }
    }
    if (param_3 < field_0x4 || player_xz_dist < mDistance) {
        field_0x4 = param_3;
        mRequestActorID = fopAcM_GetID(reqActor);
        mDistance = player_xz_dist;
        return true;
    }

    return false;
}
