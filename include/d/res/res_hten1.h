#ifndef RES_HTEN1_H
#define RES_HTEN1_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum HTEN1_RES_FILE_ID {
    /* DZB */
    HTEN1_DZB_HTEN1=0x1,
    
    /* BDL */
    HTEN1_BDL_HTEN1=0x2,
};

enum HTEN1_RES_FILE_INDEX {
    /* DZB */
    HTEN1_INDEX_DZB_HTEN1=0x4,
    
    /* BDL */
    HTEN1_INDEX_BDL_HTEN1=0x7,
};
#else
enum HTEN1_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    HTEN1_BDL_HTEN1=0x4,
    
    /* DZB */
    HTEN1_DZB_HTEN1=0x7,
};
#endif

#endif /* RES_HTEN1_H */
