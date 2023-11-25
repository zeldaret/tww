#ifndef D_A_TAG_GHOSTSHIP_H
#define D_A_TAG_GHOSTSHIP_H

#include "f_op/f_op_actor.h"

class daTag_Gship_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    void modeProcInit(int) {}

    void modeClearWaitInit();
    void modeClearWait();
    void modeClearEventInit();
    void modeClearEvent();
    void modeProc(Proc_e, int);
    BOOL _execute();
    BOOL _draw();
    void getArg();
    s32 _create();
    BOOL _delete();

public:
    /* 0x290 */ PTMF* m290;
    /* 0x294 */ s8 m294;
    /* 0x295 */ s8 m295;
    /* 0x296 */ s8 m296;
    /* 0x297 */ s8 m297;
    /* 0x298 */ f32 m298;
    /* 0x29C */ u8 m29C[0x2A4 - 0x29C];
};

#endif /* D_A_TAG_GHOSTSHIP_H */
