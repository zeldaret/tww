#ifndef D_AUCTION_SCREEN_H
#define D_AUCTION_SCREEN_H

#include "dolphin/types.h"
#include "f_pc/f_pc_base.h"

struct fopMsgM_pane_class;
class J2DPane;
class JKRArchive;

class dAuction_screen_c {
public:
    void clearTimer() {}
    void draw() {}
    void getArchive(JKRArchive*) {}
    
    void screenSet();
    void initPosSet(fopMsgM_pane_class*, f32, f32);
    void gaugeMove();
    void nowRupeeSet();
    void nextRupeeSet(s16);
    void changeNumberTexture(J2DPane*, int);
    void rupeeCountTrans();
    void rupeeCountUp();
    void rupeeCountDown();
    void slotShowAnime();
    void gaugeShowAnime();
    void initialize();
    void _create();
    void _move();
    void _draw();
    void _open();
    void _close();
};

class dAs_c {
public:
    void _create();
    void _execute();
    void _draw();
    void _delete();
};

class dAs_HIO_c {
public:
    dAs_HIO_c();
};

void dAuction_screen_delete();
void dAuction_screen_slotShow();
void dAuction_screen_slotHide();
void dAuction_screen_gaugeHide();
void dAuction_screen_gaugeShow();
void dAuction_screen_gaugeUp();
void dAuction_screen_gaugeDown();
void dAuction_screen_talkStart();
void dAuction_screen_talkEnd();
fpc_ProcID dAuction_screen_create();

#endif /* D_AUCTION_SCREEN_H */
