#ifndef D_A_OBJ_VFAN_H
#define D_A_OBJ_VFAN_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

#include "SSystem/SComponent/c_phase.h"

namespace daObjVfan {
class Act_c : public dBgS_MoveBgActor {
public:
    enum Prm_e {
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0,
    };

    static Mtx M_tmp_mtx;
    static const char M_arcname[];

    s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

    virtual BOOL CreateHeap();
    virtual BOOL Create();
    cPhs_State Mthd_Create();
    virtual BOOL Delete();
    BOOL Mthd_Delete();
    void set_mtx();
    void init_mtx();
    void ParticleSet();
    virtual BOOL Execute(Mtx**);
    virtual BOOL Draw();

public:
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ J3DModel* mpModel;
    /* 0x2D4 */ dCcD_Stts mStts;
    /* 0x310 */ dCcD_Cyl mCyl;
    /* 0x440 */ int mState;
    /* 0x444 */ bool mIsAlive;
    /* 0x448 */ int mBreakTimer;
};

};  // namespace daObjVfan

#endif /* D_A_OBJ_VFAN_H */
