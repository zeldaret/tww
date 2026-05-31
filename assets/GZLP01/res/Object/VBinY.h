#ifndef RES_VBINY_H
#define RES_VBINY_H

enum dRes_INDEX_VBINY {
    /* BDLM */
    dRes_INDEX_VBINY_BDL_VBINY_e=0x4,
    /* BTK  */
    dRes_INDEX_VBINY_BTK_VBINA_Y_e=0x7,
};

enum dRes_ID_VBINY {
    /* BDLM */
    dRes_ID_VBINY_BDL_VBINY_e=0x4,
    /* BTK  */
    dRes_ID_VBINY_BTK_VBINA_Y_e=0x7,
};

enum VBINY_JNT {
    VBINY_JNT_V_BINY_e=0x0,
    VBINY_JNT_BIN_0_OUTSIDE_e=0x1,
    VBINY_JNT_BIN_1_YOSEI_e=0x2,
    VBINY_JNT_BIN_2_INSIDE_e=0x3,
};

#endif /* !RES_VBINY_H */