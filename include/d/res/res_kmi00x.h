#ifndef RES_KMI00X_H
#define RES_KMI00X_H

#include "global.h" // IWYU pragma: keep

#if VERSION > VERSION_DEMO
enum KMI00X_RES_FILE_ID { // IDs and indexes are synced
    /* BDLM */
    KMI00X_BDL_KMI_00X=0x4,
    
    /* BRK */
    KMI00X_BRK_KMI_00X=0x7,
};
#endif

#endif /* RES_KMI00X_H */
