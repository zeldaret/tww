#ifndef RES_VDS_H
#define RES_VDS_H

#include "global.h" // IWYU pragma: keep

enum VDS_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    VDS_BCK_VDSWT0=0x6,
    VDS_BCK_VDSWT1=0x7,
    
    /* BDLM */
    VDS_BDL_VDSWT0=0xA,
    VDS_BDL_VDSWT1=0xB,
    
    /* BRK */
    VDS_BRK_VDSWT0=0xE,
    VDS_BRK_VDSWT1=0xF,
    
    /* DZB */
    VDS_DZB_VDSWT=0x12,
};

#endif /* RES_VDS_H */
