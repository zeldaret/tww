#ifndef RES_P1_H
#define RES_P1_H

enum dRes_INDEX_P1 {
    /* BMT  */
    dRes_INDEX_P1_BMT_P1B_BODY_e=0x7,
    dRes_INDEX_P1_BMT_P1C_BODY_e=0x8,
    /* BTP  */
    dRes_INDEX_P1_BTP_MABA_A_e=0xB,
    dRes_INDEX_P1_BTP_MABA_B_e=0xC,
    dRes_INDEX_P1_BTP_MABA_C_e=0xD,
    dRes_INDEX_P1_BTP_P1A_DUMMY_TEX_ALL_e=0xE,
    /* BDL  */
    dRes_INDEX_P1_BDL_P1_e=0x11,
    dRes_INDEX_P1_BDL_DORA_STICK_e=0x12,
    /* BDLM */
    dRes_INDEX_P1_BDL_P1A_HEAD_e=0x15,
    dRes_INDEX_P1_BDL_P1B_HEAD_e=0x16,
    dRes_INDEX_P1_BDL_P1C_HEAD_e=0x17,
    /* BCKS */
    dRes_INDEX_P1_BCK_ANGRY_e=0x1A,
    dRes_INDEX_P1_BCK_C_STOP_e=0x1B,
    dRes_INDEX_P1_BCK_C_TALK01_e=0x1C,
    dRes_INDEX_P1_BCK_C_TALK02_e=0x1D,
    dRes_INDEX_P1_BCK_C_WAIT_e=0x1E,
    dRes_INDEX_P1_BCK_CHECK01_e=0x1F,
    dRes_INDEX_P1_BCK_CHECK02_e=0x20,
    dRes_INDEX_P1_BCK_LOOK_e=0x21,
    dRes_INDEX_P1_BCK_OMOKJ_e=0x22,
    dRes_INDEX_P1_BCK_TALK_e=0x23,
    dRes_INDEX_P1_BCK_TALK02_e=0x24,
    dRes_INDEX_P1_BCK_TALK03_e=0x25,
    dRes_INDEX_P1_BCK_TALK04_e=0x26,
    dRes_INDEX_P1_BCK_TORIKJ_e=0x27,
    dRes_INDEX_P1_BCK_WAIT_e=0x28,
    dRes_INDEX_P1_BCK_WAIT02_e=0x29,
};

enum dRes_ID_P1 {
    /* BMT  */
    dRes_ID_P1_BMT_P1B_BODY_e=0xA,
    dRes_ID_P1_BMT_P1C_BODY_e=0x28,
    /* BTP  */
    dRes_ID_P1_BTP_MABA_A_e=0xB,
    dRes_ID_P1_BTP_MABA_B_e=0xC,
    dRes_ID_P1_BTP_MABA_C_e=0x29,
    dRes_ID_P1_BTP_P1A_DUMMY_TEX_ALL_e=0x46,
    /* BDL  */
    dRes_ID_P1_BDL_P1_e=0x31,
    dRes_ID_P1_BDL_DORA_STICK_e=0x35,
    /* BDLM */
    dRes_ID_P1_BDL_P1A_HEAD_e=0x32,
    dRes_ID_P1_BDL_P1B_HEAD_e=0x33,
    dRes_ID_P1_BDL_P1C_HEAD_e=0x34,
    /* BCKS */
    dRes_ID_P1_BCK_ANGRY_e=0x4D,
    dRes_ID_P1_BCK_C_STOP_e=0x50,
    dRes_ID_P1_BCK_C_TALK01_e=0x51,
    dRes_ID_P1_BCK_C_TALK02_e=0x52,
    dRes_ID_P1_BCK_C_WAIT_e=0x53,
    dRes_ID_P1_BCK_CHECK01_e=0x54,
    dRes_ID_P1_BCK_CHECK02_e=0x55,
    dRes_ID_P1_BCK_LOOK_e=0x57,
    dRes_ID_P1_BCK_OMOKJ_e=0x58,
    dRes_ID_P1_BCK_TALK_e=0x59,
    dRes_ID_P1_BCK_TALK02_e=0x5A,
    dRes_ID_P1_BCK_TALK03_e=0x5B,
    dRes_ID_P1_BCK_TALK04_e=0x5C,
    dRes_ID_P1_BCK_TORIKJ_e=0x5D,
    dRes_ID_P1_BCK_WAIT_e=0x5E,
    dRes_ID_P1_BCK_WAIT02_e=0x5F,
};

enum P1_JNT {
    P1_JNT_WORLD_ROOT_e=0x0,
    P1_JNT_BACKBONE_e=0x1,
    P1_JNT_NECK_e=0x2,
    P1_JNT_HEAD_e=0x3,
    P1_JNT_SHOULDERL_e=0x4,
    P1_JNT_ARML1_e=0x5,
    P1_JNT_ARML2_e=0x6,
    P1_JNT_HANDL_e=0x7,
    P1_JNT_SHOULDERR_e=0x8,
    P1_JNT_ARMR1_e=0x9,
    P1_JNT_ARMR2_e=0xA,
    P1_JNT_HANDR_e=0xB,
    P1_JNT_WAIST_e=0xC,
    P1_JNT_LEGL1_e=0xD,
    P1_JNT_LEGL2_e=0xE,
    P1_JNT_FOOTL_e=0xF,
    P1_JNT_LEGR1_e=0x10,
    P1_JNT_LEGR2_e=0x11,
    P1_JNT_FOOTR_e=0x12,
};

enum DORA_STICK_JNT {
    DORA_STICK_JNT_DORA_STICK_e=0x0,
};

enum P1A_HEAD_JNT {
    P1A_HEAD_JNT_P1A_HEAD_ALL_e=0x0,
};

enum P1B_HEAD_JNT {
    P1B_HEAD_JNT_P1B_HEAD_ALL_e=0x0,
};

enum P1C_HEAD_JNT {
    P1C_HEAD_JNT_C_HEAD_e=0x0,
};

#endif /* !RES_P1_H */