#ifndef RES_UO_H
#define RES_UO_H

enum dRes_INDEX_UO {
    /* BCKS */
    dRes_INDEX_UO_BCK_UO_BIKURI_e=0x7,
    dRes_INDEX_UO_BCK_UO_FURUE_e=0x8,
    dRes_INDEX_UO_BCK_UO_TALK01_e=0x9,
    dRes_INDEX_UO_BCK_UO_TALK02_e=0xA,
    dRes_INDEX_UO_BCK_UO_WAIT01_e=0xB,
    dRes_INDEX_UO_BCK_UO_WAIT02_e=0xC,
    dRes_INDEX_UO_BCK_UO_KYORO_e=0xD,
    dRes_INDEX_UO_BCK_UO_LETTER_e=0xE,
    dRes_INDEX_UO_BCK_UO_WALK_e=0xF,
    /* BDL  */
    dRes_INDEX_UO_BDL_UO_e=0x12,
    dRes_INDEX_UO_BDL_UO_LETTER_e=0x13,
    /* BDLM */
    dRes_INDEX_UO_BDL_UO01_HEAD_e=0x16,
    dRes_INDEX_UO_BDL_UO02_HEAD_e=0x17,
    dRes_INDEX_UO_BDL_UO03_HEAD_e=0x18,
    /* BMT  */
    dRes_INDEX_UO_BMT_UO02_e=0x1B,
    dRes_INDEX_UO_BMT_UO03_e=0x1C,
    /* BTP  */
    dRes_INDEX_UO_BTP_UO01_MABA_e=0x1F,
    dRes_INDEX_UO_BTP_UO02_MABA_e=0x20,
    dRes_INDEX_UO_BTP_UO03_MABA_e=0x21,
};

enum dRes_ID_UO {
    /* BCKS */
    dRes_ID_UO_BCK_UO_BIKURI_e=0x0,
    dRes_ID_UO_BCK_UO_FURUE_e=0x1,
    dRes_ID_UO_BCK_UO_TALK01_e=0x2,
    dRes_ID_UO_BCK_UO_TALK02_e=0x3,
    dRes_ID_UO_BCK_UO_WAIT01_e=0x4,
    dRes_ID_UO_BCK_UO_WAIT02_e=0x5,
    dRes_ID_UO_BCK_UO_KYORO_e=0x12,
    dRes_ID_UO_BCK_UO_LETTER_e=0x13,
    dRes_ID_UO_BCK_UO_WALK_e=0x14,
    /* BDL  */
    dRes_ID_UO_BDL_UO_e=0x6,
    dRes_ID_UO_BDL_UO_LETTER_e=0x15,
    /* BDLM */
    dRes_ID_UO_BDL_UO01_HEAD_e=0x7,
    dRes_ID_UO_BDL_UO02_HEAD_e=0x8,
    dRes_ID_UO_BDL_UO03_HEAD_e=0x9,
    /* BMT  */
    dRes_ID_UO_BMT_UO02_e=0xA,
    dRes_ID_UO_BMT_UO03_e=0xB,
    /* BTP  */
    dRes_ID_UO_BTP_UO01_MABA_e=0xC,
    dRes_ID_UO_BTP_UO02_MABA_e=0xD,
    dRes_ID_UO_BTP_UO03_MABA_e=0xE,
};

enum UO_JNT {
    UO_JNT_WORLD_ROOT_e=0x0,
    UO_JNT_BACKBONE_e=0x1,
    UO_JNT_NECK_e=0x2,
    UO_JNT_HEAD_e=0x3,
    UO_JNT_SHOULDERL_e=0x4,
    UO_JNT_ARML1_e=0x5,
    UO_JNT_ARML2_e=0x6,
    UO_JNT_HANDL_e=0x7,
    UO_JNT_SHOULDERR_e=0x8,
    UO_JNT_ARMR1_e=0x9,
    UO_JNT_ARMR2_e=0xA,
    UO_JNT_HANDR_e=0xB,
    UO_JNT_WAIST_e=0xC,
    UO_JNT_LEGL1_e=0xD,
    UO_JNT_LEGL2_e=0xE,
    UO_JNT_FOOTL_e=0xF,
    UO_JNT_LEGR1_e=0x10,
    UO_JNT_LEGR2_e=0x11,
    UO_JNT_FOOTR_e=0x12,
};

enum UO_LETTER_JNT {
    UO_LETTER_JNT_UO_LETTER_e=0x0,
};

enum UO01_HEAD_JNT {
    UO01_HEAD_JNT_UO01_HEAD_e=0x0,
};

enum UO02_HEAD_JNT {
    UO02_HEAD_JNT_UO02_HEAD_e=0x0,
};

enum UO03_HEAD_JNT {
    UO03_HEAD_JNT_UO03_HEAD_e=0x0,
};

#endif /* !RES_UO_H */