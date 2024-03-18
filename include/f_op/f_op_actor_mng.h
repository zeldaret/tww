#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "new.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_iter.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_searcher.h"
#include "m_Do/m_Do_audio.h"
#include "d/d_item_data.h"
#include "d/d_save.h"

#define fopAcM_SetupActor(ptr,ClassName) \
    if (!fopAcM_CheckCondition(ptr, fopAcCnd_INIT_e)) { \
        new (ptr) ClassName(); \
        fopAcM_OnCondition(ptr, fopAcCnd_INIT_e); \
    }

class J3DModelData;
class daItem_c;

struct fopAcM_prmBase_class {
    /* 0x00 */ u32 field_0x00;
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ csXyz field_0x10;
    /* 0x16 */ u16 field_0x16;
};  // Size = 0x18

struct fopAcM_prmScale_class {
    u8 x;
    u8 y;
    u8 z;
};

struct fopAcM_prm_class {
    /* 0x00 */ u32 mParameter;  // single U32 Parameter
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ csXyz mAngle;  // rotation
    /* 0x16 */ u16 mSetId;
    /* 0x18 */ fopAcM_prmScale_class mScale;
    /* 0x1B */ u8 mGbaName;
    /* 0x1C */ uint mParentPcId;  // parent process ID
    /* 0x20 */ s8 mSubtype;
    /* 0x21 */ s8 mRoomNo;
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
    /* 0x00 */ const char * mpProcName;
    /* 0x04 */ u32 mParamMask;
    /* 0x08 */ u32 mParameter;
};

class l_HIO {
public:
    ~l_HIO() {}

    void entry() {}
    void erase() {}
};

class dKy_tevstr_c;
typedef int (*heapCallbackFunc)(fopAc_ac_c*);
typedef int (*createFunc)(void*);

inline s8 fopAcM_GetRoomNo(fopAc_ac_c* pActor) {
    return pActor->current.roomNo;
}

inline uint fopAcM_GetID(void* pActor) {
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

inline bool fopAcM_CheckCondition(fopAc_ac_c* p_actor, u32 flag) {
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

inline BOOL fopAcM_IsExecuting(uint id) {
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

inline fopAc_ac_c* fopAcM_SearchByID(uint id) {
    return (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &id);
}

inline fopAc_ac_c* fopAcM_SearchByName(s16 procName) {
    return (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeForPName, &procName);
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
    if (itemNo == BLUE_JELLY) {
        // Blue Chu Jelly uses itemBitNo as if it was a switch in stageNo 0xE.
        return dComIfGs_isSaveSwitch(dSv_save_c::STAGE_BLUE_CHU_JELLY, itemBitNo);
    } else {
        return dComIfGs_isItem(itemBitNo, roomNo);
    }
}

inline void dComIfGs_onSaveSwitch(int i_stageNo, int i_no);
inline void fopAcM_onItemForIb(int itemBitNo, u8 itemNo, s8 roomNo) {
    if (itemNo == BLUE_JELLY) {
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

s32 fopAcM_SearchByID(uint id, fopAc_ac_c** p_actor);

s32 fopAcM_SearchByName(s16 procName, fopAc_ac_c** p_actor);

fopAcM_prm_class* fopAcM_CreateAppend();

fopAcM_prm_class* createAppend(u16 enemyNo, u32 parameters, cXyz* p_pos, int roomNo,
                               csXyz* p_angle, cXyz* p_scale, s8 subType,
                               uint parentPId);

void fopAcM_Log(fopAc_ac_c* p_actor, char* str);

s32 fopAcM_delete(fopAc_ac_c* p_actor);
s32 fopAcM_delete(uint actorID);

uint fopAcM_create(s16 i_procName, u32 i_parameter, cXyz* i_pos = NULL, int i_roomNo = -1,
                   csXyz* i_angle = NULL, cXyz* i_scale = NULL, s8 i_subType = -1,
                   createFunc i_createFunc = NULL);

uint fopAcM_create(char*, u32 i_parameter, cXyz* i_pos = NULL, int i_roomNo = -1,
                   csXyz* i_angle = NULL, cXyz* i_scale = NULL,
                   createFunc i_createFunc = NULL);

inline s32 fopAcM_create(s16 i_procName, createFunc i_createFunc, void*);

void* fopAcM_fastCreate(s16 procName, u32 parameter, cXyz* p_pos = NULL, int roomNo = -1,
                        csXyz* p_angle = NULL, cXyz* p_scale = NULL, s8 subType = -1,
                        createFunc p_createFunc = NULL, void* p_createFuncData = NULL);

void* fopAcM_fastCreate(char* p_actorName, u32 parameter, cXyz* pActorPos = NULL, int roomNo = -1,
                        csXyz* p_angle = NULL, cXyz* p_scale = NULL,
                        createFunc p_createFunc = NULL, void* p_createFuncData = NULL);

uint fopAcM_createChild(s16 procName, uint parentPId, u32 parameters, cXyz* p_pos,
                        int roomNo, csXyz* p_angle, cXyz* p_scale = NULL, s8 subType = -1,
                        createFunc p_createFunc = NULL);

uint fopAcM_createChild(char* pProcNameString, uint parentPcId, u32 parameter, cXyz* pPos,
                        int roomNo, csXyz* pAngle, cXyz* pScale, createFunc createFunc);

uint fopAcM_createChildFromOffset(s16 procName, uint parentProcID, u32 actorParams,
                                  cXyz* p_pos, int roomNo, csXyz* p_angle,
                                  cXyz* p_scale, s8 subType, createFunc p_createFunc);
uint fopAcM_createChildFromOffset(char* pProcNameString, uint parentPcId, u32 parameter,
                                  cXyz* pPosOffs, int roomNo, csXyz* pAngleOffs, cXyz* pScale,
                                  createFunc createFunc);

void fopAcM_DeleteHeap(fopAc_ac_c* p_actor);

bool fopAcM_entrySolidHeap(fopAc_ac_c* p_actor, heapCallbackFunc p_heapCallback, u32 size);

inline void fopAcM_SetMin(fopAc_ac_c* p_actor, f32 minX, f32 minY, f32 minZ) {
#ifndef __INTELLISENSE__
    p_actor->cull.box.min.set(minX, minY, minZ);
#endif
}

inline void fopAcM_SetMax(fopAc_ac_c* p_actor, f32 maxX, f32 maxY, f32 maxZ) {
#ifndef __INTELLISENSE__
    p_actor->cull.box.max.set(maxX, maxY, maxZ);
#endif
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
s32 fopAcM_orderSpeakEvent(fopAc_ac_c* i_actor);
s32 fopAcM_orderDoorEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderCatchEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderOtherEvent2(fopAc_ac_c* i_this, char* pEventName, u16 flag, u16 hind = -1);
s32 fopAcM_orderChangeEventId(fopAc_ac_c* i_this, s16 eventIdx, u16 flag, u16 hind);
s32 fopAcM_orderChangeEventId(fopAc_ac_c* i_this, fopAc_ac_c* i_partner, s16 eventIdx, u16 flag, u16 hind);
s32 fopAcM_orderOtherEventId(fopAc_ac_c* actor, s16 eventIdx, u8 mapToolID = -1, u16 hind = -1,
                             u16 priority = 0, u16 flag = 1);
s32 fopAcM_orderPotentialEvent(fopAc_ac_c*, u16, u16, u16);
s32 fopAcM_orderItemEvent(fopAc_ac_c*);
s32 fopAcM_orderTreasureEvent(fopAc_ac_c*, fopAc_ac_c*);
fopAc_ac_c* fopAcM_getTalkEventPartner(fopAc_ac_c*);
fopAc_ac_c* fopAcM_getItemEventPartner(fopAc_ac_c*);
fopAc_ac_c* fopAcM_getEventPartner(fopAc_ac_c*);

uint fopAcM_createItemForPresentDemo(cXyz* p_pos, int i_itemNo, u8 argFlag = 0x00, int i_itemBitNo = -1,
                                     int i_roomNo = -1, csXyz* p_angle = NULL, cXyz* p_scale = NULL);

uint fopAcM_createItemForTrBoxDemo(cXyz* p_pos, int i_itemNo, int i_itemBitNo = -1,
                                   int i_roomNo = -1, csXyz* p_angle = NULL, cXyz* p_scale = NULL);

uint fopAcM_createItemFromTable(cXyz* p_pos, int i_tableNo, int i_itemBitNo, int i_roomNo, int,
                                csXyz* p_angle, int, cXyz* p_scale = NULL);

uint fopAcM_createRaceItemFromTable(cXyz* pos, int i_itemNo, int i_itemBitNo, int i_roomNo,
                                    csXyz* angle, cXyz* scale, int param_7);

uint fopAcM_createShopItem(cXyz* p_pos, int i_itemNo, csXyz* p_angle, int roomNo, cXyz* scale = NULL,
                           createFunc createFunc = NULL);

uint fopAcM_createRaceItem(cXyz* p_pos, int i_itemNo, int i_itemBitNo, csXyz* p_angle, int roomNo,
                           cXyz* scale, int param_7);

uint fopAcM_createIball(cXyz* p_pos, int itemTableIdx, int roomNo, csXyz* p_angle, int itemStealNum);

uint fopAcM_createDemoItem(cXyz* p_pos, int itemNo, int itemBitNo, csXyz* p_angle,
                           int roomNo, cXyz* scale, u8 argFlag);

uint fopAcM_createItemForBoss(cXyz* p_pos, int param_2, int roomNo, csXyz* p_angle,
                              cXyz* p_scale = NULL, int param_8 = 0);

daItem_c* fopAcM_createItemForSimpleDemo(cXyz* p_pos, int i_itemNo, int i_roomNo,
                                         csXyz* p_angle, cXyz* p_scale, f32 speedF, f32 speedY);

uint fopAcM_createItem(cXyz* p_pos, int itemNo, int param_3, int roomNo, int type, csXyz* p_angle,
                       int action, cXyz* p_scale = NULL);

void* fopAcM_fastCreateItem2(cXyz* p_pos, int itemNo, int param_3, int roomNo, int param_5,
                             csXyz* p_angle, int, cXyz* p_scale = NULL);

void* fopAcM_fastCreateItem(cXyz* p_pos, int i_itemNo, int i_roomNo, csXyz* p_angle,
                            cXyz* p_scale, f32 p_speedF, f32 p_speedY, f32 param_8,
                            int param_9 = -1, createFunc p_createFunc = NULL);

void* fopAcM_createStealItem(cXyz* p_pos, int i_tblNo, int i_roomNo, csXyz* p_angle, int i_itemBitNo);

BOOL stealItem_CB(void* actor);

fopAc_ac_c* fopAcM_myRoomSearchEnemy(s8 roomNo);

uint fopAcM_createDisappear(fopAc_ac_c* i_actor, cXyz* p_pos, u8 i_scale, u8 i_health = 0, u8 i_itemBitNo = -1);
void fopAcM_setCarryNow(fopAc_ac_c* i_this, BOOL stageLayer);
void fopAcM_cancelCarryNow(fopAc_ac_c* i_this);
s32 fopAcM_otoCheck(fopAc_ac_c*, f32);
BOOL fopAcM_viewCutoffCheck(fopAc_ac_c* actor, f32 param_2);
BOOL fopAcM_getGroundAngle(fopAc_ac_c* actor, csXyz* p_angle);

static const char* fopAcM_getProcNameString(fopAc_ac_c* p_actor);

static fopAc_ac_c* fopAcM_findObjectCB(fopAc_ac_c* p_actor, void* p_data);

fopAc_ac_c* fopAcM_searchFromName(char* name, u32 param0, u32 param1);

fopAc_ac_c* fopAcM_findObject4EventCB(fopAc_ac_c* p_actor, void* p_data);

fopAc_ac_c* fopAcM_searchFromName4Event(char* name, s16 eventID);

s32 fopAcM_getWaterY(const cXyz*, f32*);
void fpoAcM_relativePos(fopAc_ac_c* actor, cXyz* p_inPos, cXyz* p_outPos);

void fopAcM_setGbaName(fopAc_ac_c* i_this, u8 itemNo, u8 gbaName0, u8 gbaName1);

inline fopAc_ac_c* dComIfGp_getPlayer(int);

inline s16 fopAcM_searchPlayerAngleY(fopAc_ac_c* actor) {
    return fopAcM_searchActorAngleY(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
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

inline void fopAcM_orderOtherEvent(fopAc_ac_c* ac, char* event, u16 flag) {
    fopAcM_orderOtherEvent2(ac, event, flag);
}

#endif
