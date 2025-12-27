#ifndef D_A_NPC_BMSW_H
#define D_A_NPC_BMSW_H

#include "d/d_lib.h"
#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_hostIO.h"

class ShopCursor_c;

class SwMail_c {
public:
    typedef void (SwMail_c::*SwMail_Func)();

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
    /* 0x57 */ u8 field_0x57[0x58 - 0x57];
    /* 0x58 */ cXyz* field_0x58;
    /* 0x5C */ cXyz* field_0x5C;
};  // Size: 0x60

class SwCam_c {
public:
    SwCam_c() {
        field_0x1E = 0;
        field_0x1C = 0;
        field_0x1D = 0;
        field_0x00 = SwCam_c::camera_center_data[0][1];
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

class daNpc_Bmsw_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Bmsw_c::*ActionFunc)(void*);

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_UNK_2    = 2,
        ACTION_ENDING   = -1,
    };


    Mtx& getArmLMtx() {
        return field_0x794;
    }
    Mtx& getArmRMtx() {
        return field_0x7C4;
    }
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
    BOOL checkNextMailThrowOK();
    void setGameGetRupee(short);
    void TimerCountDown();
    BOOL shiwake_game_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ s8 m_ArmR;
    /* 0x6C5 */ s8 m_ArmL;
    /* 0x6C6 */ s8 m_handR;
    /* 0x6C7 */ s8 m_handL;
    /* 0x6C8 */ s8 m_body_ArmR;
    /* 0x6C9 */ s8 m_body_ArmL;
    /* 0x6CA */ s8 m_neck_jnt_num;
    /* 0x6CB */ u8 field_0x6CB[0x6CC - 0x6CB];
    /* 0x6CC */ request_of_phase_process_class mPhs;
    /* 0x6D4 */ J3DModel* field_0x6D4;
    /* 0x6D8 */ J3DModel* field_0x6D8;
    /* 0x6DC */ J3DModel* field_0x6DC;
    /* 0x6E0 */ dKy_tevstr_c field_0x6E0;
    /* 0x790 */ mDoExt_McaMorf* mpMorfHand;
    /* 0x794 */ Mtx field_0x794;
    /* 0x7C4 */ Mtx field_0x7C4;
    /* 0x7F4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x7F8 */ mDoExt_btpAnm field_0x7F8;
    /* 0x80C */ u8 field_0x80C;
    /* 0x80D */ u8 field_0x80D[0x810 - 0x80D];
    /* 0x810 */ SwMail_c mSwMail0;
    /* 0x870 */ SwMail_c mSwMail1;
    /* 0x8D0 */ SwMail_c mSwMail2;
    /* 0x930 */ SwMail_c* field_0x930[3];
    /* 0x93C */ u8 field_0x93C;
    /* 0x93D */ u8 field_0x93D[0x940 - 0x93D];
    /* 0x940 */ SwCam_c mSwCam;
    /* 0x960 */ s16 field_0x960;
    /* 0x962 */ u8 field_0x962;
    /* 0x963 */ u8 field_0x963;
    /* 0x964 */ s16 field_0x964;
    /* 0x966 */ u8 field_0x966[0x968 - 0x966];
    /* 0x968 */ ShopCursor_c* mpShopCursor;
    /* 0x96C */ cXyz mAttPos;
    /* 0x978 */ u8 field_0x978[0x97A - 0x978];
    /* 0x97A */ s16 field_0x97A;
    /* 0x97C */ u8 field_0x97C[0x97E - 0x97C];
    /* 0x97E */ csXyz field_0x97E;
    /* 0x984 */ u8 field_0x984[0x988 - 0x984];
    /* 0x988 */ STControl field_0x988;
    /* 0x9B0 */ s8 field_0x9B0;
    /* 0x9B1 */ s8 field_0x9B1;
    /* 0x9B2 */ u8 field_0x9B2[0x9B4 - 0x9B2];
    /* 0x9B4 */ s32 field_0x9B4;
    /* 0x9B8 */ u8 mHasAttention;
    /* 0x9B9 */ u8 field_0x9B9;
    /* 0x9BA */ u8 field_0x9BA[0x9C0 - 0x9BA];
    /* 0x9C0 */ fpc_ProcID field_0x9C0;
    /* 0x9C4 */ s8 field_0x9C4;
    /* 0x9C5 */ u8 field_0x9C5[0x9C8 - 0x9C5];
    /* 0x9C8 */ ActionFunc mCurrActionFunc;
    /* 0x9D4 */ s8 field_0x9D4;
    /* 0x9D5 */ s8 field_0x9D5;
    /* 0x9D6 */ s8 field_0x9D6;
    /* 0x9D7 */ s8 field_0x9D7;
    /* 0x9D8 */ s16 field_0x9D8;
    /* 0x9DA */ s8 field_0x9DA;
    /* 0x9DB */ u8 field_0x9DB[0x9DD - 0x9DB];
    /* 0x9DD */ s8 mActionStatus;
    /* 0x9DE */ u8 field_0x9DE[0x9E0 - 0x9DE];
    /* 0x9E0 */ fpc_ProcID field_0x9E0;
};  // Size: 0x9E4

#endif /* D_A_NPC_BMSW_H */
