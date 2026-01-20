#ifndef D_A_NPC_LS1_H
#define D_A_NPC_LS1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class J3DMaterial;
class J3DNode;

class daNpc_Ls1_matAnm_c : public J3DMaterialAnm {
public:
    daNpc_Ls1_matAnm_c();
    void clrMoveFlag() { field_0x7C = 0; }
    f32& getNowOffsetX() { return field_0x6C; }
    f32& getNowOffsetY() { return field_0x70; }
    void setMoveFlag() { field_0x7C = 1; }

    void calc(J3DMaterial*) const;

public:
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ u8 field_0x74[0x7C - 0x74];
    /* 0x7C */ u8 field_0x7C;
    /* 0x7D */ u8 field_0x7D[0x80 - 0x7D];
};  // Size: 0x80

class daNpc_Ls1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Ls1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 mBckResIndex;
        /* 0x01 */ s8 mResIndex;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };  // Size: 0x10

    inline daNpc_Ls1_c();

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void _nodeCB_Hand_L(J3DNode*, J3DModel*);
    void _nodeCB_Hand_R(J3DNode*, J3DModel*);
    void _Ls_hand_nodeCB_Hand_L(J3DNode*, J3DModel*);
    void _Ls_hand_nodeCB_Hand_R(J3DNode*, J3DModel*);
    bool init_LS1_0();
    bool init_LS1_1();
    bool init_LS1_2();
    bool init_LS1_3();
    bool init_LS1_4();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    int btkResID(int);
    bool setBtp(s8, bool);
    void setMat();
    bool setBtk(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void eye_ctrl();
    void play_btk_anm();
    void setAnm_anm(daNpc_Ls1_c::anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_LS1_0();
    u32 getMsg_LS1_3();
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
    void cut_init_LOK_PLYER(int);
    bool cut_move_LOK_PLYER();
    void cut_init_PLYER_MOV(int);
    bool cut_move_PLYER_MOV();
    void cut_init_WAI(int);
    bool cut_move_WAI();
    void cut_init_ANM_CHG(int);
    bool cut_move_ANM_CHG();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    bool chk_areaIN(f32, f32, s16, cXyz);
    cXyz get_playerEvnPos(int);
    bool chkTelescope_sph(cXyz, f32, f32);
    bool chkTelescope(cXyz, f32, f32);
    bool telescope_proc();
    BOOL wait_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL wait_4();
    BOOL talk_1();
    BOOL wait_action1(void*);
    BOOL demo_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL handCreateHeap();
    BOOL itemCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_L_jnt_num;
    /* 0x6CF */ s8 m_hnd_R_jnt_num;
    /* 0x6D0 */ J3DModel* mpTelescopeModel;
    /* 0x6D4 */ f32 mTelescopeScale;
    /* 0x6D8 */ daNpc_Ls1_matAnm_c* mpMatAnms[2];
    /* 0x6E0 */ char mArcName[3];
    /* 0x6E3 */ u8 m6E3[0x6E4 - 0x6E3];
    /* 0x6E4 */ u32 mShadowID;
    /* 0x6E8 */ J3DModel* mpLsHandModel;
    /* 0x6EC */ s8 m_lsHnd_L_jnt_num;
    /* 0x6ED */ s8 m_lsHnd_R_jnt_num;
    /* 0x6EE */ u8 m6EE[0x6F0 - 0x6EE];
    /* 0x6F0 */ mDoExt_btkAnm mBtkAnm;
    /* 0x704 */ u8 field_0x704;
    /* 0x705 */ u8 m705[0x708 - 0x705];
    /* 0x708 */ mDoExt_btpAnm mBtpAnm;
    /* 0x71C */ u8 field_0x71C;
    /* 0x71D */ u8 m71D[0x71E - 0x71D];
    /* 0x71E */ s16 field_0x71E;
    /* 0x720 */ ProcFunc mCurrProcFunc;
    /* 0x72C */ Mtx mHand_L_Mtx;
    /* 0x75C */ Mtx mHand_R_Mtx;
    /* 0x78C */ fpc_ProcID mBm1ProcID;
    /* 0x790 */ fpc_ProcID m790;
    /* 0x794 */ cXyz m794;
    /* 0x7A0 */ csXyz m7A0;
    /* 0x7A6 */ csXyz field_0x7A6;
    /* 0x7AC */ u8 m7AC[0x7B4 - 0x7AC];
    /* 0x7B4 */ cXyz mTransformedEyePos;
    /* 0x7C0 */ cXyz field_0x7C0;
    /* 0x7CC */ cXyz field_0x7CC[2];
    /* 0x7E4 */ cXyz m7E4;
    /* 0x7F0 */ u8 m7F0[0x800 - 0x7F0];
    /* 0x800 */ f32 field_0x800;
    /* 0x804 */ s16 field_0x804;
    /* 0x806 */ s16 field_0x806;
    /* 0x808 */ s16 field_0x808;
    /* 0x80A */ u8 m80A[0x80C - 0x80A];
    /* 0x80C */ BOOL mbSetEyePos;
    /* 0x810 */ u32 field_0x810;
    /* 0x814 */ s16 mEventIDTbl[4];
    /* 0x81C */ s16 mEventIndex;
    /* 0x81E */ s16 field_0x81E;
    /* 0x820 */ u8 m820[0x822 - 0x820];
    /* 0x822 */ s16 field_0x822;
    /* 0x824 */ s16 field_0x824;
    /* 0x826 */ s16 field_0x826;
    /* 0x828 */ u8 m828[0x82E - 0x828];
    /* 0x82E */ s16 field_0x82E;
    /* 0x830 */ s8 field_0x830;
    /* 0x831 */ u8 field_0x831;
    /* 0x832 */ u8 field_0x832;
    /* 0x833 */ u8 field_0x833;
    /* 0x834 */ bool m834;
    /* 0x835 */ u8 field_0x835;
    /* 0x836 */ u8 field_0x836;
    /* 0x837 */ bool mbResLoadIsComplete;
    /* 0x838 */ u8 field_0x838;
    /* 0x839 */ u8 field_0x839;
    /* 0x83A */ bool m83A;
    /* 0x83B */ u8 m83B;
    /* 0x83C */ u8 m83C;
    /* 0x83D */ bool m83D;
    /* 0x83E */ u8 field_0x83E;
    /* 0x83F */ u8 field_0x83F;
    /* 0x840 */ bool field_0x840;
    /* 0x841 */ bool m841;
    /* 0x842 */ s16 mHalfHeadAngleY;
    /* 0x844 */ s16 mHalfHeadAngleX;
    /* 0x846 */ s16 m846;
    /* 0x848 */ s16 m848;
    /* 0x84A */ s8 mActionIndex;
    /* 0x84B */ u8 field_0x84B;
    /* 0x84C */ u8 mMesgAnimeTag;
    /* 0x84D */ s8 field_0x84D;
    /* 0x84E */ s8 mBtkResIDIndex;
    /* 0x84F */ s8 mBckResIndex;
    /* 0x850 */ s8 field_0x850;
    /* 0x851 */ s8 field_0x851;
    /* 0x852 */ s8 field_0x852;
    /* 0x853 */ s8 field_0x853;
    /* 0x854 */ s8 m854;
    /* 0x855 */ s8 mType;
    /* 0x856 */ s8 field_0x856;
    /* 0x857 */ s8 field_0x857;
};  // Size: 0x858

class daNpc_Ls1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackBoneX;
        /* 0x0A */ s16 mMaxBackBoneY;
        /* 0x0C */ s16 mMinBackBoneX;
        /* 0x0E */ s16 mMinBackBoneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 field_0x12;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ bool m18;
        /* 0x19 */ // 3 bytes of alignment padding
        /* 0x1C */ f32 field_0x1C;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2C;
        /* 0x30 */ s16 field_0x30;
        /* 0x32 */ // 2 bytes of alignment padding
        /* 0x34 */ f32 field_0x34;
    };  // Size: 0x38
    daNpc_Ls1_HIO_c();
    inline virtual ~daNpc_Ls1_HIO_c();
public:
    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ // 3 bytes of alignment padding
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x44

#endif /* D_A_NPC_LS1_H */
