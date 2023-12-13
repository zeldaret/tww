#ifndef D_A_BOKO_H
#define D_A_BOKO_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

struct ke_c_s {
    
};

class daBoko_c : public fopAc_ac_c {
public:
    static Vec m_top_offset[6];
    static Vec m_blur_root_offset[6];
    static Vec m_root_offset[6];
    static f32 m_cps_r[6];
    static s32 m_at_point[6];
    static u32 m_at_type[6];
    static f32 m_jump_blur_rate[6];
    static f32 m_blur_rate[6];
    static u8 m_se_type[6];

    void getAtPoint() {}
    void getAtType() {}
    void getBlurRate() {}
    void getCpsR() {}
    void getFlameTimer() {}
    void getJumpBlurRate() {}
    void getNowMode() {}
    void getSeType() {}
    void moveStateInit(f32 speedForward, f32 speedY, s16 angleY) {
        speed.y = speedY;
        speedF = speedForward;
        current.angle.y = angleY;
    }
    void onFloorFlg() {}
    void setMatrix(Mtx mtx) {
        if (mpModel) {
            mpModel->setBaseTRMtx(mtx);
        }
    }
    void setNowMode(int) {}
    void setRotAngleSpeed(s16 speed) { m2C2 = speed; }
    void setThrow(s16) {}

    void getTopPos(cXyz *);
    void getBlurRootPos(cXyz *);
    void keDraw();
    void keCalc1(ke_c_s*, int);
    void keCalc();
    BOOL draw();
    void setTopRootPos(int);
    void setBaseMatrix();
    void checkNoDraw();
    void setFlameEffect();
    void setRoomInfo();
    void setThrowReverse(short);
    void procWait_init();
    void procWait();
    void procMove_init();
    void procMove();
    void procThrow();
    void procCarry();
    BOOL execute();
    void bokoDelete();
    void createHeap();
    s32 create();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_brkAnm mBrkAnm;
    /* 0x2B4 */ u8 m2B4[0x2B8 - 0x2B4];
    /* 0x2B8 */ u8 mCurrentAction;
    /* 0x2B9 */ u8 m2B9[0x2BA - 0x2B9];
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD[0x2C0 - 0x2BD];
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ s16 m2C2;
    /* 0x2C4 */ s16 m2C4;
    /* 0x2C6 */ u8 m2C6[0x2C8 - 0x2C6];
    /* 0x2C8 */ s16 m2C8;
    /* 0x2CA */ u8 m2CA[0x2D0 - 0x2CA];
    /* 0x2D0 */ cXyz m2D0;
    /* 0x2DC */ u8 m2DC[0x2F4 - 0x2DC];
    /* 0x2F4 */ cXyz m2F4;
    /* 0x300 */ LIGHT_INFLUENCE mLight;
    /* 0x320 */ cXyz m320;
    /* 0x32C */ dPa_followEcallBack mParticleCallBack;
    /* 0x340 */ dBgS_Acch mAcch;
    /* 0x504 */ dBgS_AcchCir mAcchCir;
    /* 0x544 */ dCcD_Stts mStts;
    /* 0x580 */ dCcD_Sph mSph;
    /* 0x6AC */ dCcD_Cps mCps;
    /* 0x7E4 */ f32 m7E4;
    /* 0x7E8 */ Mtx mAlphaModelMtx[2];
    /* 0x848 */ u8 m848[0x8A8 - 0x848];
    /* 0x8A8 */ mDoExt_3DlineMat0_c* mpLineMat;
    /* 0x8AC */ int (daBoko_c::*mCurrentProc)();
};

#endif /* D_A_BOKO_H */
