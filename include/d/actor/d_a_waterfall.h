#ifndef D_A_WATERFALL_H
#define D_A_WATERFALL_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daWfall_c : public fopAc_ac_c {
public:
    typedef void (daWfall_c::*ModeProcFunc)();

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
    f32 getWaterScaleFromGatePos();
    f32 getWaterHeight();
    void set_se();

    static const char m_arcname[];
    static const s8 m_wait_timer;
    static const s16 m_heapsize[2];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpGateModel;
    /* 0x2A0 */ J3DModel* mpMinamoModel;
    /* 0x2A4 */ int mMode;
    /* 0x2A8 */ int mSwitchNo;
    /* 0x2AC */ mDoExt_btkAnm mBtk;
    /* 0x2C0 */ mDoExt_brkAnm mMinamoBrk;
    /* 0x2D8 */ mDoExt_btkAnm mMinamoBtk;
    /* 0x2EC */ dPa_followEcallBack mPtclCallBack0;
    /* 0x300 */ dPa_followEcallBack mPtclCallBack1;
    /* 0x314 */ cXyz mEmitter0Pos;
    /* 0x320 */ cXyz mEmitter1Pos;
    /* 0x32C */ u8 field_0x32C[0x338 - 0x32C];
    /* 0x338 */ csXyz mEmitter0Angle;
    /* 0x33E */ csXyz mEmitter1Angle;
    /* 0x344 */ cXyz mGatePos;
    /* 0x350 */ s16 mEventIdx;
    /* 0x352 */ s16 field_0x352;
    /* 0x354 */ u8 field_0x354;
    /* 0x355 */ u8 mDemoState;
    /* 0x356 */ u8 mType;
    /* 0x357 */ u8 field_0x357;
};  // Size: 0x358

#endif /* D_A_WATERFALL_H */
