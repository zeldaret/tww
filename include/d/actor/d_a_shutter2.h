#ifndef D_A_SHUTTER2_H
#define D_A_SHUTTER2_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor_mng.h"

class daShutter2_c : public dBgS_MoveBgActor {
public:
    BOOL Delete();
    int CreateHeap();
    int Create();
    s32 _create();
    void set_mtx();
    int Execute(Mtx**);
    void shutter_move();
    void demo();
    BOOL Draw();

    /* 0x00 */ static const float m_max_speed[1];
    /* 0x04 */ static const float m_min_speed[1];
    /* 0x08 */ static const float m_move_len[1];
    /* 0x0C */ static const float m_width[1];
    /* 0x10 */ static const float m_height[1];
    /* 0x14 */ static const s16 m_bdlidx[1];
    /* 0x16 */ static const s16 m_dzbidx[1];
    /* 0x18 */ static const s32 m_heapsize[1];
    /* 0x1C */ static const Vec m_cull_min[1];
    /* 0x28 */ static const Vec m_cull_max[1];

    static char* m_arcname[1];
    static char* m_open_ev_name[1];
    static char* m_close_ev_name[1];
    static char* m_staff_name[1];

public:
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ J3DModel* mpModel;
    /* 0x2D4 */ Mtx mMtx;
    /* 0x304 */ s32 mActionIndex;
    /* 0x308 */ s32 mSwitchNo;
    /* 0x30C */ s32 m30C;
    /* 0x310 */ s32 mStaffId;
    /* 0x314 */ s16 mOpenEventIdx;
    /* 0x316 */ s16 mCloseEventIdx;
    /* 0x318 */ u8 m318;
    /* 0x319 */ u8 mType;
    /* 0x31A */ u8 mbIsSwitch;
    /* 0x31B */ u8 mbIsNearEnemy;
};

namespace daShutter2_prm {
    inline u8 getSwitchNo(daShutter2_c* i_this) { return (fopAcM_GetParam(i_this) >> 0) & 0xFF; }
}

#endif /* D_A_SHUTTER2_H */
