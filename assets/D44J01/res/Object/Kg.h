#ifndef RES_KG_H
#define RES_KG_H

enum dRes_INDEX_KG {
    /* BDLM */
    dRes_INDEX_KG_BDL_KG_e=0x5,
    dRes_INDEX_KG_BDL_KG_PLATE_e=0x6,
    /* BTP  */
    dRes_INDEX_KG_BTP_KG_e=0x9,
    dRes_INDEX_KG_BTP_KG_PLATE_e=0xA,
    dRes_INDEX_KG_BTP_MOPEN_e=0xB,
    dRes_INDEX_KG_BTP_RADIO_e=0xC,
    dRes_INDEX_KG_BTP_WARAI_e=0xD,
    dRes_INDEX_KG_BTP_SLEEP_e=0xE,
    /* BCKS */
    dRes_INDEX_KG_BCK_KG_WAIT01_e=0x11,
    dRes_INDEX_KG_BCK_KG_CAPTAIN_e=0x12,
    dRes_INDEX_KG_BCK_KG_CAPTAIN02_e=0x13,
    dRes_INDEX_KG_BCK_KG_KAMAE_e=0x14,
    dRes_INDEX_KG_BCK_KG_KIDS_e=0x15,
    dRes_INDEX_KG_BCK_KG_KWAIT_e=0x16,
    dRes_INDEX_KG_BCK_KG_RADIO_e=0x17,
    dRes_INDEX_KG_BCK_KG_SASIKAE_e=0x18,
    dRes_INDEX_KG_BCK_KG_TALK01_e=0x19,
    dRes_INDEX_KG_BCK_KG_WAIT02_e=0x1A,
    dRes_INDEX_KG_BCK_KG_GONZO_e=0x1B,
    dRes_INDEX_KG_BCK_KG_TETORA_e=0x1C,
    dRes_INDEX_KG_BCK_KG_TETORA02_e=0x1D,
};

enum dRes_ID_KG {
    /* BDLM */
    dRes_ID_KG_BDL_KG_e=0x0,
    dRes_ID_KG_BDL_KG_PLATE_e=0x3,
    /* BTP  */
    dRes_ID_KG_BTP_KG_e=0x1,
    dRes_ID_KG_BTP_KG_PLATE_e=0x4,
    dRes_ID_KG_BTP_MOPEN_e=0x5,
    dRes_ID_KG_BTP_RADIO_e=0x6,
    dRes_ID_KG_BTP_WARAI_e=0x7,
    dRes_ID_KG_BTP_SLEEP_e=0x14,
    /* BCKS */
    dRes_ID_KG_BCK_KG_WAIT01_e=0x2,
    dRes_ID_KG_BCK_KG_CAPTAIN_e=0x8,
    dRes_ID_KG_BCK_KG_CAPTAIN02_e=0x9,
    dRes_ID_KG_BCK_KG_KAMAE_e=0xA,
    dRes_ID_KG_BCK_KG_KIDS_e=0xB,
    dRes_ID_KG_BCK_KG_KWAIT_e=0xC,
    dRes_ID_KG_BCK_KG_RADIO_e=0xD,
    dRes_ID_KG_BCK_KG_SASIKAE_e=0xE,
    dRes_ID_KG_BCK_KG_TALK01_e=0xF,
    dRes_ID_KG_BCK_KG_WAIT02_e=0x10,
    dRes_ID_KG_BCK_KG_GONZO_e=0x11,
    dRes_ID_KG_BCK_KG_TETORA_e=0x12,
    dRes_ID_KG_BCK_KG_TETORA02_e=0x13,
};

enum KG_JNT {
    KG_JNT_CENTER_e=0x0,
    KG_JNT_BACKBONE1_e=0x1,
    KG_JNT_BACKBONE2_e=0x2,
    KG_JNT_NECK_e=0x3,
    KG_JNT_HEAD_e=0x4,
    KG_JNT_SHOULDERL_e=0x5,
    KG_JNT_ARML1_e=0x6,
    KG_JNT_ARML2_e=0x7,
    KG_JNT_HANDL_e=0x8,
    KG_JNT_SHOULDERR_e=0x9,
    KG_JNT_ARMR1_e=0xA,
    KG_JNT_ARMR2_e=0xB,
    KG_JNT_HANDR_e=0xC,
    KG_JNT_WAIST_e=0xD,
    KG_JNT_LEGL1_e=0xE,
    KG_JNT_LEGL2_e=0xF,
    KG_JNT_FOOTL_e=0x10,
    KG_JNT_LEGR1_e=0x11,
    KG_JNT_LEGR2_e=0x12,
    KG_JNT_FOOTR_e=0x13,
};

enum KG_PLATE_JNT {
    KG_PLATE_JNT_KG_PLATE_e=0x0,
};

#endif /* !RES_KG_H */