#ifndef D_A_BOKO_H
#define D_A_BOKO_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class dBgS_ObjLinChk;

struct ke_c_s {
    
};

class daBoko_c : public fopAc_ac_c {
public:
    typedef BOOL (daBoko_c::*ProcFunc_t)();
    
    daBoko_c();

    static Vec m_top_offset[6];
    static Vec m_blur_root_offset[6];
    static Vec m_root_offset[6];
    static f32 m_cps_r[6];
    static s32 m_at_point[6];
    static u32 m_at_type[6];
    static f32 m_jump_blur_rate[6];
    static f32 m_blur_rate[6];
    static u8 m_se_type[6];

    static dBgS_ObjGndChk m_ground_check;
    static dBgS_ObjLinChk m_line_check;

    f32 getCpsR() { return m_cps_r[fopAcM_GetParam(this)]; }
    s32 getAtPoint() { return m_at_point[fopAcM_GetParam(this)]; }
    u32 getAtType() { return m_at_type[fopAcM_GetParam(this)]; }
    f32 getJumpBlurRate() { return m_jump_blur_rate[fopAcM_GetParam(this)]; }
    f32 getBlurRate() { return m_blur_rate[fopAcM_GetParam(this)]; }
    u8 getSeType() { return m_se_type[fopAcM_GetParam(this)]; }
    
    void getFlameTimer() {}
    void getNowMode() {}
    void setNowMode(int) {}
    void moveStateInit(f32 speedForward, f32 speedY, s16 angleY) {
        speed.y = speedY;
        speedF = speedForward;
        current.angle.y = angleY;
    }
    void onFloorFlg() {} // maybe: m2BC = 1;
    void setMatrix(Mtx mtx) {
        if (mpModel) {
            mpModel->setBaseTRMtx(mtx);
        }
    }
    void setRotAngleSpeed(s16 speed) { m2C2 = speed; }
    void setThrow(s16) {} // maybe m2BA

    void getTopPos(cXyz*);
    void getBlurRootPos(cXyz*);
    void keDraw();
    void keCalc1(ke_c_s*, int);
    void keCalc();
    BOOL draw();
    void setTopRootPos(int);
    void setBaseMatrix();
    BOOL checkNoDraw();
    void setFlameEffect();
    void setRoomInfo();
    void setThrowReverse(s16);
    BOOL procWait_init();
    BOOL procWait();
    BOOL procMove_init();
    BOOL procMove();
    BOOL procThrow();
    BOOL procCarry();
    BOOL execute();
    void bokoDelete();
    BOOL createHeap();
    cPhs_State create();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_brkAnm mBrkAnm;
    /* 0x2B4 */ u8 m2B4[0x2B8 - 0x2B4];
    /* 0x2B8 */ u8 mCurrentAction;
    /* 0x2B9 */ u8 m2B9;
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD[0x2C0 - 0x2BD];
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ s16 m2C2;
    /* 0x2C4 */ s16 m2C4;
    /* 0x2C6 */ u8 m2C6[0x2C8 - 0x2C6];
    /* 0x2C8 */ s16 m2C8;
    /* 0x2CA */ s16 m2CA;
    /* 0x2CC */ u8 m2CC[0x2D0 - 0x2CC];
    /* 0x2D0 */ cXyz m2D0;
    /* 0x2DC */ u8 m2DC[0x2F4 - 0x2DC];
    /* 0x2F4 */ cXyz m2F4;
    /* 0x300 */ LIGHT_INFLUENCE mLight;
    /* 0x320 */ cXyz m320;
    /* 0x32C */ dPa_followEcallBack mParticleCallBack;
    /* 0x340 */ dBgS_ObjAcch mAcch;
    /* 0x504 */ dBgS_AcchCir mAcchCir;
    /* 0x544 */ dCcD_Stts mStts;
    /* 0x580 */ dCcD_Sph mSph;
    /* 0x6AC */ dCcD_Cps mCps;
    /* 0x7E4 */ f32 m7E4;
    /* 0x7E8 */ Mtx mAlphaModelMtx[2];
    /* 0x848 */ u8 m848[0x8A8 - 0x848];
    /* 0x8A8 */ mDoExt_3DlineMat0_c* mpLineMat;
    /* 0x8AC */ ProcFunc_t mCurrentProc;
};

class daBoko_HIO_c {
public:
    // Size 1 in retail, size 0x14 in debug.
};

class daBoko_HIO_c0 {
public:
    static const s16 throw_timer;
    static const f32 throw_speed;
};

#endif /* D_A_BOKO_H */
