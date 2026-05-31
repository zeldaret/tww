#ifndef RES_MBDOOR_H
#define RES_MBDOOR_H

enum dRes_INDEX_MBDOOR {
    /* BDL  */
    dRes_INDEX_MBDOOR_BDL_S_MBD_L_e=0x4,
    dRes_INDEX_MBDOOR_BDL_S_MBD_R_e=0x5,
    dRes_INDEX_MBDOOR_BDL_S_MBDFU_e=0x6,
    dRes_INDEX_MBDOOR_BDL_S_MBDTO_e=0x7,
    /* DZB  */
    dRes_INDEX_MBDOOR_DZB_S_MBDFU_e=0xA,
};

enum dRes_ID_MBDOOR {
    /* BDL  */
    dRes_ID_MBDOOR_BDL_S_MBD_L_e=0x4,
    dRes_ID_MBDOOR_BDL_S_MBD_R_e=0x5,
    dRes_ID_MBDOOR_BDL_S_MBDFU_e=0x6,
    dRes_ID_MBDOOR_BDL_S_MBDTO_e=0x7,
    /* DZB  */
    dRes_ID_MBDOOR_DZB_S_MBDFU_e=0xA,
};

enum S_MBD_L_JNT {
    S_MBD_L_JNT_S_HIDARI_e=0x0,
    S_MBD_L_JNT_HIDARI_e=0x1,
    S_MBD_L_JNT_POLYSURFACE5_e=0x2,
};

enum S_MBD_R_JNT {
    S_MBD_R_JNT_S_MIGI_e=0x0,
    S_MBD_R_JNT_MIGI_e=0x1,
    S_MBD_R_JNT_POLYSURFACE6_e=0x2,
};

enum S_MBDFU_JNT {
    S_MBDFU_JNT_S_FUTI_e=0x0,
    S_MBDFU_JNT_FTI_e=0x1,
    S_MBDFU_JNT_OUT_WOOD_e=0x2,
};

enum S_MBDTO_JNT {
    S_MBDTO_JNT_S_TOME_e=0x0,
    S_MBDTO_JNT_TOME_e=0x1,
    S_MBDTO_JNT_PCUBE1_e=0x2,
};

#endif /* !RES_MBDOOR_H */