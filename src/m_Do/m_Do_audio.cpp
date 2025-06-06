//
// Generated by dtk
// Translation Unit: m_Do_audio.cpp
//

#include "m_Do/m_Do_audio.h"
#include "JSystem/JAudio/JAIGlobalParameter.h"
#include "JSystem/JAudio/JAISequenceMgr.h"
#include "JSystem/JAudio/JAIStreamMgr.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#if VERSION <= VERSION_JPN
#include "JSystem/JUtility/JUTConsole.h"
#endif
#include "SSystem/SComponent/c_lib.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_dvd_thread.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_printf.h"

#include "weak_bss_3569.h" // IWYU pragma: keep

JAIZelInst mDoAud_zelAudio_c::mTact;
mDoAud_zelAudio_c g_mDoAud_zelAudio;

bool mDoAud_zelAudio_c::mInitFlag;
bool mDoAud_zelAudio_c::mResetFlag;
bool mDoAud_zelAudio_c::mBgmSet;
u8 mDoAud_zelAudio_c::mLoadTimer;

JKRSolidHeap* g_mDoAud_audioHeap;

/* 80006D84-80006D90       .text reset__17mDoAud_zelAudio_cFv */
void mDoAud_zelAudio_c::reset() {
    mBgmSet = false;
}

/* 80006D90-80006DC0       .text calcLoadTimer__17mDoAud_zelAudio_cFv */
void mDoAud_zelAudio_c::calcLoadTimer() {
    if (mLoadTimer > 1) {
        cLib_calcTimer(&mLoadTimer);
    }
}

void* mDoAud_StreamBufferPointer;

/* 80006DC0-80006DD4       .text mDoAud_isUsedHeapForStreamBuffer__Fv */
BOOL mDoAud_isUsedHeapForStreamBuffer() {
    return mDoAud_StreamBufferPointer != NULL;
}

u8 mDoAud_StreamBufferBlocks;
JKRExpHeap* mDoAud_audioStreamHeap;

/* 80006DD4-80006F88       .text mDoAud_allocStreamBuffer__Fv */
void mDoAud_allocStreamBuffer() {
    JUT_ASSERT(98, mDoAud_StreamBufferPointer == NULL);
    u32 var1 = mDoAud_StreamBufferBlocks;
    u32 size;
    while (true) {
        JAIGlobalParameter::setParamStreamDecodedBufferBlocks(var1);
        size = JAInter::StreamLib::getNeedBufferSize();
        JUT_ASSERT(124, mDoAud_audioStreamHeap == NULL);
        mDoAud_audioStreamHeap = archiveHeap;
        mDoAud_StreamBufferPointer = JKRAllocFromHeap(archiveHeap, size, 0);
        if (!mDoAud_StreamBufferPointer) {
            mDoAud_audioStreamHeap = gameHeap;
            mDoAud_StreamBufferPointer = JKRAllocFromHeap(gameHeap, size, 0);
        }
        if (!mDoAud_StreamBufferPointer) {
            mDoAud_audioStreamHeap = zeldaHeap;
            mDoAud_StreamBufferPointer = JKRAllocFromHeap(zeldaHeap, size, 0);
        }
        if (mDoAud_StreamBufferPointer) {
            break;
        }
        if (var1 > 3) {
            var1--;
            continue;
        }
        JUT_ASSERT(144, mDoAud_StreamBufferPointer);
        return;
    }
    bool success = g_mDoAud_zelAudio.allocStreamBuffer(mDoAud_StreamBufferPointer, size);
    JUT_ASSERT(148, success);
}

/* 80006F88-8000703C       .text mDoAud_deallocStreamBuffer__Fv */
void mDoAud_deallocStreamBuffer() {
    JUT_ASSERT(174, mDoAud_StreamBufferPointer);
    bool success = g_mDoAud_zelAudio.deallocStreamBuffer();
    JUT_ASSERT(182, success);
    JKRFreeToHeap(mDoAud_audioStreamHeap, mDoAud_StreamBufferPointer);
    mDoAud_audioStreamHeap = NULL;
    mDoAud_StreamBufferPointer = NULL;
}

/* 8000703C-80007040       .text mDoAud_executeStreamBuffer__Fv */
void mDoAud_executeStreamBuffer() {}

/* 80007040-80007090       .text mDoAud_setupStreamBuffer__Fv */
void mDoAud_setupStreamBuffer() {
    JAIGlobalParameter::setParamStreamInsideBufferCut(true);
    mDoAud_StreamBufferPointer = 0;
    mDoAud_StreamBufferBlocks = 12;
    mDoAud_audioStreamHeap = 0;
    JAInter::StreamLib::setAllocBufferCallback(mDoAud_allocStreamBuffer);
    JAInter::StreamLib::setDeallocBufferCallback(mDoAud_deallocStreamBuffer);
}

mDoDvdThd_toMainRam_c* l_affCommand;
mDoDvdThd_mountArchive_c* l_arcCommand;

/* 80007090-80007224       .text mDoAud_Create__Fv */
void mDoAud_Create() {
    if (!l_affCommand) {
        l_affCommand = mDoDvdThd_toMainRam_c::create("/Audiores/JaiInit.aaf", 2, NULL);
        if (!l_affCommand) {
            return;
        }
    }
    if (!l_arcCommand) {
        char buffer[96];
        JAInter::SequenceMgr::getArchiveName(buffer);
        l_arcCommand = mDoDvdThd_mountArchive_c::create(buffer, 0, NULL);
        if (!l_arcCommand) {
            return;
        }
    }
    if (l_affCommand->sync() && l_arcCommand->sync()) {
        JAIGlobalParameter::setParamInitDataPointer(l_affCommand->getMemAddress());
        JAInter::SequenceMgr::setArchivePointer(l_arcCommand->getArchive());
        mDoAud_setupStreamBuffer();
        if (g_mDoAud_audioHeap) {
#if VERSION <= VERSION_JPN
            JUTReportConsole("mDoAud_Create g_mDoAud_zelAudio.init before\n");
#endif
            JKRSetCurrentHeap(NULL);
            g_mDoAud_zelAudio.init(g_mDoAud_audioHeap, 0x00a00000);
            JKRSetCurrentHeap(zeldaHeap);
#if VERSION <= VERSION_JPN
            JUTReportConsole("mDoAud_Create g_mDoAud_zelAudio.init after\n");
#endif
            g_mDoAud_audioHeap->adjustSize();
        } else {
            OSReport_Error("ヒープ確保失敗につきオーディオ初期化できません\n");
        }
        g_mDoAud_zelAudio.setEventBit(dComIfGs_getPEventBit());
        g_mDoAud_zelAudio.reset();
        JAIZelBasic::zel_basic->setOutputMode(OSGetSoundMode());
        JKRHeap::free(l_affCommand->getMemAddress(), NULL);
        delete l_affCommand;
        delete l_arcCommand;
        mDoAud_zelAudio_c::onInitFlag();
        mDoDvdThd::SyncWidthSound = 1;
    }
}

/* 80007224-80007268       .text mDoAud_Execute__Fv */
void mDoAud_Execute() {
    if (!mDoAud_zelAudio_c::isInitFlag()) {
        mDoAud_Create();
    } else {
        mDoAud_executeStreamBuffer();
        g_mDoAud_zelAudio.gframeProcess();
        mDoAud_zelAudio_c::calcLoadTimer();
    }
}

/* 80007268-800073D8       .text mDoAud_getTactDirection__Fii */
int mDoAud_getTactDirection(int stick, int ret) {
    f32 val;
    s16 ang;

    if (stick != 0) {
        val = g_mDoCPd_cpadInfo[0].mMainStickValue;
        ang = g_mDoCPd_cpadInfo[0].mMainStickAngle;
    } else {
        val = g_mDoCPd_cpadInfo[0].mCStickValue;
        ang = g_mDoCPd_cpadInfo[0].mCStickAngle;
    }

    if (val < 0.9f) {
        if (stick != 0) {
            return
                CPad_CHECK_HOLD_DOWN(0) ? 3 :
                CPad_CHECK_HOLD_RIGHT(0) ? 2 :
                CPad_CHECK_HOLD_LEFT(0) ? 4 :
                CPad_CHECK_HOLD_UP(0) ? 1 : 0;
        } else {
            return 0;
        }
    } else {
        s32 angi = abs(ang);
        if (ret == 0) {
            if (angi > 0x6000) {
                return 1;
            } else if (ang >= 0x2000) {
                return 2;
            } else if (ang <= -0x2000) {
                return 4;
            } else {
                return 3;
            }
        } else {
            if (angi > 0x7000) {
                return 1;
            } else if (ang >= 0x3000 && ang <= 0x5000) {
                return 2;
            } else if (ang <= -0x3000 && ang >= -0x5000) {
                return 4;
            } else if (angi < 0x1000) {
                return 3;
            }
        }
    }

    return ret;
}

/* 800073D8-80007424       .text mDoAud_setSceneName__FPCcll */
void mDoAud_setSceneName(const char* i_name, s32 i_roomNo, s32 i_layer) {
    if (mDoAud_zelAudio_c::getLoadTimer() == 0) {
        mDoAud_zelAudio_c::getInterface()->setSceneName((char*)i_name, i_roomNo, i_layer);
        mDoAud_zelAudio_c::setLoadTimer(36);
    }
}

/* 80007424-80007478       .text mDoAud_load1stDynamicWave__Fv */
int mDoAud_load1stDynamicWave() {
    if (mDoAud_zelAudio_c::getLoadTimer() == 0) {
        return 1;
    } else if (mDoAud_zelAudio_c::getLoadTimer() <= 1) {
        mDoAud_zelAudio_c::getInterface()->load1stDynamicWave();
        mDoAud_zelAudio_c::setLoadTimer(0);
        return 1;
    } else {
        return 0;
    }
}
