#ifndef D_A_OBJ_YBOIL_H
#define D_A_OBJ_YBOIL_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class J3DMaterial;
class J3DModel;

class daObjYboil_c : public fopAc_ac_c {
public:
    enum Prm_e {
        PRM_SWSAVE_S = 8,
        PRM_SWSAVE_W = 8,
    };

    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    inline u32 prm_get_swSave() const;
    inline void set_sea_material(J3DMaterial*);

    BOOL CreateHeap();
    void pos_reset(int);
    void CreateInit();
    void set_mtx();

public:
    /* 0x0290 */ request_of_phase_process_class mPhs;
    /* 0x0298 */ J3DModel* mModel[50];
    /* 0x0360 */ mDoExt_bckAnm mBckAnm[50];
    /* 0x0680 */ mDoExt_btkAnm mBtkAnm[50];
    /* 0x0A68 */ mDoExt_brkAnm mBrkAnm[50];
    /* 0x0F18 */ s32 mMdlTimer[50];
    /* 0x0FE0 */ cXyz mMdlPos[50];
    /* 0x1238 */ cXyz mMdlScale[50];
    /* 0x1490 */ f32 mScaleMax;
    /* 0x1494 */ f32 mScaleMin;
};

#endif /* D_A_OBJ_YBOIL_H */
