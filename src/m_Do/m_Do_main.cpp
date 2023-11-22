/**
 * m_Do_main.cpp
 * Main Initialization
 */

#include "m_Do/m_Do_main.h"
#include "DynamicLink.h"
#include "JSystem/JFramework/JFWSystem.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "JSystem/JUtility/JUTReport.h"
#include "MSL_C/string.h"
#include "c/c_dylink.h"
#include "d/d_com_inf_game.h"
#include "f_ap/f_ap_game.h"
#include "global.h"
#include "m_Do/m_Do_MemCard.h"
#include "m_Do/m_Do_Reset.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_dvd_thread.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_machine.h"
#include "m_Do/m_Do_printf.h"

class JUTGamePad;

/* 800056E0-80005748       .text version_check__Fv */
void version_check() {
    if (strcmp("05Sep2002", "05Sep2002") == 0 && strcmp("", "") == 0) {
        return;
    }

    OSReport_Error("SDKのバージョンが一致しません。停止します\n");
    while (true) {
    }
}

/* 80005748-800057AC       .text CheckHeap1__9HeapCheckFv */
void HeapCheck::CheckHeap1() {
    s32 totalUsedSize = mHeap->getTotalUsedSize();
    s32 freeSize = mHeap->getFreeSize();

    if (mMaxTotalUsedSize < totalUsedSize)
        mMaxTotalUsedSize = totalUsedSize;

    if (mMaxTotalFreeSize > freeSize)
        mMaxTotalFreeSize = freeSize;
}

// unused data?
static u32 lit_2100[] = {0x3F800000, 0x3F800000, 0x3F800000};
static u32 lit_2080[] = {0x3F800000, 0x3F800000, 0x3F800000};

char mDoMain::COPYDATE_STRING[18] = "??/??/?? ??:??:??";

static HeapCheck RootHeapCheck = {
    "Root", NULL, 0, 0x7FFFFFFF, 0x1400000, 0x140, 0x10000, 0, 0,
};

static HeapCheck SystemHeapCheck = {
    "System", NULL, 0, 0x7FFFFFFF, 0x870000, 0x87, 0x10000, 0, 0,
};

static HeapCheck ZeldaHeapCheck = {
    "Zelda", NULL, 0, 0x7FFFFFFF, 0x7C0000, 0x7C, 0x10000, 0, 0,
};

static HeapCheck GameHeapCheck = {
    "Game", NULL, 0, 0x7FFFFFFF, 0x300000, 0x30, 0x10000, 0, 0,
};

static HeapCheck ArchiveHeapCheck = {
    "Archive", NULL, 0, 0x7FFFFFFF, 0x880000, 0x88, 0x10000, 0, 0,
};

static HeapCheck CommandHeapCheck = {
    "Command", NULL, 0, 0x7FFFFFFF, 0x1000, 0x10, 0x100, 0, 0,
};

static HeapCheck* HeapCheckTable[HeapCheckTableNum] = {
    &RootHeapCheck, &SystemHeapCheck,  &ZeldaHeapCheck,
    &GameHeapCheck, &ArchiveHeapCheck, &CommandHeapCheck,
};

/* 800057AC-80005858       .text CheckHeap__FP10JUTGamePad */
void CheckHeap(JUTGamePad* i_pad) {
    mDoMch_HeapCheckAll();
    OSCheckActiveThreads();

    bool comboCheck = false;

    // if L + R + Z is pressed
    if ((i_pad->testButton(~CButton::Z)) == (CButton::L | CButton::R) && i_pad->testTrigger(CButton::Z))
        comboCheck = true;

    int saveRel = comboCheck;
    for (int i = 0; i < HeapCheckTableNum; i++) {
        HeapCheckTable[i]->CheckHeap1();
        if (saveRel) {
            HeapCheckTable[i]->saveRelBase();
        }
    }
}

/* 80005858-800058B0       .text countUsed__FP10JKRExpHeap */
static int countUsed(JKRExpHeap* heap) {
    OSDisableScheduler();
    int counter = 0;
    JKRExpHeap::CMemBlock* used_blocks_head = heap->getHeadUsedList();

    while (used_blocks_head) {
        used_blocks_head = used_blocks_head->getNextBlock();
        counter++;
    };

    OSEnableScheduler();
    return counter;
}

/* 800058B0-800058D4       .text getUsedCount__9HeapCheckCFv */
s32 HeapCheck::getUsedCount() const {
    return countUsed(mHeap);
}

/* 800058D4-80005B28       .text heapDisplay__9HeapCheckFv */
void HeapCheck::heapDisplay() {
    s32 heap_size = mHeap->getSize();
    s32 used_count = field_0x14 * mTargetHeapSize;

    field_0x10 = used_count;
    used_count = heap_size - used_count;

    s32 total_used = mHeap->getTotalUsedSize();
    s32 total_free = mHeap->getTotalFreeSize();
    s32 heap_free = mHeap->getFreeSize();

    JUTReport(100, 212, "[%sName]", mName);
    JUTReport(100, 227, "HeapSize         %8ld", heap_size);

    int target_size = field_0x14 * mTargetHeapSize;
    field_0x10 = target_size;

    JUTReport(100, 240, "TargetHeapSize   %8ld", target_size);
    JUTReport(100, 253, "TotalFree        %8ld", total_free - used_count);
    JUTReport(100, 266, "FreeSize         %8ld", heap_free - used_count);
    JUTReport(100, 279, "TotalUsedSize    %8ld", total_used);

    target_size = field_0x14 * mTargetHeapSize;
    field_0x10 = target_size;

    JUTReport(100, 292, "TotalUsedRate        %3ld%%", (int)(total_used * 100) / target_size);
    JUTReport(100, 305, "MaxTotalUsedSize %8ld", mMaxTotalUsedSize);

    target_size = field_0x14 * mTargetHeapSize;
    field_0x10 = target_size;

    JUTReport(100, 318, "MaxTotalUsedRate     %3ld%%", (mMaxTotalUsedSize * 100) / target_size);
    JUTReport(100, 331, "MinFreeSize      %8ld", mMaxTotalFreeSize - used_count);

    target_size = field_0x14 * mTargetHeapSize;
    field_0x10 = target_size;

    JUTReport(100, 344, "MinFreeRate          %3ld%%",
              ((mMaxTotalFreeSize - used_count) * 100) / target_size);
    used_count = countUsed(mHeap);
    JUTReport(100, 357, "UsedCount             %3ld%", used_count);
}

s8 mDoMain::developmentMode = -1;

u32 mDoMain::memMargin = 0xFFFFFFFF;

u8 mHeapBriefType = 4;

static u8 fillcheck_check_frame;

OSTime mDoMain::sPowerOnTime;
OSTime mDoMain::sHungUpTime;

static bool mDisplayHeapSize;

static u8 mSelectHeapBar;

static bool mCheckHeap;

/* 80005B28-80005DE0       .text debugDisplay__Fv */
void debugDisplay() {
    static const char* desc1[5] = {
        "", "TotalFree", "MaxUsed  ", "Used     ", "RelUsed  ",
    };

    static const char* desc2[5] = {
        "", "/ MaxFree", "/HeapSize", "Blk/Bytes", "Blk/Bytes",
    };

    if (mSelectHeapBar >= 1 && mSelectHeapBar <= 6) {
        HeapCheckTable[mSelectHeapBar - 1]->heapDisplay();
    }

    if (mHeapBriefType == 5) {
        JKRAramHeap* heap = JKRAram::getAramHeap();
        if (heap) {
            JUTReport(500, 100, "ARAM Free");
            JUTReport(500, 114, "%d", heap->getFreeSize());
            JUTReport(500, 128, "TotalFree");
            JUTReport(500, 142, "%d", heap->getTotalFreeSize());
            return;
        }
    } else if (mHeapBriefType != 0) {
        JUT_ASSERT(VERSION_SELECT(530, 531, 531), mHeapBriefType < HeapCheckTableNum);

        JUTReport(500, 100, "%s", desc1[mHeapBriefType]);
        JUTReport(500, 114, "%s", desc2[mHeapBriefType]);

        for (int i = 0; i < HeapCheckTableNum; i++) {
            HeapCheck* heap_check = HeapCheckTable[i];

            s32 check1;
            s32 check2;
            switch (mHeapBriefType) {
            case 1:
                check1 = heap_check->getHeap()->getTotalFreeSize();
                check2 = heap_check->getHeap()->getFreeSize();
                break;
            case 2:
                check1 = heap_check->getMaxTotalUsedSize();
                check2 = heap_check->getHeap()->getHeapSize();
                break;
            case 3:
                check1 = heap_check->getUsedCount();
                check2 = heap_check->getHeap()->getTotalUsedSize();
                break;
            case 4:
                check1 = heap_check->getRelUsedCount();
                check2 = heap_check->getRelTotalUsedSize();
                break;
            }

            JUTReport(500, (i * 44) + 150, " [%s]", heap_check->getName());
            JUTReport(500, (i * 44) + 164, "%10d", check1);
            JUTReport(500, (i * 44) + 178, "%10d", check2);
        }
    }
}

/* 80005DE0-800061E0       .text Debug_console__FP10JUTGamePad */
bool Debug_console(JUTGamePad* i_pad) {
    JUTConsole* console = JFWSystem::getSystemConsole();
    if (console) {
        static f32 console_position_x = 20.0f;
        static f32 console_position_y = 30.0f;
        static f32 console_scroll = 0.0f;

        if ((i_pad->getTrigger() & CButton::Z) && !(i_pad->getButton() & ~CButton::Z)) {
            console->setVisible(console->isVisible() == false);
            JUTAssertion::setMessageCount(0);
        }

        if (console->isVisible()) {
            u32 holdButtons = i_pad->getButton();
            if ((holdButtons & CButton::L && holdButtons & CButton::R) ||
                ((i_pad->getAnalogL() != 0 && i_pad->getAnalogR() != 0)))
            {
                f32 stick_x = i_pad->getMainStickX();
                f32 stick_y = i_pad->getMainStickY();

                if ((holdButtons & CButton::X) && (holdButtons & CButton::Y) &&
                    i_pad->getTrigger() & CButton::START)
                {
                    console->clear();
                }

                if (!(i_pad->getButton() & CButton::X) && !(i_pad->getButton() & CButton::Y)) {
                    console_scroll -= stick_y;

                    int scrollAmount;
                    if (console_scroll > 1.0f) {
                        scrollAmount = console_scroll;
                    } else if (console_scroll < -1.0f) {
                        scrollAmount = -(int)-console_scroll;
                    } else {
                        scrollAmount = 0;
                    }

                    if (scrollAmount != 0) {
                        console_scroll -= scrollAmount;
                        console->scroll(scrollAmount);
                    }
                } else {
                    if (i_pad->getButton() & CButton::X) {
                        console_position_x += stick_x;
                    }

                    if (i_pad->getButton() & CButton::Y) {
                        console_position_y -= stick_y;
                    }
                }

                if (i_pad->getTrigger() & CButton::A) {
                    console->dumpToTerminal(0xFFFFFFFF);
                    console->setOutput(JUTConsole::OUTPUT_OSREPORT | JUTConsole::OUTPUT_CONSOLE);
                }

                JUTReport(30, 390, 1, "Press X+Y+START to CLEAR console.");
                JUTReport(30, 400, 1, "3DStick UP/Down to scroll");
                JUTReport(30, 410, 1, "Press A to output terminal from console.");
                JUTReport(30, 420, 1, "SCROLL：%3d %3d %3d Output=%1x", console->getLineOffset(),
                          console->getPositionX(), console->getPositionY(), console->getOutput());
            } else {
                if (i_pad->getTrigger() & CButton::DPAD_DOWN) {
                    g_HIO.mDisplayMeter ^= 1;
                }

                if (i_pad->getTrigger() & CButton::DPAD_LEFT) {
                    if (JKRAram::getAramHeap()) {
                        JKRAram::getAramHeap()->dump();
                    }

                    DynamicModuleControlBase::dump();
                    g_dComIfG_gameInfo.mResControl.dump();
                }

                if (i_pad->getTrigger() & CButton::DPAD_RIGHT) {
                    JKRHeap::getSystemHeap()->dump_sort();
                }

                if (i_pad->getTrigger() & CButton::DPAD_UP) {
                    zeldaHeap->dump_sort();
                    gameHeap->dump_sort();
                    archiveHeap->dump_sort();
                }
                JUTReport(30, 440, 1, "Press L+R trigger to control console.");
                JUTReport(30, 450, 1, "Press [Z] trigger to close this window.");
            }
            console->setPosition(console_position_x, console_position_y);
            return 1;
        }
    }
    return 0;
}

/* 800061E0-800061E8       .text dump_sort__7JKRHeapFv */
bool JKRHeap::dump_sort() {
    return 1;
}

/* 800061E8-80006264       .text LOAD_COPYDATE__FPv */
s32 LOAD_COPYDATE(void*) {
    s32 status;

    DVDFileInfo ALIGN_DECL(0x20) fileInfo;
    u8 buffer[0x20];
    status = DVDOpen("/COPYDATE", &fileInfo);

    if (status) {
        DVDReadPrio(&fileInfo, &buffer, 32, 0, 2);
        memcpy(mDoMain::COPYDATE_STRING, buffer, 17);
        status = DVDClose(&fileInfo);
    }
    return status;
}

/* 80006264-80006338       .text debug__Fv */
void debug() {
    if (mDoMain::developmentMode) {
        if (mCheckHeap) {
            CheckHeap(g_mDoCPd_gamePad[2]);
        }

        if (g_mDoCPd_gamePad[2]->testButton(~CButton::Z) == CButton::R && g_mDoCPd_gamePad[2]->testTrigger(CButton::Z))
            mDisplayHeapSize ^= 1;

        if (mDisplayHeapSize) {
            if (g_mDoCPd_gamePad[2]->testButton(~CButton::Z) == CButton::L && g_mDoCPd_gamePad[2]->testTrigger(CButton::Z))
                mHeapBriefType < 5 ? mHeapBriefType++ : mHeapBriefType = 1;

            debugDisplay();
        }

        Debug_console(g_mDoCPd_gamePad[2]);
    }
}

/* 80006338-80006464       .text main01__Fv */
void main01() {
    static u32 frame;

    // Setup heaps, setup exception manager, set RNG seed, setup DVDError Thread, setup Memory card
    // Thread
    mDoMch_Create();

    // setup FrameBuffer and ZBuffer, init display lists
    mDoGph_Create();

    // Setup control pad
    mDoCPd_Create();

    RootHeapCheck.setHeap((JKRExpHeap*)JKRHeap::getRootHeap());
    SystemHeapCheck.setHeap((JKRExpHeap*)JKRHeap::getSystemHeap());
    ZeldaHeapCheck.setHeap(mDoExt_getZeldaHeap());
    GameHeapCheck.setHeap(mDoExt_getGameHeap());
    ArchiveHeapCheck.setHeap(mDoExt_getArchiveHeap());
    CommandHeapCheck.setHeap(mDoExt_getCommandHeap());

    JUTConsole* console = JFWSystem::getSystemConsole();
    console->setOutput(mDoMain::developmentMode ? JUTConsole::OUTPUT_OSR_AND_CONSOLE :
                                                  JUTConsole::OUTPUT_NONE);
    console->setPosition(32, 42);

    mDoDvdThd_callback_c::create((mDoDvdThd_callback_func)LOAD_COPYDATE, NULL);
    fapGm_Create();  // init framework
#if VERSION == VERSION_JPN
    mDisplayHeapSize = 1;
#else
    mDisplayHeapSize = 0;
#endif
    cDyl_InitAsync();  // init RELs

    g_mDoAud_audioHeap = JKRSolidHeap::create(0x166800, JKRHeap::getCurrentHeap(), false);

    do {
        frame++;
        if (fillcheck_check_frame != 0 && frame % fillcheck_check_frame == 0) {
            mDoMch_HeapCheckAll();
        }

        if (mDoDvdThd::SyncWidthSound) {
            g_mDoMemCd_control.update();
        }

        mDoCPd_Read();     // read controller input
        mDoAud_Execute();  // handle audio execution
        fapGm_Execute();   // handle game execution
        debug();           // run debugger
    } while (true);
}

OSThread mainThread;

/* 80006464-800065DC       .text main */
void main() {
    OSThread* current_thread = OSGetCurrentThread();
    u8 ALIGN_DECL(0x20) stack[0xF000];

    mDoMain::sPowerOnTime = OSGetTime();
    OSReportInit();
    version_check();
#if VERSION != VERSION_JPN
    mDoRstData* reset_data = (mDoRstData*)OSAllocFromArenaLo(0x10, 4);
    mDoRst::setResetData(reset_data);

    if (!mDoRst::getResetData()) {
        do {
        } while (true);
    }

    if (OSGetResetCode() == 0) {
        mDoRst::offReset();
        mDoRst::offResetPrepare();
        mDoRst::off3ButtonReset();
        mDoRst::set3ButtonResetPort(-1);
    }

    g_dComIfG_gameInfo.ct();
#endif

    if (mDoMain::developmentMode < 0) {
        DVDDiskID* disk_id = DVDGetCurrentDiskID();

        if (disk_id->game_version > 0x90) {
            mDoMain::developmentMode = 1;
        } else if (disk_id->game_version > 0x80) {
            u32 consoleType = OSGetConsoleType();
            mDoMain::developmentMode = (consoleType >> 0x1C) & 1;
        } else {
            mDoMain::developmentMode = 0;
        }
    }

    s32 priority = OSGetThreadPriority(current_thread);
    OSCreateThread(&mainThread, main01, 0, stack + sizeof(stack), sizeof(stack), priority, 0);
    OSResumeThread(&mainThread);
    OSSetThreadPriority(current_thread, 0x1F);
    OSSuspendThread(current_thread);
}
