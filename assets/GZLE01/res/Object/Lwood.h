#ifndef RES_LWOOD_H
#define RES_LWOOD_H

enum dRes_INDEX_LWOOD {
    /* BDL  */
    dRes_INDEX_LWOOD_BDL_ALWD_e=0x4,
    /* DZB  */
    dRes_INDEX_LWOOD_DZB_ALWD_e=0x7,
};

enum dRes_ID_LWOOD {
    /* BDL  */
    dRes_ID_LWOOD_BDL_ALWD_e=0x4,
    /* DZB  */
    dRes_ID_LWOOD_DZB_ALWD_e=0x7,
};

enum ALWD_JNT {
    ALWD_JNT_ALWD_e=0x0,
    ALWD_JNT_ALWD1_e=0x1,
    ALWD_JNT_J_ALWD_MIKI_e=0x2,
    ALWD_JNT_J_ALWD_HA_e=0x3,
    ALWD_JNT_JOINT3_e=0x4,
};

#endif /* !RES_LWOOD_H */