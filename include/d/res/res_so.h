#ifndef RES_SO_H
#define RES_SO_H

#include "global.h" // IWYU pragma: keep

enum SO_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    SO_BCK_SO_JUMP=0x5,
    SO_BCK_SO_SWIM01=0x6,
    SO_BCK_SO_TALK01=0x7,
    SO_BCK_SO_TALK02=0x8,
    SO_BCK_SO_WAIT01=0x9,
    
    /* BDLM */
    SO_BDL_SO=0xC,
    SO_BDL_SO_FUDE=0xD,
    
    /* BTP */
    SO_BTP_SO=0x10,
};

#endif /* RES_SO_H */
