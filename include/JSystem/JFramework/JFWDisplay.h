#ifndef JFWDISPLAY_H
#define JFWDISPLAY_H

#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/JUtility/JUTXfb.h"
#include "dolphin/os/OSAlarm.h"
#include "dolphin/types.h"

typedef struct _GXColor GXColor;
typedef struct _GXRenderModeObj GXRenderModeObj;
class JKRHeap;

typedef void (*JFWDisplayUnkFunc)(void);

extern u8 JFWAutoAbortGfx;

class JFWAlarm : public OSAlarm {
public:
    JFWAlarm() /* : mLink(this) */ {}
    ~JFWAlarm() {}
    void createAlarm() { OSCreateAlarm(this); }
    void cancelAlarm() { OSCancelAlarm(this); }
    //void removeLink() { sList.remove(&mLink); }
    //void appendLink() { sList.append(&mLink); }
    OSThread* getThread() const { return mThread; }
    void setThread(OSThread* thread) { mThread = thread; }

    static JSUList<JFWAlarm> sList;

public:
    /* 0x30 */ OSThread* mThread;
};

class JFWDisplay {
public:
    enum EDrawDone {
        /* 0x0 */ Sync = 0,
        /* 0x1 */ Async = 1,
    };

    void ctor_subroutine(const GXRenderModeObj*, bool enableAlpha);
    JFWDisplay(const GXRenderModeObj*, JKRHeap*, JUTXfb::EXfbNumber, bool);
    static JFWDisplay* createManager(JKRHeap*, JUTXfb::EXfbNumber, bool);
    void prepareCopyDisp();
    void drawendXfb_single();
    void exchangeXfb_double();
    void exchangeXfb_triple();
    void copyXfb_triple();
    void preGX();
    void endGX();
    void waitBlanking(int);
    void threadSleep(s64);
    void clearEfb_init();
    void clearEfb(int param_0, int param_1, int param_2, int param_3, GXColor color);
    void clearEfb();
    void clearEfb(GXColor color);
    void calcCombinationRatio();

    virtual void beginRender();
    virtual void endRender();
    virtual void endFrame();
    virtual ~JFWDisplay();

    static JFWDisplay* getManager() { return sManager; }

    BOOL startFadeOut(int fadeTime) {
        if (mpFader != NULL) {
            return mpFader->startFadeOut(fadeTime);
        }
        return 1;
    }

    BOOL startFadeIn(int fadeTime) {
        if (mpFader != NULL) {
            return mpFader->startFadeIn(fadeTime);
        }
        return 1;
    }

    void setTickRate(u32 rate) {
        mTickRate = rate;
        mFrameRate = 0;
    }

    void setDrawDoneMethod(EDrawDone drawDone) { mDrawDoneMethod = drawDone; }
    void setFader(JUTFader* fader) { mpFader = fader; }
    JUTFader * getFader() { return mpFader; }
    void setClearColor(JUtility::TColor color) { mClearColor = color; }

    u16 getFrameRate() const { return mFrameRate; }
    void setFrameRate(u16 framerate) {
        mFrameRate = framerate;
        mTickRate = 0;
    }

    void getEfbHeight() const {}
    void getEfbWidth() const {}
    void getXfbManager() const {}

    static JFWDisplay* sManager;

private:
    /* 0x04 */ JUTFader* mpFader;
    /* 0x08 */ const GXRenderModeObj* mpRenderMode;
    /* 0x0C */ JUtility::TColor mClearColor;
    /* 0x10 */ u32 mZClear;
    /* 0x14 */ JUTXfb* mXfbManager;
    /* 0x18 */ u16 mGamma;
    /* 0x1C */ EDrawDone mDrawDoneMethod;
    /* 0x20 */ u16 mFrameRate;
    /* 0x24 */ u32 mTickRate;
    /* 0x28 */ bool mEnableAlpha;
    /* 0x2A */ u16 mClamp;
    /* 0x2C */ f32 mCombinationRatio;
    /* 0x30 */ u32 field_0x30;
    /* 0x34 */ u32 field_0x34;
    /* 0x38 */ u32 field_0x38;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ u8 field_0x3E;
};

inline void JUTChangeFrameBuffer(void* buffer, u16 height, u16 width) {
    JUTDirectPrint::getManager()->changeFrameBuffer(buffer, width, height);
}

static void JFWDrawDoneAlarm();
static void JFWGXDrawDoneAutoAbort();
static void JFWGXAbortAlarmHandler(OSAlarm* p_alarm, OSContext* p_ctx);
static void waitForTick(u32 p1, u16 p2);
static void diagnoseGpHang();

#endif /* JFWDISPLAY_H */
