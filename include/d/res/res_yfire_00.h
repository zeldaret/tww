#ifndef RES_YFIRE_00_H
#define RES_YFIRE_00_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum YFIRE_00_RES_FILE_ID { // IDs and indexes are synced
    /* BMDM */
    YFIRE_00_BMD_YFIRB_00=0x5,
    YFIRE_00_BMD_YFIRE_00=0x6,
    
    /* BTK */
    YFIRE_00_BTK_YFIRB_00=0x9,
    YFIRE_00_BTK_YFIRE_00=0xA,
    
    /* BRK */
    YFIRE_00_BRK_YFIRE_00=0xD,
};
#else
enum YFIRE_00_RES_FILE_ID { // IDs and indexes are synced
    /* BMDM */
    YFIRE_00_BMD_YFIRB_00=0x5,
    YFIRE_00_BMD_YFIRE_00=0x6,
    
    /* BRK */
    YFIRE_00_BRK_YFIRE_00=0x9,
    
    /* BTK */
    YFIRE_00_BTK_YFIRB_00=0xC,
    YFIRE_00_BTK_YFIRE_00=0xD,
};
#endif

#endif /* RES_YFIRE_00_H */
