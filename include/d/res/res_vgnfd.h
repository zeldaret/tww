#ifndef RES_VGNFD_H
#define RES_VGNFD_H

#include "global.h" // IWYU pragma: keep

enum VGNFD_RES_FILE_ID { // IDs and indexes are synced
    /* BDLM */
    VGNFD_BDL_VGNFD0=0x6,
    VGNFD_BDL_VGNFD1=0x7,
    VGNFD_BDL_VGNFD2=0x8,
    VGNFD_BDL_VGNFD3=0x9,
    VGNFD_BDL_VGNFD4=0xA,
    VGNFD_BDL_VGNFD5=0xB,
    VGNFD_BDL_YGCBD00=0xC,
    
    /* BRK */
    VGNFD_BRK_VGNFD0=0xF,
    VGNFD_BRK_VGNFD1=0x10,
    VGNFD_BRK_VGNFD2=0x11,
    VGNFD_BRK_VGNFD3=0x12,
    VGNFD_BRK_VGNFD4=0x13,
    
    /* BTK */
    VGNFD_BTK_YGCBD00=0x16,
    
    /* DZB */
    VGNFD_DZB_VGNFD=0x19,
};

#endif /* RES_VGNFD_H */
