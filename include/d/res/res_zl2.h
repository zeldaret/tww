#ifndef RES_ZL2_H
#define RES_ZL2_H

#include "global.h" // IWYU pragma: keep

enum ZL2_RES_FILE_ID {
    /* BCKS */
    ZL2_BCK_WAIT=0x0,
    
    /* BDLM */
    ZL2_BDL_ZL=0x1,
    
    /* BTK */
    ZL2_BTK_MABA_A=0x2,
    
    /* BTP */
    ZL2_BTP_MABA_A=0x3,
};

enum ZL2_RES_FILE_INDEX {
    /* BCKS */
    ZL2_INDEX_BCK_WAIT=0x6,
    
    /* BDLM */
    ZL2_INDEX_BDL_ZL=0x9,
    
    /* BTK */
    ZL2_INDEX_BTK_MABA_A=0xC,
    
    /* BTP */
    ZL2_INDEX_BTP_MABA_A=0xF,
};

#endif /* RES_ZL2_H */
