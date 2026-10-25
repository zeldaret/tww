// Debug-only file. This file is known to have existed for TWW based on the debug maps.
// The contents of this are based on the TP debug build decomp and may or may not match the actual TWW debug build.

#include "JSystem/JSystem.h" // IWYU pragma: keep

#include "JSystem/JHostIO/JHICommonMem.h"

JHIMemBuf* JHICommonMem::instance;

JHIMemBuf* JHICommonMem::Instance() {
    if (instance == NULL) {
        instance = new JHIMemBuf();
    }

    return instance;
}

JHIMemBuf::JHIMemBuf() {
    mp_buffer = NULL;
    create();
}
