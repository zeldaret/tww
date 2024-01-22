#ifndef D_A_OBJ_GASHIP2_H
#define D_A_OBJ_GASHIP2_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"

namespace daObjGaship2 {
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

    static const char M_arcname[8];

    /* 0x290 */ request_of_phase_process_class mphs;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ dBgW* mpBgW;
    /* 0x2A4 */ Mtx mMtx;
};
};  // namespace daObjGaship2

#endif /* D_A_OBJ_GASHIP2_H */
