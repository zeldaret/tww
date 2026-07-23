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

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_UNK_2    = 2,
        ACTION_ENDING   = -1,
    };

public:

    bool checkAction(int (daNpc_P1_c::*action)(void*)) { return mActionFunc == action;}
    void setAction(int (daNpc_P1_c::*action)(void*), void* i_param_2, int i_param_3) {
        if(mActionFunc != action){
            if(mActionFunc != NULL){
                mActionStatus = ACTION_ENDING;
                (this->*mActionFunc)(i_param_2);
            }
            mPrevAction = mActionFunc;
            mActionFunc = action;
            mActionStatus = ACTION_STARTING;
            (this->*mActionFunc)(NULL);
        }
    }

    void setAnimFromMsg();
    BOOL setAnm(int, float);
    BOOL normalAction(void*);
    BOOL confuseAction(void*);
    BOOL talkAction(void*);
    BOOL p1c_speakAction(void*);
    BOOL speakAction(void*);
    BOOL explainAction(void*);
    u32 getNextMsgNo(int);
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
    fpc_ProcID getKajiID();
    BOOL kaji_anm();
    BOOL _execute();
    BOOL _draw();
    BOOL lookBack();

public:
                ActionFunc mActionFunc;
                ActionFunc mPrevAction;
                request_of_phase_process_class mPhs;
                mDoExt_McaMorf* mpMorf;
                u8 pad2B4[0x2C0-0x2B4];
                J3DModel* mpHeadModel;
                J3DModel* mpDoraModel;
                J3DAnmTexPattern* mpTexture;
                mDoExt_btpAnm mBtp;
                u8 mBlinkFrame;
                s16 mBlinkTimer;
                u32 mShadowId;
                dBgS_ObjAcch mObjAcch;
                dBgS_AcchCir mAcchCir;
                dCcD_Stts mStts;
                dCcD_Cyl mCyl;
    /* 0x658 */ u8 pad658;
    /* 0x659 */ s8 mActionStatus;
    /* 0x65A */ s8 m65A;
    /* 0x65B */ u8 mType;
    /* 0x65C */ u8 m65C;
    /* 0x65D */ char pad65D[3];
    /* 0x660 */ u32 mCurrMesg;
    /* 0x664 */ u32 mPrevMesg;
    /* 0x668 */ s32 mAnmNum;
    /* 0x66C */ s32 m66C;
    /* 0x670 */ u8 m670;
    /* 0x671 */ u8 m671;
                u32 mKajiId;
                s16 m678;
                s16 filler;
                dNpc_JntCtrl_c m_jnt;
                dNpc_EventCut_c mEventCut6B0;
    /* 0x71C */ dNpc_HeadAnm_c m71C;              /* inferred */
                s8 m_handR_jnt_num;
    /* 0x741 */ bool mbAttentionFlag;                          /* inferred */
    /* 0x742 */ s16 mMaxLookVel;                         /* inferred */ 

};

#endif /* D_A_NPC_P1_H */
