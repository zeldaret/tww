#ifndef RES_GM_H
#define RES_GM_H

#include "global.h" // IWYU pragma: keep

enum GM_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    GM_BAS_ATACK02=0x6,
    GM_BAS_G_ATACK03=0x7,
    GM_BAS_G_HANE=0x8,
    
    /* BCK */
    GM_BCK_ATACK01=0xB,
    GM_BCK_ATACK02=0xC,
    GM_BCK_FLY=0xD,
    GM_BCK_G_ATACK01=0xE,
    GM_BCK_G_ATACK02=0xF,
    GM_BCK_G_ATACK03=0x10,
    GM_BCK_G_CHAKUCHI=0x11,
    GM_BCK_G_DAMAGE=0x12,
    GM_BCK_G_DEAD01=0x13,
    GM_BCK_G_DEAD02=0x14,
    GM_BCK_G_HAMMER=0x15,
    GM_BCK_G_HANE=0x16,
    GM_BCK_G_MACHINGUN=0x17,
    GM_BCK_G_UCHIWA=0x18,
    GM_BCK_G_WAIT=0x19,
    GM_BCK_G_WALK=0x1A,
    GM_BCK_JETATACK=0x1B,
    GM_BCK_PAUSE=0x1C,
    GM_BCK_TOMARU=0x1D,
    GM_BCK_UMINIGE=0x1E,
    
    /* BDLM */
    GM_BDL_GM=0x21,
    GM_BDL_HANESL=0x22,
    GM_BDL_HANEUL=0x23,
    
    /* BRK */
    GM_BRK_ATACK=0x26,
    GM_BRK_DAMAGE=0x27,
    GM_BRK_DEAD=0x28,
    GM_BRK_GM=0x29,
};

#endif /* RES_GM_H */
