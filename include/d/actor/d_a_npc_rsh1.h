#ifndef D_A_NPC_RSH1_H
#define D_A_NPC_RSH1_H

#include "d/d_lib.h"
#include "d/d_npc.h"
#include "d/d_shop.h"
#include "f_op/f_op_actor.h"

class daNpc_Rsh1_c : public fopAc_ac_c {
public:
    typedef BOOL (daNpc_Rsh1_c::*ProcFunc)(void*);
    static char m_arcname[];
public:
    bool chkAction(ProcFunc i_funcP) { return mCurrProc == i_funcP; }
    s8 getBackboneJntNum() { return m_backbone_jnt_num; }
    s16 getBackbone_x() { return mJntCtrl.getBackbone_x(); }
    s16 getBackbone_y() { return mJntCtrl.getBackbone_y(); }
    s8 getHeadJntNum() { return m_head_jnt_num; }
    s16 getHead_x() { return mJntCtrl.getHead_x(); }
    s16 getHead_y() { return mJntCtrl.getHead_y(); }
    void incAttnSetCount() {}
    void setAction(ProcFunc i_funcP, void* i_actParam) {
        if (mCurrProc != i_funcP) {
            if (mCurrProc) {
                field_0x960 = -1;
                (this->*mCurrProc)(NULL);
            }
            mCurrProc = i_funcP;
            field_0x960 = 0;
            (this->*mCurrProc)(i_actParam);
        }
    }
    void setAttentionBasePos(cXyz i_attBasePos) { field_0x758 = i_attBasePos; }
    void setEyePos(cXyz i_eyePos) { eyePos = i_eyePos; }
    void setShopIdx(int) {}

    BOOL checkCreateInShopPlayer();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void setTexAnm(signed char);
    void setAnmFromMsgTag();
    bool chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void setCollision();
    void talkInit();
    u16 normal_talk();
    u16 shop_talk();
    u16 talk();
    BOOL CreateInit();
    void createShopList();
    void setAttention();
    void lookBack();
    bool pathGet();
    int getAimShopPosIdx();
    BOOL shopPosMove();
    BOOL pathMove(int*);
    bool wait01();
    bool talk01();
    BOOL getdemo_action(void*);
    BOOL wait_action(void*);
    BOOL pl_shop_out_action(void*);
    bool evn_setAnm_init(int);
    bool evn_talk_init(int);
    bool evn_continue_talk_init(int);
    BOOL evn_talk();
    bool evn_turn_init(int);
    BOOL evn_turn();
    bool privateCut();
    BOOL event_action(void*);
    BOOL dummy_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ u32 field_0x29C;
    /* 0x2A0 */ u8 field_0x2A0[0x2A4 - 0x2A0];
    /* 0x2A4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2A8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2BC */ u8 field_0x2BC;
    /* 0x2BD */ u8 field_0x2BD[0x2BE - 0x2BD];
    /* 0x2BE */ s16 field_0x2BE;
    /* 0x2C0 */ u8 field_0x2C0[0x2C4 - 0x2C0];
    /* 0x2C4 */ dBgS_ObjAcch mAcch;
    /* 0x488 */ dBgS_AcchCir mAcchCir;
    /* 0x4C8 */ dCcD_Stts mStts;
    /* 0x504 */ dCcD_Cyl mCyl;
    /* 0x634 */ s8 m_head_jnt_num;
    /* 0x635 */ s8 m_backbone_jnt_num;
    /* 0x636 */ u8 field_0x636[0x638 - 0x636];
    /* 0x638 */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x66C */ dNpc_EventCut_c mEventCut;
    /* 0x6D8 */ STControl mSTControl;
    /* 0x700 */ dPath* mpPath;
    /* 0x704 */ s8 field_0x704;
    /* 0x705 */ u8 field_0x705[0x708 - 0x705];
    /* 0x708 */ cXyz field_0x708[5];
    /* 0x744 */ s8 field_0x744[5];
    /* 0x749 */ s8 field_0x749;
    /* 0x74A */ u8 field_0x74A[0x758 - 0x74A];
    /* 0x758 */ cXyz field_0x758;
    /* 0x764 */ s16 field_0x764;
    /* 0x766 */ csXyz field_0x766;
    /* 0x76C */ u8 field_0x76C[0x76E - 0x76C];
    /* 0x76E */ s8 field_0x76E;
    /* 0x76F */ u8 field_0x76F;
    /* 0x770 */ u8 field_0x770;
    /* 0x771 */ u8 field_0x771;
    /* 0x772 */ u8 field_0x772[0x774 - 0x772];
    /* 0x774 */ f32 field_0x774;
    /* 0x778 */ u32 field_0x778;
    /* 0x77C */ u32 field_0x77C;
    /* 0x780 */ u32 field_0x780;
    /* 0x784 */ u32 field_0x784;
    /* 0x788 */ int field_0x788;
    /* 0x78C */ s32 field_0x78C;
    /* 0x790 */ s16 field_0x790;
    /* 0x792 */ u8 field_0x792;
    /* 0x793 */ u8 field_0x793;
    /* 0x794 */ cXyz field_0x794;
    /* 0x7A0 */ cXyz field_0x7A0;
    /* 0x7AC */ ProcFunc mCurrProc;
    /* 0x7B8 */ ShopCam_action_c mShopCamAct;
    /* 0x810 */ ShopItems_c* mpShopItems;
    /* 0x814 */ ShopItems_c mShopItemsArr[4];
    /* 0x924 */ __shop_items_set_data* mShopItemDataPtrs[12];
    /* 0x954 */ ShopCursor_c* mpShopCursor;
    /* 0x958 */ s8 field_0x958;
    /* 0x959 */ s8 field_0x959;
    /* 0x95A */ s8 field_0x95A;
    /* 0x95B */ s8 field_0x95B;
    /* 0x95C */ s8 field_0x95C;
    /* 0x95D */ u8 field_0x95D;
    /* 0x95E */ s8 field_0x95E;
    /* 0x95F */ u8 field_0x95F[0x960 - 0x95F];
    /* 0x960 */ s8 field_0x960;
    /* 0x961 */ s8 field_0x961;
    /* 0x962 */ s8 field_0x962;
    /* 0x963 */ u8 field_0x963;
    /* 0x964 */ u8 field_0x964[0x968 - 0x964];
};  // Size: 0x968

#endif /* D_A_NPC_RSH1_H */
