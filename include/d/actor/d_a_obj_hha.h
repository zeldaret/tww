#ifndef D_A_OBJ_HHA_H
#define D_A_OBJ_HHA_H

#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class daObjHha_c;

class daObjHhaPart_c {
public:
    typedef void(daObjHhaPart_c::*daObjHhaPartCallBack)(daObjHha_c*);
public:
    void draw(daObjHha_c* arg) { if(cbDraw) (this->*cbDraw)(arg); }
    void execute(daObjHha_c* arg) { if(cbExec) (this->*cbExec)(arg); }
    void setExeProc(daObjHhaPartCallBack newCb) { cbExec = newCb; }
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
    /* 0x30 */ u8 partIdx;
    /* 0x31 */ u8 bMid;
    /* 0x34 */ daObjHhaPartCallBack cbExec;
    /* 0x40 */ daObjHhaPartCallBack cbDraw;

}; // Size : 0x4C

class daObjHhaSplash_c {
public:
    daObjHhaSplash_c() {}
    ~daObjHhaSplash_c() {}
    cXyz get_base_pos() { return mBasePos; };
    cXyz get_pos() { return mPos; };

    f32 get_pos_y() { return mPos.y; }
    void set_pos(cXyz& pos) { mPos.set(pos); }
    void set_pos_y(float y) { mPos.y = y; }
    bool chk_stop() { return bIsActive == false; }
    
    void delete_s() {
        if(mEcallBack.getEmitter() != NULL){
            mEcallBack.end();
            bIsActive = false;
        }
    }

    void play_particle() {
        JPABaseEmitter* pSplashEmitter = mEcallBack.getEmitter();
        if(pSplashEmitter != NULL){
            pSplashEmitter->clearStatus(1);
            bIsActive = true;
        }
    }
    
    void stop_particle() {
        JPABaseEmitter* pSplashEmitter = mEcallBack.getEmitter();
        if(pSplashEmitter != NULL){
            pSplashEmitter->setStatus(1);
            bIsActive = false;
        }
    }

    void create_s(unsigned short, cXyz*, float, float, csXyz*);

public:
    /* 0x00 */ dPa_followEcallBack mEcallBack;
    /* 0x14 */ cXyz mBasePos;
    /* 0x20 */ cXyz mPos;
    /* 0x2C */ csXyz mAngle;
    /* 0x32 */ bool bIsActive;

}; // Size : 0x34

class daObjHhaYgush_c {
public:
    void anm_play(cXyz& pos) {
        set_pos(pos);
        mBtk.play();
        mBck.play();
        init_mtx();
    }
    bool check_draw() { return bVisible != false; }
    void disp_off() { bVisible = false; }
    void disp_on() { bVisible = true; }
    cXyz get_base_pos() { return mBasePos; }
    void set_pos(cXyz newpos) { mPos = newpos; }

    BOOL create_area(const char*);
    void init_data(cXyz*, f32, csXyz*, cXyz*, dKy_tevstr_c*, u8);
    void init_mtx();
    BOOL draw();

public:
    /* 0x000 */ J3DModel* mpModel;
    /* 0x004 */ mDoExt_btkAnm mBtk;
    /* 0x018 */ mDoExt_bckAnm mBck;
    /* 0x028 */ dKy_tevstr_c mTev;
    /* 0x0D8 */ cXyz mBasePos;
    /* 0x0E4 */ cXyz mPos;
    /* 0x0F0 */ cXyz mScale;
    /* 0x0FC */ csXyz mRot;
    /* 0x102 */ u8 bVisible;

}; // Size : 0x104

class daObjHha_c : public fopAc_ac_c {
public:

    BOOL check_sw(); // weak but not inline?

    static int solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    s32 _create();
    BOOL _delete();
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
    BOOL _execute();
    BOOL _draw();

public:
    static const dCcD_SrcCyl M_cyl_data;
    static const dCcD_SrcSph M_sph_data;
    static const char M_arcname[4];
    enum State_t  {State_OPEN = 0, State_SWITCHING = 1, State_CLOSED = 2};

    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ mDoExt_btkAnm mBtkA[2];
    /* 0x2BC */ request_of_phase_process_class mPhs;
    /* 0x2C4 */ dCcD_Stts mCylStts;
    /* 0x300 */ dCcD_Cyl mCyl;
    /* 0x430 */ bool mHitboxActive;
    /* 0x434 */ dCcD_Stts mSphStts;
    /* 0x470 */ dCcD_Sph mSph;
    /* 0x59C */ daObjHhaYgush_c mYgush;
    /* 0x6A0 */ daObjHhaPart_c mPartA[2];
    /* 0x738 */ daObjHhaSplash_c mSplashA[2];
    /* 0x7A0 */ cXyz mPosOffset;
    /* 0x7AC */ u32 mSwitchNo;
    /* 0x7B0 */ u8 mIsMiddle;
    /* 0x7B2 */ short mPartTimer;
    /* 0x7B4 */ float fWtrScale;
    /* 0x7B8 */ float fWtrScaleMin;
    /* 0x7BC */ u16 mWtrTimer;
    /* 0X7BE */ u8 mWtrState;
    /* 0x7C0 */ short mEventIdx;
    /* 0x7C2 */ u8 mState;
    /* 0x7C3 */ bool mWaterSound;
};

#endif /* D_A_OBJ_HHA_H */
