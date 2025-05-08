#ifndef D_A_OBJ_XFUTA_H
#define D_A_OBJ_XFUTA_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"

namespace daObjXfuta {
class Act_c : public fopAc_ac_c {
public:
    virtual ~Act_c() {}
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    cPhs_State _create();
    bool _delete();
    void set_mtx();
    bool _execute();
    bool _draw();
    BOOL Mthd_Delete();
    cPhs_State Mthd_Create();
    BOOL Mthd_Execute();
    BOOL Mthd_Draw();
    BOOL Mthd_IsDelete();
    static const char M_arcname[];

public:
    /* 0x290 */  // void* vtbl;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ Mtx mMtx;
};
};     // namespace daObjXfuta
#endif /* D_A_OBJ_XFUTA_H */
