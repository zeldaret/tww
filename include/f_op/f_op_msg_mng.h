#ifndef F_OP_MSG_MNG_H
#define F_OP_MSG_MNG_H

#include "JSystem/J2DGraph/J2DPicture.h"
#include "SSystem/SComponent/c_xyz.h"
#include "f_pc/f_pc_leaf.h"
#include "f_op/f_op_msg.h"

class JKRExpHeap;
class JKRHeap;
class fopAc_ac_c;
struct msg_class;
class J2DPane;
class J2DScreen;
class J2DPicture;
class JUTFont;
struct mesg_header;
struct mesg_data;
struct mesg_info;

// BMG INF1 messageEntry
struct JMSMesgEntry_c {
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
    /* 0x24 */ msg_method_class* sub_method; // Subclass methods
};

struct fopMsg_prm_class {
    /* 0x00 */ fopAc_ac_c* mpActor;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ u32 mMsgNo;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ int field_0x18;
}; // Size: 0x1C

struct fopMsg_prm_timer : public fopMsg_prm_class {
    /* 0x1C */ int mTimerMode;
    /* 0x20 */ u16 mLimitTimeMs;
    /* 0x22 */ u8 mShowType;
    /* 0x23 */ u8 mIconType;
    /* 0x24 */ cXy mTimerPos;
    /* 0x2C */ cXy mRupeePos;
}; // Size: 0x34

struct fopMsgM_unk_struct {
    u16 _0;
    u16 _2;
    u16 _4;
    u16 _6;
    u16 _8;
    u16 _A;
    s16 _C;
    u16 _E;
    u8 _10;
};

class J2DScreen;

class fopMsgM_f2d_class {
public:
    f32 x;
    f32 y;
};

struct fopMsgM_pane_class {
    /* 0x00 */ J2DPane* pane;
    /* 0x04 */ fopMsgM_f2d_class mPosTopLeftOrig;
    /* 0x0C */ fopMsgM_f2d_class mPosTopLeft;
    /* 0x14 */ fopMsgM_f2d_class mPosCenterOrig;
    /* 0x1C */ fopMsgM_f2d_class mPosCenter;
    /* 0x24 */ fopMsgM_f2d_class mSizeOrig;
    /* 0x2C */ fopMsgM_f2d_class mSize;
    /* 0x34 */ u8 mInitAlpha;
    /* 0x35 */ u8 mNowAlpha;
    /* 0x36 */ s16 mUserArea;
}; // Size: 0x38

struct fopMsgM_pane_alpha_class {
    /* 0x00 */ J2DPane* pane;
    /* 0x04 */ u8 mInitAlpha;
    /* 0x05 */ u8 mNowAlpha;
};

class fopMsgM_msgGet_c {
public:
    virtual ~fopMsgM_msgGet_c() {}
    mesg_header* getMesgHeader(u32 i_msgNo);
    mesg_info* getMesgInfo(mesg_header* i_head);
    mesg_data* getMesgData(mesg_header* i_head);
    JMSMesgEntry_c getMesgEntry(mesg_header* i_head);
    const char* getMessage(mesg_header* i_head);

    u32 getMesgNumber() { return (mGroupID << 8) | mResMsgNo; }

public:
    /* 0x04 */ u32 mMsgIdx;
    /* 0x08 */ u16 mGroupID;
    /* 0x0A */ u16 mMsgNo;
    /* 0x0C */ u16 mResMsgNo;
};

class fopMsgM_itemMsgGet_c {
public:
    fopMsgM_itemMsgGet_c() {
        mMsgIdx = 0;
        mMsgNo = 0;
        mResMsgNo = 0;
    }
    virtual ~fopMsgM_itemMsgGet_c() {}
    mesg_header* getMesgHeader(u32 i_msgNo);
    mesg_info* getMesgInfo(mesg_header* i_head);
    mesg_data* getMesgData(mesg_header* i_head);
    JMSMesgEntry_c getMesgEntry(mesg_header* i_head);
    const char* getMessage(mesg_header* i_head);

public:
    /* 0x04 */ u32 mMsgIdx;
    /* 0x08 */ u16 mMsgNo;
    /* 0x0A */ u16 mResMsgNo;
};

class MyPicture : public J2DPicture {
public:
    MyPicture(J2DPane* pParent, JSURandomInputStream* pStream)
        : J2DPicture(pParent, pStream) {
        m134 = 0;
    }

    virtual ~MyPicture() {}
    virtual void drawSelf(f32, f32);
    virtual void drawSelf(f32, f32, Mtx*);
    virtual void drawFullSet2(f32, f32, f32, f32, J2DBinding, J2DMirror, bool, Mtx*);

public:
    /* 0x124 */ f32 m124;
    /* 0x128 */ f32 m128;
    /* 0x12C */ f32 m12C;
    /* 0x130 */ f32 m130;
    /* 0x134 */ u8 m134;
};

enum {
    /* 0x00 */ fopMsgM_Icon_A_BUTTON_e,
    /* 0x01 */ fopMsgM_Icon_B_BUTTON_e,
    /* 0x02 */ fopMsgM_Icon_C_STICK_e,
    /* 0x03 */ fopMsgM_Icon_L_BUTTON_e,
    /* 0x04 */ fopMsgM_Icon_R_BUTTON_e,
    /* 0x05 */ fopMsgM_Icon_X_BUTTON_e,
    /* 0x06 */ fopMsgM_Icon_Y_BUTTON_e,
    /* 0x07 */ fopMsgM_Icon_Z_BUTTON_e,
    /* 0x08 */ fopMsgM_Icon_DPAD_e,
    /* 0x09 */ fopMsgM_Icon_MAIN_STICK_e,
    /* 0x0A */ fopMsgM_Icon_ARROW_LEFT_e,
    /* 0x0B */ fopMsgM_Icon_ARROW_RIGHT_e,
    /* 0x0C */ fopMsgM_Icon_ARROW_UP_e,
    /* 0x0D */ fopMsgM_Icon_ARROW_DOWN_e,
    /* 0x0E */ fopMsgM_Icon_MAIN_STICK_UP_e,
    /* 0x0F */ fopMsgM_Icon_MAIN_STICK_DOWN_e,
    /* 0x10 */ fopMsgM_Icon_MAIN_STICK_LEFT_e,
    /* 0x11 */ fopMsgM_Icon_MAIN_STICK_RIGHT_e,
    /* 0x12 */ fopMsgM_Icon_MAIN_STICK_UP_DOWN_e,
    /* 0x13 */ fopMsgM_Icon_MAIN_STICK_LEFT_RIGHT_e,
    /* 0x14 */ fopMsgM_Icon_SELECT_YOKO_LEFT_e,
    /* 0x15 */ fopMsgM_Icon_SELECT_YOKO_RIGHT_e,
    /* 0x16 */ fopMsgM_Icon_INPUT_e,
    /* 0x17 */ fopMsgM_Icon_FLASHING_A_BUTTON_e,
    /* 0x18 */ fopMsgM_Icon_HEART_e,
    /* 0x19 */ fopMsgM_Icon_MUSIC_NOTE_e,
    /* 0x1A */ fopMsgM_Icon_STARBURST_e,
    /* 0xFF */ fopMsgM_Icon_NONE_e = 0xFF,
};

class fopMsgM_msgDataProc_c {
public:
    fopMsgM_msgDataProc_c();
    virtual ~fopMsgM_msgDataProc_c();
    void dataInit();
    f32 charLength(int, int, bool);
    f32 rubyLength(int, bool);
    u32 stringLength();
    void stringShift();
    void iconSelect(int, u8);
    void iconIdxRefresh();
    u8 selectCheck2(J2DPane*, int, int, int);
    u8 selectCheck3(J2DPane*, int, int, int);
    u8 selectCheckYoko(J2DPane*, int, int, int);
    u8 inputNumber(int);
    void selectArrow(J2DPicture*, f32, f32, f32, f32);
    void selectArrow(J2DPicture*, f32, f32);
    void colorAnime(J2DPicture*);
    void stringSet();
    void getString(char*, u32);
    void getString(char*, char*, char*, char*, u32, f32*, f32*, int*);
    void getRubyString(char*, char*, char*, char*, char*, char*, f32*, f32*, int*);
#if VERSION >= VERSION_USA
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
#endif

    u8 getIconNum(int i_no) { return iconNum[i_no]; }
    int getIconPosX(int i_no) { return iconPosX[i_no]; }
    int getIconPosY(int i_no) { return iconPosY[i_no]; }
    int getIconScale(int i_no) { return iconScale[i_no]; }
    u32 getIconColor(int i_no) { return iconColor[i_no]; }

    void setCharSpace(int i_space) { charSpace = i_space; }
    void setRubyCharSpace(int i_space) { rubyCharSpace = i_space; }
    void setLineSpace(int i_space) { lineSpace = i_space; }

    void setOutMessage(char* param_0, char* param_1, char* param_2, char* param_3) {
        field_0x60 = param_0;
        field_0x40 = param_0;
        field_0x64 = param_1;
        field_0x44 = param_1;
        field_0x68 = param_2;
        field_0x48 = param_2;
        field_0x6C = param_3;
        field_0x4C = param_3;
    }
    void setSelectMessage(char* param_0, char* param_1, char* param_2, char* param_3) {
        selectMessage[0] = param_0;
        selectMessage[1] = param_1;
        selectMessage[2] = param_2;
        selectMessage[3] = param_3;
    }

    void setMesgEntry(JMSMesgEntry_c* i_entry) { mesgEntry = i_entry; }

    enum SelectFlag {
        /* 0x00 */ Select_OFF,
        /* 0x01 */ Select_ON,
        /* 0x02 */ Select_YOKO,
        /* 0x03 */ Select_AUCTION,
    };

    u8 getSelectFlag() { return selectFlag; }
    void setSelectFlagOff() { selectFlag = Select_OFF; }
    void setSelectFlagOn() { selectFlag = Select_ON; }
    void setSelectFlagYokoOn() { selectFlag = Select_YOKO; }
    void setSelectFlagAuctionOn() { selectFlag = Select_AUCTION; }
    u8 getAutoSendFlag() { return autoSendFlag; }
    void setAutoSendFlagOff() { autoSendFlag = 0; }
    void setAutoSendFlagOn() { autoSendFlag = 1; }
    u8 getHandSendFlag() { return handSendFlag; }
    void setHandSendFlagOff() { handSendFlag = 0; }
    void setHandSendFlagOn() { handSendFlag = 1; }

    int get_waitTimer() { return waitTimer; }
    void set_waitTimer(int value) { waitTimer = value; }
    void set_waitTimerZero() { waitTimer = 0; }
    int dec_waitTimer() { return waitTimer = waitTimer > 0 ? waitTimer - 1 : 0; }

    int dec_keyWaitTimer() { return keyWaitTimer = keyWaitTimer > 0 ? keyWaitTimer - 1 : 0; }

    int getLineCount() { return lineCount; }
    u8 getMesgStatus() { return mesgStatus; }
    f32 getNowCursorPos() { return nowCursorPos; }
    int getSelectLength() { return selectLength; }
    u32 getStringColor() { return stringColor; }
    void setStringColor(u32 i_color) { stringColor = i_color; }
    void resetNowLine() { nowLine = 0; }
    void selectArrow(J2DPicture* i_arrowPane) {
        selectArrow(i_arrowPane, field_0x26C, field_0x270, field_0x278, field_0x274);
    }
    void setActorPosition(cXyz* i_pos) { actorPosition = i_pos; }
    void setAimLine(int i_line) { aimLine = i_line; }
    void setBmgData(char* i_data) { bmgData = i_data; }
    void setCenterLineWidth(int i_width) { centerLineWidth = i_width; }

    u8 getCharAlpha() { return field_0x290; }
    u8 getGradAlpha() { return field_0x291; }
    u8 getRCharAlpha() { return field_0x292; }
    u8 getRGradAlpha() { return field_0x293; }
    void setCharAlpha(u8 param_0, u8 param_1, u8 param_2, u8 param_3) {
        field_0x290 = param_0;
        field_0x291 = param_1;
        field_0x292 = param_2;
        field_0x293 = param_3;
    }

    void setCount(int i_count) { count = i_count; }
    void setFont(JUTFont* i_font) { font = i_font; }
    void setFontSize(int i_size) { fontSize = i_size; }
    void setRubyFont(JUTFont* i_font) { rubyFont = i_font; }
    void setRubyFontSize(int i_size) { rubyFontSize = i_size; }
    void setLineCount(int i_count) { lineCount = i_count; }
    void setLineWidth(int i_width) { lineWidth = i_width; }
    void setSelectNum(u8) {}
    void setSendSpeed(int i_speed) { sendSpeed = i_speed; }
    void setSpaceFlagOff() { spaceFlag = 0; }
    void setSpaceFlagOn() { spaceFlag = 1; }
    void setSpaceTimer(int i_timer) { spaceTimer = i_timer; }
    void shortCut() { field_0x299 = 1; }

public:
    /* 0x004 */ JUTFont* font;
    /* 0x008 */ JUTFont* rubyFont;
    /* 0x00C */ JMSMesgEntry_c* mesgEntry;
    /* 0x010 */ cXyz* actorPosition;
    /* 0x014 */ f32 field_0x14;
    /* 0x018 */ f32 field_0x18;
    /* 0x01C */ f32 field_0x1C;
    /* 0x020 */ f32 nowCursorPos;
    /* 0x024 */ f32 field_0x24;
    /* 0x028 */ f32 field_0x28;
    /* 0x02C */ size_t field_0x2C;
    /* 0x030 */ size_t field_0x30;
    /* 0x034 */ size_t field_0x34;
    /* 0x038 */ size_t field_0x38;
    /* 0x03C */ const char* bmgData;
    /* 0x040 */ char* field_0x40;
    /* 0x044 */ char* field_0x44;
    /* 0x048 */ char* field_0x48;
    /* 0x04C */ char* field_0x4C;
    /* 0x050 */ char* selectMessage[4]; // TODO: should this be 4 separate fields? or should field_0x40 and field_0x60 also be arrays?
    /* 0x060 */ char* field_0x60;
    /* 0x064 */ char* field_0x64;
    /* 0x068 */ char* field_0x68;
    /* 0x06C */ char* field_0x6C;
    /* 0x070 */ char field_0x70[0x64]; // no idea how big this array is
    /* 0x0D4 */ char field_0xD4[4];
    /* 0x0D8 */ int field_0xD8[4];
    /* 0x0E8 */ int field_0xE8[4];
    /* 0x0F8 */ int field_0xF8[4];
    /* 0x108 */ int field_0x108[4];
    /* 0x118 */ int count;
    /* 0x11C */ int charSpace;
    /* 0x120 */ int lineSpace;
    /* 0x124 */ int rubyCharSpace;
    /* 0x128 */ int lineWidth;
    /* 0x12C */ int centerLineWidth;
    /* 0x130 */ int lineCount;
    /* 0x134 */ int field_0x134;
    /* 0x138 */ int nowLine;
    /* 0x13C */ int aimLine;
    /* 0x140 */ int field_0x140;
    /* 0x144 */ int fontSize;
    /* 0x148 */ int field_0x148; // size/scale?
    /* 0x14C */ int rubyFontSize;
    /* 0x150 */ int field_0x150;
    /* 0x154 */ int field_0x154;
    /* 0x158 */ int waitTimer;
    /* 0x15C */ int spaceTimer;
    /* 0x160 */ int sendSpeed;
    /* 0x164 */ int keyWaitTimer;
    /* 0x168 */ int iconPosX[0xF];
    /* 0x1A4 */ int iconPosY[0xF];
    /* 0x1E0 */ int iconScale[0xF];
    /* 0x21C */ int selectLength;
    /* 0x220 */ u32 iconColor[0xF];
    /* 0x25C */ u32 stringColor;
    /* 0x260 */ s16 field_0x260;
    /* 0x264 */ f32 field_0x264;
    /* 0x268 */ f32 field_0x268;
    /* 0x26C */ f32 field_0x26C;
    /* 0x270 */ f32 field_0x270;
    /* 0x274 */ f32 field_0x274;
    /* 0x278 */ f32 field_0x278;
    /* 0x27C */ u8 mesgStatus;
    /* 0x27D */ u8 field_0x27D;
    /* 0x27E */ u8 field_0x27E;
    /* 0x27F */ u8 field_0x27F;
    /* 0x280 */ u8 field_0x280;
    /* 0x281 */ u8 iconNum[0xF];
    /* 0x290 */ u8 field_0x290;
    /* 0x291 */ u8 field_0x291;
    /* 0x292 */ u8 field_0x292;
    /* 0x293 */ u8 field_0x293;
    /* 0x294 */ u8 selectFlag;
    /* 0x295 */ u8 field_0x295;
#if VERSION > VERSION_DEMO
    /* 0x296 */ u8 field_0x296;
#endif
    /* 0x297 */ u8 autoSendFlag;
    /* 0x298 */ u8 handSendFlag;
    /* 0x299 */ u8 field_0x299;
    /* 0x29A */ u8 field_0x29A;
    /* 0x29B */ u8 field_0x29B;
    /* 0x29C */ u8 spaceFlag;
    /* 0x29D */ u8 field_0x29D;
};  // Size: 0x2A0

typedef int (*fopMsgCreateFunc)(void*);

JKRExpHeap* fopMsgM_createExpHeap(u32 i_size, JKRHeap* i_heap);
JKRExpHeap* fopMsgM_createExpHeap(u32 i_size);
fpc_ProcID fopMsgM_Create(s16 i_procName, fopMsgCreateFunc, void*);
fpc_ProcID fopMsgM_create(s16 i_procName, fopAc_ac_c* i_actor = NULL, cXyz* i_pos = NULL, u32* i_msgNo = NULL, u32* param_4 = NULL, fopMsgCreateFunc i_createFunc = NULL);

inline fpc_ProcID fopMsgM_MiniGameStarter_create(s16 i_procName, u8 param_1, u16 param_2, fopMsgCreateFunc i_createFunc) {
    u32 parameter = param_1;
    parameter |= param_2 << 16;
    return fopMsgM_create(i_procName, NULL, NULL, &parameter, &parameter, i_createFunc);
}

fpc_ProcID fop_MGameTerm_create(s16 i_procName, s16, s16, int, int, fopMsgCreateFunc);

inline fpc_ProcID fopMsgM_MiniGameTerminater_create(s16 i_procName, s16 param_1, s16 param_2, int param_3, int param_4, fopMsgCreateFunc i_createFunc) {
    return fop_MGameTerm_create(i_procName, param_1, param_2, param_3, param_4, i_createFunc);
}

void fopMsgM_Delete(void* i_proc);
fopMsg_prm_class* fopMsgM_GetAppend(void* i_proc);
void fopMsgM_destroyExpHeap(JKRExpHeap* i_heap);
f32 fopMsgM_valueIncrease(int i_max, int i_value, u8 i_mode);
#if VERSION >= VERSION_USA
bool fopMsgM_hyrule_language_check(u32 i_msgNo);
#endif
s32 fopMsgM_setStageLayer(void* i_proc);
fpc_ProcID fopMsgM_messageSet(u32 i_msgNo, fopAc_ac_c* i_actor);
fpc_ProcID fopMsgM_messageSet(u32 i_msgNo, cXyz*);
fpc_ProcID fopMsgM_messageSet(u32 i_msgNo);
fpc_ProcID fopMsgM_scopeMessageSet(u32 i_msgNo);
int fopMsgM_messageSetDemo(u32 i_msgNo);
msg_class* fopMsgM_SearchByID(fpc_ProcID i_pid);
char* fopMsgM_messageGet(char* i_dest, u32 i_msgNo);
char* fopMsgM_passwordGet(char* i_dest, u32 i_msgNo);
fpc_ProcID fop_Timer_create(s16 i_procName, u8 i_mode, u16 i_limitTimeMs, u8 i_showType, u8 i_iconType, f32 i_posX, f32 i_posY, f32 i_rupeePosX, f32 i_rupeePosY, fopMsgCreateFunc i_createFunc);

inline fpc_ProcID fopMsgM_Timer_create(s16 i_procName, u8 i_mode, u16 i_limitTimeMs, u8 i_showType, u8 i_iconType, f32 i_posX, f32 i_posY, f32 i_rupeePosX, f32 i_rupeePosY, fopMsgCreateFunc createFunc) {
    return fop_Timer_create(i_procName, i_mode, i_limitTimeMs, i_showType, i_iconType, i_posX, i_posY, i_rupeePosX, i_rupeePosY, createFunc);
}

void fopMsgM_setPaneData(fopMsgM_pane_class* i_pane, J2DPane* i_paneData);
void fopMsgM_setPaneData(fopMsgM_pane_class* i_pane, J2DScreen* i_scrn, u32 i_tag);
void fopMsgM_setInitAlpha(fopMsgM_pane_class* i_pane);
void fopMsgM_setNowAlpha(fopMsgM_pane_class* i_pane, f32 i_alpha);
void fopMsgM_setNowAlphaZero(fopMsgM_pane_class* i_pane);
void fopMsgM_setAlpha(fopMsgM_pane_class* i_pane);
void fopMsgM_paneScaleX(fopMsgM_pane_class* i_pane, f32 i_scale);
void fopMsgM_paneScaleY(fopMsgM_pane_class* i_pane, f32 i_scale);
void fopMsgM_paneScale(fopMsgM_pane_class* i_pane, f32 i_scaleX, f32 i_scaleY);
void fopMsgM_paneScaleXY(fopMsgM_pane_class* i_pane, f32 i_scale);
void fopMsgM_cposMove(fopMsgM_pane_class* i_pane);
void fopMsgM_paneTrans(fopMsgM_pane_class* i_pane, f32 i_transX, f32 i_transY);

void fopMsgM_setPaneData(fopMsgM_pane_alpha_class* i_pane, J2DPane* i_paneData);
void fopMsgM_setPaneData(fopMsgM_pane_alpha_class* i_pane, J2DScreen* i_scrn, u32 i_tag);
void fopMsgM_setNowAlpha(fopMsgM_pane_alpha_class* i_pane, f32 i_alpha);
void fopMsgM_setAlpha(fopMsgM_pane_alpha_class* i_pane);

u32 fopMsgM_searchMessageNumber(u32 i_msgNo);
bool fopMsgM_forceSendOn();
bool fopMsgM_checkForceSend();
void fopMsgM_forceSendOff();
void fopMsgM_messageSendOn();
void fopMsgM_messageSendOff();
bool fopMsgM_checkMessageSend();
u32 fopMsgM_tactMessageSet();
fopMsgM_unk_struct fopMsgM_selectMessageGet(J2DPane* i_textPane, J2DPane* i_rubyPane, char* param_3, char* param_4, char* param_5, char* param_6, u32 i_msgNo);
void fopMsgM_demoMsgFlagOn();

bool fopMsgM_getScopeMode();
bool fopMsgM_releaseScopeMode();

void fopMsgM_demoMsgFlagOn();
void fopMsgM_demoMsgFlagOff();
bool fopMsgM_demoMsgFlagCheck();
void fopMsgM_tactMsgFlagOn();
void fopMsgM_tactMsgFlagOff();
bool fopMsgM_tactMsgFlagCheck();
void fopMsgM_nextMsgFlagOff();
bool fopMsgM_nextMsgFlagCheck();

void fopMsgM_blendInit(fopMsgM_pane_class* i_pane, const char* data);
void fopMsgM_blendInit(J2DPicture* pic, const char* data);
u8 fopMsgM_itemNumIdx(u8 i_no);
u8 fopMsgM_itemNum(u8 i_itemNo);
u32 fopMsgM_getColorTable(u16 i_colorNo);
void fopMsgM_int_to_char(char* i_dest, int i_value, bool param_3);
void fopMsgM_blendDraw(fopMsgM_pane_class* i_pane, const char* data);
void fopMsgM_blendDraw(J2DPicture* pic, const char* data);
void fopMsgM_setFontsizeCenter(char* param_1, char* param_2, char* param_3, char* param_4, int param_5, int param_6);
void fopMsgM_setFontsizeCenter2(char* a, char* b, char* c, char* d, int, int size, int, int);

void fopMsgM_outFontSet(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, s16* i_timer, u32 i_color, u8 i_iconNo);
void fopMsgM_outFontSet(J2DPicture* i_iconPic, s16* i_timer, u32 i_color, u8 i_iconNo);
void fopMsgM_outFontDraw(J2DPicture* i_iconPic, J2DPicture* i_sdwPic, int param_3, int param_4, int param_5, s16* i_timer, u8 i_alpha, u8 i_iconNo);
void fopMsgM_outFontDraw2(J2DPicture* i_iconPic, J2DPicture* param_2, int param_3, int param_4, int i_width, int i_height, s16* i_timer, u8 i_alpha, u8 i_iconNo);

extern u16 zfont[][2];

#endif /* F_OP_MSG_MNG_H */
