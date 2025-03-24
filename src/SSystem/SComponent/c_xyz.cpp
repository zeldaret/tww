//
// Generated by dtk
// Translation Unit: c_xyz.cpp
//

#include "SSystem/SComponent/c_xyz.h"
#include "JSystem/JUtility/JUTAssert.h"

const cXyz cXyz::Zero(0, 0, 0);
const cXyz cXyz::BaseX(1, 0, 0);
const cXyz cXyz::BaseY(0, 1, 0);
const cXyz cXyz::BaseZ(0, 0, 1);
const cXyz cXyz::BaseXY(1, 1, 0);
const cXyz cXyz::BaseXZ(1, 0, 1);
const cXyz cXyz::BaseYZ(0, 1, 1);
const cXyz cXyz::BaseXYZ(1, 1, 1);

/* 80245674-802456C4       .text __pl__4cXyzCFRC3Vec */
cXyz cXyz::operator+(const Vec& vec) const {
    Vec ret;
    VECAdd(this, &vec, &ret);
    return cXyz(ret);
}

/* 802456C4-80245714       .text __mi__4cXyzCFRC3Vec */
cXyz cXyz::operator-(const Vec& vec) const {
    Vec ret;
    VECSubtract(this, &vec, &ret);
    return cXyz(ret);
}

/* 80245714-80245760       .text __ml__4cXyzCFf */
cXyz cXyz::operator*(f32 scale) const {
    Vec ret;
    VECScale(this, &ret, scale);
    return cXyz(ret);
}

/* 80245760-802457A8       .text __ml__4cXyzCFRC3Vec */
cXyz cXyz::operator*(const Vec& vec) const {
    cXyz ret;
    ret.x = this->x * vec.x;
    ret.y = this->y * vec.y;
    ret.z = this->z * vec.z;
    return cXyz(ret);
}

/* 802457A8-802457FC       .text __dv__4cXyzCFf */
cXyz cXyz::operator/(f32 scale) const {
    Vec ret;
    VECScale(this, &ret, 1.0f / scale);
    return cXyz(ret);
}

/* 802457FC-8024584C       .text getCrossProduct__4cXyzCFRC3Vec */
cXyz cXyz::getCrossProduct(const Vec& vec) const {
    Vec ret;
    VECCrossProduct(this, &vec, &ret);
    return cXyz(ret);
}

/* 8024584C-80245874       .text outprod__4cXyzCFRC3Vec */
cXyz cXyz::outprod(const Vec& vec) const {
    return this->getCrossProduct(vec);
}

/* 80245874-80245918       .text norm__4cXyzCFv */
cXyz cXyz::norm(void) const {
    Vec ret;
    JUT_CONFIRM(233, isNearZeroSquare() == 0);
    VECNormalize(this, &ret);
    return cXyz(ret);
}

/* 80245918-802459AC       .text normZP__4cXyzCFv */
cXyz cXyz::normZP(void) const {
    Vec vec;
    if (this->isNearZeroSquare() == false) {
        VECNormalize(this, &vec);
    } else {
        vec = cXyz::Zero;
    }
    return cXyz(vec);
}

/* 802459AC-80245ADC       .text normZC__4cXyzCFv */
cXyz cXyz::normZC(void) const {
    Vec outVec;
    if (this->isNearZeroSquare() == false) {
        VECNormalize(this, &outVec);
    } else {
        outVec = (*this * 1.25f * 1000000.0f).normZP();
        if (this->isNearZeroSquare(cXyz(outVec))) {
            outVec.x = 0.0f;
            outVec.y = 0.0f;
            outVec.z = 1.0f;
            outVec = (Vec){0, 0, 1};
        }
    }
    return outVec;
}

/* 80245ADC-80245B80       .text normalize__4cXyzFv */
cXyz cXyz::normalize(void) {
    JUT_ASSERT(267, isNearZeroSquare() == FALSE);
    VECNormalize(this, this);
    return *this;
}

/* 80245B80-80245C14       .text normalizeZP__4cXyzFv */
cXyz cXyz::normalizeZP(void) {
    if (this->isNearZeroSquare() == false) {
        VECNormalize(this, this);
    } else {
        *this = cXyz::Zero;
    }
    return *this;
}

/* 80245C14-80245C64       .text normalizeRS__4cXyzFv */
bool cXyz::normalizeRS(void) {
    if (this->isNearZeroSquare()) {
        return false;
    } else {
        VECNormalize(this, this);
        return true;
    }
}

/* 80245C64-80245CA4       .text __eq__4cXyzCFRC3Vec */
bool cXyz::operator==(const Vec& vec) const {
    return this->x == vec.x && this->y == vec.y && this->z == vec.z;
}

/* 80245CA4-80245CE4       .text __ne__4cXyzCFRC3Vec */
bool cXyz::operator!=(const Vec& vec) const {
    return !(this->x == vec.x && this->y == vec.y && this->z == vec.z);
}

/* 80245CE4-80245D48       .text isZero__4cXyzCFv */
bool cXyz::isZero(void) const {
    return std::fabsf(this->x) < 3.8146972e-06f &&
           std::fabsf(this->y) < 3.8146972e-06f &&
           std::fabsf(this->z) < 3.8146972e-06f;
}

// Unused, but must be in .rodata to match
static const char * fmt0 = "[%f %f %f]\n";
static const char * fmt1 = "%s=[%f %f %f]\n";
