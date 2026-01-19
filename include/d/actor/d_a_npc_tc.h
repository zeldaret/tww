#ifndef D_A_NPC_TC_H
#define D_A_NPC_TC_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

namespace daObjSmplbg { class Act_c; };

class daNpc_Tc_c : public fopNpc_npc_c {
public:

    typedef int (daNpc_Tc_c::*ActionFunc)(void*);
    daNpc_Tc_c();
    
    void getAttentionBasePos() {}
    void getEyePos() {}
    void incAttnSetCount() {}
    void setAction(ActionFunc, void*) {}

    fopAc_ac_c* _searchTower(fopAc_ac_c*);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void smoke_set(f32, f32, f32, f32, f32);
    void setAnm();
    void setTexAnm();
    void chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    void existTcMonument();
    void anmAtr(u16);
    void stopTower();
    void startTower();
    u16 next_msgStatusBlue(u32*);
    u16 next_msgStatusNormal(u32*);
    u16 next_msgStatus(u32*);
    void setFirstMsg(bool*, u32, u32);
    u32 getMsgNormal();
    u32 getMsgBlue();
    u32 getMsg();
    void getArg();
    void createInit();
    void searchStoolPos(void*, void*);
    void setAttention();
    void calcMove();
    void lookBack();
    void statusWait();
    void statusSit();
    void statusJump();
    void statusWalkToJail();
    void statusTalkNearJail();
    void statusWaitNearJail();
    void statusWalkToStool();
    void statusSitToStool();
    void statusTalk();
    void statusPayRupee();
    void statusDemoPayRupee();
    void statusGetRupee();
    void statusDemoGetRupee();
    void statusMonumentComplete();
    void statusDemoMonumentComplete();
    void statusDemoJump();
    void statusDemoRescue();
    void statusDemoTalk();
    void help_action(void*);
    void wait_action(void*);
    void calc_sitpos();
    void set_mtx();
    BOOL _draw();
    void setTower();
    BOOL _execute();
    BOOL _delete();
    bool isCreate();
    cPhs_State _create();
    BOOL _createHeap();
    u16 next_msgStatusNormal2(u32*);
    u32 getMsgNormal2();
    void setRupeeSizeMsg();
    void existUnknownCollectMap();
    void analysisCollectMap();
    void existKnownCollectMap();
    u16 next_msgStatusWhite(u32*);
    u32 getMsgWhite();
    u16 next_msgStatusRed(u32*);
    void setFinishMsg();
    u32 getMsgRed();
    void checkMonumentFee(u16, u16);
    void checkAllMonumentFee();
    void checkAllMonumentPay();
    void checkMonumentPay(u16, u16);
    void cutProc();
    void cutSitToJumpStart(int);
    void cutSitToJumpProc(int);
    void cutPresentStart(int);
    void cutPresentProc(int);
    void cutSetAnmStart(int);
    void cutSetAnmProc(int);
    void cutBackJumpStart(int);
    void cutBackJumpProc(int);
    void cutEffectStart(int);
    void cutEffectProc(int);
    void cutDoorOpenStart(int);
    void cutDoorOpenProc(int);
    void cutDoorCloseStart(int);
    void cutDoorCloseProc(int);
    void cutDoorClose2Start(int);
    void cutDoorClose2Proc(int);
    void cutPayStart(int);
    void cutPayProc(int);

public:
    /* 0x6C4 */ u8 field_0x6C4[0x6CF - 0x6C4];
    /* 0x6CF */ s8 field_0x6CF;
    /* 0x6D0 */ ActionFunc mCurrActionFunc;
    /* 0x6DC */ u8 field_0x6DC[0x6E0 - 0x6DC];
    /* 0x6E0 */ cXyz field_0x6E0;
    /* 0x6EC */ csXyz field_0x6EC;
    /* 0x6F2 */ u8 field_0x6F2[0x6F4 - 0x6F2];
    /* 0x6F4 */ dPa_smokeEcallBack mSmokeCallBack;
    /* 0x714 */ dPa_followEcallBack field_0x714;
    /* 0x728 */ dPa_followEcallBack field_0x728;
    /* 0x73C */ request_of_phase_process_class mPhs;
    /* 0x744 */ u32 mShadowId;
    /* 0x748 */ u8 field_0x748[0x74C - 0x748];
    /* 0x74C */ mDoExt_btpAnm mBtpAnm;
    /* 0x760 */ u8 field_0x760;
    /* 0x761 */ u8 field_0x761[0x764 - 0x761];
    /* 0x764 */ cXyz field_0x764;
    /* 0x770 */ cXyz field_0x770;
    /* 0x77C */ u8 field_0x77C[0x780 - 0x77C];
    /* 0x780 */ cXyz field_0x780;
    /* 0x78C */ u8 field_0x78C[0x790 - 0x78C];
    /* 0x790 */ csXyz field_0x790;
    /* 0x796 */ u8 field_0x796[0x798 - 0x796];
    /* 0x798 */ s8 field_0x798;
    /* 0x799 */ u8 field_0x799[0x79C - 0x799];
    /* 0x79C */ f32 field_0x79C;
    /* 0x7A0 */ cXyz field_0x7A0;
    /* 0x7AC */ cXyz field_0x7AC;
    /* 0x7B8 */ cXyz field_0x7B8;
    /* 0x7C4 */ cXyz field_0x7C4;
    /* 0x7D0 */ u8 field_0x7D0[0x7DC - 0x7D0];
    /* 0x7DC */ cXyz field_0x7DC;
    /* 0x7E8 */ bool field_0x7E8;
    /* 0x7E9 */ bool field_0x7E9;
    /* 0x7EA */ u8 field_0x7EA[0x7F1 - 0x7EA];
    /* 0x7F1 */ bool field_0x7F1;
    /* 0x7F2 */ bool field_0x7F2;
    /* 0x7F3 */ s8 field_0x7F3;
    /* 0x7F4 */ u8 field_0x7F4[0x7F6 - 0x7F4];
    /* 0x7F6 */ u8 field_0x7F6;
    /* 0x7F7 */ u8 field_0x7F7[0x7F9 - 0x7F7];
    /* 0x7F9 */ s8 field_0x7F9;
    /* 0x7FA */ u8 field_0x7FA[0x7FB - 0x7FA];
    /* 0x7FB */ u8 field_0x7FB;
    /* 0x7FC */ u8 field_0x7FC;
    /* 0x7FD */ u8 field_0x7FD[0x804 - 0x7FD];
    /* 0x804 */ daObjSmplbg::Act_c* m_tower_actor;
    /* 0x808 */ u8 field_0x808[0x812 - 0x808];
    /* 0x812 */ bool field_0x812;
    /* 0x813 */ bool field_0x813;
    /* 0x814 */ u8 field_0x814[0x81C - 0x814];
};  // Size: 0x81C
    // /* 0x804 */ daObjSmplbg::Act_c* m_tower_actor;
#endif /* D_A_NPC_TC_H */
