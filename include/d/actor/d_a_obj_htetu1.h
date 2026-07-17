#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class dBgW;

class daObjHtetu1Splash_c {
public:
    bool chk_stop() { return mbIsActive == false; }

    void delete_s() {
        if (mSplashCb.getEmitter() != NULL) {
            mSplashCb.remove();
            mbIsActive = false;
        }
    }

    s16 get_timer() { return mTimer; }

    void play_particle() {
        JPABaseEmitter* emitter = mSplashCb.getEmitter();
        if (emitter != NULL) {
            emitter->playCreateParticle();
            mbIsActive = true;
        }
    }

    void set_pos_y(f32 i_y) { mPos.y = i_y; }

    void stop_particle() {
        JPABaseEmitter* emitter = mSplashCb.getEmitter();
        if (emitter != NULL) {
            emitter->stopCreateParticle();
            mbIsActive = false;
        }
    }

    void sub_timer() { mTimer--; }

    void timer_play_particle(s16 i_timer) {
        JPABaseEmitter* emitter = mSplashCb.getEmitter();
        if (emitter != NULL) {
            emitter->playCreateParticle();
            mbIsActive = true;
            mTimer = i_timer;
        }
    }

    void create_s(u16 i_particleID, cXyz* i_pos, csXyz* i_angle, dKy_tevstr_c* i_tevStr);

public:
    /* 0x00 */ dPa_followEcallBack mSplashCb;
    /* 0x14 */ Vec mPos;
    /* 0x20 */ S16Vec mAngle;
    /* 0x26 */ s16 mTimer;
    /* 0x28 */ u8 mbIsActive;
}; // Size: 0x2C

class daObjHtetu1_c : public fopAc_ac_c {
public:
    inline BOOL check_sw();

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
    static const char M_arcname[7];

    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ u32 mSwitchNo;
    /* 0x2A0 */ cXyz mPos;
    /* 0x2AC */ cXyz mOffset;
    /* 0x2B8 */ f32 mLowerY;
    /* 0x2BC */ f32 mUnlockSpeed;
    /* 0x2C0 */ u16 mUnlockTimer;
    /* 0x2C2 */ u8 mUnlockState;
    /* 0x2C4 */ s16 mEventIdx;
    /* 0x2C6 */ u8 mEventState;
    /* 0x2C8 */ s16 mQuakeTimer;
    /* 0x2CC */ dBgW* mpBgw;
    /* 0x2D0 */ daObjHtetu1Splash_c mSplash[2];
}; // Size: 0x328

#endif /* D_A_OBJ_HTETU1_H */
