#ifndef M_DO_M_DO_LIB_H
#define M_DO_M_DO_LIB_H

#include "JSystem/J3DU/J3DUClipper.h"

typedef struct _GXTexObj GXTexObj;
typedef struct _GXTlutObj GXTlutObj;
typedef struct Vec Vec;
struct ResTIMG;

struct mDoLib_clipper {
    static void changeFar(f32 far) {
        mClipper.setFar(far);
        mClipper.calcViewFrustum();
    }

    static s32 clip(const Mtx m, Vec* max, Vec* min) {
        return mClipper.clip(m, max, min);
    }

    static s32 clip(const Mtx m, Vec center, f32 radius) {
        return mClipper.clip(m, center, radius);
    }
    
    static s32 clip(J3DModel* model) {
        return mClipper.clipByBox(model);
    }

    static f32 getFar() { return mSystemFar; }
    static f32 getFovyRate() { return mFovyRate; }
    
    static void resetFar() {
        mClipper.setFar(mSystemFar);
        mClipper.calcViewFrustum();
    }

    static void setup(f32, f32, f32, f32);

    static J3DUClipper mClipper;
    static f32 mSystemFar;
    static f32 mFovyRate;
};

void mDoLib_project(Vec* src, Vec* dst);
u8 mDoLib_setResTimgObj(ResTIMG* res, GXTexObj* o_texObj, u32 tlut_name, GXTlutObj* o_tlutObj);
void mDoLib_pos2camera(Vec* src, Vec* dst);

#endif /* M_DO_M_DO_LIB_H */
