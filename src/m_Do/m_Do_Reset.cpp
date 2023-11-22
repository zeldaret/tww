/**
 * m_Do_Reset.cpp
 * Game Reset Management
 */

#include "m_Do/m_Do_Reset.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "JSystem/JUtility/JUTXfb.h"
#include "dolphin/gx/GX.h"
#include "dolphin/os/OS.h"
#include "m_Do/m_Do_DVDError.h"
#include "m_Do/m_Do_audio.h"

/* 80017D40-80017D44       .text my_OSCancelAlarmAll__Fv */
static void my_OSCancelAlarmAll() {}

/* 80017D44-80017D7C       .text destroyVideo__Fv */
void destroyVideo() {
    JUTVideo::destroyManager();
    GXSetDrawDoneCallback(NULL);
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
}

#if VERSION == VERSION_JPN
int mDoRst::mResetFlag;
int mDoRst::mResetPrepare;
int mDoRst::m3ButtonResetFlag;
int mDoRst::m3ButtonResetPort = -1;
#else
mDoRstData* mDoRst::mResetData;
#endif

/* 80017D7C-80017E40       .text mDoRst_reset__FiUli */
void mDoRst_reset(int param_0, u32 param_1, int param_2) {
    if (DVDGetDriveStatus() == DVD_STATE_FATAL_ERROR) {
        do {
        } while (true);
    }

    JUTXfb::getManager()->clearIndex();
    mDoDvdErr_ThdCleanup();
    JUTGamePad::clearForReset();
    mDoAud_zelAudio_c::offInitFlag();

#if VERSION != VERSION_JPN
    VIWaitForRetrace();
    VIWaitForRetrace();
#endif

    OSThread* gxThread = GXGetCurrentGXThread();
    s32 enable = OSDisableInterrupts();

    if (gxThread != OSGetCurrentThread()) {
        OSCancelThread(gxThread);
        GXSetCurrentGXThread();
    }

    GXFlush();
    GXAbortFrame();
    GXDrawDone();
    OSRestoreInterrupts(enable);
    destroyVideo();
    my_OSCancelAlarmAll();
    LCDisable();
#if VERSION != VERSION_JPN
    OSSetSaveRegion(mDoRst::mResetData, (u8*)&mDoRst::getResetData + 0x10);
#endif
    OSResetSystem(param_0, param_1, param_2);

    do {
        VIWaitForRetrace();
    } while (true);
}

/* 80017E40-80017EF0       .text mDoRst_resetCallBack__FiPv */
void mDoRst_resetCallBack(int port, void*) {
    if (!mDoRst::isReset()) {
        if (port == -1) {
            JUTGamePad::clearForReset();
            JUTGamePad::CRumble::setEnabled(0xF0000000);
        } else {
            if (mDoRst::is3ButtonReset()) {
                JUTGamePad::C3ButtonReset::sResetOccurred = false;
                JUTGamePad::C3ButtonReset::sCallback = mDoRst_resetCallBack;
                JUTGamePad::C3ButtonReset::sCallbackArg = NULL;
                return;
            }
            mDoRst::on3ButtonReset();
            mDoRst::set3ButtonResetPort(port);
            JUTGamePad::clearForReset();
            JUTGamePad::CRumble::setEnabled(0xF0000000);
        }
#if VERSION != VERSION_JPN
        if (DVDCheckDisk() == 0) {
            mDoRst_reset(1, 0x80000000, 0);
        }
#endif
        mDoRst::onReset();
    }
}
