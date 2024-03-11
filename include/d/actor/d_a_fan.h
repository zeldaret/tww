#ifndef D_A_FAN_H
#define D_A_FAN_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

class daFan_c : public dBgS_MoveBgActor {
public:
    s32 _create();
    BOOL Delete();
    int CreateHeap();
    int Create();
    void set_mtx();
    void set_wind_length(f32);
    void set_cps(f32);
    int Execute(Mtx**);
    BOOL Draw();

public:
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ request_of_phase_process_class mWindPhs;
    /* 0x2D8 */ J3DModel* mModel;
    /* 0x2DC */ dCcD_Stts mStts;
    /* 0x318 */ dCcD_Cps mCps;
    /* 0x450 */ u32 field_0x450[13];
    /* 0x484 */ mDoExt_btkAnm mBtkAnm;
    /* 0x498 */ u32 mSwitchNo;
    /* 0x49C */ u8 mType;
    /* 0x4A0 */ cM3dGCpsS mCpsS;
    /* 0x4BC */ s16 mFanAngle;
    /* 0x4BE */ s16 mFanSpeed;
    /* 0x4C0 */ u32 field_0x4c0;
    /* 0x4C4 */ J3DModel* mWindModel;
    /* 0x4C8 */ mDoExt_btkAnm mWindBtkAnm0;
    /* 0x4C8 */ mDoExt_btkAnm mWindBtkAnm1;
    /* 0x4C8 */ mDoExt_bckAnm mWindBckAnm;
    /* 0x500 */ cXyz mWindScale;
    /* 0x50C */ uint mWindSePId;

    static const char* m_arcname[3];
    static const char m_arcname2[8];
    static const s16 m_bdlidx[3];
    static const s16 m_dzbidx[3];
    static const f32 m_wind_length[3];
    static const f32 m_wind_r[3];
    static const Vec m_wind_model_scale[3];
    static const s16 m_fan_speed[3];
    static const u32 m_heapsize[3];
    static const Vec m_cull_min[3];
    static const Vec m_cull_max[3];
};

namespace daFan_prm {
    inline u8 getType(daFan_c* ac) { return (fopAcM_GetParam(ac) >> 8) & 0x03; }
    inline u8 getSwitchNo(daFan_c* ac) { return (fopAcM_GetParam(ac) >> 0) & 0xFF; }
};

#endif /* D_A_FAN_H */
