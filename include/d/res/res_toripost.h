#ifndef RES_TORIPOST_H
#define RES_TORIPOST_H

#include "global.h" // IWYU pragma: keep

enum TORIPOST_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    TORIPOST_BCK_POST_GET=0x4,
    TORIPOST_BCK_POST_PUTOUT=0x5,
    TORIPOST_BCK_POST_WAIT=0x6,
    
    /* BDL */
    TORIPOST_BDL_VPOST=0x9,
};

#endif /* RES_TORIPOST_H */
