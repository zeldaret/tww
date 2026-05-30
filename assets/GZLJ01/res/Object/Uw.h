#ifndef RES_UW_H
#define RES_UW_H

enum dRes_INDEX_UW {
    /* BCKS */
    dRes_INDEX_UW_BCK_UW_TALK01_e=0x7,
    dRes_INDEX_UW_BCK_UW_TALK02_e=0x8,
    dRes_INDEX_UW_BCK_UW_WAIT01_e=0x9,
    dRes_INDEX_UW_BCK_UW_WAIT02_e=0xA,
    dRes_INDEX_UW_BCK_UW_TALK03_e=0xB,
    dRes_INDEX_UW_BCK_UW_TALK04_e=0xC,
    dRes_INDEX_UW_BCK_UW_02HOKAN_e=0xD,
    dRes_INDEX_UW_BCK_UW_HAPPY_e=0xE,
    dRes_INDEX_UW_BCK_UW_MOJIMOJI_e=0xF,
    /* BDL  */
    dRes_INDEX_UW_BDL_UW_e=0x12,
    /* BDLM */
    dRes_INDEX_UW_BDL_UW01_HEAD_e=0x15,
    dRes_INDEX_UW_BDL_UW02_HEAD_e=0x16,
    /* BTP  */
    dRes_INDEX_UW_BTP_UW01_MABA_e=0x19,
    dRes_INDEX_UW_BTP_UW02_MABA_e=0x1A,
    /* BMT  */
    dRes_INDEX_UW_BMT_UW02_e=0x1D,
};

enum dRes_ID_UW {
    /* BCKS */
    dRes_ID_UW_BCK_UW_TALK01_e=0x4,
    dRes_ID_UW_BCK_UW_TALK02_e=0x5,
    dRes_ID_UW_BCK_UW_WAIT01_e=0x6,
    dRes_ID_UW_BCK_UW_WAIT02_e=0x7,
    dRes_ID_UW_BCK_UW_TALK03_e=0xB,
    dRes_ID_UW_BCK_UW_TALK04_e=0xC,
    dRes_ID_UW_BCK_UW_02HOKAN_e=0xD,
    dRes_ID_UW_BCK_UW_HAPPY_e=0xE,
    dRes_ID_UW_BCK_UW_MOJIMOJI_e=0xF,
    /* BDL  */
    dRes_ID_UW_BDL_UW_e=0x1,
    /* BDLM */
    dRes_ID_UW_BDL_UW01_HEAD_e=0x2,
    dRes_ID_UW_BDL_UW02_HEAD_e=0x8,
    /* BTP  */
    dRes_ID_UW_BTP_UW01_MABA_e=0x3,
    dRes_ID_UW_BTP_UW02_MABA_e=0x9,
    /* BMT  */
    dRes_ID_UW_BMT_UW02_e=0xA,
};

enum UW_JNT {
    UW_JNT_WORLD_ROOT_e=0x0,
    UW_JNT_BACKBONE_e=0x1,
    UW_JNT_NECK_e=0x2,
    UW_JNT_HEAD_e=0x3,
    UW_JNT_SHOULDERL_e=0x4,
    UW_JNT_ARML1_e=0x5,
    UW_JNT_ARML2_e=0x6,
    UW_JNT_HANDL_e=0x7,
    UW_JNT_SHOULDERR_e=0x8,
    UW_JNT_ARMR1_e=0x9,
    UW_JNT_ARMR2_e=0xA,
    UW_JNT_HANDR_e=0xB,
    UW_JNT_WAIST_e=0xC,
    UW_JNT_LEGL1_e=0xD,
    UW_JNT_LEGL2_e=0xE,
    UW_JNT_FOOTL_e=0xF,
    UW_JNT_LEGR1_e=0x10,
    UW_JNT_LEGR2_e=0x11,
    UW_JNT_FOOTR_e=0x12,
};

enum UW01_HEAD_JNT {
    UW01_HEAD_JNT_UW01_HEAD_e=0x0,
};

enum UW02_HEAD_JNT {
    UW02_HEAD_JNT_UW02_HEAD_e=0x0,
};

#endif /* !RES_UW_H */