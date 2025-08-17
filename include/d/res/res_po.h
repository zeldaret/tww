#ifndef RES_PO_H
#define RES_PO_H

#include "global.h" // IWYU pragma: keep

enum PO_RES_FILE_ID {
    /* BCKS */
    PO_BCK_WAIT01=0x0,
    PO_BCK_SPIT=0x4,
    PO_BCK_TALK01=0x5,
    PO_BCK_TALK02=0x6,
    PO_BCK_WALK01=0x7,
    
    /* BDLM */
    PO_BDL_PO=0x1,
    
    /* BTP */
    PO_BTP_MABA01=0x2,
    PO_BTP_MABA02=0x3,
};

enum PO_RES_FILE_INDEX {
    /* BCKS */
    PO_INDEX_BCK_WAIT01=0x5,
    PO_INDEX_BCK_SPIT=0x6,
    PO_INDEX_BCK_TALK01=0x7,
    PO_INDEX_BCK_TALK02=0x8,
    PO_INDEX_BCK_WALK01=0x9,
    
    /* BDLM */
    PO_INDEX_BDL_PO=0xC,
    
    /* BTP */
    PO_INDEX_BTP_MABA01=0xF,
    PO_INDEX_BTP_MABA02=0x10,
};

#endif /* RES_PO_H */
