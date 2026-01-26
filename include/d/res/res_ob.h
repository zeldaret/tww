#ifndef RES_OB_H
#define RES_OB_H

#include "global.h" // IWYU pragma: keep

enum OB_RES_FILE_ID {
    /* BCKS */
    OB_BCK_TALK=0x0,
    OB_BCK_THANK=0x1,
    OB_BCK_THANK02=0x2,
    OB_BCK_WAIT=0x3,
    OB_BCK_WALK=0x4,
    OB_BCK_LAUGH=0x8,
    OB_BCK_SHUTUP01=0x9,
    OB_BCK_SHUTUP02=0xA,
    
    /* BDL */
    OB_BDL_OB=0x5,
    
    /* BDLM */
    OB_BDL_OBA_HEAD=0x6,
    
    /* BTP */
    OB_BTP_MABA_A=0x7,
};

enum OB_RES_FILE_INDEX {
    /* BCKS */
    OB_INDEX_BCK_TALK=0x6,
    OB_INDEX_BCK_THANK=0x7,
    OB_INDEX_BCK_THANK02=0x8,
    OB_INDEX_BCK_WAIT=0x9,
    OB_INDEX_BCK_WALK=0xA,
    OB_INDEX_BCK_LAUGH=0xB,
    OB_INDEX_BCK_SHUTUP01=0xC,
    OB_INDEX_BCK_SHUTUP02=0xD,
    
    /* BDL */
    OB_INDEX_BDL_OB=0x10,
    
    /* BDLM */
    OB_INDEX_BDL_OBA_HEAD=0x13,
    
    /* BTP */
    OB_INDEX_BTP_MABA_A=0x16,
};

#endif /* RES_OB_H */
