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
    BOOL _delete();
    void set_mtx();
    BOOL _execute();
    BOOL _draw();

    static const char M_arcname[8];

    /* 0x290 */ request_of_phase_process_class mphs;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ dBgW* field_x2A0;
    /* 0x2A4 */ Mtx field_x2A4;
    /* 0x2D4    u8 padding?  */
};
};  // namespace daObjGaship2

#endif /* D_A_OBJ_GASHIP2_H */
