#ifndef D_MINIGAME_TERMINATER_H
#define D_MINIGAME_TERMINATER_H

#include "dolphin/types.h"

class JKRArchive;
class J2DPane;
class fopMsgM_pane_class;

class dDlst_TerminaterScrnDraw_c {
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

class dMinigame_Terminater_c {
public:
    void getResultRupee() {}
    void getResultTime() {}
    void setResultRupee(int) {}
    void setResultTime(int) {}
    
    void _create();
    void _execute();
    void _draw();
    void _delete();
};

#endif /* D_MINIGAME_TERMINATER_H */
