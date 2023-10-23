//
// Generated by dtk
// Translation Unit: JASAudioThread.cpp
//

#include "JSystem/JAudio/JASAudioThread.h"
#include "JSystem/JAudio/JASAiCtrl.h"
#include "JSystem/JAudio/JASDSPBuf.h"
#include "JSystem/JAudio/JASDSPInterface.h"
#include "JSystem/JAudio/JASDriverIF.h"
#include "JSystem/JAudio/JASDvdThread.h"
#include "JSystem/JAudio/JASKernelDebug.h"
#include "JSystem/JAudio/JASProbe.h"
#include "JSystem/JAudio/JASRate.h"
#include "JSystem/JAudio/JASSystemHeap.h"
#include "JSystem/JAudio/dspproc.h"
#include "JSystem/JAudio/dsptask.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/ai/ai.h"

OSThread JASystem::TAudioThread::sAudioThread;
u8 JASystem::TAudioThread::saAudioStack[4096];
OSMessageQueue JASystem::TAudioThread::sAudioprocMQ;

u32 JASystem::TAudioThread::sAudioprocMQInit;
int JASystem::TAudioThread::sbIsPrioritySet;
s32 JASystem::TAudioThread::sDSPPrio;
s32 JASystem::TAudioThread::sDVDPrio;
vs32 JASystem::TAudioThread::snIntCount;
int JASystem::TAudioThread::sbIsDSPBoot;

/* 80288F08-80288F88       .text syncAudio__Q28JASystem12TAudioThreadFv */
void JASystem::TAudioThread::syncAudio() {
    static u32 first = 1;
    if (first == 0) {
        Kernel::probeFinish(4);
    }
    first = 0;
    Kernel::probeStart(4, "UPDATE-DAC");
    if (sAudioprocMQInit) {
        OSSendMessage(&sAudioprocMQ, NULL, OS_MESSAGE_NOBLOCK);
    }
    /* Nonmatching */
}

/* 80288F88-80289130       .text audioproc__Q28JASystem12TAudioThreadFPv */
void* JASystem::TAudioThread::audioproc(void*) {
    /* Nonmatching */
    JKRThread thread(&sAudioThread, 0);
    i_OSInitFastCast();
    OSInitMessageQueue(&sAudioprocMQ, saAudioMsgBuf, 16);
    sAudioprocMQInit = 1;
    Kernel::init();
    TDSP_DACBuffer::init();
    if (!sbIsDSPBoot) {
        DspBoot(syncDSP);
        sbIsDSPBoot = 1;
    }
    Driver::init();
    AISetDSPSampleRate(Kernel::gAiSetting);
    AIRegisterDMACallback(syncAudio);
    AIStartDMA();
    while (true) {
        OSMessage message;
        OSReceiveMessage(&sAudioprocMQ, &message, 1);
        switch (int(message)) {
        case 0:
            Kernel::updateDac();
            break;
        case 1:
            JUT_ASSERT(145, snIntCount != 0);
            snIntCount--;
            if (snIntCount == 0) {
                Kernel::probeFinish(7);
                TDSP_DACBuffer::finishDSPFrame();
            } else {
                Kernel::probeStart(2, (char*)"SFR_DSP");
                TDSP_DACBuffer::updateDSP();
                Kernel::probeFinish(2);
            }
            break;
        case 2:
            break;
        case 3:
            OSReport("----- Audio thread stops\n");
            OSExitThread(0);
            break;
        }
    }
    return NULL;
}

/* 80289130-802891F0       .text syncDSP__Q28JASystem12TAudioThreadFPv */
void JASystem::TAudioThread::syncDSP(void*) {
    /* Nonmatching */
    while (!DSPCheckMailFromDSP()) {}
    u32 var1 = DSPReadMailFromDSP();
    if (var1 >> 16 != DSPInterface::JAS_DSP_PREFIX) {
        OSReport("----- syncDSP : Mail format error %x\n");
        return;
    }
    if ((var1 & 0xff00) == 0xff00) {
        if (sAudioprocMQInit) {
            if (!OSSendMessage(&sAudioprocMQ, OSMessage(1), OS_MESSAGE_NOBLOCK)) {
                OSReport("----- syncDSP : Send Miss\n");
            }
        } else {
            DSPReleaseHalt();
        }
    } else {
        DspFinishWork(var1);
    }
}

/* 802891F0-8028920C       .text setPriority__Q28JASystem12TAudioThreadFUcUc */
void JASystem::TAudioThread::setPriority(u8 param_1, u8 param_2) {
    sbIsPrioritySet = 1;
    sDSPPrio = param_1;
    sDVDPrio = param_2;
}

/* 8028920C-802892E0       .text start__Q28JASystem12TAudioThreadFP12JKRSolidHeapUlUl */
void JASystem::TAudioThread::start(JKRSolidHeap* param_1, u32 param_2, u32 param_3) {
    /* Nonmatching */
    if (!sbIsPrioritySet) {
        s32 priority = OSGetThreadPriority(OSGetCurrentThread());
        sDSPPrio = priority - 3;
        sDVDPrio = priority - 1;
    }
    Kernel::sysDramSetup(param_1);
    Kernel::sysAramSetup(param_2);
    Dvd::createThread(sDVDPrio, 0x5a, 0x1000);
    Dvd::resumeThread();
    Kernel::stackInit((u64*)saAudioStack, 0x200);
    if ((param_3 & 2)) {
        OSCreateThread(&sAudioThread, audioproc, NULL, &saAudioStack[sizeof(saAudioStack)], sizeof(saAudioStack), sDSPPrio, 1);
        OSResumeThread(&sAudioThread);
    }
}
