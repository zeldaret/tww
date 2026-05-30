#ifndef RES_MED_R_H
#define RES_MED_R_H

enum dRes_INDEX_MED_R {
    /* BDLM */
    dRes_INDEX_MED_R_BDL_VBINR_e=0x4,
    /* BTK  */
    dRes_INDEX_MED_R_BTK_VBINA_R_e=0x7,
};

enum dRes_ID_MED_R {
    /* BDLM */
    dRes_ID_MED_R_BDL_VBINR_e=0x4,
    /* BTK  */
    dRes_ID_MED_R_BTK_VBINA_R_e=0x7,
};

enum VBINR_JNT {
    VBINR_JNT_V_BINRGB_e=0x0,
    VBINR_JNT_BIN_0_OUTSIDE_e=0x1,
    VBINR_JNT_BIN_1_CAP_MODEL_e=0x2,
    VBINR_JNT_BIN_2_INSIDE_e=0x3,
};

#endif /* !RES_MED_R_H */