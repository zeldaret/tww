#ifndef D_A_TAG_GHOSTSHIP_H
#define D_A_TAG_GHOSTSHIP_H

#include "f_op/f_op_actor.h"

class daTag_Gship_c : public fopAc_ac_c {
public:
    enum Proc_e {
        CLEAR_WAIT = 0,
        CLEAR_EVENT
    };

    void modeProcInit(int) {}

    void modeClearWaitInit();
    void modeClearWait();
    void modeClearEventInit();
    void modeClearEvent();
    void modeProc(Proc_e, int);
    bool _execute();
    bool _draw();
    void getArg();
    s32 _create();
    bool _delete();

public:
    /* 0x290 */ int mMode;
    /* 0x294 */ s8 field_0x294;
    /* 0x298 */ f32 field_0x298;
    /* 0x29C */ u8 field_0x29C[0x2A4 - 0x29C];
}; // Size: 0x2A4

class daTag_Gship_HIO_c {
public:
    daTag_Gship_HIO_c();
    virtual ~daTag_Gship_HIO_c() {}

    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05;
    /* 0x08 */ u32 field_0x08;
    /* 0x0C */ u32 field_0x0C;
}; // Size: 0x10

#endif /* D_A_TAG_GHOSTSHIP_H */
