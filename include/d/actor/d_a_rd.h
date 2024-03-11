#ifndef D_A_RD_H
#define D_A_RD_H

#include "d/d_npc.h"
#include "d/d_jnt_hit.h"
#include "m_Do/m_Do_hostIO.h"
#include "SSystem/SComponent/c_phase.h"
#include "c/c_damagereaction.h"

class daRd_HIO_c : public mDoHIO_entry_c {
public:
    daRd_HIO_c();
    virtual ~daRd_HIO_c() {}
    
    /* 0x04 */ dNpc_HIO_c mNpc;
    /* 0x2C */ u8 m2C;
    /* 0x2D */ u8 m2D[0x30 - 0x2D];
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 mCryRadius;
    /* 0x3C */ f32 mAttackRadius;
    /* 0x40 */ s16 m40;
    /* 0x42 */ s16 mCrySpreadAngle;
    /* 0x44 */ s16 mAttackSpreadAngle;
    /* 0x46 */ s16 m46;
    /* 0x48 */ s16 m48;
    /* 0x4A */ s16 m4A;
    /* 0x4C */ s16 m4C;
    /* 0x4E */ s16 m4E;
    /* 0x50 */ s16 m50;
    /* 0x52 */ s16 m52;
    /* 0x54 */ s16 m54;
    /* 0x56 */ u8 m56[0x58 - 0x56];
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
    /* 0x60 */ f32 m60;
    /* 0x64 */ f32 m64;
    /* 0x68 */ f32 m68;
    /* 0x6C */ f32 mReturnWalkSpeed;
    /* 0x70 */ f32 m70;
    /* 0x74 */ f32 m74;
    /* 0x78 */ s16 m78;
    /* 0x7A */ s16 mParalysisDuration;
    /* 0x7C */ JntHit_HIO_c m7C;
};

class daRd_c : public fopEn_enemy_c {
public:
    enum Proc_e {
        PROC_INIT = 0,
        PROC_EXEC = 1
    };
    
    enum Mode {
        MODE_WAIT        = 0x0,
        MODE_DAMAGE      = 0x1,
        MODE_PARALYSIS   = 0x2,
        MODE_DEATH       = 0x3,
        MODE_MOVE        = 0x4,
        MODE_CRY         = 0x5,
        MODE_CRY_WAIT    = 0x6,
        MODE_ATTACK      = 0x7,
        MODE_RETURN      = 0x8,
        MODE_SILENT_PRAY = 0x9,
        MODE_SW_WAIT     = 0xA,
        MODE_KANOKE      = 0xB,
        MODE_NULL,
    };
    
    enum BckIdx {
        BckIdx_TACHIP     = 0x0,
        BckIdx_SUWARIP    = 0x1,
        BckIdx_WALK2ATACK = 0x2,
        BckIdx_ATACK      = 0x3,
        BckIdx_ATACK2WALK = 0x4,
        BckIdx_WALK       = 0x5,
        BckIdx_DAMAGE     = 0x6,
        BckIdx_DEAD       = 0x7,
        BckIdx_TATSU      = 0x8,
        BckIdx_SUWARU     = 0x9,
        BckIdx_KANOKEP    = 0xA,
        BckIdx_BEAM_HIT   = 0xB,
        BckIdx_BEAM       = 0xC,
        BckIdx_BEAM_END   = 0xD,
    };
    
    enum AnmPrm {
        AnmPrm_TACHIP0    = 0x0,
        AnmPrm_TACHIP1    = 0x1,
        AnmPrm_SUWARIP    = 0x2,
        AnmPrm_WALK2ATACK = 0x3,
        AnmPrm_ATACK      = 0x4,
        AnmPrm_ATACK2WALK = 0x5,
        AnmPrm_WALK       = 0x6,
        AnmPrm_DAMAGE     = 0x7,
        AnmPrm_DEAD       = 0x8,
        AnmPrm_TATSU      = 0x9,
        AnmPrm_SUWARU     = 0xA,
        AnmPrm_KANOKEP    = 0xB,
        AnmPrm_BEAM_HIT   = 0xC,
        AnmPrm_BEAM       = 0xD,
        AnmPrm_BEAM_END   = 0xE,
        AnmPrm_NULL,
    };
    
    typedef void (daRd_c::*ModeFunc)();
    
    static const u32 m_heapsize;
    static const char m_arc_name[];
    static const dCcD_SrcCyl m_cyl_src;
    
    daRd_c() {}
    bool isAnm(s8 idx) { return mAnmPrmIdx == idx; }
    void onIkari() { mbIkari = true; }
    void offIkari() { mbIkari = false; }
    bool isIkari() { return mbIkari; }
    void modeProcInit(int newMode) { modeProc(PROC_INIT, newMode); }
    
    fopAc_ac_c* _searchNearDeadRd(fopAc_ac_c*);
    BOOL _nodeControl(J3DNode*, J3DModel*);
    BOOL _nodeHeadControl(J3DNode*, J3DModel*);
    BOOL _createHeap();
    bool createArrowHeap();
    bool checkPlayerInAttack();
    bool checkPlayerInCry();
    void lookBack();
    bool checkTgHit();
    void setCollision();
    void setIceCollision();
    void setAttention();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeDeathInit();
    void modeDeath();
    void modeDamageInit();
    void modeDamage();
    void modeParalysisInit();
    void modeParalysis();
    void modeMoveInit();
    void modeMove();
    void modeCryInit();
    void modeCry();
    void modeCryWaitInit();
    void modeCryWait();
    void modeAttackInit();
    void modeAttack();
    void modeReturnInit();
    void modeReturn();
    void modeSilentPrayInit();
    void modeSilentPray();
    void modeSwWaitInit();
    void modeSwWait();
    void modeKanokeInit();
    void modeKanoke();
    void modeProc(Proc_e, int);
    void setBrkAnm(s8);
    void setBtkAnm(s8);
    void setAnm(s8, bool);
    bool _execute();
    void debugDraw();
    bool _draw();
    bool isLinkControl();
    void createInit();
    void getArg();
    s32 _create();
    bool _delete();
    
    /* 0x2AC */ int mMode;
    /* 0x2B0 */ u8 m2B0[0x2B4 - 0x2B0];
    /* 0x2B4 */ int mWhichIdleAnm;
    /* 0x2B8 */ int mAreaRadius;
    /* 0x2BC */ int mChecksSwitch;
    /* 0x2C0 */ int mSwNo;
    /* 0x2C4 */ u8 m2C4;
    /* 0x2C5 */ u8 mHitType; // TODO enum
    /* 0x2C6 */ u8 m2C6[0x2C8 - 0x2C6];
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2D4 */ mDoExt_btkAnm mBtkAnm;
    /* 0x2E8 */ mDoExt_brkAnm mBrkAnm;
    /* 0x300 */ cXyz mSpawnPos;
    /* 0x30C */ s16 mSpawnAngle;
    /* 0x30E */ u8 m30E[0x310 - 0x30E];
    /* 0x310 */ int mTimer1;
    /* 0x314 */ int mTimer2;
    /* 0x318 */ int mBreakFreeCounter;
    /* 0x31C */ dBgS_ObjAcch mAcch;
    /* 0x4E0 */ dBgS_AcchCir mAcchCir;
    /* 0x520 */ dCcD_Stts mStts;
    /* 0x55C */ dCcD_Cyl mCyl;
    /* 0x68C */ u8 m68C[0x690 - 0x68C];
    /* 0x690 */ u32 mShadowId;
    /* 0x694 */ mDoExt_invisibleModel mInvisModel;
    /* 0x69C */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x6D0 */ uint mCorpseID;
    /* 0x6D4 */ int m6D4;
    /* 0x6D8 */ s8 mBckIdx;
    /* 0x6D9 */ s8 mAnmPrmIdx;
    /* 0x6DA */ s8 m6DA;
    /* 0x6DB */ s8 m6DB;
    /* 0x6DC */ s8 m6DC;
    /* 0x6DD */ u8 m6DD[0x6E0 - 0x6DD];
    /* 0x6E0 */ enemyice mEnemyIce;
    /* 0xA98 */ enemyfire mEnemyFire;
    /* 0xCC0 */ JntHit_c* mpJntHit;
    /* 0xCC4 */ cXyz mTargetPos;
    /* 0xCD0 */ cXyz mRdEyePos;
    /* 0xCDC */ s16 mMaxHeadTurnVel;
    /* 0xCDE */ u8 mCDE[0xCE0 - 0xCDE];
    /* 0xCE0 */ int mCE0;
    /* 0xCE4 */ int mCE4;
    /* 0xCE8 */ Mtx mCE8;
    /* 0xD18 */ s16 mHeadAngle;
    /* 0xD1A */ s16 mD1A;
    /* 0xD1C */ s16 mD1C;
    /* 0xD1E */ s16 mD1E;
    /* 0xD20 */ u8 mD20[0xD2E - 0xD20];
    /* 0xD2E */ s16 mD2E;
    /* 0xD30 */ u8 mD30[0xD34 - 0xD30];
    /* 0xD34 */ bool mbIkari;
    /* 0xD35 */ u8 mD35[0xD38 - 0xD35];
    /* 0xD38 */ f32 mD38;
    /* 0xD3C */ int mD3C;
    /* 0xD40 */ int mD40;
};

#endif /* D_A_RD_H */
