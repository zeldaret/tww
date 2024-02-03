/**
 * m_Do_machine_exception.cpp
 * Exception Print Functions
 */

#include "m_Do/m_Do_machine_exception.h"
#include "DynamicLink.h"
#include "JSystem/JFramework/JFWSystem.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_main.h"

static JUTConsole* sConsole;

/* 8001BADC-8001BB68       .text print_f__FPCce */
void print_f(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    JUTConsole_print_f_va_(sConsole, fmt, args);
    va_end(args);
}

/* 8001BB68-8001BB90       .text print__FPCc */
void print(const char* string) {
    sConsole->print(string);
}

static const char* unused_803396f8 = "--------------------------------------\n";

/* 8001BB90-8001BCEC       .text dispHeapInfo__Fv */
void dispHeapInfo() {
    JKRExpHeap* zelda = zeldaHeap;
    JKRExpHeap* game = gameHeap;
    JKRExpHeap* archive = archiveHeap;

    u32 zeldaFree = zelda->getFreeSize();
    u32 gameFree = game->getFreeSize();
    u32 archiveFree = archive->getFreeSize();
    u32 zeldaTotal = zelda->getTotalFreeSize();
    u32 gameTotal = game->getTotalFreeSize();
    u32 archiveTotal = archive->getTotalFreeSize();

    print("-- Heap Free / TotalFree (KB) --\n");
    print_f("  Zelda %5d / %5d\n", zeldaFree / 1024, zeldaTotal / 1024);
    print_f("   Game %5d / %5d\n", gameFree / 1024, gameTotal / 1024);
    print_f("Archive %5d / %5d\n", archiveFree / 1024, archiveTotal / 1024);
    print("--------------------------------\n");

    if (JKRAram::getAramHeap()) {
        JKRAram::getAramHeap()->dump();
    }
    DynamicModuleControlBase::dump();
    dComIfG_dumpResControl();

    zelda->dump_sort();
    game->dump_sort();
    archive->dump_sort();
}

/* 8001BCEC-8001BD30       .text dispGameInfo__Fv */
void dispGameInfo() {
    print_f("Start StageName:RoomNo [%s:%d]\n", dComIfGp_getStartStageName(),
            dComIfGp_getStartStageRoomNo());
}

/* 8001BD30-8001BE84       .text dispDateInfo__Fv */
void dispDateInfo() {
    print("------------- Date Infomation ---------\n");
    print(" FINAL VERSION\n");
    print("COMPILE USER: FINAL\n");
    print_f("COPYDATE   : %17s\n", mDoMain::COPYDATE_STRING);

    OSCalendarTime time;
    OSTicksToCalendarTime(mDoMain::sPowerOnTime, &time);
    print_f("PowerOnTime: %04d/%2d/%2d %2d:%2d:%2d`%03d\"%03d\n", time.year, time.month,
            time.day_of_month, time.hours, time.minutes, time.seconds, time.milliseconds,
            time.microseconds);

    OSTicksToCalendarTime(mDoMain::sHungUpTime, &time);
    print_f("HungUpTime : %04d/%2d/%2d %2d:%2d:%2d`%03d\"%03d\n", time.year, time.month,
            time.day_of_month, time.hours, time.minutes, time.seconds, time.milliseconds,
            time.microseconds);

    OSTicksToCalendarTime(mDoMain::sHungUpTime - mDoMain::sPowerOnTime, &time);
    print_f("PlayTime   : %4d days, %2d:%2d:%2d`%03d\"%03d\n", time.year_day, time.hours,
            time.minutes, time.seconds, time.milliseconds, time.microseconds);
    print("---------------------------------------\n");
}

/* 8001BE84-8001BEAC       .text dispConsoleToTerminal__Fv */
void dispConsoleToTerminal() {
    JFWSystem::getSystemConsole()->dumpToTerminal(0xFFFFFFFF);
}

/* 8001BEAC-8001BEDC       .text exception_addition__FP10JUTConsole */
void exception_addition(JUTConsole* pConsole) {
    sConsole = pConsole;
    dispHeapInfo();
    dispDateInfo();
    dispConsoleToTerminal();
    dispGameInfo();
}
