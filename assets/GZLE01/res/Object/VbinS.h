#ifndef RES_VBINS_H
#define RES_VBINS_H

enum dRes_INDEX_VBINS {
    /* BDLM */
    dRes_INDEX_VBINS_BDL_VBINS_e=0x4,
    /* BTK  */
    dRes_INDEX_VBINS_BTK_VBINA_S_e=0x7,
};

enum dRes_ID_VBINS {
    /* BDLM */
    dRes_ID_VBINS_BDL_VBINS_e=0x4,
    /* BTK  */
    dRes_ID_VBINS_BTK_VBINA_S_e=0x7,
};

enum VBINS_JNT {
    VBINS_JNT_V_BINS_e=0x0,
    VBINS_JNT_BIN_0_OUTSIDE_e=0x1,
    VBINS_JNT_BIN_1_CAP_MODEL_e=0x2,
    VBINS_JNT_BIN_2_INSIDE_e=0x3,
};

#endif /* !RES_VBINS_H */