#ifndef RES_ZK_H
#define RES_ZK_H

enum dRes_INDEX_ZK {
    /* BCKS */
    dRes_INDEX_ZK_BCK_ZK_TALK01_e=0x5,
    dRes_INDEX_ZK_BCK_ZK_TALK02_e=0x6,
    dRes_INDEX_ZK_BCK_ZK_WAIT01_e=0x7,
    dRes_INDEX_ZK_BCK_ZK_WAIT02_e=0x8,
    /* BDLM */
    dRes_INDEX_ZK_BDL_ZK_e=0xB,
    /* BTP  */
    dRes_INDEX_ZK_BTP_MABA_e=0xE,
};

enum dRes_ID_ZK {
    /* BCKS */
    dRes_ID_ZK_BCK_ZK_TALK01_e=0x0,
    dRes_ID_ZK_BCK_ZK_TALK02_e=0x1,
    dRes_ID_ZK_BCK_ZK_WAIT01_e=0x2,
    dRes_ID_ZK_BCK_ZK_WAIT02_e=0x3,
    /* BDLM */
    dRes_ID_ZK_BDL_ZK_e=0x4,
    /* BTP  */
    dRes_ID_ZK_BTP_MABA_e=0x5,
};

enum ZK_JNT {
    ZK_JNT_CENTER_e=0x0,
    ZK_JNT_BACKBONE_e=0x1,
    ZK_JNT_NECK_e=0x2,
    ZK_JNT_HEAD_e=0x3,
    ZK_JNT_HAIR1_e=0x4,
    ZK_JNT_HAIR2_e=0x5,
    ZK_JNT_SIDEHAIRL_e=0x6,
    ZK_JNT_SIDEHAIRR_e=0x7,
    ZK_JNT_SHOULDERL_e=0x8,
    ZK_JNT_ARML1_e=0x9,
    ZK_JNT_ARML2_e=0xA,
    ZK_JNT_HANDL_e=0xB,
    ZK_JNT_SHOULDERR_e=0xC,
    ZK_JNT_ARMR1_e=0xD,
    ZK_JNT_ARMR2_e=0xE,
    ZK_JNT_HANDR_e=0xF,
    ZK_JNT_WAIST_e=0x10,
    ZK_JNT_LEGL1_e=0x11,
    ZK_JNT_LEGL2_e=0x12,
    ZK_JNT_FOOTL_e=0x13,
    ZK_JNT_LEGR1_e=0x14,
    ZK_JNT_LEGR2_e=0x15,
    ZK_JNT_FOOTR_e=0x16,
    ZK_JNT_SKIRTFL1_e=0x17,
    ZK_JNT_SKIRTFL2_e=0x18,
    ZK_JNT_SKIRTFR1_e=0x19,
    ZK_JNT_SKIRTFR2_e=0x1A,
    ZK_JNT_SKIRTR1_e=0x1B,
    ZK_JNT_SKIRTR2_e=0x1C,
};

#endif /* !RES_ZK_H */