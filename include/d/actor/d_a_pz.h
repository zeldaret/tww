#ifndef D_A_PZ_H
#define D_A_PZ_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"
#include "JSystem/J3DGraphAnimator/J3DMaterialAnm.h"
#include "m_Do/m_Do_hostIO.h"

class daPz_matAnm_c : public J3DMaterialAnm {
public:
    daPz_matAnm_c();
    virtual void calc(J3DMaterial*) const;

    void clrMoveFlag() { mMoveFlag = false; }
    f32 getNowOffsetX() { return mNowOffsetX; }
    f32 getNowOffsetY() { return mNowOffsetY; }
    void setMoveFlag() { mMoveFlag = true; }

private:
    /* 0x6C */ f32 mNowOffsetX;
    /* 0x70 */ f32 mNowOffsetY;
    /* 0x74 */ u8 m74[0x7C - 0x74];
    /* 0x7C */ bool mMoveFlag;
};

class daPz_c : public fopNpc_npc_c {
public:
    enum Proc_e {
        
    };

    MtxP getRightHandMatrix() { return mpMorf->getModel()->getAnmMtx(0x13); } // hand_R1 joint
    void isAnm(s8) {}
    void isEyeAnm(s8) {}
    void modeProcInit(int) {}
    void setAfraid() {}
    void setDown() { m08EA = true; }
    void setMove() {}
    void setStand() {}

    void _nodeHeadControl(J3DNode*, J3DModel*);
    void _nodeWaistControl(J3DNode*, J3DModel*);
    void _nodeWaist2Control(J3DNode*, J3DModel*);
    void _nodeSkirtControl(J3DNode*, J3DModel*);
    int bodyCreateHeap();
    int bowCreateHeap();
    bool _createHeap();
    void getGndPos();
    BOOL checkEyeArea(cXyz&);
    virtual u32 getMsg();
    virtual u16 next_msgStatus(u32*);
    virtual void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    void setFallSplash();
    void setHeadSplash();
    void setRipple();
    void setJntStatus();
    void demo();
    void checkTgHit();
    void getArg();
    void setAttention();
    void setBowAnm(s8, bool);
    void setBowString(bool);
    void setAnm(s8, bool, int);
    void setAnmRunSpeed();
    void setEyeBtp(int);
    void setEyeBtk(int);
    void setEyeAnm(s8);
    void ctrlEye();
    void playEyeAnm();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeMoveInit();
    void modeMove();
    void modeAttackWaitInit();
    void modeAttackWait();
    void modeAttackInit();
    void modeAttack();
    void modeDefendInit();
    void modeDefend();
    void modeDownInit();
    void modeDown();
    void modeAfraidInit();
    void modeAfraid();
    void modeSideStepInit();
    void modeSideStep();
    void modeBackStepInit();
    void modeBackStep();
    void modeTalkInit();
    void modeTalk();
    void modeFollowInit();
    void modeFollow();
    void modeProc(Proc_e, int);
    bool _execute();
    void bowDraw();
    void bodyDraw();
    void drawShadow();
    bool _draw();
    void bodyCreateInit();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const u32 m_heapsize;
    static const char m_arc_name[];
    static const f32 m_smoke_ef;
    static const f32 m_grass_ef;
    static const f32 m_splash_ef;
    static const dCcD_SrcCyl m_cyl_src;

public:
    /* 0x06C4 */ int mMode;
    /* 0x06C8 */ int m06C8;
    /* 0x06CC */ int m06CC;
    /* 0x06D0 */ u8 m06D0[0x06D3 - 0x06D0];
    /* 0x06D3 */ u8 m06D3;
    /* 0x06D4 */ u8 m06D4[0x06D5 - 0x06D4];
    /* 0x06D5 */ u8 mCurEye;
    /* 0x06D6 */ u8 m06D6[0x06E0 - 0x06D6];
    /* 0x06E0 */ dPa_rippleEcallBack mRipple;
    /* 0x06F4 */ dPa_followEcallBack mFallSplash;
    /* 0x0708 */ dPa_followEcallBack mHeadSplash;
    /* 0x071C */ cXyz mFallSplashPos;
    /* 0x0728 */ int mFallRippleTimer;
    /* 0x072C */ cXyz mHeadCenterPos;
    /* 0x0738 */ u8 m0738[0x073E - 0x0738];
    /* 0x073E */ u8 mbEyesFollowGanondorf;
    /* 0x073F */ u8 m073F;
    /* 0x0740 */ u8 m0740[0x076C - 0x0740];
    /* 0x076C */ request_of_phase_process_class mPhs;
    /* 0x0774 */ u32 m0774;
    /* 0x0778 */ mDoExt_invisibleModel mInvisibleModel;
    /* 0x0780 */ dKy_tevstr_c mTevstr;
    /* 0x0830 */ u8 m0830[0x08A8 - 0x0830];
    /* 0x08A8 */ J3DMaterialAnm* m08A8[1];
    /* 0x08AC */ u8 m08AC[0x08B0 - 0x08AC];
    /* 0x08B0 */ int m08B0;
    /* 0x08B4 */ u8 m08B4[0x08B8 - 0x08B4];
    /* 0x08B8 */ cXyz mHeadTopPos;
    /* 0x08C4 */ cXyz m08C4;
    /* 0x08D0 */ u8 m08D0[0x08DC - 0x08D0];
    /* 0x08DC */ cXyz mHeadFrontPos;
    /* 0x08E8 */ u8 m08E8[0x08EA - 0x08E8];
    /* 0x08EA */ u8 m08EA;
    /* 0x08EB */ u8 m08EB[0x08EC - 0x08EB];
    /* 0x08EC */ int m08EC;
    /* 0x08F0 */ int m08F0;
    /* 0x08F4 */ int m08F4;
    /* 0x08F8 */ u8 m08F8[0x0920 - 0x08F8];
    /* 0x0920 */ int m0920;
    /* 0x0924 */ f32 m0924;
    /* 0x0928 */ enemyice mEventIce;
    /* 0x0CE0 */ enemyfire mEnemyFire;
    /* 0x0F08 */ Mtx mWaistMtx;
    /* 0x0F38 */ cXyz mWaistPos;
    /* 0x0F44 */ f32 m0F44;
    /* 0x0F48 */ u8 m0F48;
    /* 0x0F49 */ u8 m0F49[0x0F4C - 0x0F49];
    /* 0x0F4C */ cXyz mGanondorfPosCurrent;
    /* 0x0F58 */ cXyz mGanondorfPos4;
    /* 0x0F64 */ u8 mbHasGanondorf;
    /* 0x0F65 */ u8 m0F65;
    /* 0x0F66 */ u8 m0F66;
    /* 0x0F67 */ u8 mEyeBtpState;
    /* 0x0F68 */ u8 m0F68[0x0F70 - 0x0F68];
    /* 0x0F70 */ f32 m0F70;
    /* 0x0F74 */ u8 m0F74[0x0F78 - 0x0F74];
    /* 0x0F78 */ s16 mWaist2RotZ;
    /* 0x0F7A */ s16 mWaist2RotY;
    /* 0x0F7C */ int m0F7C;
    /* 0x0F80 */ u8 m0F80;
    /* 0x0F81 */ u8 m0F81[0x0F82 - 0x0F81];
    /* 0x0F82 */ u8 m0F82;
    /* 0x0F83 */ u8 m0F83[0x0F84 - 0x0F83];
    /* 0x0F84 */ int mArg;
    /* 0x0F88 */ u8 m0F88;
    /* 0x0F89 */ u8 m0F89[0x0F8C - 0x0F89];
    /* 0x0F8C */ mDoExt_McaMorf* mpBowMcaMorf;
    /* 0x0F90 */ mDoExt_brkAnm mBrkAnm;
    /* 0x0FA8 */ mDoExt_btkAnm mBtkAnm;
    /* 0x0FBC */ mDoExt_btpAnm mBtpAnm;
    /* 0x0FD0 */ u8 m0FD0[0x1049 - 0x0FD0];
};

class daPz_HIO_c : public mDoHIO_entry_c {
public:
    daPz_HIO_c();
    virtual ~daPz_HIO_c() {}

public:
    /* 0x004 */ dNpc_HIO_c mNpc;
    /* 0x02C */ u8 m02C;
    /* 0x02D */ u8 m02D;
    /* 0x02E */ u8 m02E[0x02F - 0x02E];
    /* 0x02F */ u8 m02F;
    /* 0x030 */ u8 m030;
    /* 0x031 */ u8 m031;
    /* 0x032 */ u8 m032;
    /* 0x033 */ u8 m033;
    /* 0x034 */ u8 m034[0x03E - 0x034];
    /* 0x03E */ u8 m03E[0x040 - 0x03E];
    /* 0x040 */ f32 m040;
    /* 0x044 */ f32 m044;
    /* 0x048 */ f32 m048;
    /* 0x04C */ f32 m04C;
    /* 0x050 */ f32 m050;
    /* 0x054 */ s16 m054;
    /* 0x056 */ u8 m056[0x058 - 0x056];
    /* 0x058 */ f32 m058;
    /* 0x05C */ f32 mAttackAimRange[3];
    /* 0x068 */ f32 mAttackShootChance[3];
    /* 0x074 */ f32 mAttackAimZeroChance[3];
    /* 0x080 */ s16 mAttackWaitTimer[3];
    /* 0x086 */ s16 mFollowTimerBase[3];
    /* 0x08C */ s16 mFollowTimerRange[3];
    /* 0x092 */ s16 mAttackTimerBase[3];
    /* 0x098 */ s16 mAttackTimerRange[3];
    /* 0x09E */ u8 m09E[0x0A0 - 0x09E];
    /* 0x0A0 */ f32 m0A0;
    /* 0x0A4 */ u8 m0A4[0x0A8 - 0x0A4];
    /* 0x0A8 */ f32 m0A8;
    /* 0x0AC */ f32 m0AC;
    /* 0x0B0 */ f32 m0B0;
    /* 0x0B4 */ f32 mBackStepSpeedY;
    /* 0x0B8 */ f32 mBackStepSpeedF;
    /* 0x0BC */ f32 mSideStepSpeedY;
    /* 0x0C0 */ f32 mSideStepSpeedF;
    /* 0x0C4 */ f32 mDownSpeedY;
    /* 0x0C8 */ f32 mDownSpeedF;
    /* 0x0CC */ s16 mDownTimer;
    /* 0x0CE */ u8 m0CE[0x0D0 - 0x0CE];
    /* 0x0D0 */ f32 m0D0;
    /* 0x0D4 */ f32 m0D4;
    /* 0x0D8 */ f32 m0D8;
    /* 0x0DC */ s16 m0DC;
    /* 0x0DE */ s16 m0DE;
    /* 0x0E0 */ s16 m0E0;
    /* 0x0E2 */ s16 m0E2[4];
    /* 0x0EA */ u8 m0EA[0x0EC - 0x0EA];
    /* 0x0EC */ f32 m0EC;
    /* 0x0F0 */ f32 m0F0;
    /* 0x0F4 */ f32 m0F4;
    /* 0x0F8 */ s16 mTalkTimer[3];
    /* 0x0FE */ u8 m0FE[0x100 - 0x0FE];
    /* 0x100 */ f32 m100;
    /* 0x104 */ u8 m104[0x108 - 0x104];
    /* 0x108 */ f32 m108;
};

#endif /* D_A_PZ_H */
