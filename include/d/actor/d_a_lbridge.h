#ifndef D_A_LBRIDGE_H
#define D_A_LBRIDGE_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_particle.h"
#include "d/d_bg_w.h"

class daLbridge_c : public fopAc_ac_c {
public:
    inline BOOL _delete();

    BOOL CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void setMoveBGMtx();
    bool _execute();
    void sw_check();
    void demo();
    void appear_bridge();
    void disappear_bridge();
    void set_on_se();
    void set_off_se();
    bool _draw();

    static const char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mMtx;
    /* 0x2D0 */ mDoExt_btkAnm mBtkAnm;
    /* 0x2E4 */ mDoExt_bpkAnm mBpkAnm;
    /* 0x2F8 */ mDoExt_brkAnm mBrkAnm;
    /* 0x310 */ JPABaseEmitter* mpEmitter;
    /* 0x314 */ s32 mSwitchNo;
    /* 0x318 */ s16 mAppearEventIdx;
    /* 0x31A */ s16 mDisappearEventIdx;
    /* 0x31C */ s16 unk31C;
    /* 0x31E */ u8 mTimer;
    /* 0x31F */ u8 mIsSw;
};

namespace daLbridge_prm {
inline u8 getSwitchNo(daLbridge_c* ac) {
    return (fopAcM_GetParam(ac) >> 0) & 0xFF;
}
};  // namespace daLbridge_prm

#endif /* D_A_LBRIDGE_H */
