#ifndef F_OP_MSG_MNG_H
#define F_OP_MSG_MNG_H

#include "JSystem/J2DGraph/J2DPicture.h"
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
class JUTFont;
struct mesg_header;
struct mesg_data;
struct mesg_info;

// BMG INF1 messageEntry
struct mesg_entry {
    // mesg_entry() {} // fixes fopMsgM_selectMessageGet, but messes up getMesgEntry

    /* 0x00 */ u32 mDataOffs;
    /* 0x04 */ u16 mMsgNo;
    /* 0x06 */ s16 mItemPrice;
    /* 0x08 */ u16 mNextMsgNo;
    /* 0x0A */ u16 field_0x0a;
    /* 0x0C */ u8 mTextboxType;
    /* 0x0D */ u8 mDrawType;
    /* 0x0E */ u8 mTextboxPosition;
    /* 0x0F */ u8 mItemImage;
    /* 0x10 */ u8 mTextAlignment;
    /* 0x11 */ u8 mInitialSound;
    /* 0x12 */ u8 mInitialCamera;
    /* 0x13 */ u8 mInitialAnimation;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
};

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

class fopMsgM_f2d_class {
public:
    f32 x;
    f32 y;
};

struct fopMsgM_pane_class {
    /* 0x00 */ J2DPane * pane;
    /* 0x04 */ fopMsgM_f2d_class mPosTopLeftOrig;
    /* 0x0C */ fopMsgM_f2d_class mPosTopLeft;
    /* 0x14 */ fopMsgM_f2d_class mPosCenterOrig;
    /* 0x1C */ fopMsgM_f2d_class mPosCenter;
    /* 0x24 */ fopMsgM_f2d_class mSizeOrig;
    /* 0x2C */ fopMsgM_f2d_class mSize;
    /* 0x34 */ u8 mInitAlpha;
    /* 0x35 */ u8 mNowAlpha;
    /* 0x36 */ s16 mUserArea;
};

struct fopMsgM_pane_alpha_class {
    /* 0x00 */ J2DPane * pane;
    /* 0x04 */ u8 mInitAlpha;
    /* 0x05 */ u8 mNowAlpha;
};

class fopMsgM_msgGet_c {
public:
    virtual ~fopMsgM_msgGet_c() {}
    mesg_header* getMesgHeader(u32);
    mesg_info* getMesgInfo(mesg_header*);
    mesg_data* getMesgData(mesg_header*);
    mesg_entry getMesgEntry(mesg_header*);
    const char* getMessage(mesg_header*);

public:
    /* 0x04 */ u32 mMsgIdx;
    /* 0x08 */ u16 mGroupID;
    /* 0x0A */ u16 mMsgNo;
    /* 0x0C */ u16 mResMsgNo;
};

class fopMsgM_itemMsgGet_c {
public:
    virtual ~fopMsgM_itemMsgGet_c() {}
    mesg_header* getMesgHeader(u32);
    mesg_info* getMesgInfo(mesg_header*);
    mesg_data* getMesgData(mesg_header*);
    mesg_entry getMesgEntry(mesg_header*);
    const char* getMessage(mesg_header*);

public:
    /* 0x04 */ u32 mMsgIdx;
    /* 0x08 */ u16 mMsgNo;
    /* 0x0A */ u16 mResMsgNo;
};

class MyPicture : public J2DPicture {
public:
    virtual ~MyPicture() {}
    virtual void drawSelf(f32, f32);
    virtual void drawSelf(f32, f32, Mtx*);
    virtual void drawFullSet2(f32, f32, f32, f32, J2DBinding, J2DMirror, bool, Mtx*);

private:
    /* 0x124 */ f32 m124;
    /* 0x128 */ f32 m128;
    /* 0x12C */ f32 m12C;
    /* 0x130 */ f32 m130;
    /* 0x134 */ u8 m134;
};

class fopMsgM_msgDataProc_c {
public:
    fopMsgM_msgDataProc_c();
    virtual ~fopMsgM_msgDataProc_c() {}
    void dataInit();
    f32 charLength(int, int, bool);
    f32 rubyLength(int, bool);
    void stringLength();
    void stringShift();
    void iconSelect(int, u8);
    void iconIdxRefresh();
    int selectCheck2(J2DPane*, int, int, int);
    int selectCheck3(J2DPane*, int, int, int);
    int selectCheckYoko(J2DPane*, int, int, int);
    int inputNumber(int);
    void selectArrow(J2DPicture*, f32, f32, f32, f32);
    void selectArrow(J2DPicture*, f32, f32);
    void colorAnime(J2DPicture*);
    void stringSet();
    void setSelectFlagYokoOn();
    void setSelectFlagOn();
    void setHandSendFlagOn();
    void setAutoSendFlagOn();
    u8 getHandSendFlag();
    u8 getAutoSendFlag();
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
    /* 0x004 */ JUTFont* font[2];
    /* 0x00C */ mesg_entry* field_0x0C;
    /* 0x010 */ u32 field_0x10;
    /* 0x014 */ f32 field_0x14;
    /* 0x018 */ f32 field_0x18;
    /* 0x01C */ f32 field_0x1C;
    /* 0x020 */ f32 field_0x20;
    /* 0x024 */ f32 field_0x24;
    /* 0x028 */ f32 field_0x28;
    /* 0x02C */ u32 field_0x2C;
    /* 0x030 */ u32 field_0x30;
    /* 0x034 */ u32 field_0x34;
    /* 0x038 */ u32 field_0x38;
    /* 0x03C */ char* field_0x3C;
    /* 0x040 */ char* field_0x40;
    /* 0x044 */ char* field_0x44;
    /* 0x048 */ char* field_0x48;
    /* 0x04C */ char* field_0x4C;
    /* 0x050 */ char* field_0x50[4];
    /* 0x060 */ char* field_0x60;
    /* 0x064 */ char* field_0x64;
    /* 0x068 */ char* field_0x68;
    /* 0x06C */ char* field_0x6C;
    /* 0x070 */ char field_0x70[0x64]; // no idea how big this array is
    /* 0x0D4 */ char field_0xD4[4];
    /* 0x0D4 */ s32 field_0xD8[4];
    /* 0x0D4 */ s32 field_0xE8[4];
    /* 0x0F8 */ s32 field_0xF8[4];
    /* 0x108 */ s32 field_0x108[4];
    /* 0x118 */ u32 field_0x118;
    /* 0x11C */ s32 field_0x11C;
    /* 0x120 */ s32 field_0x120;
    /* 0x124 */ s32 field_0x124;
    /* 0x128 */ s32 field_0x128;
    /* 0x12C */ u32 field_0x12C;
    /* 0x130 */ s32 field_0x130;
    /* 0x134 */ u32 field_0x134;
    /* 0x138 */ u32 field_0x138;
    /* 0x13C */ u32 field_0x13C;
    /* 0x140 */ u32 field_0x140;
    /* 0x144 */ s32 field_0x144;
    /* 0x148 */ u32 field_0x148;
    /* 0x14C */ s32 field_0x14C;
    /* 0x150 */ int field_0x150;
    /* 0x154 */ u32 field_0x154;
    /* 0x158 */ u32 field_0x158;
    /* 0x15C */ u32 field_0x15C;
    /* 0x160 */ u32 field_0x160;
    /* 0x164 */ int field_0x164;
    /* 0x168 */ s32 field_0x168[0xF];
    /* 0x1A4 */ u32 field_0x1A4[0xF];
    /* 0x1A4 */ u32 field_0x1E0[0xF];
    /* 0x21C */ u32 field_0x21C;
    /* 0x21C */ u32 field_0x220[0xF];
    /* 0x25C */ u32 field_0x25C;
    /* 0x260 */ s16 field_0x260;
    /* 0x264 */ f32 field_0x264;
    /* 0x268 */ f32 field_0x268;
    /* 0x26C */ f32 field_0x26C;
    /* 0x270 */ f32 field_0x270;
    /* 0x274 */ f32 field_0x274;
    /* 0x278 */ f32 field_0x278;
    /* 0x27C */ u8 field_0x27C;
    /* 0x27D */ u8 field_0x27D;
    /* 0x27E */ u8 field_0x27E;
    /* 0x27F */ u8 field_0x27F;
    /* 0x280 */ u8 field_0x280;
    /* 0x281 */ u8 field_0x281[0xF];
    /* 0x290 */ u8 field_0x290;
    /* 0x291 */ u8 field_0x291;
    /* 0x292 */ u8 field_0x292;
    /* 0x293 */ u8 field_0x293;
    /* 0x294 */ u8 field_0x294;
    /* 0x295 */ u8 field_0x295;
    /* 0x296 */ u8 field_0x296;
    /* 0x297 */ u8 field_0x297;
    /* 0x298 */ u8 field_0x298;
    /* 0x299 */ u8 field_0x299;
    /* 0x29A */ u8 field_0x29A;
    /* 0x29B */ u8 field_0x29B;
    /* 0x29C */ u8 field_0x29C;
    /* 0x29D */ u8 field_0x29D;
};

typedef int (*fopMsgCreateFunc)(void*);

JKRExpHeap* fopMsgM_createExpHeap(u32, JKRHeap*);
JKRExpHeap* fopMsgM_createExpHeap(u32);
fpc_ProcID fopMsgM_Create(s16, fopMsgCreateFunc, void*);
fpc_ProcID fopMsgM_create(s16 i_procName, fopAc_ac_c* param_1 = NULL, cXyz* param_2 = NULL,
                          u32* param_3 = NULL, u32* param_4 = NULL, fopMsgCreateFunc createFunc = NULL);
fpc_ProcID fop_MGameTerm_create(s16, s16, s16, int, int, fopMsgCreateFunc);
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
void fopMsgM_tactMsgFlagOn();
void fopMsgM_tactMsgFlagOff();
bool fopMsgM_tactMsgFlagCheck();

void fopMsgM_blendInit(fopMsgM_pane_class* i_this, const char* data);
void fopMsgM_blendInit(J2DPicture* pic, const char* data);
u32 fopMsgM_getColorTable(u16 param_1);
void fopMsgM_blendDraw(fopMsgM_pane_class* i_this, const char* data);
void fopMsgM_blendDraw(J2DPicture* pic, const char* data);
void fopMsgM_setFontsizeCenter(char* param_1, char* param_2, char* param_3, char* param_4, int param_5, int param_6);
void fopMsgM_setFontsizeCenter2(char* a, char* b, char* c, char* d, int, int size, int, int);

void fopMsgM_outFontSet(J2DPicture*, J2DPicture*, s16*, u32, u8);
void fopMsgM_outFontSet(J2DPicture*, s16*, u32, u8);
void fopMsgM_outFontDraw(J2DPicture*, J2DPicture*, int, int, int, s16*, u8, u8);
void fopMsgM_outFontDraw2(J2DPicture*, J2DPicture*, int, int, int, int, s16*, u8, u8);

extern u16 zfont[][2];

#endif /* F_OP_MSG_MNG_H */
