#ifndef RES_KEY_H
#define RES_KEY_H

#include "global.h" // IWYU pragma: keep

enum KEY_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    KEY_BCK_VLOCB=0x4,
    KEY_BCK_VLOCN=0x5,
    
    /* BDLM */
    KEY_BDL_VLOCB=0x8,
    KEY_BDL_VLOCN=0x9,
};

#endif /* RES_KEY_H */
