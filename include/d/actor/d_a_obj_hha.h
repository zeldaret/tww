#ifndef D_A_OBJ_HHA_H
#define D_A_OBJ_HHA_H

#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class daObjHha_c;

class daObjHhaPart_c {
public:
    typedef void(daObjHhaPart_c::*daObjHhaPartCallBack)(daObjHha_c*);
public:
    void draw(daObjHha_c* arg) { if(mCbDraw) (this->*mCbDraw)(arg); }
    void execute(daObjHha_c* arg) { if(mCbExec) (this->*mCbExec)(arg); }
    void setExeProc(daObjHhaPartCallBack newCb) { mCbExec = newCb; }
    void start_move() { setExeProc(&daObjHhaPart_c::exe_move);}

    void init_data(float, float, u16, u8, u8);
    BOOL set_mdl_area(const char*, int);
    BOOL set_bgw(const char*, int);
    void init_mtx(cXyz, csXyz, cXyz);
    void exe_normal(daObjHha_c*);
    void exe_move(daObjHha_c*);
    void draw_normal(daObjHha_c*);
public:
    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ dBgW* mpBgw;
    /* 0x08 */ cXyz mPos; // Position offset from current.pos
    /* 0x14 */ cXyz mPosTarget;
    /* 0x20 */ cXyz mPosDeltaDir;
    /* 0x2C */ float mDeltaY;
    /* 0x30 */ u8 mPartIdx;
    /* 0x31 */ u8 mbMid;
    /* 0x34 */ daObjHhaPartCallBack mCbExec;
    /* 0x40 */ daObjHhaPartCallBack mCbDraw;

}; // Size : 0x4C

class daObjHhaSplash_c {
public:
    cXyz get_base_pos() { return mBasePos; };
    cXyz get_pos() { return mPos; };

    f32 get_pos_y() { return mPos.y; }
    void set_pos(cXyz& pos) { mPos.set(pos); }
    void set_pos_y(float y) { mPos.y = y; }
    bool chk_stop() { return mbIsActive == false; }
    
    void delete_s() {
#if VERSION == VERSION_DEMO
        if(mpEmitter != NULL){
            mSplashCb.remove();
            mpEmitter = NULL;
            mbIsActive = false;
        }
#else
        if(mSplashCb.getEmitter() != NULL){
            mSplashCb.remove();
            mbIsActive = false;
        }
#endif
    }

    void play_particle() {
#if VERSION == VERSION_DEMO
        if(mpEmitter != NULL){
            mpEmitter->playCreateParticle();
            mbIsActive = true;
        }
#else
        JPABaseEmitter* pSplashEmitter = mSplashCb.getEmitter();
        if(pSplashEmitter != NULL){
            pSplashEmitter->playCreateParticle();
            mbIsActive = true;
        }
#endif
    }
    
    void stop_particle() {
#if VERSION == VERSION_DEMO
        if(mpEmitter != NULL){
            mpEmitter->stopCreateParticle();
            mbIsActive = false;
        }
#else
        JPABaseEmitter* pSplashEmitter = mSplashCb.getEmitter();
        if(pSplashEmitter != NULL){
            pSplashEmitter->stopCreateParticle();
            mbIsActive = false;
        }
#endif
    }

    void create_s(u16, cXyz*, float, float, csXyz*);

public:
#if VERSION == VERSION_DEMO
    /* 0x00 */ JPABaseEmitter* mpEmitter;
#endif
    /* 0x00 */ dPa_followEcallBack mSplashCb;
    /* 0x14 */ cXyz mBasePos;
    /* 0x20 */ cXyz mPos;
    /* 0x2C */ csXyz mAngle;
    /* 0x32 */ bool mbIsActive;

}; // Size : 0x34

class daObjHhaYgush_c {
public:
    void anm_play(cXyz& pos) {
        set_pos(pos);
        mBtk.play();
        mBck.play();
        init_mtx();
    }
    BOOL check_draw() { return mbVisible; }
    void disp_off() { mbVisible = false; }
    void disp_on() { mbVisible = true; }
    cXyz get_base_pos() { return mBasePos; }
    void set_pos(cXyz newpos) { mPos = newpos; }

    BOOL create_area(const char*);
    void init_data(cXyz*, f32, csXyz*, cXyz*, dKy_tevstr_c*, u8);
    void init_mtx();
    void draw();

public:
    /* 0x000 */ J3DModel* M_mdl;
    /* 0x004 */ mDoExt_btkAnm mBtk;
    /* 0x018 */ mDoExt_bckAnm mBck;
    /* 0x028 */ dKy_tevstr_c mTev;
    /* 0x0D8 */ cXyz mBasePos;
    /* 0x0E4 */ cXyz mPos;
    /* 0x0F0 */ cXyz mScale;
    /* 0x0FC */ csXyz mRot;
    /* 0x102 */ u8 mbVisible;

}; // Size : 0x104

class daObjHha_c : public fopAc_ac_c {
public:
    inline BOOL check_sw(); // weak but not inlined

    static int solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    cPhs_State _create();
    bool _delete();
    void set_tex(float, float, int);
    void init_mtx();
    void init_co();
    float get_water_h();
    void set_splash_bottom_h();
    void set_splash_bottom_r();
    void set_splash_bottom_stop_r();
    void water_manager();
    void part_manager();
    void ygush_manager();
    bool _execute();
    bool _draw();

public:
#if VERSION > VERSION_DEMO
    static const dCcD_SrcCyl M_cyl_data;
    static const dCcD_SrcSph M_sph_data;
#endif
    static const char M_arcname[4];
    enum State_t  {State_OPEN = 0, State_SWITCHING = 1, State_CLOSED = 2};

    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ mDoExt_btkAnm mBtkA[2];
    /* 0x2BC */ request_of_phase_process_class mPhs;
    /* 0x2C4 */ dCcD_Stts mCylStts;
    /* 0x300 */ dCcD_Cyl mCyl;
    /* 0x430 */ bool mHitboxActive;
#if VERSION > VERSION_DEMO
    /* 0x434 */ dCcD_Stts mSphStts;
    /* 0x470 */ dCcD_Sph mSph;
#endif
    /* 0x59C */ daObjHhaYgush_c mYgush;
    /* 0x6A0 */ daObjHhaPart_c mPartA[2];
    /* 0x738 */ daObjHhaSplash_c mSplashA[2];
    /* 0x7A0 */ cXyz mPosOffset;
    /* 0x7AC */ u32 mSwitchNo;
    /* 0x7B0 */ u8 mIsMiddle;
    /* 0x7B2 */ s16 mPartTimer;
    /* 0x7B4 */ f32 mWtrScale;
    /* 0x7B8 */ f32 mWtrScaleMin;
    /* 0x7BC */ u16 mWtrTimer;
    /* 0X7BE */ u8 mWtrState;
    /* 0x7C0 */ s16 mEventIdx;
    /* 0x7C2 */ u8 mState;
    /* 0x7C3 */ bool mWaterSound;
};

#endif /* D_A_OBJ_HHA_H */
