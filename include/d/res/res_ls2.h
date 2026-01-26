#ifndef RES_LS2_H
#define RES_LS2_H

#include "global.h" // IWYU pragma: keep

enum LS2_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    LS2_BAS_LS_DEMOLOOK=0x6,
    LS2_BAS_LS_DEMOWAIT=0x7,
    
    /* BCK */
    LS2_BCK_LS_DEMOLOOK=0xA,
    LS2_BCK_LS_DEMOWAIT=0xB,
    
    /* BTK */
    LS2_BTK_LS_DEMOLOOK=0xE,
    LS2_BTK_LS_DEMOWAIT=0xF,
    
    /* BTP */
    LS2_BTP_LS_DEMOLOOK=0x12,
    LS2_BTP_LS_DEMOWAIT=0x13,
};

#endif /* RES_LS2_H */
