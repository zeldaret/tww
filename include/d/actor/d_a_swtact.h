#ifndef D_A_SWTACT_H
#define D_A_SWTACT_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor_mng.h"

class daSwTact_c : public fopAc_ac_c {
public:
    f32 getR() { return mRadius * mScale.x; }

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();
    s32 getAnswer();
    s32 _create();
    bool _execute();
    bool _draw();

    static const char * m_arcname;
    static const f32 mDefaultR;
    static const f32 mDefaultRwM;
    static const u32 m_heapsize;

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * model;
    /* 0x29C */ f32 mRadius;
    /* 0x2A0 */ u32 mSwitchNo;
    /* 0x2A4 */ u8 mAnswer;
    /* 0x2A5 */ bool mTrigger;
    /* 0x2A6 */ u8 mPlayerStatus;
};

namespace daSwTact_prm {
    inline u32 getSwitchNo(daSwTact_c * i_this)  { return (fopAcM_GetParam(i_this) >> 0) & 0xFF; }
    inline u32 getAnswer(daSwTact_c * i_this)  { return (fopAcM_GetParam(i_this) >> 8) & 0xFF; }
    inline u32 getModel(daSwTact_c * i_this) { return (fopAcM_GetParam(i_this) >> 16) & 0x0F; }
}

#endif /* D_A_SWTACT_H */
