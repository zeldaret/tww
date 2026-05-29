#ifndef RES_VYASI_H
#define RES_VYASI_H

enum dRes_INDEX_VYASI {
    /* BCK  */
    dRes_INDEX_VYASI_BCK_VYASI_e=0x4,
    /* BDL  */
    dRes_INDEX_VYASI_BDL_VYASI_e=0x7,
};

enum dRes_ID_VYASI {
    /* BCK  */
    dRes_ID_VYASI_BCK_VYASI_e=0x4,
    /* BDL  */
    dRes_ID_VYASI_BDL_VYASI_e=0x7,
};

enum VYASI_JNT {
    VYASI_JNT_MIKI_ROOT_e=0x0,
    VYASI_JNT_MIKI_2_e=0x1,
    VYASI_JNT_MIKI_3_e=0x2,
    VYASI_JNT_MIKI_4_e=0x3,
    VYASI_JNT_MIKI_5_e=0x4,
    VYASI_JNT_MIKI_E_e=0x5,
    VYASI_JNT_HA_A1_e=0x6,
    VYASI_JNT_HA_A3_e=0x7,
    VYASI_JNT_HA_B1_e=0x8,
    VYASI_JNT_HA_B3_e=0x9,
    VYASI_JNT_HA_C1_e=0xA,
    VYASI_JNT_HA_C3_e=0xB,
    VYASI_JNT_HA_D1_e=0xC,
    VYASI_JNT_HA_D3_e=0xD,
};

#endif /* !RES_VYASI_H */