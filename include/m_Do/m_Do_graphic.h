#ifndef M_DO_M_DO_GRAPHIC_H
#define M_DO_M_DO_GRAPHIC_H

#include "JSystem/JFramework/JFWDisplay.h"
#include "dolphin/mtx/mtx.h"

void mDoGph_Create();

struct ResTIMG;
class mDoGph_gInf_c {
public:
    static void create();
    static void createHeap();
    static void alloc(u32, int);
    static void free();
    static void fadeOut(f32, GXColor&);
    static void onBlure();
    static void onBlure(const Mtx);
    static void fadeOut(f32);
    static void calcFade();
    static void onMonotone();
    static void offMonotone();
    static void calcMonotone();
    static void setFrameRate(u16);
    static void getFrameRate();

    static void setFader(JUTFader* fader) {
        JFWDisplay::getManager()->setFader(fader);
        mFader = fader;
    }

    static BOOL startFadeOut(int param_0) { return JFWDisplay::getManager()->startFadeOut(param_0); }
    static BOOL startFadeIn(int param_0) { return JFWDisplay::getManager()->startFadeIn(param_0); }
    static void setFadeColor(JUtility::TColor color) { mFader->mColor.set(color); }
    static void setClearColor(JUtility::TColor color) {
        JFWDisplay::getManager()->setClearColor(color);
    }
    static void setBackColor(GXColor& color) { mBackColor = color; }
    static void endFrame() { JFWDisplay::getManager()->endFrame(); }
    static void offFade() { mFade = 0; }
    static u8 isFade() { return mFade; }
    static void offBlure() { mBlureFlag = false; }
    static bool isBlure() { return mBlureFlag; }
    static u8 getBlureRate() { return mBlureRate; }
    static MtxP getBlureMtx() { return mBlureMtx; }
    /* static void offAutoForcus() { data_80450BE7 = 0; }
    static bool isAutoForcus() { return data_80450BE7; } */
    static void setTickRate(u32 rate) { JFWDisplay::getManager()->setTickRate(rate); }
    static void waitBlanking(int wait) { JFWDisplay::getManager()->waitBlanking(wait); }
    static BOOL isMonotone() { return mMonotone; }

    static ResTIMG* getFrameBufferTimg() { return mFrameBufferTimg; }
    static void* getFrameBufferTex() { return mFrameBufferTex; }
    static void* getZbufferTex() { return mZbufferTex; }
    static void setFadeRate(f32 rate) { mFadeRate = rate; }
    static f32 getFadeRate() { return mFadeRate; }
    static GXColor& getFadeColor() { return mFadeColor; }
    static GXColor& getBackColor() { return mBackColor; }
    static void endRender() { JFWDisplay::getManager()->endRender(); }
    static GXTexObj* getZbufferTexObj() { return &mZbufferTexObj; }
    static GXTexObj* getFrameBufferTexObj() { return &mFrameBufferTexObj; }

    static GXTexObj mFrameBufferTexObj;
    static GXTexObj mZbufferTexObj;
    static Mtx mBlureMtx;
    static GXColor mBackColor;
    static GXColor mFadeColor;
    static JUTFader* mFader;
    static ResTIMG* mFrameBufferTimg;
    static void* mFrameBufferTex;
    static ResTIMG* mZbufferTimg;
    static void* mZbufferTex;
    static f32 mFadeRate;
    static f32 mFadeSpeed;
    static bool mBlureFlag;
    static u8 mBlureRate;
    static u8 mFade;
    static u8 mMonotone;
    static s16 mMonotoneRate;
    static s16 mMonotoneRateSpeed;
};

#endif /* M_DO_M_DO_GRAPHIC_H */