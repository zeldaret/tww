#ifndef D_MINIGAME_STARTER_H
#define D_MINIGAME_STARTER_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"

class JKRArchive;
struct fopMsgM_pane_class;

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

class dMinigame_Starter_c : public msg_class {
public:
    void countStart() { if (!field_0x111) field_0x111 = true; }
    
    void _create();
    void _execute();
    void _draw();
    void _delete();
    BOOL startCheck();
    BOOL deleteCheck();
public:
    /* 0x0FC */ u8 field_0x0FC[0x111 - 0x0FC];
    /* 0x111 */ bool field_0x111;
    /* 0x112 */ u8 field_0x112[0x114 - 0x112];
};  // Size: 0x114

#endif /* D_MINIGAME_STARTER_H */
