#ifndef RES_PZ_H
#define RES_PZ_H

enum dRes_INDEX_PZ {
    /* BCKS */
    dRes_INDEX_PZ_BCK_ARROW_RELORD_e=0x7,
    dRes_INDEX_PZ_BCK_ARROW_SHOOT_e=0x8,
    dRes_INDEX_PZ_BCK_ARROW_WAIT03_e=0x9,
    dRes_INDEX_PZ_BCK_DAM01_e=0xA,
    dRes_INDEX_PZ_BCK_DAM02_e=0xB,
    dRes_INDEX_PZ_BCK_DEFEND_e=0xC,
    dRes_INDEX_PZ_BCK_RELORD_e=0xD,
    dRes_INDEX_PZ_BCK_RUN01_e=0xE,
    dRes_INDEX_PZ_BCK_SHOOT_e=0xF,
    dRes_INDEX_PZ_BCK_STAND_e=0x10,
    dRes_INDEX_PZ_BCK_WAIT01_e=0x11,
    dRes_INDEX_PZ_BCK_WAIT02_e=0x12,
    dRes_INDEX_PZ_BCK_WAIT03_e=0x13,
    dRes_INDEX_PZ_BCK_WAIT04_e=0x14,
    /* BDLM */
    dRes_INDEX_PZ_BDL_BOW_e=0x17,
    dRes_INDEX_PZ_BDL_PZ_e=0x18,
    /* BRK  */
    dRes_INDEX_PZ_BRK_TRI_TEST_e=0x1B,
    /* BTK  */
    dRes_INDEX_PZ_BTK_BOW_WAIT_e=0x1E,
    dRes_INDEX_PZ_BTK_MABA_A_e=0x1F,
    dRes_INDEX_PZ_BTK_STAND_e=0x20,
    /* BTP  */
    dRes_INDEX_PZ_BTP_BOW_WAIT_e=0x23,
    dRes_INDEX_PZ_BTP_DAM01_e=0x24,
    dRes_INDEX_PZ_BTP_DAM02_e=0x25,
    dRes_INDEX_PZ_BTP_DEFEND_e=0x26,
    dRes_INDEX_PZ_BTP_MABA_A_e=0x27,
    dRes_INDEX_PZ_BTP_MABA_B_e=0x28,
    dRes_INDEX_PZ_BTP_STAND_e=0x29,
    dRes_INDEX_PZ_BTP_TALK01_e=0x2A,
    dRes_INDEX_PZ_BTP_TALK02_e=0x2B,
    dRes_INDEX_PZ_BTP_WAIT04_e=0x2C,
};

enum dRes_ID_PZ {
    /* BCKS */
    dRes_ID_PZ_BCK_ARROW_RELORD_e=0x7,
    dRes_ID_PZ_BCK_ARROW_SHOOT_e=0x8,
    dRes_ID_PZ_BCK_ARROW_WAIT03_e=0x9,
    dRes_ID_PZ_BCK_DAM01_e=0xA,
    dRes_ID_PZ_BCK_DAM02_e=0xB,
    dRes_ID_PZ_BCK_DEFEND_e=0xC,
    dRes_ID_PZ_BCK_RELORD_e=0xD,
    dRes_ID_PZ_BCK_RUN01_e=0xE,
    dRes_ID_PZ_BCK_SHOOT_e=0xF,
    dRes_ID_PZ_BCK_STAND_e=0x10,
    dRes_ID_PZ_BCK_WAIT01_e=0x11,
    dRes_ID_PZ_BCK_WAIT02_e=0x12,
    dRes_ID_PZ_BCK_WAIT03_e=0x13,
    dRes_ID_PZ_BCK_WAIT04_e=0x14,
    /* BDLM */
    dRes_ID_PZ_BDL_BOW_e=0x17,
    dRes_ID_PZ_BDL_PZ_e=0x18,
    /* BRK  */
    dRes_ID_PZ_BRK_TRI_TEST_e=0x1B,
    /* BTK  */
    dRes_ID_PZ_BTK_BOW_WAIT_e=0x1E,
    dRes_ID_PZ_BTK_MABA_A_e=0x1F,
    dRes_ID_PZ_BTK_STAND_e=0x20,
    /* BTP  */
    dRes_ID_PZ_BTP_BOW_WAIT_e=0x23,
    dRes_ID_PZ_BTP_DAM01_e=0x24,
    dRes_ID_PZ_BTP_DAM02_e=0x25,
    dRes_ID_PZ_BTP_DEFEND_e=0x26,
    dRes_ID_PZ_BTP_MABA_A_e=0x27,
    dRes_ID_PZ_BTP_MABA_B_e=0x28,
    dRes_ID_PZ_BTP_STAND_e=0x29,
    dRes_ID_PZ_BTP_TALK01_e=0x2A,
    dRes_ID_PZ_BTP_TALK02_e=0x2B,
    dRes_ID_PZ_BTP_WAIT04_e=0x2C,
};

enum PZ_BOW_JNT {
    PZ_BOW_JNT_CL_BOW_e=0x0,
    PZ_BOW_JNT_BOW_JNT_e=0x1,
    PZ_BOW_JNT_AA_JNT_e=0x2,
    PZ_BOW_JNT_AB_JNT_e=0x3,
    PZ_BOW_JNT_ACJNT_e=0x4,
    PZ_BOW_JNT_LINEAA_JNT_e=0x5,
    PZ_BOW_JNT_LINEAB_JNT_e=0x6,
    PZ_BOW_JNT_BA_JNT_e=0x7,
    PZ_BOW_JNT_BB_JNT_e=0x8,
    PZ_BOW_JNT_BC_JNT_e=0x9,
    PZ_BOW_JNT_LINEBA_JNT_e=0xA,
    PZ_BOW_JNT_LINEBB_JNT_e=0xB,
};

enum PZ_JNT {
    PZ_JNT_WORLD_ROOT_e=0x0,
    PZ_JNT_STOMACH_e=0x1,
    PZ_JNT_CHEST_e=0x2,
    PZ_JNT_NECK_e=0x3,
    PZ_JNT_HEAD_e=0x4,
    PZ_JNT_CHIN_e=0x5,
    PZ_JNT_HAIR_1_e=0x6,
    PZ_JNT_HAIR_2_e=0x7,
    PZ_JNT_HAIR_3_e=0x8,
    PZ_JNT_MOMI_L_e=0x9,
    PZ_JNT_MOMI_R_e=0xA,
    PZ_JNT_SHOULDER_L_e=0xB,
    PZ_JNT_ARM_L1_e=0xC,
    PZ_JNT_ARM_L2_e=0xD,
    PZ_JNT_HAND_L1_e=0xE,
    PZ_JNT_HAND_L2_e=0xF,
    PZ_JNT_SHOULDER_R_e=0x10,
    PZ_JNT_ARM_R1_e=0x11,
    PZ_JNT_ARM_R2_e=0x12,
    PZ_JNT_HAND_R1_e=0x13,
    PZ_JNT_HAND_R2_e=0x14,
    PZ_JNT_WAIST_e=0x15,
    PZ_JNT_LEG_1_e=0x16,
    PZ_JNT_LEG_2_e=0x17,
    PZ_JNT_SKIRT_1_e=0x18,
    PZ_JNT_SKIRT_2_e=0x19,
    PZ_JNT_SKIRT_3_e=0x1A,
};

#endif /* !RES_PZ_H */