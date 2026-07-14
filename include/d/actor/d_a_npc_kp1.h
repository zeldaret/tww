#ifndef D_A_NPC_KP1_H
#define D_A_NPC_KP1_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class J3DAnmTexPattern;
class J3DModel;

class daNpc_Kp1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        /* 0x0 */ s8 field_0x0;
        /* 0x1 */ s8 field_0x1;
        /* 0x2 */ s16 field_0x2;
        /* 0x4 */ f32 field_0x4;
        /* 0x8 */ f32 field_0x8;
        /* 0xC */ s32 field_0xC;
    };

    enum Animation {
        ANM_END = 6,
    };

    enum TexPattern {
        TEXPATTERN_END = 2,
    };

    Vec* getAttPos() { return &mAttPos; }
    s8 getBackboneJntNum() { return m_backbone_jnt_num; }
    s16 getBackbone_x() { return m_jnt.getBackbone_x(); }
    s16 getBackbone_y() { return m_jnt.getBackbone_y(); }
    Vec* getEyePos() { return &mEyePos; }
    s8 getHeadJntNum() { return m_head_jnt_num; }
    s16 getHead_x() { return m_jnt.getHead_x(); }
    s16 getHead_y() { return m_jnt.getHead_y(); }

    s32 createInit();
    void setMtx();
    bool anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(signed char);
    bool init_btp(bool, int);
    bool initTexPatternAnm(bool);
    void playTexPatternAnm();
    s32 setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void setStt(signed char);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    bool chkAttention();
    void setAttention();
    void chk_talk();
    bool decideType(int);
    void event_actionInit(int);
    void event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    void set_action(int (daNpc_Kp1_c::*)(void*), void*);
    void wait01();
    void talk01();
    void wait_action1(void*);
    BOOL demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhase; // 0x8
    /* 0x6CC */ s8 m_head_jnt_num;
    /* 0x6CD */ s8 m_backbone_jnt_num;
    /* 0x6CE */ s8 field_0x6CE;
    /* 0x6D0 */ J3DModel* field_0x6D0;
    /* 0x6D4 */ J3DModel* field_0x6D4;
    /* 0x6D8 */ u8 field_0x6D8;
    /* 0x6D9 */ u8 field_0x6D9[0x6E0 - 0x6D9];
    /* 0x6E0 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6E4 */ mDoExt_btpAnm field_0x6E4;
    /* 0x6F8 */ u8 field_0x6F8;
    /* 0x6FA */ s16 field_0x6FA;
    /* 0x6FC */ u8 field_0x6FC[0x708 - 0x6FC];
    /* 0x708 */ dNpc_EventCut_c mEventCut;
    /* 0x774 */ u8 field_0x774[0x788 - 0x774];
    /* 0x788 */ cXyz mAttPos;
    /* 0x794 */ cXyz mEyePos;
    /* 0x7A0 */ cXyz field_0x7A0;
    /* 0x7AC */ f32 field_0x7AC;
    /* 0x7B0 */ u8 field_0x7B0[0x7BC - 0x7B0];
    /* 0x7BC */ s8 field_0x7BC;
    /* 0x7BD */ s8 field_0x7BD;
    /* 0x7BE */ u8 field_0x7BE;
    /* 0x7BF */ u8 field_0x7BF;
    /* 0x7C0 */ u8 field_0x7C0;
    /* 0x7C1 */ u8 field_0x7C1;
    /* 0x7C2 */ u8 field_0x7C2;
    /* 0x7C3 */ u8 field_0x7C3;
    /* 0x7C4 */ int field_0x7C4;
    /* 0x7C8 */ int field_0x7C8;
    /* 0x7CC */ u8 field_0x7CC;
    /* 0x7CD */ s8 field_0x7CD;
    /* 0x7CE */ s8 field_0x7CE;
    /* 0x7CF */ s8 field_0x7CF;
    /* 0x7D0 */ s8 field_0x7D0;
    /* 0x7D1 */ s8 field_0x7D1;
    /* 0x7D2 */ s8 field_0x7D2;
    /* 0x7D3 */ u8 field_0x7D3;
    /* 0x7D4 */ s8 field_0x7D4;
    /* 0x7D5 */ s8 field_0x7D5;
    /* 0x7D6 */ s8 field_0x7D6;
    /* 0x7D7 */ s8 field_0x7D7;
    /* 0x7D8 */ s8 field_0x7D8;
    /* 0x7D9 */ s8 field_0x7D9;
    /* 0x7DA */ s8 field_0x7DA;
    /* 0x7DB */ s8 field_0x7DB;
    /* 0x7DC */ s8 field_0x7DC;
    /* 0x7DD */ s8 field_0x7DD;
    /* 0x7DE */ u8 field_0x7DE[0x91A - 0x7DE];
    /* 0x91A */ u8 field_0x91A;
};

class daNpc_Kp1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        s16 field_0;
        s16 field_2;
        s16 field_4;
        s16 field_6;
        s16 field_8;
        s16 field_A;
        s16 field_C;
        s16 field_E;
        s16 field_10;
        s16 field_12;
        f32 mAttentionArrowYOffset;
        f32 field_18;
    }; // Size: 0x1C

    daNpc_Kp1_HIO_c();
    virtual ~daNpc_Kp1_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

#endif /* D_A_NPC_KP1_H */
