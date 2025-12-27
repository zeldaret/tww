#ifndef RES_KS_H
#define RES_KS_H

#include "global.h" // IWYU pragma: keep

enum KS_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    KS_BAS_CLOSE=0x7,
    KS_BAS_MABATAKI=0x8,
    KS_BAS_OPEN=0x9,
    
    /* BCK */
    KS_BCK_MABATAKI=0xC,
    
    /* BDLM */
    KS_BDL_KS_BODY=0xF,
    KS_BDL_KS_EYE=0x10,
    
    /* BRK */
    KS_BRK_KS_BODY=0x13,
    KS_BRK_KS_EYE=0x14,
    
    /* BTK */
    KS_BTK_KS_EYE=0x17,
};

#endif /* RES_KS_H */
