#ifndef F_F_OP_MSG_MNG_H_
#define F_F_OP_MSG_MNG_H_

#include "SSystem/SComponent/c_xyz.h"
#include "f_pc/f_pc_leaf.h"
#include "f_op/f_op_msg.h"

class JKRExpHeap;
class JKRHeap;
class fopAc_ac_c;
class msg_class;
class J2DPane;
class J2DScreen;

struct msg_process_profile_definition {
    /* 0x00 */ leaf_process_profile_definition base;
    /* 0x24 */ msg_method_class* sub_method;  // Subclass methods
};

struct fopMsg_prm_class {
    /* 0x00 */ fopAc_ac_c* mpActor;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ u32 mMsgNo;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ int field_0x18;
};  // Size: 0x1C

struct fopMsg_prm_timer : public fopMsg_prm_class {
    /* 0x1C */ int mTimerMode;
    /* 0x20 */ u16 mLimitTimeMs;
    /* 0x22 */ u8 mShowType;
    /* 0x23 */ u8 mIconType;
    /* 0x24 */ cXy mTimerPos;
    /* 0x2C */ cXy mRupeePos;
};  // Size: 0x34

class J2DScreen;

struct fopMsgM_pane_class {
    /* 0x00 */ J2DPane * pane;
    /* 0x04 */ cXy mPosTopLeftOrig;
    /* 0x0C */ cXy mPosTopLeft;
    /* 0x14 */ cXy mPosCenterOrig;
    /* 0x1C */ cXy mPosCenter;
    /* 0x24 */ cXy mSizeOrig;
    /* 0x2C */ cXy mSize;
    /* 0x34 */ u8 mInitAlpha;
    /* 0x35 */ u8 mNowAlpha;
    /* 0x36 */ s16 mUserArea;
};

struct fopMsgM_pane_alpha_class {
    /* 0x00 */ J2DPane * pane;
    /* 0x04 */ u8 mInitAlpha;
    /* 0x05 */ u8 mNowAlpha;
};

typedef int (*fopMsgCreateFunc)(void*);

JKRExpHeap* fopMsgM_createExpHeap(u32, JKRHeap*);
JKRExpHeap* fopMsgM_createExpHeap(u32);
u32 fopMsgM_Create(s16, fopMsgCreateFunc, void*);
s32 fopMsgM_create(s16 param_0, fopAc_ac_c* param_1, cXyz* param_2, u32* param_3, u32* param_4, fopMsgCreateFunc createFunc);
void fopMsgM_Delete(void* process);
fopMsg_prm_class* fopMsgM_GetAppend(void* msg);
void fopMsgM_setMessageID(uint);
void fopMsgM_destroyExpHeap(JKRExpHeap*);
f32 fopMsgM_valueIncrease(int param_0, int param_1, u8 param_2);
s32 fopMsgM_setStageLayer(void*);
uint fopMsgM_messageSet(u32 i_msgNo, fopAc_ac_c* i_actorP);
uint fopMsgM_messageSet(u32 param_0, cXyz*);
uint fopMsgM_messageSet(u32 param_0);
int fopMsgM_messageSetDemo(u32 param_0);
msg_class* fopMsgM_SearchByID(uint param_0);
char* fopMsgM_messageGet(char* msg, u32 string_id);
uint fop_Timer_create(s16 param_0, u8 param_1, u16 param_2, u8 param_3, u8 param_4, f32 param_5,
                     f32 param_6, f32 param_7, f32 param_8, fopMsgCreateFunc createFunc);
inline uint fopMsgM_Timer_create(s16 param_0, u8 param_1, u32 param_2, u8 param_3, u8 param_4,
                                f32 param_5, f32 param_6, f32 param_7, f32 param_8,
                                fopMsgCreateFunc createFunc) {
    return fop_Timer_create(param_0, param_1, param_2, param_3, param_4, param_5, param_6, param_7,
                            param_8, createFunc);
}

void fopMsgM_setPaneData(fopMsgM_pane_class*, J2DPane*);
void fopMsgM_setPaneData(fopMsgM_pane_class*, J2DScreen*, u32);
void fopMsgM_setInitAlpha(fopMsgM_pane_class*);
void fopMsgM_setNowAlpha(fopMsgM_pane_class*, f32);
void fopMsgM_setNowAlphaZero(fopMsgM_pane_class*);
void fopMsgM_setAlpha(fopMsgM_pane_class*);
void fopMsgM_paneScaleXY(fopMsgM_pane_class*, f32);
void fopMsgM_cposMove(fopMsgM_pane_class*);
void fopMsgM_paneTrans(fopMsgM_pane_class*, f32, f32);

void fopMsgM_setPaneData(fopMsgM_pane_alpha_class*, J2DPane*);
void fopMsgM_setPaneData(fopMsgM_pane_alpha_class*, J2DScreen*, u32);
void fopMsgM_setNowAlpha(fopMsgM_pane_alpha_class*, f32);
void fopMsgM_setAlpha(fopMsgM_pane_alpha_class*);

u32 fopMsgM_searchMessageNumber(u32);
void fopMsgM_messageSendOn();
u32 fopMsgM_tactMessageSet();
void fopMsgM_demoMsgFlagOn();

void fopMsgM_demoMsgFlagOn();
void fopMsgM_demoMsgFlagOff();
bool fopMsgM_demoMsgFlagCheck();

#endif
