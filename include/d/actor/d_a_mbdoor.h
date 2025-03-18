#ifndef D_A_MBDOOR_H
#define D_A_MBDOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class daMbdoor_c : public fopAc_ac_c {
public:
    typedef BOOL (ActionFunc)(daMbdoor_c*);

    void setAction(u8 action) { mCurActionIdx = action; }

    inline BOOL draw();
    inline BOOL execute();
    cPhs_State create();
    
    u8 getSwbit();
    u8 getType();
    u8 getShapeType();
    const char* getArcName();
    u32 getFuBdl();
    u32 getLBdl();
    u32 getRBdl();
    u32 getToBdl();
    u32 getDzb();
    f32 getLOffset();
    f32 getROffset();
    f32 getToOffset();
    BOOL CreateHeap();
    void calcMtx();
    BOOL CreateInit();
    s32 getDemoAction();
    void demoProc();
    BOOL checkArea();
    BOOL checkUnlock();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpFuModel;
    /* 0x29C */ J3DModel* mpLModel;
    /* 0x2A0 */ J3DModel* mpRModel;
    /* 0x2A4 */ J3DModel* mpToModel;
    /* 0x2A8 */ dBgW* mpBgW;
    /* 0x2AC */ bool field_0x2ac;
    /* 0x2AD */ u8 field_0x2ad;
    /* 0x2AE */ u8 mCurActionIdx;
    /* 0x2AF */ u8 field_0x2AF[0x2B0 - 0x2AF];
    /* 0x2B0 */ s16 field_0x2b0;
    /* 0x2B2 */ s16 field_0x2b2;
    /* 0x2B4 */ s16 field_0x2b4;
    /* 0x2B6 */ u8 field_0x2b6;
    /* 0x2B7 */ u8 field_0x2B7[0x2B8 - 0x2B7];
    /* 0x2B8 */ s16 mAdjustmentTimer;
    /* 0x2BA */ u8 field_0x2BA[0x2BC - 0x2BA];
    /* 0x2BC */ s32 field_0x2bc;
    /* 0x2C0 */ s32 mEvtStaffId;
    /* 0x2C4 */ cXyz field_0x2c4;
    /* 0x2D0 */ cXyz mGoalPos;
    /* 0x2DC */ cXyz mGoal2Pos;
};

#endif /* D_A_MBDOOR_H */
