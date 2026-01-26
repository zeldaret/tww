#ifndef RES_BITA_H
#define RES_BITA_H

#include "global.h" // IWYU pragma: keep

enum BITA_RES_FILE_ID { // IDs and indexes are synced
    /* BDLM */
    BITA_BDL_EF_BTDITA0=0x5,
    BITA_BDL_EF_BTDITA1=0x6,
    BITA_BDL_MBIT1=0x7,
    BITA_BDL_MBIT2=0x8,
    
    /* BRK */
    BITA_BRK_EF_BTDITA0=0xB,
    BITA_BRK_EF_BTDITA1=0xC,
    
    /* DZB */
    BITA_DZB_MBIT1=0xF,
    BITA_DZB_MBIT2=0x10,
};

#endif /* RES_BITA_H */
