#ifndef RES_GBDOOR_H
#define RES_GBDOOR_H

enum dRes_INDEX_GBDOOR {
    /* BDL  */
    dRes_INDEX_GBDOOR_BDL_V_GBD_L_e=0x4,
    dRes_INDEX_GBDOOR_BDL_V_GBD_R_e=0x5,
    dRes_INDEX_GBDOOR_BDL_V_GBDFU_e=0x6,
    dRes_INDEX_GBDOOR_BDL_V_GBDTO_e=0x7,
    /* DZB  */
    dRes_INDEX_GBDOOR_DZB_GBD_e=0xA,
};

enum dRes_ID_GBDOOR {
    /* BDL  */
    dRes_ID_GBDOOR_BDL_V_GBD_L_e=0x4,
    dRes_ID_GBDOOR_BDL_V_GBD_R_e=0x5,
    dRes_ID_GBDOOR_BDL_V_GBDFU_e=0x6,
    dRes_ID_GBDOOR_BDL_V_GBDTO_e=0x7,
    /* DZB  */
    dRes_ID_GBDOOR_DZB_GBD_e=0xA,
};

enum V_GBD_L_JNT {
    V_GBD_L_JNT_V_GBD_L_e=0x0,
    V_GBD_L_JNT_HIDARI_e=0x1,
    V_GBD_L_JNT_DOOR_HIDARI_e=0x2,
};

enum V_GBD_R_JNT {
    V_GBD_R_JNT_V_GBD_R_e=0x0,
    V_GBD_R_JNT_MIGI_e=0x1,
    V_GBD_R_JNT_DOOR_MIGI_e=0x2,
};

enum V_GBDFU_JNT {
    V_GBDFU_JNT_V_GBDFU_e=0x0,
    V_GBDFU_JNT_FUTI_e=0x1,
    V_GBDFU_JNT_DOOR_FUTI_e=0x2,
};

enum V_GBDTO_JNT {
    V_GBDTO_JNT_V_GBDTO_e=0x0,
    V_GBDTO_JNT_TOME_e=0x1,
    V_GBDTO_JNT_DOOR_TOME_e=0x2,
};

#endif /* !RES_GBDOOR_H */