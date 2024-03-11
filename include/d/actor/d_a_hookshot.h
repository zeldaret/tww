#ifndef D_A_HOOKSHOT_H
#define D_A_HOOKSHOT_H

#include "f_op/f_op_actor_mng.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_gnd_chk.h"

class daHookshot_shape : public J3DPacket {
public:
    void draw();
    daHookshot_shape() {}
    ~daHookshot_shape() {}
};

class daHookshot_c : public fopAc_ac_c {
public:
    typedef BOOL (daHookshot_c::*ProcFunc)();
    
    int getChainCnt() { return mChainCnt; }
    cXyz getMoveVec() const { return mMoveVec; }
    uint getCarryActorID() const { return mCarryActorID; }
    void getHookAngle() {}
    MtxP getMtxTop() { return mMtx; }
    void getObjHookFlg() const {}
    void getSightHit() const {}
    void getObjSightCrossPos() {}
    void onObjHookFlg() {}
    void offObjHookFlg() {}
    void checkPull() {}
    void checkReturn() {}
    void checkShipRideFlg() const {}
    void checkShot() {}
    void checkWait() {}
    void setObjSightCrossPos(const cXyz*) {}
    void setCarryOffset(const cXyz*) {}
    void setReturn() {}
    void setShot() {}
    
    daHookshot_c() {}
    BOOL draw();
    BOOL procWait_init(BOOL);
    BOOL procWait();
    BOOL procShot();
    BOOL procPlayerPull();
    BOOL procReturn();
    BOOL execute();
    BOOL hookshot_delete();
    s32 create();

public:
    /* 0x290 */ daHookshot_shape mShape;
    /* 0x2A0 */ bool m2A0;
    /* 0x2A1 */ u8 m2A1;
    /* 0x2A2 */ u8 m2A2;
    /* 0x2A3 */ u8 m2A3;
    /* 0x2A4 */ s16 m2A4;
    /* 0x2A6 */ u16 m2A6;
    /* 0x2A8 */ int mChainCnt;
    /* 0x2AC */ u32 mMtrlSndId;
    /* 0x2B0 */ int m2B0;
    /* 0x2B4 */ s16 m2B4;
    /* 0x2B6 */ s16 m2B6;
    /* 0x2B8 */ s16 m2B8;
    /* 0x2BA */ csXyz m2BA;
    /* 0x2C0 */ cXyz mMoveVec;
    /* 0x2CC */ cXyz m2CC;
    /* 0x2D8 */ dBgS_RopeLinChk mLinChk;
    /* 0x344 */ dBgS_ObjGndChk mGndChk;
    /* 0x398 */ dCcD_Stts mStts;
    /* 0x3D4 */ dCcD_Cps mCps;
    /* 0x50C */ cXyz m50C;
    /* 0x518 */ uint mCarryActorID;
    /* 0x51C */ Mtx mMtx;
    /* 0x54C */ ProcFunc mCurrProcFunc;
};

#endif /* D_A_HOOKSHOT_H */
