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
class J2DPicture;

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

class fopMsgM_msgDataProc_c {
public:
    fopMsgM_msgDataProc_c();
    virtual ~fopMsgM_msgDataProc_c();
    void dataInit();
    void charLength(int, int, bool);
    void rubyLength(int, bool);
    void stringLength();
    void stringShift();
    void iconSelect(int, u8);
    void iconIdxRefresh();
    void selectCheck2(J2DPane*, int, int, int);
    void selectCheck3(J2DPane*, int, int, int);
    void selectCheckYoko(J2DPane*, int, int, int);
    void inputNumber(int);
    void selectArrow(J2DPicture*, f32, f32, f32, f32);
    void selectArrow(J2DPicture*, f32, f32);
    void colorAnime(J2DPicture*);
    void stringSet();
    void setSelectFlagYokoOn();
    void setSelectFlagOn();
    void setHandSendFlagOn();
    void setAutoSendFlagOn();
    void getHandSendFlag();
    void getAutoSendFlag();
    void getString(char*, u32);
    void getString(char*, char*, char*, char*, u32, f32*, f32*, int*);
    void getRubyString(char*, char*, char*, char*, char*, char*, f32*, f32*, int*);
    void tag_len_kaisen_game(int*, f32*, int*, int*, int*);
    void tag_len_rupee(int*, f32*, int*, int*, int*);
    void tag_len_num_input(int*, f32*, int*, int*, int*);
    void tag_len_sword_game(int*, f32*, int*, int*, int*);
    void tag_len_letter_game(int*, f32*, int*, int*, int*);
    void tag_len_letter_game_max(int*, f32*, int*, int*, int*);
    void tag_len_fish(int*, f32*, int*, int*, int*);
    void tag_len_fish_rupee(int*, f32*, int*, int*, int*);
    void tag_len_letter(int*, f32*, int*, int*, int*);
    void tag_len_rescue(int*, f32*, int*, int*, int*);
    void tag_len_forest_timer(int*, f32*, int*, int*, int*);
    void tag_len_birdman(int*, f32*, int*, int*, int*);
    void tag_len_point(int*, f32*, int*, int*, int*);
    void tag_len_get_pendant(int*, f32*, int*, int*, int*);
    void tag_len_rev_pendant(int*, f32*, int*, int*, int*);
    void tag_len_pig_timer(int*, f32*, int*, int*, int*);
    void tag_len_get_bomb(int*, f32*, int*, int*, int*);
    void tag_len_get_arrow(int*, f32*, int*, int*, int*);
    void tag_len_stock_bokobaba(int*, f32*, int*, int*, int*);
    void tag_len_stock_dokuro(int*, f32*, int*, int*, int*);
    void tag_len_stock_chuchu(int*, f32*, int*, int*, int*);
    void tag_len_stock_pendant(int*, f32*, int*, int*, int*);
    void tag_len_stock_hane(int*, f32*, int*, int*, int*);
    void tag_len_stock_kenshi(int*, f32*, int*, int*, int*);
    void tag_len_terry_rupee(int*, f32*, int*, int*, int*);
    void tag_len_input_bokobaba(int*, f32*, int*, int*, int*);
    void tag_len_input_dokuro(int*, f32*, int*, int*, int*);
    void tag_len_input_chuchu(int*, f32*, int*, int*, int*);
    void tag_len_input_pendant(int*, f32*, int*, int*, int*);
    void tag_len_input_hane(int*, f32*, int*, int*, int*);
    void tag_len_input_kenshi(int*, f32*, int*, int*, int*);
    void tag_kaisen_game();
    void tag_rupee();
    void tag_num_input();
    void tag_sword_game();
    void tag_letter_game();
    void tag_letter_game_max();
    void tag_fish();
    void tag_fish_rupee();
    void tag_letter();
    void tag_rescue();
    void tag_forest_timer();
    void tag_birdman();
    void tag_point();
    void tag_get_pendant();
    void tag_rev_pendant();
    void tag_pig_timer();
    void tag_get_bomb();
    void tag_get_arrow();
    void tag_stock_bokobaba();
    void tag_stock_dokuro();
    void tag_stock_chuchu();
    void tag_stock_pendant();
    void tag_stock_hane();
    void tag_stock_kenshi();
    void tag_terry_rupee();
    void tag_input_bokobaba();
    void tag_input_dokuro();
    void tag_input_chuchu();
    void tag_input_pendant();
    void tag_input_hane();
    void tag_input_kenshi();

public:
    /* 0x000 */ u8 field_0x00[0x29C];
};

typedef int (*fopMsgCreateFunc)(void*);

JKRExpHeap* fopMsgM_createExpHeap(u32, JKRHeap*);
JKRExpHeap* fopMsgM_createExpHeap(u32);
fpc_ProcID fopMsgM_Create(s16, fopMsgCreateFunc, void*);
fpc_ProcID fopMsgM_create(s16 i_procName, fopAc_ac_c* param_1 = NULL, cXyz* param_2 = NULL,
                          u32* param_3 = NULL, u32* param_4 = NULL, fopMsgCreateFunc createFunc = NULL);
void fopMsgM_Delete(void* process);
fopMsg_prm_class* fopMsgM_GetAppend(void* msg);
void fopMsgM_destroyExpHeap(JKRExpHeap*);
f32 fopMsgM_valueIncrease(int param_0, int param_1, u8 param_2);
s32 fopMsgM_setStageLayer(void*);
fpc_ProcID fopMsgM_messageSet(u32 i_msgNo, fopAc_ac_c* i_actorP);
fpc_ProcID fopMsgM_messageSet(u32 param_0, cXyz*);
fpc_ProcID fopMsgM_messageSet(u32 param_0);
fpc_ProcID fopMsgM_scopeMessageSet(u32 param_0);
int fopMsgM_messageSetDemo(u32 param_0);
msg_class* fopMsgM_SearchByID(fpc_ProcID param_0);
char* fopMsgM_messageGet(char* msg, u32 string_id);
void fopMsgM_passwordGet(char*, u32);
fpc_ProcID fop_Timer_create(s16 param_0, u8 param_1, u16 param_2, u8 param_3, u8 param_4, f32 param_5,
                     f32 param_6, f32 param_7, f32 param_8, fopMsgCreateFunc createFunc);
inline fpc_ProcID fopMsgM_Timer_create(s16 param_0, u8 param_1, u32 param_2, u8 param_3, u8 param_4,
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
