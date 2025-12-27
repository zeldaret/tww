#ifndef RES_YW_H
#define RES_YW_H

#include "global.h" // IWYU pragma: keep

enum YW_RES_FILE_ID {
    /* BCKS */
    YW_BCK_WAIT01=0x0,
    YW_BCK_YW_TALK01=0x1,
    YW_BCK_YW_TTALK=0x2,
    YW_BCK_YW_TWAIT=0x3,
    YW_BCK_YW_TWALK=0x4,
    YW_BCK_YW_WAIT02=0x5,
    YW_BCK_YW_TALK02=0x9,
    
    /* BDL */
    YW_BDL_YW=0x6,
    
    /* BDLM */
    YW_BDL_YWHEAD01=0x7,
    
    /* BTP */
    YW_BTP_YWHEAD01=0x8,
};

enum YW_RES_FILE_INDEX {
    /* BCKS */
    YW_INDEX_BCK_WAIT01=0x6,
    YW_INDEX_BCK_YW_TALK01=0x7,
    YW_INDEX_BCK_YW_TTALK=0x8,
    YW_INDEX_BCK_YW_TWAIT=0x9,
    YW_INDEX_BCK_YW_TWALK=0xA,
    YW_INDEX_BCK_YW_WAIT02=0xB,
    YW_INDEX_BCK_YW_TALK02=0xC,
    
    /* BDL */
    YW_INDEX_BDL_YW=0xF,
    
    /* BDLM */
    YW_INDEX_BDL_YWHEAD01=0x12,
    
    /* BTP */
    YW_INDEX_BTP_YWHEAD01=0x15,
};

#endif /* RES_YW_H */
