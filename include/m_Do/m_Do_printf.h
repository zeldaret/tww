#ifndef M_DO_M_DO_PRINTF_H
#define M_DO_M_DO_PRINTF_H

#include "stdarg.h"
#include "m_Do/m_Do_main.h"

extern "C" {
    void OSReportDisable();
    void OSReportEnable();
    void OSReportForceEnableOn();
    void OSReportForceEnableOff();
    void OSVReport(const char* format, va_list list);
    void OSReport(const char* fmt, ...);
    void OSReport_FatalError(const char* fmt, ...);
    void OSReport_Error(const char* fmt, ...);
    void OSReport_Warning(const char* fmt, ...);
    void OSPanic(const char* file, s32 line, const char* fmt, ...);
}

void OSReportInit();

extern u32 print_errors;

#endif /* M_DO_M_DO_PRINTF_H */
