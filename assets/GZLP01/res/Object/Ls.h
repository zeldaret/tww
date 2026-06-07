#ifndef RES_LS_H
#define RES_LS_H

enum dRes_INDEX_LS {
    /* BCKS */
    dRes_INDEX_LS_BCK_LS_DEMOLOOK_e=0x8,
    dRes_INDEX_LS_BCK_LS_DEMOWAIT_e=0x9,
    dRes_INDEX_LS_BCK_LS_FURIMUKI_e=0xA,
    dRes_INDEX_LS_BCK_LS_GET_e=0xB,
    dRes_INDEX_LS_BCK_LS_NOZOKU_e=0xC,
    dRes_INDEX_LS_BCK_LS_WAIT01_e=0xD,
    dRes_INDEX_LS_BCK_LS_WAIT02_e=0xE,
    dRes_INDEX_LS_BCK_LS_WAIT03_e=0xF,
    dRes_INDEX_LS_BCK_LS_WAIT04_e=0x10,
    dRes_INDEX_LS_BCK_LS_WAIT05_e=0x11,
    dRes_INDEX_LS_BCK_LS_WAIT06_e=0x12,
    dRes_INDEX_LS_BCK_LS_WATASU_e=0x13,
    dRes_INDEX_LS_BCK_LS_TALK01_e=0x14,
    dRes_INDEX_LS_BCK_LS_WAIT07_e=0x15,
    /* BDL  */
    dRes_INDEX_LS_BDL_LSHAND_e=0x18,
    /* BDLM */
    dRes_INDEX_LS_BDL_LS_e=0x1B,
    /* BTK  */
    dRes_INDEX_LS_BTK_LS_e=0x1E,
    dRes_INDEX_LS_BTK_LS_DEMOLOOK_e=0x1F,
    dRes_INDEX_LS_BTK_LS_DEMOWAIT_e=0x20,
    /* BTP  */
    dRes_INDEX_LS_BTP_FUAN_e=0x23,
    dRes_INDEX_LS_BTP_FUAN02_e=0x24,
    dRes_INDEX_LS_BTP_KIZUKU_e=0x25,
    dRes_INDEX_LS_BTP_LS_DEMOLOOK_e=0x26,
    dRes_INDEX_LS_BTP_LS_DEMOWAIT_e=0x27,
    dRes_INDEX_LS_BTP_LS_GET_e=0x28,
    dRes_INDEX_LS_BTP_MABA_e=0x29,
    dRes_INDEX_LS_BTP_NGWARAI_e=0x2A,
    dRes_INDEX_LS_BTP_NOZOKU_e=0x2B,
    dRes_INDEX_LS_BTP_OKORI_e=0x2C,
    dRes_INDEX_LS_BTP_WARAI_e=0x2D,
    /* TEX  */
    dRes_INDEX_LS_BTI_LSBODY02_e=0x30,
};

enum dRes_ID_LS {
    /* BCKS */
    dRes_ID_LS_BCK_LS_DEMOLOOK_e=0x0,
    dRes_ID_LS_BCK_LS_DEMOWAIT_e=0x1,
    dRes_ID_LS_BCK_LS_FURIMUKI_e=0x2,
    dRes_ID_LS_BCK_LS_GET_e=0x3,
    dRes_ID_LS_BCK_LS_NOZOKU_e=0x4,
    dRes_ID_LS_BCK_LS_WAIT01_e=0x5,
    dRes_ID_LS_BCK_LS_WAIT02_e=0x6,
    dRes_ID_LS_BCK_LS_WAIT03_e=0x7,
    dRes_ID_LS_BCK_LS_WAIT04_e=0x8,
    dRes_ID_LS_BCK_LS_WAIT05_e=0x9,
    dRes_ID_LS_BCK_LS_WAIT06_e=0xA,
    dRes_ID_LS_BCK_LS_WATASU_e=0xB,
    dRes_ID_LS_BCK_LS_TALK01_e=0x1E,
    dRes_ID_LS_BCK_LS_WAIT07_e=0x1F,
    /* BDL  */
    dRes_ID_LS_BDL_LSHAND_e=0xC,
    /* BDLM */
    dRes_ID_LS_BDL_LS_e=0xD,
    /* BTK  */
    dRes_ID_LS_BTK_LS_e=0xE,
    dRes_ID_LS_BTK_LS_DEMOLOOK_e=0xF,
    dRes_ID_LS_BTK_LS_DEMOWAIT_e=0x10,
    /* BTP  */
    dRes_ID_LS_BTP_FUAN_e=0x11,
    dRes_ID_LS_BTP_FUAN02_e=0x12,
    dRes_ID_LS_BTP_KIZUKU_e=0x13,
    dRes_ID_LS_BTP_LS_DEMOLOOK_e=0x14,
    dRes_ID_LS_BTP_LS_DEMOWAIT_e=0x15,
    dRes_ID_LS_BTP_LS_GET_e=0x16,
    dRes_ID_LS_BTP_MABA_e=0x17,
    dRes_ID_LS_BTP_NGWARAI_e=0x18,
    dRes_ID_LS_BTP_NOZOKU_e=0x19,
    dRes_ID_LS_BTP_OKORI_e=0x1A,
    dRes_ID_LS_BTP_WARAI_e=0x1B,
    /* TEX  */
    dRes_ID_LS_BTI_LSBODY02_e=0x1D,
};

enum LSHAND_JNT {
    LSHAND_JNT_WORLD_ROOT_e=0x0,
    LSHAND_JNT_LS_HANDL_e=0x1,
    LSHAND_JNT_LS_HANDR_e=0x2,
};

enum LS_JNT {
    LS_JNT_CENTER_e=0x0,
    LS_JNT_BACKBONE_e=0x1,
    LS_JNT_NECK_e=0x2,
    LS_JNT_HEAD_e=0x3,
    LS_JNT_HAIRL1_e=0x4,
    LS_JNT_HAIRL2_e=0x5,
    LS_JNT_HAIRR1_e=0x6,
    LS_JNT_HAIRR2_e=0x7,
    LS_JNT_SHOULDERL_e=0x8,
    LS_JNT_ARML1_e=0x9,
    LS_JNT_ARML2_e=0xA,
    LS_JNT_HANDL_e=0xB,
    LS_JNT_SHOULDERR_e=0xC,
    LS_JNT_ARMR1_e=0xD,
    LS_JNT_ARMR2_e=0xE,
    LS_JNT_HANDR_e=0xF,
    LS_JNT_WAIST_e=0x10,
    LS_JNT_LEGL1_e=0x11,
    LS_JNT_LEGL2_e=0x12,
    LS_JNT_FOOTL_e=0x13,
    LS_JNT_LEGR1_e=0x14,
    LS_JNT_LEGR2_e=0x15,
    LS_JNT_FOOTR_e=0x16,
    LS_JNT_SKIRTFL_e=0x17,
    LS_JNT_SKIRTFR_e=0x18,
    LS_JNT_SKIRTRL_e=0x19,
    LS_JNT_SKIRTRR_e=0x1A,
};

#endif /* !RES_LS_H */