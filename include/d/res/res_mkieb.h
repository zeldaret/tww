#ifndef RES_MKIEB_H
#define RES_MKIEB_H

#include "global.h" // IWYU pragma: keep

enum MKIEB_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    MKIEB_BDL_MKIEB=0x6,
    
    /* BDLM */
    MKIEB_BDL_YLSMF00=0x9,
    
    /* BRK */
    MKIEB_BRK_YLSMF00=0xC,
    
    /* DZB */
    MKIEB_DZB_MKIEB=0xF,
};

#endif /* RES_MKIEB_H */
