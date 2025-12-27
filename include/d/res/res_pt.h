#ifndef RES_PT_H
#define RES_PT_H

#include "global.h" // IWYU pragma: keep

enum PT_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    PT_BCK_ATACK=0x6,
    PT_BCK_BWALK=0x7,
    PT_BCK_HAPPY=0x8,
    PT_BCK_JUMP=0x9,
    PT_BCK_KOKE=0xA,
    PT_BCK_SIRIMOTI=0xB,
    PT_BCK_WAIT=0xC,
    
    /* BDLM */
    PT_BDL_PT=0xF,
    
    /* BRK */
    PT_BRK_PT=0x12,
    
    /* BTP */
    PT_BTP_MABATAKI=0x15,
};

#endif /* RES_PT_H */
