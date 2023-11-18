
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
    static u16 getEfbHeight() { return getRenderModeObj()->efb_height; }
    static u16 getFbWidth() { return getRenderModeObj()->fb_width; }
    static void setFbWidth(s16 v) { getRenderModeObj()->fb_width = v; }
    static void setEfbHeight(s16 v) { getRenderModeObj()->efb_height = v; }

    static GXRenderModeObj* getRenderModeObj() { return mRenderModeObj; }

    static GXRenderModeObj* mRenderModeObj;
};

#endif /* M_DO_M_DO_MACHINE_H */
