#ifndef RES_YM_H
#define RES_YM_H

enum dRes_INDEX_YM {
    /* BCKS */
    dRes_INDEX_YM_BCK_WAIT01_e=0x7,
    dRes_INDEX_YM_BCK_YM_KARI01_e=0x8,
    dRes_INDEX_YM_BCK_YM_KARI2WAIT_e=0x9,
    dRes_INDEX_YM_BCK_YM_KTALK_e=0xA,
    dRes_INDEX_YM_BCK_YM_KTALK02_e=0xB,
    dRes_INDEX_YM_BCK_YM_KWAIT_e=0xC,
    dRes_INDEX_YM_BCK_YM_NBTLOOK_e=0xD,
    dRes_INDEX_YM_BCK_YM_NBTTALK_e=0xE,
    dRes_INDEX_YM_BCK_YM_NBTWAIT_e=0xF,
    dRes_INDEX_YM_BCK_YM_SIT_e=0x10,
    dRes_INDEX_YM_BCK_YM_SITTALK_e=0x11,
    dRes_INDEX_YM_BCK_YM_TALK01_e=0x12,
    dRes_INDEX_YM_BCK_YM_WAIT02_e=0x13,
    /* BDL  */
    dRes_INDEX_YM_BDL_YMKAMA_e=0x16,
    /* BDLM */
    dRes_INDEX_YM_BDL_YM_e=0x19,
    dRes_INDEX_YM_BDL_YMHEAD01_e=0x1A,
    dRes_INDEX_YM_BDL_YMHEAD02_e=0x1B,
    /* BMT  */
    dRes_INDEX_YM_BMT_YM2_e=0x1E,
    /* BTP  */
    dRes_INDEX_YM_BTP_YMHEAD01_e=0x21,
    dRes_INDEX_YM_BTP_YMHEAD02_e=0x22,
};

enum dRes_ID_YM {
    /* BCKS */
    dRes_ID_YM_BCK_WAIT01_e=0x0,
    dRes_ID_YM_BCK_YM_KARI01_e=0x1,
    dRes_ID_YM_BCK_YM_KARI2WAIT_e=0x2,
    dRes_ID_YM_BCK_YM_KTALK_e=0x3,
    dRes_ID_YM_BCK_YM_KTALK02_e=0x4,
    dRes_ID_YM_BCK_YM_KWAIT_e=0x5,
    dRes_ID_YM_BCK_YM_NBTLOOK_e=0x6,
    dRes_ID_YM_BCK_YM_NBTTALK_e=0x7,
    dRes_ID_YM_BCK_YM_NBTWAIT_e=0x8,
    dRes_ID_YM_BCK_YM_SIT_e=0x10,
    dRes_ID_YM_BCK_YM_SITTALK_e=0x11,
    dRes_ID_YM_BCK_YM_TALK01_e=0x12,
    dRes_ID_YM_BCK_YM_WAIT02_e=0x13,
    /* BDL  */
    dRes_ID_YM_BDL_YMKAMA_e=0x9,
    /* BDLM */
    dRes_ID_YM_BDL_YM_e=0xA,
    dRes_ID_YM_BDL_YMHEAD01_e=0xB,
    dRes_ID_YM_BDL_YMHEAD02_e=0xC,
    /* BMT  */
    dRes_ID_YM_BMT_YM2_e=0xD,
    /* BTP  */
    dRes_ID_YM_BTP_YMHEAD01_e=0xE,
    dRes_ID_YM_BTP_YMHEAD02_e=0xF,
};

enum YMKAMA_JNT {
    YMKAMA_JNT_YMKAMA_e=0x0,
};

enum YM_JNT {
    YM_JNT_CENTER_e=0x0,
    YM_JNT_BACKBONE_e=0x1,
    YM_JNT_NECK_e=0x2,
    YM_JNT_HEAD_e=0x3,
    YM_JNT_SHOULDERL_e=0x4,
    YM_JNT_ARML1_e=0x5,
    YM_JNT_ARML2_e=0x6,
    YM_JNT_HANDL_e=0x7,
    YM_JNT_SHOULDERR_e=0x8,
    YM_JNT_ARMR1_e=0x9,
    YM_JNT_ARMR2_e=0xA,
    YM_JNT_HANDR_e=0xB,
    YM_JNT_WAIST_e=0xC,
    YM_JNT_LEGL1_e=0xD,
    YM_JNT_LEGL2_e=0xE,
    YM_JNT_FOOTL_e=0xF,
    YM_JNT_LEGR1_e=0x10,
    YM_JNT_LEGR2_e=0x11,
    YM_JNT_FOOTR_e=0x12,
};

enum YMHEAD01_JNT {
    YMHEAD01_JNT_YMHEAD1_e=0x0,
};

enum YMHEAD02_JNT {
    YMHEAD02_JNT_YM_HEAD02_e=0x0,
};

#endif /* !RES_YM_H */