#ifndef D_MINIGAME_TERMINATER_H
#define D_MINIGAME_TERMINATER_H

#include "d/d_drawlist.h"

class JKRArchive;
class J2DPane;
struct fopMsgM_pane_class;

class dDlst_TerminaterScrnDraw_c : public dDlst_base_c {
public:
    void acc(s16, s16, s16) {}

    void setScreen(const char*, JKRArchive*);
    void setScrnFailed();
    void setScrnSuccess(int, int);
    void changeNumberTexture(J2DPane*, int);
    void getNumber(int);
    void setAlphaFailed();
    void setAlphaSuccess();
    void getRotate(fopMsgM_pane_class*);
    void setRotate(fopMsgM_pane_class*, f32);
    void setScale(fopMsgM_pane_class*, f32);
    void animeF1(int);
    void animeF2(int);
    void animeF3(int);
    void animeS1();
    void animeS2(fopMsgM_pane_class*);
    void animeS3();
    void animeFailed1();
    void animeFailed2();
    void animeSuccess();
    void animePerfect();
    void draw();
};

class dMinigame_Terminater_c : public msg_class {
public:
    void getResultRupee() {}
    void getResultTime() {}
    void setResultRupee(int) {}
    void setResultTime(int) {}

    void _create();
    void _execute();
    void _draw();
    void _delete();

    /* 0x0FC */ dDlst_TerminaterScrnDraw_c* mTerminaterScrnDraw;
    /* 0x100 */ request_of_phase_process_class mPhs;
    /* 0x108 */ JKRSolidHeap* mHeap;
    /* 0x10C */ u32 field_0x10c;
    /* 0x110 */ u32 field_0x110;
    /* 0x114 */ u16 field_0x114;
    /* 0x116 */ u16 field_0x116;
    /* 0x118 */ s16 field_0x118;
    /* 0x11A */ s16 field_0x11a;
    /* 0x11C */ u8 field_0x11c;
};

#endif /* D_MINIGAME_TERMINATER_H */
