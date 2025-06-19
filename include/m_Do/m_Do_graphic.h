#ifndef M_DO_M_DO_GRAPHIC_H
#define M_DO_M_DO_GRAPHIC_H

#include "JSystem/JFramework/JFWDisplay.h"
#include "dolphin/mtx/mtx.h"

bool mDoGph_Create();

struct ResTIMG;

class mDoGph_gInf_c {
public:
    static void create();
    static void createHeap();
    static void* alloc(u32, int);
    static void free();
    static void fadeOut(f32, GXColor&);
    static void onBlure(); // weak?
    static void onBlure(const Mtx); // weak?
    static void fadeOut(f32);
    static void calcFade();
    static void onMonotone();
    static void offMonotone();
    static void calcMonotone();

    static void setFader(JUTFader* fader) {
        JFWDisplay::getManager()->setFader(fader);
        mFader = fader;
    }

    static BOOL startFadeOut(int fadeTime) { return JFWDisplay::getManager()->startFadeOut(fadeTime); }
    static BOOL startFadeIn(int fadeTime) { return JFWDisplay::getManager()->startFadeIn(fadeTime); }
    static void setFadeColor(JUtility::TColor& color) { mFader->setColor(color); }
    static void setClearColor(JUtility::TColor color) { JFWDisplay::getManager()->setClearColor(color); }
    static void setBackColor(GXColor& color) { mBackColor = color; }
    static void endFrame() { JFWDisplay::getManager()->endFrame(); }
    static void offFade() { mFade = 0; }
    static u8 isFade() { return mFade; }
    static void offBlure() { mBlureFlag = false; }
    static bool isBlure() { return mBlureFlag; }
    static u8 getBlureRate() { return mBlureRate; }
    static MtxP getBlureMtx() { return mBlureMtx; }
    static void offAutoForcus() { mAutoForcus = false; }
    static void onAutoForcus() { mAutoForcus = true; }
    static BOOL isAutoForcus() { return mAutoForcus; }
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
    static void beginRender() { JFWDisplay::getManager()->beginRender(); }
    static void endRender() { JFWDisplay::getManager()->endRender(); }
    static GXTexObj* getZbufferTexObj() { return &mZbufferTexObj; }
    static GXTexObj* getFrameBufferTexObj() { return &mFrameBufferTexObj; }
    static void fadeIn(f32 rate, GXColor& color) { fadeOut(-rate, color); }
    static u16 getFrameRate() { return JFWDisplay::getManager()->getFrameRate(); }
    static void setFrameRate(u16 framerate) { JFWDisplay::getManager()->setFrameRate(framerate); }
    static s16 getMonotoneRate() { return mMonotoneRate; }
    static void setMonotoneRate(s16 rate) { mMonotoneRate = rate; }
    static void setMonotoneRateSpeed(s16 speed) { mMonotoneRateSpeed = speed; }

    static void alloc32(u32) {}
    static void getFrameBufferMemory() {}
    static void getFrameBufferSize() {}
    static void setBlureMtx(const Mtx) {}
    static void setBlureRate(u8 blurRate) { mBlureRate = blurRate; }

    static GXTexObj mFrameBufferTexObj;
    static GXTexObj mZbufferTexObj;
    static Mtx mBlureMtx;
    static GXColor mBackColor;
    static GXColor mFadeColor;
    static JUTFader* mFader;
    static ResTIMG* mFrameBufferTimg;
    static void* mFrameBufferTex;
    static void* mZbufferTex;
    static f32 mFadeRate;
    static f32 mFadeSpeed;
    static bool mBlureFlag;
    static u8 mBlureRate;
    static u8 mFade;
    static bool mAutoForcus;
    static u8 mMonotone;
    static s16 mMonotoneRate;
    static s16 mMonotoneRateSpeed;
    static JKRHeap * mHeap[2];
    static u8 mCurrentHeap;
};

extern mDoGph_gInf_c g_mDoGph_graphicInfo;

#endif /* M_DO_M_DO_GRAPHIC_H */
