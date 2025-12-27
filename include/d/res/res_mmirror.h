#ifndef RES_MMIRROR_H
#define RES_MMIRROR_H

#include "global.h" // IWYU pragma: keep

enum MMIRROR_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    MMIRROR_BCK_MSUSW=0x6,
    
    /* BDLM */
    MMIRROR_BDL_MMRR=0x9,
    MMIRROR_BDL_MSUSW=0xA,
    MMIRROR_BDL_YSSMR00=0xB,
    
    /* BTK */
    MMIRROR_BTK_MMRR=0xE,
    MMIRROR_BTK_MSUSW=0xF,
    MMIRROR_BTK_YSSMR00=0x10,
    
    /* DZB */
    MMIRROR_DZB_MMRR=0x13,
    MMIRROR_DZB_MSUSW=0x14,
};

#endif /* RES_MMIRROR_H */
