#ifndef D_A_TBOX_H
#define D_A_TBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "d/d_bg_s_acch.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"

class daTbox_c : public fopAc_ac_c {
public:
    struct modelInfo {
        s16 modelId;
        s16 openBckId;
        s16 btkId;
        s16 brkId;
        s16 closedColId;
        s16 openColId;
    };
    enum {
        daTboxFlg_UNK_01 = 0x01,
        daTboxFlg_UNK_02 = 0x02,
        daTboxFlg_UNK_04 = 0x04,
        daTboxFlg_UNK_08 = 0x08,
        daTboxFlg_OPENING_e = 0x10,
        daTboxFlg_APPEARING_e = 0x20,
    };

    typedef BOOL (daTbox_c::*ActionFunc)();

    u8 getTboxNo() { return fopAcM_GetParam(this) >> 0x07 & 0x1F; }
    int getSwNo() { return fopAcM_GetParam(this) >> 0x0C & 0xFF; }
    u8 getItemNo() { return home.angle.z >> 8 & 0xFF; }
    void flagOn(u16 flag) { mFlags |= flag; }
    void flagOff(u16 flag) { mFlags &= ~flag; }
    void flagClr() { mFlags = 0; }
    BOOL flagCheck(u16 flag) { return mFlags & flag; }
    request_of_phase_process_class* getPhase() { return &mPhase; }
    bool action() { return (this->*mActionFunc)(); }
    void setAction(ActionFunc func) { mActionFunc = func; }
    void deleteProc() {
        if (mpBgWCurrent != NULL) {
            dComIfG_Bgsp()->Release(mpBgWCurrent);
        }
        mSmokeCB.remove();
    }

    inline BOOL draw();
    BOOL execute();
    cPhs_State commonShapeSet();
    cPhs_State effectShapeSet();
    cPhs_State envShapeSet();
    cPhs_State bgCheckSet();
    void searchRoomNo();
    void lightReady();
    BOOL checkEnv();
    BOOL checkOpen();
    modelInfo& getModelInfo();
    void clrDzb();
    void setDzb();
    void surfaceProc();
    BOOL checkRoomDisp(int);
    s32 getShapeType();
    s32 getFuncType();
    BOOL checkNormal();
    BOOL CreateHeap();
    void CreateInit();
    s32 boxCheck();
    void lightUpProc();
    void lightDownProc();
    void darkProc();
    void volmProc();
    void demoProcOpen();
    void demoInitAppear_Tact();
    void demoInitAppear();
    void demoProcAppear_Tact();
    void demoProcAppear();
    s32 demoProc();
    void OpenInit_com();
    void OpenInit();
    void setCollision();
    BOOL actionWait();
    BOOL actionDemo();
    BOOL actionDemo2();
    BOOL actionOpenWait();
    BOOL actionSwOnWait();
    BOOL actionSwOnWait2();
    BOOL actionGenocide();

public:
    /* 0x290 */ s32 mRoomNo;
    /* 0x294 */ request_of_phase_process_class mPhase;
    /* 0x29C */ J3DModel* mpChestMdl;
    /* 0x2A0 */ mDoExt_bckAnm mOpenAnm;
    /* 0x2B0 */ mDoExt_btkAnm* mpAppearTexAnm;
    /* 0x2B4 */ mDoExt_brkAnm* mpAppearRegAnm;
    /* 0x2B8 */ dBgW* mpBgWClosed;
    /* 0x2BC */ dBgW* mpBgWOpen;
    /* 0x2C0 */ dBgW* mpBgWVines;
    /* 0x2C4 */ dBgW* mpBgWCurrent;
    /* 0x2C8 */ J3DModel* mpFlashMdl;
    /* 0x2CC */ mDoExt_bckAnm mFlashAnm;
    /* 0x2DC */ mDoExt_btkAnm mFlashTexAnm;
    /* 0x2F0 */ mDoExt_brkAnm mFlashRegAnm;
    /* 0x308 */ u32 m0308;
    /* 0x30C */ mDoExt_brkAnm mBrkAnm3;
    /* 0x324 */ J3DModel* mpTactPlatformMdl;
    /* 0x328 */ mDoExt_brkAnm mTactPlatformBrk;
    /* 0x340 */ ActionFunc mActionFunc;
    /* 0x34C */ f32 mInvisibleScrollVal;
    /* 0x350 */ int mStaffId;
    /* 0x354 */ Mtx mMtx;
    /* 0x384 */ LIGHT_INFLUENCE mPLight;
    /* 0x3A4 */ LIGHT_INFLUENCE mEfLight;
    /* 0x3C4 */ dPa_smokeEcallBack mSmokeCB;
    /* 0x3E4 */ JPABaseEmitter* mSmokeEmitter;
    /* 0x3E8 */ f32 mAllColRatio;
    /* 0x3EC */ f32 mAppearingYOffset;
    /* 0x3F0 */ u16 mFlags;
    /* 0x3F2 */ u16 mOpenTimer;
    /* 0x3F4 */ bool mHasOpenAnmFinished;
    /* 0x3F5 */ bool mIsFlashPlaying;
    /* 0x3F6 */ u16 mAppearTimer;
    /* 0x3F8 */ u8 mGenocideDelayTimer;
    /* 0x3FC */ dBgS_ObjAcch mObjAcch;
    /* 0x5C0 */ dBgS_AcchCir mAcchCir;
    /* 0x600 */ dCcD_Stts mColStatus;
    /* 0x63C */ dCcD_Cyl mColCyl;
    /* 0x76C */ u8 mTboxNo;
};

class daTbox_HIO_c : public JORReflexible {
public:
    daTbox_HIO_c();
    virtual ~daTbox_HIO_c() { }

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x06 */ s16 m06;
    /* 0x08 */ s16 m08;
    /* 0x0A */ s16 m0A;
    /* 0x0C */ s16 m0C;
};

#endif /* D_A_TBOX_H */
