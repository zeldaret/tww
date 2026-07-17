#ifndef D_A_OBJ_HSEHI1_H
#define D_A_OBJ_HSEHI1_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "m_Do/m_Do_hostIO.h"

class JPABaseEmitter;
class daObj_hsh_c;

class daObj_hsh_HIO_c : public mDoHIO_entry_c {
public:
    daObj_hsh_HIO_c();
    virtual ~daObj_hsh_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 mAttentionDist;
    /* 0x0C */ f32 mAttentionOffsetY0;
    /* 0x10 */ f32 mAttentionOffsetY1;
    /* 0x14 */ s16 mAttentionAngle;
    /* 0x16 */ s8 m16;
    /* 0x18 */ daObj_hsh_c* mpActor;
};

class daObj_hsh_c : public fopAc_ac_c {
public:
    ~daObj_hsh_c();

    void isEventAccept() {}
    void isOffDraw() {}
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
    int setAction(int (daObj_hsh_c::*)(void*), void*);
    int waitAction(void*);
    int talkAction(void*);
    int offAction(void*);
    int deleteAction(void*);
    void eventOrder();
    void checkOrder();
    BOOL checkCommandTalk();
    BOOL chkAttention(cXyz, short);
    BOOL eventProc();
    void eventEnd();
    void initialDefault(int);
    BOOL actionDefault(int);
    void initialLinkDispEvent(int);
    void initialMsgSetEvent(int);
    void actionMsgSetEvent(int);
    void actionMessageEvent(int);
    void actionTactEvent(int);
    void initialJudgeEvent(int);
    void initialAppearEvent(int);
    BOOL actionAppearEvent(int);
    void initialDeleteEvent(int);
    BOOL actionDeleteEvent(int);
    BOOL talk_init();
    BOOL talk(int);
    u32 getMsg();
    u16 next_msgStatus(unsigned long*);
    BOOL execute();
    BOOL draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgS_ObjAcch mObjAcch;
    /* 0x460 */ dBgS_AcchCir mAcchCir;
    /* 0x4A0 */ JPABaseEmitter* mpEmitter;
    /* 0x4A4 */ Mtx mBaseMtx;
    /* 0x4D4 */ dBgW* mpBgw;
    /* 0x4D8 */ u8 m4D8[0xC];
    /* 0x4E4 */ cBgS_PolyInfo mPolyInfo;
    /* 0x4F4 */ int (daObj_hsh_c::*mpActionFunc)(void*);
    /* 0x500 */ u32 mShadowKey;
    /* 0x504 */ u32 mFlags;
    /* 0x508 */ u32 mMsgId;
    /* 0x50C */ u32 mSwitchNo;
    /* 0x510 */ u32 mMsgNo;
    /* 0x514 */ s8 mEventState;
    /* 0x515 */ s8 mEventCutIdx;
    /* 0x516 */ s8 m516;
    /* 0x517 */ s8 mActionState;
    /* 0x518 */ u8 mAttentionOn;
    /* 0x519 */ u8 mTimer;
    /* 0x51A */ u8 m51A[2];
    /* 0x51C */ s16 m51C[4];
    /* 0x524 */ u8 m524[4];
    /* 0x528 */ f32 m528;
    /* 0x52C */ u8 m52C[4];
    /* 0x530 */ s16 mEventIdx[2];
};

#endif /* D_A_OBJ_HSEHI1_H */
