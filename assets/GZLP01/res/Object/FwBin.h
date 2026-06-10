#ifndef RES_FWBIN_H
#define RES_FWBIN_H

enum dRes_INDEX_FWBIN {
    /* BDLM */
    dRes_INDEX_FWBIN_BDL_VBINW_F_e=0x4,
    /* BTK  */
    dRes_INDEX_FWBIN_BTK_VBINA_F_e=0x7,
};

enum dRes_ID_FWBIN {
    /* BDLM */
    dRes_ID_FWBIN_BDL_VBINW_F_e=0x4,
    /* BTK  */
    dRes_ID_FWBIN_BTK_VBINA_F_e=0x7,
};

enum VBINW_F_JNT {
    VBINW_F_JNT_V_BINRGB_e=0x0,
    VBINW_F_JNT_BIN_0_OUTSIDE_e=0x1,
    VBINW_F_JNT_BIN_1_CAP_MODEL_e=0x2,
    VBINW_F_JNT_BIN_2_INSIDE_e=0x3,
};

#endif /* !RES_FWBIN_H */