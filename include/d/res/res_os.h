#ifndef RES_OS_H
#define RES_OS_H

#include "global.h" // IWYU pragma: keep

enum OS_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    OS_BCK_OS_AWAKE=0x5,
    OS_BCK_OS_MOVE01=0x6,
    
    /* BDLM */
    OS_BDL_OS=0x9,
    
    /* BRK */
    OS_BRK_LINK=0xC,
    OS_BRK_OS_AWAKE=0xD,
    OS_BRK_TENMETU=0xE,
    OS_BRK_TURN_OFF=0xF,
    OS_BRK_TURN_ON=0x10,
};

#endif /* RES_OS_H */
