#ifndef D_TIMER_H
#define D_TIMER_H

#include "f_op/f_op_msg_mng.h"
#include "d/d_drawlist.h"
#include "SSystem/SComponent/c_phase.h"

class J2DPane;
class JKRArchive;
class JKRSolidHeap;

class dDlst_TimerScrnDraw_c : public dDlst_base_c {
public:
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
    bool closeAnime();
    bool hide();
    void draw();

public:
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ fopMsgM_pane_class field_0x008;
    /* 0x040 */ fopMsgM_pane_class field_0x040;
    /* 0x078 */ fopMsgM_pane_class field_0x078;
    /* 0x0B0 */ fopMsgM_pane_class field_0x0b0;
    /* 0x0E8 */ fopMsgM_pane_class field_0x0e8;
    /* 0x120 */ fopMsgM_pane_class field_0x120;
    /* 0x158 */ fopMsgM_pane_class field_0x158;
    /* 0x190 */ fopMsgM_pane_class field_0x190;
    /* 0x1C8 */ fopMsgM_pane_class field_0x1c8;
    /* 0x200 */ J2DPane* field_0x200;
    /* 0x204 */ J2DPane* field_0x204;
    /* 0x208 */ J2DPane* field_0x208;
    /* 0x20C */ J2DPane* field_0x20c;
    /* 0x210 */ J2DPane* field_0x210;
    /* 0x214 */ J2DPane* field_0x214;
    /* 0x218 */ J2DPane* field_0x218;
    /* 0x21C */ J2DPane* field_0x21c;
    /* 0x220 */ J2DPane* field_0x220;
    /* 0x224 */ J2DPane* field_0x224;
    /* 0x228 */ J2DPane* field_0x228;
    /* 0x22C */ J2DPicture* field_0x22c;
    /* 0x230 */ u32 field_0x230;
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
    void RestTimeCheck(int);
    void deleteCheck();
    void SetSE();
    void start();
    void start(s16);
    void stock_start();
    void stock_start(s16);
    void stop(u8);
    void restart(u8);
    void end(int);
    void deleteRequest();
    void getTimeMs();
    void getLimitTimeMs();
    void getRestTimeMs();

    /* 0x0FC */ dDlst_TimerScrnDraw_c* mpScrnDraw;
    /* 0x100 */ void* iconTex;
    /* 0x104 */ request_of_phase_process_class mPhs;
    /* 0x10C */ u8 field_0x10C[0x154 - 0x10C];
    /* 0x154 */ u32 mType;
    /* 0x158 */ u8 field_0x158[0x170 - 0x158];
    /* 0x170 */ JKRSolidHeap* mpSolidHeap;
    /* 0x174 */ u32 field_0x174;
};

#endif /* D_TIMER_H */
