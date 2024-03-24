#ifndef D_TIMER_H
#define D_TIMER_H

#include "f_op/f_op_msg_mng.h"
#include "d/d_drawlist.h"
#include "SSystem/SComponent/c_phase.h"
#include "dolphin/os/OSTime.h"

class J2DPane;
class JKRArchive;
class JKRSolidHeap;

class dDlst_TimerScrnDraw_c : public dDlst_base_c {
public:
    dDlst_TimerScrnDraw_c() {
        field_0x234 = 0;
        mRupeeNum = -1;
        field_0x235 = 0;
    }
    ~dDlst_TimerScrnDraw_c();
    void setScreen(const char*, JKRArchive*);
    void changeNumberTexture(J2DPane*, int);
    const char* getNumber(int);
    void setTimer(int);
    void setRupee(s16);
    void setPaneInitialPos(fopMsgM_pane_class*, f32, f32);
    void setTimerPos(f32, f32);
    void setRupeePos(f32, f32);
    void setShowType(u8);
    void setIconType(void*, u8);
    void anime();
    BOOL closeAnime();
    bool hide();
    void draw();

public:
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ fopMsgM_pane_class mClockIcon;
    /* 0x040 */ fopMsgM_pane_class mClockBG;
    /* 0x078 */ fopMsgM_pane_class mTimerNumber0;
    /* 0x0B0 */ fopMsgM_pane_class mTimerNumberBG;
    /* 0x0E8 */ fopMsgM_pane_class mTimerBG;
    /* 0x120 */ fopMsgM_pane_class mTimerBGShadow;
    /* 0x158 */ fopMsgM_pane_class mRupee;
    /* 0x190 */ fopMsgM_pane_class mRupeeXShadow;
    /* 0x1C8 */ fopMsgM_pane_class mRupeeShadow;
    /* 0x200 */ J2DPane* mTimerNumber[5];
    /* 0x214 */ J2DPane* mRupeeNumber[3];
    /* 0x220 */ J2DPane* mRupeeNumberShadow[3];
    /* 0x22C */ J2DPicture* mIconPicture;
    /* 0x230 */ s32 mRupeeNum;
    /* 0x234 */ s8 field_0x234;
    /* 0x235 */ u8 field_0x235;
    /* 0x236 */ u8 field_0x236;
    /* 0x237 */ u8 field_0x237;
};

class dTimer_c : public msg_class {
public:
    s32 _create();
    BOOL _execute();
    BOOL _draw();
    BOOL _delete();
    BOOL RestTimeCheck(int);
    BOOL deleteCheck();
    void SetSE();
    bool start();
    bool start(s16);
    bool stock_start();
    bool stock_start(s16);
    bool stop(u8);
    bool restart(u8);
    bool end(int);
    bool deleteRequest();
    s32 getTimeMs();
    s32 getLimitTimeMs();
    s32 getRestTimeMs();

    /* 0x0FC */ dDlst_TimerScrnDraw_c* mpScrnDraw;
    /* 0x100 */ void* iconTex;
    /* 0x104 */ request_of_phase_process_class mPhs;
    /* 0x10C */ u32 field_0x10c;
    /* 0x110 */ OSTime mStartTime;
    /* 0x118 */ OSTime mTime;
    /* 0x120 */ OSTime field_0x120;
    /* 0x128 */ OSTime field_0x128;
    /* 0x130 */ OSTime field_0x130;
    /* 0x138 */ OSTime field_0x138;
    /* 0x140 */ OSTime mLimitTime;
    /* 0x148 */ u32 field_0x148;
    /* 0x14C */ u32 field_0x14c;
    /* 0x150 */ s32 field_0x150;
    /* 0x154 */ s32 mTimerMode;
    /* 0x158 */ s32 field_0x158;
    /* 0x15C */ s32 field_0x15c;
    /* 0x160 */ s16 field_0x160;
    /* 0x162 */ u8 field_0x162;
    /* 0x163 */ u8 field_0x163;
    /* 0x164 */ u8 mState;
    /* 0x168 */ s32 mSeTimeLeft;
    /* 0x16C */ u32 mSeTableIndex;
    /* 0x170 */ JKRSolidHeap* mpSolidHeap;
    /* 0x174 */ u32 field_0x174;
};

uint dTimer_createStockTimer();

uint dTimer_createTimer(int, u16, u8, u8, f32, f32, f32, f32);

#endif /* D_TIMER_H */
