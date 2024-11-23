#include "dolphin/os/OSTime.h"
#include "dolphin/os/OS.h"

#define OS_TIME_MONTH_MAX 12
#define OS_TIME_WEEK_DAY_MAX 7
#define OS_TIME_YEAR_DAY_MAX 365

#ifdef __MWERKS__
asm OSTime OSGetTime(void) {
    // clang-format off
	nofralloc

	mftbu r3
    mftb r4, 0x10C
    
    mftbu r5
    cmpw r3, r5
    bne OSGetTime
    
    blr
    // clang-format on
}
#endif

#ifdef __MWERKS__
asm OSTick OSGetTick(void) {
    // clang-format off
	nofralloc

	mftb r3, 0x10C
	blr
    // clang-format on
}
#endif

#define OS_SYSTEMTIME_BASE 0x30D8

OSTime __OSGetSystemTime(void) {
    BOOL enabled;
    OSTime* timeAdjustAddr = (OSTime*)(OS_BASE_CACHED + OS_SYSTEMTIME_BASE);
    OSTime result;

    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + OSGetTime();
    OSRestoreInterrupts(enabled);

    return result;
}

OSTime __OSTimeToSystemTime(OSTime time) {
    BOOL enabled;
    OSTime* timeAdjustAddr = (OSTime*)(OS_BASE_CACHED + OS_SYSTEMTIME_BASE);
    OSTime result;

    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + time;
    OSRestoreInterrupts(enabled);

    return result;
}

// End of each month in standard year
static s32 YearDays[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
};

// End of each month in leap year
static s32 LeapYearDays[] = {
    0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
};

static inline BOOL IsLeapYear(s32 year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static inline s32 GetYearDays(s32 year, s32 mon) {
    return (IsLeapYear(year) ? LeapYearDays : YearDays)[mon];
}

static inline s32 GetLeapDays(s32 year) {
    if (year < 1) {
        return 0;
    }
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

static void GetDates(s32 days, OSCalendarTime* cal) {
    s32 year;
    s32 totalDays;
    s32* p_days;
    s32 month;
    cal->week_day = (days + 6) % OS_TIME_WEEK_DAY_MAX;

    for (year = days / OS_TIME_YEAR_DAY_MAX;
         days < (totalDays = year * OS_TIME_YEAR_DAY_MAX + GetLeapDays(year));)
    {
        year--;
    }

    days -= totalDays;
    cal->year = year;
    cal->year_day = days;

    p_days = IsLeapYear(year) ? LeapYearDays : YearDays;
    month = OS_TIME_MONTH_MAX;
    while (days < p_days[--month]) {
        ;
    }
    cal->month = month;
    cal->day_of_month = days - p_days[month] + 1;
}

#define BIAS (2000 * 365 + (2000 + 3) / 4 - (2000 - 1) / 100 + (2000 - 1) / 400)

#pragma dont_inline on
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td) {
    int days;
    int secs;
    OSTime d;

    d = ticks % OSSecondsToTicks(1);
    if (d < 0) {
        d += OSSecondsToTicks(1);
    }
    td->microseconds = (int)(OSTicksToMicroseconds(d) % 1000);
    td->milliseconds = (int)(OSTicksToMilliseconds(d) % 1000);

    ticks -= d;
    days = (int)(OSTicksToSeconds(ticks) / 86400 + BIAS);
    secs = (int)(OSTicksToSeconds(ticks) % 86400);
    if (secs < 0) {
        days -= 1;
        secs += 24 * 60 * 60;
    }

    GetDates(days, td);

    td->hours = secs / 60 / 60;
    td->minutes = (secs / 60) % 60;
    td->seconds = secs % 60;
}
#pragma dont_inline reset
