#ifndef D_A_TAG_MD_CB_H
#define D_A_TAG_MD_CB_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "SSystem/SComponent/c_lib.h"

class daTag_MdCb_c : public fopAc_ac_c {
public:
    typedef void (daTag_MdCb_c::*EventInitFunc)(int);
    typedef BOOL (daTag_MdCb_c::*EventActionFunc)(int);
    typedef BOOL (daTag_MdCb_c::*ActionFunc)(void*);

    ~daTag_MdCb_c();

    void offEventAccept() { cLib_offBit<u32>(m2AC, 1); }
    void onEventAccept() { cLib_onBit<u32>(m2AC, 1); }
    void setTimer(short value) { m2B2 = value; }

    cPhs_State create();
    BOOL init();
    BOOL checkTimer();
    BOOL checkEventFinish();
    void action(void*);
    BOOL setAction(ActionFunc, void*);
    BOOL warpAction(void*);
    BOOL messageAction(void*);
    BOOL talk_init();
    BOOL talk();
    u16 next_msgStatus(u32*);
    BOOL eventProc();
    void eventEnd();
    s32 getMyStaffId();
    void initialDefault(int);
    BOOL actionDefault(int);
    void initialInitEvent(int);
    void initialMsgSetEvent(int);
    BOOL actionMsgSetEvent(int);
    BOOL actionMessageEvent(int);
    void initialPlayerOffDrow(int);
    void initialPlayerOnDrow(int);
    void eventOrder();
    BOOL checkCommandTalk();
    BOOL checkAreaIn(fopAc_ac_c*);
    BOOL checkCondition();
    BOOL execute();
    BOOL draw();

    static u32 m_status;

public:
    /* 0x290 */ ActionFunc m290;
    /* 0x29C */ s32 m29C;
    /* 0x2A0 */ s32 m2A0;
    /* 0x2A4 */ u32 m2A4;
    /* 0x2A8 */ u32 m2A8;
    /* 0x2AC */ u32 m2AC;
    /* 0x2B0 */ u16 m2B0;
    /* 0x2B2 */ s16 m2B2;
    /* 0x2B4 */ s8 m2B4;
    /* 0x2B5 */ s8 m2B5;
    /* 0x2B6 */ s8 m2B6;
    /* 0x2B7 */ u8 m2B7;
    /* 0x2B8 */ u8 m2B8;
    /* 0x2B9 */ u8 m2B9;
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB[0x2BC - 0x2BB];
    /* 0x2BC */ s16 m2BC[7];
    /* 0x2CA */ s16 m2CA;
    /* 0x2CC */ s16 m2CC;
    /* 0x2CE */ s16 m2CE;
    /* 0x2D0 */ s16 m2D0;
    /* 0x2D2 */ u8 m2D2[0x2D8 - 0x2D2];
    /* 0x2D8 */ f32 m2D8;
    /* 0x2DC */ u8 m2DC[0x2E0 - 0x2DC];
}; // Size: 0x2E0

class daTag_MdCb_HIO_c : public JORReflexible {
public:
    struct hio_prm_c {
        /* 0x00 */ f32 m00;
        /* 0x04 */ f32 m04;
        /* 0x08 */ s16 m08;
        /* 0x0A */ s16 m0A;
        /* 0x0C */ u8 m0C;
        /* 0x0D */ u8 m0D;
        /* 0x0E */ u8 m0E;
        /* 0x0F */ u8 m0F;
        /* 0x10 */ u8 m10;
        /* 0x11 */ u8 m11;
        /* 0x12 */ u8 m12;
    };  // Size: 0x14

    daTag_MdCb_HIO_c();

    virtual ~daTag_MdCb_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ hio_prm_c mPrm;
    /* 0x1C */ daTag_MdCb_c* mpActor;
}; // size = 0x20

#endif /* D_A_TAG_MD_CB_H */
