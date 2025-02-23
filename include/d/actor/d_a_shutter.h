#ifndef D_A_SHUTTER_H
#define D_A_SHUTTER_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class dBgW;

class daShutter_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    s32 Create();
    s32 _create();
    void set_mtx();
    bool _execute();
    void shutter_move();
    void demo();
    bool _draw();

    /* 0x00 */ static const float m_max_speed[2];
    /* 0x08 */ static const float m_min_speed[2];
    /* 0x10 */ static const float m_move_len[2];
    /* 0x18 */ static const float m_width[2];
    /* 0x20 */ static const float m_height[2];
    /* 0x28 */ static const s16 m_bdlidx[2];
    /* 0x2C */ static const s16 m_dzbidx[2];
    /* 0x30 */ static const s32 m_heapsize[2];
    /* 0x38 */ static const Vec m_cull_min[2];
    /* 0x50 */ static const Vec m_cull_max[2];

    static char* m_arcname[2];
    static char* m_open_ev_name[2];
    static char* m_close_ev_name[2];
    static char* m_staff_name[2];
    
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel[2];
    /* 0x2A0 */ dBgW* mdBgW[2];
    /* 0x2A8 */ Mtx mMtx[2];
    /* 0x308 */ cXyz mcXyz[2];
    /* 0x320 */ s32 field_0x320;
    /* 0x324 */ s32 mSwitchNo;
    /* 0x328 */ s32 field_0x328;
    /* 0x32C */ s32 mStaffId;
    /* 0x330 */ s16 mOpenEventIdx;
    /* 0x332 */ s16 mCloseEventIdx;
    /* 0x334 */ u8 field_0x334;
    /* 0x335 */ u8 mType;
    /* 0x336 */ u8 mbIsSwitch;
    /* 0x337 */ s8 mFrameTimer;
    /* 0x338 */ u8 mTimer;
    /* 0x339 */ u8 field_0x339;
    /* 0x33A */ u8 field_0x33A;
    /* 0x33B */ u8 field_0x33B;
};

namespace daShutter_prm {
    inline u8 getSwitchNo(daShutter_c* item) { return (fopAcM_GetParam(item) >> 0) & 0xFF; }
    inline u8 getType(daShutter_c* item) { return (fopAcM_GetParam(item) >> 8) & 0x0F; }
}

#endif /* D_A_SHUTTER_H */
