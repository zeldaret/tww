#ifndef C_LIB_H_
#define C_LIB_H_

#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_math.h"
#include "dolphin/mtx/mtx.h"

inline bool cLib_IsZero(f32 value) {
    return std::fabsf(value) < 8e-11f;
}

void cLib_memCpy(void* dst, const void* src, unsigned long size);
void cLib_memSet(void* ptr, int value, unsigned long size);

f32 cLib_addCalc(f32* o_value, f32 target, f32 scale, f32 maxStep, f32 minStep);
void cLib_addCalc2(f32* o_value, f32 target, f32 scale, f32 maxStep);
void cLib_addCalc0(f32* o_value, f32 scale, f32 maxStep);
f32 cLib_addCalcPos(cXyz* o_value, cXyz const& target, f32 scale, f32 maxStep, f32 minStep);
f32 cLib_addCalcPosXZ(cXyz* o_value, cXyz const& target, f32 scale, f32 maxStep, f32 minStep);
void cLib_addCalcPos2(cXyz* o_value, cXyz const& target, f32 scale, f32 maxStep);
void cLib_addCalcPosXZ2(cXyz* o_value, cXyz const& target, f32 scale, f32 maxStep);
s16 cLib_addCalcAngleS(s16* o_value, s16 target, s16 scale, s16 maxStep, s16 minStep);
void cLib_addCalcAngleS2(s16* o_value, s16 target, s16 scale, s16 maxStep);
s32 cLib_addCalcAngleL(s32* pValue, s32 target, s32 scale, s32 maxStep, s32 minStep);

int cLib_chaseUC(u8* o_value, u8 target, u8 step);
int cLib_chaseS(s16* o_value, s16 target, s16 step);
int cLib_chaseF(f32* o_value, f32 target, f32 step);
int cLib_chasePos(cXyz* o_value, cXyz const& target, f32 step);
int cLib_chasePosXZ(cXyz* o_value, cXyz const& target, f32 step);
int cLib_chaseAngleS(s16* o_value, s16 target, s16 step);

s16 cLib_targetAngleY(cXyz* lhs, cXyz* rhs);
s16 cLib_targetAngleX(cXyz*, cXyz*);

void cLib_offsetPos(cXyz* pDest, cXyz* pSrc, s16 angle, cXyz* vec);
s32 cLib_distanceAngleS(s16 x, s16 y);

template <typename T>
inline void cLib_offBit(T& value, T bit) {
    value = static_cast<T>(value & ~bit);
}

template <typename T>
inline void cLib_onBit(T& value, T bit) {
    value = static_cast<T>(value | bit);
}

template <typename T>
inline T cLib_checkBit(T value, T bit) {
    return static_cast<T>(value & bit);
}

template <typename T>
inline void cLib_setBit(T& value, T bit) {
    value = bit;
}

template <typename T>
inline T cLib_minMaxLimit(T val, T min, T max) {
    return (T)((T)val < (T)min ? (T)min : ((T)val > (T)max ? (T)max : (T)val));
    // Might also be one of these? Try them first if having issues getting this inline to match.
    // return (T)((T)val < min ? min : ((T)val > max ? max : (T)val));
    // return (T)(val < min ? min : (val > max ? max : val));
}

template <typename T>
inline bool cLib_checkMinMaxLimit(T val, T min, T max) {
    return val >= min && val <= max;
}

template <typename T>
inline T cLib_maxLimit(T val, T max) {
    return (T)((T)val > (T)max ? (T)max : (T)val);
}

template <typename T>
inline T cLib_minLimit(T val, T min) {
    return (T)((T)val < (T)min ? (T)min : (T)val);
}

template <typename T>
T cLib_getRndValue(T min, T range) {
    return (T)(min + cM_rndF((f32)range));
}

template <typename T>
T cLib_calcTimer(T* value) {
    if (*(T*)value != 0) {
        *value = *value - 1;
    }
    return *value;
}

void MtxInit(void);
void MtxTrans(f32, f32, f32, u8);
void MtxScale(f32, f32, f32, u8);
void MtxPosition(cXyz* src, cXyz* dest);
void MtxPush(void);
Mtx* MtxPull(void);
void MtxRotX(f32 rot, u8 concat);
void MtxRotY(f32 rot, u8 concat);
void MtxRotZ(f32 rot, u8 concat);

extern Mtx* calc_mtx;

#endif
