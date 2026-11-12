#ifndef D_A_ICELIFT_H
#define D_A_ICELIFT_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"

class J3DModel;
class dBgW;
struct dPath;

class daIlift_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    void lift_wave();
    void path_move();
    void lift_normal_move();
    void set_next_pnt();
    bool _draw();

    static const char* m_arcname[];
    static const int m_bmdidx[];
    static const int m_dzbidx[];
    static const u32 m_heapsize[];
    static const f32 m_down_param;
    static const f32 m_max_speed;

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mMtx;
    /* 0x2D0 */ dBgS_ObjAcch mAcch;
    /* 0x494 */ dBgS_AcchCir mAcchCir;
    /* 0x4D4 */ bool mbRide;
    /* 0x4D5 */ bool mbRideOld;
    /* 0x4D6 */ s16 mTiltAngle;
    /* 0x4D8 */ s16 mTargetTilt;
    /* 0x4DC */ Quaternion mTargetRotation;
    /* 0x4EC */ Quaternion mCurrentRotation;
    /* 0x4FC */ cXyz mRideOffset;
    /* 0x508 */ f32 m508;
    /* 0x50C */ int mFrameCount;
    /* 0x510 */ int mWaveTimer;
    /* 0x514 */ u8 m514[0x518 - 0x514];
    /* 0x518 */ u8 mType;
    /* 0x51C */ cXyz mNextPos;
    /* 0x528 */ cXyz mPrevPos;
    /* 0x534 */ dPath* mpPath;
    /* 0x538 */ f32 mTargetSpeed;
    /* 0x53C */ f32 mSpeed;
    /* 0x540 */ u16 mMoveTimer;
    /* 0x542 */ u8 mPathId;
    /* 0x543 */ s8 mPntIdx;
    /* 0x544 */ s8 mPntDir;
    /* 0x545 */ u8 mMoveState;
    /* 0x548 */ u8 m548[0x54C - 0x548];
    /* 0x54C */ f32 mRideDist;
    /* 0x550 */ u8 m550[0x554 - 0x550];
    /* 0x554 */ int mSwitchNo;
    /* 0x558 */ cXyz mPlayerOldPos;
};  // Size: 0x564

#endif /* D_A_ICELIFT_H */
