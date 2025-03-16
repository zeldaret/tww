#ifndef C_M3D_G_LIN_H
#define C_M3D_G_LIN_H

#include "SSystem/SComponent/c_xyz.h"
#include "global.h"

// Line
class cM3dGLin {
private:
    /* 0x00 */ cXyz mStart;
    /* 0x0C */ cXyz mEnd;
    /* 0x18 vtable */

public:
    cM3dGLin() {}
    cM3dGLin(const cXyz& start, const cXyz& end) : mStart(start), mEnd(end) {}
    virtual ~cM3dGLin() {}
    void SetStartEnd(const cXyz& start, const cXyz& end) {
        mStart = start;
        mEnd = end;
    }
    void SetStartEnd(const Vec& start, const Vec& end) {
        mStart = start;
        mEnd = end;
    }
    void set(const Vec& start, const Vec& end) {
        mStart = start;
        mEnd = end;
    }
    void CalcPos(Vec* out, f32 scale) const {
        Vec tmp;
        VECSubtract(&mEnd, &mStart, &tmp);
        VECScale(&tmp, &tmp, scale);
        VECAdd(&tmp, &mStart, out);
    }
    void CalcVec(Vec* pOut) const { VECSubtract(&this->mEnd, &this->mStart, pOut); }
    void SetEnd(const cXyz& pos) { mEnd = pos; }
    const cXyz* GetStartP() const { return &mStart; }
    cXyz* GetStartP() { return &mStart; }
    const cXyz& GetStart() const { return mStart; }
    cXyz& GetStart() { return mStart; }
    const cXyz* GetEndP() const { return &mEnd; }
    cXyz* GetEndP() { return &mEnd; }
    const cXyz& GetEnd() const { return mEnd; }
    cXyz& GetEnd() { return mEnd; }
    f32 GetLen() const { return VECDistance(&mStart, &mEnd); }
};  // Size = 0x1C

STATIC_ASSERT(0x1C == sizeof(cM3dGLin));

#endif /* C_M3D_G_LIN_H */
