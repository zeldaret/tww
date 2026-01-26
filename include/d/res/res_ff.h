#ifndef RES_FF_H
#define RES_FF_H

#include "global.h" // IWYU pragma: keep

enum FF_RES_FILE_ID { // IDs and indexes are synced
    /* BMD */
    FF_BMD_FF=0x4,
    FF_BMD_HO=0x5,
    FF_BMD_HOP=0x6,
    FF_BMD_HOP2=0x7,
    FF_BMD_HOP_TEST=0x8,
    FF_BMD_LONG=0x9,
    
    /* BRK */
    FF_BRK_HO=0xC,
    FF_BRK_HOP=0xD,
};

#endif /* RES_FF_H */
