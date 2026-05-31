#ifndef RES_HI_H
#define RES_HI_H

enum dRes_INDEX_HI {
    /* BCKS */
    dRes_INDEX_HI_BCK_HI_POSE_e=0x6,
    dRes_INDEX_HI_BCK_HI_WAIT01_e=0x7,
    /* BDLM */
    dRes_INDEX_HI_BDL_HI_e=0xA,
    /* BTP  */
    dRes_INDEX_HI_BTP_MABA_e=0xD,
    /* BTK  */
    dRes_INDEX_HI_BTK_HI_e=0x10,
};

enum dRes_ID_HI {
    /* BCKS */
    dRes_ID_HI_BCK_HI_POSE_e=0x0,
    dRes_ID_HI_BCK_HI_WAIT01_e=0x1,
    /* BDLM */
    dRes_ID_HI_BDL_HI_e=0x2,
    /* BTP  */
    dRes_ID_HI_BTP_MABA_e=0x3,
    /* BTK  */
    dRes_ID_HI_BTK_HI_e=0x4,
};

enum HI_JNT {
    HI_JNT_CENTER_e=0x0,
    HI_JNT_BACKBONE1_e=0x1,
    HI_JNT_BACKBONE2_e=0x2,
    HI_JNT_NECK_e=0x3,
    HI_JNT_HEAD_e=0x4,
    HI_JNT_EYEBROWL_e=0x5,
    HI_JNT_EYEBROWR_e=0x6,
    HI_JNT_EYEBROWCENTER_e=0x7,
    HI_JNT_MOUTHL_e=0x8,
    HI_JNT_MOUTHR_e=0x9,
    HI_JNT_MOUTHCENTER_e=0xA,
    HI_JNT_SHOULDERL_e=0xB,
    HI_JNT_ARML1_e=0xC,
    HI_JNT_ARML2_e=0xD,
    HI_JNT_HANDL_e=0xE,
    HI_JNT_FINGERL_e=0xF,
    HI_JNT_OYUBIL_e=0x10,
    HI_JNT_SLEEVEL1_e=0x11,
    HI_JNT_SLEEVEL2_e=0x12,
    HI_JNT_SLEEVEL3_e=0x13,
    HI_JNT_SHOULDERR_e=0x14,
    HI_JNT_ARMR1_e=0x15,
    HI_JNT_ARMR2_e=0x16,
    HI_JNT_HANDR_e=0x17,
    HI_JNT_FINGERR_e=0x18,
    HI_JNT_OYUBIR_e=0x19,
    HI_JNT_SLEEVER1_e=0x1A,
    HI_JNT_SLEEVER2_e=0x1B,
    HI_JNT_SLEEVER3_e=0x1C,
    HI_JNT_WAIST_e=0x1D,
    HI_JNT_GOWNL1_e=0x1E,
    HI_JNT_GOWNL2_e=0x1F,
    HI_JNT_GOWNR1_e=0x20,
    HI_JNT_GOWNR2_e=0x21,
    HI_JNT_LEGL1_e=0x22,
    HI_JNT_LEGL2_e=0x23,
    HI_JNT_FOOTL_e=0x24,
    HI_JNT_LEGR1_e=0x25,
    HI_JNT_LEGR2_e=0x26,
    HI_JNT_FOOTR_e=0x27,
    HI_JNT_SKIRTL_e=0x28,
    HI_JNT_SKIRTR_e=0x29,
};

#endif /* !RES_HI_H */