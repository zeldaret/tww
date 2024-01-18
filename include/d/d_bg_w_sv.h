#ifndef D_BG_W_SV_H
#define D_BG_W_SV_H

#include "d/d_bg_w.h"

class dBgWSv : public dBgW {
public:
    void ChkNoCrrPos() {}
    void GetBackVtx() {}
    virtual void MatrixCrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*) {}
    void SetBackVtx(Vec*) {}
    void SetFlag(unsigned long) {}
    
    void Set(cBgD_t*, unsigned long);
    void CopyBackVtx();
    void CrrPosWork(cXyz*, int, int, int);
    virtual void CrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    void TransPosWork(cXyz*, int, int, int);
    virtual void TransPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
};

#endif /* D_BG_W_SV_H */
