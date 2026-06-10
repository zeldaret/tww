#ifndef RES_PBCO_H
#define RES_PBCO_H

enum dRes_INDEX_PBCO {
    /* BDL  */
    dRes_INDEX_PBCO_BDL_PBCO_e=0x4,
    dRes_INDEX_PBCO_BDL_PBC2_e=0x5,
    /* DZB  */
    dRes_INDEX_PBCO_DZB_PBCO_e=0x8,
};

enum dRes_ID_PBCO {
    /* BDL  */
    dRes_ID_PBCO_BDL_PBCO_e=0x0,
    dRes_ID_PBCO_BDL_PBC2_e=0x2,
    /* DZB  */
    dRes_ID_PBCO_DZB_PBCO_e=0x3,
};

enum PBCO_JNT {
    PBCO_JNT_COUNTER_HUTA_e=0x0,
};

enum PBC2_JNT {
    PBC2_JNT_PBC2_e=0x0,
};

#endif /* !RES_PBCO_H */