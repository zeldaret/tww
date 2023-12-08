// This .inc file must exist because these functions are split into a separate .text section by -sym on.
// Furthermore, the order of the symbols in d_npc's .data section does not match without this being a separate file.
// The original name of this file is not known as there are no asserts within it, so a guess was taken.

#include "d/d_npc.h"
#include "d/d_com_inf_game.h"

bool dNpc_EventCut_c::cutProc() {
    static char* action_table[] = {
        "WAIT",
        "TURN_TO_ACTOR",
        "MOVE_TO_ACTOR",
        "TURN_TO_POS",
        "MOVE_TO_POS",
        "TALK_MSG",
        "CONTINUE_TALK"
    };

    if(mpEvtStaffName == 0 || mpActor == 0) {
        return false;
    }
    else {
        mEvtStaffId = dComIfGp_evmng_getMyStaffId(mpEvtStaffName);
        if(mEvtStaffId == -1) {
            return false;
        }
        else {
            typedef void(dNpc_EventCut_c::*cut_func_t)(void);
            struct cut_entry_t {
                cut_func_t start;
                cut_func_t proc;
            };

            static cut_entry_t cut_tbl[] = {
                {
                    &dNpc_EventCut_c::cutWaitStart,
                    &dNpc_EventCut_c::cutWaitProc,
                },
                {
                    &dNpc_EventCut_c::cutTurnToActorStart,
                    &dNpc_EventCut_c::cutTurnToActorProc,
                },
                {
                    &dNpc_EventCut_c::cutMoveToActorStart,
                    &dNpc_EventCut_c::cutMoveToActorProc,
                },
                {
                    &dNpc_EventCut_c::cutTurnToPosStart,
                    &dNpc_EventCut_c::cutTurnToPosProc,
                },
                {
                    &dNpc_EventCut_c::cutMoveToPosStart,
                    &dNpc_EventCut_c::cutMoveToPosProc,
                },
                {
                    &dNpc_EventCut_c::cutTalkMsgStart,
                    &dNpc_EventCut_c::cutTalkMsgProc,
                },
                {
                    &dNpc_EventCut_c::cutContinueTalkStart,
                    &dNpc_EventCut_c::cutTalkMsgProc,
                },
            };

            mCurActIdx = dComIfGp_evmng_getMyActIdx(mEvtStaffId, action_table, ARRAY_SIZE(action_table), 1, 0);
            if(mCurActIdx == -1) {
                return false;
            }
            else {
                if(dComIfGp_evmng_getIsAddvance(mEvtStaffId)) {
                    mbAttention = 0;
                    (this->*cut_tbl[mCurActIdx].start)();
                }
                
                (this->*cut_tbl[mCurActIdx].proc)();
                return 1;
            }
        }
    }
}

void dNpc_EventCut_c::cutWaitStart() {
    u32* timer = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "Timer");
    if(timer) {
        mTimer = (s16)*timer;
    }
    else {
        mTimer = 0;
    }
}

void dNpc_EventCut_c::cutWaitProc() {
    if(cLib_calcTimer(&mTimer) == 0) {
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }
}

void dNpc_EventCut_c::cutTurnToActorStart() {
    mpActorName = dComIfGp_evmng_getMyStringP(mEvtStaffId, "ActorName");

    u32* set = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "SetId");
    if(set) {
        mSetId = *set;
    }
    else {
        mSetId = 0;
    }

    cXyz* pos = dComIfGp_evmng_getMyXyzP(mEvtStaffId, "OffsetPos");
    if(pos) {
        mOffsetPos = *pos;
    }
    else {
        mOffsetPos.set(0.0f, 0.0f, 0.0f);
    }

    u32* turnType = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "TurnType");
    if(turnType) {
        mTurnType = *turnType;
    }
    else {
        mTurnType = 1;
    }

    u32* timer = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "Timer");
    if(timer) {
        mTimer = (s16)*timer;
    }
    else {
        mTimer = 1;
    }

    u32* speed = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "TurnSpeed");
    if(speed) {
        mTurnSpeed = *speed;
    }
    else {
        mTurnSpeed = 0;
    }

    u32* angle = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "AddAngle");
    if(angle == 0) {
        mAddAngle = 0;
    }
    else {
        mAddAngle = *angle;
    }

    f32* dist = dComIfGp_evmng_getMyFloatP(mEvtStaffId, "DelDistance");
    if(dist == 0) {
        pDelDistance = 0.0f;
    }
    else {
        pDelDistance = *dist;
    }

    u32* noTurn = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "NoTurn");
    if(noTurn) {
        mbNoTurn = 1;
    }
    else {
        mbNoTurn = 0;
    }

    field_0x44 = 0;
}

void dNpc_EventCut_c::cutTurnToActorProc() {
    if(mSetId != 0) {
        mTargetActorPos.set(0.0f, 0.0f, 0.0f);
        fopAcM_Search((fopAcIt_JudgeFunc)&findActorCallBack, this);
    }
    else {
        if(mpActorName == 0 || dEvmng_strcmp(mpActorName, "Player") == 0) {
            mpTargetActor = dComIfGp_getPlayer(0);
        }
        else {
            mTargetActorPos.set(0.0f, 0.0f, 0.0f);
            fopAcM_Search((fopAcIt_JudgeFunc)&findActorCallBack, this);
        }
    }

    if(field_0x68 != 0) {
        switch(mTurnType) {
            case 2:
                field_0x68[0xA] = 1;
            case 1:
                field_0x68[0xC] = 0;
                break;
            case 0:
                field_0x68[0xC] = 1;
                break;
            default:
                field_0x68[0xC] = 0;
                break;
        }
    }

    if(mpTargetActor == 0) {
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }
    if(mpActorName == 0 || dEvmng_strcmp(mpActorName, "Player") == 0) {
        mPos = dNpc_playerEyePos(0.0f) + mOffsetPos;
    }
    else {
        if(mAddAngle && pDelDistance) {
            u16 angle = mpTargetActor->shape_angle.y + mAddAngle;
            mPos = mpTargetActor->current.pos;
            mPos.x -= pDelDistance * cM_ssin(angle);
            mPos.z -= pDelDistance * cM_scos(angle);
        }
        else {
            mPos = mpTargetActor->current.pos + mOffsetPos;
        }
    }

    mbAttention = 1;

    s16 tAngle = cLib_targetAngleY(&mpActor->current.pos, &mPos);
    int temp2 = tAngle - mpActor->current.angle.y;
    f32 temp = fabsf(temp2);
    if(field_0x44 == temp && fabsf(temp2) < 5376.0f) {
        cLib_calcTimer(&mTimer);
    }

    if(mTimer == 0) {
        mTurnSpeed = 0;
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }
    
    field_0x44 = fabsf(tAngle - mpActor->current.angle.y);
}

void dNpc_EventCut_c::cutMoveToActorStart() {
    mpActorName = dComIfGp_evmng_getMyStringP(mEvtStaffId, "ActorName");
    u32* set = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "SetId");
    f32* speed = dComIfGp_evmng_getMyFloatP(mEvtStaffId, "Speed");
    f32* dist = dComIfGp_evmng_getMyFloatP(mEvtStaffId, "DelDistance");
    cXyz* offs = dComIfGp_evmng_getMyXyzP(mEvtStaffId, "OffsetPos");
    u32* attn = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "Attention");
    u32* noTurn = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "NoTurn");
    u32* angle = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "ShapeAngle");

    if(noTurn == 0) {
        mbNoTurn = 0;
    }
    else {
        mbNoTurn = 1;
    }

    if(attn == 0) {
        mbAttention = 0;
    }
    else {
        mbAttention = 1;
    }

    if(offs == 0) {
        mOffsetPos.set(0.0f, 0.0f, 0.0f);
    }
    else {
        mOffsetPos = *offs;
    }

    if(set == 0) {
        mSetId = 0;
    }
    else {
        mSetId = *set;
    }

    if(speed == 0) {
        mSpeed = 2.0f;
    }
    else {
        mSpeed = *speed;
    }

    if(dist == 0) {
        pDelDistance = 0.0f;
    }
    else {
        pDelDistance = *dist;
    }

    if(angle == 0) {
        mAddAngle = 0;
    }
    else {
        mAddAngle = *angle;
    }
}

/* 8021D730-8021D9DC       .text cutMoveToActorProc__15dNpc_EventCut_cFv */
void dNpc_EventCut_c::cutMoveToActorProc() {
    if(mSetId != 0) {
        mTargetActorPos.set(0.0f, 0.0f, 0.0f);
        fopAcM_Search((fopAcIt_JudgeFunc)&findActorCallBack, this);
    }
    else {
        if(mpActorName == 0 || dEvmng_strcmp(mpActorName, "Player") == 0) {
            mpTargetActor = dComIfGp_getPlayer(0);
        }
        else {
            mTargetActorPos.set(0.0f, 0.0f, 0.0f);
            fopAcM_Search((fopAcIt_JudgeFunc)&findActorCallBack, this);
        }
    }

    if(mpTargetActor == 0) {
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }

    cXyz temp = mpTargetActor->current.pos + mOffsetPos;
    s16 angle = fopAcM_searchActorAngleY(mpActor, mpTargetActor);
    if(mAddAngle != 0) {
        angle = mpTargetActor->shape_angle.y + mAddAngle;
    }

    temp.x -= pDelDistance * cM_ssin(angle);
    temp.z -= pDelDistance * cM_scos(angle);

    if(mSpeed == 0.0f) {
        mpActor->current.pos = temp;
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }

    f32 dist = (temp - mpActor->current.pos).absXZ();

    cLib_addCalc2(&mpActor->current.pos.x, temp.x, 0.1f, mSpeed);
    cLib_addCalc2(&mpActor->current.pos.z, temp.z, 0.1f, mSpeed);
    if(dist < 5.0f) {
        mSpeed = 0.0f;
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }
}

fopAc_ac_c* dNpc_EventCut_c::findActorCallBack(fopAc_ac_c* pActor, void* pData) {
    dNpc_EventCut_c* cut = static_cast<dNpc_EventCut_c*>(pData);

    if(cut == 0) {
        return 0;
    }
    
    if(cut->mSetId != 0 && pActor->mSetId == cut->mSetId) {
        cut->mTargetActorPos = pActor->current.pos;
        cut->mpTargetActor = pActor;

        return pActor;
    }
    else {
        if(cut->mpActorName == 0) {
            return 0;
        }
        else {
            dStage_objectNameInf* obj = dStage_searchName(cut->mpActorName);
            if(obj == 0) {
                return 0;
            }
            else {
                if(obj->mProcName == fopAcM_GetProfName(pActor) && obj->mSubtype == pActor->mSubtype) {
                    if(cut->mTargetActorPos.abs() == 0.0f) {
                        cut->mTargetActorPos = pActor->current.pos;
                        cut->mpTargetActor = pActor;
                    }
                    else {
                        f32 mag1 = (cut->mTargetActorPos - cut->mpActor->current.pos).abs();
                        f32 mag2 = (pActor->current.pos - cut->mpActor->current.pos).abs();
                        if(mag2 < mag1) {
                            cut->mTargetActorPos = pActor->current.pos;
                            cut->mpTargetActor = pActor;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

void dNpc_EventCut_c::cutTurnToPosStart() {
    cXyz* pos = dComIfGp_evmng_getMyXyzP(mEvtStaffId, "Pos");
    if(pos) {
        mPos = *pos;
    }
    else {
        mPos.set(0.0f, 0.0f, 0.0f);
    }

    u32* turnType = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "TurnType");
    if(turnType) {
        mTurnType = *turnType;
    }
    else {
        mTurnType = 1;
    }

    u32* timer = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "Timer");
    if(timer) {
        mTimer = (s16)*timer;
    }
    else {
        mTimer = 1;
    }

    u32* speed = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "TurnSpeed");
    if(speed) {
        mTurnSpeed = *speed;
    }
    else {
        mTurnSpeed = 0;
    }
    
    u32* noTurn = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "NoTurn");
    if(noTurn) {
        mbNoTurn = 1;
    }
    else {
        mbNoTurn = 0;
    }

    u32* angle = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "AddAngle");
    if(angle == 0) {
        mAddAngle = 0;
    }
    else {
        mAddAngle = *angle;
    }

    field_0x44 = 0;
}

void dNpc_EventCut_c::cutTurnToPosProc() {
    s16 tAngle = cLib_targetAngleY(&mpActor->current.pos, &mPos);
    mbAttention = 1;

    if(field_0x68 != 0) {
        switch(mTurnType) {
            case 2:
                field_0x68[0xA] = 1;
            case 1:
                field_0x68[0xC] = 0;
                break;
            case 0:
                field_0x68[0xC] = 1;
                break;
            default:
                field_0x68[0xC] = 0;
                break;
        }
    }

    int temp2 = tAngle - mpActor->current.angle.y;
    f32 temp = fabsf(temp2);
    if(field_0x44 == temp && fabsf(temp2) < 5376.0f) {
        cLib_calcTimer(&mTimer);
    }

    if(mTimer == 0) {
        mTurnSpeed = 0;
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }
    
    field_0x44 = fabsf(tAngle - mpActor->current.angle.y);
}

void dNpc_EventCut_c::cutMoveToPosStart() {
    cXyz* pos = dComIfGp_evmng_getMyXyzP(mEvtStaffId, "Pos");
    f32* speed = dComIfGp_evmng_getMyFloatP(mEvtStaffId, "Speed");
    f32* dist = dComIfGp_evmng_getMyFloatP(mEvtStaffId, "DelDistance");
    u32* attn = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "Attention");
    u32* noTurn = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "NoTurn");
    u32* angle = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "AddAngle");

    if(noTurn == 0) {
        mbNoTurn = 0;
    }
    else {
        mbNoTurn = 1;
    }

    if(pos == 0) {
        mPos.set(0.0f, 0.0f, 0.0f);
    }
    else {
        mPos = *pos;
    }
    
    if(attn == 0) {
        mbAttention = 0;
    }
    else {
        mbAttention = 1;
    }

    if(speed == 0) {
        mSpeed = 2.0f;
    }
    else {
        mSpeed = *speed;
    }

    if(dist == 0) {
        pDelDistance = 0.0f;
    }
    else {
        pDelDistance = *dist;
    }

    if(angle == 0) {
        mAddAngle = 0;
    }
    else {
        mAddAngle = *angle;
    }
}

/* 8021E168-8021E338       .text cutMoveToPosProc__15dNpc_EventCut_cFv */
void dNpc_EventCut_c::cutMoveToPosProc() {
    s16 angle = cLib_targetAngleY(&mpActor->current.pos, &mPos);

    cXyz temp;
    temp.x = mPos.x;
    temp.y = mPos.y;
    temp.z = mPos.z;
    temp.x -= pDelDistance * cM_ssin(angle);
    temp.z -= pDelDistance * cM_scos(angle);

    if(mSpeed == 0.0f) {
        mpActor->current.pos = temp;
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }

    f32 dist = sqrtf((temp - mpActor->current.pos).abs2XZ());

    cLib_addCalc2(&mpActor->current.pos.x, temp.x, 0.1f, mSpeed);
    cLib_addCalc2(&mpActor->current.pos.z, temp.z, 0.1f, mSpeed);
    if(dist < 5.0f) {
        mSpeed = 0.0f;
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }
}

void dNpc_EventCut_c::cutTalkMsgStart() {
    if(mpTalkActor != 0) {
        u32* attn = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "Attention");
        if(attn == 0) {
            mbAttention = 0;
        }
        else {
            mbAttention = 1;
        }

        u32* firstMsgNo = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "msg_num");
        u32* endMsgNo = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "end_msg");
        if(firstMsgNo == 0) {
            mpTalkActor->mCurrMsgNo = 0;
        }
        else {
            mpTalkActor->mCurrMsgNo = *firstMsgNo;
        }
        if(endMsgNo) {
            mpTalkActor->mEndMsgNo = *endMsgNo;
        }
        else {
            mpTalkActor->mEndMsgNo = -1;
        }

        field_0x52 = 1;
    }
}

void dNpc_EventCut_c::cutContinueTalkStart() {
    if(mpTalkActor != 0) {
        u32* endMsg = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "end_num");
        if(endMsg) {
            mpTalkActor->mEndMsgNo = *endMsg;
        }
        else {
            mpTalkActor->mEndMsgNo = -1;
        }
    }
}

void dNpc_EventCut_c::cutTalkMsgProc() {
    if(mpTalkActor == 0 || field_0x52 == 0) {
        dComIfGp_evmng_cutEnd(mEvtStaffId);
    }
    else {
        u16 status = mpTalkActor->talk(0);
        if(status == dNpcMsgStts_BOX_CLOSED_e) {
            field_0x52 = 0;
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
        else if((status == 2 || status == 6) && mpTalkActor->mEndMsgNo == mpTalkActor->mCurrMsgNo) {
            mpTalkActor->mEndMsgNo = -1;
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
    }
}
