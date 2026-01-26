#ifndef RES_KANTERA_H
#define RES_KANTERA_H

#include "global.h" // IWYU pragma: keep

enum KANTERA_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    KANTERA_BCK_MO_KANTERA=0x6,
    
    /* BMD */
    KANTERA_BMD_GA=0x9,
    
    /* BMDM */
    KANTERA_BMD_LF=0xC,
    KANTERA_BMD_MK_KANTERA=0xD,
    
    /* BRK */
    KANTERA_BRK_LF=0x10,
    KANTERA_BRK_MK_KANTERA=0x11,
};

#endif /* RES_KANTERA_H */
