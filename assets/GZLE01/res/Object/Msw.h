#ifndef RES_MSW_H
#define RES_MSW_H

enum dRes_INDEX_MSW {
    /* BDL  */
    dRes_INDEX_MSW_BDL_MSWNG_e=0x4,
    dRes_INDEX_MSW_BDL_OBM_CHAIN1_e=0x5,
    /* DZB  */
    dRes_INDEX_MSW_DZB_BRIDGE_e=0x8,
    dRes_INDEX_MSW_DZB_MSWING_e=0x9,
    dRes_INDEX_MSW_DZB_OBM_BRIDGE2_e=0xA,
};

enum dRes_ID_MSW {
    /* BDL  */
    dRes_ID_MSW_BDL_MSWNG_e=0x4,
    dRes_ID_MSW_BDL_OBM_CHAIN1_e=0x5,
    /* DZB  */
    dRes_ID_MSW_DZB_BRIDGE_e=0x8,
    dRes_ID_MSW_DZB_MSWING_e=0x9,
    dRes_ID_MSW_DZB_OBM_BRIDGE2_e=0xA,
};

enum MSWNG_JNT {
    MSWNG_JNT_MSWNG_e=0x0,
};

enum OBM_CHAIN1_JNT {
    OBM_CHAIN1_JNT_OBM_CHAIN1_e=0x0,
};

#endif /* !RES_MSW_H */