#ifndef D_A_TAG_EVENT_H
#define D_A_TAG_EVENT_H

#include "f_op/f_op_actor.h"

class daTag_Event_c : public fopAc_ac_c {
public:
    enum Action_e {
        ACTION_WAIT        = 0x0,
        ACTION_ARRIVAL     = 0x1,
        ACTION_HUNT        = 0x2,
        ACTION_HUNT2       = 0x3,
        ACTION_READY       = 0x4,
        ACTION_EVENT       = 0x5,
        ACTION_SPE_ARRIVAL = 0x6,
        ACTION_SPE_HUNT    = 0x7,
        ACTION_SPE_READY   = 0x8,
        ACTION_SPE_EVENT   = 0x9,
        ACTION_MJ_HUNT     = 0xA,
        ACTION_MJ_READY    = 0xB,
    };

    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();

    void setActio(u8 i_action) { mAction = i_action; }

    u8 getEventNo();
    u8 getSwbit();
    u8 getSwbit2();
    u8 getType();
    u16 getEventFlag();
    BOOL cancelShutter();
    BOOL arrivalTerms();
    void demoInitProc();
    void demoEndProc();
    void demoProc();
    BOOL actionEvent();
    BOOL actionReady();
    BOOL actionHunt();
    BOOL actionArrival();
    BOOL actionSpeEvent();
    BOOL actionSpeReady();
    BOOL actionSpeHunt();
    BOOL actionSpeArrival();
    BOOL actionWait();
    BOOL actionMjReady();
    BOOL actionMjHunt();
    BOOL actionHunt2();

public:
    /* 0x290 */ s16 mEventIdx;
    /* 0x292 */ s16 m292;
    /* 0x294 */ s16 m294;
    /* 0x296 */ u8 mAction;
    /* 0x297 */ u8 m297;
};

#endif /* D_A_TAG_EVENT_H */
