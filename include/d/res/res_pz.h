#ifndef RES_PZ_H
#define RES_PZ_H

#include "global.h" // IWYU pragma: keep

enum PZ_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    PZ_BCK_ARROW_RELORD=0x7,
    PZ_BCK_ARROW_SHOOT=0x8,
    PZ_BCK_ARROW_WAIT03=0x9,
    PZ_BCK_DAM01=0xA,
    PZ_BCK_DAM02=0xB,
    PZ_BCK_DEFEND=0xC,
    PZ_BCK_RELORD=0xD,
    PZ_BCK_RUN01=0xE,
    PZ_BCK_SHOOT=0xF,
    PZ_BCK_STAND=0x10,
    PZ_BCK_WAIT01=0x11,
    PZ_BCK_WAIT02=0x12,
    PZ_BCK_WAIT03=0x13,
    PZ_BCK_WAIT04=0x14,
    
    /* BDLM */
    PZ_BDL_BOW=0x17,
    PZ_BDL_PZ=0x18,
    
    /* BRK */
    PZ_BRK_TRI_TEST=0x1B,
    
    /* BTK */
    PZ_BTK_BOW_WAIT=0x1E,
    PZ_BTK_MABA_A=0x1F,
    PZ_BTK_STAND=0x20,
    
    /* BTP */
    PZ_BTP_BOW_WAIT=0x23,
    PZ_BTP_DAM01=0x24,
    PZ_BTP_DAM02=0x25,
    PZ_BTP_DEFEND=0x26,
    PZ_BTP_MABA_A=0x27,
    PZ_BTP_MABA_B=0x28,
    PZ_BTP_STAND=0x29,
    PZ_BTP_TALK01=0x2A,
    PZ_BTP_TALK02=0x2B,
    PZ_BTP_WAIT04=0x2C,
};

#endif /* RES_PZ_H */
