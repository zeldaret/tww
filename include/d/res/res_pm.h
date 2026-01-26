#ifndef RES_PM_H
#define RES_PM_H

#include "global.h" // IWYU pragma: keep

enum PM_RES_FILE_ID {
    /* BAS */
    PM_BAS_FIND=0x0,
    PM_BAS_TALK01=0x1,
    PM_BAS_WAIT01=0x2,
    
    /* BCK */
    PM_BCK_FIND=0x3,
    PM_BCK_TALK01=0x4,
    PM_BCK_WAIT01=0x5,
    
    /* BDLM */
    PM_BDL_PM=0x6,
    
    /* BTP */
    PM_BTP_MABA01=0x7,
};

enum PM_RES_FILE_INDEX {
    /* BAS */
    PM_INDEX_BAS_FIND=0x6,
    PM_INDEX_BAS_TALK01=0x7,
    PM_INDEX_BAS_WAIT01=0x8,
    
    /* BCK */
    PM_INDEX_BCK_FIND=0xB,
    PM_INDEX_BCK_TALK01=0xC,
    PM_INDEX_BCK_WAIT01=0xD,
    
    /* BDLM */
    PM_INDEX_BDL_PM=0x10,
    
    /* BTP */
    PM_INDEX_BTP_MABA01=0x13,
};

#endif /* RES_PM_H */
