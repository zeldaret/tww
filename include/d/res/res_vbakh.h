#ifndef RES_VBAKH_H
#define RES_VBAKH_H

#include "global.h" // IWYU pragma: keep

enum VBAKH_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    VBAKH_BCK_VBAHX=0x5,
    VBAKH_BCK_VBAKH=0x6,
    VBAKH_BCK_VBAKM=0x7,
    VBAKH_BCK_VBAMX=0x8,
    
    /* BDLM */
    VBAKH_BDL_VBAKH=0xB,
    VBAKH_BDL_VBAKM=0xC,
    
    /* BRK */
    VBAKH_BRK_VBAHX=0xF,
    VBAKH_BRK_VBAKM=0x10,
    VBAKH_BRK_VBAMX=0x11,
};

#endif /* RES_VBAKH_H */
