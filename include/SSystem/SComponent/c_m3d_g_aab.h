#ifndef C_M3D_G_AAB_H
#define C_M3D_G_AAB_H

#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_m3d.h"
#include "global.h"

// Axis aligned bounding box
class cM3dGAab {
private:
public:
    /* 0x00 */ cXyz mMin;
    /* 0x0C */ cXyz mMax;
    /* 0x18 vtable */

    virtual ~cM3dGAab() {}
    void SetMinMax(const cXyz&);
    void Set(const cXyz& min, const cXyz& max) {
        mMin = min;
        mMax = max;
    }
    void SetMin(const cXyz&);
    void SetMax(const cXyz&);
    const cXyz* GetMaxP(void) const { return &mMax; }
    const cXyz* GetMinP(void) const { return &mMin; }
    const f32 GetMaxX(void) const { return mMax.x; }
    const f32 GetMaxY(void) const { return mMax.y; }
    const f32 GetMaxZ(void) const { return mMax.z; }
    const f32 GetMinX(void) const { return mMin.x; }
    const f32 GetMinY(void) const { return mMin.y; }
    const f32 GetMinZ(void) const { return mMin.z; }
    bool Cross(const cM3dGAab *param_1) {
        return cM3d_Cross_AabAab(this, param_1);
    }
    bool Cross(const cM3dGCyl *param_1) {
        return cM3d_Cross_AabCyl(this, param_1);
    }
    bool Cross(const cM3dGSph *param_1) {
        return cM3d_Cross_AabSph(this, param_1);
    }
    void CalcCenter(cXyz* pOut) const {
        VECAdd(&mMin, &mMax, pOut);
        VECScale(pOut, pOut, 0.5f);
    }
    void ClearForMinMax() {
        mMin.z = 1000000000.0f;
        mMin.y = 1000000000.0f;
        mMin.x = 1000000000.0f;
        mMax.z = -1000000000.0f;
        mMax.y = -1000000000.0f;
        mMax.x = -1000000000.0f;
    }
};  // Size = 0x1C

STATIC_ASSERT(0x1C == sizeof(cM3dGAab));

#endif /* C_M3D_G_AAB_H */
