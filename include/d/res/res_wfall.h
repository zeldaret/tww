#ifndef RES_WFALL_H
#define RES_WFALL_H

#include "global.h" // IWYU pragma: keep

enum WFALL_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    WFALL_BDL_HSUI1=0x7,
    
    /* BDLM */
    WFALL_BDL_YSMNM00=0xA,
    WFALL_BDL_YSWTR00=0xB,
    
    /* BRK */
    WFALL_BRK_YSMNM00=0xE,
    
    /* BTK */
    WFALL_BTK_YSMNM00=0x11,
    WFALL_BTK_YSWTR00=0x12,
    
    /* DZB */
    WFALL_DZB_HSUI1=0x15,
};

#endif /* RES_WFALL_H */
