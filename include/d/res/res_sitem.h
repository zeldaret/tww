#ifndef RES_SITEM_H
#define RES_SITEM_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum SITEM_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    SITEM_BDL_KMI_01=0x6,
    SITEM_BDL_KMI_02=0x7,
    
    /* BDLM */
    SITEM_BDL_KMI_00=0xA,
    
    /* BRK */
    SITEM_BRK_KMI_00=0xD,
    
    /* TEX */
    SITEM_BTI_SITEM=0x10,
};
#else
enum SITEM_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    SITEM_BDL_KMI_00=0x4,
    SITEM_BDL_KMI_01=0x5,
    SITEM_BDL_KMI_02=0x6,
    
    /* TEX */
    SITEM_BTI_SITEM=0x9,
};
#endif

#endif /* RES_SITEM_H */
