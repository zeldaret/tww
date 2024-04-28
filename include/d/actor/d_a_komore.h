#ifndef D_A_KOMORE_H
#define D_A_KOMORE_H

#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

namespace daKomore {
class Act_c : public fopAc_ac_c {
public:
    virtual ~Act_c() {}
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    s32 _create();
    bool _delete();
    void set_mtx();
    bool _execute();
    bool _draw();
    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2A0 */ Mtx mMtx;
};
};  // namespace daKomore

#endif /* D_A_KOMORE_H */
