
#ifndef M_DO_M_DO_MACHINE_H
#define M_DO_M_DO_MACHINE_H

#include "dolphin/gx/GX.h"

bool mDoMch_Create();
void mDoMch_HeapCheckAll();

extern GXRenderModeObj g_ntscZeldaIntDf;
extern GXRenderModeObj g_ntscZeldaProg;

class mDoMch_render_c {
public:
    static void setRenderModeObj(GXRenderModeObj* obj) { mRenderModeObj = obj; }
    static void setProgressiveMode() { setRenderModeObj(&g_ntscZeldaProg); }
    static u16 getEfbHeight() { return mRenderModeObj->efbHeight; }
    static u16 getFbWidth() { return mRenderModeObj->fbWidth; }
    static void setFbWidth(u16 v) { mRenderModeObj->fbWidth = v; }
    static void setEfbHeight(u16 v) { mRenderModeObj->efbHeight = v; }

    static GXRenderModeObj* getRenderModeObj() { return mRenderModeObj; }

    static GXRenderModeObj* mRenderModeObj;
};

#endif /* M_DO_M_DO_MACHINE_H */
