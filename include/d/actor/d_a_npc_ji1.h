#ifndef D_A_NPC_JI1_H
#define D_A_NPC_JI1_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "d/d_particle.h"

class mDoExt_McaMorf;

class daNpc_Ji1_c : public fopAc_ac_c {
public:
    typedef int (daNpc_Ji1_c::*Action_t)(void*);
    typedef int (daNpc_Ji1_c::*SubAction_t)();

    void SpRollCutChcek() {}

    bool checkAction(Action_t action) {
        return mAction == action;
    }

    bool checkSubAction(SubAction_t subAction) {
        return mSubAction == subAction;
    }

    void setAction(Action_t action, void* arg) {
        if(mAction != action) {
            if(mAction) {
                field_0xC78 = 0xFF;
                (this->*mAction)(arg);
            }

            field_0x2BC = mAction;
            mAction = action;
            field_0xC78 = 0;
            (this->*mAction)(arg);
        }
    }

    void setSubAction(SubAction_t subAction) {
        mSubAction = subAction;
    }

    BOOL isGuardAnim();
    BOOL isAttackAnim();
    int isAttackFrame();
    BOOL isItemWaitAnim();
    BOOL isClearRecord(short);
    void setClearRecord(short);
    void normalSubActionHarpoonGuard(short);
    void normalSubActionGuard(short);
    BOOL normalAction(void*);
    BOOL kaitenExpAction(void*);
    BOOL kaitenspeakAction(void*);
    BOOL kaitenwaitAction(void*);
    BOOL kaitenAction(void*);
    u32 getMsg1stType();
    u32 getMsg2ndType();
    u32 getMsg();
    u16 next_msgStatus(u32* msgId);
    BOOL talkAction(void*);
    BOOL speakAction(void*);
    BOOL speakBadAction(void*);
    static void* initPosObject(void*, void*);
    void initPos(int);
    void createItem();
    void set_mtx();
    s32 getEventActionNo(int);
    BOOL eventAction(void*);
    u32 evn_init_pos_init(int);
    u32 evn_setAnm_init(int);
    u32 evn_talk_init(int);
    u32 evn_talk();
    u32 evn_continue_talk_init(int);
    u32 evn_continue_talk();
    u32 evn_setAngle_init(int);
    u32 evn_sound_proc_init(int);
    u32 evn_head_swing_init(int);
    u32 evn_harpoon_proc_init(int);
    u32 evn_RollAtControl_init(int);
    u32 evn_RollAtControl();
    u32 evn_game_mode_init(int);
    u32 evn_turn_to_player();
    u32 evn_hide_init(int);
    void AnimeControlToWait();
    u32 privateCut();
    u32 setParticle(int, f32, f32);
    void dtParticle();
    u32 setParticleAT(int, f32, f32);
    void dtParticleAT();
    BOOL startspeakAction(void*);
    BOOL endspeakAction(void*);
    BOOL reiAction(void*);
    BOOL plmoveAction(void*);
    BOOL teachMove(f32);
    BOOL teachSpRollCutMove(f32);
    f32 calcCoCorrectValue();
    f32 calcBgCorrectValue();
    BOOL MoveToPlayer(f32, u8);
    void teachSubActionAttackInit();
    BOOL teachSubActionAttack();
    void teachSubActionJumpInit();
    BOOL teachSubActionJump();
    BOOL teachAction(void*);
    BOOL teachSPRollCutAction(void*);
    void battleGameSetTimer();
    BOOL battleMove(f32);
    void battleSubActionWaitInit();
    BOOL battleSubActionWait();
    void battleSubActionNockBackInit(int);
    BOOL battleSubActionNockBack();
    void battleSubActionAttackInit();
    BOOL battleSubActionAttack();
    void battleSubActionTateAttackInit();
    BOOL battleSubActionTateAttack();
    void battleSubActionYokoAttackInit();
    BOOL battleSubActionYokoAttack();
    void battleSubActionJumpInit();
    BOOL battleSubActionJump();
    void battleSubActionDamageInit();
    BOOL battleSubActionDamage();
    void battleSubActionJpGuardInit();
    BOOL battleSubActionJpGuard();
    void battleSubActionGuardInit();
    BOOL battleSubActionGuard();
    BOOL battleAtSet();
    BOOL battleGuardCheck();
    BOOL battleAction(void*);
    BOOL checkCutType(int, int);
    void setAnimFromMsgNo(u32);
    BOOL setAnm(int, f32, int);
    cPhs_State _create();
    BOOL CreateHeap();
    BOOL CreateInit();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();
    BOOL chkAttention(cXyz, s16);
    BOOL lookBack();
    void setHitParticle(cXyz*, u32);
    void setGuardParticle();
    void BackSlideInit();
    void BackSlide(f32, f32);
    void harpoonRelease(cXyz*);
    void harpoonMove();

public:
    /* 0x290 */ f32 field_0x290;
    /* 0x294 */ f32 field_0x294;
    /* 0x298 */ f32 field_0x298;
    /* 0x29C */ f32 field_0x29C;
    /* 0x2A0 */ f32 field_0x2A0;
    /* 0x2A4 */ f32 field_0x2A4;
    /* 0x2A8 */ u8 field_0x2A8;
    /* 0x2AC */ u32 mMsgNo;
    /* 0x2B0 */ Action_t mAction;
    /* 0x2BC */ Action_t field_0x2BC;
    /* 0x2C8 */ Action_t field_0x2C8;
    /* 0x2D4 */ SubAction_t mSubAction;
    /* 0x2E0 */ dPa_smokeEcallBack field_0x2E0;
    /* 0x300 */ dPa_smokeEcallBack field_0x300;
#if VERSION == VERSION_DEMO
    /* 0x320 */ JPABaseEmitter* field_0x320_demo;
    /* 0x324 */ JPABaseEmitter* field_0x324_demo;
#endif
    /* 0x320 */ cXyz field_0x320;
    /* 0x32C */ s16 field_0x32C;
    /* 0x330 */ mDoExt_McaMorf* mpOrcaMorf;
    /* 0x334 */ dNpc_EventCut_c mEventCut;
    /* 0x3A0 */ dNpc_JntCtrl_c m_jnt;
    /* 0x3D4 */ J3DAnmTexPattern* headTexPattern;
    /* 0x3D8 */ mDoExt_btpAnm mBlinkAnim;
    /* 0x3EC */ u8 mBlinkFrame;
    /* 0x3EE */ s16 mBlinkTimer;
    /* 0x3F0 */ u32 mShadowId;
    /* 0x3F4 */ mDoExt_McaMorf* mpSpearMorf;
    /* 0x3F8 */ J3DModel* mpTearsModel;
    /* 0x3FC */ mDoExt_brkAnm mCryBrk;
    /* 0x414 */ f32 mCryBrkFrame;
    /* 0x418 */ mDoExt_btkAnm mCryBtk;
    /* 0x42C */ f32 mCryBtkFrame;
    /* 0x430 */ JPABaseEmitter* field_0x430;
    /* 0x434 */ dBgS_ObjAcch mAcch;
    /* 0x5F8 */ dBgS_AcchCir mAcchCir;
    /* 0x638 */ dCcD_Stts field_0x638;
    /* 0x674 */ dCcD_Stts field_0x674;
    /* 0x6B0 */ dCcD_Cyl field_0x6B0;
    /* 0x7E0 */ dCcD_Cyl field_0x7E0;
    /* 0x910 */ dCcD_Cyl field_0x910;
    /* 0xA40 */ dCcD_Cps field_0xA40;
    /* 0xB78 */ cXyz field_0xB78;
    /* 0xB84 */ cXyz field_0xB84;
    /* 0xB90 */ cXyz field_0xB90;
    /* 0xB9C */ s8 handRJointNo;
    /* 0xB9D */ s8 hair1JointNo;
    /* 0xB9E */ s8 hair2JointNo;
    /* 0xB9F */ s8 hair3JointNo;
    /* 0xBA0 */ s8 armLJointNo;
    /* 0xBA1 */ s8 armRJointNo;
    /* 0xBA2 */ s16 field_0xBA2;
    /* 0xBA4 */ s16 field_0xBA4;
    /* 0xBA6 */ s16 field_0xBA6;
    /* 0xBA8 */ s16 field_0xBA8;
    /* 0xBAA */ s16 field_0xBAA;
    /* 0xBAC */ s16 field_0xBAC;
    /* 0xBAE */ s16 field_0xBAE;
    /* 0xBB0 */ s16 field_0xBB0;
    /* 0xBB2 */ s16 field_0xBB2;
    /* 0xBB4 */ s16 field_0xBB4;
    /* 0xBB6 */ s16 field_0xBB6;
    /* 0xBB8 */ s16 field_0xBB8;
    /* 0xBBA */ s16 field_0xBBA;
    /* 0xBBC */ s16 field_0xBBC;
    /* 0xBBE */ s16 field_0xBBE;
    /* 0xBC0 */ s16 field_0xBC0;
    /* 0xBC2 */ s16 field_0xBC2;
    /* 0xBC4 */ cXyz field_0xBC4;
    /* 0xBD0 */ s16 field_0xBD0;
    /* 0xBD2 */ s16 field_0xBD2;
    /* 0xBD4 */ s16 field_0xBD4;
    /* 0xBD6 */ s16 field_0xBD6;
    /* 0xBD8 */ cXyz field_0xBD8[3];
    /* 0xBFC */ dNpc_HeadAnm_c mHeadAnm;
    /* 0xC20 */ u32 pad_0xC20;
    /* 0xC24 */ s32 field_0xC24;
    /* 0xC28 */ u32 field_0xC28;
    /* 0xC2C */ s32 field_0xC2C;
    /* 0xC30 */ s32 field_0xC30;
    /* 0xC34 */ int field_0xC34;
    /* 0xC38 */ s32 field_0xC38;
    /* 0xC3C */ int field_0xC3C;
    /* 0xC40 */ cXyz field_0xC40;
    /* 0xC4C */ f32 field_0xC4C;
    /* 0xC50 */ f32 field_0xC50;
    /* 0xC54 */ s16 mEventIdx[0x12];
    /* 0xC78 */ s8 field_0xC78;
    /* 0xC7C */ request_of_phase_process_class mPhs;
    /* 0xC84 */ u32 field_0xC84;
    /* 0xC88 */ s16 field_0xC88;
    /* 0xC8C */ s32 field_0xC8C;
    /* 0xC90 */ s32 field_0xC90;
    /* 0xC94 */ s32 field_0xC94;
    /* 0xC98 */ s32 field_0xC98;
    /* 0xC9C */ f32 field_0xC9C;
    /* 0xCA0 */ Mtx field_0xCA0;
    /* 0xCD0 */ cXyz field_0xCD0;
    /* 0xCDC */ cXyz field_0xCDC;
    /* 0xCE8 */ u8 pad_0xCE8[0xC];
    /* 0xCF4 */ Quaternion field_0xCF4;
    /* 0xD04 */ Quaternion field_0xD04;
    /* 0xD14 */ s16 field_0xD14;
    /* 0xD16 */ s16 field_0xD16;
    /* 0xD18 */ f32 field_0xD18;
    /* 0xD1C */ cXyz field_0xD1C;
    /* 0xD28 */ cXyz field_0xD28;
    /* 0xD34 */ s32 field_0xD34;
    /* 0xD38 */ cXyz field_0xD38;
    /* 0xD44 */ u8 pad_0xD44[0xC];
    /* 0xD50 */ cXyz field_0xD50;
    /* 0xD5C */ csXyz field_0xD5C;
    /* 0xD64 */ s32 mAnimation;
    /* 0xD68 */ s32 field_0xD68;
    /* 0xD6C */ s32 field_0xD6C;
    /* 0xD70 */ s32 field_0xD70;
    /* 0xD74 */ s32 field_0xD74;
    /* 0xD78 */ u8 field_0xD78;
    /* 0xD79 */ u8 field_0xD79;
    /* 0xD7A */ u8 field_0xD7A;
    /* 0xD7B */ u8 field_0xD7B;
    /* 0xD7C */ u8 field_0xD7C;
    /* 0xD7D */ u8 mCreateItemNo;
    /* 0xD7E */ u8 field_0xD7E;
    /* 0xD80 */ u32 mEndMsgNo;
    /* 0xD84 */ u8 field_0xD84;
    /* 0xD85 */ bool mHide;
    
    static s8 game_life_point;
}; // Size: 0xD88

class daNpc_Ji1_HIO_c : public JORReflexible {
public:
    daNpc_Ji1_HIO_c();
    virtual ~daNpc_Ji1_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x004 */ s8 mNo;
    /* 0x008 */ f32 field_0x08;
    /* 0x00C */ s16 field_0x0C;
    /* 0x00E */ s16 field_0x0E;
    /* 0x010 */ s16 field_0x10;
    /* 0x012 */ s16 field_0x12;
    /* 0x014 */ s16 field_0x14;
    /* 0x016 */ s16 field_0x16;
    /* 0x018 */ s16 field_0x18;
    /* 0x01A */ u8 field_0x1A;
    /* 0x01C */ f32 field_0x1C;
    /* 0x020 */ f32 field_0x20;
    /* 0x024 */ f32 field_0x24;
    /* 0x028 */ u8 field_0x28;
    /* 0x02C */ f32 field_0x2C;
    /* 0x030 */ u8 field_0x30;
    /* 0x034 */ f32 field_0x34;
    /* 0x038 */ f32 field_0x38;
    /* 0x03C */ f32 field_0x3C;
    /* 0x040 */ f32 field_0x40;
    /* 0x044 */ f32 field_0x44;
    /* 0x048 */ f32 field_0x48;
    /* 0x04C */ f32 field_0x4C;
    /* 0x050 */ f32 field_0x50;
    /* 0x054 */ s16 field_0x54[6];
    /* 0x060 */ s16 field_0x60[4];
    /* 0x068 */ u8 field_0x68;
    /* 0x06C */ f32 field_0x6C;
    /* 0x070 */ f32 field_0x70;
    /* 0x074 */ f32 field_0x74;
    /* 0x078 */ f32 field_0x78;
    /* 0x07C */ f32 field_0x7C;
    /* 0x080 */ f32 field_0x80;
    /* 0x084 */ f32 field_0x84;
    /* 0x088 */ s16 field_0x88;
    /* 0x08A */ s16 field_0x8A;
    /* 0x08C */ s16 field_0x8C;
    /* 0x08E */ s16 field_0x8E;
    /* 0x090 */ s16 field_0x90;
    /* 0x092 */ s16 field_0x92;
    /* 0x094 */ s16 field_0x94;
    /* 0x096 */ s16 field_0x96;
    /* 0x098 */ s16 field_0x98;
    /* 0x09A */ s16 field_0x9A;
    /* 0x09C */ s16 field_0x9C;
    /* 0x09E */ s16 field_0x9E;
    /* 0x0A0 */ s16 field_0xA0;
    /* 0x0A2 */ u8 field_0xA2;
    /* 0x0A4 */ f32 field_0xA4;
    /* 0x0A8 */ f32 field_0xA8;
    /* 0x0AC */ f32 field_0xAC;
    /* 0x0B0 */ f32 field_0xB0;
    /* 0x0B4 */ f32 field_0xB4;
    /* 0x0B8 */ u8 field_0xB8;
    /* 0x0BC */ f32 field_0xBC;
    /* 0x0C0 */ f32 field_0xC0;
    /* 0x0C4 */ cXyz field_0xC4[3];
    /* 0x0E8 */ s16 field_0xE8;
    /* 0x0EA */ s16 field_0xEA;
    /* 0x0EC */ s16 field_0xEC;
    /* 0x0EE */ s16 field_0xEE;
    /* 0x0F0 */ s16 field_0xF0;
    /* 0x0F2 */ s16 field_0xF2;
    /* 0x0F4 */ s16 field_0xF4;
    /* 0x0F6 */ s16 field_0xF6;
    /* 0x0F8 */ s16 field_0xF8;
    /* 0x0FA */ s16 field_0xFA;
    /* 0x0FC */ s16 field_0xFC;
    /* 0x0FE */ s16 field_0xFE;
};  // Size: 0x100

#endif /* D_A_NPC_JI1_H */
