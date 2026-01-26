#ifndef RES_MTRYB_H
#define RES_MTRYB_H

#include "global.h" // IWYU pragma: keep

enum MTRYB_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    MTRYB_BDL_MTRYB=0x6,
    
    /* BDLM */
    MTRYB_BDL_YTFBL00=0x9,
    
    /* BRK */
    MTRYB_BRK_YTFBL00_APP=0xC,
    MTRYB_BRK_YTFBL00_CMN=0xD,
    
    /* DZB */
    MTRYB_DZB_MTRYB=0x10,
};

#endif /* RES_MTRYB_H */
