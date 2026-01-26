#ifndef RES_TABLE_H
#define RES_TABLE_H

#include "global.h" // IWYU pragma: keep

enum TABLE_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    TABLE_BDL_YTBLE=0x4,
    TABLE_BDL_QCFIS=0x5,
    
    /* DZB */
    TABLE_DZB_QCFIS=0x8,
    TABLE_DZB_YTBLE=0x9,
};

#endif /* RES_TABLE_H */
