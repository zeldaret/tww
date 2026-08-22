#ifndef D_A_OBJ_HSEHI1_H
#define D_A_OBJ_HSEHI1_H

#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "SSystem/SComponent/c_bg_w.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class JPABaseEmitter;

class daObj_hsh_c : public fopAc_ac_c {
public:
    ~daObj_hsh_c();
    
    void isEventAccept() {}
    BOOL isOffDraw() {
        return (mFlags & 8) == 0;
    }
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
    void createHeap();
    cPhs_State create();
    void init();
    void action(void*);
    void setAction(int (daObj_hsh_c::*)(void*), void*);
    void waitAction(void*);
    void talkAction(void*);
    void offAction(void*);
    void deleteAction(void*);
    void eventOrder();
    void checkOrder();
    void checkCommandTalk();
    void chkAttention(cXyz, short);
    void eventProc();
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
    void actionAppearEvent(int);
    void initialDeleteEvent(int);
    void actionDeleteEvent(int);
    void talk_init();
    void talk(int);
    void getMsg();
    void next_msgStatus(unsigned long*);
    BOOL execute();
    BOOL draw();

public:
    /* Place member variables here */
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];  // TODO: known: mPhs, mObjAcch, emitters...
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29c */ u8 field_0x29c[0x4a0 - 0x29c];  // TODO: Padding between field_0x290 and mpEmitter
    /* 0x4a0 */ JPABaseEmitter* mpEmitter;
    /* 0x4a4 */ Mtx mMtx;
    /* 0x4d4 */ cBgW* mpBgW;
    /* 0x4d8 */ u8 field_0x4d8[0x504 - 0x4d8];
    /* 0x504 */ u32 mFlags;
    /* 0x508 */ u8 field_0x508[0x515 - 0x508];
    /* 0x515 */ u8 field_0x515;
    /* 0x516 */ u8 field_0x516[0x530 - 0x516];
    /* 0x530 */ s16 field_0x530;
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
    };  // Size: 0x10

public:
    daObj_hsh_HIO_c();
    virtual ~daObj_hsh_HIO_c() {}

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ hio_prm_c prm;
    /* 0x18 */ daObj_hsh_c* mpActor;
};  // Size: 0x1C

#endif /* D_A_OBJ_HSEHI1_H */
