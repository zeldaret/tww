#ifndef C_SXYZ_H
#define C_SXYZ_H

#include "dolphin/mtx/vec.h"

class csXyz : public SVec {
public:
    static const csXyz Zero;
    ~csXyz() {}
    /* inline */ csXyz() {}
    /* inline */ csXyz(const csXyz& other) : SVec(other){};
    csXyz(s16, s16, s16);
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
