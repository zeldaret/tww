#ifndef RES_HHA_H
#define RES_HHA_H

#include "global.h" // IWYU pragma: keep

enum HHA_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    HHA_BCK_YGSTP00=0x6,
    
    /* BDLM */
    HHA_BDL_HHA1=0x9,
    HHA_BDL_HHA2=0xA,
    HHA_BDL_YGSTP00=0xB,
    HHA_BDL_YSWTR00=0xC,
    
    /* BTK */
    HHA_BTK_YGSTP00=0xF,
    HHA_BTK_YSWTR00_01=0x10,
    HHA_BTK_YSWTR00_02=0x11,
    
    /* DZB */
    HHA_DZB_HHA1=0x14,
    HHA_DZB_HHA2=0x15,
};

#endif /* RES_HHA_H */
