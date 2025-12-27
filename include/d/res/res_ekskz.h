#ifndef RES_EKSKZ_H
#define RES_EKSKZ_H

#include "global.h" // IWYU pragma: keep

enum EKSKZ_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    EKSKZ_BCK_YOCWD00=0x8,
    
    /* BDL */
    EKSKZ_BDL_EKSKZ=0xB,
    
    /* BDLM */
    EKSKZ_BDL_YOCWD00=0xE,
    
    /* BRK */
    EKSKZ_BRK_YOCWD00=0x11,
    
    /* BTK */
    EKSKZ_BTK_YOCWD00=0x14,
    
    /* DZB */
    EKSKZ_DZB_EKSKZ=0x17,
};

#endif /* RES_EKSKZ_H */
