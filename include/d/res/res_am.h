#ifndef RES_AM_H
#define RES_AM_H

#include "global.h" // IWYU pragma: keep

enum AM_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    AM_BAS_BOM_NOMI=0x5,
    AM_BAS_BOM_NOMI2=0x6,
    AM_BAS_CLOSE=0x7,
    AM_BAS_CLOSE_LOOP=0x8,
    AM_BAS_DAMAGE=0x9,
    AM_BAS_DAMAGE_END=0xA,
    AM_BAS_DAMAGE_LOOP=0xB,
    AM_BAS_DEAD=0xC,
    AM_BAS_OKIRU=0xD,
    AM_BAS_OPEN=0xE,
    AM_BAS_OPEN_LOOP=0xF,
    AM_BAS_SLEEP=0x10,
    AM_BAS_SLEEP_LOOP=0x11,
    
    /* BCK */
    AM_BCK_BOM_NOMI=0x14,
    AM_BCK_CLOSE=0x15,
    AM_BCK_CLOSE_LOOP=0x16,
    AM_BCK_DAMAGE=0x17,
    AM_BCK_DAMAGE_END=0x18,
    AM_BCK_DAMAGE_LOOP=0x19,
    AM_BCK_DEAD=0x1A,
    AM_BCK_OKIRU=0x1B,
    AM_BCK_OPEN=0x1C,
    AM_BCK_OPEN_LOOP=0x1D,
    AM_BCK_SLEEP=0x1E,
    AM_BCK_SLEEP_LOOP=0x1F,
    
    /* BDL */
    AM_BDL_AM=0x22,
};

#endif /* RES_AM_H */
