#ifndef D_A_ARROW_ICEEFF_H
#define D_A_ARROW_ICEEFF_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daArrow_Iceeff_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    u32 field_0x290;
    u32 field_0x294;
    J3DModel* field_0x298[30];
    J3DModel* mpModel;
    Mtx field_0x314[30];
    cXyz field_0x8B4[30];
    J3DAnmTextureSRTKey* field_0xA1C;
    mDoExt_bckAnm mBck;
    s32 field_0xA30;
    f32 field_0xA34;
    s32 field_0xA38;
    u8 field_0xA3C;
}; // Size: 0xA40

#endif /* D_A_ARROW_ICEEFF_H */
