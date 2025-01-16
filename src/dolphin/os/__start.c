#include "stdlib.h"
#include "global.h"
#include "dolphin/os/OS.h"
#include "dolphin/os/__start.h"

void DBInit();

SECTION_INIT void __check_pad3(void) {
    if ((*(u16*)0x800030E4 & 0xEEF) == 0xEEF) {
        OSResetSystem(0, 0, 0);
    }
}

SECTION_INIT ASM void __start(void) {
    // clang-format off
    nofralloc

    bl __init_registers
    bl __init_hardware
    li r0, -1
    stwu r1, -8(r1)
    stw r0, 4(r1)
    stw r0, 0(r1)
    bl __init_data
    li r0, 0
    lis r6, 0x8000
    addi r6, r6, 0x0044
    stw r0, 0(r6)
    lis r6, 0x8000
    addi r6, r6, 0x00F4
    lwz r6, 0(r6)
    cmplwi r6, 0
    beq lbl_8000319C
    lwz r7, 0xc(r6)
    b lbl_800031BC

lbl_8000319C:
    lis r5, 0x8000
    addi r5, r5, 0x0034
    lwz r5, 0(r5)
    cmplwi r5, 0
    beq lbl_800031F8
    lis r7, 0x8000
    addi r7, r7, 0x30E8
    lwz r7, 0(r7)

lbl_800031BC:
    li r5, 0
    cmplwi r7, 2
    beq lbl_800031E8
    cmplwi r7, 3
    bne lbl_800031F8
    li r5, 1

lbl_800031E8:
    lis r6, InitMetroTRK@ha
    addi r6, r6, InitMetroTRK@l
    mtlr r6
    blrl 

lbl_800031F8:
    lis r6, 0x8000
    addi r6, r6, 0x00F4
    lwz r5, 0(r6)
    cmplwi r5, 0
    beq+ lbl_80003258
    lwz r6, 8(r5)
    cmplwi r6, 0
    beq+ lbl_80003258
    add r6, r5, r6
    lwz r14, 0(r6)
    cmplwi r14, 0
    beq lbl_80003258
    addi r15, r6, 4
    mtctr r14

lbl_80003230:
    addi r6, r6, 4
    lwz r7, 0(r6)
    add r7, r7, r5
    stw r7, 0(r6)
    bdnz lbl_80003230
    lis r5, 0x8000
    addi r5, r5, 0x0034
    rlwinm r7, r15, 0, 0, 0x1a
    stw r7, 0(r5)
    b lbl_80003260
    
lbl_80003258:
    li r14, 0
    li r15, 0
    
lbl_80003260:
    bl DBInit
    bl OSInit
    lis r4, 0x8000
    addi r4, r4, 0x30E6
    lhz r3, 0(r4)
    andi. r5, r3, 0x8000
    beq lbl_80003288
    andi. r3, r3, 0x7fff
    cmplwi r3, 1
    bne lbl_8000329C
    
lbl_80003288:
    bl __check_pad3
    
lbl_8000329C:
    bl __init_user
    mr r3, r14
    mr r4, r15
    bl main
    b exit
    // clang-format on
}

ASM static void __init_registers(void)
{
#ifdef __MWERKS__
    nofralloc
    lis r1,  _stack_addr@h
    ori r1, r1,  _stack_addr@l
    lis r2, _SDA2_BASE_@h
    ori r2, r2, _SDA2_BASE_@l
    lis r13, _SDA_BASE_@h
    ori r13, r13, _SDA_BASE_@l
    blr
#endif
}

inline static void __copy_rom_section(void* dst, const void* src, u32 size)
{
    if (size && (dst != src)) {
        memcpy(dst, src, size);
        __flush_cache(dst, size);
    }
}

inline static void __init_bss_section(void* dst, u32 size)
{
    if (size) {
        memset(dst, 0, size);
    }
}

void __init_data(void)
{
    __rom_copy_info* dci;
    __bss_init_info* bii;

    dci = _rom_copy_info;
    while (TRUE) {
        if (dci->size == 0)
            break;
        __copy_rom_section(dci->addr, dci->rom, dci->size);
        dci++;
    }

    bii = _bss_init_info;
    while (TRUE) {
        if (bii->size == 0)
            break;
        __init_bss_section(bii->addr, bii->size);
        bii++;
    }
}

ASM void __init_hardware() {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfmsr r0
    ori r0,r0,0x2000
    mtmsr r0
    mflr r31
    bl __OSPSInit
    bl __OSCacheInit
    mtlr r31
    blr
#endif // clang-format on
}

ASM void __flush_cache(void* addr, u32 size)
{
#ifdef __MWERKS__
    nofralloc
    lis r5, 0xFFFFFFF1@h
    ori r5, r5, 0xFFFFFFF1@l
    and r5, r5, r3
    subf r3, r5, r3
    add r4, r4, r3
loop:
    dcbst 0, r5
    sync
    icbi 0, r5
    addic r5, r5, 8
    addic. r4, r4, -8
    bge loop
    isync
    blr
#endif
}
