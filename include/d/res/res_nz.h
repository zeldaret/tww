#ifndef RES_NZ_H
#define RES_NZ_H

#include "global.h" // IWYU pragma: keep

enum NZ_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    NZ_BAS_NZ_ATTACK=0x7,
    NZ_BAS_NZ_BUTUKARU=0x8,
    NZ_BAS_NZ_DEAD=0x9,
    NZ_BAS_NZ_DEAD2=0xA,
    NZ_BAS_NZ_EAT=0xB,
    NZ_BAS_NZ_EAT2=0xC,
    NZ_BAS_NZ_KOKERU=0xD,
    NZ_BAS_NZ_KOKERU2=0xE,
    NZ_BAS_NZ_MOTU=0xF,
    NZ_BAS_NZ_RUN=0x10,
    NZ_BAS_NZ_RUN2=0x11,
    NZ_BAS_NZ_WAIT=0x12,
    
    /* BCK */
    NZ_BCK_NZ_ATTACK=0x15,
    NZ_BCK_NZ_ATTACK2=0x16,
    NZ_BCK_NZ_BUTUKARU=0x17,
    NZ_BCK_NZ_DEAD=0x18,
    NZ_BCK_NZ_DEAD2=0x19,
    NZ_BCK_NZ_EAT=0x1A,
    NZ_BCK_NZ_EAT2=0x1B,
    NZ_BCK_NZ_KOKERU=0x1C,
    NZ_BCK_NZ_KOKERU2=0x1D,
    NZ_BCK_NZ_MOTU=0x1E,
    NZ_BCK_NZ_RUN=0x1F,
    NZ_BCK_NZ_RUN2=0x20,
    NZ_BCK_NZ_TYAKKA1=0x21,
    NZ_BCK_NZ_TYAKKA2=0x22,
    NZ_BCK_NZ_WAIT=0x23,
    
    /* BDLM */
    NZ_BDL_NZ=0x26,
    
    /* BMT */
    NZ_BMT_BOM=0x29,
    NZ_BMT_NZ=0x2A,
    
    /* DAT */
    NZ_BTI_BOM_SIPPO=0x2D,
    NZ_BTI_SIPPO=0x2E,
};

#endif /* RES_NZ_H */
