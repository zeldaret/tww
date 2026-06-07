#ifndef RES_AH_H
#define RES_AH_H

enum dRes_INDEX_AH {
    /* BCKS */
    dRes_INDEX_AH_BCK_AH_WAIT01_e=0x5,
    dRes_INDEX_AH_BCK_AH_WAIT02_e=0x6,
    /* BDLM */
    dRes_INDEX_AH_BDL_AH_e=0x9,
    /* BTP  */
    dRes_INDEX_AH_BTP_HOU_e=0xC,
    dRes_INDEX_AH_BTP_MABA_e=0xD,
};

enum dRes_ID_AH {
    /* BCKS */
    dRes_ID_AH_BCK_AH_WAIT01_e=0x0,
    dRes_ID_AH_BCK_AH_WAIT02_e=0x1,
    /* BDLM */
    dRes_ID_AH_BDL_AH_e=0x2,
    /* BTP  */
    dRes_ID_AH_BTP_HOU_e=0x3,
    dRes_ID_AH_BTP_MABA_e=0x4,
};

enum AH_JNT {
    AH_JNT_CENTER_e=0x0,
    AH_JNT_BACKBONE_e=0x1,
    AH_JNT_NECK_e=0x2,
    AH_JNT_HEAD_e=0x3,
    AH_JNT_SHOULDERL_e=0x4,
    AH_JNT_ARML1_e=0x5,
    AH_JNT_ARML2_e=0x6,
    AH_JNT_HANDL_e=0x7,
    AH_JNT_SHOULDERR_e=0x8,
    AH_JNT_ARMR1_e=0x9,
    AH_JNT_ARMR2_e=0xA,
    AH_JNT_HANDR_e=0xB,
    AH_JNT_WAIST_e=0xC,
    AH_JNT_LEGL1_e=0xD,
    AH_JNT_LEGL2_e=0xE,
    AH_JNT_FOOTL_e=0xF,
    AH_JNT_LEGR1_e=0x10,
    AH_JNT_LEGR2_e=0x11,
    AH_JNT_FOOTR_e=0x12,
};

#endif /* !RES_AH_H */