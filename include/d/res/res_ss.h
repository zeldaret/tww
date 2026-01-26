#ifndef RES_SS_H
#define RES_SS_H

#include "global.h" // IWYU pragma: keep

enum SS_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    SS_BCK_CLOSE=0x4,
    SS_BCK_DAMAGE=0x5,
    SS_BCK_NO_DAMAGE=0x6,
    SS_BCK_OPEN=0x7,
    SS_BCK_WAIT_CLOSE=0x8,
    SS_BCK_WAIT_OPEN=0x9,
    
    /* BDL */
    SS_BDL_SW=0xC,
};

#endif /* RES_SS_H */
