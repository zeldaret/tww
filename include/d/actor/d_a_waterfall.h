#ifndef D_A_WATERFALL_H
#define D_A_WATERFALL_H

#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daWfall_c : public fopAc_ac_c {
public:
    static const char m_arcname[];
    static const u8 m_wait_timer;
    static const s16 m_heapsize[];

    inline bool _draw();

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    void set_gate_mtx();
    void set_minamo_mtx();
    bool _execute();
    void mode_proc_call();
    void mode_wtr_on_init();
    void mode_wtr_on();
    void mode_wtr_off_init();
    void mode_wtr_off();
    BOOL setEmitter00Pos();
    BOOL setEmitter01Pos();
    float getWaterScaleFromGatePos();
    float getWaterHeight();
    void set_se();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mModelWater;
    /* 0x29C */ J3DModel* mModelGate;
    /* 0x2A0 */ J3DModel* mModelMinamo; // water surface model
    /* 0x2A4 */ int mModeProc;
    /* 0x2A8 */ int mWtrSwitch;
    /* 0x2AC */ mDoExt_btkAnm mBtkAnm;
    /* 0x2C0 */ mDoExt_brkAnm mBrkAnm;
    /* 0x2D8 */ mDoExt_btkAnm mBtkAnm2;
    /* 0x2EC */ dPa_followEcallBack mPCallBack;
    /* 0x300 */ dPa_followEcallBack mPCallBack2;
    /* 0x314 */ cXyz mParticlePos1;
    /* 0x320 */ cXyz mParticlePos2;
    /* 0x32C */ u8 field_0x32C[0x338 - 0x32C];
    /* 0x338 */ csXyz mParticleAngle1;
    /* 0x33E */ csXyz mParticleAngle2;
    /* 0x344 */ Vec mSePos;
    /* 0x350 */ s16 mEvtIdx;
    /* 0x352 */ s16 mSomeState;
    /* 0x354 */ u8 field_0x354[0x355 - 0x354];
    /* 0x355 */ u8 mSomeCounter;
    /* 0x356 */ u8 mType;
    /* 0x357 */ u8 field_0x357[0x358 - 0x357];
}; // Size: 0x358

#endif /* D_A_WATERFALL_H */
