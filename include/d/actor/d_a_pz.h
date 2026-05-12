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
    void checkEyeArea(cXyz&);
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

    static const dCcD_SrcCyl m_cyl_src;
    static const char m_arc_name[];

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
    /* 0x071C */ u8 m071C[0x073E - 0x071C];
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
    /* 0x08B4 */ u8 m08B4[0x08C4 - 0x08B4];
    /* 0x08C4 */ cXyz m08C4;
    /* 0x08D0 */ u8 m08D0[0x08EA - 0x08D0];
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
    /* 0x0F08 */ u8 m0F08[0x0F44 - 0x0F08];
    /* 0x0F44 */ f32 m0F44;
    /* 0x0F48 */ u8 m0F48;
    /* 0x0F49 */ u8 m0F49[0x0F4C - 0x0F49];
    /* 0x0F4C */ cXyz mGanondorfPosCurrent;
    /* 0x0F58 */ cXyz mGanondorfPos4;
    /* 0x0F64 */ u8 mbHasGanondorf;
    /* 0x0F65 */ u8 m0F65;
    /* 0x0F66 */ u8 m0F66[0x0F70 - 0x0F66];
    /* 0x0F70 */ f32 m0F70;
    /* 0x0F74 */ u8 m0F74[0x0F7C - 0x0F74];
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
    /* 0x02C */ u8 m02C[0x05C - 0x02C];
    /* 0x05C */ f32 mAttackAimRange[3];
    /* 0x068 */ f32 mAttackShootChance[3];
    /* 0x074 */ f32 mAttackAimZeroChance[3];
    /* 0x080 */ s16 mAttackWaitTimer[3];
    /* 0x086 */ s16 mFollowTimerBase[3];
    /* 0x08C */ s16 mFollowTimerRange[3];
    /* 0x092 */ s16 mAttackTimerBase[3];
    /* 0x098 */ s16 mAttackTimerRange[3];
    /* 0x09E */ u8 m09E[0x0B4 - 0x09E];
    /* 0x0B4 */ f32 mBackStepSpeedY;
    /* 0x0B8 */ f32 mBackStepSpeedF;
    /* 0x0BC */ f32 mSideStepSpeedY;
    /* 0x0C0 */ f32 mSideStepSpeedF;
    /* 0x0C4 */ f32 mDownSpeedY;
    /* 0x0C8 */ f32 mDownSpeedF;
    /* 0x0CC */ s16 mDownTimer;
    /* 0x0CE */ u8 m0CE[0x0F8 - 0x0CE];
    /* 0x0F8 */ s16 mTalkTimer[3];
    /* 0x0FE */ u8 m0FE[0x10C - 0x0FE];
};

#endif /* D_A_PZ_H */
