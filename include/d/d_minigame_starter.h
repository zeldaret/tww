#ifndef D_MINIGAME_STARTER_H
#define D_MINIGAME_STARTER_H

#include "f_op/f_op_msg_mng.h"
#include "d/d_drawlist.h"

class JKRArchive;
struct fopMsgM_pane_class;
class J2DScreen;

class dDlst_StarterScrnDraw_c : public dDlst_base_c {
public:
    f32 acc(s16 param_0, s16 param_1, s16 param_2) {
        return SQUARE((f32)(param_1 - param_2)) / SQUARE((f32)(param_0 - param_2));
    }

    void setScreen(const char*, JKRArchive*);
    BOOL anime1(int);
    BOOL anime2();
    void scaleAnime(f32);
    void setRotate(fopMsgM_pane_class*, f32);

    virtual ~dDlst_StarterScrnDraw_c() {}
    virtual void draw();

protected:
    /* 0x004 */ J2DScreen* mpScrn;
    /* 0x008 */ fopMsgM_pane_class field_0x008[VERSION_SELECT(3, 3, 7, 7)];
    /* 0x190 */ fopMsgM_pane_class field_0x190;
    /* 0x1C8 */ fopMsgM_pane_class field_0x1c8[3];
    /* 0x270 */ fopMsgM_pane_class field_0x270[3];
};

class dMinigame_Starter_c : public msg_class {
public:
    void countStart() { if (!mStatus) mStatus = 1; }
    
    cPhs_State _create();
    BOOL _execute();
    BOOL _draw();
    BOOL _delete();
    BOOL startCheck();
    BOOL deleteCheck();

public:
    /* 0x0FC */ dDlst_StarterScrnDraw_c* mStarterScrn;
    /* 0x100 */ request_of_phase_process_class mPhase;
    /* 0x108 */ JKRSolidHeap* mHeap;
    /* 0x10C */ s16 mTimer;
    /* 0x10E */ s16 field_0x10e;
    /* 0x110 */ u8 field_0x110;
    /* 0x111 */ u8 mStatus;
};  // Size: 0x114

#endif /* D_MINIGAME_STARTER_H */
