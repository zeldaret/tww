#ifndef RES_JB_H
#define RES_JB_H

#include "global.h" // IWYU pragma: keep

enum JB_RES_FILE_ID {
    /* BCKS */
    JB_BCK_JB_APPEAR=0x0,
    JB_BCK_JB_WAIT01=0x1,
    JB_BCK_YJBSM00=0x4,
    
    /* BDLM */
    JB_BDL_JB=0x2,
    
    /* BRK */
    JB_BRK_JB_LAMP=0x3,
    JB_BRK_YJBSM00=0x5,
    JB_BRK_LF=0x8,
    
    /* BMDM */
    JB_BMD_YJBSM00=0x6,
    JB_BMD_LF=0x9,
    
    /* BTK */
    JB_BTK_YJBSM00=0x7,
};

enum JB_RES_FILE_INDEX {
    /* BCKS */
    JB_INDEX_BCK_JB_APPEAR=0x7,
    JB_INDEX_BCK_JB_WAIT01=0x8,
    JB_INDEX_BCK_YJBSM00=0x9,
    
    /* BDLM */
    JB_INDEX_BDL_JB=0xC,
    
    /* BRK */
    JB_INDEX_BRK_JB_LAMP=0xF,
    JB_INDEX_BRK_YJBSM00=0x10,
    JB_INDEX_BRK_LF=0x11,
    
    /* BMDM */
    JB_INDEX_BMD_YJBSM00=0x14,
    JB_INDEX_BMD_LF=0x15,
    
    /* BTK */
    JB_INDEX_BTK_YJBSM00=0x18,
};

#endif /* RES_JB_H */
