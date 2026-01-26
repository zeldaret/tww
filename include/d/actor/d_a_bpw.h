#ifndef D_A_BPW_H
#define D_A_BPW_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"

struct bpw_class {
    enum Actor_Type_e {
        Actor_Type_BODY_e = 0,
        Actor_Type_KANTERA_e = 1,
        Actor_Type_DAMAGE_BALL_e = 2,
        Actor_Type_TORITUKI_e = 3,
    };

    enum Damage_Action_e {
        Damage_Action_LINE_e = 0,
        Damage_Action_DAMAGE_BALL_e = 1,
    };

    enum Action_e {
        Action_MOVE_DOUSA_e = 0,
        Action_ATTACK_KOUGEKI_e = 1,
        Action_BODY_DOWN_KARADA_TAORE_e = 2,
        Action_DAMAGE_e = 3,
        Action_SEPARATION_BUNRI_DOUSA_e = 4,
        Action_START_DEMO_e = 20,
    };

    enum Action_State_Type_e {
        Action_State_DAMAGE_CARRIED_e = 0x54,
        Action_State_DAMAGE_THROWN_e = 0x55,
        Action_State_DAMAGE_HIT_e = 0x65,
        Action_State_SEPARATE_BUNRI_DOUSA_INIT_e = 0x6E,
        Action_State_SEPARATE_BUNRI_DOUSA_EXECUTE_e = 0x6F,
        Action_State_SEPARATE_BUNRI_DOUSA_END_INIT_e = 0x72,
        Action_State_SEPARATE_BUNRI_DOUSA_END_GATHER_e = 0x73,
        Action_State_SEPARATE_BUNRI_DOUSA_END_GROW_e = 0x74,
        Action_State_SEPARATE_BUNRI_DOUSA_END_FINISH_e = 0x75,
    };

    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class m2AC;
    /* 0x2B4 */ mDoExt_McaMorf* mpAnim;
    /* 0x2B8 */ u8 m2B8[0x2BC - 0x2B8];
    /* 0x2BC */ mDoExt_brkAnm* mBrkAnim;
    /* 0x2C0 */ mDoExt_brkAnm* mKanteraAnim;
    /* 0x2C4 */ mDoExt_brkAnm* m2C4;
    /* 0x2C8 */ mDoExt_brkAnm* m2C8;
    /* 0x2CC */ mDoExt_brkAnm* m2CC;
    /* 0x2D0 */ mDoExt_brkAnm* m2D0;
    /* 0x2D4 */ Mtx m2D4;
    /* 0x304 */ cXyz m304[3];
    /* 0x328 */ cXyz m328[3];
    /* 0x34C */ cXyz mBodyPos;
    /* 0x358 */ cXyz m358;
    /* 0x364 */ u8 m364[0x370 - 0x364];
    /* 0x370 */ cXyz m370;
    /* 0x37C */ cXyz mChildActorPos;
    /* 0x388 */ f32 m388;
    /* 0x38C */ f32 m38C;
    /* 0x390 */ f32 m390;
    /* 0x394 */ cXyz m394;
    /* 0x3A0 */ cXyz m3A0;
    /* 0x3AC */ cXyz m3AC;
    /* 0x3B8 */ cXyz m3B8;
    /* 0x3C4 */ cXyz m3C4;
    /* 0x3D0 */ csXyz mKanteraDousaRot;
    /* 0x3D6 */ s16 m3D6;
    /* 0x3D8 */ s16 m3D8;
    /* 0x3DA */ u16 m3DA;
    /* 0x3DC */ u8 mType;
    /* 0x3DD */ u8 mUnknownParam2;
    /* 0x3DE */ u8 mLightState;
    /* 0x3DF */ u8 m3DF;
    /* 0x3E0 */ u8 m3E0;
    /* 0x3E1 */ u8 m3E1;
    /* 0x3E2 */ u8 m3E2;
    /* 0x3E3 */ u8 m3E3[0x3E4 - 0x3E3];
    /* 0x3E4 */ u8 m3E4;
    /* 0x3E5 */ u8 m3E5;
    /* 0x3E6 */ u8 m3E6;
    /* 0x3E7 */ u8 m3E7;
    /* 0x3E8 */ u8 m3E8;
    /* 0x3E9 */ u8 m3E9;
    /* 0x3EA */ u8 m3EA;
    /* 0x3EB */ u8 mKankyouHendouState;
    /* 0x3EC */ f32 m3EC;
    /* 0x3F0 */ f32 m3F0;
    /* 0x3F4 */ s16 m3F4;
    /* 0x3F6 */ s16 m3F6;
    /* 0x3F8 */ int m3F8;
    /* 0x3FC */ fpc_ProcID m3FC;
    /* 0x400 */ fpc_ProcID m400;
    /* 0x404 */ fpc_ProcID m404;
    #if VERSION > VERSION_DEMO
    /* 0x408 */ s16 m408;
    #endif
    /* 0x40C */ cXyz m40C;
    /* 0x418 */ cXyz m418;
    /* 0x424 */ cXyz m424;
    /* 0x430 */ u8 m430[0x43C - 0x430];
    /* 0x43C */ f32 m43C;
    /* 0x440 */ f32 m440;
    /* 0x444 */ s16 mBodyAction;
    /* 0x446 */ s16 mActionState;
    /* 0x448 */ u8 m448[0x44C - 0x448];
    /* 0x44C */ s16 mAttWaitTimer;
    /* 0x44E */ s16 mSomeCountdownTimers[10];
    /* 0x462 */ s16 m462;
    /* 0x464 */ s16 m464;
    /* 0x466 */ u8 m466[0x474 - 0x466];
    /* 0x474 */ s16 m474;
    /* 0x476 */ s16 m476;
    /* 0x478 */ s16 m478;
    /* 0x47A */ s16 m47A;
    /* 0x47C */ s16 m47C;
    /* 0x47E */ s16 m47E;
    /* 0x480 */ s16 m480;
    /* 0x482 */ s16 m482;
    /* 0x484 */ s16 m484;
    /* 0x486 */ u8 m486[0x488 - 0x486];
    /* 0x488 */ f32 m488;
    /* 0x48C */ f32 m48C;
    /* 0x490 */ f32 m490;
    /* 0x494 */ f32 m494;
    /* 0x498 */ f32 m498;
    /* 0x49C */ f32 m49C;
    /* 0x4A0 */ f32 m4A0;
    /* 0x4A4 */ f32 m4A4;
    /* 0x4A8 */ f32 m4A8;
    /* 0x4AC */ int mChildPoeIds[15];
    /* 0x4E8 */ u32 m4E8;
    /* 0x4EC */ LIGHT_INFLUENCE m4EC;
    #if VERSION == VERSION_DEMO
    /* 0x508 */ JPABaseEmitter* m508_demo;
    /* 0x50C */ JPABaseEmitter* m50C_demo;
    /* 0x510 */ JPABaseEmitter* m510_demo;
    #endif
    /* 0x50C */ dPa_smokeEcallBack m50C;
    #if VERSION == VERSION_DEMO
    /* 0x534 */ JPABaseEmitter* m534_demo;
    /* 0x538 */ JPABaseEmitter* m538_demo;
    /* 0x53C */ JPABaseEmitter* m53C_demo;
    /* 0x540 */ JPABaseEmitter* m540_demo;
    #else
    /* 0x52C */ dPa_followEcallBack m52C;
    /* 0x540 */ dPa_followEcallBack m540;
    #endif
    /* 0x554 */ dPa_followEcallBack m554;
    /* 0x568 */ dPa_followEcallBack mFire1Dousa_Pa_followEcallBack;
    /* 0x57C */ dPa_followEcallBack mFire1Dousa_Pa_followEcallBack2;
    /* 0x590 */ dPa_followEcallBack m590;
    #if VERSION == VERSION_DEMO
    /* 0x594 */ JPABaseEmitter* m594_demo;
    /* 0x598 */ JPABaseEmitter* m598_demo;
    #endif
    /* 0x5A4 */ dPa_followEcallBack mFireDousa2_Pa_followEcallBack;
    /* 0x5B8 */ dPa_followEcallBack mFireDousa2_Pa_followEcallBack2;
    /* 0x5CC */ dPa_followEcallBack m5CC;
    /* 0x5E0 */ dPa_smokeEcallBack m5E0[4];
    /* 0x660 */ cXyz mFire1DousaPos;
    /* 0x66C */ cXyz m66C;
    /* 0x678 */ csXyz mFire1DousaRot;
    /* 0x67E */ s16 m67E;
    /* 0x680 */ s16 m680;
    /* 0x67E */ u8 m682[0x684 - 0x682];
    /* 0x684 */ s16 m684;
    /* 0x686 */ u8 m686[0x688 - 0x686];
    /* 0x688 */ dBgS_AcchCir mAcchCir;
    /* 0x6C8 */ dBgS_ObjAcch mAcch;
    /* 0x88C */ dCcD_Stts mStts;
    /* 0x8C8 */ dCcD_Sph mBodyCoSph;
    /* 0x9F4 */ dCcD_Sph mBodyAtSph;
    /* 0xB20 */ dCcD_Sph mKanteraCoSph;
    /* 0xC4C */ dCcD_Sph mDamageBallCoSph;
    /* 0xD78 */ mDoExt_invisibleModel mD78;
};

#endif /* D_A_BPW_H */
