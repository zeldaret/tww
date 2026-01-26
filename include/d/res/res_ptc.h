#ifndef RES_PTC_H
#define RES_PTC_H

#include "global.h" // IWYU pragma: keep

enum PTC_RES_FILE_ID {
    /* BDL */
    PTC_BDL_PTCO=0x0,
    PTC_BDL_PTCU=0x1,
};

enum PTC_RES_FILE_INDEX {
    /* BDL */
    PTC_INDEX_BDL_PTCO=0x3,
    PTC_INDEX_BDL_PTCU=0x4,
};

#endif /* RES_PTC_H */
