#ifndef D_BG_W_DEFORM_H
#define D_BG_W_DEFORM_H

#include "d/d_bg_w_sv.h"
#include "JSystem/J3DGraphAnimator/J3DSkinDeform.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"

class dBgWDeform : public dBgWSv, public J3DSkinDeform {
public:
    virtual ~dBgWDeform() {}

    void MoveAfterAnmCalc(J3DModel* model) {
        cXyz* pPos = (cXyz*)model->getCurrentVtxPos();
        SetVtx(pPos);
        Move();
    }
    
    void SetVtx(Vec* pPos) {
        if (GetVtxTbl() == NULL) {
            SetVtxTbl(pPos);
            CopyBackVtx();
        } else {
            SetVtxTbl(pPos);
        }
    }

    bool Set(cBgD_t*, J3DModel*, u32);

public:
    /* 0x00 */ /* dBgWSv */
    /* 0xC4 */ /* J3DSkinDeform */
};  // Size: 0xDC

#endif /* D_BG_W_DEFORM_H */
