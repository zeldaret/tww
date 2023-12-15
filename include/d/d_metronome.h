
#ifndef D_METRONOME_H
#define D_METRONOME_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "JSystem/JUtility/TColor.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"

class dMn_HIO_c : public mDoHIO_entry_c {
public:
    dMn_HIO_c();
    virtual ~dMn_HIO_c() {}

public:
    /* 0x04 */ f32 mEchoScale;
    /* 0x08 */ s16 mShiftTiming;
    /* 0x0A */ s16 mFlashTiming;
    /* 0x0C */ JUtility::TColor mWhiteColor0;
    /* 0x10 */ JUtility::TColor mWhiteColor1;
    /* 0x14 */ JUtility::TColor mBlackColor0;
    /* 0x18 */ JUtility::TColor mBlackColor1;
    /* 0x1C */ u8 mAlphaOrig;
    /* 0x1D */ u8 mTimingTrail;
};

class dMetronome_c : public dDlst_base_c {
public:
    void screenSet();
    void metronomeMove();
    void melodyInit(u8);
    void melodyMove();
    void melodyGuideShow(s32, s16);
    void melodyShow();
    void melodyDemo();
    void melodyFlash();
    void melodyShift();
    void initialize();
    void _create();
    void _delete();
    void _move();
    void _draw();
    BOOL _open();
    BOOL _close();

public:
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ fopMsgM_pane_class pane_cn[7];
    /* 0x190 */ fopMsgM_pane_class pane_wn[7];
    /* 0x318 */ fopMsgM_pane_class pane_pk[7];
    /* 0x4A0 */ fopMsgM_pane_class pane_i12[7];
    /* 0x628 */ fopMsgM_pane_class pane_i11[7];
    /* 0x7B0 */ fopMsgM_pane_class pane_bs[7];
    /* 0x938 */ fopMsgM_pane_class pane_timing[21]; // Metronome dots at the top
    /* 0xDD0 */ fopMsgM_pane_class pane_echo; // Metronome "echo" when it hits the center dot.

    /* 0xE08 */ JPABaseEmitter * mpEmitter;
    /* 0xE0C */ f32 mCurRate;
    /* 0xE10 */ f32 mPosX;
    /* 0xE14 */ s32 field_0xE14;
    /* 0xE18 */ s32 mNote[7];
    /* 0xE34 */ s32 mCurTimer;
    /* 0xE38 */ u8 field_0xE38;
    /* 0xE39 */ u8 mMelodyNum;
    /* 0xE3A */ u8 mAction;
    /* 0xE3B */ u8 mbOpen;
};

#endif /* D_METRONOME_H */
