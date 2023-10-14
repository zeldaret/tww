
#ifndef M_DO_M_DO_MACHINE_H
#define M_DO_M_DO_MACHINE_H

#include "dolphin/gx/GX.h"

bool mDoMch_Create();
void mDoMch_HeapCheckAll();

extern GXRenderModeObj g_ntscZeldaProg;

class mDoMch_render_c {
public:
    static void setRenderModeObj(GXRenderModeObj* obj) { mRenderModeObj = obj; }
    static void setProgressiveMode() { setRenderModeObj(&g_ntscZeldaProg); }
    static u16 getEfbHeight() { return mRenderModeObj->efb_height; }
    static u16 getFbWidth() { return mRenderModeObj->fb_width; }

    static GXRenderModeObj* getRenderModeObj() { return mRenderModeObj; }

    static GXRenderModeObj* mRenderModeObj;
};

#endif /* M_DO_M_DO_MACHINE_H */
