#ifndef JUTASSERT_H
#define JUTASSERT_H

#include "dolphin/types.h"
#include "dolphin/os/OS.h"

#define JUT_ASSERT(LINE, COND)                                                                     \
    if ((COND) == 0) {                                                                             \
        JUTAssertion::showAssert(JUTAssertion::getSDevice(), __FILE__, LINE, #COND);               \
        OSPanic(__FILE__, LINE, "Halt");                                                           \
    }

#define JUT_WARN(LINE, ...)                                                                        \
    JUTAssertion::setWarningMessage_f(JUTAssertion::getSDevice(), __FILE__, LINE, __VA_ARGS__);    \

#define JUT_CONFIRM(LINE, COND)                                                                    \
    JUTAssertion::setConfirmMessage(JUTAssertion::getSDevice(), __FILE__, LINE, COND, #COND)

namespace JUTAssertion {
    u32 getSDevice();
    void showAssert(u32 device, const char * file, int line, const char * assertion);
    void setWarningMessage_f(u32 device, char * file, int line, const char * fmt, ...);
    void setConfirmMessage(u32 device, char * file, int line, bool cond, const char * msg);
    void create();
    u32 flush_subroutine();
    void flushMessage();
    void flushMessage_dbPrint();
    void setVisible(bool);
    void setMessageCount(int);
};

extern bool sAssertVisible;

#endif /* JUTASSERT_H */
