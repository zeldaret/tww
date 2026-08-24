#ifndef D_A_OBJ_HSEHI1_H
#define D_A_OBJ_HSEHI1_H

#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class JPABaseEmitter;

class daObj_hsh_c : public fopAc_ac_c {
public:
    typedef BOOL (daObj_hsh_c::*ActionFunc)(void*);
    typedef void (daObj_hsh_c::*EventActionInitFunc)(int evtStaffId);
    typedef BOOL (daObj_hsh_c::*EventActionFunc)(int evtStaffId);

    ~daObj_hsh_c();

    void isEventAccept() {}
    BOOL isOffDraw() { return (mFlags & 8) == TRUE; }
    void isTactCancel() {}
    void isTactCorrect() {}
    void offEventAccept() {}
    void offTactCancel() {}
    void offTactCorrect() {}
    void onEventAccept() {}
    void onTactCancel() {}
    void onTactCorrect() {}

    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    void particle_set(unsigned short);
    void particle_set(JPABaseEmitter**, unsigned short);
    void emitterDelete(JPABaseEmitter**);
    void setAttention(bool);
    void onOffDraw();
    void offOffDraw();
    void drawStop();
    void drawStart();
    void setBaseMtx();
    BOOL createHeap();
    cPhs_State create();
    BOOL init();
    void action(void*);
    BOOL setAction(ActionFunc, void*);
    BOOL waitAction(void*);
    BOOL talkAction(void*);
    BOOL offAction(void*);
    BOOL deleteAction(void*);
    void eventOrder();
    void checkOrder();
    BOOL checkCommandTalk();
    bool chkAttention(cXyz, short);
    BOOL eventProc();
    void eventEnd();
    void initialDefault(int);
    BOOL actionDefault(int);
    void initialLinkDispEvent(int);
    void initialMsgSetEvent(int);
    BOOL actionMsgSetEvent(int);
    BOOL actionMessageEvent(int);
    BOOL actionTactEvent(int);
    void initialJudgeEvent(int);
    void initialAppearEvent(int);
    BOOL actionAppearEvent(int);
    void initialDeleteEvent(int);
    BOOL actionDeleteEvent(int);
    BOOL talk_init();
    BOOL talk(int);
    u32 getMsg();
    u32 next_msgStatus(unsigned long*);
    BOOL execute();
    BOOL draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29c */ dBgS_ObjAcch mObjAcch;
    /* 0x460 */ dBgS_AcchCir mAcchCir;
    /* 0x4a0 */ JPABaseEmitter* mpEmitter;
    /* 0x4a4 */ Mtx mMtx;
    /* 0x4d4 */ dBgW* mpBgW;
    /* 0x4d8 */ u8 field_0x4d8[0x4e4 - 0x4d8]; // Padding
    /* 0x4e4 */ cBgS_PolyInfo mPolyInfo;
    /* 0x4f4 */ ActionFunc mAction;
    /* 0x500 */ u32 mShadowId;
    /* 0x504 */ u32 mFlags;
    /* 0x508 */ u32 mMsgNo;
    /* 0x50c */ int mSwitchNo;
    /* 0x510 */ u32 mPrmMsgNo;
    /* 0x514 */ s8 field_0x514;
    /* 0x515 */ s8 mEventSelector;
    /* 0x516 */ u8 field_0x516;
    /* 0x517 */ s8 mActionMode;
    /* 0x518 */ u8 mAttentionLatch;
    /* 0x519 */ u8 mAppearDeleteTimer;
    /* 0x51a */ u8 field_0x51a[0x51c - 0x51a]; // Padding
    /* 0x51c */ s16 field_0x51c;
    /* 0x51e */ s16 field_0x51e;
    /* 0x520 */ s16 field_0x520;
    /* 0x522 */ s16 field_0x522;
    /* 0x524 */ u8 field_0x524[0x528 - 0x524]; // Padding
    /* 0x528 */ f32 field_0x528;
    /* 0x52c */ u8 field_0x52c[0x530 - 0x52c]; // Padding
    /* 0x530 */ s16 mEventId[2];
};

class daObj_hsh_HIO_c : public JORReflexible {
public:
    struct hio_prm_c {
        // Note: Offsets are relative to daObj_hsh_HIO_c instead of hio_prm_c for convenience.
        /* 0x08 */ f32 mAttnDist;
        /* 0x0C */ f32 field_0x0c;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ s16 mAttnAngle;
        /* 0x16 */ s8 field_0x16;
    }; // Size: 0x10

public:
    daObj_hsh_HIO_c();
    virtual ~daObj_hsh_HIO_c() {}

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ hio_prm_c prm;
    /* 0x18 */ daObj_hsh_c* mpActor;
}; // Size: 0x1C

#endif /* D_A_OBJ_HSEHI1_H */
