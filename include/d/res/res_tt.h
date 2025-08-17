#ifndef RES_TT_H
#define RES_TT_H

#include "global.h" // IWYU pragma: keep

enum TT_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    TT_BAS_POSE_CC=0x6,
    TT_BAS_POSE_ND=0x7,
    TT_BAS_POSE_NL=0x8,
    TT_BAS_POSE_NR=0x9,
    TT_BAS_STEP01=0xA,
    TT_BAS_TALK01=0xB,
    TT_BAS_TALK02=0xC,
    TT_BAS_TURN=0xD,
    TT_BAS_WAIT01=0xE,
    
    /* BCK */
    TT_BCK_POSE_CC=0x11,
    TT_BCK_POSE_ND=0x12,
    TT_BCK_POSE_NL=0x13,
    TT_BCK_POSE_NR=0x14,
    TT_BCK_STEP01=0x15,
    TT_BCK_TALK01=0x16,
    TT_BCK_TALK02=0x17,
    TT_BCK_TURN=0x18,
    TT_BCK_WAIT01=0x19,
    
    /* BDLM */
    TT_BDL_TT=0x1C,
    
    /* BTP */
    TT_BTP_MABA01=0x1F,
};

#endif /* RES_TT_H */
