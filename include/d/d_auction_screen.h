#ifndef D_AUCTION_SCREEN_H
#define D_AUCTION_SCREEN_H

#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "d/d_drawlist.h"

struct fopMsgM_pane_class;
class J2DPane;
class JKRArchive;
class J2DScreen;

class dAuction_screen_c : public dDlst_base_c {
public:
    void clearTimer() {
        field_0x470 = 0;  // guess
    }

    virtual ~dAuction_screen_c() {}
    void draw() {
        _draw();
    }
    
    // TODO
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
    bool _open();
    bool _close();

    /* 0x004 */ J2DScreen* scrn1;
    /* 0x008 */ J2DScreen* scrn2;
    /* 0x00C */ fopMsgM_pane_class field_0xc;
    /* 0x044 */ fopMsgM_pane_class field_0x44[3];
    /* 0x0EC */ fopMsgM_pane_class field_0xec[3];
    /* 0x194 */ fopMsgM_pane_class field_0x194;
    /* 0x1CC */ fopMsgM_pane_class field_0x1cc[6];
    /* 0x31C */ fopMsgM_pane_class field_0x31c[4];
    /* 0x3FC */ fopMsgM_pane_class field_0x3fc;
    /* 0x434 */ fopMsgM_pane_class field_0x434;
    /* 0x46C */ JKRArchive* archive;
    /* 0x470 */ s16 field_0x470;
    /* 0x472 */ s16 field_0x472;
    /* 0x474 */ s16 field_0x474;
};

class JKRSolidHeap;

class dAs_c : public msg_class {
public:
    BOOL _create();
    BOOL _execute();
    BOOL _draw();
    BOOL _delete();

    /* 0x0FC */ JKRSolidHeap* heap;
    /* 0x100 */ dAuction_screen_c* dAs_scrn;
    /* 0x104 */ request_of_phase_process_class phase;
    /* 0x10C */ u8 proc;
};

class dAs_HIO_c {
public:
    dAs_HIO_c();
    virtual ~dAs_HIO_c() {}

    /* 0x4 */ s8 id;
};

BOOL dAuction_screen_delete();
BOOL dAuction_screen_slotShow();
BOOL dAuction_screen_slotHide();
BOOL dAuction_screen_gaugeHide();
BOOL dAuction_screen_gaugeShow();
BOOL dAuction_screen_gaugeUp();
BOOL dAuction_screen_gaugeDown();
BOOL dAuction_screen_talkStart();
BOOL dAuction_screen_talkEnd();
fpc_ProcID dAuction_screen_create();

#endif /* D_AUCTION_SCREEN_H */
