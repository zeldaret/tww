#ifndef D_TIMER_H
#define D_TIMER_H

#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_msg_mng.h"

class J2DPane;
class JKRArchive;

class dDlst_TimerScrnDraw_c {
public:
    ~dDlst_TimerScrnDraw_c();
    void setScreen(const char*, JKRArchive*);
    void changeNumberTexture(J2DPane*, int);
    void getNumber(int);
    void setTimer(int);
    void setRupee(s16);
    void setPaneInitialPos(fopMsgM_pane_class*, f32, f32);
    void setTimerPos(f32, f32);
    void setRupeePos(f32, f32);
    void setShowType(u8);
    void setIconType(void*, u8);
    void anime();
    void closeAnime();
    void hide();
    void draw();
};

class dTimer_c {
public:
    void _create();
    void _execute();
    void _draw();
    void _delete();
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

    /* 0x000 */ msg_class parent;
    /* 0x0FC */ dDlst_TimerScrnDraw_c* mpScrnDraw;
    /* 0x100 */ u8 field_0x100[0x104 - 0x100];
    /* 0x104 */ request_of_phase_process_class mPhs;
    /* 0x10C */ u8 field_0x10C[0x154 - 0x10C];
    /* 0x154 */ int field_0x154;
    /* 0x158 */ u8 field_0x158[0x170 - 0x158];
    /* 0x170 */ JKRHeap* mpSolidHeap;
};

#endif /* D_TIMER_H */
