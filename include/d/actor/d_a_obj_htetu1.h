#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"


class daObjHtetu1Splash_c {
public:
    bool chk_stop() { return !mPlaying; }

    void delete_s() {
#if VERSION == VERSION_DEMO
        if (mpEmitter != NULL) {
            mSplashCb.remove();
            mpEmitter = NULL;
            mPlaying = false;
        }
#else
        if (mSplashCb.getEmitter() != NULL) {
            mSplashCb.remove();
            mPlaying = false;
        }
#endif
    }
    
    s16 get_timer() { return mTimer; }
    
    void play_particle() {
#if VERSION == VERSION_DEMO
        if (mpEmitter != NULL) {
            mpEmitter->playCreateParticle();
            mPlaying = true;
        }
#else
        if (mSplashCb.getEmitter() != NULL) {
            mSplashCb.getEmitter()->playCreateParticle();
            mPlaying = true;
        }
#endif
    }
    void set_pos_y(float y) { mPos.y = y; }
    
    void stop_particle() {
#if VERSION == VERSION_DEMO
        if (mpEmitter != NULL) {
            mpEmitter->stopCreateParticle();
            mPlaying = false;
        }
#else
        if (mSplashCb.getEmitter() != NULL) {
            mSplashCb.getEmitter()->stopCreateParticle();
            mPlaying = false;
        }
#endif
    }

    void sub_timer() { mTimer--; }

    void timer_play_particle(short time) {
#if VERSION == VERSION_DEMO
        if (mpEmitter != NULL) {
            mpEmitter->playCreateParticle();
            mPlaying = true;
            mTimer = time;
        }
#else
        if (mSplashCb.getEmitter() != NULL) {
            mSplashCb.getEmitter()->playCreateParticle();
            mPlaying = true;
            mTimer = time;
        }
#endif
    }

    void create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*);

public:
#if VERSION == VERSION_DEMO
    /* 0x00 */ JPABaseEmitter* mpEmitter;
#endif
    /* 0x00 */ dPa_followEcallBack mSplashCb;
    /* 0x14 */ cXyz mPos;
    /* 0x20 */ csXyz mRot;
    /* 0x26 */ s16 mTimer;
    /* 0x28 */ bool mPlaying;
    /* 0x29 */ u8 field_0x29[0x2C - 0x29];
};  // Size: 0x2C


class daObjHtetu1_c : public fopAc_ac_c {
public:
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
        static const char M_arcname[7];

public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhase;
    /* 0x29C */ u32 field_0x29C;
    /* 0x2A0 */ cXyz field_0x2A0;
    /* 0x2AC */ cXyz field_0x2AC;
    /* 0x2B8 */ f32 field_0x2B8;
    /* 0x2BC */ f32 field_0x2BC;
    /* 0x2C0 */ u16 field_0x2C0;
    /* 0x2C2 */ u8 field_0x2C2;
    /* 0x2c3 */ u8 field_0x2c3;
    /* 0x2C4 */ s16 field_0x2C4;
    /* 0x2C6 */ u8 field_0x2C6;
    /* 0x2C7 */ s8 field_0x2C7;
    /* 0x2C8 */ s16 field_0x2C8;
    /* 0x2CA */ u8 field_0x2CA[0x2CC - 0x2CA];
    /* 0x2CC */ dBgW* mpBgW;
    /* 0x2D0 */ daObjHtetu1Splash_c mSplash[2];
};  // Size: 0x328

#endif /* D_A_OBJ_HTETU1_H */
