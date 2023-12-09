#ifndef C_M3D_H_
#define C_M3D_H_

#include "MSL_C/math.h"
#include "dolphin/types.h"
#include "dolphin/mtx/vec.h"
#include "dolphin/mtx/mtx.h"

class cM3dGAab;
class cM3dGCps;
class cM3dGCyl;
class cM3dGLin;
class cM3dGPla;
class cM3dGSph;
class cM3dGTri;
class csXyz;
class cXyz;

struct cM3d_Range;
struct Vec;

extern f32 G_CM3D_F_ABS_MIN;

void cM3d_InDivPos1(const Vec*, const Vec*, f32, Vec*);
void cM3d_InDivPos2(const Vec*, const Vec*, f32, Vec*);
f32 cM3d_Len2dSq(f32, f32, f32, f32);
bool cM3d_Len2dSqPntAndSegLine(f32, f32, f32, f32, f32, f32, f32*, f32*, f32*);
bool cM3d_Len3dSqPntAndSegLine(const cM3dGLin*, const Vec*, Vec*, f32*);
f32 cM3d_SignedLenPlaAndPos(const cM3dGPla*, const Vec*);
f32 cM3d_VectorProduct2d(f32, f32, f32, f32, f32, f32);
void cM3d_CalcPla(const Vec*, const Vec*, const Vec*, Vec*, f32*);
bool cM3d_Cross_AabAab(const cM3dGAab*, const cM3dGAab*);
bool cM3d_Cross_AabCyl(const cM3dGAab*, const cM3dGCyl*);
bool cM3d_Cross_AabSph(const cM3dGAab*, const cM3dGSph*);
int cM3d_Check_LinLin(const cM3dGLin*, const cM3dGLin*, f32*, f32*);
bool cM3d_Cross_LinPla(const cM3dGLin*, const cM3dGPla*, Vec*, bool, bool);
bool cM3d_Cross_MinMaxBoxLine(const Vec*, const Vec*, const Vec*, const Vec*);
bool cM3d_InclusionCheckPosIn3PosBox3d(const Vec*, const Vec*, const Vec*, const Vec*, f32);
bool cM3d_InclusionCheckPosIn3PosBox2d(f32, f32, f32, f32, f32, f32, f32, f32, f32);
bool cM3d_CrossX_Tri(const cM3dGTri*, const Vec*, f32);
bool cM3d_CrossX_Tri(const cM3dGTri*, const Vec*);
bool cM3d_CrossX_LinTri_proc(const cM3dGTri*, const Vec*);
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*);
bool cM3d_CrossY_LinTri_proc(const cM3dGTri*, const Vec*);
bool cM3d_CrossY_Tri(const Vec&, const Vec&, const Vec&, const cM3dGPla&, const Vec*);
bool cM3d_CrossY_Tri_Front(const Vec&, const Vec&, const Vec&, const Vec*);
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*, f32*);
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*, f32);
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*, const cM3d_Range*, f32*);
bool cM3d_CrossZ_Tri(const cM3dGTri*, const Vec*, f32);
bool cM3d_CrossZ_Tri(const cM3dGTri*, const Vec*);
bool cM3d_CrossZ_LinTri_proc(const cM3dGTri*, const Vec*);
bool cM3d_Cross_LinTri(const cM3dGLin*, const cM3dGTri*, Vec*, bool, bool);
bool cM3d_Cross_LinTri_Easy(const cM3dGTri*, const Vec*);
bool cM3d_Cross_SphPnt(const cM3dGSph*, const Vec*);
bool cM3d_Cross_LinSph(const cM3dGLin*, const cM3dGSph*, Vec*);
int cM3d_Cross_LinSph_CrossPos(const cM3dGSph&, const cM3dGLin&, Vec*, Vec*);
bool cM3d_Cross_CylSph(const cM3dGCyl*, const cM3dGSph*, f32*);
bool cM3d_Cross_CylSph(const cM3dGCyl*, const cM3dGSph*, Vec*, f32*);
bool cM3d_Cross_SphSph(const cM3dGSph*, const cM3dGSph*, f32*);
bool cM3d_Cross_SphSph(const cM3dGSph*, const cM3dGSph*, f32*, f32*);
bool cM3d_Cross_SphSph(const cM3dGSph*, const cM3dGSph*, Vec*);
void cM3d_CalcSphVsTriCrossPoint(const cM3dGSph*, const cM3dGTri*, Vec*);
bool cM3d_Cross_SphTri(const cM3dGSph*, const cM3dGTri*, Vec*);
inline bool cM3d_Cross_SphTri(const cM3dGSph* param_0, const cM3dGTri* param_1) {
    return cM3d_Cross_SphTri(param_0, param_1, NULL);
}
bool cM3d_Cross_CylCyl(const cM3dGCyl*, const cM3dGCyl*, f32*);
bool cM3d_Cross_CylCyl(const cM3dGCyl*, const cM3dGCyl*, Vec*);
bool cM3d_Cross_CylTri(const cM3dGCyl*, const cM3dGTri*, Vec*);
int cM3d_Cross_CylLin(const cM3dGCyl*, const cM3dGLin*, Vec*, Vec*);
int cM3d_Cross_CylPntPnt(const cM3dGCyl*, const Vec*, const Vec*, Vec*, Vec*);
bool cM3d_Cross_CylPnt(const cM3dGCyl*, const Vec*);
bool cM3d_Cross_CpsCps(const cM3dGCps&, const cM3dGCps&, Vec*);
bool cM3d_Cross_CpsCyl(const cM3dGCps&, const cM3dGCyl&, Vec*);
bool cM3d_Cross_CpsSph_CrossPos(const cM3dGCps&, const cM3dGSph&, const Vec&, Vec*);
bool cM3d_Cross_CpsSph(const cM3dGCps&, const cM3dGSph&, Vec*);
bool cM3d_Cross_TriTri(const cM3dGTri&, const cM3dGTri&, Vec*);
bool cM3d_Cross_CpsTri(const cM3dGCps&, cM3dGTri, Vec*);
void cM3d_CalcVecAngle(const Vec&, short*, short*);
void cM3d_CalcVecZAngle(const Vec&, csXyz*);
void cM3d_PlaneCrossLineProcWork(f32, f32, f32, f32, f32, f32, f32, f32*, f32*);
int cM3d_2PlaneCrossLine(const cM3dGPla&, const cM3dGPla&, cM3dGLin*);
bool cM3d_3PlaneCrossPos(const cM3dGPla&, const cM3dGPla&, const cM3dGPla&, Vec*);
f32 cM3d_lineVsPosSuisenCross(const cM3dGLin*, const Vec*, Vec*);
f32 cM3d_lineVsPosSuisenCross(const Vec&, const Vec&, const Vec&, Vec*);
int cM3d_2PlaneLinePosNearPos(const cM3dGPla&, const cM3dGPla&, const Vec*, Vec*);
void cM3d_CrawVec(const Vec&, const Vec&, Vec*);
void cM3d_UpMtx_Base(const Vec&, const Vec&, MtxP);

inline bool cM3d_IsZero(f32 f) {
    return fabsf(f) < G_CM3D_F_ABS_MIN;
}
// this is the inline cM3d_IsZero but inverted. Sometimes this will get a match where the regular cM3d_IsZero inline won't
inline bool cM3d_IsZero_inverted(f32 param_0) {
    return !(fabsf(param_0) < G_CM3D_F_ABS_MIN);
}

inline void cM3d_VectorProduct(const Vec* p01, const Vec* p02, Vec* pDst) {
    VECCrossProduct(p01, p02, pDst);
}

inline void cM3d_VectorProduct(const Vec* p0, const Vec* p1, const Vec* p2, Vec* pDst) {
    Vec v01, v02;
    VECSubtract(p1, p0, &v01);
    VECSubtract(p2, p0, &v02);
    VECCrossProduct(&v01, &v02, pDst);
}

inline f32 cM3d_VectorProduct2d(f32 pX1, f32 pY1, f32 pX2, f32 pY2, f32 pX3, f32 pY3) {
    return (pX2 - pX1) * (pY3 - pY1) - (pY2 - pY1) * (pX3 - pX1);
}

inline bool cM3d_CrossInfLineVsInfPlane_proc(f32 a, f32 b, const Vec* pA, const Vec* pB, Vec* pDst) {
    if (cM3d_IsZero(a - b)) {
        *pDst = *pB;
        return false;
    } else {
        cM3d_InDivPos2(pA, pB, a / (a - b), pDst);
        return true;
    }
}

#endif
