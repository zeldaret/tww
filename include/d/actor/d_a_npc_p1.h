#ifndef D_A_NPC_P1_H
#define D_A_NPC_P1_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_P1_c : public fopAc_ac_c {

    typedef BOOL (daNpc_P1_c::*ActionFunc)(void*);

public:

    bool checkAction(int (daNpc_P1_c::*action)(void*)) { return m290 == action;}
    void setAction(int (daNpc_P1_c::*action)(void*), void* i_param_2, int i_param_3) {
        if(m290 != action){
            if(m290 != NULL){
                m659 = -1;
                (this->*m290)(0);
            }
            mPrevAction = m290;
            m290 = action;
            m659 = 0;
            (this->*m290)(NULL);
        }
    }

    void setAnimFromMsg();
    void setAnm(int, float);
    BOOL normalAction(void*);
    BOOL confuseAction(void*);
    BOOL talkAction(void*);
    BOOL p1c_speakAction(void*);
    BOOL speakAction(void*);
    BOOL explainAction(void*);
    BOOL getNextMsgNo(int);
    BOOL playTexPatternAnm();
    void demo_end_init();
    BOOL demo_move();
    BOOL event_move();
    BOOL evn_setAnm_init(int);
    BOOL evn_talk_init(int);
    BOOL evn_talk();
    BOOL minigameExplainCut();
    BOOL privateCut();
    BOOL setAttentionPos(cXyz*);
    cPhs_State _create();
    BOOL CreateHeap();
    BOOL _delete();
    void getKajiID();
    void kaji_anm();
    BOOL _execute();
    BOOL _draw();
    void lookBack();

public:
    ActionFunc m290;
    ActionFunc mPrevAction;
    J3DModel* mpModel;
    mDoExt_McaMorf* mpMorf;
    J3DAnmTexPattern* m2C8;
    mDoExt_btpAnm mBtp;
    u32 m2D4;
    s32 m2D8;
    s32 m2DC;
    u8 m2E0;
    s16 mBlinkTimer;
    f32 m64C;
    s8 m658;
    s8 m659;
    s8 m65A;
    u8 mType65B;
    u8 m65C;
    u32 m660;
    s32 m664;
    s16 m666;
    s32 m668;
    s32 m66C;
    s32 m670;
    s32 m674;
    s32 m678;
    dNpc_JntCtrl_c m_jnt;
    
    //dNpc_JntCtrl_c m_jnt;
    s8 m684;
    s8 m685;
    u8 m686;
    u8 m687;
    u8 m688;
    // u8 m670;
    // s16 m67C;
    // s16 m67E;

    dNpc_EventCut_c mEventCut6B0;
    /* 0x710 */ u8 m6C4[0x710-0x6C4];
    /* 0x710 */ u8 m710;                          /* inferred */
    /* 0x711 */ char pad711[2];                     /* maybe part of unk710[8]? */
    /* 0x718 */ dNpc_JntCtrl_c *m_jnt2;             /* inferred */
    /* 0x71C */ dNpc_HeadAnm_c m71C;              /* inferred */
                s16 m71E;
    /* 0x73C */ s16 unk73C;                         /* inferred */
    /* 0x73E */ char pad73E[2];
    /* 0x740 */ u8 unk740;                          /* inferred */
    u8 m_handR_jnt_num;
    /* 0x741 */ u8 m741;                          /* inferred */
    /* 0x742 */ s16 unk742;                         /* inferred */ 
    void* test;
};

class daNpc_P1_childHIO_c{
public:
    daNpc_P1_childHIO_c();

public:
    /* Place member variables here */
    /* 0x00 */ char pad0[4];
    /* 0x04 */ u8 unk4;                             /* inferred */
    /* 0x05 */ char pad5[3];                        /* maybe part of unk4[4]? */
    /* 0x08 */ s32 unk8;                            /* inferred */
    /* 0x0C */ char padC[4];                        /* maybe part of unk8[3]? */
               f32 m10;
    /* 0x14 */ f32 unk14;                           /* inferred */
    /* 0x18 */ s16 unk18;                           /* inferred */
    /* 0x1A */ s16 unk1A;                           /* inferred */
    /* 0x1C */ s16 unk1C;                           /* inferred */
    /* 0x1E */ s16 unk1E;                           /* inferred */
    /* 0x20 */ s16 unk20;                           /* inferred */
    /* 0x22 */ s16 unk22;                           /* inferred */
    /* 0x24 */ s16 unk24;                           /* inferred */
    /* 0x26 */ s16 unk26;                           /* inferred */
    /* 0x28 */ s16 unk28;                           /* inferred */
    /* 0x2A */ s16 unk2A;                           /* inferred */
    /* 0x2C */ char pad2C[4];                       /* maybe part of unk2A[3]? */
    //SIZE = 0x30
};



class daNpc_P1_HIO_c : public mDoHIO_entry_c{
public:
    daNpc_P1_HIO_c();
    virtual ~daNpc_P1_HIO_c(){};
public:
    daNpc_P1_childHIO_c children[3];
    f32 m90;
    f32 m94;
    f32 m98;
    // f32 m280;
    // f32 m284;
};


#endif /* D_A_NPC_P1_H */
