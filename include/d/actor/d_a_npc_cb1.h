#ifndef D_A_NPC_CB1_H
#define D_A_NPC_CB1_H

#include "d/actor/d_a_player_npc.h"
#include "d/d_com_inf_game.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Cb1_c : public daPy_npc_c {
public:
    typedef int (daNpc_Cb1_c::*ActionFunc_t)(void*);

    enum {
        ANM_00 = 0x00,
        ANM_08 = 0x08,
        ANM_0D = 0x0D,
    };

    class AnmData {
    public:
        /* 0x00 */ s8 field_0x00;
        /* 0x01 */ u8 field_0x01;
        /* 0x02 */ s8 field_0x02;
        /* 0x03 */ s8 field_0x03;
        /* 0x04 */ s8 field_0x04;
        /* 0x05 */ s8 field_0x05;
    }; // Size: 0x06

    // daPy_py_c virtuals
    f32 getBaseAnimeFrame() { return 0.0f; }
    f32 getBaseAnimeFrameRate() { return 1.0f; }
    MtxP getLeftHandMatrix() { return cullMtx; }
    MtxP getRightHandMatrix() { return cullMtx; }

    s16 XyCheckCB(int i_itemBtn) {
        if(dComIfGp_getSelectItem(i_itemBtn) == dItem_WIND_WAKER_e && dComIfGs_isEventBit(0x1880)) {
            return true;
        }

        return false;
    }
    s16 XyEventCB(int) { return mEventIdx[2]; }
    BOOL chkNpcAction(ActionFunc_t action) { return mNpcAction == action; }
    BOOL chkPlayerAction(ActionFunc_t action) { return mPlayerAction == action; }
    s16 getBackbone_x() { return mJntCtrl.getBackbone_x(); }
    s16 getBackbone_y() { return mJntCtrl.getBackbone_y(); }
    s16 getHead_y() { return mJntCtrl.getHead_y(); }
    cXyz& getEyePos() { return m880; }
    f32 getGroundY() { return mAcch.GetGroundH(); }
    cXyz& getNusSpeed() { return m8A4; } // not entirely sure about this one
    cXyz& getNutPos() { return m898; } // not entirely sure about this one
    s16 getWork3() { return m8FA; }
    void incAttnSetCount() {
        if(m8D9 != 0xFF) {
            m8D9 += 1;
        }
    }
    BOOL isTypeBossDie() { return fopAcM_GetParam(this) == 0; }
    BOOL isTypeForest() { return fopAcM_GetParam(this) == 1; }
    BOOL isTypeWaterFall() { return fopAcM_GetParam(this) == 2; }
    BOOL isTypeEkaze() { return fopAcM_GetParam(this) == 3; }
    BOOL isTypeKaze() { return fopAcM_GetParam(this) == 4; }
    BOOL isTypeKazeBoss() { return fopAcM_GetParam(this) == 5; }
    BOOL isNoCarryAction() { return m_status & 0x01; }
    BOOL isTact() { return m_status & 0x02; }
    BOOL isTactCorrect() { return m_status & 0x04; }
    BOOL isTactCancel() { return m_status & 0x08; }
    BOOL isMusic() { return m_status & 0x10; }
    BOOL isNut() { return m_status & 0x20; }
    BOOL isShipRide() { return m_status & 0x40; }
    BOOL isPlayerFind() { return m_status & 0x80; }
    void offNoCarryAction() { m_status &= ~0x01; }
    void offTact() { m_status &= ~0x02; }
    void offTactCorrect() { m_status &= ~0x04; }
    void offTactCancel() { m_status &= ~0x08; }
    void offMusic() { m_status &= ~0x10; }
    void offNut() { m_status &= ~0x20; }
    void offShipRide() { m_status &= ~0x40; }
    void offPlayerFind() { m_status &= ~0x80; }
    void noCarryAction() { m_status |= 0x01; }
    void onTact() { m_status |= 0x02; }
    void onTactCorrect() { m_status |= 0x04; }
    void onTactCancel() { m_status |= 0x08; }
    void onMusic() { m_status |= 0x10; }
    void onNut() { m_status |= 0x20; }
    void onShipRide() { m_status |= 0x40; }
    void onPlayerFind() { m_status |= 0x80; }
    void restartPoint(s16 point) {
        setPointRestart(point, 1);
        setWaitNpcAction(NULL);
    }
    
    static bool m_playerRoom;
    static bool m_flying;
    static s16 m_flyingTimer;
    static u16 m_status;

    static s16 getMaxFlyingTimer();
    
    s16 getFlyingTimer() { return m_flyingTimer; }
    void setFlyingTimer(s16 time) { m_flyingTimer = time; }
    static bool isFlying() { return m_flying; }
    void onFlying() { m_flying = true; }
    void offFlying() { m_flying = false; }
    static bool isPlayerRoom() { return m_playerRoom; }
    void onPlayerRoom() { m_playerRoom = true; }
    void offPlayerRoom() { m_playerRoom = false; }
    
    daNpc_Cb1_c() {
        m8DB = 0xFF;
    }
    ~daNpc_Cb1_c();
    BOOL isTagCheckOK();
    void setMessageAnimation(u8);
    cPhs_State create();
    BOOL createHeap();
    BOOL setAction(ActionFunc_t*, ActionFunc_t, void*);
    void setWaitAction(void*);
    void setWaitNpcAction(void*);
    void npcAction(void*);
    void setNpcAction(ActionFunc_t, void*);
    void playerAction(void*);
    void setPlayerAction(ActionFunc_t, void*);
    s16 getStickAngY();
    int calcStickPos(s16, cXyz*);
    BOOL flyCheck();
    void checkLanding();
    void breaking();
    BOOL flyAction(int, f32, s16, int);
    BOOL walkAction(f32, f32, s16);
    void returnLinkPlayer();
    BOOL isFlyAction();
    BOOL sowCheck();
    BOOL shipRideCheck();
    BOOL eventProc();
    BOOL evCheckDisp(int);
    void evInitWait(int);
    BOOL evActWait(int);
    void evInitMsgSet(int);
    BOOL evActMsgSet(int);
    void evInitMsgEnd(int);
    BOOL evActMsgEnd(int);
    void evInitMovePos(int);
    BOOL evActMovePos(int);
    void evInitOffsetLink(int);
    BOOL evActOffsetLink(int);
    void evInitWalk(int);
    BOOL evActWalk(int);
    void evInitToLink(int);
    BOOL evActToLink(int);
    void evInitTact(int);
    BOOL evActTact(int);
    void evInitCelloPlay(int);
    BOOL evActCelloPlay(int);
    void evInitTurn(int);
    BOOL evActTurn(int);
    void evInitSow(int);
    BOOL evActSow(int);
    void evInitSetAnm(int);
    BOOL evActSetAnm(int);
    void evInitSetGoal(int);
    BOOL evActSetGoal(int);
    void evInitWarp(int);
    BOOL evActWarp(int);
    void evInitEnd(int);
    BOOL evActEnd(int);
    u8 getAnmType(int);
    BOOL initTalk();
    BOOL execTalk(int);
    BOOL waitNpcAction(void*);
    BOOL talkNpcAction(void*);
    BOOL carryNpcAction(void*);
    BOOL flyNpcAction(void*);
    void routeAngCheck(cXyz&, s16*);
    void routeWallCheck(cXyz&, cXyz&, s16*);
    f32 checkForwardGroundY(s16);
    f32 checkWallJump(s16);
    BOOL chkWallHit();
    BOOL routeCheck(f32, s16*);
    BOOL searchNpcAction(void*);
    BOOL hitNpcAction(void*);
    BOOL jumpNpcAction(void*);
    BOOL rescueNpcAction(void*);
    BOOL musicNpcAction(void*);
    BOOL shipNpcAction(void*);
    BOOL waitPlayerAction(void*);
    BOOL walkPlayerAction(void*);
    BOOL hitPlayerAction(void*);
    BOOL jumpPlayerAction(void*);
    BOOL flyPlayerAction(void*);
    BOOL carryPlayerAction(void*);
    BOOL calcFlyingTimer();
    void initAnm(s8, int);
    void musicPlay();
    void musicStop();
    BOOL setAnm(u8);
    void playAnm();
    BOOL chkAttention(f32, s32);
    void carryCheck();
    void eventOrder();
    void checkOrder();
    BOOL checkCommandTalk();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void lookBack(int);
    void setBaseMtx();
    BOOL init();
    BOOL draw();
    BOOL execute();

private:
    /* 0x4EC */ request_of_phase_process_class mPhs;
    /* 0x4F4 */ mDoExt_McaMorf* mpMorf;
    /* 0x4F8 */ u32 mShadowId;
    /* 0x4FC */ J3DModel* mpStickModel;
    /* 0x500 */ J3DModel* mpCelloModel;
    /* 0x504 */ J3DModel* mpFaceModel;
    /* 0x508 */ J3DModel* mpPropellerModel;
    /* 0x50C */ J3DModel* mpNutModel;
    /* 0x510 */ mDoExt_bckAnm mPropellerBckAnim;
    /* 0x520 */ mDoExt_bckAnm mNutBckAnim;
    /* 0x530 */ dBgS_AcchCir mAcchCir[2];
    /* 0x5B0 */ dCcD_Stts m5B0;
    /* 0x5EC */ dCcD_Cyl m5EC;
    /* 0x71C */ dCcD_Cyl field_0x71C;
    /* 0x84C */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x880 */ cXyz m880;
    /* 0x88C */ cXyz m88C;
    /* 0x898 */ cXyz m898;
    /* 0x8A4 */ cXyz m8A4;
    /* 0x8B0 */ f32 m8B0;
    /* 0x8B4 */ ActionFunc_t mPlayerAction;
    /* 0x8C0 */ ActionFunc_t mNpcAction;
    /* 0x8CC */ u32 m8CC;
    /* 0x8D0 */ s16 m8D0;
    /* 0x8D2 */ s8 m_backbone_jnt_num;
    /* 0x8D3 */ s8 m_armRend_jnt_num;
    /* 0x8D4 */ s8 m_armL2_jnt_num;
    /* 0x8D5 */ s8 m_nut_jnt_num;
    /* 0x8D6 */ s8 m_center_jnt_num;
    /* 0x8D7 */ s8 m8D7;
    /* 0x8D8 */ s8 m8D8;
    /* 0x8D9 */ u8 m8D9;
    /* 0x8DA */ u8 m8DA;
    /* 0x8DB */ u8 m8DB;
    /* 0x8DC */ s8 m8DC;
    /* 0x8DD */ s8 m8DD;
    /* 0x8DE */ u8 m8DE;
    /* 0x8DF */ u8 m8DF;
    /* 0x8E0 */ u8 m8E0;
    /* 0x8E1 */ s8 m8E1;
    /* 0x8E2 */ u8 m8E2;
    /* 0x8E3 */ s8 m8E3;
    /* 0x8E4 */ s16 mEventIdx[5];
    /* 0x8EE */ s16 m8EE;
    /* 0x8F0 */ s8 m8F0;
    /* 0x8F1 */ s8 m8F1;
    /* 0x8F2 */ s8 m8F2;
    /* 0x8F3 */ u8 m8F3;
    /* 0x8F4 */ s16 m8F4;
    /* 0x8F6 */ s16 m8F6;
    /* 0x8F8 */ s16 m8F8;
    /* 0x8FA */ s16 m8FA;
    /* 0x8FC */ f32 m8FC;
    /* 0x900 */ f32 m900;
    /* 0x904 */ cXyz m904;
    /* 0x910 */ cXyz m910;
    /* 0x91C */ cXyz m91C;
    /* 0x928 */ cBgS_PolyInfo m928;

    static AnmData anmTblData[];
    static s8 anmPrmData[];
    
    typedef void(daNpc_Cb1_c::*ev_init_func_t)(int);
    typedef BOOL(daNpc_Cb1_c::*ev_run_func_t)(int);
    struct mode_entry_t {
        ev_init_func_t init;
        ev_run_func_t run;
    };

    static mode_entry_t m_evProcTbl[];
};

class daNpc_Cb1_HIO_c : public JORReflexible {
public:
    daNpc_Cb1_HIO_c();
    virtual ~daNpc_Cb1_HIO_c() {}

public:
    /* 0x04 */ s8 field_0x04;
    /* 0x08 */ dNpc_HIO_c field_0x08;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ u8 field_0x94[4];
    /* 0x98 */ f32 field_0x98;
    /* 0x9C */ f32 field_0x9C;
    /* 0xA0 */ f32 field_0xA0;
    /* 0xA4 */ f32 field_0xA4;
    /* 0xA8 */ f32 field_0xA8;
    /* 0xAC */ f32 field_0xAC;
    /* 0xB0 */ f32 field_0xB0;
    /* 0xB4 */ f32 field_0xB4;
    /* 0xB8 */ f32 field_0xB8;
    /* 0xBC */ f32 field_0xBC;
    /* 0xC0 */ f32 field_0xC0;
    /* 0xC4 */ f32 field_0xC4;
    /* 0xC8 */ s16 field_0xC8;
    /* 0xCA */ s16 field_0xCA;
    /* 0xCC */ s16 field_0xCC;
    /* 0xCE */ s16 field_0xCE;
    /* 0xD0 */ s16 field_0xD0;
    /* 0xD2 */ s16 field_0xD2;
    /* 0xD4 */ s16 field_0xD4;
    /* 0xD6 */ s16 field_0xD6;
    /* 0xD8 */ s16 field_0xD8;
    /* 0xDA */ s16 field_0xDA;
    /* 0xDC */ s16 field_0xDC;
    /* 0xDE */ s16 field_0xDE;
    /* 0xE0 */ s16 field_0xE0;
    /* 0xE2 */ s16 field_0xE2;
    /* 0xE4 */ s16 field_0xE4;
    /* 0xE6 */ s16 field_0xE6;
    /* 0xE8 */ s16 field_0xE8;
    /* 0xEA */ s16 field_0xEA;
    /* 0xEC */ s16 field_0xEC;
    /* 0xEE */ u8 field_0xEE;
    /* 0xEF */ u8 field_0xEF;
}; // Size: 0xF0

#endif /* D_A_NPC_CB1_H */
