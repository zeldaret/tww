#ifndef D_A_TAG_PHOTO_H
#define D_A_TAG_PHOTO_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class daTagPhoto_c : public fopAc_ac_c {
public:
    daTagPhoto_c();

    typedef void(daTagPhoto_c::*ProcFunc_t)();

    int getTagNo() { return mTagNo; }

    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    BOOL _delete();
    BOOL _draw();
    void setMode(u8);
    BOOL _execute();
    void executeWait();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    u16 talk(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setMessage(u32);
    u8 getPrmTagNo();

    enum Prm_e {
        PRM_TAG_NO_W = 8,
        PRM_TAG_NO_S = 0x00,
    };
public:
    /* Place member variables here */
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ fpc_ProcID mMsgID;
    /* 0x29C */ msg_class* mpCurrMsg;
    /* 0x2A0 */ u32 mMsgNo;
    /* 0x2A4 */ dNpc_EventCut_c mEventCut;
    /* 0x310 */ u32* field_0x310;
    /* 0x314 */ s16 mPhotoTalkEventIdx;
    /* 0x316 */ s16 mPhotoTalk2EventIdx;
    /* 0x318 */ u8 mTagNo;
    /* 0x319 */ u8 mMode;
    /* 0x31A */ u8 field_0x31A;
    /* 0x31B */ s8 mActIdx;
    /* 0x31C */ u8 field_0x31C;
    /* 0x31D */ u8 field_0x31D[0x320 - 0x31D];
};  // Size: 0x320

#endif /* D_A_TAG_PHOTO_H */
