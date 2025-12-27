#ifndef RES_T_TREE_H
#define RES_T_TREE_H

#include "global.h" // IWYU pragma: keep

enum T_TREE_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    T_TREE_BCK_WAIT=0xB,
    T_TREE_BCK_WAIT01=0xC,
    T_TREE_BCK_WAITB=0xD,
    T_TREE_BCK_WALK=0xE,
    
    /* BDL */
    T_TREE_BDL_PO_TEST=0x11,
    
    /* BDLM */
    T_TREE_BDL_CL=0x14,
    T_TREE_BDL_MO=0x15,
    T_TREE_BDL_MO_LOFF_TOFF=0x16,
    T_TREE_BDL_MO_LON_TOFF=0x17,
    T_TREE_BDL_MO_LON_TON=0x18,
    T_TREE_BDL_PZ=0x19,
    
    /* BMDM */
    T_TREE_BMD_MO=0x1C,
    
    /* BMT */
    T_TREE_BMT_CLNOMALMAT=0x1F,
    
    /* BMTM */
    T_TREE_BMT_ICE=0x22,
    T_TREE_BMT_ICE_BOTH=0x23,
    T_TREE_BMT_ICE_GEN=0x24,
    T_TREE_BMT_ICE_KAN=0x25,
    T_TREE_BMT_ICE_MTX=0x26,
    T_TREE_BMT_ICE_NON=0x27,
    T_TREE_BMT_ICE_RES=0x28,
    T_TREE_BMT_ICE_TOON=0x29,
    T_TREE_BMT_MO_GREEN=0x2A,
    T_TREE_BMT_MO_NORMALT=0x2B,
    
    /* BRK */
    T_TREE_BRK_CLWARP=0x2E,
    
    /* BTK */
    T_TREE_BTK_CLWARP=0x31,
    T_TREE_BTK_ICE=0x32,
    T_TREE_BTK_ICE_KAN=0x33,
    T_TREE_BTK_ICE_RES=0x34,
    T_TREE_BTK_MABA_A=0x35,
    
    /* BTP */
    T_TREE_BTP_MABA_A=0x38,
    T_TREE_BTP_TMABATAKI=0x39,
};

#endif /* RES_T_TREE_H */
