#ifndef C_M3D_G_AAB_H
#define C_M3D_G_AAB_H

#include "SSystem/SComponent/c_m3d.h"
#include "SSystem/SComponent/c_m3d_g_lin.h"
#include "SSystem/SComponent/c_xyz.h"
#include "global.h"

// Axis aligned bounding box
class cM3dGAab {
private:
    /* 0x00 */ cXyz mMin;
    /* 0x0C */ cXyz mMax;
    /* 0x18 */ /* vtable */

public:
    virtual ~cM3dGAab() {}
    void SetMinMax(const cXyz&);
    void SetMinMax(const cM3dGAab& aab) {
        SetMinMax(aab.mMin);
        SetMinMax(aab.mMax);
    }
    void Set(const cXyz* min, const cXyz* max) {
        mMin = *min;
        mMax = *max;
    }
    void SetMin(const cXyz&);
    void SetMax(const cXyz&);
    const cXyz* GetMaxP() const { return &mMax; }
    const cXyz* GetMinP() const { return &mMin; }
    cXyz* GetMaxP() { return &mMax; }
    cXyz* GetMinP() { return &mMin; }
    const f32 GetMaxX() const { return mMax.x; }
    const f32 GetMaxY() const { return mMax.y; }
    const f32 GetMaxZ() const { return mMax.z; }
    const f32 GetMinX() const { return mMin.x; }
    const f32 GetMinY() const { return mMin.y; }
    const f32 GetMinZ() const { return mMin.z; }
    bool Cross(const cM3dGAab *aab) {
        return cM3d_Cross_AabAab(this, aab);
    }
    bool Cross(const cM3dGCyl *cyl) {
        return cM3d_Cross_AabCyl(this, cyl);
    }
    bool Cross(const cM3dGSph *sph) {
        return cM3d_Cross_AabSph(this, sph);
    }
    bool Cross(const cM3dGLin *lin) {
        return cM3d_Cross_MinMaxBoxLine(GetMinP(), GetMaxP(), lin->GetStartP(), lin->GetEndP());
    }
    void CalcCenter(cXyz* pOut) const {
        VECAdd(&mMin, &mMax, pOut);
        VECScale(pOut, pOut, 0.5f);
    }
    void ClearForMinMax() {
        mMin.z = G_CM3D_F_INF;
        mMin.y = G_CM3D_F_INF;
        mMin.x = G_CM3D_F_INF;
        mMax.z = -G_CM3D_F_INF;
        mMax.y = -G_CM3D_F_INF;
        mMax.x = -G_CM3D_F_INF;
    }
    void ClearForMinMaxY() {
        mMin.y = G_CM3D_F_INF;
        mMax.y = -G_CM3D_F_INF;
    }
    void SetMinMaxY(f32 y) {
        if (mMin.y > y) {
            mMin.y = y;
        }
        if (mMax.y < y) {
            mMax.y = y;
        }
    }
    void SetMinY(f32 y) {
        if (mMin.y > y) {
            mMin.y = y;
        }
    }
    void SetMaxY(f32 y) {
        if (mMax.y < y) {
            mMax.y = y;
        }
    }
    void PlusR(f32 r) {
        mMin.x -= r;
        mMin.y -= r;
        mMin.z -= r;
        mMax.x += r;
        mMax.y += r;
        mMax.z += r;
    }
    bool CrossY(const cXyz* v) const {
        if (mMin.x > v->x || mMax.x < v->x || mMin.z > v->z || mMax.z < v->z) {
            return false;
        } else {
            return true;
        }
    }
    bool UnderPlaneYUnder(f32 y) const {
        return mMin.y < y;
    }
    bool TopPlaneYUnder(f32 y) const {
        return mMax.y < y;
    }

    void Cross(const cM3dGAab*) const {}
    void Cross(const cM3dGCyl*) const {}
    void Cross(const cM3dGLin*) const {}
    void Cross(const cM3dGSph*) const {}
};  // Size = 0x1C

STATIC_ASSERT(0x1C == sizeof(cM3dGAab));

#endif /* C_M3D_G_AAB_H */
