#ifndef C_M3D_G_LIN_H
#define C_M3D_G_LIN_H

#include "SSystem/SComponent/c_xyz.h"
#include "global.h"

// Line
class cM3dGLin {
    // private:
public:
    /* 0x00 */ cXyz mStart;
    /* 0x0C */ cXyz mEnd;
    /* 0x18 vtable */

    cM3dGLin() {}
    cM3dGLin(const cXyz&, const cXyz&);
    virtual ~cM3dGLin() {}
    void SetStartEnd(const cXyz& start, const cXyz& end) {
        mStart = start;
        mEnd = end;
    }
    void SetStartEnd(const Vec& start, const Vec& end) {
        mStart = start;
        mEnd = end;
    }
    void CalcPos(Vec*, f32) const { /* TODO */ }
    void CalcVec(Vec* pOut) const { VECSubtract(&this->mEnd, &this->mStart, pOut); }
    void SetEnd(const cXyz&) { /* TODO */ }
    const cXyz& GetStartP() const { return mStart; }
    cXyz& GetStartP() { return mStart; }
    const cXyz& GetStart() const { return mStart; }
    cXyz& GetStart() { return mStart; }
    const cXyz& GetEndP() const { return mEnd; }
    cXyz& GetEndP() { return mEnd; }
    const cXyz& GetEnd() const { return mEnd; }
    cXyz& GetEnd() { return mEnd; }
    void GetLen() const { /* TODO */ }
    void set(const Vec&, const Vec&) { /* TODO */ }
};  // Size = 0x1C

STATIC_ASSERT(0x1C == sizeof(cM3dGLin));

#endif /* C_M3D_G_LIN_H */