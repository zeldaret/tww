#ifndef D_A_FM_H
#define D_A_FM_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"

class daFm_c : public fopEn_enemy_c {
public:
    enum Proc_e {
        PROC_0_e,
        PROC_1_e,
    };

    enum Prm_e {
        PRM_SWSAVE_W = 0x04, // unsure about names
        PRM_SWSAVE_S = 0x18,

        PRM_SOUND_W = 0x01,
        PRM_SOUND_S = 0x08
    };
    
    void isBodyAppear() {}
    void isHoleAppear() {}
    void modeProcInit(int) {}

    void _nodeControl(J3DNode*, J3DModel*);
    void _createHeap();
    void holeCreateHeap();
    void bodyCreateHeap();
    void jntHitCreateHeap();
    void _pathMove(cXyz*, cXyz*, cXyz*);
    void searchNearOtherActor(fopAc_ac_c*);
    void searchNearFm(fopAc_ac_c*);
    void moveRndBack();
    void moveRndEscape();
    void spAttackVJump();
    void spAttackJump();
    void spAttackNone();
    void iceProc();
    void bodySetMtx();
    void holeSetMtx();
    void setCollision();
    void setAttention();
    bool checkTgHit();
    void setGrabPos();
    void getOffsetPos();
    u8 checkPlayerGrabBomb();
    u8 checkPlayerGrabNpc();
    u8 checkPlayerGrabTarget();
    bool isGrabPos();
    bool isGrab();
    bool isGrabFoot();
    void modeSwWaitInit();
    void modeSwWait();
    void modeHideInit();
    void modeHide();
    void modeUnderFootInit();
    void modeUnderFoot();
    void modePathMoveInit();
    void modePathMove();
    void modeGoalKeeperInit();
    void modeGoalKeeper();
    void modeAppearInit();
    void modeAppear();
    void modeDisappearInit();
    void modeDisappear();
    void modeWaitInit();
    void modeWait();
    void modeAttackInit();
    void modeAttack();
    void modeThrowInit();
    void modeThrow();
    void modeGrabFootDemoInit();
    void modeGrabFootDemo();
    void modeParalysisInit();
    void modeParalysis();
    void modeDamageInit();
    void modeDamage();
    void modeGrabInit();
    void modeGrab();
    void modeGrabDemoInit();
    void modeGrabDemo();
    void modeDeathInit();
    void modeDeath();
    void modePrepareItemInit();
    void modePrepareItem();
    void modeGrabNpcDemoInit();
    void modeGrabNpcDemo();
    void modePlayerStartDemoInit();
    void modePlayerStartDemo();
    void modeDeleteInit();
    void modeDelete();
    void modeBikubikuInit();
    void modeBikubiku();
    void modeProc(Proc_e, int);
    void setAnm(s8, bool);
    void cancelGrab();
    void calcInvKine(fopAc_ac_c*);
    void resetInvKine();
    void grabBomb();
    void grabTsubo();
    void grabPlayer();
    void grabNPC();
    void searchTarget();
    void setBaseTarget();
    void turnToBaseTarget();
    bool isNpc(fopAc_ac_c*);
    bool checkHeight(fopAc_ac_c*);
    bool isLink(fopAc_ac_c*);
    bool isLinkControl();
    bool areaCheck();
    bool lineCheck(cXyz*, cXyz*);
    int setRnd(int, int);
    void setHoleEffect();
    void holeExecute();
    u8 setHoleScale(f32, f32, f32);
    bool _execute();
    void MtxToRot(Mtx, csXyz*);
    void debugDraw();
    void holeDraw();
    void bodyDraw();
    bool _draw();
    void getArg();
    void createInit();
    cPhs_State _create();
    bool _delete();

    typedef void (daFm_c::*ModeFunc)();

    static const dCcD_SrcSph m_sph_src;
    static const dCcD_SrcCyl m_cyl_src;
    static const u32 m_heapsize;
    static const char m_arc_name[3];

public:
    /* 0x2AC */ int mMode;
    /* 0x2B0 */ dPa_followEcallBack mpFollowEcallBack;
    /* 0x2C4 */ u8 field_0x2C4[0x2C5 - 0x2C4];
    /* 0x2C5 */ s8 field_0x2C5;
    /* 0x2C6 */ u8 field_0x2C6[0x2C7 - 0x2C6];
    /* 0x2C7 */ u8 field_0x2C7;
    /* 0x2C8 */ u16 field_0x2C8;
    /* 0x2CA */ u8 field_0x2CA[0x2CC - 0x2CA];
    /* 0x2CC */ int m_path_no;
    /* 0x2D0 */ int field_0x2D0;
    /* 0x2D4 */ int field_0x2D4;
    /* 0x2D8 */ int field_0x2D8;
    /* 0x2DC */ int field_0x2DC;
    /* 0x2E0 */ f32 field_0x2E0;
    /* 0x2E4 */ u8 field_0x2E4;
    /* 0x2E5 */ bool field_0x2E5;
    /* 0x2E6 */ u8 field_0x2E6[0x330 - 0x2E6];
    /* 0x330 */ Quaternion field_0x330[6];
    /* 0x390 */ u8 field_0x390[0x394 - 0x390];
    /* 0x394 */ f32 field_0x394;
    /* 0x398 */ u8 field_0x398[0x3B0 - 0x398];
    /* 0x3B0 */ cXyz field_0x3B0;
    /* 0x3BC */ u8 field_0x3BC[0x3C0 - 0x3BC];
    /* 0x3C0 */ dPath* mpPath;
    /* 0x3C4 */ u8 field_0x3C4[0x3C8 - 0x3C4];
    /* 0x3C8 */ J3DModel* mpModel;
    /* 0x3CC */ mDoExt_btkAnm mBtkAnm;
    /* 0x3E0 */ f32 field_0x3E0;
    /* 0x3E4 */ u8 field_0x3E4[0x3F0 - 0x3E4];
    /* 0x3F0 */ request_of_phase_process_class mPhs;
    /* 0x3F8 */ u8 field_0x3F8[0x400 - 0x3F8];
    /* 0x400 */ mDoExt_McaMorf* mpMorf;
    /* 0x404 */ dBgS_Acch mAcch;
    /* 0x5C8 */ dBgS_AcchCir mAcchCir;
    /* 0x608 */ mDoExt_invisibleModel mInvisibleModel;
    /* 0x610 */ cXyz field_0x610;
    /* 0x61C */ cXyz field_0x61C;
    /* 0x628 */ u8 field_0x628[0x630 - 0x628];
    /* 0x630 */ cXyz field_0x630;
    /* 0x63C */ cXyz field_0x63C;
    /* 0x648 */ int field_0x648;
    /* 0x64C */ int field_0x64C;
    /* 0x650 */ int field_0x650;
    /* 0x654 */ int field_0x654;
    /* 0x658 */ int field_0x658;
    /* 0x65C */ int field_0x65C;
    /* 0x660 */ cXyz field_0x660;
    /* 0x66C */ fopAc_ac_c* mpActorTarget;
    /* 0x670 */ fpc_ProcID mProcId;
    /* 0x674 */ cXyz mGrabPos;
    /* 0x680 */ u8 field_0x680[0x684 - 0x680];
    /* 0x684 */ int field_0x684;
    /* 0x688 */ u8 field_0x688[0x68C - 0x688];
    /* 0x68C */ s16 field_0x68C;
    /* 0x68E */ u8 field_0x68E[0x690 - 0x68E];
    /* 0x690 */ cXyz field_0x690;
    /* 0x69C */ cXyz field_0x69C;
    /* 0x6A8 */ fpc_ProcID mProcId2;
    /* 0x6AC */ u8 field_0x6AC[0x6B4 - 0x6AC];
    /* 0x6B4 */ int field_0x6B4;
    /* 0x6B8 */ u8 field_0x6B8;
    /* 0x6B9 */ u8 field_0x6B9[0x6BC - 0x6B9];
    /* 0x6BC */ Mtx field_0x6BC;
    /* 0x6EC */ u8 field_0x6EC[0x6F0 - 0x6EC];
    /* 0x6F0 */ dCcD_Stts mStts;
    /* 0x72C */ dCcD_Stts mStts2;
    /* 0x768 */ dCcD_Sph mSph;
    /* 0x894 */ dCcD_Cyl mCyl;
    /* 0x9C4 */ int field_0x9C4;
    /* 0x9C8 */ u8 mHitType;
    /* 0x9C9 */ u8 field_0x9C9[0x9CC - 0x9C9];
    /* 0x9CC */ fopAc_ac_c* mBaseTarget;
    /* 0x9D0 */ s16 field_0x9D0;
    /* 0x9D2 */ u8 field_0x9D2[0x9D4 - 0x9D2];
    /* 0x9D4 */ f32 field_0x9D4;
    /* 0x9D8 */ u8 field_0x9D8[0xA48 - 0x9D8];
    /* 0xA48 */ cXyz field_0xA48[12];
    /* 0xAD8 */ bool field_0xAD8[12];
    /* 0xAE4 */ u8 field_0xAE4;
    /* 0xAE5 */ u8 field_0xAE5;
    /* 0xAE6 */ u8 field_0xAE6[0xAE8 - 0xAE6];
    /* 0xAE8 */ enemyice mEnemyIce;
};  // Size: 0xEA0

#endif /* D_A_FM_H */
