#ifndef D_A_ICELIFT_H
#define D_A_ICELIFT_H

#include "d/d_bg_s_acch.h"
#include "d/d_path.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

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

    static const char* m_arcname[2];
    static const int m_bmdidx[];
    static const int m_dzbidx[];
    static const int m_heapsize[];
    static const float m_down_param[];
    static const float m_max_speed[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mMtx;
    /* 0x2D0 */ dBgS_ObjAcch mObjAcch;
    /* 0x494 */ dBgS_AcchCir mAcchCir;
    /* 0x4D4 */ u8 field_0x4D4;
    /* 0x4D5 */ u8 field_0x4D5;
    /* 0x4D6 */ s16 field_0x4D6;
    /* 0x4D8 */ s16 field_0x4D8;
    /* 0x4DA */ u8 field_0x4DA[0x4DC - 0x4DA];
    /* 0x4DC */ Quaternion mQuat1;
    /* 0x4EC */ Quaternion mQuat2;
    /* 0x4FC */ cXyz field_0x4FC;
    /* 0x508 */ f32 field_0x508;
    /* 0x50C */ u32 field_0x50C;
    /* 0x510 */ s32 field_0x510;
    /* 0x514 */ u8 field_0x514[0x518 - 0x514];
    /* 0x518 */ u8 mType;
    /* 0x51C */ cXyz mTargetPos;
    /* 0x528 */ cXyz field_0x528;
    /* 0x534 */ dPath* mpPath;
    /* 0x538 */ f32 field_0x538;
    /* 0x53C */ f32 field_0x53C;
    /* 0x540 */ u16 field_0x540;
    /* 0x542 */ u8 mPathId;
    /* 0x543 */ s8 mCurPathPoint;
    /* 0x544 */ s8 mPathPointDir;
    /* 0x545 */ u8 field_0x545;
    /* 0x546 */ u8 field_0x546[0x54C - 0x546];
    /* 0x54C */ f32 field_0x54C;
    /* 0x550 */ u32 field_0x550;
    /* 0x554 */ s32 field_0x554;
    /* 0x558 */ cXyz field_0x558;
};  // Size: 0x564

namespace daIlift_prm {
    
    inline u8 getSwNo(daIlift_c* ac)   { return (fopAcM_GetParam(ac) >> 0xc) & 0xff;}
    inline u8 getPathId(daIlift_c* ac) { return ac->mPathId; }
    inline u8 getType(daIlift_c* ac)   { return (fopAcM_GetParam(ac)) & 0x0f;}
}

#endif /* D_A_ICELIFT_H */
