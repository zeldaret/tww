#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class J3DModel;
class dBgW;
class dKy_tevstr_c;

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
        if (!mbIsActive) {
            JPABaseEmitter* emitter = mSplashCb.getEmitter();
            if (emitter != NULL) {
                emitter->playCreateParticle();
                mbIsActive = true;
            }
        }
    }

    void set_pos_y(float y) { mPos.y = y; }

    void stop_particle() {
        if (mbIsActive) {
            JPABaseEmitter* emitter = mSplashCb.getEmitter();
            if (emitter != NULL) {
                emitter->stopCreateParticle();
                mbIsActive = false;
            }
        }
    }

    void sub_timer() { mTimer--; }

    void timer_play_particle(short timer) {
        JPABaseEmitter* emitter = mSplashCb.getEmitter();
        if (emitter != NULL) {
            emitter->playCreateParticle();
            mbIsActive = true;
            mTimer = timer;
        }
    }

    void create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*);

public:
    /* 0x00 */ dPa_followEcallBack mSplashCb;
    /* 0x14 */ cXyz mPos;
    /* 0x20 */ csXyz mAngle;
    /* 0x26 */ s16 mTimer;
    /* 0x28 */ bool mbIsActive;
};  // Size: 0x2C

class daObjHtetu1_c : public fopAc_ac_c {
public:
    inline BOOL check_sw(); // weak but not inlined

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

    static const char M_arcname[];

public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ int mSwNo;
    /* 0x2A0 */ cXyz mPos;
    /* 0x2AC */ cXyz mShake;
    /* 0x2B8 */ f32 mLowY;
    /* 0x2BC */ f32 mAmp;
    /* 0x2C0 */ u16 mTimer;
    /* 0x2C2 */ u8 mMoveState;
    /* 0x2C4 */ s16 mEventIdx;
    /* 0x2C6 */ u8 mEvState;
    /* 0x2C8 */ s16 mQuakeTimer;
    /* 0x2CC */ dBgW* mpBgW;
    /* 0x2D0 */ daObjHtetu1Splash_c mSplash[2];
};  // Size: 0x328

#endif /* D_A_OBJ_HTETU1_H */
