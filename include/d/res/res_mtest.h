#ifndef RES_MTEST_H
#define RES_MTEST_H

#include "global.h" // IWYU pragma: keep

enum MTEST_RES_FILE_ID { // IDs and indexes are synced
    /* BMDC */
    MTEST_BMD_MCUBE=0x4,
    MTEST_BMD_MCYLN=0x5,
    
    /* DZB */
    MTEST_DZB_MCUBE=0x8,
    MTEST_DZB_MCUBEHG=0x9,
    MTEST_DZB_MCUBELK=0xA,
    MTEST_DZB_MCUBENC=0xB,
    MTEST_DZB_MCYLN=0xC,
    MTEST_DZB_MCYLNHG=0xD,
    MTEST_DZB_MCYLNNC=0xE,
    MTEST_DZB_MWTRSB=0xF,
    MTEST_DZB_MYGNSB=0x10,
};

#endif /* RES_MTEST_H */
