#ifndef D_A_NPC_RSH1_H
#define D_A_NPC_RSH1_H

#include "d/d_lib.h"
#include "d/d_npc.h"
#include "d/d_shop.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Rsh1_c : public fopAc_ac_c {
public:
    typedef BOOL (daNpc_Rsh1_c::*ProcFunc)(void*);
    static char m_arcname[];
public:
    bool chkAction(ProcFunc i_funcP) { return field_0x7AC == i_funcP; }
    s8 getBackboneJntNum() { return m_backbone_jnt_num; }
    s16 getBackbone_x() { return field_0x638.getBackbone_x(); }
    s16 getBackbone_y() { return field_0x638.getBackbone_y(); }
    s8 getHeadJntNum() { return m_head_jnt_num; }
    s16 getHead_x() { return field_0x638.getHead_x(); }
    s16 getHead_y() { return field_0x638.getHead_y(); }
    void incAttnSetCount() {}
    void setAction(ProcFunc i_funcP, void* i_actParam) {
        if (field_0x7AC != i_funcP) {
            if (field_0x7AC) {
                field_0x960 = -1;
                (this->*field_0x7AC)(NULL);
            }
            field_0x7AC = i_funcP;
            field_0x960 = 0;
            (this->*field_0x7AC)(i_actParam);
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
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void talkInit();
    void normal_talk();
    void shop_talk();
    void talk();
    BOOL CreateInit();
    void createShopList();
    void setAttention();
    void lookBack();
    bool pathGet();
    void getAimShopPosIdx();
    bool shopPosMove();
    void pathMove(int*);
    void wait01();
    void talk01();
    void getdemo_action(void*);
    BOOL wait_action(void*);
    BOOL pl_shop_out_action(void*);
    bool evn_setAnm_init(int);
    bool evn_talk_init(int);
    void evn_continue_talk_init(int);
    void evn_talk();
    bool evn_turn_init(int);
    bool evn_turn();
    void privateCut();
    void event_action(void*);
    BOOL dummy_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class field_0x290;
    /* 0x298 */ mDoExt_McaMorf* field_0x298;
    /* 0x29C */ u32 field_0x29C;
    /* 0x2A0 */ u8 field_0x2A0[0x2A4 - 0x2A0];
    /* 0x2A4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2A8 */ mDoExt_btpAnm field_0x2A8;
    /* 0x2BC */ u8 field_0x2BC;
    /* 0x2BD */ u8 field_0x2BD[0x2BE - 0x2BD];
    /* 0x2BE */ s16 field_0x2BE;
    /* 0x2C0 */ u8 field_0x2C0[0x2C4 - 0x2C0];
    /* 0x2C4 */ dBgS_ObjAcch field_0x2C4;
    /* 0x488 */ dBgS_AcchCir field_0x488;
    /* 0x4C8 */ dCcD_Stts field_0x4C8;
    /* 0x504 */ dCcD_Cyl field_0x504;
    /* 0x634 */ s8 m_head_jnt_num;
    /* 0x635 */ s8 m_backbone_jnt_num;
    /* 0x636 */ u8 field_0x636[0x638 - 0x636];
    /* 0x638 */ dNpc_JntCtrl_c field_0x638;
    /* 0x66C */ dNpc_EventCut_c field_0x66C;
    /* 0x6D8 */ STControl field_0x6D8;
    /* 0x700 */ dPath* field_0x700;
    /* 0x704 */ s8 field_0x704;
    /* 0x705 */ u8 field_0x705[0x708 - 0x705];
    /* 0x708 */ cXyz field_0x708[5];
    /* 0x744 */ s8 field_0x744[5];
    /* 0x749 */ s8 field_0x749;
    /* 0x74A */ u8 field_0x74A[0x758 - 0x74A];
    /* 0x758 */ cXyz field_0x758;
    /* 0x764 */ u8 field_0x764[0x766 - 0x764];
    /* 0x766 */ csXyz field_0x766;
    /* 0x76C */ u8 field_0x76C[0x76F - 0x76C];
    /* 0x76F */ u8 field_0x76F;
    /* 0x770 */ u8 field_0x770[0x778 - 0x770];
    /* 0x778 */ u32 field_0x778;
    /* 0x77C */ u8 field_0x77C[0x780 - 0x77C];
    /* 0x780 */ u32 field_0x780;
    /* 0x784 */ u32 field_0x784;
    /* 0x788 */ int field_0x788;
    /* 0x78C */ u8 field_0x78C[0x790 - 0x78C];
    /* 0x790 */ s16 field_0x790;
    /* 0x792 */ u8 field_0x792;
    /* 0x793 */ s8 field_0x793;
    /* 0x794 */ cXyz field_0x794;
    /* 0x7A0 */ cXyz field_0x7A0;
    /* 0x7AC */ ProcFunc field_0x7AC;
    /* 0x7B8 */ ShopCam_action_c field_0x7B8;
    /* 0x810 */ ShopItems_c* mpShopItems;
    /* 0x814 */ ShopItems_c field_0x814[4];
    /* 0x924 */ u8 field_0x924[0x954 - 0x924];
    /* 0x954 */ ShopCursor_c* field_0x954;
    /* 0x958 */ s8 field_0x958;
    /* 0x959 */ s8 field_0x959;
    /* 0x95A */ u8 field_0x95A[0x95B - 0x95A];
    /* 0x95B */ s8 field_0x95B;
    /* 0x95C */ u8 field_0x95C[0x95E - 0x95C];
    /* 0x95E */ s8 field_0x95E;
    /* 0x95F */ u8 field_0x95F[0x960 - 0x95F];
    /* 0x960 */ s8 field_0x960;
    /* 0x961 */ s8 field_0x961;
    /* 0x962 */ s8 field_0x962;
    /* 0x963 */ u8 field_0x963[0x968 - 0x963];
};  // Size: 0x968

class daNpc_Rsh1_HIO_c : public JORReflexible {
public:
    daNpc_Rsh1_HIO_c();
    virtual ~daNpc_Rsh1_HIO_c();

public:
    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05[0x08 - 0x05];
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ dNpc_HIO_c field_0x0C;
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
    /* 0x5C */ s8 field_0x5C;
    /* 0x5D */ s8 field_0x5D;
    /* 0x5E */ s8 field_0x5E;
    /* 0x5F */ s8 field_0x5F;
    /* 0x60 */ s8 field_0x60;
    /* 0x61 */ s8 field_0x61;
    /* 0x62 */ s8 field_0x62;
    /* 0x63 */ s8 field_0x63;
    /* 0x64 */ s8 field_0x64;
    /* 0x65 */ s8 field_0x65;
    /* 0x66 */ s8 field_0x66;
    /* 0x67 */ s8 field_0x67;
    /* 0x68 */ s8 field_0x68;
    /* 0x69 */ s8 field_0x69;
    /* 0x6A */ s8 field_0x6A;
    /* 0x6B */ s8 field_0x6B;
};  // Size: 0x6C

#endif /* D_A_NPC_RSH1_H */
