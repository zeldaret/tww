#ifndef D_A_SWPROPELLER_H
#define D_A_SWPROPELLER_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"

class daSwProp_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    bool _draw();

    static const char* m_arcname[2];
    static const s16 m_bdlidx[2];
    static const u32 m_heapsize[2];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ u8 m408[0x43C - 0x408];
    /* 0x43C */ dBgS_ObjAcch mAcch;
    /* 0x600 */ dBgS_AcchCir mAcchCir;
    /* 0x640 */ s16 mRotY;
    /* 0x642 */ s16 mRotSpeed;
    /* 0x644 */ s16 mRotTargetSpeed;
    /* 0x646 */ u8 m646[0x648 - 0x646];
    /* 0x648 */ u32 m648;
    /* 0x64C */ u8 field_0x64C;
    /* 0x64D */ u8 mType;
    /* 0x64E */ u8 field_0x64E;
    /* 0x64F */ u8 m64F[0x800 - 0x64F];
};

#endif /* D_A_SWPROPELLER_H */
