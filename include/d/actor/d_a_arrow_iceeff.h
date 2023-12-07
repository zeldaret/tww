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
    /* 0x290 */ u32 field_0x290;
    /* 0x294 */ u32 field_0x294;
    /* 0x298 */ J3DModel* field_0x298[30];
    /* 0x310 */ J3DModel* mpModel;
    /* 0x314 */ Mtx field_0x314[30];
    /* 0x8B4 */ cXyz field_0x8B4[30];
    /* 0xA1C */ J3DAnmTextureSRTKey* field_0xA1C;
    /* 0xA20 */ mDoExt_bckAnm mBck;
    /* 0xA30 */ s32 field_0xA30;
    /* 0xA34 */ f32 field_0xA34;
    /* 0xA38 */ s32 field_0xA38;
    /* 0xA3C */ u8 field_0xA3C;
}; // Size: 0xA40

#endif /* D_A_ARROW_ICEEFF_H */
