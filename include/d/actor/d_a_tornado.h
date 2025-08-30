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
    float getJointXPos(int jno) const {
        if (mpModel)
            return mpModel->getAnmMtx(jno)[0][3];
        else
            return current.pos.x;
    }
    float getJointYPos(int jno) const {
        if (mpModel)
            return mpModel->getAnmMtx(jno)[1][3];
        else
            return current.pos.y;
    }
    float getJointZPos(int jno) const {
        if (mpModel)
            return mpModel->getAnmMtx(jno)[2][3];
        else
            return current.pos.z;
    }
    void getScaleEnd() {}
    void getSmallScaleEnd() {}
    void setScaleOn() {}

    BOOL jointCallBack(int);
    BOOL draw();
    BOOL execute();
    BOOL tornado_delete();
    BOOL createHeap();
    cPhs_State create();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29c */ mDoExt_bckAnm mBck;
    /* 0x2ac */ mDoExt_btkAnm mBtk;
    /* 0x2c0 */ mDoExt_brkAnm mBrk;
    /* 0x2d8 */ J3DModel* mpModelUnder;
    /* 0x2dc */ mDoExt_bckAnm mBckUnder;
    /* 0x2ec */ mDoExt_btkAnm mBtkUnder;
    /* 0x300 */ mDoExt_brkAnm mBrkUnder;
    /* 0x318 */ short mAngle1;
    /* 0x31a */ short mAngle2;
    /* 0x31c */ short m31c;
    /* 0x31e */ short mPtclTimer;
    /* 0x320 */ float mBtkFrame;
    /* 0x324 */ float mBtkUnderFrame;
    /* 0x328 */ float mBrkFrame;
    /* 0x32c */ float m32c;
    /* 0x330 */ float mJointX[11];
    /* 0x35c */ float mJointZ[11];
    /* 0x388 */ float mJointScale[11];
    /* 0x3b4 */ cXyz mCenter;
    /* 0x3c0 */ dPa_followEcallBack mPtclCb;
};

#endif /* D_A_TORNADO_H */
