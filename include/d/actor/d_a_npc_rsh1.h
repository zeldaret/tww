#ifndef D_A_NPC_RSH1_H
#define D_A_NPC_RSH1_H

#include "d/d_lib.h"
#include "d/d_npc.h"
#include "d/d_shop.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Rsh1_c : public fopAc_ac_c {
public:
    static char m_arcname[];
public:
    void chkAction(int (daNpc_Rsh1_c::*)(void*)) {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Rsh1_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}
    void setShopIdx(int) {}

    void checkCreateInShopPlayer();
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
    void pathGet();
    void getAimShopPosIdx();
    void shopPosMove();
    void pathMove(int*);
    void wait01();
    void talk01();
    void getdemo_action(void*);
    void wait_action(void*);
    void pl_shop_out_action(void*);
    void evn_setAnm_init(int);
    void evn_talk_init(int);
    void evn_continue_talk_init(int);
    void evn_talk();
    void evn_turn_init(int);
    void evn_turn();
    void privateCut();
    void event_action(void*);
    bool dummy_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class field_0x290;
    /* 0x298 */ mDoExt_McaMorf* field_0x298;
    /* 0x29C */ u8 field_0x29C[0x2A8 - 0x29C];
    /* 0x2A8 */ mDoExt_btpAnm field_0x2A8;
    /* 0x2BC */ u8 field_0x2BC[0x2C4 - 0x2BC];
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
    /* 0x700 */ u8 field_0x700[0x708 - 0x700];
    /* 0x708 */ cXyz field_0x708[5];
    /* 0x744 */ u8 field_0x744[0x7B8 - 0x744];
    /* 0x7B8 */ ShopCam_action_c field_0x7B8;
    /* 0x810 */ ShopItems_c* mpShopItems;
    /* 0x814 */ ShopItems_c field_0x814[4];
    /* 0x924 */ u8 field_0x924[0x954 - 0x924];
    /* 0x954 */ ShopCursor_c* field_0x954;
    /* 0x958 */ s8 field_0x958;
    /* 0x959 */ u8 field_0x959[0x95E - 0x959];
    /* 0x95E */ s8 field_0x95E;
    /* 0x95F */ u8 field_0x95F[0x960 - 0x95F];
    /* 0x960 */ s8 field_0x960;
    /* 0x961 */ s8 field_0x961;
    /* 0x962 */ u8 field_0x962[0x968 - 0x962];
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
