#ifndef RES_KT_H
#define RES_KT_H

#include "global.h" // IWYU pragma: keep

enum KT_RES_FILE_ID {
    /* BCK */
    KT_BCK_KT_ESA=0x8000,
    KT_BCK_KT_FLY=0x8001,
    KT_BCK_KT_KYORO=0x8002,
    KT_BCK_KT_WALK=0x8003,
    
    /* BMD */
    KT_BMD_KT_HANE=0x8000,
    KT_BMD_KT_MODEL=0x8001,
};

enum KT_RES_FILE_INDEX {
    /* BCK */
    KT_INDEX_BCK_KT_ESA=0x4,
    KT_INDEX_BCK_KT_FLY=0x5,
    KT_INDEX_BCK_KT_KYORO=0x6,
    KT_INDEX_BCK_KT_WALK=0x7,
    
    /* BMD */
    KT_INDEX_BMD_KT_HANE=0xA,
    KT_INDEX_BMD_KT_MODEL=0xB,
};

#endif /* RES_KT_H */
