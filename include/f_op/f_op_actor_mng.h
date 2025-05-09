#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "new.h" // IWYU pragma: export // Used by the fopAcM_SetupActor macro.
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_iter.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_searcher.h"
#include "m_Do/m_Do_audio.h"
#include "d/d_item_data.h"
#include "d/d_save.h"
#include "d/d_event.h"

#define fopAcM_SetupActor(ptr,ClassName) \
    if (!fopAcM_CheckCondition(ptr, fopAcCnd_INIT_e)) { \
        new (ptr) ClassName(); \
        fopAcM_OnCondition(ptr, fopAcCnd_INIT_e); \
    }

class J3DModelData;
class daItem_c;

struct fopAcM_prmBase_class {
    /* 0x00 */ u32 parameters;
    /* 0x04 */ cXyz position;
    /* 0x10 */ csXyz angle;
    /* 0x16 */ u16 setID;
};  // Size = 0x18

struct fopAcM_prmScale_class {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u8 z;
};  // Size: 0x3

struct fopAcM_prm_class {
    /* 0x00 */ fopAcM_prmBase_class base;
    /* 0x18 */ fopAcM_prmScale_class scale;
    /* 0x1B */ u8 gbaName;
    /* 0x1C */ fpc_ProcID parent_id;
    /* 0x20 */ s8 subtype;
    /* 0x21 */ s8 room_no;
};

struct fopAcM_search4ev_prm {
    fopAcM_search4ev_prm() { clear(); }
    void clear() {
        mName[0] = 0;
        mEventID = -1;
        mProcName = 11;
        mSubType = 0;
    }

    /* 0x00 */ char mName[30];
    /* 0x1E */ s16 mEventID;
    /* 0x20 */ s16 mProcName;
    /* 0x22 */ s8 mSubType;
};

struct fopAcM_search_prm {
    /* 0x00 */ const char * procname;
    /* 0x04 */ u32 prm_mask;
    /* 0x08 */ u32 parameter;
};

enum daItemType_e {
    daItemType_0_e = 0,
    daItemType_1_e = 1,
    daItemType_3_e = 3,
};

enum daItemAction_e {
    daItemAct_0_e = 0,
    daItemAct_1_e = 1,
    daItemAct_2_e = 2,
    daItemAct_3_e = 3,
    daItemAct_4_e = 4,
    daItemAct_BOSS_DISAPPEAR_e = 5,
    daItemAct_6_e = 6,
    daItemAct_7_e = 7,
    daItemAct_8_e = 8,
    daItemAct_9_e = 9,
    daItemAct_A_e = 10,
    daItemAct_B_e = 11,
    daItemAct_BOSS_e = 12,
};

enum daDisappearItemType_e {
    daDisItem_IBALL_e = 0,
    daDisItem_NONE1_e = 1,
    daDisItem_HEART_CONTAINER_e = 2,
    daDisItem_NONE3_e = 3,
    daDisItem_UNK4_e = 4,
    daDisItem_HEART_e = 10,
    daDisItem_MAGIC_e = 11,
    daDisItem_ARROW_e = 12,
    daDisItem_NONE13_e = 13,
};

class l_HIO {
public:
    ~l_HIO() {}

    void entry() {}
    void erase() {}
};

typedef BOOL (*heapCallbackFunc)(fopAc_ac_c*);
typedef int (*createFunc)(void*);

inline s8 fopAcM_GetRoomNo(fopAc_ac_c* pActor) {
    return pActor->current.roomNo;
}

inline fpc_ProcID fopAcM_GetID(void* pActor) {
    return fpcM_GetID(pActor);
}

inline s16 fopAcM_GetName(void* pActor) {
    return fpcM_GetName(pActor);
}

inline MtxP fopAcM_GetMtx(fopAc_ac_c* pActor) {
    return pActor->cullMtx;
}

inline bool fopAcM_CheckStatus(fopAc_ac_c* pActor, u32 status) {
    return pActor->actor_status & status;
}

inline u32 fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->actor_status & fopAcStts_CARRY_e;
}

inline u32 fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_CheckStatus(pActor, fopAcStts_HOOK_CARRY_e);
}

inline u32 fopAcM_GetParam(void* pActor) {
    return fpcM_GetParam(pActor);
}

inline u32 fopAcM_GetParamBit(u32 param, u8 shift, u8 bit) {
    return (param >> shift) & ((1 << bit) - 1);
}

inline void fopAcM_SetParam(void* p_actor, u32 param) {
    fpcM_SetParam(p_actor, param);
}

inline void fopAcM_SetJntHit(fopAc_ac_c* i_actorP, JntHit_c* i_jntHitP) {
    i_actorP->jntHit = i_jntHitP;
}

inline s16 fopAcM_GetProfName(void* pActor) {
    return fpcM_GetProfName(pActor);
}

inline actor_process_profile_definition* fopAcM_GetProfile(void* pActor) {
    return (actor_process_profile_definition*)fpcM_GetProfile(pActor);
}

inline void fopAcM_SetPriority(void* pActor, int priority) {
    fpcM_SetPriority(pActor, priority);
}

inline u8 fopAcM_GetGroup(fopAc_ac_c* p_actor) {
    return p_actor->group;
}

inline void fopAcM_SetGroup(fopAc_ac_c* pActor, u8 group) {
    pActor->group = group;
}

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->actor_status |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->actor_status &= ~flag;
}

inline BOOL fopAcM_CheckStatusMap(fopAc_ac_c* pActor, u32) {
    // TODO: This implementation probably isn't right, the u32 argument is likely used for something
    return (pActor->actor_status & fopAcStts_SHOWMAP_e) && (pActor->actor_status & 0x1F) == 0;
}

inline void fopAcM_SetStatusMap(fopAc_ac_c* pActor, u32 flag) {
    pActor->actor_status = (pActor->actor_status & ~0x3F) | fopAcStts_SHOWMAP_e | flag;
}

inline fopAc_ac_c* fopAcM_Search(fopAcIt_JudgeFunc func, void* param) {
    return (fopAc_ac_c*)fopAcIt_Judge(func, param);
}

inline cXyz* fopAcM_GetPosition_p(fopAc_ac_c* pActor) {
    return &pActor->current.pos;
}

inline cXyz& fopAcM_GetPosition(fopAc_ac_c* pActor) {
    return pActor->current.pos;
}

inline cXyz* fopAcM_GetOldPosition_p(fopAc_ac_c* pActor) {
    return &pActor->old.pos;
}

inline cXyz* fopAcM_GetSpeed_p(fopAc_ac_c* pActor) {
    return &pActor->speed;
}

inline cXyz& fopAcM_GetSpeed(fopAc_ac_c* pActor) {
    return pActor->speed;
}

inline csXyz* fopAcM_GetAngle_p(fopAc_ac_c* pActor) {
    return &pActor->current.angle;
}

inline csXyz* fopAcM_GetShapeAngle_p(fopAc_ac_c* pActor) {
    return &pActor->shape_angle;
}

inline u32 fopAcM_CheckCondition(fopAc_ac_c* p_actor, u32 flag) {
    return p_actor->actor_condition & flag;
}

inline void fopAcM_OnCondition(fopAc_ac_c* p_actor, u32 flag) {
    p_actor->actor_condition |= flag;
}

inline void fopAcM_OffCondition(fopAc_ac_c* p_actor, u32 flag) {
    p_actor->actor_condition &= ~flag;
}

inline BOOL fopAcM_IsActor(void* actor) {
    return fopAc_IsActor(actor);
}

inline void fopAcM_SetRoomNo(fopAc_ac_c* actor, s8 roomNo) {
    actor->current.roomNo = roomNo;
}

inline void fopAcM_setHookCarryNow(fopAc_ac_c* actor) {
    fopAcM_OnStatus(actor, fopAcStts_HOOK_CARRY_e);
}

inline void fopAcM_cancelHookCarryNow(fopAc_ac_c* actor) {
    fopAcM_OffStatus(actor, fopAcStts_HOOK_CARRY_e);
}

inline s8 fopAcM_GetHomeRoomNo(fopAc_ac_c* pActor) {
    return pActor->home.roomNo;
}

inline void fopAcM_SetHomeRoomNo(fopAc_ac_c* pActor, s8 roomNo) {
    pActor->home.roomNo = roomNo;
}

inline void fopAcM_SetGravity(fopAc_ac_c* actor, f32 gravity) {
    actor->gravity = gravity;
}

inline void fopAcM_SetMaxFallSpeed(fopAc_ac_c* actor, f32 speed) {
    actor->maxFallSpeed = speed;
}

inline void fopAcM_SetMtx(fopAc_ac_c* actor, MtxP m) {
    actor->cullMtx = m;
}

inline void fopAcM_SetSpeed(fopAc_ac_c* actor, f32 x, f32 y, f32 z) {
    actor->speed.set(x, y, z);
}

inline void fopAcM_SetSpeedF(fopAc_ac_c* actor, f32 f) {
    actor->speedF = f;
}

inline void fopAcM_SetStatus(fopAc_ac_c* actor, u32 status) {
    actor->actor_status = status;
}

inline void fopAcM_SetModel(fopAc_ac_c* actor, J3DModel* model) {
    actor->model = model;
}

inline J3DModel* fopAcM_GetModel(fopAc_ac_c* actor) {
    return actor->model;
}

inline fopAcM_prm_class* fopAcM_GetAppend(void* actor) {
    return (fopAcM_prm_class*)fpcM_GetAppend(actor);
}

inline BOOL fopAcM_IsExecuting(fpc_ProcID id) {
    return fpcM_IsExecuting(id);
}

inline f32 fopAcM_GetSpeedF(fopAc_ac_c* p_actor) {
    return p_actor->speedF;
}

inline f32 fopAcM_GetGravity(fopAc_ac_c* p_actor) {
    return p_actor->gravity;
}

inline f32 fopAcM_GetMaxFallSpeed(fopAc_ac_c* p_actor) {
    return p_actor->maxFallSpeed;
}

inline JntHit_c* fopAcM_GetJntHit(fopAc_ac_c* i_actor) {
    return i_actor->jntHit;
}

inline void fopAcM_setCullSizeFar(fopAc_ac_c* i_actor, f32 i_far) {
    i_actor->cullSizeFar = i_far;
}

inline f32 fopAcM_getCullSizeFar(fopAc_ac_c* i_actor) {
    return i_actor->cullSizeFar;
}

inline void fopAcM_SetCullSize(fopAc_ac_c* i_actor, int i_culltype) {
    i_actor->cullType = i_culltype;
}

inline int fopAcM_GetCullSize(fopAc_ac_c* i_actor) {
    return i_actor->cullType;
}

inline BOOL fopAcM_CULLSIZE_IS_BOX(int i_culltype) {
    return (i_culltype >= fopAc_CULLBOX_0_e && i_culltype < fopAc_CULLBOX_CUSTOM_e) || i_culltype == fopAc_CULLBOX_CUSTOM_e;
}

inline int fopAcM_CULLSIZE_IDX(int i_culltype) {
    return i_culltype - fopAc_CULLBOX_0_e;
}

inline int fopAcM_CULLSIZE_Q_IDX(int i_culltype) {
    return i_culltype - fopAc_CULLSPHERE_0_e;
}

inline cXyz* fopAcM_getCullSizeSphereCenter(fopAc_ac_c* i_actor) {
    return (cXyz*)&i_actor->cull.sphere.center;
}

inline f32 fopAcM_getCullSizeSphereR(fopAc_ac_c* i_actor) {
    return i_actor->cull.sphere.radius;
}

inline cXyz* fopAcM_getCullSizeBoxMax(fopAc_ac_c* actor) {
    return (cXyz*)&actor->cull.box.max;
}

inline cXyz* fopAcM_getCullSizeBoxMin(fopAc_ac_c* actor) {
    return (cXyz*)&actor->cull.box.min;
}

inline void dComIfGs_onSwitch(int i_no, int i_roomNo);
inline void dComIfGs_offSwitch(int i_no, int i_roomNo);
inline BOOL dComIfGs_isSwitch(int i_no, int i_roomNo);
inline void dComIfGs_revSwitch(int i_no, int i_roomNo);
inline void dComIfGs_offActor(int i_no, int i_roomNo);

inline void fopAcM_onSwitch(fopAc_ac_c* pActor, int sw) {
    return dComIfGs_onSwitch(sw, fopAcM_GetHomeRoomNo(pActor));
}

inline void fopAcM_offSwitch(fopAc_ac_c* pActor, int sw) {
    return dComIfGs_offSwitch(sw, fopAcM_GetHomeRoomNo(pActor));
}

inline BOOL fopAcM_isSwitch(fopAc_ac_c* pActor, int sw) {
    return dComIfGs_isSwitch(sw, fopAcM_GetHomeRoomNo(pActor));
}

inline void fopAcM_revSwitch(fopAc_ac_c* pActor, int sw) {
    return dComIfGs_revSwitch(sw, fopAcM_GetHomeRoomNo(pActor));
}

inline fopAc_ac_c* fopAcM_SearchByID(fpc_ProcID id) {
    return (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &id);
}

inline fopAc_ac_c* fopAcM_SearchByName(s16 procName) {
    return (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeForPName, &procName);
}

inline fpc_ProcID fopAcM_GetLinkId(const fopAc_ac_c* pActor) {
    return pActor->parentActorID;
}

inline void dComIfGs_onItem(int bitNo, int roomNo);
inline void fopAcM_onItem(fopAc_ac_c* item, int bitNo) {
    dComIfGs_onItem(bitNo, fopAcM_GetHomeRoomNo(item));
}

inline BOOL dComIfGs_isItem(int bitNo, int roomNo);
inline BOOL fopAcM_isItem(fopAc_ac_c* item, int bitNo) {
    return dComIfGs_isItem(bitNo, fopAcM_GetHomeRoomNo(item));
}

inline BOOL dComIfGs_isSaveSwitch(int i_stageNo, int i_no);
inline BOOL fopAcM_isItemForIb(int itemBitNo, u8 itemNo, s8 roomNo) {
    if (itemNo == dItem_BLUE_JELLY_e) {
        // Blue Chu Jelly uses itemBitNo as if it was a switch in stageNo 0xE.
        return dComIfGs_isSaveSwitch(dSv_save_c::STAGE_BLUE_CHU_JELLY, itemBitNo);
    } else {
        return dComIfGs_isItem(itemBitNo, roomNo);
    }
}

inline void dComIfGs_onSaveSwitch(int i_stageNo, int i_no);
inline void fopAcM_onItemForIb(int itemBitNo, u8 itemNo, s8 roomNo) {
    if (itemNo == dItem_BLUE_JELLY_e) {
        // Blue Chu Jelly uses itemBitNo as if it was a switch in stageNo 0xE.
        dComIfGs_onSaveSwitch(dSv_save_c::STAGE_BLUE_CHU_JELLY, itemBitNo);
    } else {
        dComIfGs_onItem(itemBitNo, roomNo);
    }
}

inline f32 fopAcM_searchActorDistanceY(fopAc_ac_c* actorA, fopAc_ac_c* actorB) {
    return actorB->current.pos.y - actorA->current.pos.y;
}

inline u16 fopAcM_GetSetId(fopAc_ac_c* p_actor) {
    return p_actor->setID;
}

inline void dComIfGs_onActor(int bitNo, int roomNo);

inline void fopAcM_onActor(fopAc_ac_c* p_actor) {
    int setId = fopAcM_GetSetId(p_actor);
    dComIfGs_onActor(setId, fopAcM_GetHomeRoomNo(p_actor));
}

inline bool fopAcM_IsFirstCreating(void* i_actor) {
    return fpcM_IsFirstCreating(i_actor);
}

void fopAcM_setStageLayer(void* p_proc);

void fopAcM_setRoomLayer(void* p_proc, int roomNo);

BOOL fopAcM_SearchByID(fpc_ProcID id, fopAc_ac_c** p_actor);

BOOL fopAcM_SearchByName(s16 procName, fopAc_ac_c** p_actor);

fopAcM_prm_class* fopAcM_CreateAppend();

fopAcM_prm_class* createAppend(u16 enemyNo, u32 parameters, cXyz* p_pos, int roomNo,
                               csXyz* p_angle, cXyz* p_scale, s8 subType,
                               fpc_ProcID parentPId);

void fopAcM_Log(fopAc_ac_c* p_actor, char* str);

BOOL fopAcM_delete(fopAc_ac_c* p_actor);
BOOL fopAcM_delete(fpc_ProcID actorID);

fpc_ProcID fopAcM_create(s16 i_procName, u32 i_parameter, cXyz* i_pos = NULL, int i_roomNo = -1,
                   csXyz* i_angle = NULL, cXyz* i_scale = NULL, s8 i_subType = -1,
                   createFunc i_createFunc = NULL);

fpc_ProcID fopAcM_create(char*, u32 i_parameter, cXyz* i_pos = NULL, int i_roomNo = -1,
                   csXyz* i_angle = NULL, cXyz* i_scale = NULL,
                   createFunc i_createFunc = NULL);

inline fpc_ProcID fopAcM_create(s16 i_procName, createFunc i_createFunc, void* params) {
    return fpcM_Create(i_procName, i_createFunc, params);
}

inline fpc_ProcID fopAcM_Create(s16 i_procName, createFunc i_createFunc, void* params) {
    return fpcM_Create(i_procName, i_createFunc,params);
}

void* fopAcM_fastCreate(s16 procName, u32 parameter, cXyz* p_pos = NULL, int roomNo = -1,
                        csXyz* p_angle = NULL, cXyz* p_scale = NULL, s8 subType = -1,
                        createFunc p_createFunc = NULL, void* p_createFuncData = NULL);

void* fopAcM_fastCreate(char* p_actorName, u32 parameter, cXyz* pActorPos = NULL, int roomNo = -1,
                        csXyz* p_angle = NULL, cXyz* p_scale = NULL,
                        createFunc p_createFunc = NULL, void* p_createFuncData = NULL);

fpc_ProcID fopAcM_createChild(s16 procName, fpc_ProcID parentPId, u32 parameters, cXyz* p_pos,
                        int roomNo, csXyz* p_angle, cXyz* p_scale = NULL, s8 subType = -1,
                        createFunc p_createFunc = NULL);

fpc_ProcID fopAcM_createChild(char* pProcNameString, fpc_ProcID parentPcId, u32 parameter, cXyz* pPos,
                        int roomNo, csXyz* pAngle, cXyz* pScale = NULL, createFunc createFunc = NULL);

fpc_ProcID fopAcM_createChildFromOffset(s16 procName, fpc_ProcID parentProcID, u32 actorParams,
                                  cXyz* p_pos, int roomNo, csXyz* p_angle,
                                  cXyz* p_scale, s8 subType, createFunc p_createFunc);
fpc_ProcID fopAcM_createChildFromOffset(char* pProcNameString, fpc_ProcID parentPcId, u32 parameter,
                                  cXyz* pPosOffs, int roomNo, csXyz* pAngleOffs, cXyz* pScale,
                                  createFunc createFunc);

void fopAcM_DeleteHeap(fopAc_ac_c* p_actor);

bool fopAcM_entrySolidHeap(fopAc_ac_c* p_actor, heapCallbackFunc p_heapCallback, u32 estimatedHeapSize);

inline void fopAcM_SetMin(fopAc_ac_c* p_actor, f32 minX, f32 minY, f32 minZ) {
    p_actor->cull.box.min.set(minX, minY, minZ);
}

inline void fopAcM_SetMax(fopAc_ac_c* p_actor, f32 maxX, f32 maxY, f32 maxZ) {
    p_actor->cull.box.max.set(maxX, maxY, maxZ);
}

void fopAcM_setCullSizeBox(fopAc_ac_c* p_actor, f32 minX, f32 minY, f32 minZ, f32 maxX, f32 maxY,
                           f32 maxZ);

void fopAcM_setCullSizeSphere(fopAc_ac_c* p_actor, f32 minX, f32 minY, f32 minZ, f32 radius);

void fopAcM_setCullSizeBox2(fopAc_ac_c* p_actor, J3DModelData* p_modelData);

bool fopAcM_addAngleY(fopAc_ac_c* p_actor, s16 target, s16 step);

void fopAcM_calcSpeed(fopAc_ac_c* p_actor);

void fopAcM_posMove(fopAc_ac_c* p_actor, const cXyz* p_movePos);

void fopAcM_posMoveF(fopAc_ac_c* p_actor, const cXyz* p_movePos);

s16 fopAcM_searchActorAngleY(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

s32 fopAcM_seenActorAngleY(fopAc_ac_c*, fopAc_ac_c*);

f32 fopAcM_searchActorDistance(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

f32 fopAcM_searchActorDistance2(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

f32 fopAcM_searchActorDistanceXZ(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

f32 fopAcM_searchActorDistanceXZ2(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

s32 fopAcM_rollPlayerCrash(fopAc_ac_c* i_this, f32 distAdjust, u32 flag);
s32 fopAcM_checkCullingBox(Mtx, f32, f32, f32, f32, f32, f32);
s32 fopAcM_cullingCheck(fopAc_ac_c*);
s32 fopAcM_orderTalkEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderTalkXBtnEvent(fopAc_ac_c* i_this, fopAc_ac_c* i_partner);
s32 fopAcM_orderTalkYBtnEvent(fopAc_ac_c* i_this, fopAc_ac_c* i_partner);
s32 fopAcM_orderTalkZBtnEvent(fopAc_ac_c* i_this, fopAc_ac_c* i_partner);
s32 fopAcM_orderZHintEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderSpeakEvent(fopAc_ac_c* i_actor);
s32 fopAcM_orderDoorEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderCatchEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderOtherEvent2(fopAc_ac_c* i_this, char* pEventName, u16 flag, u16 hind = -1);
s32 fopAcM_orderChangeEvent(fopAc_ac_c* i_this, char* pEventName, u16 flag, u16 hind);
s32 fopAcM_orderChangeEvent(fopAc_ac_c* i_this, fopAc_ac_c* i_partner, char* pEventName, u16 flag, u16 hind);
s32 fopAcM_orderChangeEventId(fopAc_ac_c* i_this, s16 eventIdx, u16 flag, u16 hind);
s32 fopAcM_orderChangeEventId(fopAc_ac_c* i_this, fopAc_ac_c* i_partner, s16 eventIdx, u16 flag, u16 hind);
s32 fopAcM_orderOtherEventId(fopAc_ac_c* actor, s16 eventIdx, u8 mapToolID = -1, u16 hind = -1,
                             u16 priority = 0, u16 flag = 1);
s32 fopAcM_orderPotentialEvent(fopAc_ac_c*, u16 flag, u16 hind, u16 priority);
s32 fopAcM_orderItemEvent(fopAc_ac_c*);
s32 fopAcM_orderTreasureEvent(fopAc_ac_c*, fopAc_ac_c*);
fopAc_ac_c* fopAcM_getTalkEventPartner(fopAc_ac_c*);
fopAc_ac_c* fopAcM_getItemEventPartner(fopAc_ac_c*);
fopAc_ac_c* fopAcM_getEventPartner(fopAc_ac_c*);

fpc_ProcID fopAcM_createItemForPresentDemo(cXyz* p_pos, int i_itemNo, u8 argFlag = 0x00, int i_itemBitNo = -1,
                                     int i_roomNo = -1, csXyz* p_angle = NULL, cXyz* p_scale = NULL);

fpc_ProcID fopAcM_createItemForTrBoxDemo(cXyz* p_pos, int i_itemNo, int i_itemBitNo = -1,
                                   int i_roomNo = -1, csXyz* p_angle = NULL, cXyz* p_scale = NULL);

fpc_ProcID fopAcM_createItemFromTable(cXyz* p_pos, int i_tableNo, int i_itemBitNo, int i_roomNo, int type,
                                csXyz* p_angle, int action, cXyz* p_scale = NULL);

fpc_ProcID fopAcM_createRaceItemFromTable(cXyz* pos, int i_itemNo, int i_itemBitNo, int i_roomNo,
                                    csXyz* angle, cXyz* scale, int param_7);

fpc_ProcID fopAcM_createShopItem(cXyz* p_pos, int i_itemNo, csXyz* p_angle, int roomNo, cXyz* scale = NULL,
                           createFunc createFunc = NULL);

fpc_ProcID fopAcM_createRaceItem(cXyz* p_pos, int i_itemNo, int i_itemBitNo, csXyz* p_angle, int roomNo,
                           cXyz* scale, int param_7);

fpc_ProcID fopAcM_createIball(cXyz* p_pos, int itemTableIdx, int roomNo, csXyz* p_angle, int itemStealNum);

fpc_ProcID fopAcM_createDemoItem(cXyz* p_pos, int itemNo, int itemBitNo, csXyz* p_angle,
                           int roomNo, cXyz* scale, u8 argFlag);

fpc_ProcID fopAcM_createItemForBoss(cXyz* p_pos, int unused, int roomNo, csXyz* p_angle,
                              cXyz* p_scale, int param_8);

daItem_c* fopAcM_createItemForSimpleDemo(cXyz* p_pos, int i_itemNo, int i_roomNo,
                                         csXyz* p_angle, cXyz* p_scale, f32 speedF, f32 speedY);

fpc_ProcID fopAcM_createItem(cXyz* p_pos, int itemNo, int itemBitNo, int roomNo, int type, csXyz* p_angle,
                       int action, cXyz* p_scale = NULL);

void* fopAcM_fastCreateItem2(cXyz* p_pos, int itemNo, int itemBitNo, int roomNo, int type,
                             csXyz* p_angle, int action, cXyz* p_scale = NULL);

void* fopAcM_fastCreateItem(cXyz* p_pos, int i_itemNo, int i_roomNo, csXyz* p_angle,
                            cXyz* p_scale, f32 speedF, f32 speedY, f32 gravity,
                            int i_itemBitNo = -1, createFunc p_createFunc = NULL);

void* fopAcM_createStealItem(cXyz* p_pos, int i_tblNo, int i_roomNo, csXyz* p_angle, int i_itemBitNo);

BOOL stealItem_CB(void* actor);

fopAc_ac_c* fopAcM_myRoomSearchEnemy(s8 roomNo);

fpc_ProcID fopAcM_createDisappear(fopAc_ac_c* i_actor, cXyz* p_pos, u8 i_scale, u8 i_dropType, u8 i_itemBitNo = -1);
void fopAcM_setCarryNow(fopAc_ac_c* i_this, BOOL stageLayer);
void fopAcM_cancelCarryNow(fopAc_ac_c* i_this);
s32 fopAcM_otoCheck(fopAc_ac_c*, f32);
BOOL fopAcM_viewCutoffCheck(fopAc_ac_c* actor, f32 param_2);
BOOL fopAcM_getGroundAngle(fopAc_ac_c* actor, csXyz* p_angle);

static const char* fopAcM_getProcNameString(fopAc_ac_c* p_actor);

static fopAc_ac_c* fopAcM_findObjectCB(fopAc_ac_c* p_actor, void* p_data);

fopAc_ac_c* fopAcM_searchFromName(char* name, u32 paramMask, u32 parameter);

fopAc_ac_c* fopAcM_findObject4EventCB(fopAc_ac_c* p_actor, void* p_data);

fopAc_ac_c* fopAcM_searchFromName4Event(char* name, s16 eventID);

BOOL fopAcM_getWaterY(const cXyz*, f32*);
void fpoAcM_relativePos(fopAc_ac_c* actor, cXyz* p_inPos, cXyz* p_outPos);

void fopAcM_setGbaName(fopAc_ac_c* i_this, u8 itemNo, u8 gbaName0, u8 gbaName1);

inline fopAc_ac_c* dComIfGp_getPlayer(int);

inline s16 fopAcM_searchPlayerAngleY(fopAc_ac_c* actor) {
    return fopAcM_searchActorAngleY(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline s32 fopAcM_seenPlayerAngleY(fopAc_ac_c* actor) {
    return fopAcM_seenActorAngleY(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistanceY(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistanceY(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistanceXZ2(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistanceXZ2(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistanceXZ(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistanceXZ(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistance(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistance(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistance2(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistance2(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

s8 dComIfGp_getReverb(int roomNo);

inline void fopAcM_seStartCurrent(fopAc_ac_c* actor, u32 i_seNum, u32 param_2) {
    mDoAud_seStart(i_seNum, &actor->current.pos, param_2, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

inline void fopAcM_seStart(fopAc_ac_c* actor, u32 i_seNum, u32 param_2) {
    mDoAud_seStart(i_seNum, &actor->eyePos, param_2, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

inline void fopAcM_monsSeStart(fopAc_ac_c* actor, u32 i_seNum, u32 param_2) {
    mDoAud_monsSeStart(i_seNum, &actor->eyePos, fopAcM_GetID(actor), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

inline void fopAcM_monsSeStart(fopAc_ac_c* actor, u32 i_seNum, Vec* i_sePos, u32 param_2) {
    mDoAud_monsSeStart(i_seNum, i_sePos, fopAcM_GetID(actor), param_2);
}

void fopDwTg_ToDrawQ(create_tag_class*, int);
void fopDwTg_DrawQTo(create_tag_class*);

inline void fopAcM_onDraw(fopAc_ac_c* actor) {
    fopDwTg_ToDrawQ(&actor->draw_tag, fpcLf_GetPriority(actor));
}

inline void fopAcM_offDraw(fopAc_ac_c* actor) {
    fopDwTg_DrawQTo(&actor->draw_tag);
}

inline void fopAcM_orderOtherEvent(fopAc_ac_c* ac, char* event, u16 hind = -1) {
    fopAcM_orderOtherEvent2(ac, event, dEvtFlag_NOPARTNER_e, hind);
}

#endif
