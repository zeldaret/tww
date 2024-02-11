#ifndef D_BG_W_SV_H
#define D_BG_W_SV_H

#include "d/d_bg_w.h"

class dBgWSv : public dBgW {
public:
    virtual void MatrixCrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*) {}
    bool ChkNoCrrPos() { return mSvFlag & 1; }
    void SetFlag(u32 flag) { mSvFlag = flag; }
    Vec* GetBackVtx() { return mBackVtx; }
    void SetBackVtx(Vec* vtx) { mBackVtx = vtx; }
    
    bool Set(cBgD_t*, u32);
    void CopyBackVtx();
    bool CrrPosWork(cXyz*, int, int, int);
    virtual void CrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    bool TransPosWork(cXyz*, int, int, int);
    virtual void TransPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);

private:
    /* 0xBC */ u32 mSvFlag;
    /* 0xC0 */ Vec* mBackVtx;
};  // Size: 0xC4

#endif /* D_BG_W_SV_H */
