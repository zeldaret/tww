#ifndef RES_YCAGE_H
#define RES_YCAGE_H

#include "global.h" // IWYU pragma: keep

enum YCAGE_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    YCAGE_BCK_YHRBR00=0x7,
    
    /* BDLM */
    YCAGE_BDL_YCAGE00=0xA,
    YCAGE_BDL_YHRBR00=0xB,
    
    /* BRK */
    YCAGE_BRK_YCAGE00=0xE,
    YCAGE_BRK_YHRBR00=0xF,
    
    /* BTK */
    YCAGE_BTK_YCAGE00=0x12,
    YCAGE_BTK_YHRBR00=0x13,
    
    /* DZB */
    YCAGE_DZB_KEKKAI=0x16,
};

#endif /* RES_YCAGE_H */
