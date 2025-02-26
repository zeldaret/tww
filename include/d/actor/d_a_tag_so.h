#ifndef D_A_TAG_SO_H
#define D_A_TAG_SO_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class daTag_So_c : public fopAc_ac_c {
public:
    void getJumpRange() {}
    void getRndNum() {}
    void isMinigame() {}
    void isTag() {}

    bool _execute();
    void debugDraw();
    bool _draw();
    void getArg();
    s32 _create();
    bool _delete();

public:
    /* 0x290 */ u8 mParam;
    /* 0x291 */ u8 m291[0x293-0x291];
    /* 0x294 */ float mRadius;
    /* 0x298 */ u8 m298;
    /* 0x299 */ u8 m299[0x2A2 - 0x299];
};

class daTag_So_HIO_c {
public:
    daTag_So_HIO_c();
    virtual ~daTag_So_HIO_c(){}

public:
    /* 0x00 */ //vtable
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06[0x0F-0x06];
};

#endif /* D_A_TAG_SO_H */
