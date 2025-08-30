#ifndef D_A_OBJ_TORIPOST_H
#define D_A_OBJ_TORIPOST_H

#include "d/d_npc.h"
#include "SSystem/SComponent/c_phase.h"

struct daObjTpost_c__letter_data {
    /* 0x00 */ bool field_0x00;
    /* 0x04 */ u32 mMsgNo;
    /* 0x08 */ u8 mItemNo;
    /* 0x0A */ u16 mEventReg;
};

class daObjTpost_c : public fopNpc_npc_c {
public:
    enum Proc_e {
        PROC_INIT = 0,
        PROC_EXEC = 1
    };

    enum Mode {
        MODE_WAIT         = 0x0,
        MODE_TALK         = 0x1,
        MODE_TALK_XY      = 0x2,
        MODE_RECEIVE      = 0x3,
        MODE_RECEIVE_DEMO = 0x4,
        MODE_NULL,
    };

    enum BckIdx {
        BckIdx_POST_GET    = 0x0,
        BckIdx_POST_PUTOUT = 0x1,
        BckIdx_POST_WAIT   = 0x2,
    };

    enum AnmPrm {
        AnmPrm_POST_GET0   = 0x1,
        AnmPrm_POST_GET1   = 0x2,
        AnmPrm_POST_PUTOUT = 0x3,
        AnmPrm_POST_WAIT   = 0x4,
        AnmPrm_NULL,
    };

    void eventSet(s8 eventIdx) { mEventIdx = eventIdx; }
    int getSendPrice() { return m_send_price[mPayType]; }
    bool isAnm(s8 idx) { return mAnmPrmIdx == idx; }
    void modeProcInit(int newMode) { modeProc(PROC_INIT, newMode); }

    BOOL _createHeap();
    void cutProc();
    void cutPresentStart(int staffIdx);
    void cutPresentProc(int staffIdx);
    void cutSetAnmStart(int staffIdx);
    void cutSetAnmProc(int staffIdx);
    void cutDispLetterStart(int staffIdx);
    void cutDispLetterProc(int staffIdx);
    void deliverLetter();
    s16 getReceiveLetterNum();
    s32 getReadableLetterNum();
    u8 checkSendPrice();
    int getMsgXY();
    int getMsgNormal();
    u32 getMsg();
    u16 next_msgStatus(u32* pMsgNo);
    bool checkTalk();
    void eventOrder();
    void checkOrder();
    void setAttention();
    void setAnm(s8 param_1, bool param_2);
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeTalkInit();
    void modeTalk();
    void modeTalkXYInit();
    void modeTalkXY();
    void modeReceiveInit();
    void modeReceive();
    void modeReceiveDemoInit();
    void modeReceiveDemo();
    void modeProc(Proc_e proc, int newMode);
    bool _execute();
    void debugDraw();
    bool _draw();
    void createInit();
    void getArg();
    cPhs_State _create();
    bool _delete();

    static const char m_arc_name[];
    static const daObjTpost_c__letter_data m_letter[];
    static const dCcD_SrcCyl m_cyl_src;

private:
    static const s32 m_send_price[];

    /* 0x6C4 */ u32 mCurMode;
    /* 0x6C8 */ s8 mBckIdx;
    /* 0x6C9 */ s8 mAnmPrmIdx;
    /* 0x6CA */ s8 mOldAnmPrmIdx;
    /* 0x6CC */ request_of_phase_process_class mPhs;
    /* 0x6D4 */ mDoExt_McaMorf* mMorf;
    /* 0x6D8 */ dBgS_ObjAcch mAcch;
    /* 0x89C */ dBgS_AcchCir mAcchCir;
    /* 0x8DC */ int field_0x8DC;
    /* 0x8E0 */ int field_0x8E0;
    /* 0x8E4 */ int field_0x8E4;
    /* 0x8E8 */ u8 mPayType;
    /* 0x8E9 */ u8 field_0x8E9;
    /* 0x8EA */ u8 field_0x8EA;
    /* 0x8EB */ u8 field_0x8EB;
    /* 0x8EC */ int mNumReadable;
    /* 0x8F0 */ u32 field_0x8F0;
    /* 0x8F4 */ u8 field_0x8F4;
    /* 0x8F5 */ u8 field_0x8F5;
    /* 0x8F6 */ u8 mPreItemNo;
    /* 0x8F7 */ s8 mEventIdx;
};

#endif /* D_A_OBJ_TORIPOST_H */
