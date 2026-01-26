#ifndef RES_AJ_H
#define RES_AJ_H

#include "global.h" // IWYU pragma: keep

enum AJ_RES_FILE_ID {
    /* BCKS */
    AJ_BCK_ANGRY=0x0,
    AJ_BCK_CALL=0x1,
    AJ_BCK_JAMP=0x2,
    AJ_BCK_LOOK=0x3,
    AJ_BCK_NOBI=0x4,
    AJ_BCK_SHOCK=0x5,
    AJ_BCK_TIRE=0x6,
    AJ_BCK_WAIT01=0x7,
    AJ_BCK_WAIT02=0x8,
    
    /* BDL */
    AJ_BDL_AJ_STICK=0x9,
    
    /* BDLM */
    AJ_BDL_AJ=0xA,
    
    /* BTP */
    AJ_BTP_MABA=0xB,
};

enum AJ_RES_FILE_INDEX {
    /* BCKS */
    AJ_INDEX_BCK_ANGRY=0x6,
    AJ_INDEX_BCK_CALL=0x7,
    AJ_INDEX_BCK_JAMP=0x8,
    AJ_INDEX_BCK_LOOK=0x9,
    AJ_INDEX_BCK_NOBI=0xA,
    AJ_INDEX_BCK_SHOCK=0xB,
    AJ_INDEX_BCK_TIRE=0xC,
    AJ_INDEX_BCK_WAIT01=0xD,
    AJ_INDEX_BCK_WAIT02=0xE,
    
    /* BDL */
    AJ_INDEX_BDL_AJ_STICK=0x11,
    
    /* BDLM */
    AJ_INDEX_BDL_AJ=0x14,
    
    /* BTP */
    AJ_INDEX_BTP_MABA=0x17,
};

#endif /* RES_AJ_H */
