#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "d/d_bg_s_wtr_chk.h"

class dBgW;

class daObjHtetu1Splash_c : public dPa_followEcallBack {
public:
    daObjHtetu1Splash_c() {}
    virtual ~daObjHtetu1Splash_c() {}
    void create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*);

    void chk_stop() {}
    void delete_s() {}
    s16 get_timer() { return mTimer; }
    void play_particle() {}
    void set_pos_y(float y) { mPos.y = y; }
    void stop_particle() {}
    void sub_timer() {
        if (mTimer > 0) {
            mTimer--;
        }
    }
    void timer_play_particle(short) {}

public:
    /* 0x14 */ cXyz mPos;
    /* 0x20 */ csXyz mRot;
    /* 0x26 */ s16 mTimer;
    /* 0x28 */ u8 mState;
};

class daObjHtetu1_c : public fopAc_ac_c {
public:
    static const char M_arcname[];

    // TODO: this function is marked as weak in the REL symbol map, but it does not get inlined for some reason?
    // void check_sw() {}
    BOOL check_sw();

    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    void unlock();
    f32 get_water_h();
    void splash_manager();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhase;
    /* 0x29C */ int mSw;
    /* 0x2A0 */ cXyz mTargetPos;
    /* 0x2AC */ cXyz mGatePos;
    /* 0x2B8 */ float mBaseY;
    /* 0x2BC */ float mSpeedY;
    /* 0x2C0 */ u16 mMoveTimer;
    /* 0x2C2 */ u8 mState;
    /* 0x2C3 */ u8 pad_0x2C3;
    /* 0x2C4 */ s16 mEventIdx;
    /* 0x2C6 */ u8 mMode;
    /* 0x2C7 */ u8 pad_0x2C7;
    /* 0x2C8 */ s16 mQuakeTimer;
    /* 0x2CA */ u8 pad_0x2CA[2];
    /* 0x2CC */ dBgW* mpBgW;
    /* 0x2D0 */ daObjHtetu1Splash_c mSplash[2];
};

#endif /* D_A_OBJ_HTETU1_H */
