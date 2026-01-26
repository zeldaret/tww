#ifndef RES_VMR_H
#define RES_VMR_H

#include "global.h" // IWYU pragma: keep

enum VMR_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    VMR_BCK_VMRMZ=0x5,
    VMR_BCK_VMRTY=0x6,
    
    /* BDLM */
    VMR_BDL_VMRTO=0x9,
    VMR_BDL_VMRTY=0xA,
    
    /* BRK */
    VMR_BRK_VMRMZ=0xD,
};

#endif /* RES_VMR_H */
