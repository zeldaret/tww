#ifndef RES_TABLE_H
#define RES_TABLE_H

enum dRes_INDEX_TABLE {
    /* BDL  */
    dRes_INDEX_TABLE_BDL_YTBLE_e=0x4,
    dRes_INDEX_TABLE_BDL_QCFIS_e=0x5,
    /* DZB  */
    dRes_INDEX_TABLE_DZB_QCFIS_e=0x8,
    dRes_INDEX_TABLE_DZB_YTBLE_e=0x9,
};

enum dRes_ID_TABLE {
    /* BDL  */
    dRes_ID_TABLE_BDL_YTBLE_e=0x4,
    dRes_ID_TABLE_BDL_QCFIS_e=0x5,
    /* DZB  */
    dRes_ID_TABLE_DZB_QCFIS_e=0x8,
    dRes_ID_TABLE_DZB_YTBLE_e=0x9,
};

enum YTBLE_JNT {
    YTBLE_JNT_Y_TUKUE_DISP_e=0x0,
    YTBLE_JNT_A00_e=0x1,
    YTBLE_JNT_TUKUE00_e=0x2,
};

enum QCFIS_JNT {
    QCFIS_JNT_Y_ISU_DISP_e=0x0,
    QCFIS_JNT_A00_e=0x1,
    QCFIS_JNT_ISU_e=0x2,
};

#endif /* !RES_TABLE_H */