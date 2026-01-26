#ifndef D_A_HOOKSHOT_H
#define D_A_HOOKSHOT_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_gnd_chk.h"
#include "f_op/f_op_actor_mng.h"

class daHookshot_shape : public J3DPacket {
public:
    void draw();
    daHookshot_shape() {}
    ~daHookshot_shape() {}
};

class daHookshot_c : public fopAc_ac_c {
public:
    typedef BOOL (daHookshot_c::*ProcFunc)();
    
    enum Mode {
        Mode_Wait = 0,
        Mode_Shot = 1,
        Mode_Return = 2,
        Mode_Pull = 3,
    };
    
    int getChainCnt() { return mChainCnt; }
    cXyz getMoveVec() const { return mMoveVec; }
    fpc_ProcID getCarryActorID() const { return mCarryActorID; }
    const csXyz* getHookAngle() { return &mHookAngle; }
    MtxP getMtxTop() { return mMtx; }
    u32 getSightHit() const { return const_cast<dCcD_Cps*>(&mSightCps)->ChkAtHit(); }
    const cXyz* getObjSightCrossPos() { return &mObjSightCrossPos; }
    void setObjSightCrossPos(const cXyz* pos) { mObjSightCrossPos = *pos; }
    void setCarryOffset(const cXyz* offset) { mCarryOffset = *offset; }

    bool checkWait() { return fopAcM_GetParam(this) == Mode_Wait; }
    bool checkShot() { return fopAcM_GetParam(this) == Mode_Shot; }
    void setShot() { fopAcM_SetParam(this, Mode_Shot); }
    bool checkReturn() { return fopAcM_GetParam(this) == Mode_Return; }
    void setReturn() { fopAcM_SetParam(this, Mode_Return); }
    bool checkPull() { return fopAcM_GetParam(this) == Mode_Pull; }

    BOOL getObjHookFlg() const { return mObjHookFlg; }
    void onObjHookFlg() { mObjHookFlg = TRUE; }
    void offObjHookFlg() { mObjHookFlg = FALSE; }
    bool checkShipRideFlg() const { return mShipRideFlg; }
    
    BOOL draw();
    BOOL procWait_init(BOOL);
    BOOL procWait();
    BOOL procShot();
    BOOL procPlayerPull();
    BOOL procReturn();
    BOOL execute();
    BOOL hookshot_delete();
    cPhs_State create();

private:
    /* 0x290 */ daHookshot_shape mShape;
    /* 0x2A0 */ bool m2A0;
    /* 0x2A1 */ u8 m2A1;
    /* 0x2A2 */ bool mShipRideFlg;
    /* 0x2A3 */ bool m2A3;
    /* 0x2A4 */ s16 m2A4;
    /* 0x2A6 */ u16 m2A6;
    /* 0x2A8 */ int mChainCnt;
    /* 0x2AC */ u32 mMtrlSndId;
    /* 0x2B0 */ BOOL mObjHookFlg;
    /* 0x2B4 */ csXyz mHookAngle;
    /* 0x2BA */ csXyz m2BA;
    /* 0x2C0 */ cXyz mMoveVec;
    /* 0x2CC */ cXyz mObjSightCrossPos;
    /* 0x2D8 */ dBgS_RopeLinChk mLinChk;
    /* 0x344 */ dBgS_ObjGndChk mGndChk;
    /* 0x398 */ dCcD_Stts mStts;
    /* 0x3D4 */ dCcD_Cps mSightCps;
    /* 0x50C */ cXyz mCarryOffset;
    /* 0x518 */ fpc_ProcID mCarryActorID;
    /* 0x51C */ Mtx mMtx;
    /* 0x54C */ ProcFunc mCurrProcFunc;
};

#endif /* D_A_HOOKSHOT_H */
