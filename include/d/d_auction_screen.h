#ifndef D_AUCTION_SCREEN_H
#define D_AUCTION_SCREEN_H

#include "dolphin/types.h"

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

#endif /* D_AUCTION_SCREEN_H */
