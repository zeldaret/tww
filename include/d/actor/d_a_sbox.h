#ifndef D_A_SBOX_H
#define D_A_SBOX_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_particle.h"

class daSbox_c : public fopAc_ac_c {
public:
    bool chkFlag(unsigned short flg) { return (m34E & flg) == flg; }
    void clrFlag(unsigned short flg) { m34E &= ~flg; }
    inline BOOL draw();
    inline BOOL execute();
    void setAction(unsigned char action) { m2EC = action; }
    void setFlag(unsigned short flg) { m34E |= flg; }

    BOOL CreateHeap();
    void calcMtx();
    void shipMtx();
    BOOL volmProc();
    BOOL darkProc();
    BOOL lightProc();
    void lightInit();
    BOOL CreateInit();
    cPhs_State create();
    void demoInitWait();
    BOOL demoProcWait();
    void demoInitOpen();
    void demoProcOpen();
    void demoInitDelete();
    void demoProcDelete();
    void demoInitCom();
    void demoProcCom();
    s32 getNowEventAction();
    BOOL demoProc();
    BOOL actionWait();

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x2AC */ J3DModel* mpModel1;
    /* 0x29C */ mDoExt_bckAnm mBck1;
    /* 0x2AC */ J3DModel* mpModel2;
    /* 0x2B0 */ mDoExt_bckAnm mBck2;
    /* 0x2C0 */ mDoExt_btkAnm mBtk;
    /* 0x2D4 */ mDoExt_brkAnm mBrk;
    /* 0x2EC */ u8 m2EC;
    /* 0x2ED */ u8 m2ED[0x2F4 - 0x2ED];
    /* 0x2F4 */ s16 m2F4;
    /* 0x2F8 */ s32 m2F8;
    /* 0x2FC */ JPABaseEmitter* mEmitter;
    /* 0x300 */ s16 m300;
    /* 0x304 */ f32 m304;
    /* 0x308 */ s16 m308;
    /* 0x30C */ LIGHT_INFLUENCE m30C;
    /* 0x32C */ LIGHT_INFLUENCE m32C;
    /* 0x34C */ s16 m34C;
    /* 0x34E */ u16 m34E;
}; // size = 0x350

#endif /* D_A_SBOX_H */
