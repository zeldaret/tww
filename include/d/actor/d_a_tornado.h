#ifndef D_A_TORNADO_H
#define D_A_TORNADO_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_particle.h"

class daTornado_HIO_c0 {
    public:
        static const float move_dis;
        static const float start_dis;
};

class daTornado_c : public fopAc_ac_c {
public:
    f32 getJointXPos(int jno) const {
        if (mpModel)
            return mpModel->getAnmMtx(jno)[0][3];
        else
            return current.pos.x;
    }
    f32 getJointYPos(int jno) const {
        if (mpModel)
            return mpModel->getAnmMtx(jno)[1][3];
        else
            return current.pos.y;
    }
    f32 getJointZPos(int jno) const {
        if (mpModel)
            return mpModel->getAnmMtx(jno)[2][3];
        else
            return current.pos.z;
    }
    f32 getScaleEnd() { return mJointScale[10]; }
    f32 getSmallScaleEnd() { return mJointScale[10]; }
    void setScaleOn() { m31c = 1; }

    BOOL jointCallBack(int);
    BOOL draw();
    BOOL execute();
    BOOL tornado_delete();
    BOOL createHeap();
    cPhs_State create();

private:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29c */ mDoExt_bckAnm mBck;
    /* 0x2ac */ mDoExt_btkAnm mBtk;
    /* 0x2c0 */ mDoExt_brkAnm mBrk;
    /* 0x2d8 */ J3DModel* mpModelUnder;
    /* 0x2dc */ mDoExt_bckAnm mBckUnder;
    /* 0x2ec */ mDoExt_btkAnm mBtkUnder;
    /* 0x300 */ mDoExt_brkAnm mBrkUnder;
    /* 0x318 */ s16 mAngle1;
    /* 0x31a */ s16 mAngle2;
    /* 0x31c */ s16 m31c;
    /* 0x31e */ s16 mPtclTimer;
    /* 0x320 */ f32 mBtkFrame;
    /* 0x324 */ f32 mBtkUnderFrame;
    /* 0x328 */ f32 mBrkFrame;
    /* 0x32c */ f32 m32c;
    /* 0x330 */ f32 mJointX[11];
    /* 0x35c */ f32 mJointZ[11];
    /* 0x388 */ f32 mJointScale[11];
    /* 0x3b4 */ cXyz mCenter;
    /* 0x3c0 */ dPa_followEcallBack mPtclCb;
};

#endif /* D_A_TORNADO_H */
