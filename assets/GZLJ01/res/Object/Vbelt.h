#ifndef RES_VBELT_H
#define RES_VBELT_H

enum dRes_INDEX_VBELT {
    /* BDLM */
    dRes_INDEX_VBELT_BDL_VBELT_e=0x4,
    /* BTK  */
    dRes_INDEX_VBELT_BTK_VBELT_e=0x7,
};

enum dRes_ID_VBELT {
    /* BDLM */
    dRes_ID_VBELT_BDL_VBELT_e=0x4,
    /* BTK  */
    dRes_ID_VBELT_BTK_VBELT_e=0x7,
};

enum VBELT_JNT {
    VBELT_JNT_ROOT_VBELT_e=0x0,
    VBELT_JNT_VBELT_MODEL_e=0x1,
};

#endif /* !RES_VBELT_H */