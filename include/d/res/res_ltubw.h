#ifndef RES_LTUBW_H
#define RES_LTUBW_H

#include "global.h" // IWYU pragma: keep

enum LTUBW_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    LTUBW_BDL_ITUBW=0x6,
    LTUBW_BDL_ITUHU=0x7,
    
    /* BDLM */
    LTUBW_BDL_YWPFM00=0xA,
    
    /* BRK */
    LTUBW_BRK_YWPFM00=0xD,
    
    /* DZB */
    LTUBW_DZB_ITUBW=0x10,
    LTUBW_DZB_ITUHT=0x11,
    LTUBW_DZB_ITUSO=0x12,
};

#endif /* RES_LTUBW_H */
