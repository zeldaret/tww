#ifndef RES_KN_H
#define RES_KN_H

#include "global.h" // IWYU pragma: keep

enum KN_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    KN_BCK_PATA=0x4,
    KN_BCK_WAIT01=0x5,
    KN_BCK_WAIT02=0x6,
    KN_BCK_WALK=0x7,
    
    /* BDL */
    KN_BDL_KN=0xA,
};

#endif /* RES_KN_H */
