#include "dolphin/base/PPCArch.h"

#include "global.h"

ASM u32 PPCMfmsr() {
    nofralloc
    mfmsr r3
    blr    
}

ASM void PPCMtmsr(__REGISTER u32 newMSR) {
    nofralloc
    mtmsr newMSR
    blr
}

ASM u32 PPCMfhid0() {
    nofralloc
    mfspr r3, HID0
    blr
}

ASM void PPCMthid0(__REGISTER u32 newHID0) {
    nofralloc
    mtspr HID0, newHID0
    blr
}

ASM u32 PPCMfl2cr() {
    nofralloc
    mfspr r3, L2CR
    blr
}

ASM void PPCMtl2cr(__REGISTER u32 newL2cr) {
    nofralloc
    mtspr L2CR, newL2cr
    blr
}

ASM void PPCMtdec(__REGISTER u32 newDec) {
    nofralloc
    mtdec newDec
    blr
}

ASM void PPCSync() {
    nofralloc
    sc
    blr
}

ASM void PPCHalt() {
    nofralloc
    sync
loop:
    nop
    li r3, 0
    nop
    b loop
}

u32 PPCMffpscr() {
    union FpscrUnion m;

    asm {
        mffs fp31
        stfd fp31, m.f;
    }

    return m.u.fpscr; 
}

void PPCMtfpscr(__REGISTER u32 newFPSCR) {
    union FpscrUnion m;

    asm {
        li    r4, 0
        stw   r4, m.u.fpscr_pad;
        stw   newFPSCR, m.u.fpscr
        lfd   fp31, m.f
        mtfsf 0xff, fp31
    }
}

ASM u32 PPCMfhid2() {
    nofralloc
    mfspr r3, HID2
    blr
}

ASM void PPCMthid2(__REGISTER u32 newhid2) {
    nofralloc
    mtspr HID2, newhid2
    blr
}

ASM void PPCMtwpar(__REGISTER u32 newwpar) {
    nofralloc
    mtspr WPAR, newwpar
    blr
}

void PPCDisableSpeculation(void) {
    PPCMthid0(PPCMfhid0() | HID0_SPD);
}

ASM void PPCSetFpNonIEEEMode() {
	nofralloc
	mtfsb1 29
	blr
}
