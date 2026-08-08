#ifndef C_SXYZ_H
#define C_SXYZ_H

#include "dolphin/mtx/vec.h"

class csXyz : public SVec {
public:
    static const csXyz Zero;
#ifdef __MWERKS__
    ~csXyz() {}
    csXyz() {}
    csXyz(s16, s16, s16);
#else
    ~csXyz() = default;
    csXyz() = default;
    csXyz(s16 pX, s16 pY, s16 pZ) {
        x = pX;
        y = pY;
        z = pZ;
    };
#endif
    csXyz operator+(csXyz&);
    void operator+=(csXyz&);
    csXyz operator-(csXyz&);
    csXyz operator*(f32);

    void set(s16 oX, s16 oY, s16 oZ) {
        x = oX;
        y = oY;
        z = oZ;
    }

    void setall(s16 val) {
        x = val;
        y = val;
        z = val;
    }
};

#endif /* C_SXYZ_H */
