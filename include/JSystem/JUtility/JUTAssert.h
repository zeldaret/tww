#ifndef JUTASSERT_H
#define JUTASSERT_H

#include "dolphin/types.h"
#include "dolphin/os/OS.h"

#define JUT_ASSERT(FILE, LINE, COND)                                                               \
    if (!(COND)) {                                                                                 \
        JUTAssertion::showAssert(JUTAssertion::getSDevice(), FILE, LINE, #COND);                   \
        OSPanic(FILE, LINE, "Halt");                                                               \
    }

#define JUT_PANIC(FILE, LINE, TEXT)                                                                \
    JUTAssertion::showAssert(JUTAssertion::getSDevice(), FILE, LINE, TEXT);                        \
    OSPanic(FILE, LINE, "Halt");

namespace JUTAssertion {
    u32 getSDevice();
    void showAssert(u32 device, const char * file, int line, const char * assertion);
    void create();
    u32 flush_subroutine();
    void flushMessage();
    void flushMessage_dbPrint();
    void setVisible(bool);
    void setMessageCount(int);
};

extern bool sAssertVisible;

#endif /* JUTASSERT_H */
