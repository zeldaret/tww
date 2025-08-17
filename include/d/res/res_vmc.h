#ifndef RES_VMC_H
#define RES_VMC_H

#include "global.h" // IWYU pragma: keep

enum VMC_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    VMC_BCK_VMCWG=0x6,
    VMC_BCK_VMCWH=0x7,
    
    /* BDL */
    VMC_BDL_VMCBS=0xA,
    
    /* BDLM */
    VMC_BDL_VMCWD=0xD,
    
    /* DZB */
    VMC_DZB_VMCBS=0x10,
    VMC_DZB_VMCWD=0x11,
};

#endif /* RES_VMC_H */
