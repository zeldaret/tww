#ifndef D_A_NPC_KK1_H
#define D_A_NPC_KK1_H

#include "d/actor/d_a_player.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"


class J3DNode;



static void* searchActor_SWC00(void*, void*);

class daNpc_Kk1_c : public fopNpc_npc_c {

public:

    typedef int (daNpc_Kk1_c::*ActionFunc)(void*);
    typedef void* (pFunc)(void*, void*);
    struct anm_prm_c {
        s8 field0;
        s8 field1;
        u16 field2;
        f32 field4;
        f32 field8;
        u32 fieldC;
    };
    struct prm_tbl {
        u32 field_0x00;
        u32 field_0x04;
        u32 field_0x08;
        u32 field_0x0C;
        u32 field_0x10;    
        f32 field_0x14;  
        u32 field_0x18;
        u32 field_0x1C;
        u32 field_0x20;
        u32 field_0x24;
        f32 field_0x28;    
        f32 field_0x2C;    
        u32 field_0x30;    
        f32 field_0x34;    
        f32 field_0x38;    
        f32 field_0x3C;    
        u32 field_0x40;    
        f32 field_0x44;   
        f32 field_0x48;    
        u32 field_0x4C;    
        f32 field_0x50;    
    };
    // struct struct_0x7E4{
    // /* 0x0 */   u16 unk0;
    // /* 0x2 */   u16 unk2;
    // /* 0x4 */   u16 unk4;
    // /* 0x6 */   u16 unk6;   
    // /* 0x8 */   u16 unk8;   
    // /* 0xA */   u16 unkA;    
    // };

    int getSWbit();

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_KK1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool setBtp(signed char, bool);
    void init_texPttrnAnm(signed char, bool);
    void play_btp_anm();
    void play_eff_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg_KK1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    bool partner_search_sub(pFunc*);
    void partner_search();
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    BOOL decideType(int);
    void cut_init_RUN_START(int);
    bool cut_move_RUN_START();
    void cut_init_RUN(int);
    bool cut_move_RUN();
    void cut_init_CATCH_START(int);
    bool cut_move_CATCH_START();
    void cut_init_CATCH_END(int);
    bool cut_move_CATCH_END();
    void cut_init_TRN(int);
    bool cut_move_TRN();
    void cut_init_BYE_START(int);
    bool cut_move_BYE_START();
    void cut_init_BYE(int);
    bool cut_move_BYE();
    void cut_init_BYE_CONTINUE(int);
    bool cut_move_BYE_CONTINUE();
    void cut_init_BYE_END(int);
    bool cut_move_BYE_END();
    void cut_init_PLYER_TRN(int);
    bool cut_move_PLYER_TRN();
    void cut_init_OTOBOKE(int);
    bool cut_move_OTOBOKE();
    void cut_init_PLYER_MOV(int);
    bool cut_move_PLYER_MOV();
    void cut_init_RUNAWAY_START(int);
    bool cut_move_RUNAWAY_START();
    void cut_init_RUNAWAY_END(int);
    bool cut_move_RUNAWAY_END();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    bool checkCommandTalk();
    bool set_action(ActionFunc, void*);
    void setStt(signed char);
    void createTama(float);
    u32 chk_areaIN(float, cXyz);
    bool startEvent_check();
    bool chkHitPlayer();
    void set_pthPoint(unsigned char);
    bool event_move(bool);
    cXyz kyoroPos(int);
    bool kyorokyoro();
    bool chk_attn();
    void setBikon(cXyz);
    void delBikon();
    void setAse();
    void flwAse();
    void delAse();
    bool wait_1();
    bool walk_1();
    void wait_2();
    void init_CMT_WAI();
    void move_CMT_WAI();
    void init_CMT_TRN();
    void move_CMT_TRN();
    void init_CMT_PCK();
    void move_CMT_PCK();
    void cmmt_1();
    void wait_3();
    void wait_4();
    void talk_1();
    int wait_action1(void*);
    void demo();
    void shadowDraw();
    bool _draw();
    bool _execute();
    bool _delete();
    cPhs_State _create();
    void bodyCreateHeap();
    void effcCreateHeap();
    void CreateHeap();

public:

    /* 0x6C4 */ request_of_phase_process_class field_0x6C4;
    /* 0x6CC */ s8 mAnmMtxIdx;
    /* 0x6CD */ s8 field_0x6CD;   //ui bodyCreateHeap
    /* 0x6CE */ char mArcName;  
    /* 0x6CF */ u8 field_0x6CF;
    /* 0x6D0 */ u8 field_0x6D0[0x6D8 - 0x6D0];
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC*/  u8 field_0x6EC;
    /* 0x6ED*/  s8 field_0x6ED;
    /* 0x6EE*/  s16 field_0x6EE;
    /* 0x6F0*/  ActionFunc field_0x6F0;
    /* 0x6FC*/  fpc_ProcID mPartnerProcID;
    /* 0x700*/  u32 field_0x700;
    /* 0x704*/  dNpc_PathRun_c mRunPath;
    /* 0x70C */ u8 field_0x70C[0x71A - 0x70C];
    /* 0x71A */ s16 field_0x71A;
    /* 0x71C */ s16 field_0x71C;
    /* 0x71E */ csXyz field_0x71E;
    /* 0x724 */ u8 field_0x724[0x72C - 0x724];
    /* 0x72C */ cXyz field_0x72C;
    /* 0x738 */ cXyz field_0x738;
    /* 0x744 */ u8 field_0x744[0x750 - 0x744];
    /* 0x750 */ cXyz field_0x750;
    /* 0x75C */ cXyz field_0x75C;
    /* 0x768 */ f32  field_0x768;
    /* 0x76A */ u8   field_0x76A[4];
    /* 0x770 */ s16 mAngleY;
    /* 0x772 */ s16 field_0x772;
    /* 0x774 */ s16 field_0x774;
    /* 0x776 */ s16 field_0x776;
    /* 0x778 */ int field_0x778;  
    /* 0x77C */ s16 mEvtIDTbl[0x08]; //8 Elements * U16 = 16 bytes
    /* 0x78C */ s16  mEvtIDIdx; //Array Index?
    /* 0x78E */ s8  field_0x78E[0x792 - 0x78E];
    /* 0x792 */ s16 field_0x792;
    /* 0x794 */ s16 field_0x794;
    /* 0x796 */ s16 field_0x796;
    /* 0x798 */ s16 field_0x798;
    /* 0x79A */ s16 field_0x79A;
    /* 0x79C */ s16 field_0x79C;
    /* 0x79E */ s8 field_0x79E;
    /* 0x79E */ s8 field_0x79F;
    /* 0x7A0 */ s16 field_0x7A0;

    /* 0x7A2 */ s16 field_0x7A2;

    /* 0x7A4 */ s16 field_0x7A4;

    /* 0x7A6 */ s16 field_0x7A6;

    /* 0x7A8 */ s16 field_0x7A8;

    /* 0x7AA */ s16 field_0x7AA;

    /* 0x7AC */ s16 field_0x7AC;
    /* 0x7AE */ s16 field_0x7AE;
    /* 0x7B0 */ s16 field_0x7B0;
    /* 0x7B2 */ s8 field_0x7B2;
    /* 0x7B2 */ u8 field_0x7B3;
    /* 0x7B4 */ u8 field_0x7B4;
    /* 0x7B5 */ u8 field_0x7B5;
    /* 0x7B5 */ u8 field_0x7B6;
    /* 0x7B5 */ u8 field_0x7B7;
    /* 0x7B8 */ u8 field_0x7B8;
    /* 0x7B9 */ u8 field_0x7B9;
    /* 0x7BA */ u8 field_0x7BA;
    /* 0x7BB */ u8 field_0x7BB;
    /* 0x7BC */ u8 field_0x7BC;
    /* 0x7BD */ u8 field_0x7BD;
    /* 0x7BE */ u8 field_0x7BE;
    /* 0x7BF */ u8 field_0x7BF;
    /* 0x7C0 */ u8 field_0x7C0;
    /* 0x7C1 */ u8 field_0x7C1; 
    /* 0x7C2 */ u8 field_0x7C2;
    /* 0x7C3 */ u8 field_0x7C3;
    /* 0x7C4 */ bool field_0x7C4;
    /* 0x7C5 */ u8 field_0x7C5[0x7CF - 0x7C5];
    /* 0x7CF */ u8 field_0x7CF;
    /* 0x7D0 */ anm_prm_c* field_0x7D0;
    /* 0x7D4 */ u8 field_0x7D4[0x7DC - 0x7D4];
    // /* 0x7E4 */ s16* field_0x7E4;                //Appears to be a struct
    // /* 0x7E8 */ u8 field_0x7E8[0x7F0 - 0x7E8];
                mDoExt_btkAnm field_0x7DC;
    /* 0x7F0 */ mDoExt_bckAnm field_0x7F0;
    /* 0x800 */ s16 field_0x800;
    /* 0x802 */ s16 field_0x802;
    /* 0x804 */ s16 field_0x804;
    /* 0x806 */ u16 field_0x806;
//TODO: SOME KIND OF STRUCT HERE?
    /* 0x808*/  J3DModel* field_0x808;       //Offset 0
    /* 0x80C */ //J3DModelData* field_0x80C;  //Offset 4
                u8 field_0x80C[0x810-0x80C];
    /* 0x810 */ JPABaseEmitter* field_0x810;
    /* 0x814 */ s8 mCutsceneIndex;
    /* 0x815 */ s8 field_0x815;
    /* 0x816 */ s8 field_0x816;
    /* 0x817 */ u8 mAnimationNum;
    /* 0x818 */ u8 field_0x818;
    /* 0x819 */ s8 field_0x819;
    /* 0x81A */ s8 field_0x81A;
    /* 0x81B */ s8 field_0x81B; 
    /* 0x81C */ s8 field_0x81C;
    /* 0x81D */ u8 field_0x81D;
    /* 0x81E */ u8 field_0x81E;
    /* 0x81F */ s8 field_0x81F;
    /* 0x820 */ s8 field_0x820;
    /* 0x821 */ s8 field_0x821;
    /* 0x822 */ s8 field_0x822;
    /* 0x823 */ s8 field_0x823;     

};  // Size: 0x824

class daNpc_Kk1_HIO_c : mDoHIO_entry_c{
public:
    daNpc_Kk1_HIO_c();
    virtual ~daNpc_Kk1_HIO_c(){};
public:
    /* 0x04  */ s8  mNo;
    /* 0x08  */ s16 mHorizontalDistance;
    /* 0x08  */ s32 field_0xA;
    /* 0x0C  */ s16 field_0xC;
    /* 0x0E  */ s16 field_0xE;   
    /* 0x10  */ u8  mUnusedU8;
    /* 0x11  */ u8  field_0x11[0x1E - 0x11];
    /* 0x1E  */ s16 field_0x1E;  
    /* 0x20  */ f32 field_0x20;
    /* 0x24  */ f32 field_0x24;
    /* 0x28  */ s16 field_0x28;
    /* 0x28  */ s16 field_0x2A;
    /* 0x2C  */ s16 field_0x2C;
    /* 0x2C  */ s16 field_0x2E;
    /* 0x30  */ s16 field_0x30; //TODO: Struct
    /* 0x32  */ s16 field_0x32;
    /* 0x34  */ f32 field_0x34;
    /* 0x38  */ f32 field_0x38;
    /* 0x3C  */ f32 field_0x3C;
    /* 0x40  */ f32 field_0x40;
    /* 0x44  */ f32 field_0x44;
    ///* 0x44  */ s16 field_0x46;
    /* 0x48  */ f32 field_0x48;
    /* 0x4C  */ f32 field_0x4C;
    /* 0x50  */ f32 field_0x50;
    /* 0x54  */ f32 field_0x54;
    /* 0x58  */ f32 field_0x58;
    /* 0x5C  */ f32 field_0x5C;
    /* Place member variables here */
};
#endif /* D_A_NPC_KK1_H */
