#ifndef RES_UK_H
#define RES_UK_H

#include "global.h" // IWYU pragma: keep

enum UK_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    UK_BCK_UK_DA=0x7,
    UK_BCK_UK_JIDA01=0x8,
    UK_BCK_UK_JIDA02=0x9,
    UK_BCK_UK_JUMP=0xA,
    UK_BCK_UK_KEIKAI=0xB,
    UK_BCK_UK_LAND=0xC,
    UK_BCK_UK_RUN=0xD,
    UK_BCK_UK_TALK01=0xE,
    UK_BCK_UK_TALK02=0xF,
    UK_BCK_UK_WAIT=0x10,
    UK_BCK_UK_WALK=0x11,
    
    /* BDL */
    UK_BDL_UKHEAD_B=0x14,
    UK_BDL_UKHEAD_D=0x15,
    
    /* BDLM */
    UK_BDL_UK=0x18,
    UK_BDL_UKHEAD_C=0x19,
    
    /* BMT */
    UK_BMT_UK_C=0x1C,
    UK_BMT_UK_D=0x1D,
    
    /* BTP */
    UK_BTP_UK_MABA_C=0x20,
    UK_BAK_UK_MABA_C_BTP=0x21,
};

#endif /* RES_UK_H */
