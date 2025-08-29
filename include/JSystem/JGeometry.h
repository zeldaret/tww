#ifndef JGEOMETRY_H
#define JGEOMETRY_H

#include "dolphin/mtx/vec.h"
#include "math.h"

namespace JGeometry {

template <typename T>
struct TUtil {
    static inline f32 epsilon() { return 3.81469727e-06f; }

    static inline f32 sqrt(f32 mag) {
        if (mag <= 0.0f) {
            return mag;
        } else {
            f32 root = __frsqrte(mag);
            return 0.5f * root * (3.0f - mag * (root * root)) * mag;
        }
    }

    static inline f32 inv_sqrt(f32 mag) {
        if (mag <= 0.0f) {
            return mag;
        }
        f32 root = __frsqrte(mag);
        root = 0.5f * root * (3.0f - mag * (root * root));
        return root;
    }
};

template <typename T>
struct TVec3 {
    T x;
    T y;
    T z;

    TVec3<T>& operator=(const TVec3<T>& b) {
        set(b.x, b.y, b.z);
        return *this;
    }

    TVec3() {}

    template<T>
    TVec3(const T x, const T y, const T z) { set(x, y, z); }

    template <T>
    void set(T x_, T y_, T z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

template <>
struct TVec3<s16> : public SVec {
    // s16 x, y, z;

    TVec3& operator=(const TVec3& b) {
        set(b.x, b.y, b.z);
        return *this;
    }

    TVec3() {}

    TVec3(const s16 x, const s16 y, const s16 z) { set(x, y, z); }

    void set(s16 x_, s16 y_, s16 z_) {
        x = x_;
        y = y_;
        z = z_;
    }

    TVec3(const int x, const int y, const int z) { set(x, y, z); }

    void set(int x_, int y_, int z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

template <>
struct TVec3<f32> : public Vec {
    TVec3() {}

    template<typename f32>
    TVec3(const f32 x, const f32 y, const f32 z) { set(x, y, z); }

    TVec3(const Vec& b) { set(b); }

    operator Vec*() { return (Vec*)&x; }
    operator const Vec*() const { return (Vec*)&x; }

    template<typename f32>
    void set(const TVec3<f32>& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    void set(const Vec& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    template<typename f32>
    void set(f32 x_, f32 y_, f32 z_) {
        x = x_;
        y = y_;
        z = z_;
    }

    void zero() { x = y = z = 0.0f; }

    void add(const TVec3<f32>& b) {
        x += b.x;
        y += b.y;
        z += b.z;
    }

    void add(const TVec3<f32>& a, const TVec3<f32>& b) {
        x = a.x + b.x;
        y = a.y + b.y;
        z = a.z + b.z;
    }

    void sub(const TVec3<f32>& b) {
        x -= b.x;
        y -= b.y;
        z -= b.z;
    }

    void sub(const TVec3<f32>& a, const TVec3<f32>& b) {
        x = a.x - b.x;
        y = a.y - b.y;
        z = a.z - b.z;
    }

    void mul(const TVec3<f32>& b) {
        x *= b.x;
        y *= b.y;
        z *= b.z;
    }

    void mul(const TVec3<f32>& a, const TVec3<f32>& b) {
        x = a.x * b.x;
        y = a.y * b.y;
        z = a.z * b.z;
    }

    void scale(f32 scale, const TVec3<f32>& b) {
        x = b.x * scale;
        y = b.y * scale;
        z = b.z * scale;
    }

    void scale(f32 scale) {
        x *= scale;
        y *= scale;
        z *= scale;
    }

    void scaleAdd(f32 scale, const TVec3<f32>& b, const TVec3<f32>& c) {
        x = b.x + c.x * scale;
        y = b.y + c.y * scale;
        z = b.z + c.z * scale;
    }

    void negate() {
        x = -x;
        y = -y;
        z = -z;
    }

    f32 dot(const TVec3<f32>& b) const {
        return x*b.x + y*b.y + z*b.z;
    }

    f32 squared() const {
        return dot(*this);
    }

    f32 squared(const TVec3<f32>& b) const {
        return (x - b.x)*(x - b.x) + (y - b.y)*(y - b.y) + (z - b.z)*(z - b.z);
    }

    f32 length() const {
        return TUtil<f32>::sqrt(squared());
    }

    f32 normalize() {
        f32 sq = squared();
        if (sq <= TUtil<f32>::epsilon()) {
            return 0.0f;
        }
        f32 norm = TUtil<f32>::inv_sqrt(sq);
        scale(norm);
        return norm;
    }

    bool isZero() const {
        return squared() <= TUtil<f32>::epsilon();
    }

    void cross(const TVec3<f32>& a, const TVec3<f32>& b) {
        set(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    void cross_hack(const TVec3<f32>& a, const TVec3<f32>& b) {
        // obviously fake
        x = a.y * b.z - a.z * b.y;
        y = a.z * b.x - a.x * b.z;
        z = a.x * b.y - a.y * b.x;
    }

    f32 setLength(f32 len) {
        f32 sq = squared();
        if (sq <= TUtil<f32>::epsilon()) {
            return 0.0f;
        }
        f32 norm = TUtil<f32>::inv_sqrt(sq);
        scale(norm * len);
        return norm * sq;
    }

    f32 setLength(const TVec3<f32>& b, f32 len) {
        f32 sq = b.squared();
        if (sq <= TUtil<f32>::epsilon()) {
            zero();
            return 0.0f;
        }
        f32 norm = TUtil<f32>::inv_sqrt(sq);
        scale(norm * len, b);
        return norm * sq;
    }

    template<typename S>
    void cubic(const JGeometry::TVec3<f32>& vec1, const JGeometry::TVec3<f32>& vec2, const JGeometry::TVec3<f32>& vec3, const JGeometry::TVec3<f32>& vec4, f32 f19) {
        // TODO: name variables properly
        f32 f5 = f19 * f19;
        f32 f4 = f5 * f19;
        f32 f3 = 1.0f + ((2.0f * f4) - (3.0f * f5));
        f32 f2 = (-2.0f * f4) + (3.0f * f5);
        f32 f1 = f19 + (f4 - (2.0f * f5));
        f32 f0 = (f4 - f5);
        this->x = (f3 * vec1.x) + (f2 * vec2.x) + (f1 * vec4.x) + (f0 * vec3.z);
        this->y = (f3 * vec1.y) + (f2 * vec2.y) + (f1 * vec4.y) + (f0 * vec3.y);
        this->z = (f3 * vec1.z) + (f2 * vec2.z) + (f1 * vec4.z) + (f0 * vec3.x);
    }

    inline TVec3<f32>& operator+=(const TVec3<f32>& b) {
        add(b);
        return *this;
    }

    inline TVec3<f32>& operator*=(const TVec3<f32>& b) {
        mul(b);
        return *this;
    }

    inline TVec3<f32>& operator=(const TVec3<f32>& b) {
        set(b.x, b.y, b.z);
        return *this;
    }

    inline TVec3<f32>& operator=(const Vec& vec) {
        set(vec);
        return *this;
    }
};

template <typename T>
struct TVec2 {
    TVec2() {}
    TVec2(T x, T y) { set(x, y); }

    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }

    void set(const TVec2<T>& other) {
        x = other.x;
        y = other.y;
    }

    void setMin(const TVec2<T>& min) {
        if (x >= min.x)
            x = min.x;
        if (y >= min.y)
            y = min.y;
    }

    void setMax(const TVec2<T>& max) {
        if (x <= max.x)
            x = max.x;
        if (y <= max.y)
            y = max.y;
    }

    void add(const TVec2<T>& other) {
        x += other.x;
        y += other.y;
    }

    bool isAbove(const TVec2<T>& other) const {
        return (x >= other.x) && (y >= other.y) ? true : false;
    }

    T dot(const TVec2<T>& other) {
        return x * other.x + y * other.y;
    }

    T squared() {
        return dot(*this);
    }

    T length() {
        T sqr = squared();
        return TUtil<T>::sqrt(sqr);
    }

    T x;
    T y;
};

template <class T>
struct TBox {
    TBox() : i(), f() {}
    TBox(const TBox& other) : i(other.i), f(other.f) {}

    T i, f;
};

// clang-format off
template<> struct TBox<TVec2<f32> > {
    f32 getWidth() const { return f.x - i.x; }
    f32 getHeight() const { return f.y - i.y; }

    bool isValid() const { return f.isAbove(i); }

    void addPos(f32 x, f32 y) {
        addPos(TVec2<f32>(x, y));
    }

    void setSize(TVec2<f32> size) {
        f.x = size.x;
        f.y = size.y;
    }

    void addPos(const TVec2<f32>& pos) {
        i.add(pos);
        f.add(pos);
    }

    bool intersect(const TBox<TVec2<f32> >& other) {
        i.setMax(other.i);
        f.setMin(other.f);
        return isValid();
    }

    TVec2<f32> i, f;
};

template <typename T>
struct TBox2 : TBox<TVec2<T> > {
    TBox2() {}
    TBox2(const TVec2<f32>& i, const TVec2<f32> f) { set(i, f); }
    TBox2(f32 x0, f32 y0, f32 x1, f32 y1) { set(x0, y0, x1, y1); }

    void absolute() {
        if (!this->isValid()) {
            TBox2<T> box(*this);
            this->i.setMin(box.i);
            this->i.setMin(box.f);
            this->f.setMax(box.i);
            this->f.setMax(box.f);
        }
    }

    void set(const TBox2& other) { set(other.i, other.f); }
    void set(const TVec2<f32>& i, const TVec2<f32>& f) { this->i.set(i), this->f.set(f); }
    void set(f32 x0, f32 y0, f32 x1, f32 y1) { this->i.set(x0, y0); this->f.set(x1, y1); }
};

// clang-format on

}  // namespace JGeometry

#endif
