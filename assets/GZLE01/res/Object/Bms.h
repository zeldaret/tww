#ifndef RES_BMS_H
#define RES_BMS_H

enum dRes_INDEX_BMS {
    /* BMDM */
    dRes_INDEX_BMS_BMD_SHOP_CURSOR01_e=0x8,
    /* BRK  */
    dRes_INDEX_BMS_BRK_SHOP_CURSOR01_e=0xB,
    /* BTP  */
    dRes_INDEX_BMS_BTP_BY_T01_e=0xE,
    dRes_INDEX_BMS_BTP_MABA01_e=0xF,
    /* BCKS */
    dRes_INDEX_BMS_BCK_BY2_WAIT00_e=0x12,
    dRes_INDEX_BMS_BCK_BY1_WAIT01_e=0x13,
    dRes_INDEX_BMS_BCK_BY1_WAIT02_e=0x14,
    dRes_INDEX_BMS_BCK_BY1_BOW_e=0x15,
    dRes_INDEX_BMS_BCK_BY1_TALK01_e=0x16,
    dRes_INDEX_BMS_BCK_BY1_TALK02_e=0x17,
    /* BDL  */
    dRes_INDEX_BMS_BDL_BY2_e=0x1A,
    dRes_INDEX_BMS_BDL_BY_EYE_e=0x1B,
    dRes_INDEX_BMS_BDL_BY_MASK_e=0x1C,
    dRes_INDEX_BMS_BDL_BY1_e=0x1D,
    dRes_INDEX_BMS_BDL_BY_LOW1_e=0x1E,
    dRes_INDEX_BMS_BDL_BY_LOW2_e=0x1F,
    dRes_INDEX_BMS_BDL_PTARU_e=0x20,
    /* BDLM */
    dRes_INDEX_BMS_BDL_BY_HEAD_e=0x23,
};

enum dRes_ID_BMS {
    /* BMDM */
    dRes_ID_BMS_BMD_SHOP_CURSOR01_e=0x4,
    /* BRK  */
    dRes_ID_BMS_BRK_SHOP_CURSOR01_e=0x5,
    /* BTP  */
    dRes_ID_BMS_BTP_BY_T01_e=0x8,
    dRes_ID_BMS_BTP_MABA01_e=0x9,
    /* BCKS */
    dRes_ID_BMS_BCK_BY2_WAIT00_e=0xA,
    dRes_ID_BMS_BCK_BY1_WAIT01_e=0xF,
    dRes_ID_BMS_BCK_BY1_WAIT02_e=0x10,
    dRes_ID_BMS_BCK_BY1_BOW_e=0x15,
    dRes_ID_BMS_BCK_BY1_TALK01_e=0x16,
    dRes_ID_BMS_BCK_BY1_TALK02_e=0x17,
    /* BDL  */
    dRes_ID_BMS_BDL_BY2_e=0xB,
    dRes_ID_BMS_BDL_BY_EYE_e=0xC,
    dRes_ID_BMS_BDL_BY_MASK_e=0xD,
    dRes_ID_BMS_BDL_BY1_e=0x11,
    dRes_ID_BMS_BDL_BY_LOW1_e=0x12,
    dRes_ID_BMS_BDL_BY_LOW2_e=0x13,
    dRes_ID_BMS_BDL_PTARU_e=0x14,
    /* BDLM */
    dRes_ID_BMS_BDL_BY_HEAD_e=0xE,
};

enum SHOP_CURSOR01_JNT {
    SHOP_CURSOR01_JNT_CURSOR01_e=0x0,
};

enum BY2_JNT {
    BY2_JNT_WORLD_ROOT_e=0x0,
    BY2_JNT_BACKBONE_e=0x1,
    BY2_JNT_HEAD_e=0x2,
    BY2_JNT_WAIST_e=0x3,
    BY2_JNT_LEG1_e=0x4,
    BY2_JNT_LEG2_e=0x5,
};

enum BY_EYE_JNT {
    BY_EYE_JNT_BY_EYE_e=0x0,
};

enum BY_MASK_JNT {
    BY_MASK_JNT_BY_MASK_e=0x0,
};

enum BY1_JNT {
    BY1_JNT_CENTER_e=0x0,
    BY1_JNT_BACKBONE_e=0x1,
    BY1_JNT_HEAD_e=0x2,
    BY1_JNT_SHOULDERL_e=0x3,
    BY1_JNT_ARML1_e=0x4,
    BY1_JNT_ARML2_e=0x5,
    BY1_JNT_HANDL_e=0x6,
    BY1_JNT_SHOULDERR_e=0x7,
    BY1_JNT_ARMR1_e=0x8,
    BY1_JNT_ARMR2_e=0x9,
    BY1_JNT_HANDR_e=0xA,
};

enum BY_LOW1_JNT {
    BY_LOW1_JNT_BY_LOW_BODY1_e=0x0,
};

enum BY_LOW2_JNT {
    BY_LOW2_JNT_BY_LOW_BODY2_e=0x0,
};

enum PTARU_JNT {
    PTARU_JNT_KTARU_01_e=0x0,
};

enum BY_HEAD_JNT {
    BY_HEAD_JNT_HEAD_CENTER_e=0x0,
    BY_HEAD_JNT_HAIRL_e=0x1,
    BY_HEAD_JNT_HAIRR_e=0x2,
};

#endif /* !RES_BMS_H */