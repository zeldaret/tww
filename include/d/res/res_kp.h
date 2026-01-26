#ifndef RES_KP_H
#define RES_KP_H

#include "global.h" // IWYU pragma: keep

enum KP_RES_FILE_ID {
    /* BCKS */
    KP_BCK_HAND=0x0,
    KP_BCK_HAPPY=0x1,
    KP_BCK_PRAY=0x2,
    KP_BCK_READ=0x3,
    KP_BCK_THINK=0x4,
    KP_BCK_WAIT01=0x5,
    
    /* BDL */
    KP_BDL_LT_01=0x6,
    KP_BDL_LT_02=0x7,
    
    /* BDLM */
    KP_BDL_KP=0x8,
    
    /* BTP */
    KP_BTP_MABA01=0x9,
};

enum KP_RES_FILE_INDEX {
    /* BCKS */
    KP_INDEX_BCK_HAND=0x6,
    KP_INDEX_BCK_HAPPY=0x7,
    KP_INDEX_BCK_PRAY=0x8,
    KP_INDEX_BCK_READ=0x9,
    KP_INDEX_BCK_THINK=0xA,
    KP_INDEX_BCK_WAIT01=0xB,
    
    /* BDL */
    KP_INDEX_BDL_LT_01=0xE,
    KP_INDEX_BDL_LT_02=0xF,
    
    /* BDLM */
    KP_INDEX_BDL_KP=0x12,
    
    /* BTP */
    KP_INDEX_BTP_MABA01=0x15,
};

#endif /* RES_KP_H */
