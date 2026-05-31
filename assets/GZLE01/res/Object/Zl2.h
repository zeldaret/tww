#ifndef RES_ZL2_H
#define RES_ZL2_H

enum dRes_INDEX_ZL2 {
    /* BCKS */
    dRes_INDEX_ZL2_BCK_WAIT_e=0x6,
    /* BDLM */
    dRes_INDEX_ZL2_BDL_ZL_e=0x9,
    /* BTK  */
    dRes_INDEX_ZL2_BTK_MABA_A_e=0xC,
    /* BTP  */
    dRes_INDEX_ZL2_BTP_MABA_A_e=0xF,
};

enum dRes_ID_ZL2 {
    /* BCKS */
    dRes_ID_ZL2_BCK_WAIT_e=0x0,
    /* BDLM */
    dRes_ID_ZL2_BDL_ZL_e=0x1,
    /* BTK  */
    dRes_ID_ZL2_BTK_MABA_A_e=0x2,
    /* BTP  */
    dRes_ID_ZL2_BTP_MABA_A_e=0x3,
};

enum ZL_JNT {
    ZL_JNT_WORLD_ROOT_e=0x0,
    ZL_JNT_STOMACH_e=0x1,
    ZL_JNT_CHEST_e=0x2,
    ZL_JNT_MAFFLER_L_e=0x3,
    ZL_JNT_MAFFLER_R_e=0x4,
    ZL_JNT_NECK_e=0x5,
    ZL_JNT_HEAD_e=0x6,
    ZL_JNT_CHIN_e=0x7,
    ZL_JNT_HAIR_e=0x8,
    ZL_JNT_MOMI_L_e=0x9,
    ZL_JNT_MOMI_R_e=0xA,
    ZL_JNT_ZL_EYE_e=0xB,
    ZL_JNT_ZL_MAYU_e=0xC,
    ZL_JNT_ZL_NOSE_e=0xD,
    ZL_JNT_SHOULDER_L_e=0xE,
    ZL_JNT_ARM_L1_e=0xF,
    ZL_JNT_ARM_L2_e=0x10,
    ZL_JNT_ZL_HAND_L_e=0x11,
    ZL_JNT_SHOULDER_R_e=0x12,
    ZL_JNT_ARM_R1_e=0x13,
    ZL_JNT_ARM_R2_e=0x14,
    ZL_JNT_ZL_HAND_R_e=0x15,
    ZL_JNT_WAIST_e=0x16,
    ZL_JNT_LEG_L0_e=0x17,
    ZL_JNT_LEG_L1_e=0x18,
    ZL_JNT_LEG_L2_e=0x19,
    ZL_JNT_FOOT_L_e=0x1A,
    ZL_JNT_LEG_R0_e=0x1B,
    ZL_JNT_LEG_R1_e=0x1C,
    ZL_JNT_LEG_R2_e=0x1D,
    ZL_JNT_FOOT_R_e=0x1E,
    ZL_JNT_ZL_GRIP_e=0x1F,
    ZL_JNT_ZL_POD_e=0x20,
    ZL_JNT_ZL_SACK_e=0x21,
};

#endif /* !RES_ZL2_H */