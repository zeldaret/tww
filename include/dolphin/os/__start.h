#ifndef __START_H
#define __START_H

#include "global.h"
#include "dolphin/os/OSUtil.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

#define PAD3_BUTTON_ADDR        0x800030E4
#define OS_RESET_RESTART        0
#define FALSE                   0
#define TRUE                    1
#define EXCEPTIONMASK_ADDR      0x80000044
#define BOOTINFO2_ADDR          0x800000F4
#define OS_BI2_DEBUGFLAG_OFFSET 0xC
#define ARENAHI_ADDR            0x80000034
#define DEBUGFLAG_ADDR          0x800030E8
#define DVD_DEVICECODE_ADDR     0x800030E6
#define DOL_ADDR_LIMIT          0x80700000

extern void InitMetroTRK();

u16 Pad3Button AT_ADDRESS(PAD3_BUTTON_ADDR);

extern int main(int argc, char* argv[]);
extern void exit(int);
extern void __init_user(void);
extern void InitMetroTRK_BBA(void);
extern void OSInit(void);
extern void OSResetSystem(BOOL reset, u32 resetCode, BOOL forceMenu);

SECTION_INIT extern void __check_pad3(void);
SECTION_INIT extern void __set_debug_bba(void);
SECTION_INIT extern u8 __get_debug_bba(void);
SECTION_INIT extern void __start(void);
SECTION_INIT extern void __init_registers(void);
SECTION_INIT extern void __init_data(void);
SECTION_INIT extern void __init_hardware(void);
SECTION_INIT extern void __flush_cache(void* addr, u32 size);

SECTION_INIT extern u8 _stack_addr[];
SECTION_INIT extern char _SDA_BASE_[];
SECTION_INIT extern char _SDA2_BASE_[];

typedef struct __rom_copy_info {
    char* rom;
    char* addr;
    uint size;
} __rom_copy_info;

SECTION_INIT extern __rom_copy_info _rom_copy_info[];

typedef struct __bss_init_info {
    char* addr;
    uint size;
} __bss_init_info;

SECTION_INIT extern __bss_init_info _bss_init_info[];

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif /* __START_H */
