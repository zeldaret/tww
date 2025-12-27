#ifndef D_A_NPC_BTSW_H
#define D_A_NPC_BTSW_H

#include "d/d_lib.h"
#include "d/d_npc.h"
#include "d/d_shop.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class SwMail2_c {
public:
    typedef void (SwMail2_c::*SwMail_Func)();

    BOOL CheckProc(SwMail_Func func) {
        return mFunc == func;
    }
    void SetProc(SwMail_Func func) {
        mFunc = func;
    }

    BOOL MailCreateInit(cXyz*, cXyz*);
    static u8 getNextNo(unsigned char);
    void init();
    void set_mtx();
    void set_mtx_throw();
    void DummyInit();
    void Dummy();
    void AppearInit();
    void Appear();
    void WaitInit();
    void Wait();
    void ThrowInit(cXyz, unsigned char);
    void Throw();
    void EndInit();
    void End();
    void SeDelete();
    void move();
    void draw(dKy_tevstr_c*);

    static u8 m_same_count;
    static u8 m_no_buff;

public:
    /* 0x00 */ SwMail_Func mFunc;
    /* 0x0C */ J3DModel* mpModel;
    /* 0x10 */ mDoExt_btpAnm field_0x10;
    /* 0x24 */ cXyz field_0x24;
    /* 0x30 */ cXyz field_0x30;
    /* 0x3C */ cXyz field_0x3C;
    /* 0x48 */ csXyz field_0x48;
    /* 0x4E */ csXyz field_0x4E;
    /* 0x54 */ u8 field_0x54;
    /* 0x55 */ u8 field_0x55;
    /* 0x56 */ u8 field_0x56;
    /* 0x58 */ cXyz* field_0x58;
    /* 0x5C */ cXyz* field_0x5C;
};  // Size: 0x60

class SwCam2_c {
public:
    SwCam2_c() {
        field_0x1E = 0;
        field_0x1C = 0;
        field_0x1D = 0;
        field_0x00 = SwCam2_c::camera_center_data[0][1];
        field_0x0C = camera_eye;
        field_0x18 = 58.0f;
    }

    void ActiveOff() {
        field_0x1E = 0;
    }
    void ActiveOn() {
        field_0x1E = 1;

        field_0x00 = camera_center_data[0][1];
        field_0x0C = camera_eye;
        field_0x18 = 58.0f;

        setAimIdx(0, 0);
    }
    cXyz* getCenterP() {
        return &field_0x0C;
    }
    cXyz* getEyeP() {
        return &field_0x00;
    }
    void setAimIdx(s8 row, s8 col) {
        field_0x1C = row;
        field_0x1D = col;
    }

    void Move();

    static cXyz camera_center_data[2][3];
    static cXyz camera_eye;

public:
    /* 0x00 */ cXyz field_0x00;
    /* 0x0C */ cXyz field_0x0C;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ s8 field_0x1C;
    /* 0x1D */ s8 field_0x1D;
    /* 0x1E */ u8 field_0x1E;
};  // Size: 0x1F

class daNpc_Btsw_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Btsw_c::*ActionFunc)(void*);

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_UNK_2    = 2,
        ACTION_ENDING   = -1,
    };

    cXyz& getAttentionBasePos() {
        return mAttPos;
    }
    void setAction(ActionFunc func, void* arg) {
        if (mCurrActionFunc != func) {
            if (mCurrActionFunc) {
                mActionStatus = ACTION_ENDING;
                (this->*mCurrActionFunc)(arg);
            }
            mCurrActionFunc = func;
            mActionStatus = ACTION_STARTING;
            (this->*mCurrActionFunc)(arg);
        }
    }

    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    bool chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void anmAtr(unsigned short);
    BOOL CreateInit();
    void set_mtx();
    void setAttention();
    void lookBack();
    void wait01();
    void talk01();
    BOOL wait_action(void*);
    BOOL dummy_event_action(void*);
    BOOL checkNextMailThrowOK();
    void TimerCountDown();
    BOOL shiwake_game_action(void*);
    BOOL getdemo_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ s8 m_handL;
    /* 0x6C5 */ s8 m_handR;
    /* 0x6C6 */ u8 field_0x6C6[0x6C8 - 0x6C6];
    /* 0x6C8 */ request_of_phase_process_class mPhs;
    /* 0x6D0 */ J3DModel* field_0x6D0;
    /* 0x6D4 */ dKy_tevstr_c field_0x6D4;
    /* 0x784 */ u8 field_0x784[0x7E4 - 0x784];
    /* 0x7E4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x7E8 */ mDoExt_btpAnm field_0x7E8;
    /* 0x7FC */ u8 field_0x7FC;
    /* 0x7FD */ u8 field_0x7FD[0x800 - 0x7FD];
    /* 0x800 */ SwMail2_c mSwMail0;
    /* 0x860 */ SwMail2_c mSwMail1;
    /* 0x8C0 */ SwMail2_c mSwMail2;
    /* 0x920 */ SwMail2_c* field_0x920[3];
    /* 0x92C */ u8 field_0x92C;
    /* 0x92D */ u8 field_0x92D[0x930 - 0x92D];
    /* 0x930 */ SwCam2_c mSwCam;
    /* 0x950 */ s16 field_0x950;
    /* 0x952 */ u8 field_0x952;
    /* 0x953 */ u8 field_0x953;
    /* 0x954 */ s16 field_0x954;
    /* 0x956 */ u8 field_0x956[0x958 - 0x956];
    /* 0x958 */ ShopCursor_c* mpShopCursor;
    /* 0x95C */ cXyz mAttPos;
    /* 0x968 */ u8 field_0x968[0x96A - 0x968];
    /* 0x96A */ s16 field_0x96A;
    /* 0x96C */ u8 field_0x96C[0x96E - 0x96C];
    /* 0x96E */ csXyz field_0x96E;
    /* 0x974 */ u8 field_0x974[0x978 - 0x974];
    /* 0x978 */ STControl field_0x978;
    /* 0x9A0 */ s8 field_0x9A0;
    /* 0x9A1 */ s8 field_0x9A1;
    /* 0x9A2 */ u8 field_0x9A2[0x9A4 - 0x9A2];
    /* 0x9A4 */ s32 field_0x9A4;
    /* 0x9A8 */ u8 mHasAttention;
    /* 0x9A9 */ u8 field_0x9A9;
    /* 0x9AA */ u8 field_0x9AA[0x9B0 - 0x9AA];
    /* 0x9B0 */ fpc_ProcID field_0x9B0;
    /* 0x9B4 */ s8 field_0x9B4;
    /* 0x9B5 */ u8 field_0x9B5[0x9B8 - 0x9B5];
    /* 0x9B8 */ ActionFunc mCurrActionFunc;
    /* 0x9C4 */ s8 field_0x9C4;
    /* 0x9C5 */ s8 field_0x9C5;
    /* 0x9C6 */ s8 field_0x9C6;
    /* 0x9C7 */ s8 field_0x9C7;
    /* 0x9C8 */ s16 field_0x9C8;
    /* 0x9CA */ s8 field_0x9CA;
    /* 0x9CB */ u8 field_0x9CB[0x9CD - 0x9CB];
    /* 0x9CD */ s8 mActionStatus;
    /* 0x9CE */ u8 field_0x9CE[0x9D0 - 0x9CE];
};  // Size: 0x9D0

#endif /* D_A_NPC_BTSW_H */
