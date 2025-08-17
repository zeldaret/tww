#ifndef RES_MK_H
#define RES_MK_H

#include "global.h" // IWYU pragma: keep

enum MK_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    MK_BCK_MK_DA=0x5,
    MK_BCK_MK_JIDA01=0x6,
    MK_BCK_MK_JIDA02=0x7,
    MK_BCK_MK_JUMP=0x8,
    MK_BCK_MK_KEIKAI=0x9,
    MK_BCK_MK_LAND=0xA,
    MK_BCK_MK_RUN=0xB,
    MK_BCK_MK_TALK01=0xC,
    MK_BCK_MK_TALK02=0xD,
    MK_BCK_MK_TIRABARE=0xE,
    MK_BCK_MK_WAIT=0xF,
    MK_BCK_MK_WALK=0x10,
    
    /* BDLM */
    MK_BDL_MK=0x13,
    
    /* BTP */
    MK_BTP_MK_MABA=0x16,
};

#endif /* RES_MK_H */
