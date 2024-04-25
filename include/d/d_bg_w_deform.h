#ifndef D_BG_W_DEFORM_H
#define D_BG_W_DEFORM_H

#include "d/d_bg_w_sv.h"
#include "JSystem/J3DGraphAnimator/J3DSkinDeform.h"

class dBgWDeform : public dBgWSv, public J3DSkinDeform {
public:
    void MoveAfterAnmCalc(J3DModel*) {}
    void SetVtx(Vec*) {}

    bool Set(cBgD_t*, J3DModel*, u32);

public:
    /* 0x00 */ /* dBgWSv */
    /* 0xC4 */ /* J3DSkinDeform */
};  // Size: 0xDC

#endif /* D_BG_W_DEFORM_H */
