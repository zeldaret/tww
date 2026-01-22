#ifndef D_A_NPC_ZL1_H
#define D_A_NPC_ZL1_H

#include "d/d_npc.h"

class J3DMaterial;
class J3DNode;

class daNpc_Zl1_matAnm_c : public J3DMaterialAnm{
public:
    void clrMoveFlag() {field_0x7C = false;}
    f32& getNowOffsetX() {return mOffset.x;}
    f32& getNowOffsetY() {return mOffset.y;}
    void setMoveFlag() {field_0x7C = true;}

    daNpc_Zl1_matAnm_c();

    void calc(J3DMaterial*) const;

public:
    /* 0x6C */ cXy mOffset;
    /* 0x74 */ cXy field_0x74;
    /* 0x7C */ bool field_0x7C;
};  // Size: 0x7D

class daNpc_Zl1_c : public fopNpc_npc_c {
public:

    typedef int (daNpc_Zl1_c::*ActionFunc)(void*);

    struct anm_prm_c {
        s8 field_0x0;
        s8 field_0x1;
        f32 mMorf;
        f32 mPlaySpeed;
        int mLoopMode;
    };

    daNpc_Zl1_c();
    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    BOOL set_startPos(int);
    bool init_ZL1_0();
    bool init_ZL1_1();
    bool init_ZL1_2();
    bool init_ZL1_3();
    bool init_ZL1_4();
    bool init_ZL1_5();
    bool init_ZL1_6();
    bool init_ZL1_7();
    bool createInit();
    void play_animation();
    bool swoon_OnShip();
    void setMtx(bool);
    char* bckResID(int);
    char* btpResID(int);
    char* btkResID(int);
    bool setBtp(s8, bool);
    void setMat();
    bool setBtk(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void eye_ctrl();
    void play_btk_anm();
    void setAnm_anm(daNpc_Zl1_c::anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_ZL1_2();
    u32 getMsg_ZL1_4();
    u32 getMsg_ZL1_5();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    bool partner_search_sub(void* (*)(void*, void*));
    void partner_search();
    void setEyeCtrl();
    void clrEyeCtrl();
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    f32 get_prmFloat(f32*, f32);
    cXyz set_LightPos();
    void init_Light();
    void incEnvironment();
    void decEnvironment();
    void darkProc();
    void cut_init_LOK_PLYER(int);
    BOOL cut_move_LOK_PLYER();
    void cut_init_LOK_PARTNER(int);
    BOOL cut_move_LOK_PARTNER();
    void cut_init_CHG_ANM_ATR(int);
    BOOL cut_move_CHG_ANM_ATR();
    void cut_init_PLYER_TRN_PARTNER(int);
    BOOL cut_move_PLYER_TRN_PARTNER();
    void cut_init_PLYER_TRN_TETRA(int);
    BOOL cut_move_PLYER_TRN_TETRA();
    void cut_init_MAJYU_START(int);
    BOOL cut_move_MAJYU_START();
    void cut_init_OKIRU(int);
    BOOL cut_move_OKIRU();
    void cut_init_OKIRU_2(int);
    BOOL cut_move_OKIRU_2();
    void cut_init_DRW_ONOFF(int);
    BOOL cut_move_DRW_ONOFF();
    void cut_init_PLYER_DRW_ONOFF(int);
    BOOL cut_move_PLYER_DRW_ONOFF();
    void cut_init_JMP_OFF(int);
    BOOL cut_move_JMP_OFF();
    void cut_init_OMAMORI_ONOFF(int);
    BOOL cut_move_OMAMORI_ONOFF();
    void cut_init_SURPRISED(int);
    BOOL cut_move_SURPRISED();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    bool set_action(ActionFunc, void*);
    void setStt(s8);
    bool chk_areaIN(f32, f32, s16, cXyz);
    void setWaterRipple();
    void setWaterSplash();
#if VERSION != VERSION_DEMO
    void set_simpleLand(bool);
#else
    void set_simpleLand();
#endif
    void setEff();
    BOOL setFrontWallType();
    bool move_jmp();
    cXyz kyoroPos(int);
    BOOL kyorokyoro();
    BOOL wait_1();
    BOOL talk_1();
    BOOL demo_1();
    BOOL demo_2();
    BOOL demo_3();
    BOOL demo_4();
    BOOL optn_1();
    BOOL optn_2();
    BOOL optn_3();
    int wait_action1(void*);
    int demo_action1(void*);
    int demo_action2(void*);
    int optn_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL itemCreateHeap();
    BOOL CreateHeap();
public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ u8 field_0x6CE[0x6D0 - 0x6CE];
    /* 0x6D0 */ J3DModel* mpModel;
    /* 0x6D4 */ daNpc_Zl1_matAnm_c* field_0x6D4[2];
    /* 0x6DC */ char mArcName[3];
    /* 0x6E0 */ u32 mShadowId;
    /* 0x6E4 */ u8 field_0x6E4[0x6E8 - 0x6E4];
    /* 0x6E8 */ mDoExt_btkAnm mBtkAnm;
    /* 0x6FC */ u8 mBtkAnmFrame;
    /* 0x700 */ mDoExt_btpAnm mBtpAnm;
    /* 0x714 */ u8 mBtpAnmFrame;
    /* 0x716 */ s16 mTimer;
    /* 0x718 */ ActionFunc mCurrActionFunc;
    /* 0x724 */ fpc_ProcID mProcId1;
    /* 0x728 */ fpc_ProcID mProcId2;
    /* 0x72C */ cXyz field_0x72C;
    /* 0x738 */ csXyz field_0x738;
    /* 0x73E */ csXyz field_0x73E;
    /* 0x744 */ csXyz field_0x744;
    /* 0x74A */ u8 field_0x74A[0x74C - 0x74A];
    /* 0x74C */ cXyz field_0x74C;
    /* 0x758 */ cXyz field_0x758;
    /* 0x764 */ cXyz field_0x764;
    /* 0x770 */ cXyz field_0x770;
    /* 0x77C */ cXyz field_0x77C;
    /* 0x788 */ f32 mRatio;
    /* 0x78C */ f32 mFrame;
    /* 0x790 */ u8 field_0x790[0x794 - 0x790];
    /* 0x794 */ csXyz field_0x794;
    /* 0x79C */ BOOL field_0x79C;
    /* 0x7A0 */ s16 mEventIdx[6];
    /* 0x7AC */ u8 field_0x7AC[0x7AE - 0x7AC];
    /* 0x7AE */ s16 field_0x7AE;
    /* 0x7B0 */ s16 field_0x7B0;
    /* 0x7B2 */ s16 field_0x7B2;
    /* 0x7B4 */ u8 field_0x7B4[0x7B6 - 0x7B4];
    /* 0x7B6 */ s16 field_0x7B6;
    /* 0x7B8 */ s16 field_0x7B8;
    /* 0x7BA */ s16 field_0x7BA;
    /* 0x7BC */ s16 field_0x7BC;
    /* 0x7BE */ u8 field_0x7BE[0x7C0 - 0x7BE];
    /* 0x7C0 */ s16 field_0x7C0;
    /* 0x7C2 */ s8 field_0x7C2;
    /* 0x7C3 */ s8 field_0x7C3;
    /* 0x7C4 */ s8 field_0x7C4;
    /* 0x7C5 */ u8 mItemNo;
    /* 0x7C6 */ bool field_0x7C6;
    /* 0x7C7 */ bool field_0x7C7;
    /* 0x7C8 */ bool field_0x7C8;
    /* 0x7C9 */ bool field_0x7C9;
    /* 0x7CA */ bool field_0x7CA;
    /* 0x7CB */ bool field_0x7CB;
    /* 0x7CC */ bool field_0x7CC;
    /* 0x7CD */ u8 field_0x7CD[0x7CE - 0x7CD];
    /* 0x7CE */ bool field_0x7CE;
    /* 0x7CF */ bool mStateIsComplaete;
    /* 0x7D0 */ bool field_0x7D0;
    /* 0x7D1 */ bool field_0x7D1;
    /* 0x7D2 */ bool field_0x7D2;
    /* 0x7D3 */ bool field_0x7D3;
    /* 0x7D4 */ bool field_0x7D4;
    /* 0x7D5 */ bool field_0x7D5;
    /* 0x7D6 */ bool mHasAttention;
    /* 0x7D7 */ bool field_0x7D7;
    /* 0x7D8 */ bool field_0x7D8;
    /* 0x7D9 */ bool field_0x7D9;
    /* 0x7DC */ dPa_rippleEcallBack mRippleCallBack;
    /* 0x7F0 */ LIGHT_INFLUENCE mLightInfluence1;
    /* 0x810 */ LIGHT_INFLUENCE mLightInfluence2;
    /* 0x830 */ cXyz field_0x830;
    /* 0x83C */ s16 field_0x83C;
    /* 0x83E */ s16 field_0x83E;
    /* 0x840 */ s16 field_0x840;
    /* 0x842 */ s16 field_0x842;
    /* 0x844 */ s8 mActIdx;
    /* 0x845 */ u8 field_0x845;
    /* 0x846 */ u8 field_0x846;
    /* 0x847 */ s8 field_0x847;
    /* 0x848 */ s8 field_0x848;
    /* 0x849 */ s8 field_0x849;
    /* 0x84A */ s8 field_0x84A;
    /* 0x84B */ s8 field_0x84B;
    /* 0x84C */ s8 field_0x84C;
    /* 0x84D */ s8 field_0x84D;
    /* 0x84E */ s8 field_0x84E;
    /* 0x84F */ s8 field_0x84F;
    /* 0x850 */ s8 field_0x850;
    /* 0x851 */ s8 field_0x851;
    /* 0x854 */ J3DJoint* mJoint1;
    /* 0x858 */ J3DJoint* mJoint2;
    /* 0x85C */ J3DJoint* mJoint3;
    /* 0x860 */ J3DMaterial* field_0x860[6];
    /* 0x878 */ J3DMaterial* field_0x878[6];
    /* 0x890 */ J3DShape* field_0x890[6];
    /* 0x8A8 */ J3DShape* field_0x8A8[6];
    /* 0x8C0 */ mDoExt_offCupOnAupPacket mOffCupOnAupPacket1;
    /* 0x8D0 */ mDoExt_offCupOnAupPacket mOffCupOnAupPacket2;
    /* 0x8E0 */ mDoExt_onCupOffAupPacket mOnCupOffAupPacket1;
    /* 0x8F0 */ mDoExt_onCupOffAupPacket mOnCupOffAupPacket2;
};  // Size: 0x900

#endif /* D_A_NPC_ZL1_H */
