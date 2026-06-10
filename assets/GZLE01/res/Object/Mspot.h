#ifndef RES_MSPOT_H
#define RES_MSPOT_H

enum dRes_INDEX_MSPOT {
    /* BDLM */
    dRes_INDEX_MSPOT_BDL_MSPOCN_e=0x4,
    dRes_INDEX_MSPOT_BDL_MSPOT_e=0x5,
    /* BTK  */
    dRes_INDEX_MSPOT_BTK_MSPOCN_e=0x8,
    dRes_INDEX_MSPOT_BTK_MSPOT_e=0x9,
};

enum dRes_ID_MSPOT {
    /* BDLM */
    dRes_ID_MSPOT_BDL_MSPOCN_e=0x4,
    dRes_ID_MSPOT_BDL_MSPOT_e=0x5,
    /* BTK  */
    dRes_ID_MSPOT_BTK_MSPOCN_e=0x8,
    dRes_ID_MSPOT_BTK_MSPOT_e=0x9,
};

enum MSPOCN_JNT {
    MSPOCN_JNT_MSPOCN_e=0x0,
    MSPOCN_JNT_HIKARITAG_e=0x1,
    MSPOCN_JNT_KOGEN_e=0x2,
};

enum MSPOT_JNT {
    MSPOT_JNT_MSPOT_e=0x0,
    MSPOT_JNT_HIKARITAG_e=0x1,
    MSPOT_JNT_KOGEN_e=0x2,
};

#endif /* !RES_MSPOT_H */