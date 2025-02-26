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
    float getJointXPos(int jntIdx) const { return -m35c[jntIdx] * 3572.0f * 0.001f; }
    float getJointYPos(int) const { return 0.0f; }
    float getJointZPos(int jntIdx) const { return m330[jntIdx] * 3572.0f * 0.001f; }
    void getScaleEnd() {}
    void getSmallScaleEnd() {}
    void setScaleOn() {}

    int jointCallBack(int);
    BOOL draw();
    BOOL execute();
    int tornado_delete();
    BOOL createHeap();
    s32 create();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29c */ mDoExt_bckAnm mBck1;
    /* 0x2ac */ mDoExt_btkAnm mBtk1;
    /* 0x2c0 */ mDoExt_brkAnm mBrk1;
    /* 0x2d8 */ J3DModel* mpUnderModel;
    /* 0x2dc */ mDoExt_bckAnm mBck2;
    /* 0x2ec */ mDoExt_btkAnm mBtk2;
    /* 0x300 */ mDoExt_brkAnm mBrk2;
    /* 0x318 */ short mCurAngle1;
    /* 0x31a */ short mCurAngle2;
    /* 0x31c */ short m31c;
    /* 0x31e */ short m31e;
    /* 0x320 */ float mBtk1Frame;
    /* 0x324 */ float mBtk2Frame;
    /* 0x328 */ float mBrk1Frame;
    /* 0x32c */ float m32c;
    /* 0x330 */ float m330[11];
    /* 0x35c */ float m35c[11];
    /* 0x388 */ float mCurJointScale[11];
    /* 0x3b4 */ cXyz m3b4;
    /* 0x3c0 */ dPa_followEcallBack mPtclCb;
};

#endif /* D_A_TORNADO_H */
