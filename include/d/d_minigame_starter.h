#ifndef D_MINIGAME_STARTER_H
#define D_MINIGAME_STARTER_H

#include "dolphin/types.h"

class JKRArchive;
class fopMsgM_pane_class;

class dDlst_StarterScrnDraw_c {
public:
    void acc(s16, s16, s16) {}
    
    void setScreen(const char*, JKRArchive*);
    void anime1(int);
    void anime2();
    void scaleAnime(f32);
    void setRotate(fopMsgM_pane_class*, f32);
    void draw();
};

class dMinigame_Starter_c {
public:
    void countStart() {}
    
    void _create();
    void _execute();
    void _draw();
    void _delete();
    void startCheck();
    void deleteCheck();
};

#endif /* D_MINIGAME_STARTER_H */
