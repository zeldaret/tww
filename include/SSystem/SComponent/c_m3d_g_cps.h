#ifndef C_M3D_G_CPS_H
#define C_M3D_G_CPS_H

#include "SSystem/SComponent/c_m3d.h"
#include "SSystem/SComponent/c_m3d_g_lin.h"
#include "SSystem/SComponent/c_m3d_g_tri.h"
#include "global.h"

struct cM3dGCpsS {
    /* 0x00 */ Vec mStart;
    /* 0x0C */ Vec mEnd;
    /* 0x18 */ f32 mRadius;
};  // Size: 0x1C

class cM3dGCps : public cM3dGLin {
public:
    /* 0x1C */ f32 mRadius;

    cM3dGCps() {}
    virtual ~cM3dGCps() {}
    void Set(const cXyz& start, const cXyz& end, f32 radius) {
        SetStartEnd(start, end);
        SetR(radius);
    }
    void Set(const cM3dGCpsS& src) {
        SetStartEnd(src.mStart, src.mEnd);
        SetR(src.mRadius);
    }
    void SetCps(const cM3dGCps& cps) {
        Set(cps.GetStart(), cps.GetEnd(), cps.GetR());
    }
    bool Cross(cM3dGCps const* cps, cXyz* xyz) const { return cM3d_Cross_CpsCps(*this, *cps, xyz); }
    bool Cross(cM3dGCyl const* cyl, cXyz* xyz) const { return cM3d_Cross_CpsCyl(*this, *cyl, xyz); }
    bool Cross(cM3dGSph const* sph, cXyz* xyz) const { return cM3d_Cross_CpsSph(*this, *sph, xyz); }
    bool Cross(cM3dGTri const& tri, cXyz* xyz) const { return cM3d_Cross_CpsTri(*this, tri, xyz); }
    f32 GetR() const { return mRadius; }
    void SetR(f32 r) { mRadius = r; }

    bool NearPos(const cXyz& pos, cXyz* outPos) {
        return cM3d_NearPos_Cps(*this, pos, outPos);
    }
};  // Size = 0x20

STATIC_ASSERT(0x20 == sizeof(cM3dGCps));

#endif /* C_M3D_G_CPS_H */