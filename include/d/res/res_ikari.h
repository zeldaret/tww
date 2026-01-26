#ifndef RES_IKARI_H
#define RES_IKARI_H

#include "global.h" // IWYU pragma: keep

#if VERSION == VERSION_DEMO
enum IKARI_RES_FILE_ID { // IDs and indexes are synced
    /* BMD */
    IKARI_BMD_S_IKARI2=0x3,
    IKARI_BMD_S_IKARI3=0x4,
    IKARI_BMD_S_IKARI4=0x5,
};
#else
enum IKARI_RES_FILE_ID { // IDs and indexes are synced
    /* BDL */
    IKARI_BDL_S_IKARI2=0x3,
    IKARI_BDL_S_IKARI3=0x4,
    IKARI_BDL_S_IKARI4=0x5,
};
#endif

#endif /* RES_IKARI_H */
