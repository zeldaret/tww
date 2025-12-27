#ifndef RES_TRND_H
#define RES_TRND_H

#include "global.h" // IWYU pragma: keep

enum TRND_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    TRND_BCK_YTRND00=0x6,
    TRND_BCK_YWUWT00=0x7,
    
    /* BDLM */
    TRND_BDL_YTRND00=0xA,
    TRND_BDL_YWUWT00=0xB,
    
    /* BRK */
    TRND_BRK_YTRND00=0xE,
    TRND_BRK_YWUWT00=0xF,
    
    /* BTK */
    TRND_BTK_YTRND00=0x12,
    TRND_BTK_YWUWT00=0x13,
};

#endif /* RES_TRND_H */
