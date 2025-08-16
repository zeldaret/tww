#ifndef RES_PF_H
#define RES_PF_H

#include "global.h" // IWYU pragma: keep

enum PF_RES_FILE_ID {
    /* BCKS */
    PF_BCK_CRY=0x0,
    PF_BCK_REGRET=0x1,
    PF_BCK_SPIT=0x2,
    PF_BCK_TALK01=0x3,
    PF_BCK_WAIT01=0x4,
    PF_BCK_WALK01=0x5,
    PF_BCK_WALK02=0x6,
    PF_BCK_WISH=0x7,
    
    /* BDLM */
    PF_BDL_PF=0x8,
    
    /* BTP */
    PF_BTP_MABA01=0x9,
};

enum PF_RES_FILE_INDEX {
    /* BCKS */
    PF_INDEX_BCK_CRY=0x5,
    PF_INDEX_BCK_REGRET=0x6,
    PF_INDEX_BCK_SPIT=0x7,
    PF_INDEX_BCK_TALK01=0x8,
    PF_INDEX_BCK_WAIT01=0x9,
    PF_INDEX_BCK_WALK01=0xA,
    PF_INDEX_BCK_WALK02=0xB,
    PF_INDEX_BCK_WISH=0xC,
    
    /* BDLM */
    PF_INDEX_BDL_PF=0xF,
    
    /* BTP */
    PF_INDEX_BTP_MABA01=0x12,
};

#endif /* RES_PF_H */
