#ifndef D_A_WATERFALL_H
#define D_A_WATERFALL_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

class J3DModel;

class daWfall_c : public fopAc_ac_c {
public:
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
    static const u8 m_wait_timer;
    static const s16 m_heapsize[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpGateModel;
    /* 0x2A0 */ J3DModel* mpMinamoModel;
    /* 0x2A4 */ int mMode;
    /* 0x2A8 */ int mSwNo;
    /* 0x2AC */ mDoExt_btkAnm mBtkAnm;
    /* 0x2C0 */ mDoExt_brkAnm mMinamoBrkAnm;
    /* 0x2D8 */ mDoExt_btkAnm mMinamoBtkAnm;
    /* 0x2EC */ dPa_followEcallBack mEmitterCb0;
    /* 0x300 */ dPa_followEcallBack mEmitterCb1;
    /* 0x314 */ cXyz mEmitterPos0;
    /* 0x320 */ cXyz mEmitterPos1;
    /* 0x32C */ u8 m32C[0x338 - 0x32C];
    /* 0x338 */ csXyz mEmitterAngle0;
    /* 0x33E */ csXyz mEmitterAngle1;
    /* 0x344 */ cXyz mGatePos;
    /* 0x350 */ s16 mEventIdx;
    /* 0x352 */ s16 m352;
    /* 0x354 */ u8 m354;
    /* 0x355 */ u8 mEvState;
    /* 0x356 */ u8 mType;
};  // Size: 0x358

#endif /* D_A_WATERFALL_H */
