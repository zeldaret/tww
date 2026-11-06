// Debug-only file. This file is known to have existed for TWW based on the debug maps.
// The contents of this are based on the TP debug build decomp and may or may not match the actual TWW debug build.

#include "JSystem/JSystem.h" // IWYU pragma: keep

#include "JSystem/JHostIO/JHIMccBuf.h"
#include "dolphin/hio.h"

s32 gExiChannel = -1;

JHIMccContext tContext_old;
JHIMccContext tContext_new;
bool initialized_;
u8 negotiate_;

BOOL JHIhioCallbackEnum(s32 type) {
    gExiChannel = type;
    return 0;
}

void JHIEnumDevices(s32*, u32*) {
    /* Nonmatching */
}

u32 JHIInitInterface() {
    /* Nonmatching */
    return 1;
}

bool JHINegotiateInterface(u32) {
    /* Nonmatching */
    return 0;
}

JHIMccContext JHIGetHiSpeedContext() {
    if (tContext_new.mp_reader == NULL) {
        tContext_new.mp_reader = new JHIMccBufReader(1, 0x18, 0x6000);
    }
    
    if (tContext_new.mp_writer == NULL) {
        tContext_new.mp_writer = new JHIMccBufWriter(1, 0x18, 0x6000);
    }

    return tContext_new;
}

JHIMccContext JHIGetLowSpeedContext() {
    if (tContext_old.mp_reader == NULL) {
        tContext_old.mp_reader = new JHIMccBufReader(1, 2, 0);
    }
    
    if (tContext_old.mp_writer == NULL) {
        tContext_old.mp_writer = new JHIMccBufWriter(1, 2, 0);
    }

    return tContext_old;
}

BOOL JHIInitMCC(JHIMccContext* pCtx, bool* param_1) {
    JHIGetHiSpeedContext();
    JHIGetLowSpeedContext();

    if (!JHIInitInterface()) {
        *pCtx = tContext_old;
        return FALSE;
    }

    initialized_ = JHINegotiateInterface(800);
    if (initialized_) {
        tContext_new.mp_reader->enablePort();
        tContext_new.mp_writer->enablePort();
        tContext_new.mp_reader->init();
        tContext_new.mp_writer->init();
    } else {
        tContext_old.mp_reader->enablePort();
        tContext_old.mp_writer->enablePort();
        tContext_old.mp_reader->init();
        tContext_old.mp_writer->init();
    }

    if (param_1 != NULL) {
        *param_1 = initialized_;
    }

    if (initialized_) {
        *pCtx = tContext_new;
    } else {
        *pCtx = tContext_old;
    }

    return TRUE;
}
