#ifndef RES_TC_H
#define RES_TC_H

#include "global.h" // IWYU pragma: keep

enum TC_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    TC_BCK_DANCE01=0x6,
    TC_BCK_DANCE02=0x7,
    TC_BCK_GET=0x8,
    TC_BCK_GUARD=0x9,
    TC_BCK_HAPPY=0xA,
    TC_BCK_JAMP_A=0xB,
    TC_BCK_JAMP_B=0xC,
    TC_BCK_JAMP_C=0xD,
    TC_BCK_JTBT=0xE,
    TC_BCK_MAWASU=0xF,
    TC_BCK_TALK01=0x10,
    TC_BCK_TALK02=0x11,
    TC_BCK_WAIT01=0x12,
    TC_BCK_WAIT02=0x13,
    TC_BCK_WAIT03=0x14,
    TC_BCK_WAIT04=0x15,
    TC_BCK_WALK01=0x16,
    
    /* BDLM */
    TC_BDL_TC=0x19,
    
    /* BMT */
    TC_BMT_TCA=0x1C,
    TC_BMT_TCB=0x1D,
    TC_BMT_TCC=0x1E,
    
    /* BTP */
    TC_BTP_MABA01=0x21,
};

#endif /* RES_TC_H */
