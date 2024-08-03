#ifndef D_A_OBJ_LPALM_H
#define D_A_OBJ_LPALM_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class daObjLpalm_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void set_mtx() {}

    BOOL CreateHeap();
    void CreateInit();

    struct Attr_c {
        u8 flag0;
        u8 flag1;
    };
    static const Attr_c M_attr;
    inline const Attr_c& attr() const { return M_attr; }
    static const char M_arcname[];

public:
    /* 0x290 */ u8 m290[0x294 - 0x290];
    /* 0x294 */ Quaternion mBaseQuat;
    /* 0x2A4 */ Quaternion mBaseQuatTarget;
    /* 0x2B4 */ Quaternion mAnmMtxQuat[2];
    /* 0x2D4 */ s16 mAnimDir[2];
    /* 0x2D8 */ s16 mAnimWave[2];
    /* 0x2DC */ request_of_phase_process_class mPhs;
    /* 0x2E4 */ J3DModel* mModel;
    /* 0x2E8 */ dBgW* mpBgW;
};

#endif /* D_A_OBJ_LPALM_H */
