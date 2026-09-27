#ifndef TPOSITION3_H
#define TPOSITION3_H

#include "dolphin/mtx/mtx.h"
#include "JSystem/JGeometry.h"
#include "JSystem/JMath/JMath.h"

namespace JGeometry {

template <typename T>
struct SMatrix34C {
    T data[3][4];
};

template <>
struct SMatrix34C<f32> {
    f32 data[3][4];

    void identity() { MTXIdentity(data); }

    typedef f32 ArrType[4];
    void set(const ArrType* src) { JMath::gekko_ps_copy12((f32*)data, (f32*)src); }

    operator ArrType*() const { return (ArrType*)data; }
    operator const ArrType*() const { return data; }
};

template <typename T>
struct TMatrix34 : public T {};

template <typename T>
struct TRotation3 : public T {
    void setXYZDir(const TVec3<f32>& x, const TVec3<f32>& y, const TVec3<f32>& z) {
        this->ref(0, 0) = x.x;
        this->ref(1, 0) = x.y;
        this->ref(2, 0) = x.z;
        this->ref(0, 1) = y.x;
        this->ref(1, 1) = y.y;
        this->ref(2, 1) = y.z;
        this->ref(0, 2) = z.x;
        this->ref(1, 2) = z.y;
        this->ref(2, 2) = z.z;
    }
};

template <typename T>
struct TPosition3 : public T {};

typedef TPosition3<TRotation3<TMatrix34<SMatrix34C<f32> > > > TPosition3f32;

}  // namespace JGeometry

#endif
