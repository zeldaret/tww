#ifndef RES_DOORBS_H
#define RES_DOORBS_H

enum dRes_INDEX_DOORBS {
    /* BDL  */
    dRes_INDEX_DOORBS_BDL_DOORDR_e=0x4,
    dRes_INDEX_DOORBS_BDL_DOORKD_e=0x5,
    /* DZB  */
    dRes_INDEX_DOORBS_DZB_DOOR20_D_e=0x8,
    dRes_INDEX_DOORBS_DZB_DOOR20_K_e=0x9,
};

enum dRes_ID_DOORBS {
    /* BDL  */
    dRes_ID_DOORBS_BDL_DOORDR_e=0x4,
    dRes_ID_DOORBS_BDL_DOORKD_e=0x5,
    /* DZB  */
    dRes_ID_DOORBS_DZB_DOOR20_D_e=0x8,
    dRes_ID_DOORBS_DZB_DOOR20_K_e=0x9,
};

enum DOORDR_JNT {
    DOORDR_JNT_DOOR20_DD_0_e=0x0,
};

enum DOORKD_JNT {
    DOORKD_JNT_DOOR20KD_e=0x0,
};

#endif /* !RES_DOORBS_H */