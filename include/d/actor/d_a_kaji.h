#ifndef D_A_KAJI_H
#define D_A_KAJI_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

class mDoExt_McaMorf;

class daKaji_c : public fopAc_ac_c {
public:
    static const char M_arcname[];

    void set_mtx() {
        mpMorf->getModel()->setBaseScale(mScale);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        MTXCopy(mDoMtx_stack_c::get(), mMtx);
    }
    void setAnm(int, f32) {}

    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _execute();
    inline bool _draw();

    BOOL CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u8 pad[0x29C - 0x298];
    /* 0x29C */ mDoExt_McaMorf* mpMorf;
    /* 0x2A0 */ Mtx mMtx;
};

#endif /* D_A_KAJI_H */
