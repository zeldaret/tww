#ifndef RES_TOUSEKI_H
#define RES_TOUSEKI_H

#include "global.h" // IWYU pragma: keep

enum TOUSEKI_RES_FILE_ID {
    /* BCK */
    TOUSEKI_BCK_ATOSK_MAKI=0x0,
    TOUSEKI_BCK_ATOSK_NAGE=0x1,
    
    /* BDL */
    TOUSEKI_BDL_ATOSK_A=0x3,
};

enum TOUSEKI_RES_FILE_INDEX {
    /* BCK */
    TOUSEKI_INDEX_BCK_ATOSK_MAKI=0x4,
    TOUSEKI_INDEX_BCK_ATOSK_NAGE=0x5,
    
    /* BDL */
    TOUSEKI_INDEX_BDL_ATOSK_A=0x8,
};

#endif /* RES_TOUSEKI_H */
